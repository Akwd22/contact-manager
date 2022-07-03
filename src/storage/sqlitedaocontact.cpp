#include "daodatabase.h"
#include "stdqt.h"
#include "sqlitedaocontact.h"

#include <QDebug>

SQLiteDaoContact::~SQLiteDaoContact()
{

}

unsigned int SQLiteDaoContact::readMaxId() const
{
    QSqlQuery query("SELECT MAX(id) FROM Contact");

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de récupérer l'identifiant maximal des contacts dans la base de données : " + query.lastError().text().toStdString());
    }

    query.next();

    unsigned int maxId = 0;

    if (query.value(0).canConvert<unsigned int>())
    {
        maxId = query.value(0).toUInt();
    }

    return maxId + 1;
}

void SQLiteDaoContact::create(const ContactModel &contact) const
{
    QSqlQuery query;
    query.prepare("INSERT INTO Contact VALUES (:id, :nom, :prenom, :entreprise, :email, :tel, :photo, :date_modification, :date_creation)");

    query.bindValue(":id", contact.getId());
    query.bindValue(":nom", StdQt::string(contact.getNom()));
    query.bindValue(":prenom", StdQt::string(contact.getPrenom()));
    query.bindValue(":entreprise", StdQt::string(contact.getEntreprise()));
    query.bindValue(":email", StdQt::string(contact.getEmail()));
    query.bindValue(":tel", StdQt::string(contact.getTel()));
    query.bindValue(":photo", StdQt::string(contact.getPhoto()));
    query.bindValue(":date_modification", StdQt::date(contact.getDateModification()));
    query.bindValue(":date_creation", StdQt::date(contact.getDateCreation()));

    if (!query.exec())
    {
        throw std::runtime_error("Impossible d'insérer le contact dans la base de données : " + query.lastError().text().toStdString());
    }
}

ContactCollection SQLiteDaoContact::readAll() const
{
    QSqlQuery query("SELECT * FROM Contact");

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de récupérer les contacts dans la base de données : " + query.lastError().text().toStdString());
    }

    ContactCollection list;

    while (query.next())
    {
        // Extraction date de création.
        Date dateCreation = StdQt::date(query.value("date_creation"));

        // Extraction date de dernière modification.
        Date dateModification = StdQt::date(query.value("date_modification"));

        // Instanciation du contact.
        ContactModel contact(query.value("id").toUInt(), dateCreation);
        contact.setNom(StdQt::string(query.value("nom")));
        contact.setPrenom(StdQt::string(query.value("prenom")));
        contact.setEntreprise(StdQt::string(query.value("entreprise")));
        contact.setEmail(StdQt::string(query.value("email")));
        contact.setTel(StdQt::string(query.value("tel")));
        contact.setPhoto(StdQt::string(query.value("photo")));
        if (!dateModification.isNull()) contact.setDateModification(dateModification);

        list.add(contact);
    }

    return list;
}

void SQLiteDaoContact::update(const ContactModel &contact) const
{
    QSqlQuery query;
    query.prepare("UPDATE Contact SET "
        "nom                = :nom,"
        "prenom             = :prenom,"
        "entreprise         = :entreprise,"
        "email              = :email,"
        "tel                = :tel,"
        "photo              = :photo,"
        "date_modification  = :date_modification"
        " WHERE id = :id"
    );

    query.bindValue(":nom", StdQt::string(contact.getNom()));
    query.bindValue(":prenom", StdQt::string(contact.getPrenom()));
    query.bindValue(":entreprise", StdQt::string(contact.getEntreprise()));
    query.bindValue(":email", StdQt::string(contact.getEmail()));
    query.bindValue(":tel", StdQt::string(contact.getTel()));
    query.bindValue(":photo", StdQt::string(contact.getPhoto()));
    query.bindValue(":date_modification", StdQt::date(contact.getDateModification()));
    query.bindValue(":id", contact.getId());

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de modifier le contact dans la base de données : " + query.lastError().text().toStdString());
    }
}

void SQLiteDaoContact::destroy(unsigned int id) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM Contact WHERE id = :id");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de supprimer le contact de la base de données : " + query.lastError().text().toStdString());
    }
}

void SQLiteDaoContact::destroyAll() const
{
    QSqlQuery query("DELETE FROM Contact");

    if (!query.exec())
    {
        throw std::runtime_error("Impossible de supprimer les contacts de la base de données : " + query.lastError().text().toStdString());
    }
}
