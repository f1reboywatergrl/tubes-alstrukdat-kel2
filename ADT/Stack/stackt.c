#include "stackt.h"
#include <stdio.h>
/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */
{
    Top(*S)=Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
    return (Top(S)==Nil);
}
boolean IsFull (Stack S)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
    return (Top(S)==MaxEl-1);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotype X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    if (IsEmpty(*S)){
        Top(*S)=0;
    }
    else{
        Top(*S)++;
    }    
    InfoTop(*S)=X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotype* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    (*X) = InfoTop(*S);
    if (Top(*S)==0){
        Top(*S)=Nil;
    }
    else{
        Top(*S)--;
    }
}
void CopyStack (Stack S, Stack *S1){
    Stack Temp;
    CreateEmpty(&Temp);
    infotype X;
    while(Top(S)!=Nil){
        Pop(&S,&X);
        Push(&Temp,X);
    }
    while(Top(Temp)!=Nil){
        Pop(&Temp,&X);
        Push(S1,X);
    }

}
void InverseStack(Stack *S){
    Stack S1;
    CreateEmpty(&S1);
    CopyStack((*S),&S1);
    CreateEmpty(S);
    infotype X;
    while(Top(S1)!=Nil){
        Pop(&S1,&X);
        Push(S,X);
    }
}
/*S1 diletakkan dibawah S*/
Stack MergeStack (Stack S, Stack S1){
    Stack Temp;
    CreateEmpty(&Temp);
    CopyStack(S1,&Temp);
    CopyStack(S,&Temp);
    return Temp;
}

