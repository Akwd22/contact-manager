#ifndef IDUMP_H
#define IDUMP_H

#include "storage_global.h"

#include <contactcollection.h>

#include <QString>

/// Interface pour générer des dumps des données de l'application.
class STORAGE_EXPORT IDump
{
protected:
    /// Chemin du fichier d'exportation.
    QString filePath;

public:
    /**
     * @brief Constructeur par défaut.
     * @param filePath Chemin du fichier d'exportation.
     */
    IDump(QString filePath) : filePath(filePath) {};
    virtual ~IDump() {};

    /**
     * @brief Générer un dump profond de l'ensemble des données de l'application.
     * @param contacts Liste des contacts à exporter.
     * @throw std::runtime_error Erreur lors de l'écriture du fichier d'export.
     */
    virtual void dumpAll(const ContactCollection & contacts) const = 0;
};

#endif // IDUMP_H
