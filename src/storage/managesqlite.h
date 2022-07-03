#ifndef MANAGESQLITE_H
#define MANAGESQLITE_H

#include "imanagedatabase.h"
#include "storage_global.h"

/**
 * @brief Classe pour la gestion de la structure d'une base de données SQLite.
 * @throw std::runtime_error Toutes les méthodes en cas d'erreur lors des opérations.
 */
class STORAGE_EXPORT ManageSQLite : public IManageDatabase
{
public:
    void createTables() const;
    void createTableGeneral() const;
    void createTableContact() const;
    void createTableInteraction() const;
    void createTableTodo() const;
    void insertMockData() const;
};

#endif // MANAGESQLITE_H
