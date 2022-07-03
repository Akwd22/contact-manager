#ifndef INTERACTIONMODEL_H
#define INTERACTIONMODEL_H

#include <string>
#include <iostream>
#include <regex>
#include "todocollection.h"
#include "todomodel.h"

using namespace std;

/**
 * @brief Modèle stockant les informations d'une interaction d'un contact.
 * @n
 * @n Une interaction possède un contenu texte contenant un commentaire et/ou des tags comme \@todo ou \@date.
 * @n Voir @link InteractionModel::parseTodos() @endlink pour plus d'explications concernant les tags.
 * @n Voir @link InteractionModel::setContenu() @endlink pour un exemple de contenu.
 * @see TodoModel
 */
class InteractionModel
{
private:
    /// Identifiant unique de l'interaction.
    unsigned int id;
    /// Date de création.
    Date dateInteraction;
    /// Contenu de l'interaction.
    string contenu;
    /// Liste des todos associés à l'interaction.
    mutable TodoCollection todos;

public:
    /**
     * Correspond au prochain identifiant qui sera utilisé à la création
     * d'une nouvelle interaction. S'incrémente à chaque nouvelle interaction.
     * @brief Numéro d'identifiant maximal généré.
     */
    static unsigned int idCount;

    /* -------------------------------------------------------------------------- */
    /*                                Constructeurs                               */
    /* -------------------------------------------------------------------------- */

    /**
     * @brief Constructeur par défaut.
     * Identifiant généré automatiquement, et date de création initialisée à la date du jour.
     * @param contenu Contenu de l'interaction (ne doit pas être vide).
     * @throw std::invalid_argument Voir les exceptions de @link InteractionModel::setContenu() @endlink.
     */
    InteractionModel(const string &contenu);
    /**
     * @brief Créer une instance pré-initialisée.
     * @param id Identifiant unique.
     * @param dateInteraction Date de création de l'interaction (ne doit pas être vide).
     * @param contenu Contenu de l'interaction (ne doit pas être vide).
     * @throw std::invalid_argument Voir les exceptions de @link InteractionModel::setContenu() @endlink.
     * @throw std::invalid_argument Date de création vide.
     */
    InteractionModel(unsigned int id, const Date &dateInteraction, const string &contenu);
    /**
     * @brief Constructeur par copie.
     * @param interaction Interaction à copier.
     */
    InteractionModel(const InteractionModel &interaction);

    /* -------------------------------------------------------------------------- */
    /*                                  Méthodes                                  */
    /* -------------------------------------------------------------------------- */

    /**
     * @brief Analyser le contenu de l'interaction et en extraire les todos.
     * Les todos extraits sont instanciés et ajoutés à la liste des todos de l'interaction.
     * @note
     * Pour chaque ligne du contenu, s'il n'y a pas de tag \@todo, la ligne est ignorée.
     * @n Si la ligne contient un \@todo, une instance @link TodoModel @endlink est créée et est ajoutée à la liste @link InteractionModel::todos @endlink.
     * @n S'il y a également un tag \@date, la date du todo est celle décrite par le tag, sinon c'est la date du jour qui est assignée.
     * @throw std::runtime_error Date de réalisation d'un todo < date du jour.
     */
    void parseTodos();

    /* -------------------------------------------------------------------------- */
    /*                                 Opérateurs                                 */
    /* -------------------------------------------------------------------------- */

    /// Retourne une interaction copiée d'une autre date.
    InteractionModel &operator=(const InteractionModel &interaction);
    /// Retourne @a true si les attributs sont égaux à ceux de l'autre interaction.
    bool operator==(const InteractionModel &interaction) const;
    /// Retourne @a true si les attributs ne pas sont égaux à ceux de l'autre interaction.
    bool operator!=(const InteractionModel &interaction) const;
    /// Retourne un flux sortant avec les attributs de l'interaction.
    friend ostream &operator<<(ostream &out, const InteractionModel &interaction);

    /* -------------------------------------------------------------------------- */
    /*                                 Propriétés                                 */
    /* -------------------------------------------------------------------------- */

    /// Retourner l'identifiant unique de l'interaction.
    unsigned int getId() const;
    /// Retourner la date de création.
    const Date &getDateInteraction() const;
    /// Retourner le contenu de l'interaction.
    const string &getContenu() const;
    /**
     * @brief Définir le contenu de l'interaction.
     * @param newContenu Contenu de l'interaction.
     * @throw std::invalid_argument Contenu vide.
     * @details
     * <b>Exemple de contenu :</b>
     * @n Mon interaction
     * @n \@todo Rendez-vous chef \@date 01/10/2021
     * @n \@todo Rendez-vous client \@date 1-10-2021
     * @n Un autre commentaire
     * @n Encore un autre commentaire \@todo Faire les courses
     * @n \@todo Appeler fournisseur\@date 22/07/2022Un dernier commentaire
     */
    void setContenu(const string &newContenu);
    /// Retourner la liste des todos associés à l'interaction.
    TodoCollection &getTodos() const;
};

#endif // INTERACTIONMODEL_H
