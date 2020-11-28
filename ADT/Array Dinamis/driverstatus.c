#include "status.c"

int main(){
    int UangPemain = 4000; //Asumsi awal uang//
    int Build = 3; //Ambil dari Queue
    int Order = 1; //nanti variablenya disesuain sm yg lain
    int Lokasi = -1; // Ini nanti disesuain sama hasil dari move?, contoh doang
    int length = 3; //Contoh contoh contoh
    
    List Inventory = MakeList();
    for (int i=0;i<length;i++){
        ElTypeList ElInventory = InputLElType();
        InsertLAt(&Inventory,ElInventory,i);
    }
    TulisIsiList(Inventory);
    Status(UangPemain, Build, Order, Inventory, Lokasi);
    return 0;
}
