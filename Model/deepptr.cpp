#include "deepptr.h"

//Costruttore
template<class T>
Deepptr<T>::Deepptr(T* t) : p(t ? new T(*t) : nullptr) {}

//Costruttore di copia
template<class T>
Deepptr<T>::Deepptr(const Deepptr<T>& d) : p(d.p ? d->clone() : nullptr) {}

//Costruttore di spostamento
template<class T>
Deepptr<T>::Deepptr(Deepptr<T>&& d) : p(d.p) {
    d.p = nullptr;
}

//Operatore di assegnazione
template<class T>
Deepptr<T>& Deepptr<T>::operator=(const Deepptr<T>& d) {
    if(this != &d){
        delete p;
        p = d.p ? d->clone() : nullptr;
    }
    return *this;
}

//Distruttore
template<class T>
Deepptr<T>::~Deepptr(){ delete p; }

//Operatori di dereferenziazione
template<class T>
T& Deepptr<T>::operator* () const { return *p; }

template<class T>
T* Deepptr<T>::operator-> () const { return p; }

//Operatori di uguaglianza
template<class T>
bool Deepptr<T>::operator == (const Deepptr& d) const { return p == d.p;}

template<class T>
bool Deepptr<T>::operator != (const Deepptr& d) const { return p != d.p;}

//Operatore di negazione
template<class T>
bool Deepptr<T>::operator!() const { return !p;}
