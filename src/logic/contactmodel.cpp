#include "contactmodel.h"

unsigned int ContactModel::idCount = 1;

Date ContactModel::dateSuppression;

const Date &ContactModel::getDateSuppression()
{
    return ContactModel::dateSuppression;
}

void ContactModel::setDateSuppression(const Date &newDateSuppression)
{
    if (!newDateSuppression.isNull() && newDateSuppression < ContactModel::dateSuppression)
    {
        throw invalid_argument("La nouvelle date de suppression doit être supérieure ou égale à la date de suppression actuelle");
    }

    ContactModel::dateSuppression = newDateSuppression;
}

ContactModel::ContactModel() : id(idCount++)
{
    this->dateCreation.setNow();
}

ContactModel::ContactModel(unsigned int id, const Date &dateCreation)
    : id(id)
{
    if (dateCreation.isNull()) {
        throw invalid_argument("La date de création ne doit pas être vide");
    }

    this->dateCreation = dateCreation;
}

ContactModel::ContactModel(const ContactModel &contact)
    : id(contact.id)
    , nom(contact.nom)
    , prenom(contact.prenom)
    , entreprise(contact.entreprise)
    , email(contact.email)
    , tel(contact.tel)
    , photo(contact.photo)
    , dateCreation(contact.dateCreation)
    , dateModification(contact.dateModification)
    , interactions(contact.interactions)
{
}

ContactModel &ContactModel::operator=(const ContactModel &contact)
{
    this->id = contact.id;
    this->dateCreation = contact.dateCreation;
    this->nom = contact.nom;
    this->prenom = contact.prenom;
    this->entreprise = contact.entreprise;
    this->email = contact.email;
    this->tel = contact.tel;
    this->photo = contact.photo;
    this->dateModification = contact.dateModification;
    this->interactions = contact.interactions;

    return *this;
}

bool ContactModel::operator==(const ContactModel &contact) const
{
    return this->id == contact.id && this->dateCreation == contact.dateCreation && this->nom == contact.nom && this->prenom == contact.prenom && this->entreprise == contact.entreprise && this->email == contact.email && this->tel == contact.tel && this->photo == contact.photo && this->dateModification == contact.dateModification && this->interactions == contact.interactions;
}

bool ContactModel::operator!=(const ContactModel &contact) const
{
    return !this->operator==(contact);
}

ostream &operator<<(ostream &out, const ContactModel &contact)
{
    return out
           << "(Contact n°" << contact.id << ")"
           << " Prénom/nom : " << contact.prenom << " " << contact.nom << endl
           << "Entreprise : " << contact.entreprise << endl
           << "E-mail : " << contact.email << " Téléphone : " << contact.tel << endl
           << "Photo : " << contact.photo << endl
           << "Création : " << contact.dateCreation << " Modification : " << contact.dateModification;
}

unsigned int ContactModel::getId() const
{
    return id;
}

const string &ContactModel::getNom() const
{
    return nom;
}

void ContactModel::setNom(const string &newNom)
{
    nom = newNom;
}

const string &ContactModel::getPrenom() const
{
    return prenom;
}

void ContactModel::setPrenom(const string &newPrenom)
{
    prenom = newPrenom;
}

const string &ContactModel::getEntreprise() const
{
    return entreprise;
}

void ContactModel::setEntreprise(const string &newEntreprise)
{
    entreprise = newEntreprise;
}

const string &ContactModel::getEmail() const
{
    return email;
}

void ContactModel::setEmail(const string &newEmail)
{
    if (!newEmail.empty() && !regex_search(newEmail, regex("^(?!\\.)(?!.*\\.@)(?!.*?\\.\\.)[\\wÀ-ú-.+/!%]{1,64}@[a-zA-Z0-9À-ú\\-]+(?:\\.[a-zA-Z0-9]+)?$")))
    {
        throw invalid_argument("Format d'adresse e-mail invalide");
    }

    email = newEmail;
}

const string &ContactModel::getTel() const
{
    return tel;
}

void ContactModel::setTel(const string &newTel)
{
    if (!newTel.empty() && !regex_search(newTel, regex("^\\+?\\d+$")))
    {
        throw invalid_argument("Format de numéro de téléphone invalide");
    }

    tel = newTel;
}

const string &ContactModel::getPhoto() const
{
    return photo;
}

void ContactModel::setPhoto(const string &newPhoto)
{
    photo = newPhoto;
}

const Date &ContactModel::getDateCreation() const
{
    return dateCreation;
}

const Date &ContactModel::getDateModification() const
{
    return dateModification;
}

void ContactModel::setDateModification(const Date &newDateModification)
{
    if (newDateModification < this->dateCreation)
    {
        throw invalid_argument("La date de modification doit être supérieure ou égale à la date de création");
    }

    if (newDateModification < this->dateModification)
    {
        throw invalid_argument("La nouvelle date de modification doit être supérieure ou égale à la date de modification actuelle");
    }

    dateModification = newDateModification;
}

InteractionCollection &ContactModel::getInteractions() const
{
    return interactions;
}
