#ifndef __DYNAMIC_LIST__
#define __DYNAMIC_LIST__
#include "boolean.h"

#define InitialSize 10
//BUAT SHOP & INVENTORY PEMAIN
/*
Yang harus disimpen:
-Invoice
-Nomor pelanggan
-Order number
*/
typedef int IdxType;
typedef struct 
{
    char *nama; // Bentuk String, menjelaskan nama -> Ketika nyimpen Build yg udah jadi -> "Rakitan"
    int harga; //Untuk menjelaskan harga -> Ketika nyimpen Build yg udah jadi -> Invoice
    int jumlah; //Untuk menjelaskan jumlah -> Ketika nyimpen Build yg udah jadi -> Nomor pelanggan 
    int kategori; //Untuk menjelaskan kategori -> Ketika nyimpen Build yg udah jadi -> Order Number
}ElTypeList;

typedef struct {
    ElTypeList *A;
    int Capacity;
    int Neff;
} List;

#define ListElmt(T,i) (T).A[i] //Macro buat element ke-i pada list T
#define Harga(T) T.harga
#define Nama(T) T.nama
#define Jumlah(T) T.jumlah
#define Kategori(T) T.kategori
#define Neff(T) T.Neff

List MakeList();
/* Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize */

void DeallocateList(List *list);
 /* Destruktor
 * I.S. List terdefinisi
 * F.S. list->A terdealokasi */

boolean IsLEmpty(List list);
/* Fungsi untuk mengetahui apakah suatu list kosong.
 Prekondisi: list terdefinisi */

int LengthList(List list) ;
/* Mengukur panjang dari suatu list */

ElTypeList GetL(List list, IdxType i);

int GetLCapacity(List list);
/* Fungsi untuk mendapatkan kapasitas yang tersedia.
 Prekondisi: list terdefinisi */

ElTypeList InputLElType();
/* Fungsi untuk menambahkan elemen baru di index ke-i
 Prekondisi: list terdefinisi, i di antara 0..Length(list). */

void InsertLAt(List *list, ElTypeList el, IdxType i);
/* Fungsi untuk menambahkan elemen baru di akhir indeks i */

void InsertLLast(List *list, ElTypeList el);
/* Fungsi untuk menambahkan elemen baru di akhir list. */

void InsertFirst(List *list, ElTypeList el);
/* Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi */

void TulisIsiList(List T);
/*Menampilkan isi dari list */

void TampilInventory(List T);
/* Menampilkan Isi Inventory untuk command STATUS */

void CreateElmt (ElTypeList *el, int Harga, char *Nama, int Type );
/* Membuat elemen dummy dengan properti el->harga = Harga, el->nama = *Nama, el->kategori = Type, 
el->jumlah = 0*/

void CreateElmtLengkap (ElTypeList *el, int Harga, char Nama[], int Type, int Jumlah);
/* Membuat elemen dummy dengan properti el->harga = Harga, el->nama = *Nama, el->kategori = Type, 
el->jumlah = Jumlah*/

void CreateDummies(List *Dummies);
/* Membuat list dummy berisikan elemen dummy (hard-coded) */


ElTypeList SearchElTypeList (List Dummies, char *Nama, int jumlah);

void IsiJumlah (ElTypeList *item, int jumlah);
#endif