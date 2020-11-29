#include "list.c"
#include "string.h"

int main(){
    List L=MakeList();
    CreateDummies(&L);
    TulisIsiList(L);
    return 0;
}