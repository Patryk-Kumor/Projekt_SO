#include "iostream"
#include <pthread.h>
#include <deque>
#include <unistd.h>


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
            if (Ile() > 0)
            {
                food.pop_front();
            }

        }
    }
    void Usun()
    {
        if (Ile() > 0)
        {
            food.pop_front();
        }
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
            if (Ile() > 0)
            {
                osadnicy.pop_back();
            }          
        }
    }
    void Dodaj()
    {
        osadnicy.push_front(18);
    }
    void Usun_Najstarszego()
    {
        if (Ile() > 0)
        {
            osadnicy.pop_back();
        }
    }
    void Usun_Losowego()
    {
    if (Ile() > 0)
    {
        int Maks = osadnicy.size();
        int E = rand()%Maks+1;
        osadnicy.erase(osadnicy.begin()+E);}
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
int full_houses;

//Deklaracje globalne aktorów
pthread_mutex_t m_hunters = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_gatherers = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_cooks = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_woodcutters = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_builders = PTHREAD_MUTEX_INITIALIZER;
Osadnicy hunters;
Osadnicy gatherers;
Osadnicy cooks;
Osadnicy woodcutters;
Osadnicy builders;
Dzieci kids;


void *hunting(void *arg)
{
    int H = rand()%6+1;
    int Z = rand()%6+1;
    if (H>=Z)
    {
        pthread_mutex_lock(&m_meat);
        meat.Dodaj();
        pthread_mutex_unlock(&m_meat);
    }


    pthread_mutex_lock(&m_food);
    if (food.Ile()>0)
    {
        food.Usun();
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_food);

        pthread_mutex_lock(&m_hunters);
        hunters.Usun_Losowego();
        pthread_mutex_unlock(&m_hunters);
        pthread_exit(NULL);
    }

    pthread_mutex_lock(&m_houses);
    if (full_houses<houses)
    {
        full_houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_houses);

        pthread_mutex_lock(&m_hunters);
        hunters.Usun_Losowego();
        pthread_mutex_unlock(&m_hunters);
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
    return NULL;
}
void *gathering(void *arg)
{
    pthread_exit(NULL);
    return NULL;
}
void *cooking(void *arg)
{
    pthread_exit(NULL);
    return NULL;
}
void *cutting(void *arg)
{
    pthread_exit(NULL);
    return NULL;
}
void *building(void *arg)
{
    pthread_exit(NULL);
    return NULL;
}
void *kids_stuff(void *arg)
{
    pthread_exit(NULL);
    return NULL;
}


int main(int argc, char* argv[])
{
    if (argc == 12) // 11 argumentów
    {
        //Aktorzy: myśliwi, zbieracze, kucharze, drwale, budowlańcy, dzieci
        hunters = Osadnicy(10,80);
        gatherers = Osadnicy(10,80);
        cooks = Osadnicy(10,80);
        woodcutters = Osadnicy(10,80);
        builders = Osadnicy(10,80);
        kids = Dzieci(10);
        //Zasoby: pożywienie, mięso, rośliny, drewno, domy
        meat = Jedzenie(365,25);
        plants = Jedzenie(365,15);
        food = Jedzenie(365,20);
        wood = 1;
        houses = 6;
        full_houses = 0;
        

        cout << "\n--- Symulacja rozpoczęta --- \n" << "Aktorzy: \n -";
        cout << "myśliwi ["<< hunters.Ile() <<"], zbieracze ["<< gatherers.Ile() <<"], ";
        cout << "kucharze ["<< cooks.Ile() <<"], drwale ["<< woodcutters.Ile() <<"], ";
        cout << "budowlańcy ["<< builders.Ile() <<"], dzieci ["<< kids.Ile() <<"]\n";
        cout << "Zasoby: \n -pożywienie ["<< food.Ile() <<"], mięso ["<< meat.Ile() <<"], ";
        cout << "rośliny ["<< plants.Ile() <<"], drewno ["<< wood <<"], domy ["<< houses <<"]\n";

        for (int i=0; i<365; i++)
        {
            full_houses = 0;
            int h = hunters.Ile(); pthread_t hunters_t[h];
            int g = gatherers.Ile(); pthread_t gatherers_t[g];
            int c = cooks.Ile(); pthread_t cooks_t[c];           
            int w = woodcutters.Ile(); pthread_t woodcutters_t[w];
            int b = builders.Ile(); pthread_t builders_t[b];
            int k = kids.Ile(); pthread_t kids_t[k];
  
  
            for (int i = 0; i<h; i++)
            {
                pthread_create(&hunters_t[i],NULL,hunting,NULL);
            }
            for (int i = 0; i<g; i++)
            {
                pthread_create(&gatherers_t[i],NULL,cooking,NULL);
            }
            for (int i = 0; i<c; i++)
            {
                pthread_create(&cooks_t[i],NULL,hunting,NULL);
            }
            for (int i = 0; i<w; i++)
            {
                pthread_create(&woodcutters_t[i],NULL,cutting,NULL);
            }
            for (int i = 0; i<b; i++)
            {
                pthread_create(&builders_t[i],NULL,building,NULL);
            }
            for (int i = 0; i<k; i++)
            {
                pthread_create(&kids_t[i],NULL,kids_stuff,NULL);
            }
                                                         
            /* działanie wielowątkowe */
            cout << "pętla" << endl;
	    usleep(1);
            
            for (int i = 0; i<h; i++)
            {
                pthread_join(hunters_t[i],NULL);
            }
            for (int i = 0; i<g; i++)
            {
                pthread_join(gatherers_t[i],NULL);
            }
            for (int i = 0; i<c; i++)
            {
                pthread_join(cooks_t[i],NULL);
            }
            for (int i = 0; i<w; i++)
            {
                pthread_join(woodcutters_t[i],NULL);
            }
            for (int i = 0; i<b; i++)
            {
                pthread_join(builders_t[i],NULL);
            }
            for (int i = 0; i<k; i++)
            {
                pthread_join(kids_t[i],NULL);
            }
                                 
            food.Termin(); meat.Termin(); plants.Termin();
            hunters.Wiek(); gatherers.Wiek(); cooks.Wiek();
            woodcutters.Wiek(); builders.Wiek();
        }
        
        cout << "\n\n--- Symulacja zakończona --- \n" << "Aktorzy: \n -";
        cout << "myśliwi ["<< hunters.Ile() <<"], zbieracze ["<< gatherers.Ile() <<"], ";
        cout << "kucharze ["<< cooks.Ile() <<"], drwale ["<< woodcutters.Ile() <<"], ";
        cout << "budowlańcy ["<< builders.Ile() <<"], dzieci ["<< kids.Ile() <<"]\n";
        cout << "Zasoby: \n -pożywienie ["<< food.Ile() <<"], mięso ["<< meat.Ile() <<"], ";
        cout << "rośliny ["<< plants.Ile() <<"], drewno ["<< wood <<"], domy ["<< houses <<"]\n";
    }
    else
    {
        cout << "Niepoprawna liczba argumentów \n";
    }
}

