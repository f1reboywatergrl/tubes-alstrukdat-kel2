/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#ifndef queue_H
#define queue_H

#include "boolean.h"
#include "../Stack/stackt.h"


/* Konstanta untuk mendefinisikan address tak terdefinisi */
#define NilQ -1

/*
Infotype dipecah jadi:
- Stack Komponen (isinya komponen yang pelanggan mau)
- int Invoice (isinya duit yang pelanggan akan bayar)
- int Pemesan (no. pelanggan)
- int OrderNumber (no. pesanan)
*/

typedef struct{
        Stack komponen;
        int invoice;
        int pemesan;
        int orderNumber;
} Qinfotype;

/* Definisi elemen dan address */
typedef int Qaddress;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct { Qinfotype * T;   /* tabel penyimpan elemen */
                 Qaddress HEAD;  /* alamat penghapusan */
                 Qaddress TAIL;  /* alamat penambahan */
                 int MaxElQueue;     /* Max elemen queue */
               } Queue;
/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q) (Q).MaxElQueue

/* Macro infotype queue */
#define Komponen(T) (T).komponen
#define Invoice(T) (T).invoice
#define Pemesan(T) (T).pemesan
#define OrderNumber(T) (T).orderNumber

/* ********* Prototype ********* */
boolean IsQEmpty (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsQFull (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int QNBElmt (Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void QCreateEmpty (Queue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void QDeAlokasi(Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void QAdd (Queue * Q, Qinfotype X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void QDel (Queue * Q, Qinfotype * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
void PrintInfoHead(Queue Q);
void PrintQueue (Queue Q);

#endif
