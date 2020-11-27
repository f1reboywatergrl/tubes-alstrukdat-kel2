#include "ADT/Matriks/matriks.c"
#include "ADT/Mesin Karakter & Kata/mesin_kar.c"
#include "ADT/Mesin Karakter & Kata/mesinkata.c"
#include "string.h"

int main(){
    char InputCommand[100];
    printf("Selamat datang! Silahkan pilih input Anda:\n");
    printf("\033[0;32m"); //set color Green
    printf("MAP ");
    printf("\033[0;31m"); //set color Red
    printf("EXIT");
    
    printf("\033[0;36m\n"); //set color Cyan
    scanf("%s",InputCommand);
    while(strcmp(InputCommand,"EXIT")!=0){
        printf("\033[0;37m"); //set color White
        if (strcmp(InputCommand,"MAP")==0){
            MATRIKS M2;
            STARTKATA("ADT/Matriks/map.txt");
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
                IsiPoint(&M2,CTemp);
            }
            ADVKATA();
            PrintMap(M2); //AMAN
        
        }
        else{
            printf("Input Anda salah!\n");
        }
        printf("Selamat datang! Silahkan pilih input Anda:\n");
        printf("\033[0;32m");
        printf("MAP ");
        printf("\033[0;31m"); 
        printf("EXIT");
        
        printf("\033[0;36m\n");
        scanf("%s",InputCommand);       
    }

    printf("\033[0;37m\n");
    return 0;
}
