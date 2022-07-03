#ifndef SQLITEDAOINTERACTION_H
#define SQLITEDAOINTERACTION_H

#include "storage_global.h"
#include "idaointeraction.h"

#include <QtSql/QtSql>

/// Classe DAO de @link InteractionModel @endlink globaux pour une base de données SQLite.
class STORAGE_EXPORT SQLiteDaoInteraction : public IDaoInteraction
{
public:
    ~SQLiteDaoInteraction();

    unsigned int readMaxId() const;

    void create(unsigned int contactId, const InteractionModel &interaction) const;
    InteractionCollection readAll(unsigned int contactId) const;
    void update(const InteractionModel &interaction) const;
    void destroy(unsigned int id) const;
};

#endif // SQLITEDAOINTERACTION_H
