//#include "stackt.c"
#include "../Queue/queue.c"

/*
1. Motherboard Micro-ATX (0)
2. Motherboard Mini ITX (0)
3. Motherboard E-ATX (0)

4. Processor Intel i3 (0)  
5. Processor Intel i5 (0)  
6. Processor Intel i7 (0)
  
7. RAM 4GB (0)
8. RAM 8GB (0)
9. RAM 16GB (0)

10. Heatsink (0)
11. Liquid Cooler (0)
12. Dry Ice Cooler (0)

13. Plastic (0)
14. Metal (0)
15. Carbon Fiber (0)

16. NVDIA NV3 (0)
17. NVDIA NV4 (0)
18. NVDIA GEFORCE (0)

19. 512GB (0)
20. 1TB (0)
21. 2TB (0)

22. Power Supply AT (0)
23. Power Supply ATX (0)
24. Power Supply BTX (0)
*/

int main(){
   
    List inventory = MakeList();
    CreateDummies(&inventory);

    /*
    ElTypeList El;      Nama(El) = "A";     Kategori(El) = 1;       Jumlah(El) = 1;     Harga(El)=5000;
    ElTypeList El2;     Nama(El2) = "B";    Kategori(El2) = 2;      Jumlah(El2) = 1;    Harga(El2)=5000;
    ElTypeList El3;     Nama(El3) = "C";    Kategori(El3) = 3;      Jumlah(El3) = 1;    Harga(El3)=5000;
    ElTypeList El4;     Nama(El4) = "D";    Kategori(El4) = 4;      Jumlah(El4) = 1;    Harga(El4)=5000;
    ElTypeList El5;     Nama(El5) = "E";    Kategori(El5) = 5;      Jumlah(El5) = 1;    Harga(El5)=5000;
    ElTypeList El6;     Nama(El6) = "F";    Kategori(El6) = 6;      Jumlah(El6) = 1;    Harga(El6)=5000;
    ElTypeList El7;     Nama(El7) = "G";    Kategori(El7) = 7;      Jumlah(El7) = 1;    Harga(El7)=5000;
    ElTypeList El8;     Nama(El8) = "H";    Kategori(El8) = 8;      Jumlah(El8) = 1;    Harga(El8)=5000;
 

    InsertLLast(&inventory,El);
    InsertLLast(&inventory,El2);
    InsertLLast(&inventory,El3);
    InsertLLast(&inventory,El4);
    InsertLLast(&inventory,El5);
    InsertLLast(&inventory,El6);
    InsertLLast(&inventory,El7);
    InsertLLast(&inventory,El8);
*/
    printf("Isi inventory: \n");
    PrintInventory(inventory);
    //TulisIsiList(inventory);
    boolean lagiBuild = false;
    int NoPesanan = 1;
    int NoPelanggan = 2;

    Jumlah(ListElmt(inventory,0))=4;
    Jumlah(ListElmt(inventory,3))=4;
    Jumlah(ListElmt(inventory,6))=4;
    Jumlah(ListElmt(inventory,9))=4;
    Jumlah(ListElmt(inventory,12))=4;
    Jumlah(ListElmt(inventory,15))=4;
    Jumlah(ListElmt(inventory,18))=4;
    Jumlah(ListElmt(inventory,21))=4;


    Stack Pesanan;
    CreateStackEmpty(&Pesanan);
    Push(&Pesanan, ListElmt(inventory,0));
    Push(&Pesanan, ListElmt(inventory,3));
    Push(&Pesanan, ListElmt(inventory,6));
    Push(&Pesanan, ListElmt(inventory,9));
    Push(&Pesanan, ListElmt(inventory,12));
    Push(&Pesanan, ListElmt(inventory,15));
    Push(&Pesanan, ListElmt(inventory,18));
    Push(&Pesanan, ListElmt(inventory,21));

    Queue Q;
    QCreateEmpty (&Q, 10);
    
    Qinfotype isipesanan;
    isipesanan.invoice = 100000;
    isipesanan.pemesan = 1;
    isipesanan.orderNumber = 1;
    isipesanan.komponen = Pesanan;

    QAdd (&Q, isipesanan);
    QAdd (&Q, isipesanan);
    QAdd (&Q, isipesanan);

    Stack Rakitan;
    CreateStackEmpty(&Rakitan);

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    printf("\n");

    Qinfotype CurrentPesanan = InfoHead(Q);
    STARTBUILD(&Rakitan,&lagiBuild,OrderNumber(CurrentPesanan),Pemesan(CurrentPesanan));
    printf("\n");

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");

    ADDCOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");

    
    REMOVECOMPONENT(&Rakitan, &inventory, lagiBuild);
    PrintStack(Rakitan);
    printf("\n");
    
    FINISHBUILD(&inventory, &Komponen(CurrentPesanan), Rakitan, &lagiBuild,OrderNumber(CurrentPesanan),Pemesan(CurrentPesanan),Invoice(CurrentPesanan));
    QDel(&Q, &CurrentPesanan);
    PrintStack(Rakitan);
    
    /*
    Stack Rakitan;
    CreateStackEmpty(&Rakitan);

    List inventory = MakeList();
    ElTypeList El;      Nama(El) = "A";     Kategori(El) = 1;       Jumlah(El) = 1;     Harga(El)=5000;
    ElTypeList El2;     Nama(El2) = "B";    Kategori(El2) = 2;      Jumlah(El2) = 1;    Harga(El2)=5000;
    InsertLLast(&inventory,El);
    InsertLLast(&inventory,El2);
    ADDCOMPONENT(&Rakitan, &inventory);
*/

    return 0;
}