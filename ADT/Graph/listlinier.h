/* File : listLinierlinier.h */
/* contoh ADT listLinier berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotypeLinier adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "boolean.h"

#define Nil NULL

typedef int infotypeLinier;
typedef struct tElmtlistLinier *address;
typedef struct tElmtlistLinier { 
	infotypeLinier info;
	address next;
} ElmtListLinier;
typedef struct {
	address First;
} ListLinier;

/* Definisi listLinier : */
/* ListLinier kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir listLinier : jika addressnya Last, maka Next(Last)=Nil */
#define InfoLinier(P) (P)->info
#define NextLinier(P) (P)->next
#define First(L) ((L).First)

/* PROTOTYPE */
/****************** TEST LISTLinier KOSONG ******************/
boolean IsEmpty (ListLinier L);
/* Mengirim true jika listLinier kosong */

/****************** PEMBUATAN LISTLinier KOSONG ******************/
void CreateEmpty (ListLinier *L);
/* I.S. sembarang             */
/* F.S. Terbentuk listLinier kosong */

/****************** Manajemen Memori ******************/
address Alokasi (infotypeLinier X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void Dealokasi (address *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN LISTLinier ******************/
address Search (ListLinier L, infotypeLinier X);
/* Mencari apakah ada elemen listLinier dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (ListLinier *L, infotypeLinier X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (ListLinier *L, infotypeLinier X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen listLinier di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (ListLinier *L, infotypeLinier *X);
/* I.S. ListLinier L tidak kosong  */
/* F.S. Elemen pertama listLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast (ListLinier *L, infotypeLinier *X);
/* I.S. listLinier tidak kosong */
/* F.S. Elemen terakhir listLinier dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstLinier (ListLinier *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsertAfterLinier (ListLinier *L, address P, address Prec);
/* I.S. Prec pastilah elemen listLinier dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLastLinier (ListLinier *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (ListLinier *L, address *P);
/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen pertama listLinier sebelum penghapusan */
/*      Elemen listLinier berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP (ListLinier *L, infotypeLinier X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen listLinier beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari listLinier dan di-dealokasi */
/* Jika tidak ada elemen listLinier dengan info(P)=X, maka listLinier tetap */
/* ListLinier mungkin menjadi kosong karena penghapusan */
void DelLast (ListLinier *L, address *P);
/* I.S. ListLinier tidak kosong */
/* F.S. P adalah alamat elemen terakhir listLinier sebelum penghapusan  */
/*      Elemen listLinier berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfter (ListLinier *L, address *Pdel, address Prec);
/* I.S. ListLinier tidak kosong. Prec adalah anggota listLinier  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen listLinier yang dihapus  */

/****************** PROSES SEMUA ELEMEN LISTLinier ******************/
void PrintInfo (ListLinier L);
/* I.S. ListLinier mungkin kosong */
/* F.S. Jika listLinier tidak kosong, iai listLinier dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika listLinier kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
int NbElmt (ListLinier L);
/* Mengirimkan banyaknya elemen listLinier; mengirimkan 0 jika listLinier kosong */

/*** Prekondisi untuk Max/Min/rata-rata : ListLinier tidak kosong ***/
infotypeLinier Max (ListLinier L);
/* Mengirimkan nilai info(P) yang maksimum */
address AdrMax (ListLinier L);
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
infotypeLinier Min (ListLinier L);
/* Mengirimkan nilai info(P) yang minimum */
address AdrMin (ListLinier L);
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
float Average (ListLinier L);
/* Mengirimkan nilai rata-rata info(P) */

/****************** PROSES TERHADAP LISTLinier ******************/

void InversListLinier (ListLinier *L);
/* I.S. sembarang. */
/* F.S. elemen listLinier dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen listLinier, tanpa melakukan alokasi/dealokasi. */

void Konkat1 (ListLinier *L1, ListLinier *L2, ListLinier *L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah listLinier : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen listLinier L1 dan L2) */
/* dan L1 serta L2 menjadi listLinier kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */

#endif