
#include "../ADT/Mesin Karakter & Kata/mesin_kar.c"
#include "../ADT/Mesin Karakter & Kata/mesinkata.c"
#include "../ADT/Graph/graph.c"
// #include "../ADT/Array Dinamis/list.c"
//#include "../ADT/Stack/stackt.c"
//#include "../ADT/Queue/queue.c"
#include "../ADT/ADT Lain/list-statik.c"
#include <string.h>
#include "user-interface.c"
#include "stdlib.h"

int main(){
    /* ---- TAMPILAN MENU UTAMA BANGET ---- */
    clear();
    MainMenu();
    char Kata[100];
    BacaInput(Kata); // Membaca input dari user
    int length = strlen(Kata); //JANGAN DIAPUS NANTI ERROR
    // variabel Kata menyimpan hasil input
    /* INISIALISASI STRUKTUR DATA PENYIMPANAN DATA PENTING */
    MATRIKS MapMatrix; // -> Nyimpen data Peta, letak pemain, letak Customer
    Graph G; // -> Nyimpen konektivitas titik2 pada peta
    MATRIKS GraphMatrix; // -> Nyimpen Adjacency Matriks untuk titik2 pada peta
    int UangPemain; // -> Default uang pemain
    Stack Rakitan; // -> Nyimpen Rakitan yang lagi dibangun
    Stack CurrentPesanan; // -> Nyimpen stack komponen2 pesanan sekarang
    boolean lagiBuild; // -> Kalo udah startbuild-> true, klo ga false
    List InventoryPemain; // Nyimpen inventory pemain, set kosong di awal
    List ListDummy ; // Nyimpen semua data barang yang bisa dijual/diorder 
    boolean SecretShop; // Nyimpen apakah udah pernah masuk ke secret shop
    int diskon;  // Nyimpen jumlah diskon (bernilai 2 kalo secret shop dah kebuka)
    Queue AntrianPesanan; // Menyimpan antrian pesanan
    ListStatik DataDummyPesanan; // Meyimpan data dummy pesanan
    int RandomSeed=1; // Untuk kebutuhan random
    int OrderNumber; //Variable global order number

    if (strcmp(Kata,"START")==0){

        /* Kosongkan semua yang bakal dinamis / set defaults for new game */
        UangPemain = 4000;
        lagiBuild=false;
        SecretShop=false;
        InventoryPemain=MakeList();
        ListDummy= MakeList();
        CreateStackEmpty(&Rakitan);
        CreateDummies(&ListDummy);
        //PENGISIAN DATA DUMMY PEMESAN SETELAH AKUISISI JUMLAH CUSTOMER
        QCreateEmpty(&AntrianPesanan, 20);
        diskon = 1; // Diskon awal
        OrderNumber=1; //Ordernumber Awal
        
        
        /* PEMBACAAN FILE KONFIGURASI */

        STARTKATA("../ADT/Matriks/map.txt");
        //2 karena tambah ruang untuk border
        int BrsPita = 2;
        int KolPita = 2;
        //BAG 1. AKUISISI - Misal akuisisi 10 & 15 dari pita
        for (int a=0;a<CKata.Length;a++){
            char temp = CKata.TabKata[a]; // berisi nilai akuisisi
            int convert = temp - '0'; // mengubah dari char ke int
            int pangkat = Pangkat(10,CKata.Length-a-1);
            BrsPita += pangkat*convert;
        }
        ADVKATA();
        for (int b = 0;b<CKata.Length;b++){
            char temp = CKata.TabKata[b]; // berisi nilai akuisisi
            int convert = temp - '0'; // mengubah dari char ke int
            int pangkat = Pangkat(10,CKata.Length-b-1);
            KolPita += pangkat*convert;
        }
        MakeMATRIKS(BrsPita,KolPita,&MapMatrix);
        EmptyMatrix(&MapMatrix);
        
        // sampe sini baca pita AMAN

        //BAG 2. TOTAL TITIK - Misal total titik di peta ada 9
        ADVKATA();
        int TitikTotal=0;
        for (int c=1;c<CKata.Length;c++){ /* mulai dari c=1 karena Lengthnya tambah akibat ada blank*/
            char temp = CKata.TabKata[c]; // berisi nilai akuisisi
            int convert = temp - '0'; // mengubah dari char ke int
            int pangkat = Pangkat(10,CKata.Length-c-1);
            TitikTotal += pangkat*convert;
        }
        TitikTotal-=2; //karena kita mulai dari -1
        // baca titik total AMAN

        //BAG 3. PEMETAAN - Start pasang-pasang titik ke peta,
        for(int I=-1;I<=TitikTotal;I++) {
            POINT CTemp;
            ADVKATA();
            char Type = CKata.TabKata[1]; /* Bukan 0 karena indeks 0 isinya blank*/
            ADVKATA();
            int Absis=0;
            for (int d=0;d<CKata.Length;d++){
                char temp = CKata.TabKata[d]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-d-1);
                Absis += pangkat*convert;
            }
            ADVKATA();
            int Ordinat=0;
            for (int e=0;e<CKata.Length;e++){
                char temp = CKata.TabKata[e]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-e-1);
                Ordinat += pangkat*convert;
            }
            SimpanPoint(&CTemp,Absis,Ordinat,Type,I);
            if (I==-1){
                CurrentAbsis(MapMatrix)=Absis;
                CurrentOrdinat(MapMatrix)=Ordinat;
            }
            IsiPoint(&MapMatrix,CTemp);
        }
        ADVKATA(); 
        MakeZeroMatrix(&GraphMatrix,TitikTotal,TitikTotal);               

        for (int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
            for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
                if (CKata.Length == 1){
                    char temp = CKata.TabKata[0]; 
                    int konversi = temp - '0';
                    ElmtMatrix(GraphMatrix,i,j)=konversi;
                    ADVKATA();
                }
                else { // CKata.Length = 2 jika membaca baris baru (enter)
                    char temp = CKata.TabKata[1]; 
                    int konversi = temp - '0';
                    ElmtMatrix(GraphMatrix,i,j)=konversi;
                    ADVKATA();
                }
            }
        }
        initGraph(&G,TitikTotal);
        for (int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
            for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
                if (ElmtMatrix(GraphMatrix,i,j)==1){
                    AddLink(&G,i-1,j-1);
                }
            }
        }

        White;
        CreateDummiesPemesan(&DataDummyPesanan,TitikTotal-2,ListDummy);
        QAdd(&AntrianPesanan,ElmtStatik(DataDummyPesanan,RandomSeed));
        SetOrderNumber(&AntrianPesanan,OrderNumber);
        //OrderNumber++;
        DelAtStatik(&DataDummyPesanan,RandomSeed);
        //copy stack dari head q ke currentpesanan
        CopyStack(InfoHead(AntrianPesanan).komponen,&CurrentPesanan);
        int CurrentDeliveryLoc = InfoHead(AntrianPesanan).pemesan;
        POINT PointDeliveryLoc = SearchMatrix(MapMatrix,CurrentDeliveryLoc);
        
        /* ---- TAMPILAN MENU SETELAH IN-GAME ---- */
        clear();
        printf("Welcome to Santo's World...\n");
        ShowUI();
        Cyan; //set color Cyan
        // Reset isi Kata
        for (int x=0;x<100;x++){ // Reset nilai Kata supaya bisa input lag
            Kata[x] = '\0';
        }
        BacaInput(Kata);
        // Kata menyimpan hasil input
        while(strcmp(Kata,"EXIT")!=0){
            White; //set color White
            clear();
            
            /* ---- DAFTAR COMMAND UTAMA PERMAINAN ---- */
            /* COMMAND 1: MOVE */
            if (strcmp(Kata,"MOVE")==0){            
                ShowValidTargets(G,CurrentPos(MapMatrix));
                int InputTarget;
                scanf("%d",&InputTarget);
                addressGraph P1;
                P1=FirstGraph(G);
                while (InfoGraph(P1)!=CurrentPos(MapMatrix)){
                    P1=NextGraph(P1);
                }
                address AdrTarget = First(Link(P1));                
                if(InputTarget>NbElmt(Link(P1)) || InputTarget<1){
                    printf("That area is not accessible, please impute according to shown indices (1-%d).\n", NbElmt(Link(P1)));
                }
                else{
                    for (int i=1;i<InputTarget;i++){
                        AdrTarget=NextGraph(AdrTarget);
                    }
                    infotypeGraph IndexTarget;
                    IndexTarget=InfoGraph(AdrTarget);
                    Move(G,CurrentPos(MapMatrix),IndexTarget,&MapMatrix);
                    printf("You have reached ");
                    switch(CurrentPos(MapMatrix)){
                        case -1:
                            printf("your\033[0;33m Base");break;
                        case 0:
                            printf("the\033[0;32m Shop");break;
                        default:
                            printf("Customer\033[0;31m %d",CurrentPos(MapMatrix));
                    }
                    White;
                    printf(".\n");                   
                }
            }

            /* COMMAND 2 : STATUS */
            else if (strcmp(Kata,"STATUS")==0){  
                printf("Uang tersisa: $%d\n",UangPemain);
                printf("Build yang sedang dikerjakan: pesanan %d untuk Customer %d.\n", InfoHead(AntrianPesanan).orderNumber, InfoHead(AntrianPesanan).pemesan);
                printf("Lokasi: pemain sedang berada pada ");
                switch(CurrentPos(MapMatrix)){
                    case -1:
                    printf("Base");break;
                    
                    case 0:
                    printf("Shop");break;

                    default:
                    printf("Customer %d",CurrentPos(MapMatrix));
                }
                printf("\n");
                printf("Inventory anda:\n");
                TampilInventory(InventoryPemain);
            }


            /* COMMAND 3 : CHECKORDER */
            else if (strcmp(Kata,"CHECKORDER")==0){
                printf("Order Number: %d\n",OrderNumber);
                printf("Customer: Pelanggan %d\n",InfoHead(AntrianPesanan).pemesan);
                printf("Invoice: %d\n",InfoHead(AntrianPesanan).invoice);
                printf("Komponen: \n");
                PrintStack(InfoHead(AntrianPesanan).komponen);
            }

            /* COMMAND 4 : STARTBUILD */
            else if (strcmp(Kata,"STARTBUILD")==0){
                if(CurrentPos(MapMatrix)==-1){
                    /* fputs("STARTBUILD ", fsave) */
                    Qinfotype CurrentPesanan = InfoHead(AntrianPesanan);
                    STARTBUILD(&Rakitan,&lagiBuild,OrderNumber(CurrentPesanan),Pemesan(CurrentPesanan));
                }
                else{
                    printf("Return to your base to start building!\n");
                }
            }

            /* COMMAND 5 : FINISHBUILD */
            else if (strcmp(Kata,"FINISHBUILD")==0){
                if(CurrentPos(MapMatrix)==-1){
                    /* fputs("FINISHBUILD ",fsave); */
                    Qinfotype CurrentPesanan = InfoHead(AntrianPesanan);
                    FINISHBUILD(&InventoryPemain, Komponen(CurrentPesanan), Rakitan, &lagiBuild,OrderNumber(CurrentPesanan),Pemesan(CurrentPesanan));
                    QDel(&AntrianPesanan, &CurrentPesanan);
                }
                else{
                    printf("Return to your base to finish building!\n");
                }
            }

            /* COMMAND 6 : ADDCOMPONENT */
            else if(strcmp(Kata,"ADDCOMPONENT")==0){
                if(CurrentPos(MapMatrix)==-1 && lagiBuild){
                    //fputs("ADDCOMPONENT ",fsave);
                    ADDCOMPONENT(&Rakitan, &InventoryPemain, lagiBuild);
                }
                else{
                    switch(lagiBuild){
                        case true:
                        printf("Return to your base to add a component!\n");break;
                        default:
                        printf("Cannot add because no project has been started!\n");
                    }
                }                
            }
            /* COMMAND 7 : REMOVECOMPONENT */
            else if (strcmp(Kata,"REMOVECOMPONENT")==0){
                if(CurrentPos(MapMatrix)==-1 && lagiBuild){
                    REMOVECOMPONENT(&Rakitan,&InventoryPemain, lagiBuild);
                }
                else{
                    switch(lagiBuild){
                        case true:
                        printf("Return to your base to remove a component!\n");break;
                        default:
                        printf("Cannot remove because no project has been started!\n");
                    }
                    
                }
            }

    
            /* COMMAND 8 : SHOP */
            else if(strcmp(Kata,"SHOP")==0){
                if(CurrentPos(MapMatrix)==0){
                    int NoKomponen, JumlahKomponen, HitungTotal;
                    printf("Komponen yang tersedia:\n");
                    for (int i=0;i<LengthList(ListDummy);i++){
                        printf("%d. %s - $%d\n",i+1,Nama(ListElmt(ListDummy,i)),(Harga(ListElmt(ListDummy,i)))/diskon);
                    }
                    printf("Komponen yang ingin dibeli: ");
                    scanf("%d",(&NoKomponen));
                    if (NoKomponen==-999){
                        if (!SecretShop){
                            clear();
                            int Choice;
                            SecretShopIntro();
                            scanf("%d",&Choice);
                            Red;
                            if(Choice==2111){
                                diskon = 2;
                                printf("You have chosen... wisely. Come back to the shop, there's a surprise waiting for you...\n");                                
                            }
                            else{
                                printf("You have chosen... poorly. I am sorry, but there are no second chances...\n");
                            }
                            printf("I will seal this room permanently now. See you soon, computer cowboy...\n");
                            LockShop(&SecretShop);
                        }
                        else{
                            Red;
                            printf("The door is locked...\n");
                            //show failed entry ui
                        }
                        White;
                        
                    }
                    else if (NoKomponen>0 && NoKomponen<=24){
                        printf("Masukkan jumlah yang ingin dibeli: ");
                        scanf("%d",(&JumlahKomponen));
                        HitungTotal = ((Harga(ListElmt(ListDummy,NoKomponen-1))/diskon)*JumlahKomponen);
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
                        }                        
                    }
                    else{
                        printf("Enter a correct input!\n");
                    }
                }
                else{
                    printf("Move to the shop to access the shop!\n");
                }

            }

            /* COMMAND 9: DELIVER */
            else if (strcmp(Kata,"DELIVER")==0){
                //Keknya mending delivery loc diambil dari anak queue
                if(CurrentAbsis(MapMatrix)==Absis(PointDeliveryLoc) && CurrentOrdinat(MapMatrix)==Ordinat(PointDeliveryLoc)){
                    printf("Item successfully delivered to Customer %d!\n",CurrentPos(MapMatrix));
                }
                else{
                    printf("This is not the right address for your delivery!\n");
                }
            }
            /* COMMAND 10: END_DAY */
            else if (strcmp(Kata,"END_DAY")==0){
                Qinfotype X;
                QDel(&AntrianPesanan,&X);
                Yellow;
                printf("Santo shuts his eyelids and started counting sheep... 1...2...\n\n");
                printf("A new day has arrived, the sun has risen again.\n");
                Green;
                printf("Today is not just another day. It is a new opportunity, another chance, a new beginning.\n");
                RandomSeed=AvoidCollision(DataDummyPesanan,RandomSeed,TitikTotal,ListDummy);
                QAdd(&AntrianPesanan,ElmtStatik(DataDummyPesanan,RandomSeed));
                SetOrderNumber(&AntrianPesanan,OrderNumber);
                IncrementOrderNumber(&OrderNumber);
                DelAtStatik(&DataDummyPesanan,RandomSeed);
                CreateStackEmpty(&CurrentPesanan);
                CopyStack(InfoHead(AntrianPesanan).komponen,&CurrentPesanan);
                
                White;
            }

            /* COMMAND 11: SAVE */
            else if (strcmp(Kata,"SAVE")==0){
                static FILE * fsave;
                fsave = fopen("save.txt","w"); // isi save.txt teroverwrite dengan kondisi pemain terakhir
                /* Append UangPemain, Build, dan Order */
                char Uang[100];
                sprintf(Uang,"%d ",UangPemain);
                const char* konvertuang = Uang;
                fputs(konvertuang,fsave);
                /* bagian build belom ada jadi dikomentari dulu
                char Bangun[100];
                sprintf(Bangun,"%d ",Build);
                const char* konvertbangun = Bangun;
                fputs(konvertbangun,fsave);
                char pesanan[100];
                sprintf(pesanan,"%d ",Order);
                const char* konvertpesanan = pesanan;
                fputs(konvertpesanan,fsave);
                */
                /* Append current absis dan ordinat */
                char CAbsis[100];
                char COrdinat[100];
                sprintf(CAbsis,"%d ",CurrentAbsis(MapMatrix));
                sprintf(COrdinat,"%d ",CurrentOrdinat(MapMatrix));
                const char* konvertabsis = CAbsis;
                const char* konvertordinat = COrdinat;
                fputs(konvertabsis,fsave);
                fputs(konvertordinat,fsave);
                /* Append Rakitan */
                Stack copyrakit;
                CreateStackEmpty(&copyrakit);
                CopyStack(Rakitan,&copyrakit); // Mengcopy stack Rakitan
                InverseStack(&copyrakit); // Supaya yang disave itu adalah yang paling bawah stack terlebih dahulu
                ElTypeList komponenrakit;
                int i;
                for (i = Top(copyrakit); i >= 0; i--){
                    Pop(&copyrakit, &komponenrakit);
                    const char* komp = Nama(komponenrakit);
                    fputs(komp,fsave);
                    fputs(";",fsave); // Kasih titik koma antar komponen
                }
                fputs(".",fsave); // Tambahkan mark supaya tau akhir dari stack rakitan
                /* Append Queue pesanan */
                ElTypeList komponenqueue;
                int j;
                const char* kompqueue;
                if (!IsQEmpty(AntrianPesanan)){ // Jika queue tidak empty, berarti ada pesanan
                    /* Simpan nilai head queue */
                    Stack copyqueue;
                    CreateStackEmpty(&copyqueue);
                    CopyStack((InfoHead(AntrianPesanan).komponen),&copyqueue);
                    InverseStack(&copyqueue);
                    for (i = Top(copyqueue); i >= 0; i--){ // Simpan stack komponen untuk pesanan
                        Pop(&copyqueue, &komponenqueue);
                        kompqueue = Nama(komponenqueue);
                        fputs(kompqueue,fsave);
                        fputs(";",fsave); // Kasih titik koma antar komponen
                    }
                    fputs(".",fsave); // penanda sudah akhir dari stack
                    char inv[100]; // simpan invoice
                    sprintf(inv,"%d ",(InfoHead(AntrianPesanan).invoice));
                    const char* konvertinv = inv;
                    fputs(konvertinv,fsave);
                    char pmsn[100]; // simpan pemesan
                    sprintf(pmsn,"%d ",(InfoHead(AntrianPesanan).pemesan));
                    const char* konvertpmsn = pmsn;
                    fputs(konvertpmsn,fsave);
                    char ordN[100]; // simpan orderNumber
                    sprintf(ordN,"%d ",(InfoHead(AntrianPesanan).orderNumber));
                    const char* konvertordN = ordN;
                    fputs(konvertordN,fsave);
                    if (QNBElmt(AntrianPesanan)>1){ // Jika queue lebih dari 1 pesanan
                        for (i = Head(AntrianPesanan)+1; i <= Tail(AntrianPesanan); i++){
                            for (int x=0;x<100;x++){ // Reset semua nilai inv, pmsn, dan ordN supaya bisa diisi lagi
                                inv[x] = '\0';
                                pmsn[x] = '\0';
                                ordN[x] = '\0';
                            }
                            CreateStackEmpty(&copyqueue); // Mereset isi stack copyqueue supaya bisa diisi ulang
                            CopyStack(((AntrianPesanan).T[i].komponen),&copyqueue);
                            InverseStack(&((AntrianPesanan).T[i].komponen));
                            for (j = Top(((AntrianPesanan).T[i].komponen)); j >= 0; j--){ // Simpan stack komponen
                                Pop(&((AntrianPesanan).T[i].komponen), &komponenqueue);
                                kompqueue = Nama(komponenqueue);
                                fputs(kompqueue,fsave);
                                fputs(";",fsave); // Kasih titik koma antar komponen
                            }
                            fputs(".",fsave); // penanda sudah akhir dari stack
                            // simpan invoice
                            sprintf(inv,"%d ",((AntrianPesanan).T[i].invoice));
                            const char* konvertinv = inv;
                            fputs(konvertinv,fsave);
                            // simpan pemesan
                            sprintf(pmsn,"%d ",((AntrianPesanan).T[i].pemesan));
                            const char* konvertpmsn = pmsn;
                            fputs(konvertpmsn,fsave);
                            // simpan orderNumber
                            sprintf(ordN,"%d ",((AntrianPesanan).T[i].orderNumber));
                            const char* konvertordN = ordN;
                            fputs(konvertordN,fsave);
                         }
                    }
                }
                /* Append lagiBuild*/
                if (lagiBuild == true){
                    fputs("true ",fsave);
                }
                else{ // lagiBuild == false
                    fputs("false ",fsave);
                }
                /* Append SecretShop */
                if (SecretShop == true){
                    fputs("true ",fsave);
                }
                else{ // SecretShop == false
                    fputs("false ",fsave);
                }
                /* Append Inventory Pemain */
                const char *appendnama;
                char tempjumlah[10];
                const char *appendjumlah;
                for (int i=0;i<LengthList(InventoryPemain);i++){
                    if (Jumlah(ListElmt(InventoryPemain,i))>0){
                        appendnama = Nama(ListElmt(InventoryPemain,i));
                        fputs(appendnama,fsave);
                        fputs(";",fsave); // Beri spasi antara nama barang dan jumlahnya
                        sprintf(tempjumlah, "%d ", Jumlah(ListElmt(InventoryPemain,i)));
                        appendjumlah = tempjumlah;
                        fputs(appendjumlah,fsave);
                        for (int x=0;x<10;x++){ // Reset semua nilai tempjumlah supaya bisa diisi lagi
                            tempjumlah[x] = '\0';
                        }
                    }
                }
                /* Tambahan mark di akhir untuk menandakan akhir file */
                fputs(".",fsave);
                printf("Lokasi save file:");
                printf("C/User/Documents/GitHub/tubes-alstrukdat-kel2/ADT/Mesin Karakter & Kata/save.txt\n");
                printf("Game berhasil di save!\n");
                fclose(fsave);
            }
            /* COMMAND 12: MAP */
            else if (strcmp(Kata,"MAP")==0){   
                PrintMap(MapMatrix); //AMAN
            
            }
            /* WRONG INPUT */
            else{
                printf("Input Anda salah!\n");
            }
            ShowUI();
            Cyan;
            for (int x=0;x<100;x++){ // Reset semua nilai Kata supaya bisa input lagi
                Kata[x] = '\0';
            }
            RandomSeed++;
            BacaInput(Kata);
            // Kata menyimpan hasil input             
        }
        
        White;
        printf("Thank you for playing!\n");
        


    }
    
    return 0;
}
