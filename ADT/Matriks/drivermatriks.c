#include "matriks.c"

int main(){
    //BrsMax -> 11, KolMax -> 16 (base-0)
    MATRIKS M;
    MakeMATRIKS(BrsMax,KolMax,&M);
    ZeroMatrix(&M);
    CurrentAbsis(M)=9;
    CurrentOrdinat(M)=10;
    int CustFileOrder = 1;
    IsiPoint(&M,10,3,"B",&CustFileOrder);
    IsiPoint(&M,6,3,"S",&CustFileOrder);
    IsiPoint(&M,1,1,"C",&CustFileOrder);
    IsiPoint(&M,8,2,"C",&CustFileOrder);
    IsiPoint(&M,4,6,"C",&CustFileOrder);
    IsiPoint(&M,1,9,"C",&CustFileOrder);
    IsiPoint(&M,9,10,"C",&CustFileOrder);
    IsiPoint(&M,3,12,"C",&CustFileOrder);
    IsiPoint(&M,7,7,"C",&CustFileOrder);
    printf("\n");
    PrintMap(M);
    return 0;
}