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
    bool modificato;
    static void copia(Nodo*, Nodo*&, Nodo*&);
    static void distruggi(Nodo*);
public:
    //Iteratore (non const)
    class iterator{
        friend class Container<T>;
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

    //Funzioni di ritorno degli iteratori (inizio e fine)
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    //Funzione di dimensione
    unsigned int size() const;
    bool empty() const;
    //Funzioni di push
    void push_front(const T& t);
    void push_back(const T& t);
    //Funzioni di pop
    void pop_front();
    void pop_back();
    void erase(int posizione);
    void erase(const iterator& it);
    void clear();
    //Operatore di subscripting
    T& operator[](int pos) const;
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
    return !(*this == i);
}

//Operatori di incremento
template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++(){
    if(nodo) {
        if(nodo->next){
            nodo=nodo->next;
        }else{
            pastTheEnd=true;
        }
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
    return app;
}


/**------ Funzioni della classe Container ------**/

//Funzione di copia
template<typename T>
void Container<T>::copia(Nodo* nodo, Nodo*& first, Nodo*& last) {
    if(!nodo){
        first = last = nullptr;
    }else{
        first = last = new Nodo(nodo->info);
        Nodo* successivo = nodo->next;
        while (successivo){
            last = new Nodo(successivo->info, last);
            last->prev->next = last;
            successivo = successivo->next;
        }
    }
}

//Funzione di distruzione
template <typename T>
void Container<T>::distruggi(Container<T>::Nodo* nodo) {
    if (nodo != nullptr) {
        distruggi(nodo->next);
        delete nodo;
    }
}

//Costruttore
template <class T>
Container<T>::Container() : first(nullptr), last(nullptr), modificato(false){}

//Costruttore di copia
template <class T>
Container<T>::Container(const Container& c) : modificato(c.modificato){
    copia(c.first, first, last);
}

//Costruttore di spostamento
template <class T>
Container<T>::Container(const Container&& c) : first(c.first), last(c.last), modificato(c.modificato){
    first = last = nullptr;
}

//Operatore di assegnazione
template <class T>
Container<T>& Container<T>::operator=(const Container& c){
    if(this != &c){
        distruggi(first);
        copia(c.first,first,last);
        modificato = c.modificato;
    }
    return *this;
}

//Operatori di assegnazione di spostamento
template <class T>
Container<T>& Container<T>::operator=(const Container&& c){
    if(this != &c){
        distruggi(first);
        first = c.first;
        last = c.last;
        modificato = c.modificato;
        c.first = c.last = nullptr;
    }
    return *this;
}

//Distruttore
template <class T>
Container<T>::~Container(){
    distruggi(first);
}

//Funzioni di ritorno degli iteratori (inizio e fine)
template<class T>
typename Container<T>::iterator Container<T>::begin() {
    return iterator(first, !first);
}

template<class T>
typename Container<T>::const_iterator Container<T>::begin() const {
    return const_iterator(first, !first);
}

template<class T>
typename Container<T>::iterator Container<T>::end() {
    return iterator(last, true);
}

template<class T>
typename Container<T>::const_iterator Container<T>::end() const {
    return const_iterator(last, true);
}

//Funzione di dimensione
template<class T>
unsigned int Container<T>::size() const {
    int counter = 0;
    if (!first){
        return 0;
    }else{
        Nodo* app = first;
        while(app->next != nullptr){
            counter++;
            app = app->next;
        }
        return counter;
    }
}

template <typename T>
bool Container<T>::empty() const {
    return size() == 0;
}

//Funzioni di push
template<class T>
void Container<T>::push_front(const T& t) {
    if (first != nullptr) {
        first->prev = new Nodo(t,first);
        first = first->prev_;
    } else {
        first = last = new Nodo(t);
    }
}

template<class T>
void Container<T>::push_back(const T& t) {
    if (last != nullptr) {
        last->next = new Nodo(t,0,last);
        last = last->next;
    } else {
        first = last = new Nodo(t);
    }
}

//Funzioni di pop
template<class T>
void Container<T>::pop_front(){
    if(!this->empty()) {
        if (first == last) {
            delete first;
            first = last = nullptr;
        }else{
            Nodo* app = first;
            first = first->next;
            delete app;
        }
    }
}

template<class T>
void Container<T>::pop_back(){
    if(!this->empty()) {
        if (first == last) {
            delete first;
            first = last = nullptr;
        }else{
            Nodo* app = last->prev;
            delete last;
            last = app;
        }
    }
}

template<class T>
void Container<T>::erase(int posizione) {
    Nodo* app = first;
    if(posizione == 0) this->pop_front();
    else{
        for (int i = 0; i < posizione; ++i) app = app->next;

        if (app->next) app->next->prev = app->prev;
        else last = app->prev;

        if (app->prev) app->prev->next = app->next;
        else first = app->next;

        delete app;
    }
}

template<class T>
void Container<T>::erase(const iterator& it) {
    Nodo* app = it.nodo;
    if (app->next) app->next->prev = app->prev;
    else last = app->prev;

    if (app->prev_) app->prev->next = app->next;
    else first = app->next;

    delete app;
}

template<class T>
void Container<T>::clear() {
    distruggi(first);
}

//Operatore di subscripting
template<class T>
T& Container<T>::operator[](int posizione) const {
    Nodo* app = first;
    for (int i = 0; i < posizione; ++i) app = app->next;
    return app->info;
}

#endif // CONTAINTER_H
