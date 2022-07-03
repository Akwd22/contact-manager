#ifndef TODOCOLLECTION_H
#define TODOCOLLECTION_H

#include <list>
#include "collection.h"
#include "todomodel.h"

using namespace std;

/// Classe collection de @link TodoModel @endlink.  Permet d'effectuer des filtres sur la liste de todos.
class TodoCollection : public Collection<TodoModel>
{
public:
    /**
     * @brief Retourner l'instance d'un todo à partir de son identifiant.
     * @throw std::runtime_error Todo n'existe pas dans la collection.
     */
    TodoModel &getById(unsigned int id) const;
    /// Filtrer la liste pour ne garder que le todo d'identifiant @p id.
    TodoCollection &filterId(unsigned int id);
    /// Filtrer les todos ayant pour date de réalisation @p date.
    TodoCollection &filterDateRealisation(const Date & date);
    /**
     * @brief Filtrer les todos ayant pour date de réalisation dans une intervalle de dates.
     * @param dateMin Date minimale. Si date nulle, alors seuls les todos dont date de réalisation <= @p dateMax sont retenus.
     * @param dateMax Date maximale. Si date nulle, alors seuls les todos dont date de réalisation >= @p dateMin sont retenus.
     */
    TodoCollection &filterDateRealisation(const Date & dateMin, const Date & dateMax);

    /// Retourner les \@dates de l'ensemble des todos de la collection.
    Collection<Date> getDates() const;
};

#endif // TODOCOLLECTION_H
