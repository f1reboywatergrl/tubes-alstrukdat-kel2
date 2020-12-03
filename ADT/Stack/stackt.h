/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "boolean.h"
#include "../Array Dinamis/list.c"

#define NilStack -1
#define MaxEl 8

/* Setiap indeks didefine sebagai komponen rakitan*/

/* NilStack adalah stack dengan elemen kosong . */

typedef int AdressTOP;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  ElTypeList T[MaxEl]; /* tabel penyimpan elemen */
  AdressTOP TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Definisi stack S kosong : S.TOP = NilStack */
/* Elemen yang dipakai menyimpan NilStackai Stack T[0]..T[MaxEl-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateStackEmpty (Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP berNilStackai NilStack */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsStackEmpty (Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */

boolean IsStackFull (Stack S);
/* Mengirim true jika tabel penampung NilStackai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, ElTypeList X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, ElTypeList* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah NilStackai elemen TOP yang lama, TOP berkurang 1 */

void CopyStack (Stack S, Stack *S1);

void InverseStack (Stack *S);

Stack MergeStack (Stack S, Stack S1);
/*S2 diletakkan dibawah S1*/


boolean CekUrutan (Stack S, int urutan);
/* saat user add component, kategori komponen direpresentasikan sebagai 
angka urutan kategori komponen tersebut

boolean IsStackEqual(Stack S1, Stack S2);
/* Mengirim true jika kedua stack yang full adalah sama
   Mengirim false jika kedua stack berbeda atau stack tidak full */

void PrintStack(Stack S);

int PrintInventory(List T);

/***** COMMAND *****/

void STARTBUILD(Stack *S, boolean *lagiBuild, int NoPesanan, int NoPelanggan);
/* memulai build */

void FINISHBUILD(List *inventory, Stack Pesanan, Stack Rakitan, boolean *lagiBuild, int NoPesanan, int NoPelanggan);
/* mengecek kesesuaian rakitan dengan pesanan dan mengakhiri build */

void ADDCOMPONENT(Stack *Rakitan, List *inventory, boolean lagiBuild);
/* menambah komponen dari inventory untuk merakit */

void REMOVECOMPONENT(Stack *Rakitan, List *inventory, boolean lagiBuild);
/* melepas komponen dari rakitan dan memasukannya ke inventory kembali */

void CreateDummyStacks (Stack *Dummies, ElTypeList order1, ElTypeList order2, ElTypeList order3, ElTypeList order4, ElTypeList order5, ElTypeList order6, ElTypeList order7, ElTypeList order8);
/* Membuat data dummy kumpulan stack untuk order*/
#endif