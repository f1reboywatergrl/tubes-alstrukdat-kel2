#include "list-statik.c"
#include <stdio.h>

int main(){
    int custTotal=9;
    int Index=1;
    List L=MakeList();
    ListStatik LS;
    CreateDummies(&L);
    /* Misalnya ada 9 customer */
    CreateDummiesPemesan(&LS, custTotal, L);
    PrintStatik(LS);
    Index=AvoidCollision(LS,Index,custTotal,L);
    printf("<%d,%d>\n",ElmtStatik(LS,Index).invoice, ElmtStatik(LS,Index).pemesan);
    DelAtStatik(&LS,Index);
    Index=AvoidCollision(LS,Index,custTotal,L);
    printf("<%d,%d>\n",ElmtStatik(LS,Index).invoice, ElmtStatik(LS,Index).pemesan);
    return 0;
    /*
    ALUR PENGISIAN DATA DUMMY:
    1. Buat kumpulan stack untuk diambil sebagai stack komponen
    2. Ambil random number dari pemesan untuk menentukan pelanggan yg memesan
    3. Sekarang nilai akan diambil secara acak secara unlimited, dengan cara
    mengambil seed dari variable global, sambil mencari orderan yang tepat (menghindari collision)
    4. Jika ketemu yang valid, nanti akan di *delete* dengan cara mengubah invoice menjadi -999
    5. Jika list udah kosong, nanti direstore
    */
}