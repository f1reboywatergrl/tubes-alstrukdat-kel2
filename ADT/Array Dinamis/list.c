#include "list.h"
#include <stdlib.h>
#include "stdio.h"
/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize
 */
List MakeList() {
    List list;
    list.A = (ElTypeList *) malloc(InitialSize * sizeof(ElTypeList));
    list.Capacity = InitialSize;
    list.Neff = 0;
    return list;
}

void DeallocateList(List *list) {
    free(list->A);
}

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsLEmpty(List list) {
    return list.Neff == 0;
}

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int LengthList(List list) {
    return list.Neff;
}

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
ElTypeList GetL(List list, IdxType i) {
    return list.A[i];
}

// /**
//  * Fungsi untuk mendapatkan kapasitas yang tersedia.
//  * Prekondisi: list terdefinisi
//  */
int GetLCapacity(List list) {
    return list.Capacity;
}

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */

ElTypeList InputLElType(){
    ElTypeList el;
    printf("Masukkan nama barang:");
    scanf("%s",((el.nama)));
    printf("Masukkan harga:");
    scanf("%d",(&el.harga));
    printf("Masukkan jumlah:");
    scanf("%d",(&el.jumlah));
    printf("Masukkan kategori:");
    scanf("%d",(&el.kategori));
    return el;
}
/*
Contoh buat kalo setiap fungsi minta masuk ElType, dibikin jadi variabel dulu,
ElType el;
el = InputElType(); 
baru bisa dimasukin, karena skrg ElType nya isinya >1 elemen
*/

void InsertLAt(List *list, ElTypeList el, IdxType i) {
    int length = LengthList(*list);
    int capacity = GetLCapacity(*list);

    if (length == capacity) {
        int desiredCapacity = capacity + InitialSize;
        ElTypeList *array = (ElTypeList *) malloc(desiredCapacity * sizeof(ElTypeList));
        for (int a = 0; a < length; a++) {
            array[a] = GetL(*list, a);
        }
        free(list->A);
        
        list->A = array;
        list->Capacity = desiredCapacity;
    }

    for (int a = length - 1; a >= i; a--) {
        list->A[a + 1] = list->A[a];
    }

    list->A[i] = el;
    list->Neff++;
}

/**
 * Fungsi untuk menambahkan elemen baru di akhir list.
 * Prekondisi: list terdefinisi
 */
void InsertLLast(List *list, ElTypeList el) 
{
    int insertAt = LengthList(*list);
    //printf("%d",LengthList(*list));
    InsertLAt(list, el, insertAt);
}

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void InsertLFirst(List *list, ElTypeList el) {
    InsertLAt(list, el, 0);
}

void TulisIsiList(List T){
    /*printf("[");
    if (!IsLEmpty(T)){
        int i;
        for (i=0; i < LengthList(T); i++){
            int panjang = LengthList(T);
            if ((ListElmt(T,i).jumlah) > 0){
                printf("[");
                int j;
                for (j=0; j<4; j++){
                    if (j==0){
                        printf("%s",((ListElmt(T,i)).nama));
                    }
                    if (j==1){
                        printf("%d",(((ListElmt(T,i)).harga)));
                    }
                    if (j==2){
                        printf("%d",((ListElmt(T,i)).jumlah));
                    }   
                    if (j==3){
                        printf("%d",((ListElmt(T,i)).kategori));
                    }
                if (j != 3){
                    printf(",");
                    }
                }
                printf("]");
                if (i != (LengthList(T)-1)){
                    printf(",");
                }
            }
        }
    }
    printf("]\n");*/

    /*
    Dalam bentuk 
    1. x
    2. y
    3. z
    dst.
    */
    for (int i=0;i<LengthList(T);i++){
        printf("%d. %s (%d)\n",i+1,Nama(ListElmt(T,i)),Jumlah(ListElmt(T,i)));
    }
}

void TampilInventory(List T){
    int j = 1;
    for (int i=0;i<LengthList(T);i++){
        if (Jumlah(ListElmt(T,i))>0){
            printf("%d. %s - (%d)\n",j,Nama(ListElmt(T,i)),Jumlah(ListElmt(T,i)));
            j++;
        }
    }

}
/* ------------ FUNGSI PEMBUAT DATA DUMMY ------------ */
void CreateElmt (ElTypeList *el, int Harga, char *Nama, int Type )
/* Membuat elemen dummy dengan properti el->harga = Harga, el->nama = *Nama, el->kategori = Type, 
el->jumlah = 0*/
{
    el->harga = Harga;
    el->nama = Nama;
    el->jumlah =0;
    el->kategori = Type;
}
void CreateElmtLengkap (ElTypeList *el, int Harga, char *Nama, int Type, int Jumlah){

    el->harga = Harga;
    el->nama = Nama;
    el->jumlah = Jumlah;
    el->kategori = Type;

}
void CreateDummies(List *Dummies)
/* Membuat list dummy berisikan elemen dummy (hard-coded) */
{
    ElTypeList el;
    /* MOTHERBOARD */
    CreateElmt(&el,100,"Motherboard Micro-ATX",1);InsertLLast(Dummies,el);
    CreateElmt(&el,150,"Motherboard Mini ITX",1);InsertLLast(Dummies,el);
    CreateElmt(&el,200,"Motherboard E-ATX",1);InsertLLast(Dummies,el);
    /* CPU */
    CreateElmt(&el,2000,"Processor Intel i3",2);InsertLLast(Dummies,el);
    CreateElmt(&el,2500,"Processor Intel i5",2);InsertLLast(Dummies,el);
    CreateElmt(&el,3000,"Processor Intel i7",2);InsertLLast(Dummies,el);
    /* MEMORY */
    CreateElmt(&el,70,"RAM 4GB",3);InsertLLast(Dummies,el);
    CreateElmt(&el,140,"RAM 8GB",3);InsertLLast(Dummies,el);
    CreateElmt(&el,210,"RAM 16GB",3);InsertLLast(Dummies,el);
    /* CPU COOLER */
    CreateElmt(&el,60,"Heatsink",4);InsertLLast(Dummies,el);
    CreateElmt(&el,70,"Liquid Cooler",4);InsertLLast(Dummies,el);
    CreateElmt(&el,80,"Dry Ice Cooler",4);InsertLLast(Dummies,el);
    /* CASE */
    CreateElmt(&el,120,"Plastic",5);InsertLLast(Dummies,el);
    CreateElmt(&el,140,"Metal",5);InsertLLast(Dummies,el);
    CreateElmt(&el,160,"Carbon Fiber",5);InsertLLast(Dummies,el);
    /* GPU */
    CreateElmt(&el,200,"NVDIA NV3",6);InsertLLast(Dummies,el);
    CreateElmt(&el,400,"NVDIA NV4",6);InsertLLast(Dummies,el);
    CreateElmt(&el,500,"NVDIA GEFORCE",6);InsertLLast(Dummies,el);
    /* STORAGE */
    CreateElmt(&el,500,"512GB",7);InsertLLast(Dummies,el);
    CreateElmt(&el,750,"1TB",7);InsertLLast(Dummies,el);
    CreateElmt(&el,1000,"2TB",7);InsertLLast(Dummies,el);
    /* PSU */
    CreateElmt(&el,20,"Power Supply AT",8);InsertLLast(Dummies,el);
    CreateElmt(&el,30,"Power Supply ATX",8);InsertLLast(Dummies,el);
    CreateElmt(&el,40,"Power Supply BTX",8);InsertLLast(Dummies,el);
}