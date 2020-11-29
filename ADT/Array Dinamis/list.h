#ifndef __DYNAMIC_LIST__
#define __DYNAMIC_LIST__
#include "boolean.h"

#define InitialSize 10
//BUAT SHOP & INVENTORY PEMAIN
    
typedef int IdxType;
typedef struct 
{
    char *nama; // Bentuk String, menjelaskan nama
    int harga; //Untuk menjelaskan harga 
    int jumlah; //Untuk menjelaskan jumlah
    int kategori; //Untuk menjelaskan kategori
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

/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize
 */
List MakeList();

/**
 * Destruktor
 * I.S. List terdefinisi
 * F.S. list->A terdealokasi
 */
void DeallocateList(List *list);
 
/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsLEmpty(List list);

int LengthList(List list) ;


ElTypeList GetL(List list, IdxType i);

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int GetLCapacity(List list);

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */

ElTypeList InputLElType();


void InsertLAt(List *list, ElTypeList el, IdxType i);


void InsertLLast(List *list, ElTypeList el);

/**
 * Fungsi uLntuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void InsertFirst(List *list, ElTypeList el);


void TulisIsiList(List T);

void PrintStore(List T);

void CreateElmt (ElTypeList *el, int Harga, char *Nama, int Type );
/* Membuat elemen dummy dengan properti el->harga = Harga, el->nama = *Nama, el->kategori = Type, 
el->jumlah = 0*/


void CreateElmtLengkap (ElTypeList *el, int Harga, char *Nama, int Type, int Jumlah);

void CreateDummies(List *Dummies);
/* Membuat list dummy berisikan elemen dummy (hard-coded) */

#endif