#include <stdio.h>
#include <stdlib.h>
#include "list.c" 

void Status(int UangPemain, int Build, int Order, List InventoryPemain, int Lokasi){
    printf("Uang tersisa: $%d\n",UangPemain);
    printf("Build yang sedang dikerjakan: pesanan %d untuk pelanggan %d.\n", Order, Build);
    printf("Lokasi: pemain sedang berada pada ");
    switch(Lokasi){
        case -1:
        printf("Base");break;
        
        case 0:
        printf("Shop");break;

        default:
        printf("Pelanggan %d",Lokasi);
    }
    printf("\n");
    printf("Inventory anda:\n");
    TampilInventory(InventoryPemain);
}
