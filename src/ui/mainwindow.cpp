#include "contacteditwindow.h"
#include "requetewindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <daodatabase.h>
#include <stdqt.h>
#include <sqlitedaocontact.h>
#include <sqlitedaogeneral.h>
#include <sqlitedaointeraction.h>
#include <sqlitedaotodo.h>
#include <idump.h>
#include <dumpjson.h>

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->init();
    this->initWidgets();

    this->connect(this->ui->buttonFiltrer, SIGNAL(clicked()), this, SLOT(filtrer()));
    this->connect(this->ui->buttonReset, SIGNAL(clicked()), this, SLOT(resetFiltres()));
    this->connect(this->ui->ButtonCreateContact, SIGNAL(clicked()), this, SLOT(creerContact()));
    this->connect(this->ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(editContact(QTableWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete this->ui;

    delete this->daoContact;
    delete this->daoGeneral;
    delete this->daoInteraction;
    delete this->daoTodo;

    DaoDatabase::close();
}



void MainWindow::init()
{
    // Ouvrir la base de données.
    try {
        DaoDatabase::openSQLite("database.db");
    }  catch (std::exception & e) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'initialisation de la base de données. Relancez l'application. Raison : " + QString(e.what()));
        return;
    }

    // Instanciation des DAO.
    this->daoContact = new SQLiteDaoContact();
    this->daoInteraction = new SQLiteDaoInteraction();
    this->daoTodo = new SQLiteDaoTodo();
    this->daoGeneral = new SQLiteDaoGeneral();

    // Charger les données.
    try {
        this->loadData();
    }  catch (std::exception & e) {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données.");
        qDebug() << e.what();
    }
}

void MainWindow::initWidgets()
{
    this->ui->frameFilter->setVisible(false);
    this->ui->dateEditMin->setDate(QDate::currentDate());
    this->ui->dateEditMax->setDate(QDate::currentDate());

    this->statusBar();
    this->refreshTable();
}

void MainWindow::loadData()
{
    ContactModel::idCount = this->daoContact->readMaxId();
    InteractionModel::idCount = this->daoInteraction->readMaxId();
    TodoModel::idCount = this->daoTodo->readMaxId();

    ContactModel::setDateSuppression(StdQt::date(this->daoGeneral->read("dateSuppression")));

    this->contacts.replace(daoContact->readAll());

    for (ContactModel & contact : this->contacts.getList())
    {
        contact.getInteractions().replace(daoInteraction->readAll(contact.getId()));

        for (InteractionModel & interaction : contact.getInteractions().getList())
        {
            interaction.getTodos().replace(daoTodo->readAll(interaction.getId()));
        }
    }
}

void MainWindow::statusBar()
{
    this->lastSuppr = new QLabel();
    this->nbContact = new QLabel();
    this->ui->statusbar->addWidget(this->lastSuppr, 0);
    this->ui->statusbar->addWidget(this->nbContact, 0);
    this->lastSuppr->setText("Dernière suppression : XX/XX/XXXX");
    this->nbContact->setText("Nombre de contacts :");
    this->refreshStatusBar();
}



void MainWindow::refreshStatusBar()
{
    // Nombre de contacts.
    QString nbLabelContactCount;
    nbLabelContactCount.setNum(this->contacts.count());
    this->nbContact->setText("Nombre de contacts : " + nbLabelContactCount);

    // Date dernière suppression.
    Date dLastSuppr = ContactModel::getDateSuppression();
    QString sLastSuppr = !dLastSuppr.isNull() ? StdQt::string(dLastSuppr.toString()) : "Pas de suppression récente";
    this->lastSuppr->setText("Dernière suppression : " + sLastSuppr + "\t");
}

void MainWindow::refreshFilteredContact()
{
    this->contactsFiltered = contacts;
    Date dateMin;
    Date dateMax;
    string filterEntreprise;
    string filterNom;
    string filterPrenom;

    // Date Filter
    if (this->ui->checkBoxDateMin->isChecked()) dateMin = StdQt::date(this->ui->dateEditMin->date());
    if (this->ui->checkBoxDateMax->isChecked()) dateMax = StdQt::date(this->ui->dateEditMax->date());

    this->contactsFiltered.filterDateCreation(dateMin, dateMax);

    // Filter Entreprise
    if (!this->ui->lineEditFilterEntreprise->text().isEmpty()) filterEntreprise = StdQt::string(this->ui->lineEditFilterEntreprise->text());
    this->contactsFiltered.filterEntreprise(filterEntreprise);

    // Filter Nom
    if (!this->ui->lineEditFilterNom->text().isEmpty()) filterNom = StdQt::string(this->ui->lineEditFilterNom->text());
    this->contactsFiltered.filterNom(filterNom);

    // Filter Prenom
    if (!this->ui->lineEditFilterPrenom->text().isEmpty()) filterPrenom = StdQt::string(this->ui->lineEditFilterPrenom->text());
    this->contactsFiltered.filterPrenom(filterPrenom);
}

void MainWindow::refreshTable()
{
    this->refreshFilteredContact();
    this->refreshStatusBar();

    unsigned int nbC = this->contactsFiltered.count();

    // Mettre à jour le nombre de résultats.
    this->ui->labelResult->setText("Résultat(s) : " + StdQt::string(std::to_string(nbC)));

    // Vider la table.
    this->ui->tableWidget->setRowCount(0);
    this->ui->tableWidget->setSortingEnabled(false);

    // Remplir la table à patir des contacts filtrés.
    for(unsigned int i=0;i<nbC;i++){
        ContactModel & c = this->contactsFiltered.getIndex(i);

        // Case prénom.
        QTableWidgetItem * prenom = new QTableWidgetItem(StdQt::string(c.getPrenom()));
        prenom->setData(Qt::UserRole, QVariant(c.getId()));

        // Case nom.
        QTableWidgetItem * nom = new QTableWidgetItem(StdQt::string(c.getNom()));
        nom->setData(Qt::UserRole, QVariant(c.getId()));

        // Case entreprise.
        QTableWidgetItem * entreprise = new QTableWidgetItem(StdQt::string(c.getEntreprise()));
        entreprise->setData(Qt::UserRole, QVariant(c.getId()));

        // Case date de création.
        QTableWidgetItem * datecreation = new QTableWidgetItem();
        datecreation->setData(Qt::DisplayRole, StdQt::string(c.getDateCreation().toString()));
        datecreation->setData(Qt::UserRole, QVariant(c.getId()));

        this->ui->tableWidget->insertRow(i);

        this->ui->tableWidget->setItem(i, 0, prenom);
        this->ui->tableWidget->setItem(i, 1, nom);
        this->ui->tableWidget->setItem(i, 2, entreprise);
        this->ui->tableWidget->setItem(i, 3, datecreation);
    }

    this->ui->tableWidget->setSortingEnabled(true);
}



void MainWindow::creerContact()
{
    ContactModel c;

    ContactEditWindow editC(c, false);
    int ret = editC.exec();

    // Le contact a été créé.
    if(ret == 1){
        try {
            daoContact->create(c);
            contacts.add(c);

            refreshTable();
        }  catch (std::runtime_error & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }
    }
}

void MainWindow::editContact(QTableWidgetItem *item)
{
    unsigned int idContact = item->data(Qt::UserRole).toUInt();

    ContactModel & original = this->contacts.getById(idContact);
    ContactModel nouveau = original;

    ContactEditWindow editC(nouveau, true);
    int ret = editC.exec();

    // Le contact a été supprimé.
    if(ret == 2)
    {
        try {
            daoContact->destroy(original.getId());

            // Supprimer le fichier de la photo du contact.
            QFile::remove(StdQt::string(original.getPhoto()));
            contacts.remove(original);

            // Set la date de dernière suppression
            Date dateSuppr;
            dateSuppr.setNow();
            daoGeneral->update("dateSuppression", QVariant(StdQt::date(dateSuppr)));
            ContactModel::setDateSuppression(dateSuppr);

            refreshTable();
        }  catch (std::runtime_error & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }

    }

    // Le contact a été mis à jour.
    if(ret == 1)
    {
        try {
            daoContact->update(nouveau);
            original = nouveau;

            refreshTable();
        }  catch (std::runtime_error & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }
    }
}



void MainWindow::resetFiltres()
{
    this->ui->lineEditFilterEntreprise->setText("");
    this->ui->lineEditFilterNom->setText("");
    this->ui->lineEditFilterPrenom->setText("");
    this->ui->dateEditMin->setEnabled(false);
    this->ui->dateEditMax->setEnabled(false);
    this->ui->checkBoxDateMin->setChecked(false);
    this->ui->checkBoxDateMax->setChecked(false);
    this->refreshTable();
}

void MainWindow::filtrer()
{
    this->refreshTable();
}



void MainWindow::on_buttonOpenFilter_clicked()
{
    if(isFilterOpen){
        isFilterOpen = false;
        ui->frameFilter->setVisible(isFilterOpen);
    }
    else {
        isFilterOpen = true;
        ui->frameFilter->setVisible(isFilterOpen);
    }
}

void MainWindow::on_buttonRequest_clicked()
{
    RequeteWindow win(this->contacts);
    win.exec();
}



void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionExportJson_triggered()
{
    QString chemin = QFileDialog::getSaveFileName(this, QString(), QString(), "JSON (*.json)");
    DumpJson dump(chemin);

    if (chemin.isEmpty()) return;

    try {
        dump.dumpAll(this->contacts);
        QMessageBox::information(this, "Information", "Exportation des données en JSON avec succès.");
    }  catch (std::exception & e) {
        QMessageBox::critical(this, "Erreur", e.what());
    }
}

void MainWindow::on_actionResetAll_triggered()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "Question", "Voulez-vous vraiment réinitialiser toutes les données ?");

    if(QMessageBox::Yes == button){
        try{
            // Détruire tous les données.
            daoContact->destroyAll();
            contacts.clear();

            // Mettre à jour la date de dernière suppression.
            daoGeneral->update("dateSuppression", QVariant(StdQt::date(Date())));
            ContactModel::setDateSuppression(Date());

            refreshTable();
        }  catch (std::exception & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }
    }
}

void MainWindow::on_actionDonneesTest_triggered()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "Question", "Voulez-vous insérer les données de test ? Les données existantes seront supprimées.");

    if (button == QMessageBox::Yes)
    {
        try {
            // Détruire tous les données.
            this->daoContact->destroyAll();
            this->contacts.clear();

            DaoDatabase::getManager()->insertMockData();
            this->loadData();

            this->refreshTable();
        }  catch (std::exception & e) {
            QMessageBox::critical(this, "Erreur", "Impossible d'insérer les données de test.");
            qDebug() << e.what();
        }
    }
}








