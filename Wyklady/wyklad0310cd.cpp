#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>// titaj nie jest generowany kod szablonu  

    //qsort odrzuca kontroli typów i urzywa sie wskaźników na nic 
    //const void* -> wskaźnik na cokolwiek
int compare_ints(const void* a, const void* b)// tutaj sciągamy kontrole typów a potem w funkcji bedziemy je przywracać 
{
    
    
}
// od tego momentu kompulator wie ze zawza bedzie zarezerwowana dla tego szablonu 
template <typename T> // szablon zależny od typu T dla kazdego takiego szablonu jest generowana inna funckja optymalizowana do typu na ktorym dziala 
std::string name(const T & obj)
{
    return typeid(obj).name();
};
//mozna tez generować szablon na podstawie klasy
template <typename V>
class vector 
{
    size_v size;
    size_v capacity;
    V*      buffer;
public: 
vector(size_v n=0);

template<class T>
const T pi = T(3.14159265L);

template<class T>
float 

};
int main()
{
    
    std::vector<int> v{1,2,3};//tu generuje sie nowy kod z szablonu zestaw argumentów takie jak int czy float tworzą osobną klase
    std::vector<float> W{1,2,3};//tu generuje sie nowy kod 
    std::vector<int> X{1,2,3};// tu nie generuje sie nowy kod 

    auto x = 1;
    std::cout <<name(x)<<"\n"; //
    x=3.154321; 
    std::cout <<name(x)<<"\n";
    //x="ala";
    std::cout <<name("Ala")<<"\n"; // tabela 4 znakow poniewaz na koncu jest znak zerowy

}
//w c instancja klasy to obiekt klasy
//vector<int> <- konkretyzacja 
// jezeli chcemy zeby szablon byl widoczny w calym programie to musi byc w pliku .h nie w .cpp
// nastepnie w fukcjach nadajemy atrybuty inline]
// kompilacja przeprrowadzana jest w 2 fazach, ogolne sprawdzanie skadni( wstepna diagnostyka bledow)
// 