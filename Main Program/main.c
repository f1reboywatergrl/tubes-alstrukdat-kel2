
#include "../ADT/Mesin Karakter & Kata/mesin_kar.c"
#include "../ADT/Mesin Karakter & Kata/mesinkata.c"
#include "../ADT/Graph/graph.c"
// #include "../ADT/Array Dinamis/list.c"
#include "../ADT/Stack/stackt.c"

#include <string.h>
#include "user-interface.c"
#include "stdlib.h"

int main(){
    /* ---- TAMPILAN MENU UTAMA BANGET ---- */
    system("cls");
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
    int diskon; 
    diskon = 1; // Diskon awal

    if (strcmp(Kata,"START")==0){

        /* Kosongkan semua yang bakal dinamis / set defaults for new game */
        UangPemain = 4000;
        lagiBuild=false;
        SecretShop=false;
        InventoryPemain=MakeList();
        ListDummy= MakeList();
        CreateStackEmpty(&Rakitan);
        CreateDummies(&ListDummy);
        
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
        int CurrentDeliveryLoc = 3;
        POINT PointDeliveryLoc = SearchMatrix(MapMatrix,CurrentDeliveryLoc);
        White;


        
        /* ---- TAMPILAN MENU SETELAH IN-GAME ---- */
        system("cls");
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
            system("cls");
            
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
                int Build = 3; //Ambil dari Queue
                int Order = 1; //nanti variablenya disesuain sm yg lain
                int length = 2; //Contoh contoh contoh
                
                // List InventoryPemain = MakeList(); //BUAT DUMMY DOANG
                // for (int i=0;i<length;i++){
                //     ElTypeList ElInventory = InputLElType();
                //     InsertLAt(&InventoryPemain,ElInventory,i);
                // }

                printf("Uang tersisa: $%d\n",UangPemain);
                printf("Build yang sedang dikerjakan: pesanan %d untuk Customer %d.\n", Order, Build);
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
                int Order = 3;
                int Pemesan = 1;
                int Invoice = 0;
                Stack S;
                ElTypeList X;

                CopyStack(CurrentPesanan, &S);
                while (!IsStackEmpty(S)){
                    Pop(&S, &X);
                    Invoice += X.harga;
                }
                printf("Nomor Order: %d\n", Order);
                printf("Pemesan: %d\n", Pemesan);
                printf("Invoice: %d\n", Invoice);
                printf("Komponen:");

                PrintStack(CurrentPesanan);
            }

            /* COMMAND 4 : STARTBUILD */
            else if (strcmp(Kata,"STARTBUILD")==0){
                if(CurrentPos(MapMatrix)==-1){
                    /* fputs("STARTBUILD ", fsave) */
                    STARTBUILD(&Rakitan,&lagiBuild,1,2);
                }
                else{
                    printf("Return to your base to start building!\n");
                }
            }

            /* COMMAND 5 : FINISHBUILD */
            else if (strcmp(Kata,"FINISHBUILD")==0){
                if(CurrentPos(MapMatrix)==-1){
                    /* fputs("FINISHBUILD ",fsave); */
                    FINISHBUILD(&InventoryPemain, CurrentPesanan, Rakitan, &lagiBuild,1,2);
                }
                else{
                    printf("Return to your base to finish building!\n");
                }
            }

            /* COMMAND 6 : ADDCOMPONENT */
            else if(strcmp(Kata,"ADDCOMPONENT")==0){
                if(CurrentPos(MapMatrix)==-1 && lagiBuild){
                    //fputs("ADDCOMPONENT ",fsave);
                    ADDCOMPONENT(&Rakitan, &InventoryPemain);
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
                    //fputs("REMOVECOMPONENT ",fsave);
                    REMOVECOMPONENT(&Rakitan,&InventoryPemain);
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
                            system("cls");
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
                    //harusnya ada Dequeue disini
                }
                else{
                    printf("This is not the right address for your delivery!\n");
                }
            }
            /* COMMAND 10: END_DAY */
            else if (strcmp(Kata,"END_DAY")==0){
                //harusnya ada Enqueue disini
            }

            /* COMMAND 11: SAVE */
            else if (strcmp(Kata,"SAVE")==0){
                static FILE * fsave;
                fsave = fopen("save.txt","w"); // isi save.txt teroverwrite dengan kondisi pemain terakhir
                /* Append UangPemain */
                char Uang[100];
                sprintf(Uang,"%d ",UangPemain);
                const char* konvertuang = Uang;
                fputs(konvertuang,fsave);
                /* Append Rakitan */
                InverseStack(&Rakitan); // Supaya yang disave itu adalah yang paling bawah stack terlebih dahulu
                ElTypeList komponen;
                int i;
                for (i = Top(Rakitan); i >= 0; i--){
                    Pop(&Rakitan, &komponen);
                    const char* komp = Nama(komponen);
                    fputs(komp,fsave);
                    fputs(" ",fsave); // Kasih blank antar komponen
                }
                /* harusnya simpen Queue pesanan di sini*/
                /* Append lagiBuild*/
                /*
                char buildchar = Convert.ToChar(lagiBuild); // Mengubah kata 'true'/'false' dari boolean ke string
                const char* buildcchar = buildchar;
                fputs(buildcchar,fsave);
                fputs(" ",fsave); // Tambah blank untuk memisahkan kata
                /* 
                List InventoryPemain; // Nyimpen inventory pemain, set kosong di awal
                List ListDummy ; // Nyimpen semua data barang yang bisa dijual/diorder 
                boolean SecretShop; // Nyimpen apakah udah pernah masuk ke secret shop
                printf("Lokasi save file:");
                printf("C/User/Documents/GitHub/tubes-alstrukdat-kel2/ADT/Mesin Karakter & Kata/save.txt\n");
                printf("Game berhasil di save!\n");
                fclose(fsave);
                */
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
            BacaInput(Kata);
            // Kata menyimpan hasil input             
        }
        
        White;
        printf("Thank you for playing!\n");
        


    }
    
    return 0;
}
