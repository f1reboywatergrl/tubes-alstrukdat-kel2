#include "matriks.c"

int main(){
    //BrsMax -> 12, KolMax -> 17 (base-0)
    //Tes 1 - Simulasi Statik
    printf("\nTest case 1 - Simulasi rancang map dengan variable static\n");
    MATRIKS M;
    MakeMATRIKS(BrsMax,KolMax,&M);
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
    //BAG 1. AKUISISI - Misal akuisisi 10 & 15 dari pita
    int BrsPita=10;
    int KolPita=15;
    //+=2 karena tambah ruang untuk border
    BrsPita+=2;
    KolPita+=2;
    MakeMATRIKS(BrsPita,KolPita,&M2);
    EmptyMatrix(&M2);

    //BAG 2. TOTAL TITIK - Misal total titik di peta ada 9
    int TitikTotal=9;
    TitikTotal-=2; //karena kita mulai dari -1

    //BAG 3. PEMETAAN - Start pasang-pasang titik ke peta,
    for(int I=-1;I<=TitikTotal;I++) {
        POINT CTemp;
        switch(I){
            case -1:
                SimpanPoint(&CTemp,10,3,'B',I);break;
            case 0:
                SimpanPoint(&CTemp,6,3,'S',I);break;
            case 1:
                SimpanPoint(&CTemp,1,1,'C',I);break;
            case 2:
                SimpanPoint(&CTemp,8,2,'C',I);break;
            case 3:
                SimpanPoint(&CTemp,4,6,'C',I);break;
            case 4:
                SimpanPoint(&CTemp,1,9,'C',I);break;
            case 5:
                SimpanPoint(&CTemp,9,10,'C',I);break;
            case 6:
                SimpanPoint(&CTemp,3,12,'C',I);break;
            case 7:
                SimpanPoint(&CTemp,7,7,'C',I);break;
            //Nanti ini ga pake switch case, switch case ini simulasi pembacaan aja.
            //nanti, parameter SimpanPoint lgsg hasil akuisisi pita kar.
            //Contoh -> SimpanPoint (&CTemp,XAkuisisi,YAkuisisi,TypeAkuisisi,I);
        }
        IsiPoint(&M2,CTemp);
    }
    PrintMap(M2);
    //SUKSES, kekurangannya, point tersimpan dgn baik di matriks, tp ga disimpan di POINT scr permanent.


    return 0;
}