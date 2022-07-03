#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <iostream>
#include "date.h"

using namespace std;

/// Modèle stockant les informations d'un todo d'une interaction.
class TodoModel
{
private:
    /// Identifiant unique du todo.
    unsigned int id;
    /// Date de réalisation du todo.
    Date dateTodo;
    /// Résumé du todo.
    string resume;

public:
    /**
     * Correspond au prochain identifiant qui sera utilisé à la création
     * d'un nouveau todo. S'incrémente à chaque nouveau todo.
     * @brief Numéro d'identifiant maximal généré.
     */
    static unsigned int idCount;

    /* -------------------------------------------------------------------------- */
    /*                                Constructeurs                               */
    /* -------------------------------------------------------------------------- */

    /**
     * @brief Constructeur par défaut.
     * Identifiant généré automatiquement, et date de réalisation initialisée à la date du jour.
     * @param resume Résumé du todo (ne doit pas être vide).
     * @throw std::invalid_argument Voir les exceptions de @link TodoModel::setResume() @endlink.
     */
    TodoModel(const string &resume);
    /**
     * @brief Créer une instance pré-initialisée.
     * @param id Identifiant unique.
     * @param dateTodo Date de réalisation du todo (ne doit pas être vide).
     * @param resume Résumé du todo (ne doit pas être vide).
     * @throw std::invalid_argument Voir les exceptions de @link TodoModel::setResume() @endlink.
     * @throw std::invalid_argument Voir les exceptions de @link TodoModel::setDateTodo() @endlink.
     */
    TodoModel(unsigned int id, const Date &dateTodo, const string &resume);
    /**
     * @brief Constructeur par copie.
     * @param todo Todo à copier.
     */
    TodoModel(const TodoModel &todo);

    /* -------------------------------------------------------------------------- */
    /*                                 Opérateurs                                 */
    /* -------------------------------------------------------------------------- */

    /// Retourne un todo copié d'un autre todo.
    TodoModel &operator=(const TodoModel &todo);
    /// Retourne @a true si les attributs des deux todos sont égaux.
    bool operator==(const TodoModel &todo) const;
    /// Retourne @a true si les attributs des deux todos ne sont pas égaux.
    bool operator!=(const TodoModel &todo) const;
    /// Retourne un flux sortant avec les attributs du todo.
    friend ostream &operator<<(ostream &out, const TodoModel &todo);

    /* -------------------------------------------------------------------------- */
    /*                                 Propriétés                                 */
    /* -------------------------------------------------------------------------- */

    /// Retourner l'identifiant unique du todo.
    unsigned int getId() const;
    /// Retourner la date de réalisation du todo.
    const Date &getDateTodo() const;
    /// Retourner le résumé.
    const string &getResume() const;
    /**
     * @brief Définir le date de réalisation du todo.
     * @param newDateTodo Nouvelle date de réalisation.
     * @throw std::invalid_argument Date de réalisation vide.
     */
    void setDateTodo(const Date &newDateTodo);
    /**
     * @brief Définir le résumé du todo.
     * @param newResume Résumé du todo.
     * @throw std::invalid_argument Résumé vide.
     */
    void setResume(const string &newResume);
};

#endif // TODOMODEL_H
