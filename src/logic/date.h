#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <regex>
#include <iostream>

using namespace std;

/// Classe utilitaire pour stocker et manipuler une date simplement (ne gère pas le temps).
class Date
{
private:
    /// Structure date C.
    struct tm date;
    /// La date est-telle vide ?
    bool nullDate;

    /// Retourner la différence entre deux dates (en secondes).
    double getDiff(const Date &date) const;

public:
    /* -------------------------------------------------------------------------- */
    /*                                Constructeurs                               */
    /* -------------------------------------------------------------------------- */

    /**
     * @brief Constructeur par défaut.
     * Date initialisée à vide.
     */
    Date();
    /**
     * @brief Constructeur à partir d'un jour, mois et année.
     * @param j Jour.
     * @param m Mois.
     * @param a Année.
     * @throw std::domain_error Voir les exceptions de @link Date::fromDate() @endlink.
     */
    Date(const unsigned int j, const unsigned int m, const unsigned int a);
    /**
     * @brief Constructeur par copie.
     * @param date Date à copier.
     */
    Date(const Date &date);

    /* -------------------------------------------------------------------------- */
    /*                                  Méthodes                                  */
    /* -------------------------------------------------------------------------- */

    /**
     * @brief Définir la date à partir d'un jour, mois et année.
     * @param j Jour.
     * @param m Mois.
     * @param a Année.
     * @throw std::domain_error @p j < 1 || @p j > 31.
     * @throw std::domain_error @p m < 1 || @p m > 12.
     * @throw std::domain_error @p a < 1970 || @p a > 3000.
     */
    void fromDate(const unsigned int j, const unsigned int m, const unsigned int a);
    /**
     * @brief Définir la date à partir d'un string.
     * @param date String contenant la date (format JJ/MM/AAAA, JJ-MM-AAAA).
     * @throw std::invalid_argument Format de date invalide.
     * @throw std::domain_error Voir les exceptions de @link Date::fromDate() @endlink.
     * @note Exemples de format de date valide : "22/07/2000", "22-07-2000", "22/7/2000", "22-7-2000".
     */
    void fromString(const string &date);

    /* -------------------------------------------------------------------------- */
    /*                                 Opérateurs                                 */
    /* -------------------------------------------------------------------------- */

    /// Retourne une date copiée d'une autre date.
    Date &operator=(const Date &date);
    /// Retourne @a true si les deux dates sont égales.
    bool operator==(const Date &date) const;
    /// Retourne @a true si les deux dates ne sont pas égales.
    bool operator!=(const Date &date) const;
    /// Retourne @a true si la date est inférieure à l'autre date.
    bool operator<(const Date &date) const;
    /// Retourne @a true si la date est inférieure ou égale à l'autre date.
    bool operator<=(const Date &date) const;
    /// Retourne @a true si la date est supérieure à l'autre date.
    bool operator>(const Date &date) const;
    /// Retourne @a true si la date est supérieure ou égale à l'autre date.
    bool operator>=(const Date &date) const;
    /// Retourne un flux sortant avec la date au format JJ/MM/AAAA.
    friend ostream &operator<<(ostream &out, const Date &date);

    /* -------------------------------------------------------------------------- */
    /*                                 Propriétés                                 */
    /* -------------------------------------------------------------------------- */

    /// La date est-telle nulle ?
    bool isNull() const;
    /// Définir la date à partir d'une structure date C.
    void setDate(const tm &newDate);
    /// Définir la date sur la date du jour.
    void setNow();
    /// Définir la date sur une date vide.
    void setNull();
    /// Retourner la date en string (format JJ/MM/AAAA), ou string vide si date nulle.
    string toString() const;
    /// Retourner le jour du mois, ou 0 si date nulle.
    unsigned int getJour() const;
    /// Retourner le numéro du mois, ou 0 si date nulle.
    unsigned int getMois() const;
    /// Retourner l'année, ou 0 si date nulle.
    unsigned int getAnnee() const;
};

#endif // DATE_H
