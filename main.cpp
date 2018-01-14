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


class Dzieci
{
public:
    deque<int> osadnicy;
    int maks_wiek;
    int ile_doroslych;
    Dzieci()
    {
        deque<int> osadnicy;
    }
    Dzieci(int ilosc)
    {
        maks_wiek = 18;
        ile_doroslych = 0;
        int i;
        for (i=0; i<ilosc; i++)
        {
            osadnicy.push_back(1);
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
        ile_doroslych += ile_przeterminowanych;
    }
    int Dorosli()
    {
        int temp = ile_doroslych;
        ile_doroslych = 0;
        return temp;
    }
    void Dodaj()
    {
        osadnicy.push_front(1);
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


//Deklaracje globalne zasobów
pthread_mutex_t m_meat = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_plants = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_food = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_wood = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_houses = PTHREAD_MUTEX_INITIALIZER;
Jedzenie meat; 
Jedzenie plants; 
Jedzenie food; 
int wood; 
int houses;


int main(int argc, char* argv[])
{
    if (argc == 12) // 11 argumentów
    {
        //Aktorzy: myśliwi, kucharze, zbieracze, drwale, budowlańcy, dzieci
        //Zasoby: pożywienie, mięso, rośliny, drewno, domy

        food = Jedzenie(1,20);
        meat = Jedzenie(1,25);
        plants = Jedzenie(1,15);
        wood = 1;
        houses = 1;

        Osadnicy hunters; hunters = Osadnicy(1,80);
        Osadnicy cooks; cooks = Osadnicy(1,80);
        Osadnicy gatherers; gatherers = Osadnicy(1,80);
        Osadnicy woodcutters; woodcutters = Osadnicy(1,80);
        Osadnicy builders; builders = Osadnicy(1,80);
        Dzieci kids; kids = Dzieci(1);

        cout << "\n--- Symulacja rozpoczęta --- \n" << "Aktorzy: \n -";
        cout << "myśliwi ["<< hunters.Ile() <<"], kucharze ["<< cooks.Ile() <<"], ";
        cout << "zbieracze ["<< gatherers.Ile() <<"], drwale ["<< woodcutters.Ile() <<"], ";
        cout << "budowlańcy ["<< builders.Ile() <<"], dzieci ["<< kids.Ile() <<"]\n";
        cout << "Zasoby: \n -pożywienie ["<< food.Ile() <<"], mięso ["<< meat.Ile() <<"], ";
        cout << "rośliny ["<< plants.Ile() <<"], drewno ["<< wood <<"], domy ["<< houses <<"]\n";

        for (int i=0; i<365; i++)
        {
            //Wywoływanie procedur
            //Wywoływanie funkcji
        }
    }
    else
    {
        cout << "Niepoprawna liczba argumentów \n";
    }
}

