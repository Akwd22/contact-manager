#ifndef IDAOCONTACT_H
#define IDAOCONTACT_H

#include "storage_global.h"

#include <contactcollection.h>
#include <contactmodel.h>

/**
 * @brief Interface DAO pour les opérations CRUD sur les instances de type @link ContactModel @endlink.
 * @throw std::runtime_error Toutes les méthodes en cas d'erreur lors de l'opération.
 */
class STORAGE_EXPORT IDaoContact
{
public:
    virtual ~IDaoContact() {};

    /// Retourner l'identifiant maximal jamais généré pour un contact.
    virtual unsigned int readMaxId() const = 0;

    /// Créer un contact.
    virtual void create(const ContactModel & contact) const = 0;
    /// Retourner tous les contacts enregistrés (sans leur interactions, ni todos).
    virtual ContactCollection readAll() const = 0;
    /// Mettre à jour un contact avec des nouvelles données.
    virtual void update(const ContactModel & contact) const = 0;
    /// Détruire un contact à partir de son identifiant @p id.
    virtual void destroy(unsigned int id) const = 0;
    /// Détruire tous les contacts enregistrés.
    virtual void destroyAll() const = 0;
};

#endif // IDAOCONTACT_H
