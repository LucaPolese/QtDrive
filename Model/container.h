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
    Nodo* first, last;
    static Nodo* copia(Nodo* n, Nodo*f, Nodo*& l);

public:
    //Iteratore (non const)
    class iterator{
    private:
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
    //Operatore di
    T& operator[](int idx) const;
    //Funzioni di ritorno degli iteratori (inizio e fine)
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};

#endif // CONTAINTER_H
