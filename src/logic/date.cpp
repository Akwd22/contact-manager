#include "date.h"

Date::Date()
{
    this->setNull();
}

Date::Date(const unsigned int j, const unsigned int m, const unsigned int a)
{
    this->fromDate(j, m, a);
}

Date::Date(const Date &date) : date(date.date), nullDate(date.nullDate)
{
}

double Date::getDiff(const Date &date) const
{
    struct tm d1 = this->date;
    struct tm d2 = date.date;
    return difftime(mktime(&d1), mktime(&d2));
}

void Date::fromDate(const unsigned int j, const unsigned int m, const unsigned int a)
{
    if (j < 1 || j > 31 || m < 1 || m > 12 || a < 1970 || a > 3000)
    {
        throw domain_error("Date hors plage, les intervalles valides sont pour le jour [1, 31], le mois [1, 12], l'année [1970, 3000]");
    }

    time_t mt;
    time(&mt);
    struct tm *md = localtime(&mt);
    md->tm_mday = j;
    md->tm_mon = m - 1;
    md->tm_year = a - 1900;
    md->tm_hour = 12;
    md->tm_min = 0;
    md->tm_sec = 0;
    md->tm_isdst = 0;

    mt = mktime(md);
    this->setDate(*localtime(&mt));
}

void Date::fromString(const string &date)
{
    smatch matches;

    if (!regex_match(date, matches, regex("^(\\d{1,2})[\\/-](\\d{1,2})[\\/-](\\d{4})$")))
    {
        throw invalid_argument("Format de date invalide, le format est JJ/MM/AAAA");
    }

    unsigned int j = stoul(matches[1]);
    unsigned int m = stoul(matches[2]);
    unsigned int a = stoul(matches[3]);

    this->fromDate(j, m, a);
}

void Date::setNow()
{
    time_t n = time(0);
    this->setDate(*localtime(&n));
}

void Date::setNull()
{
    struct tm date;
    date.tm_mday = 0;
    date.tm_mon = 0;
    date.tm_wday = 0;
    date.tm_yday = 0;
    date.tm_year = 0;
    date.tm_hour = 12;
    date.tm_min = 0;
    date.tm_sec = 0;

    this->date = date;
    this->nullDate = true;
}

string Date::toString() const
{
    return this->nullDate ? "" : to_string(this->getJour()) + "/" + to_string(this->getMois()) + "/" + to_string(this->getAnnee());
}

unsigned int Date::getJour() const
{
    return this->nullDate ? 0 : this->date.tm_mday;
}

unsigned int Date::getMois() const
{
    return this->nullDate ? 0 : this->date.tm_mon + 1;
}

unsigned int Date::getAnnee() const
{
    return this->nullDate ? 0 : this->date.tm_year + 1900;
}

Date &Date::operator=(const Date &date)
{
    this->date = date.date;
    this->nullDate = date.nullDate;
    return *this;
}

bool Date::operator==(const Date &date) const
{
    return this->getDiff(date) == 0;
}

bool Date::operator!=(const Date &date) const
{
    return !this->operator==(date);
}

bool Date::operator<(const Date &date) const
{
    return this->getDiff(date) < 0;
}

bool Date::operator<=(const Date &date) const
{
    return this->getDiff(date) <= 0;
}

bool Date::operator>(const Date &date) const
{
    return this->getDiff(date) > 0;
}

bool Date::operator>=(const Date &date) const
{
    return this->getDiff(date) >= 0;
}

ostream &operator<<(ostream &out, const Date &date)
{
    return out << date.toString();
}

bool Date::isNull() const
{
    return this->nullDate;
}

void Date::setDate(const tm &newDate)
{
    this->date = newDate;
    this->date.tm_hour = 12;
    this->date.tm_min = 0;
    this->date.tm_sec = 0;
    this->date.tm_isdst = 0;
    this->nullDate = false;
}
