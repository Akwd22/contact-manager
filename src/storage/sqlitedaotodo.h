#ifndef SQLITEDAOTODO_H
#define SQLITEDAOTODO_H

#include "storage_global.h"
#include "idaotodo.h"

#include <QtSql/QtSql>

/// Classe DAO de @link TodoModel @endlink pour une base de données SQLite.
class STORAGE_EXPORT SQLiteDaoTodo : public IDaoTodo
{
public:
    ~SQLiteDaoTodo();

    unsigned int readMaxId() const;

    void create(unsigned int interactionId, const TodoModel &todo) const;
    TodoCollection readAll(unsigned int interactionId) const;
    void update(const TodoModel &todo) const;
    void destroy(unsigned int id) const;
    void destroyAll(unsigned int interactionId) const;
};

#endif // SQLITEDAOTODO_H
