#include "stackt.c"

int main(){
    List L=MakeList();
    Stack S1,S2,S3,
    S4,S5,
    S6,S7,
    S8,S9,
    S10,S11,
    S12,S13,
    S14,S15,
    S16,S17,
    S18,S19,
    S20,S21,
    S22,S23,
    S24,S25,
    S26,S27;

    CreateDummies(&L);
    CreateDummyStacks(&S1,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S2,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S3,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    
    CreateDummyStacks(&S4,ListElmt(L,1),ListElmt(L,4),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S5,ListElmt(L,2),ListElmt(L,5),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    
    CreateDummyStacks(&S6,ListElmt(L,1),ListElmt(L,3),ListElmt(L,7),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S7,ListElmt(L,2),ListElmt(L,3),ListElmt(L,8),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));    
    
    CreateDummyStacks(&S8,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,10),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S9,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,11),ListElmt(L,12),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));    
    
    CreateDummyStacks(&S10,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,13),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S11,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,14),ListElmt(L,15),ListElmt(L,18),ListElmt(L,21));    
    
    CreateDummyStacks(&S12,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,16),ListElmt(L,18),ListElmt(L,21));
    CreateDummyStacks(&S13,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,17),ListElmt(L,18),ListElmt(L,21));
    
    CreateDummyStacks(&S14,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S15,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S16,ListElmt(L,1),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,22));
    CreateDummyStacks(&S17,ListElmt(L,2),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,23));

    CreateDummyStacks(&S18,ListElmt(L,0),ListElmt(L,4),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S19,ListElmt(L,0),ListElmt(L,5),ListElmt(L,6),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S20,ListElmt(L,0),ListElmt(L,3),ListElmt(L,7),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S21,ListElmt(L,0),ListElmt(L,3),ListElmt(L,8),ListElmt(L,9),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S22,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,10),ListElmt(L,12),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S23,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,11),ListElmt(L,12),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));
    
    CreateDummyStacks(&S24,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,13),ListElmt(L,15),ListElmt(L,19),ListElmt(L,21));
    CreateDummyStacks(&S25,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,14),ListElmt(L,15),ListElmt(L,20),ListElmt(L,21));

    CreateDummyStacks(&S26,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,13),ListElmt(L,15),ListElmt(L,19),ListElmt(L,22));
    CreateDummyStacks(&S27,ListElmt(L,0),ListElmt(L,3),ListElmt(L,6),ListElmt(L,9),ListElmt(L,14),ListElmt(L,15),ListElmt(L,20),ListElmt(L,23));
 
    //Nanti buat ngebantu bikin orderan dummy

    printf("STEK \n\n");
    PrintStack(S1);printf("\n");
    PrintStack(S2);printf("\n");
    PrintStack(S3);printf("\n\n");

    PrintStack(S4);printf("\n");
    PrintStack(S5);printf("\n");
    PrintStack(S6);printf("\n");
    return 0;
}