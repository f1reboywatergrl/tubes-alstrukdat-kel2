#include "status.c"

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
    if (HitungTotal > UangPemain){
        printf("Uang tidak cukup!\n");
    }
    else{
        UangPemain = UangPemain-HitungTotal;
        printf("Komponen berhasil dibeli!\n");
        ElTypeList elinventory;
        boolean Found = false;
        for (int i=0;i<LengthList(InventoryPemain);i++){
            if(Nama(ListElmt(ListDummy,NoKomponen-1)),(Nama(ListElmt(InventoryPemain,NoKomponen-1))==0)){
                Found = true;
                Jumlah(ListElmt(InventoryPemain,NoKomponen-1)) = Jumlah(ListElmt(InventoryPemain,NoKomponen-1))+JumlahKomponen;
            }
            else{
                CreateElmtLengkap(&elinventory,Harga(ListElmt(ListDummy,NoKomponen-1)),Nama(ListElmt(ListDummy,NoKomponen-1)),Kategori(ListElmt(ListDummy,NoKomponen-1)),JumlahKomponen);
                InsertLLast(&InventoryPemain,elinventory);
            }
        }

        CreateElmt(&elinventory,300,"CPU",1);
        InsertLLast(&InventoryPemain,elinventory);
        TampilInventory(InventoryPemain);
    }

    return 0;
}