#include <stdio.h>
#include <stdlib.h>
#include "list.c" 

void Status(int uang, int pelanggan, int order, List Inventory, char lokasi[100]){
    printf("Uang tersisa: $%d\n",uang);
    printf("Build yang sedang dikerjakan: pesanan %d untuk pelanggan %d.\n",order,pelanggan);
    printf("Lokasi: pemain sedang berada pada %s.\n",lokasi);
    printf("Inventory anda:\n");
    for (int i=0;i<Length(Inventory);i++){
        printf("%d. %s (%d)\n",i+1,(Inventory.A)[i].name,(Inventory.A)[i].count);
    }
}
