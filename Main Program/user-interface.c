#include <stdio.h>

/* --------GALERI WARNA------------ */
#define Yellow printf("\033[0;33m");
#define Purple printf("\033[0;35m");
#define IBlue printf("\033[0;94m");
#define IYellow printf("\033[0;93m");
#define Green printf("\033[0;32m");
#define Red printf("\033[0;31m");
#define White printf("\033[0;37m");
#define Cyan printf("\033[0;36m\n");

void ShowUI (){
    Yellow; //set color Yellow
    printf("MOVE | ");
    printf("STATUS");
    printf("\n");

    Purple; //set color Purple
    printf("CHECKORDER | ");
    printf("STARTBUILD | ");
    printf("FINISHBUILD ");
    printf("\n");

    IBlue; //set color High Intensity Blue
    printf("ADDCOMPONENT | ");
    printf("REMOVECOMPONENT ");
    printf("\n");

    IYellow; //set color High Intensity Yellow
    printf("SHOP | ");
    printf("DELIVER | ");
    printf("MAP ");
    printf("\n");

    
    Green; //set color Green
    printf("END_DAY | ");
    printf("SAVE");
    printf("\n");

    Red; //set color Red
    printf("EXIT");
}

void MainMenu(){
    printf("Santo's World\n");
    printf("Please choose your input... \n");
    Red;
    printf("START ");
    Green;
    printf("LOAD\n");
}