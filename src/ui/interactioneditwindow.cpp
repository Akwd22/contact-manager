#include "interactioneditwindow.h"
#include "ui_interactioneditwindow.h"

#include <interactionmodel.h>
#include <stdqt.h>

#include <QMessageBox>
#include <QDebug>

InteractionEditWindow::InteractionEditWindow(InteractionModel &im, bool isEdit, QWidget *parent) : QDialog(parent),
                                                                                                   ui(new Ui::InteractionEditWindow),
                                                                                                   im(im),
                                                                                                   isEdit(isEdit)
{
    this->setWindowFlags(Qt::Window);
    this->ui->setupUi(this);
    this->initWidgets();

    this->connect(this->ui->buttonEnregistrer, SIGNAL(clicked()), this, SLOT(enregistrer()));
    this->connect(this->ui->buttonAnnuler, SIGNAL(clicked()), this, SLOT(annuler()));
    this->connect(this->ui->buttonSupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
}

InteractionEditWindow::~InteractionEditWindow()
{
    delete this->ui;
}



void InteractionEditWindow::initWidgets()
{
    if (!this->isEdit)
    {
        this->ui->buttonSupprimer->setVisible(false);
    }

    this->ui->textEdit->setText(StdQt::string(isEdit ? im.getContenu() : ""));
    this->ui->labelDateCreation->setText("Date de création : " + StdQt::string(im.getDateInteraction().toString()));
}



void InteractionEditWindow::enregistrer()
{
    try
    {
        im.setContenu(StdQt::string(this->ui->textEdit->toPlainText()));
        im.parseTodos();
        this->done(1);
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this, "Avertissement", e.what());
    }
}

void InteractionEditWindow::annuler()
{
    this->done(0);
}

void InteractionEditWindow::supprimer()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, "Question", "Voulez-vous vraiment supprimer cette interaction ?");

    if (QMessageBox::Yes == button)
    {
        this->done(2);
    }
}
