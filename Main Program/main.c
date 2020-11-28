
#include "../ADT/Mesin Karakter & Kata/mesin_kar.c"
#include "../ADT/Mesin Karakter & Kata/mesinkata.c"
#include "../ADT/Graph/graph.c"

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
    if (strcmp(InputCommand,"START")==0){
        /* PEMBACAAN FILE KONFIGURASI */
        MATRIKS M2;
        STARTKATA("../ADT/Matriks/map.txt");
        //2 karena tambah ruang untuk border
        int BrsPita = 2;
        int KolPita = 2;
        //BAG 1. AKUISISI - Misal akuisisi 10 & 15 dari pita
        for (int a=0;a<CKata.Length;a++){
            char temp = CKata.TabKata[a]; // berisi nilai akuisisi
            int convert = temp - '0'; // mengubah dari char ke int
            BrsPita += pow(10,CKata.Length-a-1)*convert;
        }
        ADVKATA();
        for (int b = 0;b<CKata.Length;b++){
            char temp = CKata.TabKata[b]; // berisi nilai akuisisi
            int convert = temp - '0'; // mengubah dari char ke int
            KolPita += pow(10,CKata.Length-b-1)*convert;
        }
        MakeMATRIKS(BrsPita,KolPita,&M2);
        EmptyMatrix(&M2);
        
        // sampe sini baca pita AMAN

        //BAG 2. TOTAL TITIK - Misal total titik di peta ada 9
        ADVKATA();
        int TitikTotal=0;
        for (int c=1;c<CKata.Length;c++){ /* mulai dari c=1 karena Lengthnya tambah akibat ada blank*/
            char temp = CKata.TabKata[c]; // berisi nilai akuisisi
            int convert = temp - '0'; // mengubah dari char ke int
            TitikTotal += pow(10,CKata.Length-c-1)*convert;
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
                Absis += pow(10,CKata.Length-d-1)*convert;
            }
            ADVKATA();
            int Ordinat=0;
            for (int e=0;e<CKata.Length;e++){
                char temp = CKata.TabKata[e]; // berisi nilai akuisisi
                int convert = temp - '0'; // mengubah dari char ke int
                Ordinat += pow(10,CKata.Length-e-1)*convert;
            }
            SimpanPoint(&CTemp,Absis,Ordinat,Type,I);
            if (I==-1){
                CurrentAbsis(M2)=Absis;
                CurrentOrdinat(M2)=Ordinat;
            }
            IsiPoint(&M2,CTemp);
        }
        ADVKATA();                
        Graph G;
        MATRIKS GraphMatrix;
        MakeMATRIKS(TitikTotal,TitikTotal,&GraphMatrix);
        for(int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
            for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
                Elmt(GraphMatrix,i,j)=0;
            }
        }
        GenerateStaticAdjacency(&GraphMatrix);
        initGraph(&G,TitikTotal);
        for (int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
            for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
                if (Elmt(GraphMatrix,i,j)==1){
                    AddLink(&G,i-1,j-1);
                }
            }
        }
        int CurrentDeliveryLoc = 3;
        POINT PointDeliveryLoc = SearchMatrix(M2,CurrentDeliveryLoc);
        White;


        
        /* ---- TAMPILAN MENU SETELAH IN-GAME ---- */
        system("cls");
        printf("Selamat datang! Silahkan pilih input Anda:\n");
        ShowUI();
        Cyan; //set color Cyan
        scanf("%s",InputCommand);
        while(strcmp(InputCommand,"EXIT")!=0){
            White; //set color White
            system("cls");
            
            /* ---- DAFTAR COMMAND UTAMA PERMAINAN ---- */
            /* COMMAND 1: MOVE */
            if (strcmp(InputCommand,"MOVE")==0){            
                
                ShowValidTargets(G,CurrentPos(M2));
                int InputTarget;
                scanf("%d",&InputTarget);
                addressGraph P1;
                P1=FirstGraph(G);
                while (InfoGraph(P1)!=CurrentPos(M2)){
                    P1=NextGraph(P1);
                }
                address AdrTarget = First(Link(P1));                
                if(InputTarget>NbElmt(Link(P1)) || InputTarget<1){
                    printf("That area is not accessible, please impute according to shown indices (1-%d).\n", NbElmt(Link(P1)));
                }
                else{
                    for (int i=1;i<InputTarget;i++){
                        AdrTarget=Next(AdrTarget);
                    }
                    infotype IndexTarget;
                    IndexTarget=Info(AdrTarget);
                    Move(G,CurrentPos(M2),IndexTarget,&M2);
                    printf("You have reached ");
                    switch(CurrentPos(M2)){
                        case -1:
                            printf("your\033[0;33m Base");break;
                        case 0:
                            printf("the\033[0;32m Shop");break;
                        default:
                            printf("Pelanggan\033[0;31m %d",CurrentPos(M2));break;
                    }
                    White;
                    printf(".\n");                   
                }
            }

            /* COMMAND 9: DELIVER */
            else if (strcmp(InputCommand,"DELIVER")==0){
                if(CurrentAbsis(M2)==Absis(PointDeliveryLoc) && CurrentOrdinat(M2)==Ordinat(PointDeliveryLoc)){
                    printf("Item successfully delivered to Pelanggan %d!\n",CurrentPos(M2));
                    //harusnya ada Dequeue disini
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
                fputs("MAP ",fsave); // Menyimpan command dalam file save
                
                PrintMap(M2); //AMAN
            
            }
            /* WRONG INPUT */
            else{
                printf("Input Anda salah!\n");
            }
            printf("Silahkan pilih input Anda selanjutnya: \n");
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
