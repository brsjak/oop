/*Саксиско Цвеќе Problem 1 (23 / 65)
Да се имплементира апстрактна класа за репрезентација на саксиско цвеќе. За секое саксиско цвеќе се чуваат податоци за неговото име (низа од знаци), основна цена (цел број) и фамилија на која припаѓа (низа од знаци).

Од класата SaksiskoCvekje да се изведат класите BezCvet и SoCvet. За секое цвеќе со цвет се чува колку расцветани цветови има (цел број), а за цвеќето без цвет се чува податок за тоа колку дена е старо (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод presmetajCena, за пресметување на цената на цвеќето на следниот начин:

За BezCvet - основната цена се зголемува за 20 ако не е постаро од 10дена, а за 10 ако не е постаро од 35 дена.

За SoCvet - основната цена се зголемува за бројот на расцветани цветови (10 поени)

преоптоварен оператор == за споредба на две саксиски цвеќиња. Две цвеќиња се исти ако се од иста фамлија. (5 поени)

Да се имплементира функција pecatiMaxCena што на влез прима низа од саксиски цвеќиња, бројот на елементите од низата и едно саксиско цвеќе C. Функцијата го печати името, фамилија и цена на најскапото цвеќе од цвеќињата од низата кои се од иста фамилија со цвеќето C (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)*/

#include <iostream>
#include <cstring>

using namespace std;

class SaksiskoCvekje{
protected:
	char ime[10];
	int osnovnaCena;
	char familija[10];
public:
	SaksiskoCvekje(){}
	SaksiskoCvekje(char ime[], int osnovnaCena, char familija[]){
		strcpy(this->ime,ime);
		this->osnovnaCena=osnovnaCena;
		strcpy(this->familija,familija);
	}
	void setIme(char ime[]){
		strcpy(this->ime,ime);
	}
	void setCena(int osnovnaCena){
		this->osnovnaCena=osnovnaCena;
	}
	void setFamilija(char familija[]){
		strcpy(this->familija,familija);
	}
	char *getIme(){
		return ime;
	}
	int getCena(){
		return osnovnaCena;
	}
	char *getFamilija(){
		return familija;
	}
	virtual int presmetajCena()=0;
	virtual ~SaksiskoCvekje(){}
};

class BezCvet:public SaksiskoCvekje{
private:
	int starost;
public:
	BezCvet(){}
	BezCvet(char ime[], int osnovnaCena, char familija[], int starost):SaksiskoCvekje(ime,osnovnaCena,familija){
		this->starost=starost;
	}
	int presmetajCena(){
		if(starost<=10){
			return osnovnaCena+20;
		}
		else{
			if(starost<=35){
				return osnovnaCena+10;
			}
		}
		return osnovnaCena;
	}
	~BezCvet(){}
};
class SoCvet:public SaksiskoCvekje{
private:
	int rascvetani;
public:
	SoCvet(){}
	SoCvet(char ime[], int osnovnaCena, char familija[], int rascvetani):SaksiskoCvekje(ime,osnovnaCena,familija){
		this->rascvetani=rascvetani;
	}
	int presmetajCena(){
		return osnovnaCena+rascvetani;
	}
	~SoCvet(){}
};
bool operator==(SaksiskoCvekje &sc, SaksiskoCvekje &s){
    if(strcmp(sc.getFamilija(),s.getFamilija())==0){
    	return true;
    }
    return false;
}
void pecatiMaxCena(SaksiskoCvekje **cvekinja, int n, SaksiskoCvekje &C){
	int maxI, maxCena=0;
	for(int i=0;i<n;i++){
		if(*cvekinja[i]==C){
			if(cvekinja[i]->presmetajCena()>maxCena){
				maxCena=cvekinja[i]->presmetajCena();
				maxI=i;
			}
		}
	}
	cout<<cvekinja[maxI]->getIme()<<" "<<cvekinja[maxI]->getFamilija()<<" "<<maxCena<<endl;
}

int main(){

char ime[10],familija[10];
int tip,starost,broj,cena;
int n;
cin>>n;
SaksiskoCvekje **cvekinja;
cvekinja=new SaksiskoCvekje*[n];

for (int i=0;i<n;i++){

    cin>>tip>>ime>>cena>>familija;
    if (tip==1) {
        cin>>starost;
        cvekinja[i]=new BezCvet(ime,cena,familija,starost);

    }
    else {
        cin>>broj;
        cvekinja[i]=new SoCvet(ime,cena,familija,broj);
    }


}

BezCvet nov("opuntia",90,"cactus",10);
pecatiMaxCena(cvekinja,n,nov);

for (int i=0;i<n;i++) delete cvekinja[i];
delete [] cvekinja;
return 0;
}
