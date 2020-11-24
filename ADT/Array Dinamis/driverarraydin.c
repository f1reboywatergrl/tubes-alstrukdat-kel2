#include "arraydin.c"
#include <stdio.h>
#include <stdlib.h>

int main(){
    TabInt A;
    MakeEmpty(&A,5);
    BacaIsi(&A);
    TulisIsiTab(A);
    return 0;

}
