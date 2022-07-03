#ifndef DUMPJSON_H
#define DUMPJSON_H

#include "idump.h"
#include "storage_global.h"

#include <QJsonArray>
#include <QJsonObject>

/// Classe pour générer des dumps des données de l'application au format JSON.
class STORAGE_EXPORT DumpJson : public IDump
{
public:
    /**
     * @brief Constructeur par défaut.
     * @param filePath Chemin où générer le fichier JSON.
     */
    DumpJson(QString filePath);
    ~DumpJson() {};

    void dumpAll(const ContactCollection &contacts) const;

private:
    /**
     * @brief Écrire le fichier JSON.
     * @param bytes Tableau d'octets.
     * @throw std::runtime_error Erreur lors de l'écriture du fichier.
     */
    void writeFile(const QByteArray & bytes) const;

    /// Dump les données des contacts.
    QJsonArray dumpContacts(const ContactCollection & contacts) const;
    /// Dump les données des interactions.
    QJsonArray dumpInteractions(const InteractionCollection & interactions) const;
    /// Dump les données des todos.
    QJsonArray dumpTodos(const TodoCollection & todos) const;

    /// Dump les données d'un contact.
    QJsonObject dumpContact(const ContactModel & contact) const;
    /// Dump les données d'une interaction.
    QJsonObject dumpInteraction(const InteractionModel & interaction) const;
    /// Dump les données d'un todo.
    QJsonObject dumpTodo(const TodoModel &todo) const;
};

#endif // DUMPJSON_H
