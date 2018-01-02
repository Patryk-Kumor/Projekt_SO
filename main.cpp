#include "iostream"
#include <pthread.h>
#include <deque>

using namespace std;

class Jedzenie
{
public:
    deque<int> food;
    int food_termin;
    Jedzenie()
    {
        deque<int> food;
    }
    Jedzenie(int ilosc, int termin)
    {
	food_termin = termin;
        int i;
        for (i=0; i<ilosc; i++)
        {
            food.push_back(termin);
        }
    }
    int Ile()
    {
        return food.size();
    }
    void Termin()
    {
        int i;
        for (i=0; i<Ile(); i++)
        {
            food[i] -= 1;
            if (food[i] <= 0) { food.pop_front(); }
        }
    }
    void Wypisz()
    {
        int i;
        for (i=0; i<Ile(); i++)
        {
            cout << food[i] << endl;
        }
    }
    void Wykorzystaj()
    {
        food.pop_front();
    }
    void Dodaj()
    {
        food.push_back(food_termin);
    }
};


int main(int argc, char* argv[])
{
    Jedzenie food;
    food = Jedzenie(3,5);
    cout << food.Ile() << endl << endl;


    food.Wypisz();
    food.Termin();   food.Wypisz();
    food.Wykorzystaj(); food.Wykorzystaj(); food.Wykorzystaj(); food.Dodaj(); food.Dodaj();
    food.Termin(); food.Wypisz();
    food.Termin(); food.Wypisz();
    food.Termin(); food.Wypisz(); food.Dodaj();
    food.Termin(); food.Wypisz();
    food.Termin(); food.Wypisz();
    food.Termin(); food.Wypisz();
    cout << endl;
    food.Wypisz();
    food.Termin(); food.Wypisz();
    food.Termin(); food.Wypisz();
    food.Termin(); food.Wypisz(); cout << endl;
    food.Termin(); food.Wypisz();
    food.Termin(); food.Wypisz();
     cout << food.Ile() << endl;
}

