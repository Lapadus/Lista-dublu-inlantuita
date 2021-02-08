#include<iostream>
#include <stdlib.h>
using namespace std;

class Lista;
class Nod{
private:
    Nod* prev;
    Nod* next;
    int info;
public:
    Nod();
    Nod(Nod*,Nod*,int);
    ~Nod(); //destructor nod

    void setInfo(int info){this->info=info;} //setter pt info
    void setPrev(Nod* prev){this->prev=prev;} //setter pt prev
    void setNext(Nod* next){this->next=next;} //setter pt next
    Nod* getPrev(){return prev;} //getter pt prev
    Nod* getNext(){return next;} //getter pt next
    int getInfo(){return info;} //getter pt info

    void citire(istream& in); //functia de citire
    friend istream& operator>>(istream& in, Nod& n); //supraincarcarea op de citire >>

    void afisare(ostream& out); //functia de afisare
    friend ostream& operator<<(ostream& out, Nod& n); //supraincarcarea op de afisare <<

    friend class Lista;
};
Nod::Nod(){
    this->info=0;
    this->prev=NULL;
    this->next=NULL;
}
Nod::Nod(Nod* prev,Nod* next,int info){
    this->info=info;
    this->prev=prev;
    this->next=next;
    prev->next=this;
    next->prev=this;
}
Nod::~Nod(){
    info=0;
    if(prev!=NULL) //Daca nodul meu nu e primul nod din lista
    {
        if(next!=NULL) //Daca nodul meu nu e ultimul(adica e in mijl)
        {
            prev->next=next;
            next->prev=prev;
        }
        else //Nodul meu e ultimul din lista
        {
            prev->next=NULL;
        }
    }
    else //Nodul meu e primul nod din lista
    {
       prev->next=NULL;
    }
    prev=NULL;
    next=NULL;
}
void Nod::citire(istream& in){
    cout<<"Introduceti info: ";
    in>>info;
}
istream& operator>>(istream& in,Nod& n){
    n.citire(in);
    return in;
}
void Nod::afisare(ostream& out){
    out<<"Info introdusa este: "<<info<<endl;
}
ostream& operator<<(ostream& out, Nod& n){
    n.afisare(out);
    return out;
}

class Lista{
private:
    Nod* prim;
    Nod* ultim;
public:
    Lista();
    Lista(Nod*,Nod*);
    ~Lista(); //destructor lista

    void setPrim(Nod* prim){this->prim=prim;} //setter prim
    Nod* getPrim(){return prim;} //getter prim

    void setUltim(Nod* ultim){this->ultim=ultim;} //setter ultim
    Nod* getUltim(){return ultim;} //getter ultim

    void adaugare(int info,int poz); //metoda publica de adaugare a unui nod pe o anumita pozitie

    void stergere(int);  //metoda publica stergere a unui nod pe o anumita pozitie

    Lista& operator+(Lista& obj2); //concatenarea a doua liste dublu inlantuite

    void citire(istream& in); //metoda publica de citire a unei liste
    friend istream& operator>>(istream& in, Lista& l); //supraincarcarea operatorului de citire >>

