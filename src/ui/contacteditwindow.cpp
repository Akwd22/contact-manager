#include "interactioneditwindow.h"
#include "contacteditwindow.h"
#include "ui_contacteditwindow.h"

#include <sqlitedaointeraction.h>
#include <sqlitedaotodo.h>
#include <stdqt.h>

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

ContactEditWindow::ContactEditWindow(ContactModel &cm, bool isEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactEditWindow),
    cm(cm),
    isEdit(isEdit)
{
    this->setWindowFlags(Qt::Window);
    this->ui->setupUi(this);

    this->daoInteraction = new SQLiteDaoInteraction();
    this->daoTodo = new SQLiteDaoTodo();

    this->initWidgets();

    this->connect(this->ui->buttonEnregister, SIGNAL(clicked()), this, SLOT(enregistrer()));
    this->connect(this->ui->buttonAnnuler, SIGNAL(clicked()), this, SLOT(annuler()));
    this->connect(this->ui->buttonSupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    this->connect(this->ui->buttonCreateInteraction, SIGNAL(clicked()), this, SLOT(creerInteraction()));
    this->connect(this->ui->ButtonPhoto, SIGNAL(clicked()), this, SLOT(editPhoto()));
    this->connect(this->ui->tableWidgetInteraction, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(editInteraction(QTableWidgetItem*)));
}

ContactEditWindow::~ContactEditWindow()
{
    delete this->ui;
    delete this->daoInteraction;
    delete this->daoTodo;
}



void ContactEditWindow::initWidgets()
{
    // Désactiver le bouton Enregister s'il n'y a pas de nom ou prénom renseigné.
    ui->buttonEnregister->setDisabled(cm.getNom().empty() || cm.getPrenom().empty());

    // Désactiver les boutons Supprimer et Créer interaction en mode création.
    if(!isEdit){
        this->ui->buttonSupprimer->setVisible(false);
        this->ui->buttonCreateInteraction->setEnabled(false);
    }

    // Afficher en premier les todos les plus urgents.
    this->ui->tableWidgetTodos->sortItems(0, Qt::AscendingOrder);

    // Afficher les données du contact.
    this->ui->lineEditPrenom->setText(StdQt::string(cm.getPrenom()));
    this->ui->lineEditNom->setText(StdQt::string(cm.getNom()));
    this->ui->lineEditEntreprise->setText(StdQt::string(cm.getEntreprise()));
    this->ui->lineEditTel->setText(StdQt::string(cm.getTel()));
    this->ui->lineEditEmail->setText(StdQt::string(cm.getEmail()));

    // Afficher la photo du contact, sinon celle par défaut.
    QString str = cm.getPhoto().empty() ? ":/resources/assets/profil.png" : StdQt::string(cm.getPhoto());
    this->ui->ButtonPhoto->setIcon(QIcon(str));
    this->ui->ButtonPhoto->setIconSize(QSize(64,64));

    // Afficher la date de création.
    this->ui->labelDateCreation->setText("Date de création : " + StdQt::string(cm.getDateCreation().toString()));

    // Afficher la date de dernière modification du contact.
    Date dateModif = cm.getDateModification();
    QLabel * labelDM =  this->ui->labelDerniereModification;
    dateModif.isNull() ? labelDM->setVisible(false) : labelDM->setText("Dernière date de modification : " +StdQt::string(dateModif.toString()));

    // Afficher les interactions et todos du contact.
    this->refreshInteractionsAndTodosTable();
}



void ContactEditWindow::supprimer()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "Question", "Voulez-vous vraiment supprimer ce contact ?");

    if(QMessageBox::Yes == button)
    {
        this->done(2);
    }
}

void ContactEditWindow::enregistrer()
{
    try {
        if(isEdit){
            Date d;
            d.setNow();
            cm.setDateModification(d);
        }
        cm.setPrenom(StdQt::string(this->ui->lineEditPrenom->text()));
        cm.setNom(StdQt::string(this->ui->lineEditNom->text()));
        cm.setEntreprise(StdQt::string(this->ui->lineEditEntreprise->text()));
        cm.setEmail(StdQt::string(this->ui->lineEditEmail->text()));
        cm.setTel(StdQt::string(this->ui->lineEditTel->text()));

        this->done(1);
    }  catch (std::invalid_argument & e) {
        QMessageBox::warning(this, "Avertissement", e.what());
    }
}

void ContactEditWindow::annuler()
{
    this->done(0);
}



void ContactEditWindow::creerInteraction()
{
    InteractionModel i(" ");
    InteractionEditWindow editI(i, false);
    int ret = editI.exec();

    // L'interaction a été crée.
    if(ret == 1){
        try {
            daoInteraction->create(cm.getId(), i);

            // Créer les todos.
            i.parseTodos();
            for (TodoModel & newTodo : i.getTodos().getList())
            {
                this->daoTodo->create(i.getId(), newTodo);
            }

            cm.getInteractions().add(i);

            refreshInteractionsAndTodosTable();
        }  catch (std::exception & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }
    }
}

