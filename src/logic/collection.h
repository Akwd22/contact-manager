#ifndef COLLECTION_H
#define COLLECTION_H

#include <list>
#include <ostream>

using namespace std;

template<class T>
/**
 * @brief Classe collection pour gérer une liste d'instances d'une classe @p T.
 * @tparam T Classe à lister.
 */
class Collection
{
protected:
    /// Liste des instances.
    mutable list<T> liste;

public:
    /* -------------------------------------------------------------------------- */
    /*                                  Méthodes                                  */
    /* -------------------------------------------------------------------------- */

    /// Ajouter une instance à la liste.
    void add(const T &instance);
    /// Ajouter à la liste le contenu d'une autre liste.
    void add(const Collection<T> &collection);
    /// Remplacer le contenu de la liste par le contenu d'une autre collection.
    void replace(const Collection<T> &collection);
    /// Supprimer une instance de la liste.
    void remove(const T &instance);
    /// Vider la liste.
    void clear();

    /* -------------------------------------------------------------------------- */
    /*                                 Opérateurs                                 */
    /* -------------------------------------------------------------------------- */

    /// Retourne une copie d'une autre collection.
    Collection<T> & operator=(const Collection<T>& collection);
    /// Retourne @a true si les deux collections contiennent des instances égales.
    bool operator==(const Collection<T> &collection) const;
    /// Retourne @a true si les deux collections ne contiennent pas des instances égales.
    bool operator!=(const Collection<T> &collection) const;
    /// Retourne un flux sortant avec toutes les informations de chaque instance de la liste.
    friend ostream &operator<<(ostream &out, const Collection<T> &collection) {
        for (auto & it : collection.getList()) {
            out << it << endl
                << "--------------------------------" << endl;
        }

        return out;
    }

    /* -------------------------------------------------------------------------- */
    /*                                 Propriétés                                 */
    /* -------------------------------------------------------------------------- */

    /**
     * @brief Retourner un élément par son index dans la liste.
     * @param index Index dans la liste.
     * @throw std::out_of_range Index en dehors de la liste.
     */
    T & getIndex(unsigned int index) const;
    /// Retourner le nombre d'instances dans la liste.
    unsigned int count() const;
    /// Retourner la liste.
    list<T> &getList() const;

protected:
    /// Retourner si @p string2 est contenu dans @p string1 sans respecter la casse.
    static bool findStrings(string string1, string string2);
};

#include "collection_impl.h"



#endif // COLLECTION_H
