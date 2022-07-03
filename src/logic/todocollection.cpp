#include "todocollection.h"

TodoModel &TodoCollection::getById(unsigned int id) const
{
    for (TodoModel & t : this->getList())
    {
        if (t.getId() == id) return t;
    }

    throw runtime_error("Todo n°" + to_string(id) + " n'existe pas dans la collection");
}

TodoCollection &TodoCollection::filterId(unsigned int id)
{
    if (!id) return *this;

    this->liste.remove_if([id](TodoModel & t) {
        return !(t.getId() == id);
    });

    return *this;
}

TodoCollection &TodoCollection::filterDateRealisation(const Date &date)
{
    this->liste.remove_if([&date](TodoModel & t) {
        return !(t.getDateTodo() == date);
    });

    return *this;
}

TodoCollection &TodoCollection::filterDateRealisation(const Date &dateMin, const Date &dateMax)
{
    this->liste.remove_if([&dateMin, &dateMax](TodoModel & t) {
        if (dateMax.isNull()) return !(t.getDateTodo() >= dateMin);
        if (dateMin.isNull()) return !(t.getDateTodo() <= dateMax);
        return !(t.getDateTodo() >= dateMin && t.getDateTodo() <= dateMax);
    });

    return *this;
}

Collection<Date> TodoCollection::getDates() const
{
    Collection<Date> dates;

    for (TodoModel & todo : this->liste)
    {
        dates.add(todo.getDateTodo());
    }

    return dates;
}
