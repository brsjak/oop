/*Курс Problem 2 (11 / 11)
Дадена е дел од дефиниција на класата UcesnikKurs. За секој учесник се чуваат информации за неговото име (низа од максимум 10 знаци), број на освоени поени на финалниот испит (цел број) и дали на учесникот ќе сака да изработува дополнителни активности (булова променлива).

Максималниот број на поени кои еден учесник може да освои е 100 поени. Самиот финален испит исто носи максимум 100 поени. Кај оние учесници кои сакаат да изработуваат дополнителни активности се оценуваат така што 20% од освоените поени на курсот се од дополнителните активности, а 80% се поените од финалниот испит. За поените секогаш се зема целиот дел. На пример ако на финалниот испит некој учесник има 97 поени и има една активност оценета со 3 поени, тогаш тој ќе освои 77+3=80 поени.

Имплементирај соодветна класа UcesnikKursDopolnitelen во која се чуваат дополнителни информации за бројот на дополнителни активност на учесникот на курсот (цел број) и поени за секоја дополнителна активност (динамичко алоцирана низа од цели броеви).

Секој учесник може да има изработено најмногу M дополнителни активности. M има фиксна вредност 5 која не може да се промени. Секоја дополнителна активност носи по 4 поени (Со ова еден учесник може да освои најмногу 20 поени со дополнителните активности)

Во класите UcesnikKurs и UcesnikKursDopolnitelno треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << - во кој се печатат информации за учесник на курсот во формат: Ime - OsvoeniPoeni (5 поени)
osvoeniPoeni() – го пресметува бројот на освоени поени на курсот (5 поени)
Во класата UcesnikKursDopolnitelno дефинирај ја функцијата:

преоптоварен оператор += за додавање на поени од една дополнителна активност (5 поени)
Ако се направи обид да се внесат поени за повеќе од дозволениот број на дополнителни активности M да се фрли исклучок (објект од класата IndexOutOfBoundException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Ne moze da se vnesat uste dopolnitelni aktivnosti) и справете се со исклучокот така што новите поени нема да се додадат за учесникот.(10 поени)

Дадена е дел од дефиницијата на класата Kurs во која се чуваат информаци за името на курсот (низа од 30 знаци) и за учесниците на курсот (низа од 10 покажувачи кон класата UcesnikKurs) како и бројот на учесници на курсот.

Учесник на еден курс ќе го положи курсот ако има освоено барем Pод поените. Вредноста P е членка на класата Kurs има почетна вредност 50 и истата може да се промени со функцијата setP(). За сите учесници на курсеви минималниот број поени за положување мора да е иста. (5 поени)

Во класата Kurs имплементирај ги функциите:

функција pecatiUcesnici() во која се печатат сите положени учесници на курсот, секој во посебен ред. Претходно во првиот ред се печати: _Na kursot XXXXX polozeni se:_ (5 поени).

функција dodadiPoeniDopolnitelnaAktivnost(char * ime, int poeniAktivnost) во која на учесникот на курсот со даденото име му се додават поени за нова активност. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)*/

#include <iostream>
#include <string.h>
using namespace std;
class IndexOutOfBoundException{};
class UcesnikKurs{
   protected:
       char ime[30];
       int finalenIspit;
       bool dopolnitelna;
       const static int M;
   public:
    UcesnikKurs(){
    	this->dopolnitelna=false;
    }
    UcesnikKurs(char* ime,int finalenIspit){
       strcpy(this->ime,ime);
       this->finalenIspit=finalenIspit;
       this->dopolnitelna=false;
     }
    bool getDopolnitelna(){
    	return dopolnitelna;
    }
    char *getIme(){
    	return ime;
    }
     virtual int osvoeniPoeni(){
      return finalenIspit;
     }
     friend ostream& operator<<(ostream &out, UcesnikKurs &k){
      out<<k.ime<<" - "<<k.osvoeniPoeni()<<endl;
      return out;
     }
    virtual ~UcesnikKurs(){}
};
const int UcesnikKurs::M=5;


