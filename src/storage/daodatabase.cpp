#include "daodatabase.h"
#include "managesqlite.h"

QSqlDatabase DaoDatabase::database;
IManageDatabase *DaoDatabase::manager = nullptr;

void DaoDatabase::openSQLite(const QString &path)
{
    DaoDatabase::close();

    bool isNew = !QFileInfo::exists(path);

    DaoDatabase::database = QSqlDatabase::addDatabase("QSQLITE");
    DaoDatabase::database.setDatabaseName(path);
    DaoDatabase::manager = new ManageSQLite();

    if (!DaoDatabase::database.open())
    {
        throw std::runtime_error("Impossible d'ouvrir la base de données SQLite : " + DaoDatabase::database.lastError().text().toStdString());
    }

    DaoDatabase::database.exec("PRAGMA foreign_keys = ON");

    // Si la base de données est vierge, l'initialiser.
    if (isNew)
    {
        try {
            manager->createTables();
        }  catch (std::exception & e) {
            // Si problème, supprimer le fichier de la base de données.
            DaoDatabase::close();
            QFile::remove(path);
            qDebug() << e.what();
            throw e;
        }
    }
}

void DaoDatabase::close()
{
    DaoDatabase::database.close();
}

QSqlDatabase &DaoDatabase::getDatabase()
{
    return DaoDatabase::database;
}

void DaoDatabase::setDatabase(const QSqlDatabase &newDatabase)
{
    DaoDatabase::close();
    DaoDatabase::database = newDatabase;
}

IManageDatabase const*DaoDatabase::getManager()
{
    return DaoDatabase::manager;
}
