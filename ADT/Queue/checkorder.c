#include <stdio.h>
#include <stdlib.h>
#include <queue.c>

void CheckOrder (int Order, int Build, int Invoice, int Komponen){
    printf("Nomor Order: %d\n", Order);
    printf("Pemesan : %d\n", Build);
    printf("Invoice: %d\n", Invoice);
    printf("Komponen:\n");
    for (int i=0; i<LengthList(Komponen);i++){
        printf("%d. %s (%d)\n"), i+1, Nama(ListElmt(Komponen, i));
    }
}