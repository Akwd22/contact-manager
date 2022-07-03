#include "managesqlite.h"
#include "sqlitedaocontact.h"
#include "sqlitedaointeraction.h"
#include "sqlitedaotodo.h"

#include <contactmodel.h>

void ManageSQLite::createTables() const
{
    this->createTableGeneral();
    this->createTableContact();
    this->createTableInteraction();
    this->createTableTodo();
}

void ManageSQLite::createTableGeneral() const
{
    QSqlQuery query1(
        "CREATE TABLE IF NOT EXISTS General ( \
          attribut            TEXT PRIMARY KEY NOT NULL, \
          valeur              TEXT \
        )"
    );

    QSqlQuery query2("INSERT OR IGNORE INTO General VALUES ('dateSuppression', NULL)");

    if (!query1.exec())
    {
        throw std::runtime_error("Impossible de créer la table General : " + query1.lastError().text().toStdString());
    }

    if (!query2.exec())
    {
        throw std::runtime_error("Impossible d'insérer l'attribut 'dateSuppression' dans la table General : " + query2.lastError().text().toStdString());
    }
}

void ManageSQLite::createTableContact() const
{
    QSqlQuery query(
        "CREATE TABLE IF NOT EXISTS Contact ( \
          id                  INTEGER PRIMARY KEY, \
          nom                 TEXT NOT NULL CHECK (nom <> ''), \
          prenom              TEXT NOT NULL CHECK (prenom <> ''), \
          entreprise          TEXT, \
          email               TEXT, \
          tel                 TEXT, \
          photo               TEXT, \
          date_modification   TEXT, \
          date_creation       TEXT NOT NULL DEFAULT (DATE('now')) \
        )"
    );

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de créer la table Contact : " + query.lastError().text().toStdString());
    }
}

void ManageSQLite::createTableInteraction() const
{
    QSqlQuery query(
        "CREATE TABLE IF NOT EXISTS Interaction ( \
          id                  INTEGER PRIMARY KEY, \
          contenu             TEXT NOT NULL CHECK (contenu <> ''), \
          date_creation       TEXT NOT NULL DEFAULT (DATE('now')), \
          id_contact          INTEGER NOT NULL, \
        \
          FOREIGN KEY (id_contact) REFERENCES Contact(id) \
            ON DELETE CASCADE \
        )"
    );

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de créer la table Interaction : " + query.lastError().text().toStdString());
    }
}

void ManageSQLite::createTableTodo() const
{
    QSqlQuery query(
        "CREATE TABLE IF NOT EXISTS Todo ( \
          id                  INTEGER PRIMARY KEY, \
          resume              TEXT NOT NULL CHECK (resume <> ''), \
          date_realisation    TEXT NOT NULL DEFAULT (DATE('now')), \
          id_interaction      INTEGER NOT NULL, \
          \
          FOREIGN KEY (id_interaction) REFERENCES Interaction(id) \
            ON DELETE CASCADE \
        );"
    );

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de créer la table Todo : " + query.lastError().text().toStdString());
    }
}

void ManageSQLite::insertMockData() const
{
    SQLiteDaoContact daoC;
    SQLiteDaoInteraction daoI;
    SQLiteDaoTodo daoT;

    // Contacts.
    {
        Date date; date.setNow();
        ContactModel c(1, date);
        c.setPrenom("Jean");
        c.setNom("Dupont");
        c.setEntreprise("Google");
        c.setTel("0618251474");
        c.setEmail("jean.dupont@gmail.com");
        daoC.create(c);
    }

    {
        Date date(22, 1, 2020);
        ContactModel c(2, date);
        c.setPrenom("Lucas");
        c.setNom("Durand");
        c.setDateModification(date);
        daoC.create(c);
    }

    {
        Date date(10, 12, 2019);
        ContactModel c(3, date);
        c.setPrenom("Fabrice");
        c.setNom("Delarivère");
        c.setEntreprise("Facebook");
        daoC.create(c);
    }

    // Interactions et todos.
    {
        Date date; date.setNow();
        InteractionModel i(1, date, "Descriptif interaction 1\n@todo Faire les courses");
        daoI.create(1, i);
    }

    {
        Date date(23, 1, 2020);
        InteractionModel i(2, date, "Descriptif interaction 2\n@todo Faire les devoirs @date 25/01/2020");
        daoI.create(2, i);
    }

    // Todos.
    {
        Date date; date.setNow();
        TodoModel i(1, date, "Faire les courses");
        daoT.create(1, i);
    }

    {
        Date date(25, 1, 2020);
        TodoModel i(2, date, "Faire les devoirs");
        daoT.create(2, i);
    }
}
