#include "worki2.h"
#include <algorithm>
#include <list>

using namespace std;

static worek *wsk_na_biurko = new worek(-1);
static list<worek*> smieciarka_w{wsk_na_biurko};
static list<przedmiot*> smieciarka_p;

// Wkłada worek co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(worek *co, worek *gdzie){
    co->wsrodku = gdzie->syn;
    gdzie->syn->l_przedmiotow += co->syn->l_przedmiotow;
}

// Wkłada przedmiot co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(przedmiot *co, worek *gdzie){
    co->wsrodku = gdzie->syn;
    gdzie->syn->l_przedmiotow++;
}

// Nowy worek na biurku; otrzymuje kolejny numer, począwszy od 0.
worek *nowy_worek(){
    static int indeks = 0;
    worek *w = new worek(indeks++);
    wloz(w, wsk_na_biurko);
    smieciarka_w.push_back(w);
    return w;
}

// Nowy przedmiot na biurku
przedmiot *nowy_przedmiot(){
    przedmiot *p = new przedmiot;
    wloz(p, wsk_na_biurko);
    smieciarka_p.push_back(p);
    return p;
}

// Wyjmuje przedmiot p z worka i kładzie na biurku.
// Założenie: Przedmiot p był w worku leżącym na biurku.
void wyjmij(przedmiot *p){
    p->wsrodku->l_przedmiotow--;
    p->wsrodku = wsk_na_biurko->syn;
}

// Wyjmuje worek w z worka i kładzie na biurku.
// Założenie: Worek w był w worku leżącym na biurku.
void wyjmij(worek *w){
    w->wsrodku->l_przedmiotow -= ile_przedmiotow(w);
    w->wsrodku = wsk_na_biurko->syn;
}

// Wynik: numer worka, w którym znajduje się przedmiot p (-1 jeśli na biurku).
int w_ktorym_worku(przedmiot *p){
    return p->wsrodku->rodzic->numer;
}

// Wynik: numer worka, w którym znajduje się worek w (-1 jeśli na biurku).
int w_ktorym_worku(worek *w){
    return w->wsrodku->rodzic->numer;
}

// Wynik: liczba przedmiotów zawartych (bezpośrednio i pośrednio) w worku w
int ile_przedmiotow(worek *w){
    return w->syn->l_przedmiotow;
}

// Cała zawartość worka w ląduje na biurku, a wszystko, co poza workiem w
// znajdowało się bezpośrednio na biurku, ląduje wewnątrz worka w.
void na_odwrot(worek *w){
    swap(w->syn, wsk_na_biurko->syn);
    w->syn->rodzic = w;
    wsk_na_biurko->syn->rodzic = wsk_na_biurko;
    w->wsrodku = wsk_na_biurko->syn;

    // na poczatku w worku bylo x przedmiotow, a na biurku x+y
    // teraz jest   x+y, x
    // chcemy       y, x+y
    w->syn->l_przedmiotow -= ile_przedmiotow(wsk_na_biurko); // x+y -= x
    wsk_na_biurko->syn->l_przedmiotow += ile_przedmiotow(w); // x   += y
}

template <typename T>
static void delete_na_liscie(list<T>& v){
    for(T x: v)
        delete x;
}

// Kończy i zwalnia pamięć
void gotowe(){
    delete_na_liscie(smieciarka_p);
    delete_na_liscie(smieciarka_w);
}