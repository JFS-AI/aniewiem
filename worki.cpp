#include "worki.h"
#include <algorithm>
#include <list>

using namespace std;

static int indeks = 0;
worek *wsk_na_biurko = new worek;
static list<worek*> smieciarka_w{wsk_na_biurko};
static list<przedmiot*> smieciarka_p;

// Wkłada worek co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(worek *co, worek *gdzie){
    co->wsk = gdzie;
    gdzie->l_elementow += co->l_elementow;
}

// Wkłada przedmiot co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(przedmiot *co, worek *gdzie){
    co->wsk = gdzie;
    gdzie->l_elementow++;
}

// Nowy worek na biurku; otrzymuje kolejny numer, począwszy od 0.
worek *nowy_worek(){
    worek *w = new worek{.wsk = nullptr, .numer = indeks++};
    wloz(w, wsk_na_biurko);
    smieciarka_w.push_back(w);
    return w;
}

// Nowy przedmiot na biurku
przedmiot *nowy_przedmiot(){
    przedmiot *p = new przedmiot{};
    wloz(p, wsk_na_biurko);
    smieciarka_p.push_back(p);
    return p;
}

// Wyjmuje przedmiot p z worka i kładzie na biurku.
// Założenie: Przedmiot p był w worku leżącym na biurku.
void wyjmij(przedmiot *p){
    p->wsk->l_elementow--;
    p->wsk = wsk_na_biurko;
}

// Wyjmuje worek w z worka i kładzie na biurku.
// Założenie: Worek w był w worku leżącym na biurku.
void wyjmij(worek *w){
    w->wsk->l_elementow -= w->l_elementow;
    w->wsk = wsk_na_biurko;
}

// Wynik: numer worka, w którym znajduje się przedmiot p (-1 jeśli na biurku).
int w_ktorym_worku(przedmiot *p){
    return p->wsk->numer;
}

// Wynik: numer worka, w którym znajduje się worek w (-1 jeśli na biurku).
int w_ktorym_worku(worek *w){
    return w->wsk->numer;
}

// Wynik: liczba przedmiotów zawartych (bezpośrednio i pośrednio) w worku w
int ile_przedmiotow(worek *w){
    return w->l_elementow;
}

// Cała zawartość worka w ląduje na biurku, a wszystko, co poza workiem w
// znajdowało się bezpośrednio na biurku, ląduje wewnątrz worka w.
void na_odwrot(worek *&w){
    swap(w, wsk_na_biurko);
    swap(w->numer, wsk_na_biurko->numer);
    w->wsk = wsk_na_biurko;
}

template <typename T>
static void delete_na_liscie(list<T>& v){
    for(T x: v)
        delete(x);
}

// Kończy i zwalnia pamięć
void gotowe(){
    delete_na_liscie(smieciarka_p);
    delete_na_liscie(smieciarka_w);
}