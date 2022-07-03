#ifndef IMANAGEDATABASE_H
#define IMANAGEDATABASE_H

#include "storage_global.h"

#include <QtSql/QtSql>

/**
 * @brief Interface pour la gestion de la structure d'une base de données SQL.
 * Fournit des méthodes pour créer les tables et l'insertion des données préliminaires.
 * 
 * @throw std::runtime_error Toutes les méthodes en cas d'erreur lors des opérations.
 */
class STORAGE_EXPORT IManageDatabase
{
public:
    virtual ~IManageDatabase() {};

    /// Créer toutes les tables.
    virtual void createTables() const = 0;
    /// Créer la table General.
    virtual void createTableGeneral() const = 0;
    /// Créer la table Contact.
    virtual void createTableContact() const = 0;
    /// Créer la table Interaction.
    virtual void createTableInteraction() const = 0;
    /// Créer la table Todo.
    virtual void createTableTodo() const = 0;
    /// Insérer des données de test.
    virtual void insertMockData() const = 0;
};

#endif // IMANAGEDATABASE_H
