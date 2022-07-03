#include "daodatabase.h"
#include "stdqt.h"
#include "sqlitedaointeraction.h"

SQLiteDaoInteraction::~SQLiteDaoInteraction()
{

}

unsigned int SQLiteDaoInteraction::readMaxId() const
{
    QSqlQuery query("SELECT MAX(id) FROM Interaction");

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de récupérer l'identifiant maximal des interactions dans la base de données : " + query.lastError().text().toStdString());
    }

    query.next();

    unsigned int maxId = 0;

    if (query.value(0).canConvert<unsigned int>())
    {
        maxId = query.value(0).toUInt();
    }

    return maxId + 1;
}

void SQLiteDaoInteraction::create(unsigned int contactId, const InteractionModel &interaction) const
{
    QSqlQuery query;
    query.prepare("INSERT INTO Interaction VALUES (:id, :contenu, :date_creation, :id_contact)");

    query.bindValue(":id", interaction.getId());
    query.bindValue(":contenu", StdQt::string(interaction.getContenu()));
    query.bindValue(":date_creation", StdQt::date(interaction.getDateInteraction()));
    query.bindValue(":id_contact", contactId);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible d'insérer l'interaction dans la base de données : " + query.lastError().text().toStdString());
    }
}

InteractionCollection SQLiteDaoInteraction::readAll(unsigned int contactId) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Interaction WHERE id_contact = :id_contact");

    query.bindValue(":id_contact", contactId);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de récupérer les interactions du contact n°" + std::to_string(contactId) + " dans la base de données : " + query.lastError().text().toStdString());
    }

    InteractionCollection list;

    while (query.next())
    {
        // Extraction date de création.
        Date dateCreation = StdQt::date(query.value("date_creation"));

        // Instanciation de l'interaction.
        InteractionModel interaction(query.value("id").toUInt(), dateCreation, StdQt::string(query.value("contenu")));

        list.add(interaction);
    }

    return list;
}

void SQLiteDaoInteraction::update(const InteractionModel &interaction) const
{
    QSqlQuery query;
    query.prepare("UPDATE Interaction SET contenu = :contenu WHERE id = :id");

    query.bindValue(":contenu", StdQt::string(interaction.getContenu()));
    query.bindValue(":id", interaction.getId());

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de modifier l'interaction dans la base de données : " + query.lastError().text().toStdString());
    }
}

void SQLiteDaoInteraction::destroy(unsigned int id) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM Interaction WHERE id = :id");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de supprimer l'interaction de la base de données : " + query.lastError().text().toStdString());
    }
}
