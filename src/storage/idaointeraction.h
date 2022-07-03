#ifndef IDAOINTERACTION_H
#define IDAOINTERACTION_H

#include "storage_global.h"

#include <interactioncollection.h>
#include <interactionmodel.h>

/**
 * @brief Interface DAO pour les opérations CRUD sur les instances de type @link InteractionModel @endlink.
 * @throw std::runtime_error Toutes les méthodes en cas d'erreur lors de l'opération.
 */
class STORAGE_EXPORT IDaoInteraction
{
public:
    virtual ~IDaoInteraction() {};

    /// Retourner l'identifiant maximal jamais généré pour une interaction.
    virtual unsigned int readMaxId() const = 0;

    /// Créer un interaction pour un contact d'identifiant @p contactId.
    virtual void create(unsigned int contactId, const InteractionModel & interaction) const = 0;
    /// Retourner toutes les interactions enregistrées pour un contact d'identifiant @p contactId (sans leurs todos).
    virtual InteractionCollection readAll(unsigned int contactId) const = 0;
    /// Mettre à jour une interaction avec des nouvelles données.
    virtual void update(const InteractionModel & interaction) const = 0;
    /// Détruire une interaction à partir de son identifiant @p id.
    virtual void destroy(unsigned int id) const = 0;
};

#endif // IDAOINTERACTION_H
