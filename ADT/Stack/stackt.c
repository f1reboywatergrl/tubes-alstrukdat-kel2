#include "stackt.h"
#include <stdio.h>
#include "string.h"
/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateStackEmpty (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP berNilStackai NilStack */
{
    Top(*S)=NilStack;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsStackEmpty (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
    return (Top(S)==NilStack);
}
boolean IsStackFull (Stack S)
/* Mengirim true jika tabel penampung NilStackai elemen stack penuh */
{
    return (Top(S)==MaxEl-1);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, ElTypeList X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    if (IsStackEmpty(*S)){
        Top(*S)=0;
    }
    else{
        Top(*S)++;
    }    
    InfoTop(*S)=X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, ElTypeList* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah NilStackai elemen TOP yang lama, TOP berkurang 1 */
{
    (*X) = InfoTop(*S);
    if (Top(*S)==0){
        Top(*S)=NilStack;
    }
    else{
        Top(*S)--;
    }
}
void CopyStack (Stack S, Stack *S1){
    Stack Temp;
    CreateStackEmpty(&Temp);
    ElTypeList X;
    while(Top(S)!=NilStack){
        Pop(&S,&X);
        Push(&Temp,X);
    }
    while(Top(Temp)!=NilStack){
        Pop(&Temp,&X);
        Push(S1,X);
    }

}
void InverseStack(Stack *S){
    Stack S1;
    CreateStackEmpty(&S1);
    CopyStack((*S),&S1);
    CreateStackEmpty(S);
    ElTypeList X;
    while(Top(S1)!=NilStack){
        Pop(&S1,&X);
        Push(S,X);
    }
}
/*S1 diletakkan dibawah S*/
Stack MergeStack (Stack S, Stack S1){
    Stack Temp;
    CreateStackEmpty(&Temp);
    CopyStack(S1,&Temp);
    CopyStack(S,&Temp);
    return Temp;
}


boolean CekUrutan (Stack S, int urutan){
    if (IsStackEmpty(S)){
        return (urutan == 1);
    }
    else{
        return (urutan - InfoTop(S).kategori == 1);
    }
}


/* saat user add component, kategori komponen direpresentasikan 
sebagai angka urutan kategori komponen tersebut*/

boolean IsStackEqual(Stack S1, Stack S2){
    if(!IsStackFull(S1) || !IsStackFull(S2)){
        return false;
    }
    else{
        ElTypeList X1;
        ElTypeList X2;
        int i = 0;
        boolean sama = true;
        while(i<8 && sama){
            Push(&S1, X1);
            Push(&S2,X2);
            if(strcmp(X1.nama, X2.nama)!=0){
                sama = false;
            }
            i++;
        }
        return sama;
    }
}

void PrintStack(Stack S)
{
    InverseStack(&S);
    ElTypeList komponen;
    int i;
    int nomor=1;
    for (i = Top(S); i >= 0; i--){
        Pop(&S, &komponen);
        printf("%d. %s ",nomor, Nama(komponen));
        nomor++;
        printf("\n");
    }
}

void PrintInventory(List T){
    if (!IsLEmpty(T)){
        int nomor = 1;
        int i;
        int panjang = LengthList(T);
        for (i=0; i < panjang; i++){
            if ((ListElmt(T,i).jumlah) > 0){
                printf("%d. %s\n", nomor, ((ListElmt(T,i)).nama));
                nomor++;
            }
        }
    }
}

/*** COMMAND ***/

/* COMMAND 4 : STARTBUILD */

void STARTBUILD(Stack *S, boolean *lagiBuild, int NoPesanan, int NoPelanggan){
    CreateStackEmpty(S);
    if (*lagiBuild){
        printf("Sedang merakit komputer lain, tidak bisa merakit pesanan yang lainnya.\n");
    }
    else{
        *lagiBuild = true;
        printf("kamu telah memulai pesanan %d untuk pelanggan %d.\n", NoPesanan, NoPelanggan);
    }
}

/* COMMAND 5 : FINISHBUILD */

void FINISHBUILD(List *inventory, Stack Pesanan, Stack Rakitan, boolean *lagiBuild, int NoPesanan, int NoPelanggan){
    if (IsStackEqual(Pesanan, Rakitan)){ //Harus cari cara nyocokin + nentuin Invoice
        *lagiBuild = false;
        printf("Pesanan %d telah selesai. Silahkan antar ke pelanggan %d!\n", NoPesanan, NoPelanggan);
        ElTypeList hasilBuild;
        sprintf(Nama(hasilBuild), "%d", NoPesanan);
        Kategori(hasilBuild) = 9;
        Harga(hasilBuild) = NoPelanggan*(-1);
        Jumlah(hasilBuild) = 1;
        InsertLLast(inventory,hasilBuild);
    }
    else{
        printf("Komponen yang dipasangkan belum sesuai dengan pesanan, build belum dapat diselesaikan.\n");
    }
}
/* lagiBuild adalah variabel yang menandakan apakah user sedang mengerjakan suatu pesanan (status) */

/* COMMAND 6 : ADDCOMPONENT */

void ADDCOMPONENT(Stack *Rakitan, List *inventory){
    if(IsStackFull(*Rakitan)){
        printf("Tidak bisa menambah komponen karena rakitan sudah penuh\n");
    }
    else{
        printf("Komponen yang telah terpasang:\n");
        PrintStack(*Rakitan);

        printf("Komponen yang tersedia:\n");
        PrintInventory(*inventory);
        
        printf("Komponen yang ingin dipasang:\n");
        int nomor; // dari daftar nomor yang muncul di interface
        int penanda = 0; // untuk mencari nomor itu ada di index berapa
        int index = -1; // index inventory 
        scanf("%d", &nomor); 
        while(nomor != penanda){
            index++;
            if ((ListElmt(*inventory,index).jumlah) > 0){
                penanda++;
            }
        }
        if (CekUrutan(*Rakitan, (ListElmt(*inventory,index)).kategori)){
            Push(Rakitan, (ListElmt(*inventory,index)));
            Jumlah(ListElmt(*inventory,index))--;
            printf("Komponen berhasil dipasang!\n");
        }
        else{
            printf("Komponen gagal dipasang karena salah urutan pemasangan\n");
        }
    }
}

/* COMMAND 7 : REMOVECOMPONENT */

void REMOVECOMPONENT(Stack *Rakitan, List *inventory){
    if(IsStackEmpty(*Rakitan)){
        printf("Tidak bisa remove karena rakitan kosong\n");
    }
    else{
        ElTypeList komponen;
        Pop(Rakitan,&komponen);
        int i = 0;
        while(strcmp(Nama(ListElmt(*inventory,i)), Nama(komponen))!=0){
            i++;
        }
        Jumlah(ListElmt(*inventory,i))++;
    }
}
                        
                    