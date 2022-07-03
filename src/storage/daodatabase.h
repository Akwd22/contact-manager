#ifndef DAODATABASE_H
#define DAODATABASE_H

#include "imanagedatabase.h"
#include "storage_global.h"

#include <QtSql/QtSql>

/**
 * @brief Classe statique pour gérer la connexion à une base de données.
 * 
 * La connexion est effective pour toute l'application, et qu'une seule connexion à la fois est possible.
 */
class STORAGE_EXPORT DaoDatabase
{
public:
    virtual ~DaoDatabase() = 0;

    /**
     * @brief Ouvrir une base de données SQLite.
     * Si la base de données n'existe pas, sa structure est initialisée.
     * 
     * @param path Chemin du fichier de base de données SQLite.
     * @throw std::runtime_error Connexion impossible.
     * @throw std::runtime_error Erreur lors de l'initialisation de la structure de la base de données.
     */
    static void openSQLite(const QString & path);
    /// Fermer la connexion active.
    static void close();

    /// Retourner la connexion à la base de données actuelle.
    static QSqlDatabase &getDatabase();
    /// Définir une nouvelle connexion à la base de données. L'ancienne connexion est fermée.
    static void setDatabase(const QSqlDatabase &newDatabase);

    /// Retourner le manager de base de données.
    static IManageDatabase const*getManager();

private:
    /// Connexion à la base de données.
    static QSqlDatabase database;
    /// Manager de la base de données.
    static IManageDatabase * manager;
};

#endif // DAODATABASE_H
