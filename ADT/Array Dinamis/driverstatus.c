#include "status.c"

int main(){
    int uang = 4000; //Asumsi awal uang//
    int pelanggan = 1; //nanti variablenya disesuain sm yg lain
    int order = 1; //nanti variablenya disesuain sm yg lain
    char lokasi[100] = "base"; // Ini nanti disesuain sama hasil dari move?, contoh doang
    int length = 3; //Contoh contoh contoh

    List Inventory = MakeList();
    for (int i=0;i<length;i++){
        ElType ElInventory = InputElType();
        InsertAt(&Inventory,ElInventory,i);
    }
    Status(uang, pelanggan, order, Inventory, lokasi);
    return 0;
}
