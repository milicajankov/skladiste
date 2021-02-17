#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;
class Proizvod {
protected:
    int id;
    char oznaka;
public:
    Proizvod(int i, char o): id(i), oznaka(o) { }
    virtual double zapremina()const = 0; //apstraktna klasa sada

    virtual int getId(){
        return id;
    }

    virtual string ispis() const { //redefinisu je sanduk i bure
        return string("[") + oznaka + "," + to_string(id) + "]";

    }

    virtual bool poredjenje(const Proizvod &r)const { //redefinisu je sanduk i bure
        return (id==r.id) && (oznaka==r.oznaka);
    }
    friend ostream& operator << (ostream& out, const Proizvod& p){
        out << p.ispis();
        return out;
    }
    friend bool operator == (const Proizvod &p1, const Proizvod &p2){
        return p1.poredjenje(p2);

    }
    friend bool operator != (const Proizvod &p1, const Proizvod &p2){
        return !(p1.poredjenje(p2));
    }
};

class Sanduk: public Proizvod{
    double a, b, c;
public:
    Sanduk(int i, double aa=0., double bb=0., double cc=0.): Proizvod(i, 'S'), a(aa), b(bb), c(cc){ }
    double zapremina() const {
        return a*b*c;
    }
   string ispis() const { //redefinisu je sanduk i bure
        return Proizvod::ispis()  +  "(" + to_string(a) + "," + to_string(b) + ", " + to_string(c) + ")";

    }
   bool poredjenje(const Sanduk &s)const {
        return Proizvod::poredjenje(s) && (a==s.a) && (b==s.b) && (c==s.c);
   }
    int getId(Sanduk &s)const{
        return s.id;
    }
};

class Bure : public Proizvod{
    double r, h;
public:
    Bure(int i , double rr=0., double hh=0.) : Proizvod(i, 'B'), r(rr), h(hh){}
    string ispis() const {
        return Proizvod::ispis() + string("(") + to_string(r) + " , "  +  to_string(h) + ")";
    }
    bool poredjenje(const Bure &b)const {
        return Proizvod:: poredjenje(b) && (r==b.r) && (h==b.h);
    }

    double zapremina()const {
        return 2*M_PI*r*h;
                    }
     int getId(Bure &b)const{
        return b.id;
    }
};
class Skladiste {
    vector<Proizvod*> skup; //u pocetku je ovaj niz prazan
    int max_mesta;
    double max_vol;
public:
    Skladiste(int m, double v): max_mesta(m), max_vol(v) { }

    int trenutni_broj()const{ // broj elemenata
        return skup.size();
    }

    int max_broj()const{
        return max_mesta;
    }
    int max_id()const{
        auto poc=0;
        auto tmp=0;
        for(auto x: skup){
            if(poc < x->getId()){
                tmp+=x->getId();
                poc=tmp;
                }
            return poc;
            }
    }
    double trenutna_vol()const{
        double res=0.;
        for(auto x: skup)
            res+= x->zapremina();
            return res;
    }

    double preostala_vol()const {
        return max_vol - trenutna_vol();

    }
    void dodaj(Proizvod* p ){
        if(trenutni_broj() < max_mesta && (p-> zapremina() + trenutna_vol())<= max_vol){
        skup.push_back(p); //na kraj niza
        }
        else
        cout<<"greska";
    }
    void izbaci(const Proizvod *p){
        size_t i = 0;
        for(i=0; i<skup.size(); ++i)
            if(*skup[i] == *p)
                break;
            skup.erase(skup.begin() + i);
    }
    friend ostream& operator << (ostream &out, const Skladiste &s){

    out << "Sadrzaj skladista: " << endl;
    for(auto p: s.skup)
        out << (*p) << endl;
        return out;
    }
};
int main()
{
    Skladiste s(7, 3000);
    s.dodaj(new Sanduk(1, 2 , 4, 3 ));
    s.dodaj(new Sanduk(9, 2, 3, 5));
    s.dodaj(new Bure (1, 2, 4));
    s.dodaj(new Bure (5, 2 ,4));
    s.izbaci(new Bure (1, 2, 4));
    cout << s << endl;
    cout << s.trenutna_vol() << endl;
    cout << s.preostala_vol() << endl;
    cout << s.trenutni_broj() << endl;
    cout << s.max_broj() << endl;
    cout << s.max_id() << endl;
    /*vector<Proizvod*>niz;
    for(auto el : niz)
        cout << *el << endl;

    cout << endl << "Najnoviji: "
         << **min_element(niz.begin(), niz.end(),
                          [](Proizvod *a, Proizvod *b) {return a->getId() > b->getId();}
                          ) << endl;

    cout << endl << "Najjeftiniji: "
         << **min_element(niz.begin(), niz.end(),
                          [](Proizvod  *a, Proizvod  *b) {return a->getId() < b->getId();}
                          ) << endl;
    double suma = 0;
    for (auto el: niz)
        suma += el->getId();
    */
    /*cout << "Prosecna cena: " << suma / niz.size() << endl;
    cout << "Android telefoni: " << count_if(niz.begin(), niz.end(),
                                             [](Proizvod  *p){ if(p->getOS() == "Android")
                                                            return true;
                                                           return false;}
                                             ) << endl;

    // primer lambde
    auto f = [](int a, int b) {return a + b;};
    cout << endl << endl << f(4,5) << endl;
*/
    /*Sanduk s(0, 1, 2, 3);
    Sanduk x(2, 2, 3, 5);

    Bure b(0, 1, 2);
    Bure y(0, 1, 2);
    cout << s;
    cout << endl;
    cout << x;
    cout << endl;
    cout << (s==y) << endl;// mogu da poredim bure i sanduk jer je == virtuelna funkcija
    cout << (b==y) << endl;
    cout << (s!=x) << endl;
    cout << s.poredjenje(x);*/

    return 0;
}
