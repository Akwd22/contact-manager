#ifndef CONTACTCOLLECTION_H
#define CONTACTCOLLECTION_H

#include "collection.h"
#include "contactmodel.h"

using namespace std;

/// Classe collection de @link ContactModel @endlink. Permet d'effectuer des filtres sur la liste de contacts.
class ContactCollection : public Collection<ContactModel>
{
public:
    /**
     * @brief Retourner l'instance d'un contact à partir de son identifiant.
     * @throw std::runtime_error Contact n'existe pas dans la collection.
     */
    ContactModel &getById(unsigned int id) const;
    /// Filtrer la liste pour ne garder que le contact d'identifiant @p id.
    ContactCollection &filterId(unsigned int id);
    /// Filtrer les contacts dont @p prenom est contenu dans leur prénom sans respecter la casse.
    ContactCollection &filterPrenom(const string & prenom);
    /// Filtrer les contacts dont @p nom est contenu dans leur nom sans respecter la casse.
    ContactCollection &filterNom(const string & nom);
    /// Filtrer les contacts dont @p entreprise est contenu dans leur entreprise sans respecter la casse.
    ContactCollection &filterEntreprise(const string & entreprise);
    /// Filtrer les contacts ayant pour date de création @p date.
    ContactCollection &filterDateCreation(const Date & date);
    /**
     * @brief Filtrer les contacts ayant pour date de création dans une intervalle de dates.
     * @param dateMin Date minimale. Si date nulle, alors seuls les contacts dont date de création <= @p dateMax sont retenus.
     * @param dateMax Date maximale. Si date nulle, alors seuls les contacts dont date de création >= @p dateMin sont retenus.
     */
    ContactCollection &filterDateCreation(const Date & dateMin, const Date & dateMax);
    
    /// Retourner les interactions de l'ensemble des contacts de la collection.
    InteractionCollection getInteractions() const;
    /// Retourner les todos de l'ensemble des contacts de la collection.
    TodoCollection getTodos() const;
};

#endif // CONTACTCOLLECTION_H
