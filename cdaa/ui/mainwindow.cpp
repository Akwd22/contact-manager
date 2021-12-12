#include "contacteditwindow.h"
#include "mainwindow.h"
#include "requetewindow.h"
#include "ui_mainwindow.h"

#include <daodatabase.h>
#include <stdqt.h>
#include <sqlitedaocontact.h>
#include <sqlitedaogeneral.h>
#include <sqlitedaointeraction.h>
#include <sqlitedaotodo.h>
#include <QMessageBox>
#include <QFileDialog>
#include <idump.h>
#include <dumpjson.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->ui->frameFilter->setVisible(false);
    this->ui->dateEditMin->setDate(QDate::currentDate());
    this->ui->dateEditMax->setDate(QDate::currentDate());

    this->init();
    this->refreshTable();

    connect(this->ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(on_itemDoubleClicked(QTableWidgetItem*)));
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
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'initialisation de la base de données. Relancez l'application.");
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
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données. Essayez de réparer dans Fichier -> Réparer.");
        qDebug() << e.what();
    }
}

void MainWindow::loadData()
{
    ContactModel::idCount = this->daoContact->readMaxId();
    InteractionModel::idCount = this->daoInteraction->readMaxId();
    TodoModel::idCount = this->daoTodo->readMaxId();

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

void MainWindow::refreshTable()
{
    this->ui->tableWidget->setRowCount(0);
    unsigned int nbC = this->contacts.count();

    QString s;
    s.setNum(nbC);
    this->ui->labelResult->setText("Résultat(s) : " + s);

    for(unsigned int i=0;i<nbC;i++){
        ContactModel & c = this->contacts.getIndex(i);

        QTableWidgetItem * prenom = new QTableWidgetItem(StdQt::string(c.getPrenom()));
        prenom->setData(Qt::UserRole, QVariant(i));

        QTableWidgetItem * nom = new QTableWidgetItem(StdQt::string(c.getNom()));
        nom->setData(Qt::UserRole, QVariant(i));

        QTableWidgetItem * entreprise = new QTableWidgetItem(StdQt::string(c.getEntreprise()));
        entreprise->setData(Qt::UserRole, QVariant(i));

        QTableWidgetItem * datecreation = new QTableWidgetItem(StdQt::string(c.getDateCreation().toString()));
        datecreation->setData(Qt::UserRole, QVariant(i));

        this->ui->tableWidget->insertRow(i);

        this->ui->tableWidget->setItem(i, 0, prenom);
        this->ui->tableWidget->setItem(i, 1, nom);
        this->ui->tableWidget->setItem(i, 2, entreprise);
        this->ui->tableWidget->setItem(i, 3, datecreation);
    }
}

void MainWindow::on_itemDoubleClicked(QTableWidgetItem *item)
{
    unsigned int idContact = item->data(Qt::UserRole).toUInt();
    ContactModel & original = this->contacts.getIndex(idContact);
    ContactModel nouveau = original;
    ContactEditWindow editC(nouveau, true);
    int ret = editC.exec();
    if(ret == 2)
    {
        try {
            daoContact->destroy(original.getId());
            contacts.remove(original);
            refreshTable();
        }  catch (std::runtime_error & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }

    }

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


void MainWindow::on_actionQuit_triggered()
{
    this->close();
}


void MainWindow::on_actionExportJson_triggered()
{
    QString chemin = QFileDialog::getSaveFileName(this, QString(), QString(), "JSON (*.json)");
    DumpJson dump(chemin);

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
            daoContact->destroyAll();
            contacts.clear();
            refreshTable();
        }  catch (std::runtime_error & e) {
            QMessageBox::critical(this, "Erreur", e.what());
        }
    }
}


void MainWindow::on_buttonReset_clicked()
{

}


void MainWindow::on_buttonFiltrer_clicked()
{

}


void MainWindow::on_buttonRequest_clicked()
{
    RequeteWindow win(this->contacts);
    win.exec();
}


void MainWindow::on_ButtonCreateContact_clicked()
{
    ContactModel c;
    ContactEditWindow editC(c, false);
    int ret = editC.exec();
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


void MainWindow::on_dateEditMin_userDateChanged(const QDate &date)
{

}

void MainWindow::on_actionDonneesTest_triggered()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "Question", "Voulez-vous insérer les données de test ? Les données existantes seront supprimées.");

    if (button == QMessageBox::Yes)
    {
        try {
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

