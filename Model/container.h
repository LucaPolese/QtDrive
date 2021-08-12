#ifndef CONTAINTER_H
#define CONTAINTER_H

template <class T>
class Container{
private:
    class Nodo {
    public:
        T info;
        Nodo *next, *prev;
        //Costruttore a 0,1,2,3 parametri
        Nodo(const T& i = T(), Nodo* n = nullptr, Nodo*p = nullptr);
    };
    Nodo *first, *last;
    static Nodo* copia(Nodo* n, Nodo*f, Nodo*& l);

public:
    //Iteratore (non const)
    class iterator{
        friend class Container;
    private:
        Nodo* nodo;
        bool pastTheEnd;
        iterator(Nodo* n, bool hasPastTheEnd = false);
    public:
        //Costruttore
        iterator();
        //Costruttore di copia
        iterator(const iterator& i);
        //Operatori di dereferenziazione
        T& operator*() const;
        T* operator->() const;
        //Operatori di equivalenza
        bool operator==(const iterator& i) const;
        bool operator!=(const iterator& i) const;
        //Operatori di incremento
        iterator& operator++();
        iterator operator++(int);
        //Operatori di decremento
        iterator& operator--();
        iterator operator--(int);
    };

    //Iteratore const
    class const_iterator{
        friend class Container<T>;
    private:
        Nodo* nodo;
        bool pastTheEnd;
        const_iterator(Nodo* n, bool hasPastTheEnd = false);
    public:
        //Costruttore
        const_iterator();
        //Costruttore di copia
        const_iterator(const const_iterator& i);
        //Operatori di dereferenziazione
        const T& operator*() const;
        const T* operator->() const;
        //Operatori di equivalenza
        bool operator==(const const_iterator& i) const;
        bool operator!=(const const_iterator& i) const;
        //Operatori di somma e sottrazione
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
    };

    //Costruttore
    Container();
    //Costruttore di copia
    Container(const Container& c);
    //Costruttore di spostamento
    Container(const Container&& c);
    //Operatore di assegnazione
    Container& operator=(const Container& c);
    //Operatori di assegnazione di spostamento
    Container& operator=(const Container&& c);
    //Distruttore
    ~Container();

    //Funzioni di dimensione
    unsigned int size() const;
    //Funzioni di push
    void push_front(const T& t);
    void push_back(const T& t);
    //Funzioni di pop
    void pop_front();
    void pop_back();
    void erase(int pos);
    void erase(const iterator& it);
    void clear();
    //Funzioni di ridimensionamento
    void resize(unsigned int contatore);
    void resize(unsigned int contatore, T valore = T());
    //Operatore di subscripting
    T& operator[](int pos) const;
    //Funzioni di ritorno degli iteratori (inizio e fine)
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};

/**------ Funzioni della classe Nodo ------**/

//Costruttore a 0,1,2,3 parametri di Nodo
template <class T>
Container<T>::Nodo::Nodo(const T& i, Nodo* n, Nodo*p) : info(i), next(n), prev(p){}

/**------ Funzioni della classe iterator ------**/

//Costruttore di iteratore a 1/2 parametri
template <class T>
Container<T>::iterator::iterator(Nodo* n, bool hasPastTheEnd) : nodo(n), pastTheEnd(hasPastTheEnd) {}

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
Container<T>::const_iterator::const_iterator(Nodo* n, bool hasPastTheEnd) : nodo(n), pastTheEnd(hasPastTheEnd) {}

//Costruttore di iteratore a 0 parametri
template <class T>
Container<T>::const_iterator::const_iterator() : nodo(nullptr), pastTheEnd(false) {}

//Costruttore di copia
template <class T>
Container<T>::const_iterator::const_iterator(const const_iterator& i) : nodo(i.nodo), pastTheEnd(i.pastTheEnd) {}

//Operatori di dereferenziazione
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

//Operatori di incremento
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

//Operatori di decremento
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
typename Container<T>::Nodo* Container<T>::copia(Nodo* nodo, Nodo* last, Nodo*& prev){
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



#endif // CONTAINTER_H
