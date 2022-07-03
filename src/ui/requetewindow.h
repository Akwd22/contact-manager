#ifndef REQUETEWINDOW_H
#define REQUETEWINDOW_H

#include <contactcollection.h>

#include <QDialog>

namespace Ui {
class RequeteWindow;
}

/**
 * @brief Fenêtre permettant d'effectuer et d'afficher des requêtes sur les interactions et les todos.
 * @note La fenêtre est modale.
 */
class RequeteWindow : public QDialog
{
    Q_OBJECT

/// Énumérations des sujets de requête possible.
enum class Sujet {
    /// Rechercher des interactions.
    Interactions,
    /// Rechercher des todos.
    Todos,
    /// Rechercher des \@date de todos.
    DatesTodo
};

public:
    /**
     * @brief Constructeur par défaut.
     * @param contacts Référence vers la liste de l'ensemble des contacts.
     */
    explicit RequeteWindow(const ContactCollection & contacts, QWidget *parent = nullptr);
    ~RequeteWindow();

private:
    /// Initialiser les widgets.
    void initWidgets();

    /// Actualiser la liste déroulante affichant l'ensemble des contacts.
    void refreshComboBox();
    /// Actualiser la zone des résultats.
    void refreshResults();

    /// Effectuer une requête des interactions selon les filtres choisis.
    void queryInteractions();
    /// Effectuer une requête des todos selon les filtres choisis.
    void queryTodos();

private slots:
    /// Exécuter la recherche.
    void rechercher();

    /// Slot lors du toggle de la radio @a Interactions.
    void on_radioInteractions_toggled(bool checked);
    /// Slot lors du toggle de la radio @a Todos.
    void on_radioTodos_toggled(bool checked);
    /// Slot lors du toggle de la radio @a Dates @a todos.
    void on_radioDatesTodo_toggled(bool checked);

private:
    Ui::RequeteWindow *ui;

    /// Référence vers la liste de l'ensemble des contacts.
    const ContactCollection & contacts;

    /// Sujet de recherche choisi.
    enum Sujet sujet = Sujet::Interactions;

    /// Liste des contacts filtrés.
    ContactCollection filteredContacts;
    /// Liste des interactions filtrées.
    InteractionCollection filteredInteractions;
    /// Liste des todos filtrés.
    TodoCollection filteredTodos;
};

#endif // REQUETEWINDOW_H
