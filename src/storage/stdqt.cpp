#include "stdqt.h"


QString StdQt::string(const std::string &stdString)
{
    return QString::fromStdString(stdString);
}

std::string StdQt::string(const QVariant &qVariant)
{
    if (!qVariant.canConvert<QString>())
    {
        throw std::runtime_error("Impossible de convertir le QVariant en QString");
    }

    return StdQt::string(qVariant.toString());
}

std::string StdQt::string(const QString &qString)
{
    return qString.toStdString();
}

QDate StdQt::date(const Date &stdDate)
{
    return QDate::fromString(QString::fromStdString(stdDate.toString()), "d/M/yyyy");
}

Date StdQt::date(const QVariant &qVariant)
{
    if (!qVariant.canConvert<QDate>())
    {
        throw std::runtime_error("Impossible de convertir le QVariant en QDate");
    }

    return StdQt::date(qVariant.toDate());
}

Date StdQt::date(const QDate &qDate)
{
    Date stdDate;

    if (!qDate.isNull() && qDate.isValid())
    {
        stdDate.fromString(qDate.toString("dd/M/yyyy").toStdString());
    }

    return stdDate;
}

