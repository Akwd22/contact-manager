#include "interactionmodel.h"

unsigned int InteractionModel::idCount = 1;

InteractionModel::InteractionModel(const string &contenu) : id(idCount++)
{
    this->dateInteraction.setNow();
    this->setContenu(contenu);
}

InteractionModel::InteractionModel(unsigned int id, const Date &dateInteraction, const string &contenu)
    : id(id)
{
    if (dateInteraction.isNull()) {
        throw invalid_argument("La date de l'interaction ne doit pas être vide");
    }

    this->dateInteraction = dateInteraction;
    this->setContenu(contenu);
}

InteractionModel::InteractionModel(const InteractionModel &interaction)
    : id(interaction.id)
    , dateInteraction(interaction.dateInteraction)
    , contenu(interaction.contenu)
    , todos(interaction.todos)
{
}

void InteractionModel::parseTodos()
{
    this->todos.clear();

    istringstream iss(this->contenu);

    string line;
    while (getline(iss, line))
    {
        smatch matches;

        if (regex_match(line, matches, regex("^.*@todo (.+?)(?:$| ?@date (\\d{1,2}[\\/-]\\d{1,2}[\\/-]\\d{4})).*$")))
        {
            string resume = matches[1];
            string dateStr = matches[2];

            Date now; now.setNow();
            Date date; dateStr.empty() ? date.setNow() : date.fromString(dateStr);

            if (date < now)
            {
                throw runtime_error("La date de réalisation doit être supérieure à celle d'aujourd'hui.");
            }

            TodoModel todo(resume);
            todo.setDateTodo(date);

            this->todos.add(todo);
        }
    }
}

InteractionModel &InteractionModel::operator=(const InteractionModel &interaction)
{
    this->id = interaction.id;
    this->dateInteraction = interaction.dateInteraction;
    this->contenu = interaction.contenu;
    this->todos = interaction.todos;
    return *this;
}

bool InteractionModel::operator==(const InteractionModel &interaction) const
{
    return this->id == interaction.id && this->dateInteraction == interaction.dateInteraction && this->contenu == interaction.contenu && this->todos == interaction.todos;
}

ostream &operator<<(ostream &out, const InteractionModel &interaction)
{
    return out << "(Interaction n°" << interaction.id << ")" << " Date : " << interaction.dateInteraction << " - Nombre de todos : " << interaction.todos.count() << endl
               << "Contenu :" << endl
               << "'" << interaction.contenu << "'";
}

bool InteractionModel::operator!=(const InteractionModel &interaction) const
{
    return !this->operator==(interaction);
}

unsigned int InteractionModel::getId() const
{
    return this->id;
}

const Date &InteractionModel::getDateInteraction() const
{
    return this->dateInteraction;
}

const string &InteractionModel::getContenu() const
{
    return this->contenu;
}

void InteractionModel::setContenu(const string &newContenu)
{
    if (newContenu.empty())
    {
        throw invalid_argument("Le contenu de l'interaction ne doit pas être vide");
    }

    this->contenu = newContenu;
}

TodoCollection &InteractionModel::getTodos() const
{
    return this->todos;
}
