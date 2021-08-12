#include "container.h"
/**------ Funzioni della classe Nodo ------**/

//Costruttore a 0,1,2,3 parametri di Nodo
template <class T>
Container<T>::Nodo::Nodo(const T& i, Nodo* n, Nodo*p) : info(i), next(n), prev(p){}

/**------ Funzioni della classe iterator ------**/

//Costruttore di iteratore a 1/2 parametri
template <class T>
Container<T>::iterator::iterator(Container<T>::Nodo* n, bool hasPastTheEnd) : nodo(n), pastTheEnd(hasPastTheEnd) {}

//Costruttore di iteratore a 0 parametri
template <class T>
Container<T>::iterator::iterator() : nodo(nullptr), pastTheEnd(false) {}

//Costruttore di copia
template <class T>
Container<T>::iterator::iterator(const iterator& i) : nodo(i.nodo), pastTheEnd(i.pastTheEnd) {}

//Operatori di redeferenziazione
template <class T>
T& Container<T>::iterator::operator*() const{
    return nodo->info;
}

template <class T>
T* Container<T>::iterator::operator->() const{
    return &(nodo->info);
}

//Operatori di equivalenza
template <class T>
bool Container<T>::iterator::operator==(const iterator& i) const{
    return nodo == i.nodo && pastTheEnd == i.pastTheEnd;
}

template <class T>
bool Container<T>::iterator::operator!=(const iterator& i) const{
    return !(this == i);
}

//Operatori di Incremento
template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator++(){
    if(nodo) {
        nodo->next ? nodo=nodo->next : pastTheEnd=true;
    }
    return *this;
}

template <class T>
typename Container<T>::iterator Container<T>::iterator::operator++(int){
    Container<T>::iterator app (*this);
    if(nodo) {
        nodo->next ? nodo=nodo->next : pastTheEnd=true;
    }
    return app;
}

//Operatori di Decremento
template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator--(){
    if(nodo) {
        nodo->prev ? nodo=nodo->prev: pastTheEnd=false;
    }
    return *this;
}

template <class T>
typename Container<T>::iterator Container<T>::iterator::operator--(int){
    Container<T>::iterator app (*this);
    if(nodo) {
        nodo->prev ? nodo=nodo->prev: pastTheEnd=false;
    }
    return *this;
}


/**------ Funzioni della classe const_iterator ------**/

//Costruttore di iteratore a 1/2 parametri
template <class T>
Container<T>::const_iterator::const_iterator(Container<T>::Nodo* n, bool hasPastTheEnd) : nodo(n), pastTheEnd(hasPastTheEnd) {}

//Costruttore di iteratore a 0 parametri
template <class T>
Container<T>::const_iterator::const_iterator() : nodo(nullptr), pastTheEnd(false) {}

//Costruttore di copia
template <class T>
Container<T>::const_iterator::const_iterator(const const_iterator& i) : nodo(i.nodo), pastTheEnd(i.pastTheEnd) {}

//Operatori di redeferenziazione
template <class T>
const T& Container<T>::const_iterator::operator*() const{
    return nodo->info;
}

template <class T>
const T* Container<T>::const_iterator::operator->() const{
    return &(nodo->info);
}

//Operatori di equivalenza
template <class T>
bool Container<T>::const_iterator::operator==(const const_iterator& i) const{
    return nodo == i.nodo && pastTheEnd == i.pastTheEnd;
}

template <class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& i) const{
    return !(this == i);
}

//Operatori di Incremento
template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++(){
    if(nodo) {
        nodo->next ? nodo=nodo->next : pastTheEnd=true;
    }
    return *this;
}

template <class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int){
    Container<T>::const_iterator app (*this);
    if(nodo) {
        nodo->next ? nodo=nodo->next : pastTheEnd=true;
    }
    return app;
}

//Operatori di Decremento
template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--(){
    if(nodo) {
        nodo->prev ? nodo=nodo->prev: pastTheEnd=false;
    }
    return *this;
}

template <class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int){
    Container<T>::const_iterator app (*this);
    if(nodo) {
        nodo->prev ? nodo=nodo->prev: pastTheEnd=false;
    }
    return *this;
}


/**------ Funzioni della classe Container ------**/

//Funzione di copia
template <class T>
typename Container<T>::Nodo* Container<T>::copia(Container<T>::Nodo* nodo, Container<T>::Nodo* last, Container<T>::Nodo*& prev){
    /*//Se non ho un nodo oppure sono arrivato in fondo alla lista,
    //non devo creare altri nodi
    if(!nodo) {
        last = prev;
        return nullptr;
    }else{
        Container<T>::Nodo* app;
        app = new Container<T>::Nodo();
        return copia(nodo->next,app,nodo->info);
    }*/
}

//Costruttore
template <class T>
Container<T>::Container() : first(nullptr), last(nullptr){}

/*//Costruttore di copia
template <class T>
Container<T>::Container(const Container& c) : first(copia(c.first)), last(copia(c.last)) {}

Container(const Container&& c);

const_iterator begin() const {
    return first;
}

const_iterator end() const {
    if(!last) return nullptr;
    return const_iterator(last+1,true);
}*/