    void afisare(ostream& out);  //metoda publica de afisare a unei liste
    friend ostream& operator<<(ostream& out, Lista& l);  //supraincarcarea operatorului de afisare <<

};
Lista::Lista(){
    this->prim=NULL;
    this->ultim=NULL;
}
Lista::Lista(Nod* prim, Nod* ultim){
    this->prim=prim;
    this->ultim=ultim;
}
Lista::~Lista(){
   Nod* curr=prim; //curr este primul nod
   while(curr!=NULL) //cat timp nu am ajuns la finalul listei
   {
       Nod* aux=curr; //copiem nodul curent intr-un nod auxiliar care urmeaza sa fie distrus
       curr->prev=NULL; //rupem legaturile
       aux->next=NULL; //rupem legaturile
       delete aux; //stergem nodul
       prim=curr;
   }
   prim=NULL;
   ultim=NULL;
}
void Lista::adaugare(int info,int poz){
     int i;
     Nod* nodnou=new Nod; //nodul pe care il vom adauga
     Nod* curr=new Nod; //curr este nodul curent cu care parcurgem lista
         if(prim==NULL) //daca lista e goala noul nodul nou adaugat va fi si primul si ultim nod al listei
        {
            nodnou->info=info;
            prim=ultim=nodnou;
            prim->prev=NULL;
            ultim->next=NULL;
        }
     else
    {
         curr=prim; //actualizam nodul curent cu primul nod pentru a parcurge lista
         i=1;
         while(i<poz-1 and curr!=NULL)
         {
             curr=curr->next; //parcurgem lista pana ajungem la pozitia pe care vrem sa adaugam noul nod
             i++;
         }
        if(poz==1)
         {
             nodnou->info=info;
             nodnou->next=prim;
             nodnou->prev=NULL;
             prim->prev=nodnou;
             prim=nodnou;
         }
         else if(curr==ultim) //daca vrem sa adaugam la finalul listei
         {
             nodnou->info=info;
             nodnou->next=NULL;
             nodnou->prev=ultim;
             ultim->next=nodnou;
             ultim=nodnou;
         }
         else if(curr!=NULL) //daca vrem sa adaugam pe o anumita poz care nu e nici ultima si nici prima
         {
             nodnou->info=info;
             nodnou->next=curr->next;
             nodnou->prev=curr;
             curr->next->prev=nodnou;
             curr->next=nodnou;
         }
     }
}
void Lista::stergere(int poz){
    Nod* sters; //nodul pe care il vrem sters
    if(poz==1) //daca pozitia de pe care vrem sa stergem este 1 atunci primul elem va fi cel sters
    {
        sters=prim;
        prim=prim->next;
        delete sters;
        return;
    }
    Nod* curr=prim->next; //mergem la urm nod
    int k=2;
    while(curr!=NULL) //cat timp nu am ajuns la final
    {
        if(poz==k and curr->next!=NULL) //daca am gasit pozitia de pe care vrem sa stergem nodul iar acesta nu este ultimul nod al listei
        {
            sters=curr;
            curr->prev->next=curr->next;
            curr->next->prev=curr->prev;
            delete sters;
            return;
        }
        else if(poz==k and curr->next==NULL) //daca am gasit pozitia de pe care vrem sa stergem nodul iar acesta este ultimul nod al listei
        {
            sters=curr;
            curr->prev->next=NULL;
            ultim=curr->prev;
            delete sters;
            return;
        }
        k++; //trecem mai departe la urm pozitie
        curr=curr->next; //avansam cu parcurgerea listei
    }
    return;
}
Lista& Lista::operator+(Lista& obj2){

    Lista rez; //noua lista ce va rezulta dupa concatenarea celor doua liste
    int p=1; //pozitiile pe care vor fi adaugate nodurile
    Nod* curr=this->prim; //nodul curent retine adresa primului nod al primei liste de concatenat
    while(curr!=NULL) //cat timp nu am terminat de parcurs prima lista
    {
        rez.adaugare(curr->info,p); //adaugam fiecare nod la lista rez
        curr=curr->next;
        p++;
    }
    //dupa ce am terminat de pus elementele primei liste in noua lisra rez, facem acelasi lucru si pt a doua lista
    curr=obj2.prim; //actualizam nodul curent cu primul elem al celei de-a doua liste de concatenat
    while(curr!=NULL)
    {
        rez.adaugare(curr->info,p);
        curr=curr->next;
        p++;
    }
    cout<<rez; //afisam lista rezultata
    return rez;
}
void Lista::citire(istream& in){
    int n,info;
    cout<<"Introduceti nr de elem al listei: ";
    in>>n;
    cout<<"Enumarati elem listei: ";
    for(int i=1;i<=n;i++)
    {
        Nod* nodnou=new Nod;
        in>>info;
        adaugare(info,i);
    }
}
istream& operator>>(istream& in, Lista& l){
    l.citire(in);
    return in;
}
void Lista::afisare(ostream& out){
    Nod* curr=prim;
    out<<"Lista afisata in mod normal este: ";
    while(curr!=NULL)
    {
        out<<curr->info<<" ";
        curr=curr->next;
    }
    out<<endl;
    curr=ultim;
    out<<"Lista afisata in mod invers este: ";
    while(curr!=NULL)
    {
        out<<curr->info<<" ";
        curr=curr->prev;
    }
}
ostream& operator<<(ostream& out, Lista& l){
    l.afisare(out);
    return out;
}
///Mentionez ca meniul a fost luat din cadrul laboratorului de POO.
void menu_output(){
    cout<<"\n Lapadus Raluca 254 - Proiect 7 - Nume proiect: Lista_dublu_inlantuita \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citim n obiecte: "; cout<<"\n";
    cout<<"2. Afisam cele n obiecte: "; cout<<"\n";
    cout<<"3. Stergem un nod al listei: "; cout<<"\n";
    cout<<"4. Adaugam un nod pe pozitia:"; cout<<"\n";
    cout<<"5. Concatenam listele: "; cout<<"\n";
    cout<<"0. Iesire."; cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int n=0,x,k,info,poz,p;
    Lista *L;

    do
    {
        menu_output();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if (option==1)
        {
            cout<<"Introduceti nr de liste: ";
            cin>>n;
            L = new Lista[n];
            for (int i=0; i<n; i++)
                cin>>L[i];
        }
        if (option==2)
        {
             for (int i=0;i<n;i++)
            {
                cout<<L[i]<<endl;
            }
        }
        if (option==3)
        {
            cout<<"Introduceti pozitia de pe care vreti sa fie sters nodul: ";
            cin>>x;
            cout<<"Alegeti lista din care vreti sa stergeti: ";
            cin>>k;
            L[k].stergere(x);
                cout<<L[k]<<endl;
        }
        if (option==4)
        {
           cout<<"Introduceti info pe care vreti sa o adaugati: ";
            cin>>info;
            cout<<"Introduceti pozitia pe care vreti sa adaugati: ";
            cin>>poz;
            cout<<"Alegeti lista in care vreti sa adaugati: ";
            cin>>k;
            L[k].adaugare(info,poz);
                cout<<L[k]<<endl;
        }
        if (option==5)
        {
            cout<<"Alegeti una din liste pentru concatenare: ";
            cin>>k;
            cout<<"Alegeti si a doua lista pentru concatenare: ";
            cin>>p;
            cout<<"Concatenarea: "<<endl;
            cout<<L[k]+L[p];
        }
        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }
        if (option<0||option>5)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause");
        system("cls");
    }
    while(option!=0);
}
int main()
{
	menu();
	return 0;
}
