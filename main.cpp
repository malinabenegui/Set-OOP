#include <iostream>
#include "Set.h"

using namespace std;

int main()
{
    double a[]={1, 2.7, 3, 1, 2, 3.18};
    bool x, y;
    Set<double> first_set, set1(a, 6), set2(set1);
    first_set.inserare(32.9);
    first_set.inserare(7);
    first_set.inserare(7.53);
    first_set.inserare(54);
    first_set.inserare(2.31);
    first_set.inserare(5);

    cout << "first_set initial este: "<< first_set << '\n' << '\n';
    cout << "Afisez set1" << set1 << '\n';


    first_set = first_set*2;
    cout << "Inmultesc first_set cu 2 si afisez rezultatul: " << first_set << '\n' << '\n';

    first_set.deletee(14);


    cout << "Afisez first_set, dupa ce am sters elementul 14: " << first_set << '\n' << '\n';

    cout << "Afisez set2 (copia lui set1): "<< set2 << '\n' << '\n';
    cout << "Caut elementul 5 in first_set: ";
    cout << first_set.searchh(5) << '\n' << '\n';

    first_set = (first_set + set1);
    cout <<"Adun first_set cu set1: "<< first_set << '\n' << '\n';

    x = first_set < set1;
    y = first_set > set1;
    cout <<"Verific daca first_set < set1, respectiv daca first_set > set1: "<< x << " " << y << '\n' << '\n';

    cout <<"Calculez suma elementelor multimii: "<< first_set.suma() << '\n' << '\n';
    cout <<"Numarul de elemente ale setului este: "<< first_set.nr_elem() << '\n' << '\n';


    //cout <<"Elementele impare din set sunt: "<< '\n' << first_set.elem_impar()<< '\n'  << '\n';
    //cout <<"Elementele pare din set sunt: "<< first_set.elem_par() << '\n' << '\n';

    return 0;
}
