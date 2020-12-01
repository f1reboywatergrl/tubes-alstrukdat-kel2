#include "list-statik.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong */
void MakeEmptyStatik(ListStatik *L)
/* I.S. sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
{
    L->Neff = 0;
}

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */

void InsertAtStatik(ListStatik *L, IdxType i, ElTypeStatik v)
/* I.S. L terdefinisi, tidak kosong, i merupakan indeks lojik yang valid di L. */
/* F.S. v disisipkan dalam L pada indeks ke-i (bukan menimpa elemen di i). */
{
    IdxType iterationIdx;
    for (iterationIdx = L->Neff; iterationIdx > i; iterationIdx--)
    {
        L->A[iterationIdx] = L->A[iterationIdx - 1];
    }
    L->A[iterationIdx] = v;
    L->Neff++;
}

void InsertLast(ListStatik *L, ElTypeStatik v)
/* I.S. L terdefinisi, mungkin kosong. */
/* F.S. v menjadi elemen terakhir L. */
{
    InsertAt(L, L->Neff, v);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty(ListStatik L)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    if (L.Neff > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* PEMBUATAN DUMMY PEMESAN */
void CreatePesanan (Qinfotype *ps, int OrderNumber, int Pemesan, int Invoice){
    ps->orderNumber = OrderNumber;
    ps->pemesan = Pemesan;
    ps->invoice = 0;
}

void CreateDummiesPemesan(ListStatik *DummiesPemesan){
    Qinfotype ps;

    CreatePesanan(&ps, 1, 1, 3452);
    CreatePesanan(&ps, 2, 2, 3487);
    CreatePesanan(&ps, 3, 2, 3542);
    CreatePesanan(&ps, 4, 3, 3982);
    CreatePesanan(&ps, 5, 4, 4587);
    CreatePesanan(&ps, 6, 5, 3509);
    CreatePesanan(&ps, 7, 5, );
    CreatePesanan(&ps, 8, 5, );
    CreatePesanan(&ps, 9, 6, );
    CreatePesanan(&ps, 10, 6, );
    CreatePesanan(&ps, 11, 7, );
    CreatePesanan(&ps, 12, 8, );
    CreatePesanan(&ps, 13, 9, );
    CreatePesanan(&ps, 14, 10, );
    CreatePesanan(&ps, 15, 10, );
    CreatePesanan(&ps, 16, 10, );
    CreatePesanan(&ps, 17, 10, );
    CreatePesanan(&ps, 18, 11, );
    CreatePesanan(&ps, 19, 11, );
    CreatePesanan(&ps, 20, 12, );
    CreatePesanan(&ps, 21, 12, );
    CreatePesanan(&ps, 22, 13, );
    CreatePesanan(&ps, 23, 14, );
    CreatePesanan(&ps, 24, 15, );
    CreatePesanan(&ps, 25, 16, );
    CreatePesanan(&ps, 26, 16, );
    CreatePesanan(&ps, 27, 17, );
}