#include<iostream>
#include<vector>

#include "worki.h"

using namespace std;

//
/*
0
1
2
3
4
5
6
7
*/
enum {
    NOWY_WOREK, 
    NOWY_PRZEDMIOT,
    WYJMIJ_P,
    WYJMIJ_W,
    ZAMIANA,
    ILE_P,
    WLOZ_P,
    WLOZ_W,
    NR_WORKA,
    WOREK_W
};


int main(){
    int q;
    cin>>q;
    vector<przedmiot*> P;
    vector<worek*> W;
    for(int i = 0; i<q; i++){
        int c;
        cin>>c;
        int a,b,d;
        //worek* w;
        switch(c){
            case NOWY_WOREK:
                W.push_back(nowy_worek());
                cout<<"NOWY WOREK:" << W.size()-1<<"\n";
                break;
            case NOWY_PRZEDMIOT:
                P.push_back(nowy_przedmiot());
                cout<<"NOWY PRZEDMIOT:" << P.size()-1<<"\n";
                break;
            case WLOZ_P:
                cin>>a>>b;
                cout<<"WKLADAM PRZEDMIOT "<<a<<" DO WORKA "<<b<<"\n";
                cout<<ile_przedmiotow(W[b])<<"\n";
                wloz(P[a], W[b]);
                cout<<"WLOZONY, ROZMIAR\n";
                cout<<ile_przedmiotow(W[b])<<"\n";
                break;
            case WYJMIJ_P:
                cout<<"WYJMUJE PRZEDMIOT "<<a<<" Z WORKA "<<w_ktorym_worku(P[a])<<"\n";
                cin>>a;
                d = w_ktorym_worku(P[a]);
                cout<<ile_przedmiotow(W[d])<<"\n";
                wyjmij(P[a]);
                cout<<"WYJETY, rozmiar worka\n";
                cout<<ile_przedmiotow(W[d])<<"\n";
                break;
            case WLOZ_W:
                cin>>a>>b;
                //co, gdzie
                cout<<"WKLADAM WOREK "<<a<<" DO WORKA "<<b<<"\n";
                cout<<ile_przedmiotow(W[a])<<"\n";
                cout<<ile_przedmiotow(W[b])<<"\n";
                wloz(W[a],W[b]);
                cout<<ile_przedmiotow(W[b])<<"\n";
                break;
            case WYJMIJ_W:
                cin>>a;

                d = w_ktorym_worku(W[a]);
                cout<<"WYJMUJE WOREK "<<a<<" Z WORKA "<<d<<"\n";
                cout<<ile_przedmiotow(W[w_ktorym_worku(W[a])])<<"\n";
                wyjmij(W[a]);
                cout<<ile_przedmiotow(W[d])<<"\n";
                break;
            case ILE_P:
                
                cin>>a;
                cout<<"PRZEDMIOTY W WORKU "<<a<<"\n";
                cout<<ile_przedmiotow(W[a])<<"\n";
                break;
            case ZAMIANA:

                cin>>a;
                cout<<"WIELKA ZAMIANA Z "<<a<<"\n";
                cout<<ile_przedmiotow(W[a])<<"\n";
                na_odwrot(W[a]);
                cout<<ile_przedmiotow(W[a])<<"\n";
                break;
            case NR_WORKA:
                cin>>a;
                cout<<"PRZEDMIOT "<<a<<" W WORKU\n";
                cout<<w_ktorym_worku(P[a])<<"\n";
                break;
            
            case WOREK_W:
                cin>>a;
                cout<<"WOREK "<<a<<" W "<<w_ktorym_worku(W[a])<<"\n";
                break;
        }
    }

}
