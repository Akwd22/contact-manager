#ifndef INTERACTIONCOLLECTION_H
#define INTERACTIONCOLLECTION_H

#include "collection.h"
#include "interactionmodel.h"

using namespace std;

/// Classe collection de @link InteractionModel @endlink.  Permet d'effectuer des filtres sur la liste d'interactions.
class InteractionCollection : public Collection<InteractionModel>
{
public:
    /**
     * @brief Retourner l'instance d'une interaction à partir de son identifiant.
     * @throw std::runtime_error Interaction n'existe pas dans la collection.
     */
    InteractionModel &getById(unsigned int id) const;
    /// Filtrer la liste pour ne garder que l'interaction d'identifiant @p id.
    InteractionCollection &filterId(unsigned int id);
    /// Filtrer les interactions ayant pour date de création @p date.
    InteractionCollection &filterDateCreation(const Date & date);
    /**
     * @brief Filtrer les interactions ayant pour date de création dans une intervalle de dates.
     * @param dateMin Date minimale. Si date nulle, alors seules les interactions dont date de création <= @p dateMax sont retenues.
     * @param dateMax Date maximale. Si date nulle, alors seules les interactions dont date de création >= @p dateMin sont retenues.
     */
    InteractionCollection &filterDateCreation(const Date & dateMin, const Date & dateMax);
    
    /// Retourner les todos de l'ensemble des interactions de la collection.
    TodoCollection getTodos() const;
};

#endif // INTERACTIONCOLLECTION_H
