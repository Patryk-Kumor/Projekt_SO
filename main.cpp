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
        int i; int ile_przeterminowanych = 0;
        for (i=0; i<Ile(); i++)
        {
            food[i] -= 1;
            if (food[i] <= 0) { ile_przeterminowanych++; }
        }
        for (i=0; i<ile_przeterminowanych; i++)
        {
            food.pop_front();
        }
    }
    void Usun()
    {
        food.pop_front();
    }
    void Dodaj()
    {
        food.push_back(food_termin);
    }
    void Wypisz()
    {
        int i;
        for (i=0; i<Ile(); i++)
        {
            cout << food[i] << endl;
        }
    }
};


class Osadnicy
{
public:
    deque<int> osadnicy;
    int maks_wiek;
    Osadnicy()
    {
        deque<int> osadnicy;
    }
    Osadnicy(int ilosc, int termin)
    {
        maks_wiek = termin;
        int i;
        for (i=0; i<ilosc; i++)
        {
            osadnicy.push_back(18);
        }
    }
    int Ile()
    {
        return osadnicy.size();
    }
    void Wiek()
    {
        int i; int ile_przeterminowanych = 0;
        for (i=0; i<Ile(); i++)
        {
            osadnicy[i] += 1;
            if (osadnicy[i] >= maks_wiek) { ile_przeterminowanych++; }
        }
        for (i=0; i<ile_przeterminowanych; i++)
        {
            osadnicy.pop_back();
        }
    }
    void Dodaj()
    {
        osadnicy.push_front(18);
    }
    void Usun_Najstarszego()
    {
        osadnicy.pop_back();
    }
    void Usun_Losowego()
    {
        int Maks = osadnicy.size();
        int E = rand()%Maks+1;
        osadnicy.erase(osadnicy.begin()+E);
    }
    void Wypisz()
    {
        int i;
        for (i=0; i<Ile(); i++)
        {
            cout << osadnicy[i] << endl;
        }
    }
};


int main(int argc, char* argv[])
{
   // int A = atoi(argv[1]);
   // cout << A;

    deque<int> osadnicy;
    osadnicy.push_back(1); osadnicy.push_back(2); osadnicy.push_back(3);
    cout << endl << osadnicy[0] << osadnicy[1] << osadnicy[2] << osadnicy[3] << endl;
	cout << osadnicy.size();	
    osadnicy.erase(osadnicy.begin()+1);
    cout << endl << osadnicy[0] << osadnicy[1] << osadnicy[2] << endl;
	cout << osadnicy.size();	
	cout << osadnicy.max_size() << endl << endl;

    Osadnicy nasi;
    nasi = Osadnicy(3,18);
    nasi.Wypisz();
    cout << endl;
    nasi.Usun_Losowego();
    nasi.Wypisz();
    cout << endl;
    nasi.Usun_Losowego();
    nasi.Wypisz();
    cout << endl;
    nasi.Usun_Losowego();
    nasi.Wypisz();
    cout << nasi.Ile() << endl;
}

