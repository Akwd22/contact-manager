#include "requetewindow.h"
#include "ui_requetewindow.h"

#include <stdqt.h>

RequeteWindow::RequeteWindow(const ContactCollection & contacts, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RequeteWindow),
    contacts(contacts)
{
    this->setWindowFlags(Qt::Window);
    this->ui->setupUi(this);
    this->initWidgets();

    this->connect(this->ui->buttonRechercher, SIGNAL(clicked()), this, SLOT(rechercher()));
}

RequeteWindow::~RequeteWindow()
{
    delete this->ui;
}



void RequeteWindow::initWidgets()
{
    this->ui->frameFiltresTodo->setVisible(false);
    this->ui->dateEditInteractionMin->setDate(QDate::currentDate());
    this->ui->dateEditInteractionMax->setDate(QDate::currentDate());
    this->ui->dateEditTodoMin->setDate(QDate::currentDate());
    this->ui->dateEditTodoMax->setDate(QDate::currentDate());
    this->refreshComboBox();
}

void RequeteWindow::refreshComboBox()
{
    this->ui->comboBoxContact->clear();

    this->ui->comboBoxContact->addItem("Rechercher dans tous", QVariant(0));

    for (const ContactModel & c : this->contacts.getList())
    {
        QString nom = QString::fromStdString(c.getPrenom() + " " + c.getNom());
        if (!c.getEntreprise().empty()) nom += QString::fromStdString(" - " + c.getEntreprise());

        QVariant contactId(c.getId());

        this->ui->comboBoxContact->addItem(nom, contactId);
    }
}

void RequeteWindow::refreshResults()
{
    std::stringstream ss;

    switch (this->sujet)
    {
        case Sujet::Interactions:   ss << this->filteredInteractions; break;
        case Sujet::Todos:          ss << this->filteredTodos; break;
        case Sujet::DatesTodo:      ss << this->filteredTodos.getDates(); break;
    }

    this->ui->textEditResultats->setText(StdQt::string(ss.str()));
}



void RequeteWindow::queryInteractions()
{
    unsigned int contactId = this->ui->comboBoxContact->currentData().toUInt(); // 0 si recherche dans tous les contacts.
    Date dateMin;
    Date dateMax;

    if (this->ui->checkBoxInteractionDateMin->isChecked()) dateMin = StdQt::date(this->ui->dateEditInteractionMin->date());
    if (this->ui->checkBoxInteractionDateMax->isChecked()) dateMax = StdQt::date(this->ui->dateEditInteractionMax->date());

    this->filteredInteractions = this->filteredContacts.filterId(contactId).getInteractions();
    this->filteredInteractions.filterDateCreation(dateMin, dateMax);
}

void RequeteWindow::queryTodos()
{
    unsigned int contactId = this->ui->comboBoxContact->currentData().toUInt(); // 0 si recherche dans tous les contacts.
    Date dateMin;
    Date dateMax;

    if (this->ui->checkBoxTodoDateMin->isChecked()) dateMin = StdQt::date(this->ui->dateEditTodoMin->date());
    if (this->ui->checkBoxTodoDateMax->isChecked()) dateMax = StdQt::date(this->ui->dateEditTodoMax->date());

    this->filteredTodos = this->filteredContacts.filterId(contactId).getTodos();
    this->filteredTodos.filterDateRealisation(dateMin, dateMax);
}

void RequeteWindow::rechercher()
{
    this->filteredContacts = this->contacts;
    this->filteredInteractions.clear();
    this->filteredTodos.clear();

    switch (this->sujet)
    {
        case Sujet::Interactions:   this->queryInteractions(); break;
        case Sujet::Todos:          this->queryTodos(); break;
        case Sujet::DatesTodo:      this->queryTodos(); break;
    }

    this->refreshResults();
}



void RequeteWindow::on_radioInteractions_toggled(bool checked)
{
    if (checked) this->sujet = Sujet::Interactions;
}

void RequeteWindow::on_radioTodos_toggled(bool checked)
{
    if (checked) this->sujet = Sujet::Todos;
}

void RequeteWindow::on_radioDatesTodo_toggled(bool checked)
{
    if (checked) this->sujet = Sujet::DatesTodo;
}
