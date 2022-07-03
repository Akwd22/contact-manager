#include "interactioncollection.h"

InteractionModel &InteractionCollection::getById(unsigned int id) const
{
    for (InteractionModel & i : this->getList())
    {
        if (i.getId() == id) return i;
    }

    throw runtime_error("Interaction n°" + to_string(id) + " n'existe pas dans la collection");
}

InteractionCollection &InteractionCollection::filterId(unsigned int id)
{
    if (!id) return *this;

    this->liste.remove_if([id](InteractionModel & i) {
        return !(i.getId() == id);
    });

    return *this;
}

InteractionCollection &InteractionCollection::filterDateCreation(const Date &date)
{
    this->liste.remove_if([&date](InteractionModel & i) {
        return !(i.getDateInteraction() == date);
    });

    return *this;
}

InteractionCollection &InteractionCollection::filterDateCreation(const Date &dateMin, const Date &dateMax)
{
    this->liste.remove_if([&dateMin, &dateMax](InteractionModel & i) {
        if (dateMax.isNull()) return !(i.getDateInteraction() >= dateMin);
        if (dateMin.isNull()) return !(i.getDateInteraction() <= dateMax);
        return !(i.getDateInteraction() >= dateMin && i.getDateInteraction() <= dateMax);
    });

    return *this;
}

TodoCollection InteractionCollection::getTodos() const
{
    TodoCollection todos;

    for (InteractionModel & interaction : this->liste)
    {
        todos.add(interaction.getTodos());
    }

    return todos;
}
