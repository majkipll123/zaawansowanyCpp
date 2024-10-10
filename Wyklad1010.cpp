#include <array>
//przeciazanie nazw szablonów
template <typename T>
//inline T const& max(const* T const& a, const* T const& b)
//{
//    return a < b? b : a;
//}
// specializacja czesciowa polega na tym ze mozemy zrobic szablon z klasy ktory dziala na wszystkich typach
// dodatkowo mozna zrobic vektor tylko od wskaźników na T  ten ktory dziala na wszystkim jest ogolnym a ten ktory dziala na niektorych jest szczególny
// kompilator spróbyuje wykonać w szczególnej klasie jezeli nie wyjdzie to przejdzie do ogólnego 
// specializacna pelna polega na tym zeby np preciazyc fukcje max do porównywania wskaźników nie za pomocą znaków < tylko np funkcji strcmp(a.b)
// szablon ogólny oraz szablon specializowany nie dziedziczy funkcji po sobie 
int main()
{

    return 0;
}