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
    if (CekUrutan(S1,1)){
        Push(&S1,1);
    }
    else{
        printf("salah komponen yang ditambahkan\n");
    }
    if (CekUrutan(S1,2)){
        Push(&S1,2);
    }
    else{
        printf("salah komponen yang ditambahkan\n");
    }
    if (CekUrutan(S1,3)){
        Push(&S1,3);
    }
    else{
        printf("salah komponen yang ditambahkan\n");
    }
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