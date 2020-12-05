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

void InsertAtStatik(ListStatik *L, IdxTypeStatik i, ElTypeStatik v)
/* I.S. L terdefinisi, tidak kosong, i merupakan indeks lojik yang valid di L. */
/* F.S. v disisipkan dalam L pada indeks ke-i (bukan menimpa elemen di i). */
{
    IdxTypeStatik iterationIdx;
    for (iterationIdx = L->Neff; iterationIdx > i; iterationIdx--)
    {
        L->A[iterationIdx] = L->A[iterationIdx - 1];
    }
    L->A[iterationIdx] = v;
    L->Neff++;
}

void InsertLastStatik(ListStatik *L, ElTypeStatik v)
/* I.S. L terdefinisi, mungkin kosong. */
/* F.S. v menjadi elemen terakhir L. */
{
    InsertAtStatik(L, L->Neff, v);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyStatik(ListStatik L)
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
void CreatePesanan (Qinfotype *ps, Stack StackPesanan, int Pemesan, int Invoice){
    ps->komponen = StackPesanan;
    ps->orderNumber = 0;
    if(Pemesan==0){
        ps->pemesan=1;
    }
    else{
        ps->pemesan = Pemesan;
    }
    ps->invoice = Invoice;
}

void PrintStatik (ListStatik L){
    printf("[");
    if(!IsEmptyStatik(L)){
        printf("<%d,%d>",ElmtStatik(L,0).pemesan,ElmtStatik(L,0).invoice);
        for(int i=1;i<Neff(L);i++){
            printf(",<%d,%d>",ElmtStatik(L,i).pemesan,ElmtStatik(L,i).invoice);
        }
    }
    printf("]\n");
}

void CreateDummiesPemesan(ListStatik *DummiesPemesan, int CustTotal, List L){
    Stack S1,S2,S3,
    S4,S5,
    S6,S7,
    S8,S9,
    S10,S11,
    S12,S13,
    S14,S15,
    S16,S17,
    S18,S19,
    S20,S21,
    S22,S23,
    S24,S25,
    S26,S27;

    CreateDummyStacks(&S1,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S2,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S3,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    
    CreateDummyStacks(&S4,ListElmt(L,1),ListElmt(L,4),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S5,ListElmt(L,2),ListElmt(L,5),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    
    CreateDummyStacks(&S6,ListElmt(L,1),ListElmt(L,3),ListElmt(L,7),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S7,ListElmt(L,2),ListElmt(L,3),ListElmt(L,8),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));    
    
    CreateDummyStacks(&S8,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,10),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S9,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,11),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));    
    
    CreateDummyStacks(&S10,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,13),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S11,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,14),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));    
    
    CreateDummyStacks(&S12,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,16),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S13,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,17),ListElmt(L,18),ListElmt(L,21));
    
    CreateDummyStacks(&S14,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S15,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S16,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,22));
    CreateDummyStacks(&S17,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,23));

    CreateDummyStacks(&S18,ListElmt(L,0),ListElmt(L,4),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S19,ListElmt(L,0),ListElmt(L,5),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S20,ListElmt(L,0),ListElmt(L,3),ListElmt(L,7),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S21,ListElmt(L,0),ListElmt(L,3),ListElmt(L,8),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S22,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,10),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S23,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,11),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));
    
    CreateDummyStacks(&S24,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,13),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S25,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,14),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S26,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,13),ListElmt(L,15),ListElmt(L,19),ListElmt(L,22));
    CreateDummyStacks(&S27,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,14),ListElmt(L,15),ListElmt(L,20),ListElmt(L,23));
 
    Qinfotype ps;
    MakeEmptyStatik(DummiesPemesan);
    int seed=GetRandomPemesan(5,CustTotal);
    /*
    ALUR PENGISIAN DATA DUMMY:
    1. Buat kumpulan stack untuk diambil sebagai stack komponen
    2. Ambil random number dari pemesan untuk menentukan pelanggan yg memesan
    3. Sekarang nilai akan diambil secara acak secara unlimited, dengan cara
    mengambil seed dari variable global, sambil mencari orderan yang tepat (menghindari collision)
    4. Jika ketemu yang valid, nanti akan di *delete* dengan cara mengubah invoice menjadi -999
    5. Jika list udah kosong, nanti direstore
    */
    CreatePesanan(&ps, S1, seed, 4452);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S2, seed, 4487);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S3, seed, 4542);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S4, seed, 4982);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S5, seed, 5587);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S6, seed, 4509);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S7, seed, 5201);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S8, seed, 5102);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S9, seed, 5420);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S10, seed, 4918);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S11, seed, 5271);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S12, seed, 4871);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S13, seed, 5321);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S14, seed, 5420);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S15, seed, 5503);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S16, seed, 4849);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S17, seed, 4988);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S18, seed, 4762);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S19, seed, 4901);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S20, seed, 5209);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S21, seed, 5376);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S22, seed, 5175);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S23, seed, 5672);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S24, seed, 4984);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S25, seed, 5000);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S26, seed, 5112);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
    CreatePesanan(&ps, S27, seed, 5290);InsertLastStatik(DummiesPemesan,ps);seed=GetRandomPemesan(seed,CustTotal);
}

int GetRandomPemesan(int seed, int CustTotal)
/* Menentukan pelanggan pemesan secara acak */
{
    int seedRes;
    switch(CustTotal){
        case 6:
        seedRes=(seed+5)%(7);break;
        default:
        seedRes=(seed+7)%(CustTotal+1);
    }
    return seedRes;
}

void DelAtStatik(ListStatik *L, IdxTypeStatik I)
/* Definisi Pesanan sudah pernah diambil = Invoicenya -999 */
/* DelAt akan dipanggil SETELAH hasil selesai diakuisisi */
{
    ElmtStatik(*L,I).invoice=ValUndefStatik;
}

int AvoidCollision (ListStatik LStatik, int seed, int custTotal, List L)
/* Mengambil sebuah order secara acak */
{
    seed = seed%27;
    if(ElmtStatik(LStatik,seed).invoice==ValUndefStatik){
        int temp=seed;
        seed = (seed + 1) % 27;
        while(ElmtStatik(LStatik,seed).invoice==ValUndefStatik){
            seed = (seed + 1) % 27;
        }
        if(temp==seed){
            RestartDummyOrders(&LStatik,custTotal,L);
        }
    }
    return seed;
    /* Nanti, seed ini akan digunakan kembali dalam AvoidCollision, 
    lalu element ke-seed akan di delete*/
}

void RestartDummyOrders(ListStatik *DummiesPemesan, int CustTotal, List L)
/* Mengisi kembali list yang sudah kosong */
{
    CreateDummiesPemesan(DummiesPemesan,CustTotal,L);
}
