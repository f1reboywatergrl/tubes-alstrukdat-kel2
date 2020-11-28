#include "list.h"
#include <stdlib.h>

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
void InsertLast(List *list, ElTypeList el) 
{
    int insertAt = LengthList(*list);
    printf("%d",LengthList(*list));
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
    printf("[");
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
    printf("]\n");
    return;
}
