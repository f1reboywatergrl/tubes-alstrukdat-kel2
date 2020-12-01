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

int PrintInventory(List T){
    if (!IsLEmpty(T)){
        int nomor = 0;
        int i;
        int panjang = LengthList(T);
        for (i=0; i < panjang; i++){
            if ((ListElmt(T,i).jumlah) > 0){
                printf("%d. %s\n", nomor+1, ((ListElmt(T,i)).nama));
                nomor++;
            }
        }
        if(nomor == 0){
            printf("Inventory is empty\n");
        }
        return nomor;
    }
    else{
        printf("Inventory is empty\n");
        return 0;
    }
}
/*** COMMAND ***/

/* COMMAND 4 : STARTBUILD */

void STARTBUILD(Stack *S, boolean *lagiBuild, int NoPesanan, int NoPelanggan){
    if(*lagiBuild){
        printf("Cant start a new build while you haven't finished current build\n");
    }
    else{
        CreateStackEmpty(S);
        if (*lagiBuild){
            printf("Currently building another computer, unable to start a new build.\n");
        }
        else{
            *lagiBuild = true;
            printf("Started order %d for Customer %d.\n", NoPesanan, NoPelanggan);
        }
    }
}

/* COMMAND 5 : FINISHBUILD */

void FINISHBUILD(List *inventory, Stack Pesanan, Stack Rakitan, boolean *lagiBuild, int NoPesanan, int NoPelanggan){
    if(*lagiBuild){    
        if (IsStackEqual(Pesanan, Rakitan)){ //Harus cari cara nyocokin + nentuin Invoice
            *lagiBuild = false;
            printf("Order #%d is complete. Deliver it to Customer %d!\n", NoPesanan, NoPelanggan);
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
    else{
        printf("There is no build that has been started currently\n");
    }
}
/* lagiBuild adalah variabel yang menandakan apakah user sedang mengerjakan suatu pesanan (status) */

/* COMMAND 6 : ADDCOMPONENT */

void ADDCOMPONENT(Stack *Rakitan, List *inventory, boolean lagiBuild){
    if(lagiBuild){
        if(IsStackFull(*Rakitan)){
            printf("Cannot add anymore components!\n");
        }
        else{
            printf("Currently attached components:\n");
            PrintStack(*Rakitan);

            printf("Available components:\n");
            int amount = PrintInventory(*inventory); //jumlah komponen yang tersedia
            if(amount==0){
                //printf("Cannot add anymore components!\n");
                printf("Go to shop to buy component\n");
            }
            else{
                printf("Attach which component?:\n");
                int nomor; // dari daftar nomor yang muncul di interface
                int penanda = 0; // untuk mencari nomor itu ada di index berapa
                int index = -1; // index inventory 
                scanf("%d", &nomor);
                if(nomor<1 || nomor>amount){
                    printf("Wrong input!\n");
                }
                else{        
                    while(nomor != penanda){
                        index++;
                        if ((ListElmt(*inventory,index).jumlah) > 0){
                            penanda++;
                        }
                    }
                    if (CekUrutan(*Rakitan, (ListElmt(*inventory,index)).kategori)){
                        Push(Rakitan, (ListElmt(*inventory,index)));
                        Jumlah(ListElmt(*inventory,index))--;
                        printf("Successfully attached!\n");
                    }
                    else{
                        printf("Attachment unsucessful! Re-check your order!\n");
                    }
                }
            }
        }
    }
    else{
        printf("Can't add any component because there is no build that has started currently\n");
    }
}

/* COMMAND 7 : REMOVECOMPONENT */

void REMOVECOMPONENT(Stack *Rakitan, List *inventory, boolean lagiBuild){
    if (lagiBuild){
        if(IsStackEmpty(*Rakitan)){
            printf("Your build is currently empty.\n");
        }
        else{
            ElTypeList komponen;
            Pop(Rakitan,&komponen);
            int i = 0;
            while(strcmp(Nama(ListElmt(*inventory,i)), Nama(komponen))!=0){
                i++;
            }
            Jumlah(ListElmt(*inventory,i))++;
            printf("%s has been sucessfully removed from the current build.\n",Nama(komponen));
        }
    }
    else{
        printf("Can't remove any component because there is no build that has started currently.\n");
    }
}
                        
void CreateDummyStacks (Stack *Dummies, ElTypeList order1, ElTypeList order2, ElTypeList order3, ElTypeList order4, ElTypeList order5, ElTypeList order6, ElTypeList order7, ElTypeList order8)
/* Membuat data dummy kumpulan stack untuk order*/
{
    CreateStackEmpty(Dummies);
    Push(Dummies,order1);
    Push(Dummies,order2);
    Push(Dummies,order3);
    Push(Dummies,order4);
    Push(Dummies,order5);
    Push(Dummies,order6);
    Push(Dummies,order7);
    Push(Dummies,order8);
}                    