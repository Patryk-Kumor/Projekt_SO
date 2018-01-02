#include "iostream"
#include <pthread.h>
#include <deque>

using namespace std;

class Jedzenie
{
public:
    deque<int> food;
    Jedzenie()
    {
        deque<int> food;
    }
    Jedzenie(int ilosc, int termin)
    {
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
    void Dodaj(int termin)
    {
        food.push_back(termin);
    }
};


int main(int argc, char* argv[])
{
    deque<int> jedzenie;

    jedzenie.push_back(1);
    cout << jedzenie [0] << endl;

    jedzenie.push_back(2);
    cout << jedzenie [0] << jedzenie [1] << jedzenie [2] << endl;

    jedzenie.push_front(3);
    cout << jedzenie [0] << jedzenie [1] << jedzenie [2] << jedzenie [3] << endl;

    jedzenie.push_front(3);
    cout << jedzenie [-1] << jedzenie [0] << jedzenie [1] << jedzenie [2] << jedzenie [3] << endl;

    cout << jedzenie.size() << endl;;

    jedzenie[0] = 9;

    cout << jedzenie [-1] << jedzenie [0] << jedzenie [1] << jedzenie [2] << jedzenie [3] << endl;

    Jedzenie food;
    food = Jedzenie(3,5);
    cout << food.Ile() << endl << endl;


    food.Wypisz();
    food.Termin();
    food.Wypisz();
    food.Wykorzystaj(); food.Wykorzystaj(); food.Wykorzystaj();
    cout << endl;
    food.Wypisz();
}

