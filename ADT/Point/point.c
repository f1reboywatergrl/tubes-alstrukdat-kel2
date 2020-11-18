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
POINT MakePOINT (float X, float Y)
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
    float x,y;
    scanf("%f %f",&x,&y);
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
    printf("(%.2f,%.2f)",Absis(P),Ordinat(P)); /* perhatikan bahwa untuk menghasilkan 2 desimal, gunakan %.2f */
}
          

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
    return (Absis(P1) == Absis(P2) && Ordinat(P1) == Ordinat(P2));
}

boolean NEQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
    return !EQ(P1,P2);
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
    return EQ(P,MakePOINT(0,0));
}

boolean IsOnSbX (POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
    return (Ordinat(P) == 0);
}

boolean IsOnSbY (POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
    return (Absis(P) == 0);
}

int Kuadran (POINT P)
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
{
    if(Absis(P) > 0 && Ordinat(P) > 0) {
        return 1;
    } else if(Absis(P) > 0 && Ordinat(P) < 0) {
        return 4;
    } else if(Absis(P) < 0 && Ordinat(P) < 0) {
        return 3;
    }
    else {
        return 2;
    }
}


/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
POINT PlusDelta (POINT P, float deltaX, float deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
    Absis(P) = Absis(P) + deltaX;
    Ordinat(P) = Ordinat(P) + deltaY;
    return P;
}

void Geser (POINT *P, float deltaX, float deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
    Absis(*P) = Absis(*P) + deltaX;
    Ordinat(*P) = Ordinat(*P) + deltaY;
}

float Jarak0 (POINT P)
/* Menghitung jarak P ke (0,0) */
{
    return (sqrt( (Absis(P) * Absis(P) ) + (Ordinat(P) * Ordinat(P) ) ) ); /* atau bisa dengan pow(...,2) */
}

float Panjang (POINT P1, POINT P2)
/* Menghitung panjang garis yang dibentuk P1 dan P2. */
{
    return sqrt(pow(Absis(P1) - Absis(P2), 2) + pow(Ordinat(P1) - Ordinat(P2), 2));
}