void ContactEditWindow::editInteraction(QTableWidgetItem *item)
{
    unsigned int idInteraction = item->data(Qt::UserRole).toUInt();
    InteractionModel & original = this->cm.getInteractions().getById(idInteraction);
    InteractionModel nouveau = original;
    InteractionEditWindow editI(nouveau, true);
    int ret = editI.exec();

    // L'interaction a été supprimée.
    if(ret == 2)
    {
        try {
            daoInteraction->destroy(original.getId());
            cm.getInteractions().remove(original);

            refreshInteractionsAndTodosTable();
        }  catch (std::exception & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }

    }

    // L'interaction a été mis à jour.
    if(ret == 1)
    {
        try {
            daoInteraction->update(nouveau);

            // Supprimer les anciens todos.
            this->daoTodo->destroyAll(idInteraction);

            // Ajouter les nouveaux todos.
            original = nouveau;
            original.parseTodos();

            for (TodoModel & newTodo : nouveau.getTodos().getList())
            {
                this->daoTodo->create(nouveau.getId(), newTodo);
            }

            refreshInteractionsAndTodosTable();
        }  catch (std::exception & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }
    }
}

void ContactEditWindow::editPhoto()
{
    // Charger l'image.
    QString chemin = QFileDialog::getOpenFileName(this, QString(), QString(), "Image (*.png *.jpg *.jpeg)");
    if(chemin.isEmpty()) return;

    // Afficher la photo sur l'IHM.
    QImage img(chemin);
    QImage img2 = img.scaled(64,64, Qt::KeepAspectRatio);
    QPixmap pixmap =  QPixmap::fromImage(img2);
    this->ui->ButtonPhoto->setIcon(QIcon(pixmap));
    this->ui->ButtonPhoto->setIconSize(QSize(64,64));

    // Copier l'image chargée dans le répertoire des photos des contacts.
    // Le nom de l'image porte l'identifiant du contact.
    QFileInfo fileInfo(chemin);
    QString destinationFile = "photos/" + StdQt::string(std::to_string(cm.getId())) + "." + fileInfo.suffix();
    if (!QDir("photos").exists()) QDir().mkdir("photos");
    QFile::remove(destinationFile);
    QFile::copy(chemin, destinationFile);

    // Modifier l'URI de la photo du contact.
    cm.setPhoto(StdQt::string(destinationFile));
}



void ContactEditWindow::refreshInteractionsAndTodosTable()
{
    this->ui->tableWidgetTodos->setSortingEnabled(false);

    // Vider les tables.
    this->ui->tableWidgetInteraction->setRowCount(0);
    this->ui->tableWidgetTodos->setRowCount(0);

    unsigned nbI = this->cm.getInteractions().count();
    int curTodosIndexTable = 0;

    //INTERACTIONS TABLE
    for(unsigned int i=0;i<nbI;i++){
        InteractionModel & inte = this->cm.getInteractions().getIndex(i);

        // Case de date interaction.
        QTableWidgetItem * dateInter = new QTableWidgetItem();
        dateInter->setData(Qt::DisplayRole, StdQt::string(inte.getDateInteraction().toString()));
        dateInter->setData(Qt::UserRole, QVariant(inte.getId()));

        // Case de contenu interaction.
        QTableWidgetItem * contenu = new QTableWidgetItem(StdQt::string(inte.getContenu()));
        contenu->setData(Qt::UserRole, QVariant(inte.getId()));

        this->ui->tableWidgetInteraction->insertRow(i);

        this->ui->tableWidgetInteraction->setItem(i, 0, dateInter);
        this->ui->tableWidgetInteraction->setItem(i, 1, contenu);

        //TODOS TABLE
        for(unsigned int j=0;j<inte.getTodos().count();j++){
            TodoModel & todo = inte.getTodos().getIndex(j);

            // Case de date réalisation.
            QTableWidgetItem * dateRea = new QTableWidgetItem();
            dateRea->setData(Qt::DisplayRole, StdQt::date(todo.getDateTodo()));
            dateRea->setData(Qt::UserRole, QVariant(todo.getId()));

            // Case de résumé du todo.
            QTableWidgetItem * tache = new QTableWidgetItem(StdQt::string(todo.getResume()));
            tache->setData(Qt::UserRole, QVariant(todo.getId()));

            this->ui->tableWidgetTodos->insertRow(curTodosIndexTable);

            this->ui->tableWidgetTodos->setItem(curTodosIndexTable, 0, dateRea);
            this->ui->tableWidgetTodos->setItem(curTodosIndexTable, 1, tache);

            curTodosIndexTable++;
        }
    }

    // Trier les todos les plus urgents en premier.
    this->ui->tableWidgetTodos->setSortingEnabled(true);
    this->ui->tableWidgetTodos->sortItems(0, Qt::AscendingOrder);
}



void ContactEditWindow::on_lineEditPrenom_textChanged()
{
     ui->buttonEnregister->setDisabled(this->ui->lineEditPrenom->text().isEmpty() || this->ui->lineEditNom->text().isEmpty());
}

void ContactEditWindow::on_lineEditNom_textChanged()
{
    ui->buttonEnregister->setDisabled(this->ui->lineEditNom->text().isEmpty() || this->ui->lineEditPrenom->text().isEmpty());
}
