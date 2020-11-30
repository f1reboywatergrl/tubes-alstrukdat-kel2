
#include "../ADT/Mesin Karakter & Kata/mesin_kar.c"
#include "../ADT/Mesin Karakter & Kata/mesinkata.c"
#include "../ADT/Graph/graph.c"
// #include "../ADT/Array Dinamis/list.c"
#include "../ADT/Stack/stackt.c"

#include "string.h"
#include "user-interface.c"
#include "stdlib.h"

int main(){
    /* ---- TAMPILAN MENU UTAMA BANGET ---- */
    system("cls");
    static FILE * fsave;
    fsave = fopen("save.txt","a");
    char InputCommand[100];
    MainMenu();
    scanf("%s",InputCommand);
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

    if (strcmp(InputCommand,"START")==0){

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
        scanf("%s",InputCommand);
        while(strcmp(InputCommand,"EXIT")!=0){
            White; //set color White
            system("cls");
            
            /* ---- DAFTAR COMMAND UTAMA PERMAINAN ---- */
            /* COMMAND 1: MOVE */
            if (strcmp(InputCommand,"MOVE")==0){            
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
                    fputs("MOVE ",fsave); // Menyimpan command ke save file
                    // Save input perpindahan lokasi ke save file
                    char input[3];
                    sprintf(input,"%d ",InputTarget); // Mengubah int menjadi char
                    // "%d " membuat ada spasi di input
                    const char* p = input; // mengubah char ke const char* supaya menjadi parameter fputs
                    fputs(p,fsave);
                    // Selesai disave
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
            else if (strcmp(InputCommand,"STATUS")==0){  
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
            else if (strcmp(InputCommand,"CHECKORDER")==0){
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
            else if (strcmp(InputCommand,"STARTBUILD")==0){
                if(CurrentPos(MapMatrix)==-1){
                    /* fputs("STARTBUILD ", fsave) */
                    STARTBUILD(&Rakitan,&lagiBuild,1,2);
                }
                else{
                    printf("Return to your base to start building!\n");
                }
            }

            /* COMMAND 5 : FINISHBUILD */
            else if (strcmp(InputCommand,"FINISHBUILD")==0){
                if(CurrentPos(MapMatrix)==-1){
                    /* fputs("FINISHBUILD ",fsave); */
                    FINISHBUILD(&InventoryPemain, CurrentPesanan, Rakitan, &lagiBuild,1,2);
                }
                else{
                    printf("Return to your base to finish building!\n");
                }
            }

            /* COMMAND 6 : ADDCOMPONENT */
            else if(strcmp(InputCommand,"ADDCOMPONENT")==0){
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
            else if (strcmp(InputCommand,"REMOVECOMPONENT")==0){
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
            else if(strcmp(InputCommand,"SHOP")==0){
                if(CurrentPos(MapMatrix)==0){
                    int NoKomponen, JumlahKomponen, HitungTotal;
                    printf("Komponen yang tersedia:\n");
                    PrintStore(ListDummy);
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
                                printf("You have chosen... wisely. Come back to the shop, there's a surprise waiting for you...\n");
                                
                                //fungsi discount 
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
                    else if (NoKomponen<0 || NoKomponen>24){
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
            else if (strcmp(InputCommand,"DELIVER")==0){
                //Keknya mending delivery loc diambil dari anak queue
                if(CurrentAbsis(MapMatrix)==Absis(PointDeliveryLoc) && CurrentOrdinat(MapMatrix)==Ordinat(PointDeliveryLoc)){
                    /* fputs("DELIVER ",fsave); */
                    printf("Item successfully delivered to Customer %d!\n",CurrentPos(MapMatrix));
                    //harusnya ada Enqueue disini
                }
                else{
                    printf("This is not the right address for your delivery!\n");
                }
            }

            /* COMMAND 11: SAVE */
            else if (strcmp(InputCommand,"SAVE")==0){
                fputs(". ",fsave); // akhir dari program yang disave ditandai mark
                printf("Lokasi save file:");
                printf("C/User/Documents/GitHub/tubes-alstrukdat-kel2/ADT/Mesin Karakter & Kata/save.txt\n");
                printf("Game berhasil di save!\n");
            }
            /* COMMAND 12: MAP */
            else if (strcmp(InputCommand,"MAP")==0){   
                PrintMap(MapMatrix); //AMAN
            
            }
            /* WRONG INPUT */
            else{
                printf("Input Anda salah!\n");
            }
            ShowUI();
            Cyan;
            scanf("%s",InputCommand);       
        }
        
        White;
        fclose(fsave);
        printf("Thank you for playing!\n");
        


    }
    return 0;
}
