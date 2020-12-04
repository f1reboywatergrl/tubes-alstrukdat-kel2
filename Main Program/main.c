
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
    char Kata[100];
    BacaInput(Kata); // Membaca input dari user
    int length = strlen(Kata); //JANGAN DIAPUS NANTI ERROR
    while ((strncmp(Kata,"START",5)!=0) && (strncmp(Kata,"LOAD",4)!=0)){
        printf("Please enter a valid input!\n");
        for (int x=0;x<100;x++){ // reset nilai Kata
            Kata[x] = '\0';
        }
        BacaInput(Kata);
    }
    White; //set color White
    clear();
    if (strncmp(Kata,"START",5)==0){ // Hanya membandingkan 5 karakter pertama dari Kata
        /* Kosongkan semua yang bakal dinamis / set defaults for new game */
        UangPemain = 4000;
        lagiBuild=false;
        SecretShop=false;
        InventoryPemain=MakeList();
        CreateStackEmpty(&Rakitan);
        //PENGISIAN DATA DUMMY PEMESAN SETELAH AKUISISI JUMLAH CUSTOMER
        QCreateEmpty(&AntrianPesanan, 20);
        diskon = 1; // Diskon awal
        OrderNumber=1; //Ordernumber Awal
        /* Ini ketika New game: */
        QAdd(&AntrianPesanan,ElmtStatik(DataDummyPesanan,RandomSeed));
        SetOrderNumber(&AntrianPesanan,OrderNumber);
        IncrementNumber(&OrderNumber);
        DelAtStatik(&DataDummyPesanan,RandomSeed);
        printf("Welcome to Santo's World!\n");
    }
    else if (strncmp(Kata,"LOAD",4)==0){
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
        char temp = CKata.TabKata[0]; // langsung 0 karena current pos tidak bisa lebih dari 1 digit
        int convert = temp - '0'; // mengubah dari char ke int
        POINT P = SearchMatrix(MapMatrix,convert); // dari posisi pelanggan/base/shop didapat koordinat
        CurrentAbsis(MapMatrix) = Absis(P);
        CurrentOrdinat(MapMatrix) = Ordinat(P);

        // LagiBuild
        ADVKATA();
        if (strncmp(CKata.TabKata,"true",4)){ // true
            lagiBuild = true;
        }   
        else{ // false
            lagiBuild = false;
        }

        // Secret Shop
        ADVKATA();
        if (strncmp(CKata.TabKata,"false",5)==0){
            SecretShop = true;
        }
        else{
            SecretShop = false;
        }
        ADVKATA();
        // Diskon
        if (CKata.TabKata[0] == '1'){
            diskon = 1;
        }
        else if (CKata.TabKata[0] == '2'){
            diskon = 2;
        }
        // RAKITAN
        IgnoreBlank();
        ElTypeList listtemp;
        CreateStackEmpty(&Rakitan);
        while (CC != MARK){
            int i = 0;
            while (CC != ';') {
                CKata.TabKata[i] = CC;
                CKata.TabKata[i+1] = '\0';
                ADV();
                i++;
            } 
            CKata.Length = i;
            printf("%s\n",CKata.TabKata);
            listtemp.nama = CKata.TabKata;
            printf("%s\n",listtemp.nama);
            ADV(); // Memajukkan CC sekali karena CC sekarang berada di ';'
            ADVKATA();
            int price = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                price += pangkat*convert;
            }
            listtemp.harga = price;
            listtemp.jumlah = 1; // Jumlah komponen pada rakitan pasti 1
            ADVKATA();
            int category = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                category += pangkat*convert;
            }
            listtemp.kategori = category;
            Push(&Rakitan,listtemp);
            IgnoreBlank();
        }
        ADV(); // Maju satu karakter dari rakitan ke queue antrianpesanan
        // Queue Pesanan
        // Ambil listtemp dari rakitan
        Qinfotype tempqinfo;
        QCreateEmpty(&AntrianPesanan, 20);
        Stack komptemp; // Menyimpan komponen untuk pesanan yang sedang diakuisisi
        CreateStackEmpty(&komptemp);
        while (CC != MARK){
            while (CC != '/'){
                int i = 0;
                while (CC != ';') {
                    CKata.TabKata[i] = CC;
                    CKata.TabKata[i+1] = '\0';
                    ADV();
                    i++;
                } 
                CKata.Length = i;
                printf("%s\n",CKata.TabKata);
                listtemp.nama = CKata.TabKata;
                printf("%s\n",listtemp.nama);
                ADV(); // Memajukkan CC sekali karena CC sekarang berada di ';'
                ADVKATA();
                int price = 0;
                for (int a=0;a<CKata.Length;a++){
                    char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                    int convert = temp - '0'; // mengubah dari char ke int
                    int pangkat = Pangkat(10,CKata.Length-a-1);
                    price += pangkat*convert;
                }
                listtemp.harga = price;
                listtemp.jumlah = 1; // Jumlah komponen pada pesanan pasti 1
                ADVKATA();
                int category = 0;
                for (int a=0;a<CKata.Length;a++){
                    char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                    int convert = temp - '0'; // mengubah dari char ke int
                    int pangkat = Pangkat(10,CKata.Length-a-1);
                    category += pangkat*convert;
                }
                listtemp.kategori = category;
                Push(&komptemp,listtemp);
                IgnoreBlank(); // Hanya ignore blank saja, tapi tidak mengakusisi kata yang ditemukan
                }
            Komponen(tempqinfo) = komptemp; // Simpan stack komponen
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
            IgnoreBlank(); // Hanya ignore blank saja, tapi tidak mengakusisi kata yang ditemukan
            CreateStackEmpty(&komptemp); // Reset ulang isi stack supaya bisa dipakai lagi
            OrderNumber = ordN + 1; // Saat keluar dari loop, OrderNumber untuk pesanan selanjutnya pada program adalah OrderNumber pesanan di akhir queue + 1
        }
        // Saat keluar, maka OrderNumber sudah berisi OrderNumber pesanan pada akhir queue + 1
        ADV(); // Supaya CC tidak di mark dan sekarang berada di inventory
        // Inventory
        InventoryPemain=MakeList();
        ElTypeList listtemp2;
        // Pakai listtemp lagi sebagai ElTypeList
        while (CC != MARK){
            int i = 0;
            while (CC != ';') {
                CKata.TabKata[i] = CC;
                CKata.TabKata[i+1] = '\0';
                ADV();
                i++;
            } 
            CKata.Length = i;
            printf("%s\n",CKata.TabKata);
            listtemp2.nama = CKata.TabKata;
            printf("%s\n",listtemp2.nama);
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
            listtemp2.harga = price;
            ADVKATA();
            // akuisisi jumlah
            int amount = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                amount += pangkat*convert;
            }
            listtemp2.jumlah = amount; 
            ADVKATA();
            // akuisisi kategori
            int category = 0;
            for (int a=0;a<CKata.Length;a++){
                char temp = CKata.TabKata[a]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                int pangkat = Pangkat(10,CKata.Length-a-1);
                category += pangkat*convert;
            }
            listtemp2.kategori = category;
            InsertLLast(&InventoryPemain,listtemp2);
            IgnoreBlank();
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
        Kata[x] = '\0';
    }
    BacaInput(Kata);
    // Kata menyimpan hasil input
    while(strcmp(Kata,"EXIT")!=0){
        White;
        clear();
        /* ---- DAFTAR COMMAND UTAMA PERMAINAN ---- */
        /* COMMAND 1: MOVE */
        if (strcmp(Kata,"MOVE")==0){           
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
                White;
                printf(".\n");                   
            }
        }

        /* COMMAND 2 : STATUS */
        else if (strcmp(Kata,"STATUS")==0){ 
            Green; 
            printf("Money: $%d\n",UangPemain);
            Yellow;
            if(!IsQEmpty(AntrianPesanan)){
                printf("Current build: Order #%d for Customer %d.", OrderNumber(CurrentPesanan), Pemesan(CurrentPesanan));
                if(!lagiBuild){
                    printf(" (This build hasn't been started yet. Impute STARTBUILD at your base to start it!)");
                }
                printf("\n");
                }
            else{
                printf("No new orders available.\n");
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
        else if (strcmp(Kata,"CHECKORDER")==0){
            if(!IsQEmpty(AntrianPesanan)){
                printf("Order Number: %d\n",OrderNumber(CurrentPesanan));
                printf("Customer: Pelanggan %d\n",Pemesan(CurrentPesanan));
                printf("Invoice: %d\n",Invoice(CurrentPesanan));
                printf("Required components: \n");
                PrintStack(Komponen(CurrentPesanan));                    
            }
            else{
                printf("Currently not doing any builds. End the day to receive a new order!\n");
            }
        }

        /* COMMAND 4 : STARTBUILD */
        else if (strcmp(Kata,"STARTBUILD")==0){
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
        else if (strcmp(Kata,"FINISHBUILD")==0){
            if(CurrentPos(MapMatrix)==-1){
                Qinfotype HasilDequeue;
                if(FINISHBUILD(&InventoryPemain, &Komponen(CurrentPesanan), Rakitan, &lagiBuild, OrderNumber(CurrentPesanan),Pemesan(CurrentPesanan), Invoice(CurrentPesanan))){
                    QDel(&AntrianPesanan, &HasilDequeue);
                    CurrentPesanan = InfoHead(AntrianPesanan);
                }
            }
            else{
                printf("Return to your base to finish building!\n");
            }
        }

        /* COMMAND 6 : ADDCOMPONENT */
        else if(strcmp(Kata,"ADDCOMPONENT")==0){
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
        else if (strcmp(Kata,"DELIVER")==0){
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
                printf("Tidak ada");
            }
            else{
                printf("Order #%d successfully delivered to Customer %d!\n", Kategori(ListElmt(InventoryPemain,i)) ,CurrentPos(MapMatrix));
                UangPemain += Harga(ListElmt(InventoryPemain,i));
            }
        }
        /* COMMAND 10: END_DAY */
        else if (strcmp(Kata,"END_DAY")==0){
            // Buat Kepentingan debug
            // Qinfotype X;
            // QDel(&AntrianPesanan,&X);
            EndDayMessage();

            /* Ngambil dari List Statik secara random, jika hasil random adalah variasi yang udah pernah diambil, dia akan cari
            sampe ketemu yang belom keambil. Kalo udah keambil semua, di reset
            Kemudian akan di enqueue ke antrian pesanan. */
            RandomSeed=AvoidCollision(DataDummyPesanan,RandomSeed,TitikTotal-2,ListDummy);
            QAdd(&AntrianPesanan,ElmtStatik(DataDummyPesanan,RandomSeed));
            SetOrderNumber(&AntrianPesanan,OrderNumber);
            IncrementNumber(&OrderNumber);
            DelAtStatik(&DataDummyPesanan,RandomSeed);
            
            White;
        }

        /* COMMAND 11: SAVE */
        else if (strncmp(Kata,"SAVE",4)==0){
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
                char hrg[100]; // simpan harga komponen
                sprintf(hrg,"%d ",Harga(komponenrakit));
                const char* converthrg = hrg;
                fputs(converthrg,fsave);
                char ktg[100]; // simpan kategori komponen
                sprintf(ktg,"%d ",Kategori(komponenrakit));
                const char* convertktg = ktg;
                fputs(convertktg,fsave);
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
                    char hrg[100]; // simpan harga komponen
                    sprintf(hrg,"%d ",Harga(komponenqueue));
                    const char* converthrg = hrg;
                    fputs(converthrg,fsave);
                    char ktg[100]; // simpan kategori komponen
                    sprintf(ktg,"%d ",Kategori(komponenqueue));
                    const char* convertktg = ktg;
                    fputs(convertktg,fsave);
                }
                fputs("/",fsave); // penanda sudah akhir dari stack
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
                            char hrg[100]; // simpan harga komponen
                            sprintf(hrg,"%d ",Harga(komponenqueue));
                            const char* converthrg = hrg;
                            fputs(converthrg,fsave);
                            char ktg[100]; // simpan kategori komponen
                            sprintf(ktg,"%d ",Kategori(komponenqueue));
                            const char* convertktg = ktg;
                            fputs(convertktg,fsave);
                        }
                        fputs("/",fsave); // penanda sudah akhir dari stack
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
                    appendnama = Nama(ListElmt(InventoryPemain,i));
                    fputs(appendnama,fsave);
                    fputs(";",fsave); // Beri spasi antara nama barang dan jumlahnya
                    sprintf(tempharga,"%d ",Harga(ListElmt(InventoryPemain,i)));
                    const char* convertharga = tempharga;
                    fputs(convertharga,fsave);
                    sprintf(tempjumlah, "%d ", Jumlah(ListElmt(InventoryPemain,i)));
                    appendjumlah = tempjumlah;
                    fputs(appendjumlah,fsave);
                    sprintf(tempkat,"%d ",Kategori(ListElmt(InventoryPemain,i)));
                    const char* convertkat = tempkat;
                    fputs(convertkat,fsave);
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
        else if (strcmp(Kata,"MAP")==0){   
            PrintMap(MapMatrix); 
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
        IncrementNumber(&RandomSeed);
        BacaInput(Kata);
        // Kata menyimpan hasil input             
    }
    White;
    printf("Thank you for playing!\n");
    return 0; 
}
