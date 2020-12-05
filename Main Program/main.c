
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
    // variabel Kata menyimpan hasil input
    /* INISIALISASI STRUKTUR DATA PENYIMPANAN DATA PENTING */
    /* DATA STATIK YANG GA BAKAL BERUBAH */
    MATRIKS MapMatrix; // -> Nyimpen data Peta, letak pemain, letak Customer
    Graph G; // -> Nyimpen konektivitas titik2 pada peta
    MATRIKS GraphMatrix; // -> Nyimpen Adjacency Matriks untuk titik2 pada peta
    /* DATA DINAMIS YANG BERUBAH KETIKA SAVE/LOAD */
    int UangPemain; // -> Default uang pemain
    Stack Rakitan; // -> Nyimpen Rakitan yang lagi dibangun
    Qinfotype CurrentPesanan; // -> Nyimpen pesanan sekarang
    boolean lagiBuild; // -> Kalo udah startbuild-> true, klo ga false
    List InventoryPemain; // Nyimpen inventory pemain, set kosong di awal
    List ListDummy ; // Nyimpen semua data barang yang bisa dijual/diorder 
    boolean SecretShop; // Nyimpen apakah udah pernah masuk ke secret shop
    int diskon;  // Nyimpen jumlah diskon (bernilai 2 kalo secret shop dah kebuka)
    Queue AntrianPesanan; // Menyimpan antrian pesanan
    ListStatik DataDummyPesanan; // Meyimpan data dummy pesanan
    int RandomSeed=1; // Untuk kebutuhan random, Sebenernya bodo amat save/engga keknya hehe
    int OrderNumber; //Variable global order number
    /* Generate kombinasi pesanan yang mungkin dalam List Statik (di luar start/load) */
    

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
        if (Type(CTemp)=='B'){
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
    SaveLinks(GraphMatrix,&G);
    ListDummy= MakeList();
    CreateDummies(&ListDummy);
    CreateDummiesPemesan(&DataDummyPesanan,TitikTotal-2,ListDummy);
    // Input
    char InputKata[100];
    BacaInput(InputKata); // Membaca input dari user
    int length = strlen(InputKata); //JANGAN DIAPUS NANTI ERROR
    while ((strncmp(InputKata,"START",5)!=0) && (strncmp(InputKata,"LOAD",4)!=0)){
        printf("Please enter a valid input!\n");
        for (int x=0;x<100;x++){ // reset nilai Kata
            InputKata[x] = '\0';
        }
        BacaInput(InputKata);
    }
    White; //set color White
    clear();
    InventoryPemain=MakeList();
    CreateStackEmpty(&Rakitan);
    QCreateEmpty(&AntrianPesanan, 10);
    if (strncmp(InputKata,"START",5)==0){ // Hanya membandingkan 5 karakter pertama dari Kata
        /* Kosongkan semua yang bakal dinamis / set defaults for new game */
        UangPemain = 4000;
        lagiBuild=false;
        SecretShop=false;
        //PENGISIAN DATA DUMMY PEMESAN SETELAH AKUISISI JUMLAH CUSTOMER
        diskon = 1; // Diskon awal
        OrderNumber=1; //Ordernumber Awal
        /* Ini ketika New game: */
        QAdd(&AntrianPesanan,ElmtStatik(DataDummyPesanan,RandomSeed));
        SetOrderNumber(&AntrianPesanan,OrderNumber);
        OrderNumber ++;
        DelAtStatik(&DataDummyPesanan,RandomSeed);
        RandomSeed++;
        printf("Welcome to Santo's World!\n");
    }
    else if (strncmp(InputKata,"LOAD",4)==0){
        STARTKATA("save.txt");
        // Uang Pemain
        UangPemain = 0;
        for (int a=0;a<CKata.Length;a++){
            char temp = CKata.TabKata[a]; // berisi nilai akuisisi
            int convert = temp - '0'; // mengubah dari char ke int
            int pangkat = Pangkat(10,CKata.Length-a-1);
            UangPemain += pangkat*convert;
        }
        ADVKATA();
        // Current Position
        char temp;
        int convert;
        if (CKata.TabKata[0] == '-'){ // di base
            convert = -1;
        }
        else{ // selain base
            temp = CKata.TabKata[0]; // langsung 0 karena current pos tidak bisa lebih dari 1 digit
            convert = temp - '0'; // mengubah dari char ke int
        }
        POINT P = SearchMatrix(MapMatrix,convert); // dari posisi pelanggan/base/shop didapat koordinat
        CurrentAbsis(MapMatrix) = Absis(P);
        CurrentOrdinat(MapMatrix) = Ordinat(P);
        // LagiBuild
        ADVKATA();
        if (strncmp(CKata.TabKata,"true",4)==0){ // true
            lagiBuild = true;
        }   
        else{ // false
            lagiBuild = false;
        }

        // Secret Shop
        ADVKATA();
        if (strncmp(CKata.TabKata,"false",5)==0){
            SecretShop = false;
        }
        else{
            SecretShop = true;
        }
        ADVKATA();
        // Diskon
        if (CKata.TabKata[0] == '1'){
            diskon = 1;
        }
        else if (CKata.TabKata[0] == '2'){
            diskon = 2;
        }
        // OrderNumber
        ADVKATA();
        OrderNumber = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                OrderNumber += pangkat*convert;
            }
        // RAKITAN
        ADVKATA();
        ElTypeList listtemp;
        while (CC != MARK){
            int i = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                i += pangkat*convert;
            }
            /*
            while (CC != ';') {
                CKata.TabKata[i] = CC;
                CKata.TabKata[i+1] = '\0';
                ADV();
                i++;
            } 
            */
            Push(&Rakitan, ListElmt(ListDummy,i));
            /*
            char nama[100];
            for (int x=0;x<100;x++){
                nama[x] = CKata.TabKata[x];
            } 
            ADV(); // Memajukkan CC sekali karena CC sekarang berada di ';'
            ADVKATA();
            int price = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                price += pangkat*convert;
            }
            ADVKATA();
            int category = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                category += pangkat*convert;
            }
            */
            // CreateElmtLengkap(&listtemp,price,nama,category,1); // Jumlah komponen pada pesanan pasti 1
            // Push(&Rakitan,listtemp);
            ADVKATA();
        }
        ADV(); // Maju satu karakter dari rakitan ke queue antrianpesanan
        // Queue Pesanan
        // Ambil listtemp dari rakitan
        ADVKATA();
        Qinfotype tempqinfo;
        Stack komptemp; // Menyimpan komponen untuk pesanan yang sedang diakuisisi
        ElTypeList listtemp1;
        CreateStackEmpty(&komptemp);        
        while (CC != MARK){
            while (CC != MARK){
                int i = 0;
                for (int a=0;a<CKata.Length;a++){
                    char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                    int convert = temp - '0'; // mengubah dari char ke int
                    int pangkat = Pangkat(10,CKata.Length-a-1);
                    i += pangkat*convert;
                }
                Push(&komptemp,ListElmt(ListDummy,i));
                /*Kata nama;
                //char nama[100];
                printf("Sebelom Push\n");
                //printf("HARUSNYA KOSONG => %s\n",nama);
                PrintStack(komptemp);
                printf("\n\n");
                //sampe sini masih bener            
                int i = 0;
                while (CC != ';') {
                    CKata.TabKata[i] = CC;
                    CKata.TabKata[i+1] = '\0';
                    ADV();
                    i++;
                } 
                CKata.Length = i;
                printf("%s\n",CKata.TabKata);
                //Stack masih bener


                //Salahnya disini

                for (int x = 0;x<100;x++){
                    nama[x] = '\0';
                }
                printf("Sebelom Push - Baris 278\n");
                //Ketika kelar dari sini^, stacknya jadi blank semua
                printf("%d\n", InfoTop(komptemp).harga);
                PrintStack(komptemp);
                printf("\n\n"); 
                //printf("Nama Komponen Queue = %s\n",nama);                
                for (int x=0;x<CKata.Length;x++){
                    nama.TabKata[x] = CKata.TabKata[x];
                }
                // printf("%s\n",nama);
                PrintStack(komptemp);
                printf("\n\n"); 
                // Ketika kelar dari sini^, stack yang lama ke-overwrite


                ADV(); // Memajukkan CC sekali karena CC sekarang berada di ';'
                printf("%c\n",CC);
                nama.Length=0;
                ADVKATA();
                int price = 0;
                for (int a=0;a<CKata.Length;a++){
                    char tempQ = CKata.TabKata[a]; // berisi nilai akuisisi
                    int convertQ = tempQ - '0'; // mengubah dari char ke int
                    int pangkat = Pangkat(10,CKata.Length-a-1);
                    price += pangkat*convertQ;
                }
                //printf("Nama Komponen Queue 2 = %s\n",nama);
                nama.Length=0;
                ADVKATA();
                int category = 0;
                for (int a=0;a<CKata.Length;a++){
                    char tempQ = CKata.TabKata[a]; // berisi nilai akuisisi
                    int convertQ = tempQ - '0'; // mengubah dari char ke int
                    int pangkat = Pangkat(10,CKata.Length-a-1);
                    category += pangkat*convertQ;
                }
                
                CreateElmtLengkap(&listtemp1,price,nama.TabKata,category,0); // Jumlah komponen pada pesanan pasti 0
                printf("Nama, Price, Category Komponen = %s, %d, %d\n",Nama(listtemp1),Harga(listtemp1),Kategori(listtemp1));
                PrintStack(komptemp);
                Push(&komptemp,listtemp1);
                printf("%d\n", komptemp.T[Top(komptemp)-1].harga);
                printf("\nSesudah Push\n\n");
                PrintStack(komptemp);
                printf("\n");*/
                ADVKATA(); // Hanya ignore blank saja, tapi tidak mengakusisi kata yang ditemukan
            }
            Komponen(tempqinfo) = komptemp;
            /*
            for (int x=Top(komptemp);x>-1;x--){
                Pop(&komptemp,&listtemp1);
                printf("%s", listtemp1.nama);
                Push(&(tempqinfo.komponen),listtemp1);
            }
            */
            ADV(); // Maju satu karakter karena CC sekarang ada di '/'
            // Sekarang ada di karakter pertama invoice
            ADVKATA();
            // akuisisi invoice
            int inv = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                inv += pangkat*convert;
            }
            Invoice(tempqinfo) = inv;
            ADVKATA();
            // akuisisi pemesan
            int pmsn  = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                pmsn += pangkat*convert;
            }
            Pemesan(tempqinfo) = pmsn;
            ADVKATA();
            // akuisisi orderNumber
            int ordN  = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                ordN += pangkat*convert;
            }
            OrderNumber(tempqinfo) = ordN;
            QAdd(&AntrianPesanan,tempqinfo); // pesanan yang sudah diakuisisi dimasukkan dalam queue
            ADVKATA(); // Hanya ignore blank saja, tapi tidak mengakusisi kata yang ditemukan
            MakeStackEmpty(&komptemp); // Reset ulang isi stack supaya bisa dipakai lagi
            OrderNumber = ordN + 1; // Saat keluar dari loop, OrderNumber untuk pesanan selanjutnya pada program adalah OrderNumber pesanan di akhir queue + 1
        }
        // Saat keluar, maka OrderNumber sudah berisi OrderNumber pesanan pada akhir queue + 1
        ADV(); // Supaya CC tidak di mark dan sekarang berada di inventory
        ADVKATA();
        // Inventory
        ElTypeList listtemp2;
        while (CC != MARK){
            /*
            int i = 0;
            while (CC != ';') {
                CKata.TabKata[i] = CC;
                CKata.TabKata[i+1] = '\0';
                ADV();
                i++;
            }
            */
           int i = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                i += pangkat*convert;
            }
            listtemp2 = ListElmt(ListDummy,i); //i -> akuisisi indeks
            ADVKATA();
            int j = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                j += pangkat*convert;
            }

            IsiJumlah(&listtemp2,j); //j -> akuisisi jumlah
            // CKata.Length = i;
            /*
            char nama[100];
            for (int x=0;x<100;x++){
                nama[x] = CKata.TabKata[x];
            } 
            int panjang = strlen(nama);
            ADV(); // Memajukkan CC sekali karena CC sekarang berada di ';'
            ADVKATA();
            // akuisisi harga
            int price = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                price += pangkat*convert;
            }
            ADVKATA();
            // akuisisi jumlah
            int amount = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                amount += pangkat*convert;
            }
            ADVKATA();
            // akuisisi kategori
            int category = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                category += pangkat*convert;
            }*/
            // CreateElmtLengkap(&listtemp2,price,nama,category,amount);
            InsertLLast(&InventoryPemain,listtemp2);
            ADVKATA();
        }
        // Sudah selesai akuisisi inventory
        ADV(); // Supaya CC maju dari MARK, dan sekarang berada di index datadummy
        ADVKATA();
        // Mengubah invoice dari DataDummy dengan index yanag diakuisisi menjadi -999
        while (CC != MARK){
            int indeks = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                indeks += pangkat*convert;
            }
            ElmtStatik(DataDummyPesanan,indeks).invoice = ValUndefStatik;
            ADVKATA();
        }
        Green;
        printf("Game successfully loaded!\n");
        White;
        printf("Welcome back to Santo's World!\n");
    }
    /* ---- END OF FUNGSI LOAD ---- */
    //inisiasi current pesanan
    CurrentPesanan = InfoHead(AntrianPesanan);
    
    /* ---- TAMPILAN MENU SETELAH IN-GAME ---- */
    ShowUI();
    Cyan; //set color Cyan
    // Reset isi Kata
    for (int x=0;x<100;x++){ // Reset nilai Kata supaya bisa input lag
        InputKata[x] = '\0';
    }
    BacaInput(InputKata);
    // Kata menyimpan hasil input
    while(strcmp(InputKata,"EXIT")!=0){
        White;
        clear();
        /* ---- DAFTAR COMMAND UTAMA PERMAINAN ---- */
        /* COMMAND 1: MOVE */
        if (strcmp(InputKata,"MOVE")==0){           
            ShowValidTargets(G,CurrentPos(MapMatrix));
            int InputTarget;
            scanf("%d",&InputTarget);
            addressGraph P1=SearchGraph(G,CurrentPos(MapMatrix));
            address AdrTarget = First(Link(P1));
            while(InputTarget>NbElmt(Link(P1)) || InputTarget<0){
                clear();
                printf("That area is not accessible, please impute according to shown indices (1-%d) or cancel by imputing 0.\n", NbElmt(Link(P1)));
                ShowValidTargets(G,CurrentPos(MapMatrix));
                scanf("%d",&InputTarget);
            }                
            if (InputTarget==0){
                printf("Decided to stay.\n");
            }
            else{
                //Maju sebanyak input number, buat cari target move
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
                printf(".\n"); 
                White;            
            }
        }

        /* COMMAND 2 : STATUS */
        else if (strcmp(InputKata,"STATUS")==0){ 
            Green; 
            printf("Money: $%d\n",UangPemain);
            Yellow;
            if(lagiBuild){
                printf("Current build: Order #%d for Customer %d.\n", OrderNumber(CurrentPesanan), Pemesan(CurrentPesanan));
            }
            else{
                printf("Not currently building any orders.\n");
            }
            printf("You are currently located at ");
            switch(CurrentPos(MapMatrix)){
                case -1:
                IBlue;printf("your Base");break;
                
                case 0:
                Green;printf("the Shop");break;

                default:
                Red;printf("Customer %d's place",CurrentPos(MapMatrix));
            }
            White;
            printf("\n");
            printf("Inventory:\n");
            TampilInventory(InventoryPemain);
        }


        /* COMMAND 3 : CHECKORDER */
        else if (strcmp(InputKata,"CHECKORDER")==0){
            if(lagiBuild){
                printf("Order Number: %d\n",OrderNumber(CurrentPesanan));
                printf("Customer: Pelanggan %d\n",Pemesan(CurrentPesanan));
                printf("Invoice: %d\n",Invoice(CurrentPesanan));
                printf("Required components: \n");
                PrintStack(Komponen(CurrentPesanan));                                  
            }
            else{
                Yellow;
                printf("Currently not doing any builds.");
                if(IsQEmpty(AntrianPesanan)){
                    printf(" End the day to receive a new order!\n");
                }
                else{
                    printf(" Impute STARTBUILD at your base to start building!\n");
                }
                White;
            }
        }

        /* COMMAND 4 : STARTBUILD */
        else if (strcmp(InputKata,"STARTBUILD")==0){
            if(CurrentPos(MapMatrix)==-1){
                if(IsQEmpty(AntrianPesanan)){
                    printf("You do not have any order to start. End the day to receive a new order!\n");
                }
                else{
                    STARTBUILD(&Rakitan,&lagiBuild,OrderNumber(CurrentPesanan),Pemesan(CurrentPesanan));
                }
            }
            else{
                printf("Return to your base to start building!\n");
            }
        }

        /* COMMAND 5 : FINISHBUILD */
        else if (strcmp(InputKata,"FINISHBUILD")==0){
            if(CurrentPos(MapMatrix)==-1){
                Qinfotype HasilDequeue;
                if(FINISHBUILD(&InventoryPemain, &Komponen(CurrentPesanan), Rakitan, &lagiBuild, OrderNumber(CurrentPesanan),Pemesan(CurrentPesanan), Invoice(CurrentPesanan))){
                    MakeStackEmpty(&Rakitan);
                    QDel(&AntrianPesanan, &HasilDequeue);
                    if(!IsQEmpty(AntrianPesanan)){
                        CurrentPesanan = InfoHead(AntrianPesanan);
                    }
                    
                }
            }
            else{
                printf("Return to your base to finish building!\n");
            }
        }

        /* COMMAND 6 : ADDCOMPONENT */
        else if(strcmp(InputKata,"ADDCOMPONENT")==0){
            if(CurrentPos(MapMatrix)==-1 && lagiBuild){
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
        else if (strcmp(InputKata,"REMOVECOMPONENT")==0){
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
        else if(strcmp(InputKata,"SHOP")==0){
            if(CurrentPos(MapMatrix)==0){
                int NoKomponen, JumlahKomponen, HitungTotal;
                printf("Available components:\n");
                for (int i=0;i<LengthList(ListDummy);i++){
                    printf("%d. %s - $%d\n",i+1,Nama(ListElmt(ListDummy,i)),(Harga(ListElmt(ListDummy,i)))/diskon);
                }
                printf("Buy which component? : ");
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
                    }
                    White;
                    
                }
                else if (NoKomponen>0 && NoKomponen<=24){
                    printf("Enter component amount: ");
                    scanf("%d",(&JumlahKomponen));
                    HitungTotal = ((Harga(ListElmt(ListDummy,NoKomponen-1))/diskon)*JumlahKomponen);
                    if (HitungTotal > UangPemain){
                        printf("Not enough cash!\n");
                    }
                    else{
                        UangPemain = UangPemain-HitungTotal;
                        printf("Component bought successfully!\n");
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
        else if (strcmp(InputKata,"DELIVER")==0){
            boolean found = false;
            int i = 0;
            while (found == false && i<LengthList(InventoryPemain))
            {
                if ((Jumlah(ListElmt(InventoryPemain,i)) == CurrentPos(MapMatrix)) && (strncmp(Nama(ListElmt(InventoryPemain,i)),"RAKITAN",7)==0) && (Jumlah(ListElmt(InventoryPemain,i))!=0))
                {
                    Jumlah(ListElmt(InventoryPemain,i)) = 0;
                    found = true;
                }
                else{
                    
                    i++;
                }
            }
            if (!found){
                printf("Wrong address for delivery! Re-check your inventory!\n");
            }
            else{
                printf("Order #%d successfully delivered to Customer %d!\n", Kategori(ListElmt(InventoryPemain,i)) ,CurrentPos(MapMatrix));
                UangPemain += Harga(ListElmt(InventoryPemain,i));
            }
        }
        /* COMMAND 10: END_DAY */
        else if (strcmp(InputKata,"END_DAY")==0){
            // Buat Kepentingan debug
            // Qinfotype X;
            // QDel(&AntrianPesanan,&X);
            EndDayMessage();

            /* Ngambil dari List Statik secara random, jika hasil random adalah variasi yang udah pernah diambil, dia akan cari
            sampe ketemu yang belom keambil. Kalo udah keambil semua, di reset
            Kemudian akan di enqueue ke antrian pesanan. */
            if(!IsQFull(AntrianPesanan)){
                RandomSeed=AvoidCollision(DataDummyPesanan,RandomSeed,TitikTotal-2,ListDummy);
                QAdd(&AntrianPesanan,ElmtStatik(DataDummyPesanan,RandomSeed));
                SetOrderNumber(&AntrianPesanan,OrderNumber);
                IncrementNumber(&OrderNumber);
                DelAtStatik(&DataDummyPesanan,RandomSeed);
                if(QNBElmt(AntrianPesanan)==1){
                    CurrentPesanan = InfoHead(AntrianPesanan);
                }
                // PrintTail(AntrianPesanan);
                //                 
            }
            else{
                printf("However, your waiting list is full. Finish at least an order to receive new orders!\n");
            }
            
            White;
        }

        /* COMMAND 11: SAVE */
        else if (strncmp(InputKata,"SAVE",4)==0){
            static FILE * fsave;
            fsave = fopen("save.txt","w"); // isi save.txt teroverwrite dengan kondisi pemain terakhir
            /* Append UangPemain, Build, dan Order */
            char Uang[100];
            sprintf(Uang,"%d ",UangPemain);
            const char* konvertuang = Uang;
            fputs(konvertuang,fsave);
            
            /* Append current position*/
            char Cpos[100];
            sprintf(Cpos,"%d ",CurrentPos(MapMatrix));
            const char* konvertcpos = Cpos;
            fputs(konvertcpos,fsave);
            /* Append lagiBuild*/
            if (lagiBuild == true){
                fputs("true ",fsave);
            }
            else{ // lagiBuild == false
                fputs("false ",fsave);
            }
            /* Append SecretShop & Diskon */
            if (SecretShop == true){
                fputs("true ",fsave);
            }
            else{ // SecretShop == false
                fputs("false ",fsave);
            }
            char disc[100]; // simpan harga komponen
            sprintf(disc,"%d ",diskon);
            const char* convertdisc = disc;
            fputs(convertdisc,fsave);
            /* Append OrderNumber*/
            char ordNumber[100]; // simpan harga komponen
            sprintf(ordNumber,"%d ",OrderNumber);
            const char* convertordNumber = ordNumber;
            fputs(convertordNumber,fsave);
            /* Append Rakitan */
            Stack copyrakit;
            CreateStackEmpty(&copyrakit);
            CopyStack(Rakitan,&copyrakit); // Mengcopy stack Rakitan
            InverseStack(&copyrakit); // Supaya yang disave itu adalah yang paling bawah stack terlebih dahulu
            ElTypeList komponenrakit;
            int i;
            for (i = Top(copyrakit); i >= 0; i--){
                Pop(&copyrakit, &komponenrakit); 
                Harga(komponenrakit) = Harga(SearchElTypeList(ListDummy,Nama(komponenrakit),0));
                /* const char* komp = Nama(komponenrakit);
                fputs(komp,fsave);
                fputs(";",fsave); // Kasih titik koma antar komponen
                */
                char hrg[100]; // simpan harga komponen
                sprintf(hrg,"%d ",Harga(komponenrakit));
                const char* converthrg = hrg;
                fputs(converthrg,fsave);
                /*
                char ktg[100]; // simpan kategori komponen
                sprintf(ktg,"%d ",Kategori(komponenrakit));
                const char* convertktg = ktg;
                fputs(convertktg,fsave);
                */
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
                    Harga(komponenqueue) = Harga(SearchElTypeList(ListDummy,Nama(komponenqueue),0));
                    char hrg[100]; // simpan harga komponen
                    sprintf(hrg,"%d ",Harga(komponenqueue));
                    const char* converthrg = hrg;
                    fputs(converthrg,fsave);
                    /*
                    char ktg[100]; // simpan kategori komponen
                    sprintf(ktg,"%d ",Kategori(komponenqueue));
                    const char* convertktg = ktg;
                    fputs(convertktg,fsave);
                    */
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
                            Harga(komponenqueue) = Harga(SearchElTypeList(ListDummy,Nama(komponenqueue),0));
                            char hrg[100]; // simpan harga komponen
                            sprintf(hrg,"%d ",Harga(komponenqueue));
                            const char* converthrg = hrg;
                            fputs(converthrg,fsave);
                            /*
                            char ktg[100]; // simpan kategori komponen
                            sprintf(ktg,"%d ",Kategori(komponenqueue));
                            const char* convertktg = ktg;
                            fputs(convertktg,fsave);
                            */
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
            fputs(".",fsave); // Penanda sudah selesai simpan queue pesanan
            
            /* Append Inventory Pemain */
            const char *appendnama;
            char tempharga[100]; // simpan harga komponen
            char tempjumlah[100];
            char tempkat[100]; // simpan kategori komponen
            const char *appendjumlah;
            for (int i=0;i<LengthList(InventoryPemain);i++){
                if (Jumlah(ListElmt(InventoryPemain,i))>0){
                    /*
                    appendnama = Nama(ListElmt(InventoryPemain,i));
                    fputs(appendnama,fsave);
                    fputs(";",fsave); // Beri spasi antara nama barang dan jumlahnya
                    */
                    ElTypeList ItemInventory = SearchElTypeList(ListDummy,Nama(ListElmt(InventoryPemain,i)),Jumlah(ListElmt(InventoryPemain,i)));
                    sprintf(tempharga,"%d ",Harga(ItemInventory));
                    const char* convertharga = tempharga;
                    fputs(convertharga,fsave);
                    sprintf(tempjumlah, "%d ", Jumlah(ItemInventory));
                    appendjumlah = tempjumlah;
                    fputs(appendjumlah,fsave);
                    /*
                    sprintf(tempkat,"%d ",Kategori(ListElmt(InventoryPemain,i)));
                    const char* convertkat = tempkat;
                    fputs(convertkat,fsave);
                    */
                    for (int x=0;x<100;x++){ // Reset semua nilai temp supaya bisa diisi lagi
                        tempharga[x] = '\0';
                        tempjumlah[x] = '\0';
                        tempkat[x] = '\0';
                    }
                }
            }
            fputs(".",fsave); // Penanda akhir dari inventory
            /* Append indeks data dummies untuk pesanan yang memiliki invoice -999 */
            char idx[100]; // simpan index
            for (int p = 0;p<27;p++){
                if (ElmtStatik(DataDummyPesanan,p).invoice==ValUndefStatik){ // Jika invoice untku seed/index p itu -999
                    sprintf(idx,"%d ",p);
                    const char* konvertidx = idx;
                    fputs(konvertidx,fsave);
                }
                idx[0] = '\0'; // Reset nilai idx
                idx[1] = '\0'; // Reset nilai idx
            }
            /* Tambahan mark di akhir untuk menandakan akhir file */
            fputs(".",fsave);
            printf("Savefile location:");
            printf("C/User/Documents/GitHub/tubes-alstrukdat-kel2/ADT/Mesin Karakter & Kata/save.txt\n");
            printf("Game successfully saved!\n");
            fclose(fsave);
        }
        /* COMMAND 12: MAP */
        else if (strcmp(InputKata,"MAP")==0){   
            PrintMap(MapMatrix); 
        }
        /* WRONG INPUT */
        else{
            printf("Input Anda salah!\n");
        }
        ShowUI();
        Cyan;
        for (int x=0;x<100;x++){ // Reset semua nilai Kata supaya bisa input lagi
            InputKata[x] = '\0';
        }
        RandomSeed = (RandomSeed+1) %27;
        BacaInput(InputKata);
        // Kata menyimpan hasil input             
    }
    White;
    printf("Thank you for playing!\n");
    return 0; 
}
