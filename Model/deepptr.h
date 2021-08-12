#ifndef DEEPPTR_H
#define DEEPPTR_H

template<class T>
class Deepptr{
private:
    T* p;
public:
    //Costruttore
    Deepptr(T* t);
    //Costruttori di copia
    Deepptr(const Deepptr<T>& d);
    //Costruttore di spostamento
    Deepptr(Deepptr<T>&& d);
    //Operatore di assegnazione
    Deepptr<T>& operator=(const Deepptr<T>& d);
    //Operatore di assegnazione di spostamento
    Deepptr<T>& operator=(Deepptr<T>&& d);
    //Distruttore
    ~Deepptr();
    //Operatori di dereferenziazione
    T& operator* () const;
    T* operator->() const;
    //Operatori di uguaglianza
    bool operator== (const Deepptr<T>& d) const;
    bool operator!= (const Deepptr<T>& d) const;
    //Operatore di negazione
    bool operator!() const;
};

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

//Operatore di assegnazione di spostamento
template <class T>
Deepptr<T>& Deepptr<T>::operator=(Deepptr<T>&& d) {
    if (this != &d) {
        delete p;
        p = d.p;
        d.p = nullptr;
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

#endif // DEEPPTR_H
