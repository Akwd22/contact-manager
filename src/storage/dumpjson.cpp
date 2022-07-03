#include "stdqt.h"
#include "dumpjson.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

DumpJson::DumpJson(QString filePath) : IDump(filePath)
{

}

void DumpJson::dumpAll(const ContactCollection &contacts) const
{
    QJsonDocument doc;
    QJsonObject root;

    // Dump de la date de dernière suppression.
    bool hasDateSuppression = !ContactModel::getDateSuppression().isNull();
    root.insert("dateSuppression", hasDateSuppression ? StdQt::string(ContactModel::getDateSuppression().toString()) : QJsonValue());

    // Dump des contacts, de leurs interactions, et de leurs todos.
    root.insert("contacts", this->dumpContacts(contacts));

    doc.setObject(root);

    this->writeFile(doc.toJson());
}

void DumpJson::writeFile(const QByteArray &bytes) const
{
    QFile file(this->filePath);

    if (!file.open(QIODevice::WriteOnly))
    {
        throw runtime_error("Impossible d'ouvrir le fichier " + this->filePath.toStdString() + " pour exporter en JSON");
    }

    if (!file.write(bytes))
    {
        file.close();
        throw runtime_error("Impossible d'écrire dans le fichier pour exporter en JSON");
    }
}

QJsonArray DumpJson::dumpContacts(const ContactCollection &contacts) const
{
    QJsonArray array;

    for (ContactModel & c : contacts.getList())
    {
        array.append(this->dumpContact(c));
    }

    return array;
}

QJsonArray DumpJson::dumpInteractions(const InteractionCollection &interactions) const
{
    QJsonArray array;

    for (InteractionModel & i : interactions.getList())
    {
        array.append(this->dumpInteraction(i));
    }

    return array;
}

QJsonArray DumpJson::dumpTodos(const TodoCollection &todos) const
{
    QJsonArray array;

    for (TodoModel & t : todos.getList())
    {
        array.append(this->dumpTodo(t));
    }

    return array;
}

QJsonObject DumpJson::dumpContact(const ContactModel &contact) const
{
    QJsonObject obj;

    obj.insert("id", QJsonValue((int) contact.getId()));
    obj.insert("nom", QJsonValue(StdQt::string(contact.getNom())));
    obj.insert("prenom", QJsonValue(StdQt::string(contact.getPrenom())));
    obj.insert("entreprise", QJsonValue(StdQt::string(contact.getEntreprise())));
    obj.insert("email", QJsonValue(StdQt::string(contact.getEmail())));
    obj.insert("tel", QJsonValue(StdQt::string(contact.getTel())));
    obj.insert("photo", QJsonValue(StdQt::string(contact.getPhoto())));
    obj.insert("dateCreation", QJsonValue(StdQt::string(contact.getDateCreation().toString())));

    bool hasDateModification = !contact.getDateModification().isNull();
    obj.insert("dateModification", hasDateModification ? StdQt::string(contact.getDateModification().toString()) : QJsonValue());

    obj.insert("interactions", this->dumpInteractions(contact.getInteractions()));

    return obj;
}

QJsonObject DumpJson::dumpInteraction(const InteractionModel &interaction) const
{
    QJsonObject obj;

    obj.insert("id", QJsonValue((int) interaction.getId()));
    obj.insert("contenu", QJsonValue(StdQt::string(interaction.getContenu())));
    obj.insert("dateInteraction", QJsonValue(StdQt::string(interaction.getDateInteraction().toString())));

    obj.insert("todos", this->dumpTodos(interaction.getTodos()));

    return obj;
}

QJsonObject DumpJson::dumpTodo(const TodoModel &todo) const
{
    QJsonObject obj;

    obj.insert("id", QJsonValue((int) todo.getId()));
    obj.insert("resume", QJsonValue(StdQt::string(todo.getResume())));
    obj.insert("dateRealisation", QJsonValue(StdQt::string(todo.getDateTodo().toString())));

    return obj;
}

