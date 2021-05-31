#include <iostream>
#include <fstream>

using namespace std;

struct node{
    string plaka;
    int ucret;
    string aracTipi;
    node *prev;
    node *next;
    };

struct node *head=NULL;

void ekle(string plaka, string aracTipi, int ucret){
    system("cls");
    struct node* arac= new node();
    arac->plaka = plaka;
    arac->aracTipi=aracTipi;
    arac->ucret=ucret;

    if(head==NULL){ //otoparkta arac yoksa
        arac->prev=NULL;
        arac->next=NULL;
        head=arac;
        cout << plaka << " plakali ilk arac otoparka alindi!" << endl;}

    else{
        arac->next=head; //her gelen arac basa eklenir
        head->prev=arac;
        head=arac;
        head->prev=NULL;
        cout << plaka << " plakali arac otoparka alindi!" << endl;}
}

void cikar(string plaka){
    system("cls");
    bool sonuc=false;

    if(head==NULL){
        cout << "Otopark bos!" << endl;
        sonuc=true;
		}

    else{
        if(head->next==NULL && head->plaka==plaka){//otoparkta tek arac varsa
            delete head;
            head=NULL;
            cout << plaka << " plakali ilk ve son arac otoparktan cikartildi!" << endl;
            sonuc=true;}

        else if(head->next!=NULL && head->plaka==plaka){ //bir suru arac icerisinden ilk arac cikartilacaksa
            node* temp= head->next;
            delete head;
            head=temp;
            head->next=temp->next;
            head->prev=NULL;
            sonuc=true;
            cout << plaka << " plakali ilk arac otoparktan cikartildi!" << endl;
        }

        else{ //ortadan bir arac cikartilacaksa
            node * iter= head;
            while(iter!=NULL){   //son araca kadar git
                if(iter->next==NULL && iter->plaka== plaka  ){ //silinecek arac otoparkin sonundaysa
                node* temp= iter->prev;
                temp->next=NULL;
                delete iter;
                cout << plaka << " plakali son arac otoparktan cikartildi!" << endl;
                sonuc=true;}

                else if(iter->plaka== plaka) {
                    node* temp1= iter->prev;
                    node* temp2= iter->next;

                    temp1->next=temp2;
                    temp2->prev=temp1;

                    delete iter;
                    cout << plaka << " plakali arac otoparktan cikartildi!" << endl;
                    sonuc=true;
                }

                iter=iter->next;
            }

	        if(!sonuc)
	            cout << plaka << " plakali arac otoparkta yoktur!" << endl;

 		}
 	}

}

void yazdir(){
    system("cls");
    if(head==NULL){ //otopark bossa
        cout << "Otoparkta arac yoktur!" << endl; }

    else{
        node* iter= head;
        while(iter!=NULL){
            cout << "Arac plakasi: " << iter->plaka << endl;
            cout << "Arac tipi: " << iter->aracTipi << endl;
            cout << "Arac ucreti: " << iter->ucret << endl;
            iter=iter->next;}}
}

void adet(){
    system("cls");
    int adet=0;
    if(head==NULL)
        cout << "Otoparkta arac yoktur!" << endl;
    else{
        node* iter=head;
        while(iter!=NULL){
            adet++;
            iter=iter->next;}
        cout << "Otoparkta bulunan arac sayisi: " << adet << endl;}
}


void ucretToplami(){
    system("cls");
    int toplam=0;
    if(head==NULL)
        cout << "Otoparkta arac yoktur!" << endl;
    else{
        node* iter=head;
        while(iter!=NULL){
            toplam+=iter->ucret;
            iter=iter->next;}
        cout << "Otoparkta bulunan araclarin toplam ucreti: " << toplam << endl;}
}

void dosyayaYaz(){
    system("cls"); //onceki kodlari temizler
    ofstream yaz("Otopark.txt", ios::app);

    if(head==NULL){
        cout << "Otopark bos!" << endl;}
    else{
        node* temp=head;
        while(temp!=NULL){
            yaz << temp->plaka << " " << temp->aracTipi << " " << temp->ucret << endl;
            temp=temp->next;}
        yaz.close();
        cout << "Otoparkta bulunan araclar 'Otopark.txt' dosyasina kaydedildi!" << endl;}
}

void dosyadanOku(){
    system("cls");
    ifstream oku("Otopark.txt");
    string satir= "";
    while(getline(oku,satir)){
        cout << satir << endl;}
    oku.close();
}

int main()
{
    int ucret, secim;
    bool dongu=true;
    string plaka, aracTipi;
    while(dongu){
        cout << "\nOTOPARK UYGULAMASI" << endl;
        cout << "0- Cikis" << endl;
        cout << "1- Arac ekle" << endl;
        cout << "2- Arac cikar" << endl;
        cout << "3- Arac listesi" << endl;
        cout << "4- Arac sayisi" << endl;
        cout << "5- Araclarin toplam ucreti" << endl;
        cout << "6- Araclari dosyaya kaydet" << endl;
        cout << "7- Dosyada kaydindaki araclari getir" << endl;
        cin >> secim;
        switch(secim){
            case 0:
                cout << "Programdan cikis yapiliyor..." << endl;
                dongu=false;
                break;
            case 1:
                cout << "Otoparka alinacak aracin bilgilerini giriniz" << endl;
                cout << "Plaka: "; cin >> plaka;
                cout << "Arac tipi: "; cin >> aracTipi;
                cout << "Ucret: "; cin >> ucret;
                ekle(plaka,aracTipi,ucret);
                break;
            case 2:
                cout << "Otoparktan cikartilacak aracin plakasini giriniz" << endl;
                cout << "Plaka: "; cin >> plaka;
                cikar(plaka);
                break;
            case 3:
                cout << "Arac Listesi:" << endl;
                yazdir();
                break;
            case 4:
                adet();
                break;
            case 5:
                ucretToplami();
                break;
            case 6:
                dosyayaYaz();
                break;
            case 7:
                dosyadanOku();
                break;
            default:
                cout << "Lutfen gecerli bir islem seciniz!" << endl;
                break;}
    }

    return 0;
}
