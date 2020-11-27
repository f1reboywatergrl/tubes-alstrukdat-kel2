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

/*
void STARTBUILD(Stack *S, boolean *lagiBuild, int NoPesanan, int NoPelanggan){
    CreateEmpty(*S);
    if (*lagiBuild){
        printf("Sedang merakit komputer lain, tidak bisa merakit pesanan yang lainnya.");
    }
    else{
        *lagiBuild = true;
        printf("kamu telah memulai pesanan %d untuk pelanggan %d.\n",NoPesanan,NoPelanggan);
    }
}

void FINISHBUILD(Stack Pesanan, Stack Rakitan, boolean lagiBuild, int NoPesanan, int NoPelanggan){
    if (IsStackEqual(Pesanan, Rakitan)){
        *lagiBuild = false;
        printf("Pesanan %d telah selesai. Silahkan antar ke pelanggan %d!\n",NoPesanan,NoPelanggan);

    }
    else{
        printf("Komponen yang dipasangkan belum sesuai dengan pesanan, build belum dapat diselesaikan.\n");
    }
}

lagiBuild adalah variabel yang menandakan apakah user sedang mengerjakan suatu pesanan (status)
*/
int main(){
    Stack CKata;
    Stack S1,S;
    Stack S2;
    infotype CKar;

    CreateEmpty(&S2);    
    CreateEmpty(&S1);
/*
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
    */
    printf("-----------Stack 1-----------\n");
    PrintStack(S1);  
    CopyStack(S1, &S2);
    InverseStack(&S2);
    printf("-----------Stack 2-------------\n");
    PrintStack(S2);
    printf("\n\n");
    S=MergeStack(S1,S2);
    PrintStack(S);    

    char string1[100] = 'abcd';
    char string2[100] = 'abcd';
    if(IsStringEqual(string1,string2)){
        printf("String sama sob!\n");
    }
    return 0;
}