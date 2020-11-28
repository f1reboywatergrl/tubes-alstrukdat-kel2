#include "graph.c"
#include "stdio.h"
#include "stdlib.h"
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

int main(){
    Graph G;
    MATRIKS GraphMatrix;
    MakeMATRIKS(9,9,&GraphMatrix);

    //Buat smua 0
    for(int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
        for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
            ElmtMatrix(GraphMatrix,i,j)=0;
        }
    }

    GenerateStaticAdjacency(&GraphMatrix);
    TulisMATRIKS(GraphMatrix);printf("\n");
    

    initGraph(&G,9);
    for (int i=BrsMin;i<NBrsEff(GraphMatrix);i++){
        for (int j=KolMin;j<NKolEff(GraphMatrix);j++){
            if (ElmtMatrix(GraphMatrix,i,j)==1){
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
    PrintLink(G,5);printf("\n");
    addressGraph P1;
    P1=FirstGraph(G);
    while (InfoGraph(P1)!=5){
        P1=NextGraph(P1);
    }
    printf("%d\n",Info(First(Link(P1))));
    address AdrTarget = First(Link(P1));
    for (int i=0;i<2;i++){
        AdrTarget=Next(AdrTarget);
    }
    //infotype IndexTarget=Info(AdrTarget);
    //printf("%d\n",IndexTarget);
    //Move(G,CurrentPos(M2),IndexTarget,&M2);
    //Move (G,&CurrentPos,6);
    ShowValidTargets(G,7);
    // Pembacaan graph static OK
    
    /* Test Delivery */
    int CurrentDeliveryLoc = 5;
    //POINT PointDeliveryLoc = SearchMatrix(M,5);
    
    
    return 0;
}