/*Транспорт Problem 1 (8 / 127)
Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)*/
#include <iostream>
#include <cstring>

using namespace std;

class Transport{
protected:
	char destinacija[20];
	int osnovnaCena;
	int rastojanie;
public:
	Transport(){}
	Transport(char destinacija[], int osnovnaCena, int rastojanie){
		strcpy(this->destinacija,destinacija);
		this->osnovnaCena=osnovnaCena;
		this->rastojanie=rastojanie;
	}
	void setDestinacija(char destinacija[]){
		strcpy(this->destinacija,destinacija);
	}
	void setCena(int osnovnaCena){
		this->osnovnaCena=osnovnaCena;
	}
	void setRastojanie(int rastojanie){
		this->rastojanie=rastojanie;
	}
	char *getDestinacija(){
		return destinacija;
	}
	int getCena(){
		return osnovnaCena;
	}
	int getRastojanie(){
		return rastojanie;
	}
	virtual int cenaTransport()=0;
	virtual ~Transport(){}
};
class AvtomobilTransport:public Transport{
private:
	bool shofer;
public:
	AvtomobilTransport(){shofer=false;}
	AvtomobilTransport(char destinacija[], int osnovnaCena, int rastojanie, bool shofer):Transport(destinacija, osnovnaCena, rastojanie){
		this->shofer=shofer;
	}
	int cenaTransport(){
		if(shofer==true){
			return (osnovnaCena)+osnovnaCena*0.20;
		}
		return osnovnaCena;
	}
	~AvtomobilTransport(){}
};
class KombeTransport:public Transport{
private:
	int lugje;
public:
	KombeTransport(){}
	KombeTransport(char destinacija[], int osnovnaCena, int rastojanie, int lugje):Transport(destinacija, osnovnaCena, rastojanie){
		this->lugje=lugje;
	}
	int cenaTransport(){
		return osnovnaCena-lugje*200;
	}
	~KombeTransport(){}
};
bool operator <(Transport &tr, Transport &s){
	return tr.getRastojanie()<s.getRastojanie();

}
void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &T){
	Transport *temp;
	for(int i=0;i<n-1;i++){
        for(int j=i;j<n;j++){
		if(ponudi[i]->getRastojanie()>ponudi[j]->getRastojanie()){
			temp=ponudi[j];
			ponudi[j]=ponudi[i];
			ponudi[i]=temp;
		}
        }
	}
	for(int i=0;i<n;i++){
		if(T.cenaTransport()<ponudi[i]->cenaTransport()){
			cout<<ponudi[i]->getDestinacija()<<" "<<ponudi[i]->getRastojanie()<<" "<<ponudi[i]->cenaTransport()<<endl;
		}
	}
}
/*
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)

*/
int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
