#include "todomodel.h"

unsigned int TodoModel::idCount = 1;

TodoModel::TodoModel(const string &resume) : id(idCount++)
{
    this->dateTodo.setNow();
    this->setResume(resume);
}

TodoModel::TodoModel(unsigned int id, const Date &dateTodo, const string &resume)
    : id(id)
{
    this->setDateTodo(dateTodo);
    this->setResume(resume);
}

TodoModel::TodoModel(const TodoModel &todo)
    : id(todo.id), dateTodo(todo.dateTodo), resume(todo.resume)
{
}

TodoModel &TodoModel::operator=(const TodoModel &todo)
{
    this->id = todo.id;
    this->dateTodo = todo.dateTodo;
    this->resume = todo.resume;
    return *this;
}

bool TodoModel::operator==(const TodoModel &todo) const
{
    if (this->resume == todo.getResume() && this->dateTodo == todo.getDateTodo() && this->id == todo.getId())
        return true;

    return false;
}

bool TodoModel::operator!=(const TodoModel &todo) const
{
    return !this->operator==(todo);
}

ostream &operator<<(ostream &out, const TodoModel &todo)
{
    return out << "(Todo n°" << todo.id << ")"
               << " Date de réalisation : " << todo.dateTodo << " - Résumé : " << todo.resume;
}

unsigned int TodoModel::getId() const
{
    return this->id;
}

const Date &TodoModel::getDateTodo() const
{
    return this->dateTodo;
}

void TodoModel::setDateTodo(const Date &newDateTodo)
{
    if (newDateTodo.isNull()) {
        throw invalid_argument("La date de réalisation du todo ne doit pas être vide");
    }

    this->dateTodo = newDateTodo;
}

const string &TodoModel::getResume() const
{
    return this->resume;
}

void TodoModel::setResume(const string &newResume)
{
    if (newResume.empty())
    {
        throw invalid_argument("Le résumé du todo ne doit pas être vide");
    }

    this->resume = newResume;
}
