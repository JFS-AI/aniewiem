#include "worki3.h"
#include <algorithm>
#include <memory>
#include <list>

using namespace std;

// trzymacz trzyma zawartosc workow
// przedmioty i worki posiadaja wskazniki na trzymacz, w srodku ktorego sie znajduja
// worki dodatkowo posiadaja wskaznik na wlasna zawartosc (syn)

namespace {

    struct trzymacz_wskaznikow {
        worek *rodzic = nullptr;
        int l_przedmiotow = 0;
    };

}

struct przedmiot {
    trzymacz_wskaznikow *wsrodku = nullptr;
    przedmiot(trzymacz_wskaznikow *w) : wsrodku(w) {};
    virtual ~przedmiot() = default;
};

struct worek : przedmiot {
    unique_ptr<trzymacz_wskaznikow> syn;
    int numer = -1;
    worek(int n, trzymacz_wskaznikow *w = nullptr) 
        : przedmiot(w), syn(make_unique<trzymacz_wskaznikow>(this)), numer(n) {};
    
    worek(const worek&) = delete;
    worek& operator=(const worek&) = delete;
};

static const int NUMER_BIURKA = -1;
static auto posiadacz_biurka = make_unique<worek>(NUMER_BIURKA);
static list<unique_ptr<przedmiot>> smieciarka;

// Nowy worek na biurku; otrzymuje kolejny numer, począwszy od 0.
worek *nowy_worek() {
    static int indeks = 0;
    smieciarka.push_back(make_unique<worek>(indeks++, posiadacz_biurka->syn.get()));
    return static_cast<worek*>(smieciarka.back().get());
}

// Nowy przedmiot na biurku
przedmiot *nowy_przedmiot() {
    smieciarka.push_back(make_unique<przedmiot>(posiadacz_biurka->syn.get()));
    posiadacz_biurka->syn->l_przedmiotow++;
    return smieciarka.back().get();
}

// Wynik: liczba przedmiotów zawartych (bezpośrednio i pośrednio) w worku w
int ile_przedmiotow(worek *w) {
    return w->syn->l_przedmiotow;
}

// Wkłada worek co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(worek *co, worek *gdzie) {
    co->wsrodku = gdzie->syn.get();
    gdzie->syn->l_przedmiotow += ile_przedmiotow(co);
}

// Wkłada przedmiot co do worka gdzie.
// Założenie: co i gdzie leżą na biurku.
void wloz(przedmiot *co, worek *gdzie) {
    co->wsrodku = gdzie->syn.get();
    gdzie->syn->l_przedmiotow++;
}

// Wyjmuje przedmiot p z worka i kładzie na biurku.
// Założenie: Przedmiot p był w worku leżącym na biurku.
void wyjmij(przedmiot *p) {
    p->wsrodku->l_przedmiotow--;
    p->wsrodku = posiadacz_biurka->syn.get();
}

// Wyjmuje worek w z worka i kładzie na biurku.
// Założenie: Worek w był w worku leżącym na biurku.
void wyjmij(worek *w) {
    w->wsrodku->l_przedmiotow -= ile_przedmiotow(w);
    w->wsrodku = posiadacz_biurka->syn.get();
}

// Wynik: numer worka, w którym znajduje się przedmiot p (-1 jeśli na biurku).
int w_ktorym_worku(przedmiot *p) {
    return p->wsrodku->rodzic->numer;
}

// Wynik: numer worka, w którym znajduje się worek w (-1 jeśli na biurku).
int w_ktorym_worku(worek *w) {
    return w->wsrodku->rodzic->numer;
}

// Cała zawartość worka w ląduje na biurku, a wszystko, co poza workiem w
// znajdowało się bezpośrednio na biurku, ląduje wewnątrz worka w.
void na_odwrot(worek *w) {
    swap(w->syn, posiadacz_biurka->syn);

    // teraz w->wsrodku == w->syn, wiec trzeba to naprawic
    w->wsrodku = posiadacz_biurka->syn.get();

    // musimy pamietac ze wskazniki ida w OBIE strony, czyli je tez trzeba zaktualizowac
    swap(w->syn->rodzic, posiadacz_biurka->syn->rodzic);

    // na poczatku w worku bylo x przedmiotow, a na biurku x+y
    // teraz jest   x+y, x
    // chcemy       y, x+y
    w->syn->l_przedmiotow -= ile_przedmiotow(posiadacz_biurka.get()); // x+y -= x
    posiadacz_biurka->syn->l_przedmiotow += ile_przedmiotow(w);       // x   += y
}

// Kończy i zwalnia pamięć
void gotowe() {
    smieciarka.clear(); // tak naprawde nie musimy nic recznie zwalniac 
}