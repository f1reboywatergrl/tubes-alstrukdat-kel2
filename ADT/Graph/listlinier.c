/*Samuel Gondokusumo / 18219024
  Implementasi List Linier
  24 October 2020
*/
#include "listlinier.h"
#include "stdlib.h"
#include "stdio.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong */
{
    return (First(L)==Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    First(*L)=Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    ElmtList *L;
    L=(ElmtList*)malloc(sizeof(infotype));
    if (L!=Nil){
        Info(L)=X;
        Next(L)=Nil;
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

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    address C;
    C=Nil;
    boolean cek=false;
    if(!IsEmpty(L)){
        C=First(L);
        while(cek==false && C!=Nil){
            if(Info(C)==X){
                cek=true;
            }
            else{
                C=Next(C);                
            }
        }
    }
    return C;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    address C;
    C=Alokasi(X);
    if(C!=Nil){
        InsertFirst(L,C);
    }
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address C;
    C=Alokasi(X);
    if(C!=Nil){
        InsertLast(L,C);
    }
}
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    address P;
    DelFirst(L,&P);    
    (*X)=Info(P);
    Dealokasi(&P);
}
void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    address P;
    DelLast(L,&P);
    (*X)=Info(P);
    Dealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    Next(P)=First(*L);
    First(*L)=P;
}
void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{    
    Next(P)=Next(Prec);
    Next(Prec)=P;
}
void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if(IsEmpty(*L)){
        InsertFirst(L,P);        
    }
    else{
        address C;
        C=(First(*L));
        while(Next(C)!=Nil){
            C=Next(C);
        }    
        InsertAfter(L,P,C);       
    }

}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    address temp;
    (*P)=First(*L);
    if(NbElmt(*L)==1){
        CreateEmpty(L);
    }
    else{
        temp=Next(First(*L));
        First(*L)=temp;        
    }        
}
void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
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
            while(Next(P)!=Lokasi){
                P=Next(P);
            }
            DelAfter(L,&Pdel,P);
            Dealokasi(&Pdel);             
        }
      
    }

}
void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
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
        while(Next(Plast)!=Nil){
            Prec=Plast;
            Plast=Next(Plast);
        }   
        DelAfter(L,P,Prec);        
    }

}
void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    address Gabung;
    Gabung = Next(Next(Prec));
    (*Pdel)=Next(Prec);
    if(*Pdel!=Nil){
        Next(Prec)=Gabung;        
    }

}

void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    address P;
    if(IsEmpty(L)){
        printf("[]");
    }
    else{
        P=First(L);
        printf("[");
        printf("%d",Info(P));
        P=Next(P);
        while(P!=Nil){
            printf(",%d",Info(P));
            P=Next(P);
        }
        printf("]");
    }

}
int NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int C;
    address P;
    C=0;
    P=First(L);
    while(P!=Nil){
        P=Next(P);
        C++;
    }
    return C;
}
/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
    infotype Gede;
    address P;
    P=First(L);
    Gede=Info(P);
    while(P!=Nil){
        if(Info(P)>Gede){
            Gede=Info(P);
        }
        P=Next(P);
    }
    return Gede;
}
/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    address P;
    CreateEmpty(L3);
    if(!IsEmpty(*L1)){
        First(*L3)=First(*L1);
        P=First(*L3);
        while(Next(P)!=Nil){
            P=Next(P);
        }
        Next(P)=First(*L2);
    }
    else{
        First(*L3)=First(*L2);
    }
    CreateEmpty(L1);
    CreateEmpty(L2);

}

address AdrMax (List L)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
    address P;
    P=First(L);
    address adr;
    adr=First(L);
    while(P!=Nil){
        if(Info(P)>Info(adr)){
            adr=P;
        }
        P=Next(P);
    }
    return adr;
}
infotype Min (List L)
/* Mengirimkan nilai info(P) yang minimum */
{
    return Info(AdrMin(L));
}
address AdrMin (List L)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
    address P,adr;
    P=First(L);
    adr=First(L);
    while(P!=Nil){
        if(Info(adr)>Info(P)){
            adr=P;
        }
        P=Next(P);
    }
    return adr;
}
float Average (List L)
/* Mengirimkan nilai rata-rata info(P) */
{
    int C;
    float avg,sum;
    C=0;
    sum=0;
    address P;
    P=First(L);
    while(P!=Nil){
        sum=sum+Info(P);        
        C++;
        P=Next(P);
    }
    avg=sum/C;
    return avg;
}

/****************** PROSES TERHADAP LIST ******************/

void InversList (List *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
    address P;
    P=First(*L);
    while(Next(P)!=Nil){
        P=Next(P);
    }
    infotype temp=Info(P);
    while(Info(First(*L))!=temp){
        address X;
        DelFirst(L,&X);
        InsertAfter(L,X,P);
    }
}