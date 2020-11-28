#include "graph.c"
#include "stdio.h"
#include "stdlib.h"
#include "../Matriks/matriks.c"
#include "../Matriks/matriks.h"
/*
0 0 0 1 0 0 1 0 0
0 0 1 1 1 0 0 1 1
0 1 0 0 1 1 0 0 0
1 1 0 0 0 0 0 0 0
0 1 1 0 0 0 0 1 0
0 0 1 0 0 0 0 1 0
1 0 0 0 0 0 0 0 1
0 1 0 0 1 1 0 0 0
0 1 0 0 0 0 1 0 0

*/

void GenerateStaticAdjacency(MATRIKS *GraphMatrix){
    Elmt(*GraphMatrix,3,0)=1;
    Elmt(*GraphMatrix,0,3)=1;
    Elmt(*GraphMatrix,0,6)=1;
    Elmt(*GraphMatrix,6,0)=1;
    Elmt(*GraphMatrix,1,3)=1;
    Elmt(*GraphMatrix,3,1)=1;
    Elmt(*GraphMatrix,1,4)=1;
    Elmt(*GraphMatrix,4,1)=1;
    Elmt(*GraphMatrix,2,5)=1;
    Elmt(*GraphMatrix,5,2)=1;
    Elmt(*GraphMatrix,1,7)=1;
    Elmt(*GraphMatrix,7,1)=1;
    Elmt(*GraphMatrix,1,8)=1;
    Elmt(*GraphMatrix,8,1)=1;
    Elmt(*GraphMatrix,1,2)=1;
    Elmt(*GraphMatrix,2,1)=1;
    Elmt(*GraphMatrix,2,4)=1;
    Elmt(*GraphMatrix,4,2)=1;
    Elmt(*GraphMatrix,7,4)=1;
    Elmt(*GraphMatrix,4,7)=1;
    Elmt(*GraphMatrix,7,5)=1;
    Elmt(*GraphMatrix,5,7)=1;
    Elmt(*GraphMatrix,6,8)=1;
    Elmt(*GraphMatrix,8,6)=1;    
}

int main(){
    Graph G;
    MATRIKS GraphMatrix;
    MakeMATRIKS(9,9,&GraphMatrix);
    for(int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
        for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
            Elmt(GraphMatrix,i,j)=0;
        }
    }
    GenerateStaticAdjacency(&GraphMatrix);
    TulisMATRIKS(GraphMatrix);printf("\n");
    

    initGraph(&G,9);
    for (int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
        for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
            if (Elmt(GraphMatrix,i,j)==1){
                AddLink(&G,i-1,j-1);
            }
        }
    }
    for (int C=-1;C<9;C++){
        PrintLink(G,C);
        printf("\n");
    }
    int CurrentPos = 5;
    ShowValidTargets(G,CurrentPos);
    //Move (G,&CurrentPos,6);
    ShowValidTargets(G,CurrentPos);
    // Pembacaan graph static OK
    return 0;
}