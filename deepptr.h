#ifndef DEEPPTR_H
#define DEEPPTR_H

template<class T>
class Deepptr{
private:
    T* p;
public:
    //Costruttore
    Deepptr(T* t = 0);
    //Costruttori di copia
    Deepptr(const Deepptr<T>& d);
    //Costruttore di spostamento
    Deepptr(Deepptr<T>&& d);
    //Operatore di assegnazione
    Deepptr& operator=(const Deepptr<T>& d);
    //Operatore di assegnazione di spostamento
    Deepptr& operator=(Deepptr<T>&& d);
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

#endif // DEEPPTR_H
