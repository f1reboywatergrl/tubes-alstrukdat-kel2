/* MODUL LISTStatik INTEGER */
/* Berisi definisi dan semua primitif pemrosesan listStatik integer */
/* Penempatan elemen selalu rapat kiri */

#include "boolean.h"
#include "../Queue/queue.c"

#ifndef LISTStatik_H
#define LISTStatik_H

/* Kamus Umum */

#define IdxMax 26
#define IdxMin 0
#define ValUndefStatik -999 /* indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef  int IdxTypeStatik;
typedef Qinfotype ElTypeStatik;

typedef struct
{
    ElTypeStatik A[IdxMax - IdxMin + 1]; /* memori tempat penyimpan elemen (container) */
    int Neff;                      /* banyaknya elemen efektif */
} ListStatik;

#define ElmtStatik(T,i) (T).A[i] 
#define NeffStatik(T) (T).Neff
/* Indeks yang digunakan [IdxMin..IdxMax] */
/* Jika L adalah ListStatik, cara deklarasi dan akses: */
/* Deklarasi : L : ListStatik */
/* Maka cara akses:
 * L.A untuk mengakses seluruh nilai elemen listStatik
 * L.Neff untuk mengetahui banyaknya elemen
 * L.A[i] untuk mengakses elemen ke-i */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create listStatik kosong */
void MakeEmptyStatik(ListStatik *T);
/* I.S. sembarang */
/* F.S. Terbentuk listStatik L kosong dengan kapasitas IdxMax-IdxMin+1 */

void InsertAtStatik(ListStatik *L, IdxTypeStatik i, ElTypeStatik v);
/* I.S. L terdefinisi, tidak kosong, i merupakan indeks lojik yang valid di L. */
/* F.S. v disisipkan dalam L pada indeks ke-i (bukan menimpa elemen di i). */
void InsertLastStatik(ListStatik *L, ElTypeStatik v);
/* I.S. L terdefinisi, mungkin kosong. */
/* F.S. v menjadi elemen terakhir L. */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test listStatik kosong *** */
boolean IsEmptyStatik(ListStatik L);
/* Mengirimkan true jika listStatik L kosong, mengirimkan false jika tidak */

int GetRandomPemesan(int seed, int CustTotal);
/* Menentukan pelanggan pemesan secara acak */

void DelAtStatik(ListStatik *L, IdxTypeStatik I);
/* Definisi Pesanan sudah pernah diambil = Invoicenya -999 */

int AvoidCollision (ListStatik LStatik, int seed, int custTotal, List L);
/* Mengambil sebuah order secara acak */

void RestartDummyOrders(ListStatik *DummiesPemesan, int CustTotal, List L);
/* Mengisi kembali list yang sudah kosong */
#endif