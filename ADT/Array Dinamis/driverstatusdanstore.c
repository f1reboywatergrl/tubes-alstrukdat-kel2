#include "status.c"
#include "string.h"


int main(){
    List InventoryPemain = MakeList();
    int NoKomponen, JumlahKomponen, HitungTotal;
    int UangPemain = 4500;
    List ListDummy = MakeList();
    CreateDummies(&ListDummy);
    printf("Komponen yang tersedia:\n");
    PrintStore(ListDummy);
    printf("Komponen yang ingin dibeli: ");
    scanf("%d",(&NoKomponen));
    printf("Masukkan jumlah yang ingin dibeli: ");
    scanf("%d",(&JumlahKomponen));
    HitungTotal = (Harga(ListElmt(ListDummy,NoKomponen-1))*JumlahKomponen);
    TampilInventory(InventoryPemain);
    if (HitungTotal > UangPemain){
        printf("Uang tidak cukup!\n");
    }
    else{
        UangPemain = UangPemain-HitungTotal;
        printf("Komponen berhasil dibeli!\n");
        ElTypeList elinventory;
        boolean Found = false;
        for (int i=0;i<(LengthList(InventoryPemain));i++){
            if(strcmp((Nama(ListElmt(InventoryPemain,i))),(Nama(ListElmt(ListDummy,NoKomponen-1))))==0)
            {
                Found = true;
                Jumlah(ListElmt(InventoryPemain,i)) = Jumlah(ListElmt(InventoryPemain,i))+JumlahKomponen;
             }
        }
        if (!Found){
            CreateElmtLengkap(&elinventory,Harga(ListElmt(ListDummy,NoKomponen-1)),Nama(ListElmt(ListDummy,NoKomponen-1)),Kategori(ListElmt(ListDummy,NoKomponen-1)),JumlahKomponen);
            InsertLLast(&InventoryPemain,elinventory);
        }


        int Build = 3; //Ambil dari Queue
        int Order = 1; //nanti variablenya disesuain sm yg lain
        int length = 2; //Contoh contoh contoh
                
        printf("\n");
        printf("Uang tersisa: $%d\n",UangPemain);
        printf("Build yang sedang dikerjakan: pesanan %d untuk Customer %d.\n", Order, Build);
        printf("Lokasi: pemain sedang berada pada ");

        printf("\n");
        printf("Inventory anda:\n");
        int j = 1;
        TampilInventory(InventoryPemain);
    }
    return 0;
}