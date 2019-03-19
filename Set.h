#ifndef SET_H
#define SET_H
#include <iostream>
#include <cstdlib>

using namespace std;

template <class T> class Set
{
    public:
        Set();
        Set(T *set_array, int n); //constructor cu parametrii
        Set(const Set& first_set); //constructor de copiere
        virtual ~Set();

        void inserare(T x);
        void deletee(T x);
        int searchh(T x);

        T& operator [](int i);
        Set operator +(const Set& x);
        bool operator >(Set const &x);
        bool operator <(Set const &x);
        Set operator *(T const &x);
        void operator =(const Set &x);

        T suma();
        Set elem_par();
        Set elem_impar();

        template <class T1> friend istream &operator>>(istream &in, Set<T1> &first_set);

        friend ostream &operator<<(ostream &out, const Set<T> &first_set)
        {
            if(first_set.sizee == 0)
                out << "Setul nu contine elemente";
            else
            {
                out << '{';

                for(int i = 0; i < first_set.nr_elem() - 1; i++)
                    out << first_set.getset_array()[i] << ", ";
                out << first_set.getset_array()[first_set.nr_elem()-1]; //afisez separat pt a nu avea virgula si dupa ultimul element
                out << '}';
            }

            return out;
        }

        const int nr_elem() const;
        const T* getset_array() const;

    protected:

    private:
        int search_poz(T x);
        T *set_array;
        int sizee, max_size;
};

template <class T> istream &operator>>(istream &in, Set<T> &first_set)
    {
            int x;
            in >> first_set.sizee;
            for(int i = 0; i < first_set.sizee; i++)
            {
                in >> x;
                first_set.inserare(x);
            }
            return in;
        }

template <class T>
Set<T>::Set()
{
    //ctor
    sizee = 0;
    set_array = NULL;
    max_size = 0;
}

template <class T>
Set<T>::Set(T* set_array, int n) //constructor parametrizat
{
    max_size = n;
    sizee = 0;
    this -> set_array = new T[max_size];

    for(int i = 0; i < n; i++)
        this->inserare(set_array[i]);
}

template <class T>
Set<T>::Set(const Set& first_set) //constructor de copiere
{
    sizee = first_set.sizee;
    max_size = first_set.max_size;
    set_array = new T[max_size];
    for(int i = 0; i < sizee; i++)
        set_array[i]=first_set.set_array[i];
}

template <class T>
int Set<T>::searchh(T x) //caut binar elementul x in multimea ordonata crescator
{
    int st = 0, dr = sizee;
    int mij;
    while(st <= dr)
    {
        mij = (st+dr)/2;
        if(set_array[mij] == x)
            return mij;

        if(set_array[mij] < x)
            st = mij + 1;
        else if(set_array[mij] > x)
            dr = mij - 1;
    }

    return -1;
}

template <class T>
int Set<T>::search_poz(T x) //caut binar pozitia la care ar trebui sa inserez elementul x
{
    int st = 0, dr = sizee -1;
    int mij;
    while(st <= dr)
    {
        mij = (st+dr)/2;
        if(set_array[mij] == x)
            return -1;

        if(set_array[mij] < x)
            st = mij + 1;
        else if(set_array[mij] > x)
            dr = mij - 1;
    }
    return st;
}

template <class T>
void Set<T>::inserare(T x) //inserez un element
{
    if(set_array == NULL) //daca nu am niciun element in multime
    {
        set_array = new T[1];
        max_size = 1;
        sizee = 1;
        set_array[0] = x;
    }
    else
    {
        int poz = search_poz(x); //caut binar pozitia pe care trebuie sa inserez elementul
        if(poz == -1) //daca elementul x este deja in multime, nu il mai inserez
            return;

        if(sizee + 1 > max_size) //daca depasesc memoria alocata pana acum
        {
            max_size = sizee + 1;
            set_array = (T*)realloc(set_array, (max_size) * sizeof(T)); //aloc memorie pt inserarea elementului x
        }

        for(int i = sizee - 1; i >= poz; i--) //mut elementele cu o pozitie la dreapta
            set_array[i+1] = set_array[i];
        sizee++;
        set_array[poz] = x; //inserez elementul x;
    }
}

template <class T>
void Set<T>::deletee(T x) //sterg elementul x din set
{
    int poz;
    poz = searchh(x); //caut binar pozitia elementului ce trebuie sters
    for(int i = poz; i < sizee; i++)
        set_array[i] = set_array[i+1];
    sizee--;
}

template <class T>
T Set<T>::suma() //calculez suma elementelor din multime
{
    T suma_elementelor = 0;
    for(int i = 0; i < sizee; i++)
        suma_elementelor += set_array[i];
    return suma_elementelor;
}

template <class T>
Set<T> Set<T>::elem_impar() //construiesc un set ce contine elementele impare
{
    Set aux;
    for(int i = 0; i < sizee; i++)
        if(set_array[i] % 2)
            aux.inserare(set_array[i]);
    return aux;
}

template <class T>
Set<T> Set<T>::elem_par() //construiesc un set ce contine elementele impare
{
    Set aux;
    for(int i = 0; i < sizee; i++)
        if(set_array[i] % 2 == 0)
            aux.inserare(set_array[i]);
    return aux;
}

template <class T>
const int Set<T>::nr_elem() const //returnez nr de elemente ale multimii
{
    return sizee;
}

template <class T>
T& Set<T>::operator[](int i)
{
    return set_array[i];
}

template <class T>
bool Set<T>::operator<(Set const& first_set)
{
    return this -> nr_elem() < first_set.nr_elem();
}

template <class T>
bool Set<T>::operator>(Set const& first_set)
{
    return this -> nr_elem() > first_set.nr_elem();
}

template <class T>
const T* Set<T>::getset_array() const
{
    return set_array;
}

template <class T>
Set<T> Set<T>::operator*(T const &x) //supraincarc operatorul * pt inmultirea cu un scalar
{
    for(int i = 0; i < sizee; i++)
        set_array[i] *= x;

    return *this;
}

template <class T>
Set<T> Set<T>::operator+(const Set& x)
{
    Set s(x);
    for(int i = 0; i < sizee; i++)
        s.inserare(set_array[i]);

    return s;
}

template <class T>
void Set<T>::operator=(const Set &first_set)
{
    sizee = first_set.sizee;
    max_size = first_set.max_size;
    if(set_array != NULL)
        delete[]set_array;
    set_array = new T[max_size];

    for(int i = 0; i < sizee; i++)
        set_array[i]=first_set.set_array[i];
}

template <class T>
Set<T>::~Set()
{
    //dtor
    if(set_array != NULL)
        delete []set_array;
}

#endif // SET_H
