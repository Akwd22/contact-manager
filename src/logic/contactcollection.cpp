#include "contactcollection.h"

ContactModel &ContactCollection::getById(unsigned int id) const
{
    for (ContactModel & c : this->getList())
    {
        if (c.getId() == id) return c;
    }

    throw runtime_error("Contact n°" + to_string(id) + " n'existe pas dans la collection");
}

ContactCollection &ContactCollection::filterId(unsigned int id)
{
    if (!id) return *this;

    this->liste.remove_if([id](ContactModel & c) {
        return !(c.getId() == id);
    });

    return *this;
}

ContactCollection &ContactCollection::filterPrenom(const string &prenom)
{
    this->liste.remove_if([prenom](ContactModel & c) {
        return !ContactCollection::findStrings(c.getPrenom(), prenom);
    });

    return *this;
}

ContactCollection &ContactCollection::filterNom(const string &nom)
{
    this->liste.remove_if([&nom](ContactModel & c) {
        return !ContactCollection::findStrings(c.getNom(), nom);
    });

    return *this;
}

ContactCollection &ContactCollection::filterEntreprise(const string &entreprise)
{
    this->liste.remove_if([&entreprise](ContactModel & c) {
        return !ContactCollection::findStrings(c.getEntreprise(), entreprise);
    });

    return *this;
}

ContactCollection &ContactCollection::filterDateCreation(const Date &date)
{
    this->liste.remove_if([&date](ContactModel & c) {
        return !(c.getDateCreation() == date);
    });

    return *this;
}

ContactCollection &ContactCollection::filterDateCreation(const Date &dateMin, const Date &dateMax)
{
    this->liste.remove_if([&dateMin, &dateMax](ContactModel & c) {
        if (dateMax.isNull()) return !(c.getDateCreation() >= dateMin);
        if (dateMin.isNull()) return !(c.getDateCreation() <= dateMax);
        return !(c.getDateCreation() >= dateMin && c.getDateCreation() <= dateMax);
    });

    return *this;
}

InteractionCollection ContactCollection::getInteractions() const
{
    InteractionCollection interactions;

    for (ContactModel & contact : this->liste)
    {
        interactions.add(contact.getInteractions());
    }

    return interactions;
}

TodoCollection ContactCollection::getTodos() const
{
    TodoCollection todos;

    for (ContactModel & contact : this->liste)
    {
        for (InteractionModel & interaction : contact.getInteractions().getList())
        {
            todos.add(interaction.getTodos());
        }
    }

    return todos;
}

