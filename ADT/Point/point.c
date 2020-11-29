/* File: point.c */
/* Tanggal: 17 September 2020 */
/* *** Implementasi ABSTRACT DATA TYPE POINT *** */

#include <stdio.h>
#include "boolean.h"
#include "math.h"
#include "point.h"

/* *** Notasi Akses: Selektor POINT *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y
        
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
    POINT a;
    Absis(a) = X;
    Ordinat(a) = Y;
    return a;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPOINT (POINT * P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
    int x,y;
    scanf("%d %d",&x,&y);
    Absis(*P) = x;
    Ordinat(*P) = y;
}


void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya */
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
{
    printf("<%d %d>, Type=%c, CustFileOrder=%d\n",Absis(P),Ordinat(P),Type(P),CustFileOrder(P));
}
          

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean PEQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
    return (Absis(P1) == Absis(P2) && Ordinat(P1) == Ordinat(P2));
}

boolean PNEQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
    return !PEQ(P1,P2);
}

void CurrentPoint (POINT *P, int X, int Y)
/* Menentukan posisi pemain sekarang */
{
    Absis(*P)=X;
    Ordinat(*P)=Y;
}

void SimpanPoint (POINT *P, int X, int Y, char Type, int custFileOrder)
/* Menyimpan point hasil pembacaan pita karakter */
{
    Absis(*P)=X;
    Ordinat(*P)=Y;
    Type(*P)=Type;
    CustFileOrder(*P)=custFileOrder;
}
