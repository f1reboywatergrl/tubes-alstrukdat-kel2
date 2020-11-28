/*Samuel Gondokusumo / 18219024
  Implementasi ListLinier Linier
  24 October 2020
*/
#include "listlinier.h"
#include "stdlib.h"
#include "stdio.h"

/* PROTOTYPE */
/****************** TEST LISTLinier KOSONG ******************/
boolean IsEmpty (ListLinier L)
/* Mengirim true jika listLinier kosong */
{
    return (First(L)==Nil);
}

/****************** PEMBUATAN LISTLinier KOSONG ******************/
void CreateEmpty (ListLinier *L)
/* I.S. sembarang             */
/* F.S. Terbentuk listLinier kosong */
{
    First(*L)=Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotypeLinier X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    ElmtListLinier *L;
    L=(ElmtListLinier*)malloc(sizeof(infotypeLinier));
    if (L!=Nil){
        InfoLinier(L)=X;
        NextLinier(L)=Nil;
        return L;
    }
    else{
        return Nil;
    }
}
void Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LISTLinier ******************/
address Search (ListLinier L, infotypeLinier X)
/* Mencari apakah ada elemen listLinier dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    address C;
    C=Nil;
    boolean cek=false;
    if(!IsEmpty(L)){
        C=First(L);
        while(cek==false && C!=Nil){
            if(InfoLinier(C)==X){
                cek=true;
            }
            else{
                C=NextLinier(C);                
            }
        }
    }
    return C;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (ListLinier *L, infotypeLinier X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    address C;
    C=Alokasi(X);
    if(C!=Nil){
        InsertFirstLinier(L,C);
    }
}
void InsVLast (ListLinier *L, infotypeLinier X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen listLinier di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address C;
    C=Alokasi(X);
    if(C!=Nil){
        InsertLastLinier(L,C);
    }
}
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (ListLinier *L, infotypeLinier *X)
/* I.S. ListLinier L tidak kosong  */
/* F.S. Elemen pertama listLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    address P;
    DelFirst(L,&P);    
    (*X)=InfoLinier(P);
    Dealokasi(&P);
}
void DelVLast (ListLinier *L, infotypeLinier *X)
/* I.S. listLinier tidak kosong */
/* F.S. Elemen terakhir listLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    address P;
    DelLast(L,&P);
    (*X)=InfoLinier(P);
    Dealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstLinier (ListLinier *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    NextLinier(P)=First(*L);
    First(*L)=P;
}
void InsertAfterLinier (ListLinier *L, address P, address Prec)
/* I.S. Prec pastilah elemen listLinier dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{    
    NextLinier(P)=NextLinier(Prec);
    NextLinier(Prec)=P;
}
void InsertLastLinier (ListLinier *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if(IsEmpty(*L)){
        InsertFirstLinier(L,P);        
    }
    else{
        address C;
        C=(First(*L));
        while(NextLinier(C)!=Nil){
            C=NextLinier(C);
        }    
        InsertAfterLinier(L,P,C);       
    }

}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (ListLinier *L, address *P)
/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen pertama listLinier sebelum penghapusan */
/*      Elemen listLinier berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    address temp;
    (*P)=First(*L);
    if(NbElmt(*L)==1){
        CreateEmpty(L);
    }
    else{
        temp=NextLinier(First(*L));
        First(*L)=temp;        
    }        
}
void DelP (ListLinier *L, infotypeLinier X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen listLinier beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari listLinier dan di-dealokasi */
/* Jika tidak ada elemen listLinier dengan info(P)=X, maka listLinier tetap */
/* ListLinier mungkin menjadi kosong karena penghapusan */
{
    address P,Pdel,Prec,Lokasi;
    P=First(*L);
    Lokasi=Search(*L,X);
    if(Lokasi!=Nil){
        if(P==Lokasi){
            DelFirst(L,&Lokasi);
            Dealokasi(&Lokasi);
        }
        else{
            while(NextLinier(P)!=Lokasi){
                P=NextLinier(P);
            }
            DelAfter(L,&Pdel,P);
            Dealokasi(&Pdel);             
        }
      
    }

}
void DelLast (ListLinier *L, address *P)
/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen terakhir listLinier sebelum penghapusan  */
/*      Elemen listLinier berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
    address Plast,Prec;
    Plast=First(*L);
    Prec=Nil;    
    if(NbElmt(*L)==1){
        (*P)=First(*L);
        CreateEmpty(L);
    }
    else{
        while(NextLinier(Plast)!=Nil){
            Prec=Plast;
            Plast=NextLinier(Plast);
        }   
        DelAfter(L,P,Prec);        
    }

}
void DelAfter (ListLinier *L, address *Pdel, address Prec)
/* I.S. ListLinier tidak kosong. Prec adalah anggota listLinier  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen listLinier yang dihapus  */
{
    address Gabung;
    Gabung = NextLinier(NextLinier(Prec));
    (*Pdel)=NextLinier(Prec);
    if(*Pdel!=Nil){
        NextLinier(Prec)=Gabung;        
    }

}

