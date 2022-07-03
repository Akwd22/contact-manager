#ifndef SQLITEDAOCONTACT_H
#define SQLITEDAOCONTACT_H

#include "storage_global.h"
#include "idaocontact.h"

#include <QtSql/QtSql>

/// Classe DAO de @link ContactModel @endlink pour une base de données SQLite.
class STORAGE_EXPORT SQLiteDaoContact : public IDaoContact
{
public:
    ~SQLiteDaoContact();

    unsigned int readMaxId() const;

    void create(const ContactModel &contact) const;
    ContactCollection readAll() const;
    void update(const ContactModel &contact) const;
    void destroy(unsigned int id) const;
    void destroyAll() const;
};

#endif // SQLITEDAOCONTACT_H
