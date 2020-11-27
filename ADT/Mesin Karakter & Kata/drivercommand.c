#include <stdio.h>
#include <stdlib.h>
#include "mesin_kar.c"
#include "mesinkata.c"

int main(){
    static FILE *FNow;
    const char *FILENAME = "save.txt";
    FNow = fopen(FILENAME,"a");
    fputs("REMOVECOMPONENT ",FNow);
    fclose(FNow);
}