class UcesnikKursDopolnitelen : public UcesnikKurs{
private:
  int aktivnosti;
  int *poeni;
public:
  UcesnikKursDopolnitelen(): UcesnikKurs(){
    this->aktivnosti=0;
    poeni=new int[aktivnosti];
    this->dopolnitelna=true;
  }
  UcesnikKursDopolnitelen(char *ime, int finalenIspit):UcesnikKurs(ime,finalenIspit){
    this->aktivnosti=0;
    poeni=new int[aktivnosti];
    this->dopolnitelna=true;
  }
  int osvoeniPoeni(){
    int vkupno=finalenIspit*80/100;
    for(int i=0;i<aktivnosti;i++){
      vkupno+=poeni[i];
    }
    return vkupno;
  }
  //proverka dali dve referenci pokazuvaat kon ist objekt?
  UcesnikKursDopolnitelen& operator=(UcesnikKursDopolnitelen &uk){
    if(&uk!=this){
      strcpy(ime,uk.ime);
      finalenIspit=uk.finalenIspit;
      delete [] poeni;
      aktivnosti=uk.aktivnosti;
      for(int i=0;i<aktivnosti;i++){
        poeni[i]=uk.poeni[i];
      }
      dopolnitelna=uk.dopolnitelna;
    }
    return *this;
  }
  UcesnikKursDopolnitelen& operator+=(int poen){
    if(aktivnosti==M){
      throw(IndexOutOfBoundException());
    }
    int *tmp=new int[aktivnosti+1];
    for(int i=0;i<aktivnosti;i++){
      tmp[i]=poeni[i];
    }
    tmp[aktivnosti++]=poen;
    delete [] poeni;
    poeni=tmp;
    return *this;
  }
    ~UcesnikKursDopolnitelen(){
    	//delete [] poeni;
    }
};

class Kurs{
private:
    char naziv[30];
    UcesnikKurs *ucesnici[10];
    int broj;
    static int P;
public:
    Kurs(char *naziv, UcesnikKurs** ucesnici,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako ucesnikot ima dopolnitelni aktivnosti
        if (ucesnici[i]->getDopolnitelna()){
            this->ucesnici[i]=new UcesnikKursDopolnitelen(*dynamic_cast<UcesnikKursDopolnitelen*>(ucesnici[i]));
        }
        else this->ucesnici[i]=new UcesnikKurs(*ucesnici[i]);
      }
      this->broj=broj;
    }
    static void setP(int p){
      P=p;
    }
    void pecatiUcesnici(){
      cout<<"Na kursot "<<naziv<<" polozeni se:"<<endl;
      for(int i=0;i<broj;i++){
        if(ucesnici[i]->osvoeniPoeni()>=P){
          cout<<*ucesnici[i];
        }
      }
    }
    void dodadiPoeniDopolnitelnaAktivnost(char *ime, int poeniAktivnost){
      for(int i=0;i<broj;i++){
        /*proverka dali ucesnikot e so dopolnitelna aktivnost, bidejki ne mozat da se dodadat poeni
        na ucesnik koj nema dopolnitelna aktivnost. Isto taka ne moze da se dodade dopolnitelna aktivnost na obicen ucesnik bidejki += ni e preoptovaren SAMO vo UcesnikKursDopolnitelen*/
        if(strcmp(ucesnici[i]->getIme(),ime)==0){
          UcesnikKursDopolnitelen *s= dynamic_cast<UcesnikKursDopolnitelen*>(ucesnici[i]);
          if(s!=0){
            *s+=poeniAktivnost;
          }
        }
      }
    }
    ~Kurs(){
    for (int i=0;i<broj;i++) delete ucesnici[i];
    }

    //дополни ја класата
};

int Kurs::P=50;

int main(){

UcesnikKurs **niza;
int n,m,poeni;
char ime[10];
bool daliDopolnitelnaAktivnost;
cin>>n;
niza=new UcesnikKurs*[n];
for (int i=0;i<n;i++){
   cin>>ime;
   cin>>poeni;
   cin>>daliDopolnitelnaAktivnost;
   if (!daliDopolnitelnaAktivnost)
    niza[i]=new UcesnikKurs(ime,poeni);
   else
    niza[i]=new UcesnikKursDopolnitelen(ime,poeni);
}

Kurs programiranje("Programiranje",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;

cin>>m;
for (int i=0;i<m;i++){
   cin>>ime>>poeni;
   try{
    programiranje.dodadiPoeniDopolnitelnaAktivnost(ime,poeni);
   }
   catch(IndexOutOfBoundException){
    cout<<"Ne moze da se vnesat uste dopolnitelni aktivnosti"<<endl;
   }
}

Kurs::setP(60);

programiranje.pecatiUcesnici();

}
