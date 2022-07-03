#ifndef IDAOTODO_H
#define IDAOTODO_H

#include "storage_global.h"

#include <todocollection.h>
#include <todomodel.h>

/**
 * @brief Interface DAO pour les opérations CRUD sur les instances de type @link TodoModel @endlink.
 * @throw std::runtime_error Toutes les méthodes en cas d'erreur lors de l'opération.
 */
class STORAGE_EXPORT IDaoTodo
{
public:
    virtual ~IDaoTodo() {};

    /// Retourner l'identifiant maximal jamais généré pour un todo.
    virtual unsigned int readMaxId() const = 0;

    /// Créer un todo pour une interaction d'identifiant @p interactionId.
    virtual void create(unsigned int interactionId, const TodoModel & todo) const = 0;
    /// Retourner tous les todos enregistrés pour une interaction d'identifiant @p interactionId.
    virtual TodoCollection readAll(unsigned int interactionId) const = 0;
    /// Mettre à jour un todo avec des nouvelles données.
    virtual void update(const TodoModel & todo) const = 0;
    /// Détruire un todo à partir de son identifiant @p id.
    virtual void destroy(unsigned int id) const = 0;
    /// Détruire tous les todos d'une interaction d'identifiant @p interactionId.
    virtual void destroyAll(unsigned int interactionId) const = 0;
};

#endif // IDAOTODO_H
