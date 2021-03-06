/* File: queue.c */


#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/* ********* Prototype ********* */
boolean IsQEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (Tail(Q)==NilQ && Head(Q)==NilQ);
}
boolean IsQFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElQueue */
{
    return (QNBElmt(Q)==MaxElQueue(Q));
}
int QNBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if(IsQEmpty(Q)){
        return 0;
    }
    else{
        if(Head(Q)<=Tail(Q)){
            return (Tail(Q)-Head(Q)+1);
        }
        else{
            return (MaxElQueue(Q)-(Head(Q)-Tail(Q)) +1);
        }
    }
}
/* *** Kreator *** */
void QCreateEmpty (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElQueue=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
    (*Q).T = (Qinfotype *)malloc((Max+1)*sizeof(Qinfotype));
    if((*Q).T!=NULL){
        MaxElQueue(*Q) = Max;
        Head(*Q) = NilQ;
        Tail(*Q) = NilQ;
    }
    else{
        MaxElQueue(*Q)=0;
    }

}

/* *** Destruktor *** */
void QDeAlokasi(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQueue(Q) diset 0 */
{
    free((*Q).T);
    MaxElQueue(*Q)=0;
}

/* *** Primitif Add/Delete *** */
void QAdd (Queue * Q, Qinfotype X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
    if(IsQEmpty(*Q)){
        Head(*Q)=0;
        Tail(*Q)=0;
        InfoTail(*Q)=X;
        InfoHead(*Q)=X;        
    }
    else{
        Tail(*Q)=( (Tail(*Q)+1) % MaxElQueue(*Q) );
        InfoTail(*Q)=X;
    }
}
void QDel (Queue * Q, Qinfotype * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
    if(QNBElmt(*Q)==1){
        *X=InfoHead(*Q);
        Head(*Q)=NilQ;
        Tail(*Q)=NilQ;
    }
    else{
        *X=InfoHead(*Q);
        Head(*Q)=( (Head(*Q)+1) % MaxElQueue(*Q));   
        InfoHead(*Q)=(*Q).T[Head(*Q)];     
    }
}


void SetOrderNumber (Queue *Q, int OrderNumber)
/* Set order number dari TAIL(Q) (setelah Enqueue) */
{
    OrderNumber(InfoTail(*Q)) = OrderNumber;
}

void IncrementNumber (int *Number)
/* Increments order number */
{
    *Number = *Number +1;
}

void PrintTail (Queue Q)
{
    printf("Invoice = %d\n",Invoice(InfoTail(Q)));
    printf("Pemesan = %d\n",Pemesan(InfoTail(Q)));
    printf("OrderNo = %d\n",OrderNumber(InfoTail(Q)));
    printf("Nama Top = %s\n",InfoTop(Komponen(InfoTail(Q))).nama);
}

