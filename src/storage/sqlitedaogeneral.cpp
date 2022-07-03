#include "daodatabase.h"
#include "sqlitedaogeneral.h"

SQLiteDaoGeneral::~SQLiteDaoGeneral()
{

}

void SQLiteDaoGeneral::create(const QString &attribut, const QVariant &valeur) const
{
    QSqlQuery query;
    query.prepare("INSERT INTO General VALUES (:attribut, :valeur)");

    query.bindValue(":attribut", attribut);
    query.bindValue(":valeur", valeur);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de créer un attribut dans la base de données : " + query.lastError().text().toStdString());
    }
}

QVariant SQLiteDaoGeneral::read(const QString &attribut) const
{
    QSqlQuery query;
    query.prepare("SELECT valeur FROM General WHERE attribut = :attribut");

    query.bindValue(":attribut", attribut);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de récupérer un attribut dans la base de données : " + query.lastError().text().toStdString());
    }

    if (!query.next())
    {
        throw std::runtime_error("Attribut " + attribut.toStdString() + " n'existe pas dans la base de données");
    }

    return query.value(0);
}

void SQLiteDaoGeneral::update(const QString &attribut, const QVariant &valeur) const
{
    QSqlQuery query;
    query.prepare("UPDATE General SET valeur = :valeur WHERE attribut = :attribut");

    query.bindValue(":valeur", valeur);
    query.bindValue(":attribut", attribut);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de modifier un attribut dans la base de données : " + query.lastError().text().toStdString());
    }
}

void SQLiteDaoGeneral::destroy(const QString &attribut) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM General WHERE attribut = :attribut");

    query.bindValue(":attribut", attribut);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de supprimer un attribut dans la base de données : " + query.lastError().text().toStdString());
    }
}
