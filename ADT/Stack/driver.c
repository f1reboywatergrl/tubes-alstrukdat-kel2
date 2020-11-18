#include "stackt.c"
#include <stdio.h>
void PrintStack(Stack S)
{
    int i;

    for (i = Top(S); i >= 0; i--){
        printf("%d -> %d ",i, S.T[i]);
        if (i == Top(S)){
            printf("<top>");
        }
        printf("\n");
    }
}

int main(){
    Stack CKata;
    Stack S1,S;
    Stack S2;
    infotype CKar;

    CreateEmpty(&S2);    
    CreateEmpty(&S1);
    Push(&S1,9);
    Push(&S1,8);
    Push(&S1,7);
    printf("-----------Stack 1-----------\n");
    PrintStack(S1);  
    CopyStack(S1, &S2);
    InverseStack(&S2);
    printf("-----------Stack 2-------------\n");
    PrintStack(S2);
    printf("\n\n");
    S=MergeStack(S1,S2);
    PrintStack(S);    
    return 0;
}