void PrintInfo (ListLinier L)
/* I.S. ListLinier mungkin kosong */
/* F.S. Jika listLinier tidak kosong, iai listLinier dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika listLinier kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    address P;
    if(IsEmpty(L)){
        printf("[]");
    }
    else{
        P=First(L);
        printf("[");
        printf("%d",InfoLinier(P));
        P=NextLinier(P);
        while(P!=Nil){
            printf(",%d",InfoLinier(P));
            P=NextLinier(P);
        }
        printf("]");
    }

}
int NbElmt (ListLinier L)
/* Mengirimkan banyaknya elemen listLinier; mengirimkan 0 jika listLinier kosong */
{
    int C;
    address P;
    C=0;
    P=First(L);
    while(P!=Nil){
        P=NextLinier(P);
        C++;
    }
    return C;
}
/*** Prekondisi untuk Max/Min/rata-rata : ListLinier tidak kosong ***/
infotypeLinier Max (ListLinier L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
    infotypeLinier Gede;
    address P;
    P=First(L);
    Gede=InfoLinier(P);
    while(P!=Nil){
        if(InfoLinier(P)>Gede){
            Gede=InfoLinier(P);
        }
        P=NextLinier(P);
    }
    return Gede;
}
/****************** PROSES TERHADAP LISTLinier ******************/
void Konkat1 (ListLinier *L1, ListLinier *L2, ListLinier *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah listLinier : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen listLinier L1 dan L2) */
/* dan L1 serta L2 menjadi listLinier kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    address P;
    CreateEmpty(L3);
    if(!IsEmpty(*L1)){
        First(*L3)=First(*L1);
        P=First(*L3);
        while(NextLinier(P)!=Nil){
            P=NextLinier(P);
        }
        NextLinier(P)=First(*L2);
    }
    else{
        First(*L3)=First(*L2);
    }
    CreateEmpty(L1);
    CreateEmpty(L2);

}

address AdrMax (ListLinier L)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
    address P;
    P=First(L);
    address adr;
    adr=First(L);
    while(P!=Nil){
        if(InfoLinier(P)>InfoLinier(adr)){
            adr=P;
        }
        P=NextLinier(P);
    }
    return adr;
}
infotypeLinier Min (ListLinier L)
/* Mengirimkan nilai info(P) yang minimum */
{
    return InfoLinier(AdrMin(L));
}
address AdrMin (ListLinier L)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
    address P,adr;
    P=First(L);
    adr=First(L);
    while(P!=Nil){
        if(InfoLinier(adr)>InfoLinier(P)){
            adr=P;
        }
        P=NextLinier(P);
    }
    return adr;
}
float Average (ListLinier L)
/* Mengirimkan nilai rata-rata info(P) */
{
    int C;
    float avg,sum;
    C=0;
    sum=0;
    address P;
    P=First(L);
    while(P!=Nil){
        sum=sum+InfoLinier(P);        
        C++;
        P=NextLinier(P);
    }
    avg=sum/C;
    return avg;
}

/****************** PROSES TERHADAP LISTLinier ******************/

void InversListLinier (ListLinier *L)
/* I.S. sembarang. */
/* F.S. elemen listLinier dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen listLinier, tanpa melakukan alokasi/dealokasi. */
{
    address P;
    P=First(*L);
    while(NextLinier(P)!=Nil){
        P=NextLinier(P);
    }
    infotypeLinier temp=InfoLinier(P);
    while(InfoLinier(First(*L))!=temp){
        address X;
        DelFirst(L,&X);
        InsertAfterLinier(L,X,P);
    }
}