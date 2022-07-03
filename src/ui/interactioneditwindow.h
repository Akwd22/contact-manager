#ifndef INTERACTIONEDITWINDOW_H
#define INTERACTIONEDITWINDOW_H

#include <interactionmodel.h>

#include <QDialog>
#include <QWidget>

namespace Ui {
class InteractionEditWindow;
}

/**
 * @brief Fenêtre permettant de créer ou modifier une interaction.
 * 
 * La fenêtre possède deux modes :
 * - Mode de création : permet de créer une interaction, mais pas de la supprimer.
 * - Mode de modification : permet de modifier le contenu de l'interaction, et de la supprimer.
 * 
 * @note La fenêtre est modale.
 */
class InteractionEditWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur par défaut.
     * @param im Référence de l'interaction à remplir ou à modifier.
     * @param isEdit Créer la fenêtre pour le mode de modification ?
     */
    explicit InteractionEditWindow(InteractionModel &im, bool isEdit, QWidget *parent = nullptr);
    ~InteractionEditWindow();

private:
    /// Initialiser les widgets.
    void initWidgets();

private slots:
    /// Enregister l'interaction et fermer la fenêtre.
    void enregistrer();
    /// Annuler la modification et fermer la fenêtre.
    void annuler();
    /// Supprimer l'interaction et fermer la fenêtre.
    void supprimer();

private:
    Ui::InteractionEditWindow *ui;
    /// Référence vers l'instance de l'interaction à remplir ou modifier.
    InteractionModel &im;
    /// En mode de modification ?
    bool isEdit = true;
};

#endif // INTERACTIONEDITWINDOW_H
