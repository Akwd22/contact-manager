#ifndef STDQT_H
#define STDQT_H

#include "storage_global.h"

#include <date.h>

#include <QDate>
#include <QVariant>

/// Classe statique utilitaire pour convertir un type C++ standard en un type Qt et inversement.
class STORAGE_EXPORT StdQt
{
public:
    virtual ~StdQt() = 0;

    /// Convertir un string standard en un string Qt.
    static QString string(const std::string & stdString);
    /// Convertir un string Qt en un string standard.
    static std::string string(const QString & qString);
    /**
     * @brief Convertir un QVariant contenant un string en un string standard.
     * @throw runtime_error QVariant ne peut pas être converti en date.
     */
    static std::string string(const QVariant & qVariant);

    /// Convertir une date standard en une date Qt.
    static QDate date(const Date & stdDate);
    /// Convertir une date Qt en une date standard.
    static Date date(const QDate & qDate);
    /**
     * @brief Convertir un QVariant contenant une date en une date standard.
     * @throw runtime_error QVariant ne peut pas être converti en date.
     */
    static Date date(const QVariant & qVariant);
};

#endif // STDQT_H
