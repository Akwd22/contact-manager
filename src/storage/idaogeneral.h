#ifndef IDAOGENERAL_H
#define IDAOGENERAL_H

#include "storage_global.h"

#include <QVariant>

/**
 * @brief Interface DAO pour les opérations CRUD concernant les attributs globaux de l'application.
 * 
 * Ces attributs qui sont des chaînes de caractères peuvent contenir n'importe quelle valeur.
 * Cela s'apparente à une carte clé-valeur.
 * 
 * @note Par exemple, cela peut servir à sauvegarder la date de la dernière suppression d'un contact, ce dernier étant un attribut global.
 * @throw std::runtime_error Toutes les méthodes en cas d'erreur lors de l'opération.
 */
class STORAGE_EXPORT IDaoGeneral
{
public:
    virtual ~IDaoGeneral() {};

    /**
     * @brief Créer un attribut nommé @p attribut ayant pour valeur @p valeur.
     * @param attribut Nom de l'attribut.
     * @param valeur Valeur de l'attribut.
     */
    virtual void create(const QString & attribut, const QVariant & valeur) const = 0;
    /**
     * @brief Retourner la valeur d'un attribut.
     * @param attribut Nom de l'attribut.
     * @return QVariant Valeur de l'attribut.
     */
    virtual QVariant read(const QString & attribut) const = 0;
    /**
     * @brief Mettre à jour la valeur d'un attribut.
     * @param attribut Nom de l'attribut.
     * @param valeur Nouvelle valeur de l'attribut.
     * @return QVariant Nouvelle valeur de l'attribut.
     */
    virtual void update(const QString & attribut, const QVariant & valeur) const = 0;
    /**
     * @brief Détruire un attribut.
     * @param attribut Nom de l'attribut.
     */
    virtual void destroy(const QString & attribut) const = 0;
};

#endif // IDAOGENERAL_H
