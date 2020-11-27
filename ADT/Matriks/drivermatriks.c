#include "matriks.c"
#include "../Mesin Karakter & Kata/mesinkata.c"
#include "../Mesin Karakter & Kata/mesin_kar.c"

int main(){
    //BrsMax -> 12, KolMax -> 17 (base-0)
    //Tes 1 - Simulasi Statik
    printf("\nTest case 1 - Simulasi rancang map dengan variable static\n");
    MATRIKS M;
    MakeMATRIKS(12,17,&M);
    EmptyMatrix(&M);
    //CurrentAbsis(M)=9;
    //CurrentOrdinat(M)=10;
    POINT B,S,C1,C2,C3,C4,C5,C6,C7;
    SimpanPoint(&B,10,3,'B',-1);
    SimpanPoint(&S,6,3,'S',0);
    SimpanPoint(&C1,1,1,'C',1);
    SimpanPoint(&C2,8,2,'C',2);
    SimpanPoint(&C3,4,6,'C',3);
    SimpanPoint(&C4,1,9,'C',4);
    SimpanPoint(&C5,9,10,'C',5);
    SimpanPoint(&C6,3,12,'C',6);
    SimpanPoint(&C7,7,7,'C',7);

    IsiPoint(&M,B);
    IsiPoint(&M,S);
    IsiPoint(&M,C1);
    IsiPoint(&M,C2);
    IsiPoint(&M,C3);
    IsiPoint(&M,C4);
    IsiPoint(&M,C5);
    IsiPoint(&M,C6);
    IsiPoint(&M,C7);
    //TulisMATRIKS(M);
    printf("\n");
    PrintMap(M);
    //SUKSES, kekurangannya sangat statik, kalau dikutak katik jml variablenya nanti gagal.


    printf("\n");

    //Tes 2 - Simulasi baca pita karakter
    printf("Test case 2 - Simulasi rancang map dengan pitakar\n\n");
    MATRIKS M2;
    STARTKATA("map.txt");
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
        printf("%d\n",Ordinat(CTemp));
        IsiPoint(&M2,CTemp);
    }
    ADVKATA();
    printf("x = %d y = %d\n", BrsPita,KolPita); //Brspita, Kolpita aman
    printf("Total Titik = %d\n",TitikTotal); //Expected -> titik di file konfigurasi - 2 , aman
    printf("Shop = %d Base = %d\n",Elmt(M2,10,3), Elmt(M2,6,3));
    printf("Tes Titik = %d\n",Elmt(M2,3,12));
    printf("Tes Titik Last = %d\n",Elmt(M2,6,4));
    PrintMap(M2); //AMAN
    //SUKSES, kekurangannya, point tersimpan dgn baik di matriks, tp ga disimpan di POINT scr permanent.//


    return 0;

    
}

/*
13 17 
10 
B 10 3 
S 6 3 
C 1 1 
C 8 2 
C 4 6 
C 1 9 
C 9 10 
C 3 12 
C 7 7 
C 6 4

*/