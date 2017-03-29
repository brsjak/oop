/*Вештачко цвеќе Problem 1 (3 / 32)
Да се имплементира апстрактна класа за репрезентација на вештачко цвеќе. За секое вечтачко цвеќе се чуваат податоци за неговото име (низа од знаци), основна цена (цел број) и боја која преовладува на цвеќето (низа од знаци).

Од класата VestackoCveke да се изведат класите SoSaksija и BezSaksija. За секое цвеќе кое е во саксија се чува колку е неговата маса (децимален број), а за цвеќето без саксија се чува инфомрација дали има цветови (булова променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод vratiCena, за пресметување на цената на цвеќето на следниот начин:

За SoSaksija - основната цена се зголемува за 30% од вредноса на неговата маса.

За BezSaksija - основната цена се зголемува за 50 ако цвеќето има цветови (10 поени)

преоптоварен оператор ! = за споредба на две вештачки цвеќиња. Две цвеќиња се различни ако имаат различна боја која преовладува. (5 поени)

Да се имплементира функција pecatiMinCena што на влез прима низа од вештачки цвеќиња, бројот на елементите од низата и едно вештачко цвеќе V. Функцијата го печати името, бојата и цена на најевтиното цвеќе од цвеќињата од низата кои се со различна боја со цвеќето V (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)*/
#include <iostream>
#include <cstring>

using namespace std;

class VestackoCveke {
protected:
    char ime[10];
    int osnovnaCena;
    char boja[10];
public:
    VestackoCveke() {}
    VestackoCveke(char ime[], int osnovnaCena, char boja[]) {
        strcpy(this->ime,ime);
        this->osnovnaCena=osnovnaCena;
        strcpy(this->boja,boja);
    }
    void setIme(char ime[]) {
        strcpy(this->ime,ime);
    }
    void setCena(int osnovnaCena) {
        this->osnovnaCena=osnovnaCena;
    }
    void setBoja(char boja[]) {
        strcpy(this->boja,boja);
    }
    char *getIme() {
        return ime;
    }
    int getCena() {
        return osnovnaCena;
    }
    char *getBoja() {
        return boja;
    }
    virtual float vratiCena()=0;
    virtual ~VestackoCveke() {}
};

class SoSaksija:public VestackoCveke {
private:
    float masa;
public:
    SoSaksija() {}
    SoSaksija(char ime[], int osnovnaCena, char boja[], float masa):VestackoCveke(ime,osnovnaCena,boja) {
        this->masa=masa;
    }
    void setMasa(float masa) {
        this->masa=masa;
    }
    float getMasa() {
        return masa;
    }
    float vratiCena() {
        return osnovnaCena+(masa*30/100);
    }
    ~SoSaksija() {}
};
class BezSaksija:public VestackoCveke {
private:
    bool cvetovi;
public:
    BezSaksija() {}
    BezSaksija(char ime[], int osnovnaCena, char boja[], bool cvetovi):VestackoCveke(ime,osnovnaCena,boja) {
        this->cvetovi=cvetovi;
    }
    void setCvetovi(bool cvetovi) {
        this->cvetovi=cvetovi;
    }
    bool getCvetovi() {
        return cvetovi;
    }
    float vratiCena() {
        if(cvetovi) {
            return osnovnaCena+50;
        }
        return osnovnaCena;
    }
    ~BezSaksija() {}
};
bool operator!=(VestackoCveke *s, VestackoCveke &sc) {
    if(strcmp(s->getBoja(),sc.getBoja())==0) {
        return true;
    }
    return false;
}
void pecatiMinCena(VestackoCveke **cvekinja, int n, VestackoCveke &v) {
    float minCena=9999;
    int minI=0;
    for(int i=0; i<n; i++) {
        if(!(cvekinja[i]!=v) ){
            if(cvekinja[i]->vratiCena()<minCena) {
                minCena=cvekinja[i]->vratiCena();
                minI=i;
            }
        }
    }
    cout<<cvekinja[minI]->getIme()<<" "<<cvekinja[minI]->getBoja()<<" "<<minCena<<endl;
}
/*
Да се имплементира функција pecatiMinCena што на влез прима низа од вештачки цвеќиња, бројот на елементите од низата и едно вештачко цвеќе V. Функцијата го печати името, бојата и цена на најевтиното цвеќе од цвеќињата од низата кои се со различна боја со цвеќето V (погледни го повикот на функцијата) (10 поени)
*/

int main() {

    char ime[20],boja[10];
    int tip,cena;
    float masa;
    bool cvet;
    int n;
    cin>>n;
    VestackoCveke  **cvekinja;
    cvekinja=new VestackoCveke *[n];

    for (int i=0; i<n; i++) {

        cin>>tip>>ime>>cena>>boja;
        if (tip==1) {
            cin>>masa;
            cvekinja[i]=new SoSaksija(ime,cena,boja,masa);

        } else {
            cin>>cvet;
            cvekinja[i]=new BezSaksija(ime,cena,boja,cvet);
        }


    }

    SoSaksija novo("ljubicici",45,"crvena",10.5);
    pecatiMinCena(cvekinja,n,novo);

    for (int i=0; i<n; i++) delete cvekinja[i];
    delete [] cvekinja;
    return 0;
}
