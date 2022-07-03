#include "daodatabase.h"
#include "stdqt.h"
#include "sqlitedaotodo.h"

SQLiteDaoTodo::~SQLiteDaoTodo()
{

}

unsigned int SQLiteDaoTodo::readMaxId() const
{
    QSqlQuery query("SELECT MAX(id) FROM Todo");

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de récupérer l'identifiant maximal des todos dans la base de données : " + query.lastError().text().toStdString());
    }

    query.next();

    unsigned int maxId = 0;

    if (query.value(0).canConvert<unsigned int>())
    {
        maxId = query.value(0).toUInt();
    }

    return maxId + 1;
}

void SQLiteDaoTodo::create(unsigned int interactionId, const TodoModel &todo) const
{
    QSqlQuery query;
    query.prepare("INSERT INTO Todo VALUES (:id, :resume, :date_realisation, :id_interaction)");

    query.bindValue(":id", todo.getId());
    query.bindValue(":resume", StdQt::string(todo.getResume()));
    query.bindValue(":date_realisation", StdQt::date(todo.getDateTodo()));
    query.bindValue(":id_interaction", interactionId);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible d'insérer le todo dans la base de données : " + query.lastError().text().toStdString());
    }
}

TodoCollection SQLiteDaoTodo::readAll(unsigned int interactionId) const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Todo WHERE id_interaction = :id_interaction");

    query.bindValue(":id_interaction", interactionId);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de récupérer les todos de l'interaction n°" + std::to_string(interactionId) + " dans la base de données : " + query.lastError().text().toStdString());
    }

    TodoCollection list;

    while (query.next())
    {
        // Extraction date de réalisation.
        Date dateRealisation = StdQt::date(query.value("date_realisation"));

        // Instanciation du todo.
        TodoModel interaction(query.value("id").toUInt(), dateRealisation, StdQt::string(query.value("resume")));

        list.add(interaction);
    }

    return list;
}

void SQLiteDaoTodo::update(const TodoModel &todo) const
{
    QSqlQuery query;
    query.prepare("UPDATE Todo SET resume = :resume, date_realisation = :date_realisation WHERE id = :id");

    query.bindValue(":resume", StdQt::string(todo.getResume()));
    query.bindValue(":date_realisation", StdQt::date(todo.getDateTodo()));
    query.bindValue(":id", todo.getId());

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de modifier le todo dans la base de données : " + query.lastError().text().toStdString());
    }
}

void SQLiteDaoTodo::destroy(unsigned int id) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM Todo WHERE id = :id");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de supprimer le todo de la base de données : " + query.lastError().text().toStdString());
    }
}

void SQLiteDaoTodo::destroyAll(unsigned int interactionId) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM Todo WHERE id_interaction = :id_interaction");

    query.bindValue(":id_interaction", interactionId);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de supprimer les todos de l'interaction n°" + std::to_string(interactionId) + " de la base de données : " + query.lastError().text().toStdString());
    }
}
