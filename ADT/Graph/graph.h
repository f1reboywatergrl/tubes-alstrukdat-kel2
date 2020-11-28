/* File: graph.h */
/* ADT graph dengan representasi multilist */
#include "../Matriks/matriks.c"
#ifndef GRAPH_H
#define GRAPH_H

#include "boolean.h"
#include "listlinier.c"
#include <stdlib.h>

#define Nil NULL

typedef int infotypeGraph;

typedef struct tElmtgraph *addressGraph;
typedef struct tElmtgraph {
	infotypeGraph info;
	List link;
	addressGraph next;
} ElmtGraph;
typedef struct {
	addressGraph First;
} Graph;

/* Definisi graph :
   Graph kosong : First(L) = Nil
   Setiap elemen dengan addressGraph P dapat diacu Info(P), Next(P)
   Elemen terakhir graph : jika addressnya Last, maka NextGraph(Last)=Nil */

/*	
	Misal file konfigurasi
	1 2 3 4

1	0 1 1 0
2	1 0 1 0
3	1 1 0 1
4	0 0 1 0 

Maka
	1 -> 2,3
	2 -> 1,3
	3 -> 1,2,4
	4 -> 3
akan berupa List Linier yang menunjuk ke titik2nya
*/

#define InfoGraph(P) (P)->info
#define NextGraph(P) (P)->next
#define Link(P) 	 (P)->link
#define FirstGraph(G) ((G).First)

void CreateEmptyGraph(Graph *G);
/* I.S. sembarang             */
/* F.S. Terbentuk graph kosong */

boolean IsGraphEmpty(Graph G);
/* Mengirimkan true jika graph kosong */

addressGraph AlokasiGraph(infotype X);
/* Mengirimkan addressGraph hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressGraph tidak nil, dan misalnya */
/* menghasilkan P, maka InfoGraph(P)=X, NextGraph(P)=NULL, dan Link(P) berisi list kosong */
/* Jika alokasi gagal, mengirimkan NULL */

void initGraph(Graph *G, int n);
/* I. S. Graph G sembarang, n adalah jumlah building/ jumlah elemen parent list
   F. S. Terbentuk Graph n elemen dan link tiap elemen berupa empty list */

void PrintGraph(Graph G);
/* I.S. Graph mungkin kosong */
/* F.S. Jika Graph tidak kosong, isi info Graph dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Graph kosong : menulis [] */


void AddLink(Graph *G, infotype n, infotype p);
/* I. S. Graph G terdefinisi, n dan p pasti tidak lebih dari jumlah building
   F. S. Link dari elemen n bertambah dengan p, dan sebaliknya (soalnya bolak balik)
   contoh :
   1 2->3
   2 1
   3 1
   Add(&G, 2, 3) 
   1 2->3
   2 1->3
   3 1->3 */

void PrintLink(Graph G, infotype X);

boolean IsLinked(Graph G, infotype n, infotype p);
/* Mengembalikan true jika pada link n ada p */

addressGraph SearchGraph(Graph G, infotype X);

void Move (Graph G, int CurrentPos, int TargetPos,MATRIKS *M);

void ShowValidTargets (Graph G, int CurrentPos);
#endif