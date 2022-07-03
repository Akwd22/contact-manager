#ifndef COLLECTION_IMPL_H
#define COLLECTION_IMPL_H

#include <algorithm>

#include "collection.h"

template<class T>
void Collection<T>::add(const T &instance)
{
    this->liste.push_back(instance);
}

template<class T>
void Collection<T>::add(const Collection<T> &collection)
{
    this->liste.insert(this->liste.begin(), collection.getList().begin(), collection.getList().end());
}

template<class T>
void Collection<T>::replace(const Collection<T> &collection)
{
    this->liste = collection.liste;
}

template<class T>
void Collection<T>::remove(const T &instance)
{
    this->liste.remove(instance);
}

template<class T>
void Collection<T>::clear()
{
    this->liste.clear();
}

template<class T>
T & Collection<T>::getIndex(unsigned int index) const
{
    if (index > this->count() - 1) {
        throw out_of_range("Index en dehors de la liste");
    }

    auto it = this->liste.begin();

    for (unsigned int i = 0; i < index; i++) {
        it++;
    }

    return *it;
}

template<class T>
unsigned int Collection<T>::count() const
{
    return this->liste.size();
}

template<class T>
Collection<T> &Collection<T>::operator=(const Collection<T> &collection)
{
    this->liste = collection.liste;
    return *this;
}

template<class T>
bool Collection<T>::operator==(const Collection<T> &collection) const
{
    return this->liste == collection.getList();
}

template<class T>
bool Collection<T>::operator!=(const Collection<T> &collection) const
{
    return !this->operator==(collection);
}

template<class T>
list<T> &Collection<T>::getList() const
{
    return this->liste;
}

template<class T>
bool Collection<T>::findStrings(string string1, string string2)
{
    transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
    transform(string2.begin(), string2.end(), string2.begin(), ::tolower);

    return string1.find(string2) != string::npos;
}

#endif // COLLECTION_IMPL_H
