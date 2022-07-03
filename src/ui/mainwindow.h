#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <idaocontact.h>
#include <idaogeneral.h>
#include <idaointeraction.h>
#include <idaotodo.h>
#include <contactcollection.h>
#include "requetewindow.h"

#include <QLabel>
#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// Fenêtre principale de l'application. Elle affiche notamment la liste des contacts et permet d'accéder aux autres fenêtres
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /// Initialiser l'application.
    void init();
    /// Charger les données depuis la base de données.
    void loadData();

    /// Initialiser les widgets.
    void initWidgets();
    /// Initialiser la status bar.
    void statusBar();

    /// Actualiser la table des contacts en prenant source la liste des contacts filtrés @link contactsFiltered @endlink.
    void refreshTable();
    /// Actualiser la status bar.
    void refreshStatusBar();
    /// Actualiser la liste @link contactsFiltered @endlink selon la recherche de l'utilisateur.
    void refreshFilteredContact();

private:
    Ui::MainWindow *ui;

    /// DAO des attributs globaux.
    IDaoGeneral * daoGeneral;
    /// DAO des contacts.
    IDaoContact * daoContact;
    /// DAO des interactions.
    IDaoInteraction * daoInteraction;
    /// DAO des todos.
    IDaoTodo * daoTodo;

    /// Liste de l'ensemble des contacts.
    ContactCollection contacts;
    /// Liste des contacts filtrés selon la recherche de l'utilisateur.
    ContactCollection contactsFiltered;

    /// Panneau des filtres ouverts ?
    bool isFilterOpen = false;

    /// Label affichant la date de dernière suppression dans la status bar.
    QLabel * lastSuppr;
    /// Label affichant le nombre de contacts totals dans la status bar.
    QLabel * nbContact;

private slots:
    /// Réinitialiser la recherche de l'utilisateur.
    void resetFiltres();
    /// Exécuter la recherche de l'utilisateur.
    void filtrer();

    /// Modifier un contact.
    void editContact(QTableWidgetItem*item);
    /// Créer un contact.
    void creerContact();

    /// Slot lors du déclenchement de l'action <em>Insérer les données de test</em> du menu.
    void on_actionDonneesTest_triggered();
    /// Slot lors du déclenchement de l'action <em>Réinitialiser les données</em> du menu.
    void on_actionResetAll_triggered();
    /// Slot lors du déclenchement de l'action <em>Exporter en JSON</em> du menu.
    void on_actionExportJson_triggered();
    /// Slot lors du déclenchement de l'action @a Quitter du menu.
    void on_actionQuit_triggered();

    /// Slot lors du clique sur le bouton <em>Faire une requête</em>.
    void on_buttonRequest_clicked();
    /// Slot lors du clique sur le bouton <em>Ouvrir les filtres</em>.
    void on_buttonOpenFilter_clicked();
};
#endif // MAINWINDOW_H
