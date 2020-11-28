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
#define BCyan printf("\033[1;36m");
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
    BCyan;
    printf(R"EOF(

  .-')    ('-.        .-') _ .-') _                  .-')           (`\ .-') /`           _  .-')          _ .-') _   
 ( OO ). ( OO ).-.   ( OO ) (  OO) )            ,--.( OO ).          `.( OO ),'          ( \( -O )        ( (  OO) )  
(_)---\_)/ . --. ,--./ ,--,'/     '._ .-'),-----\  (_)---\_)      ,--./  .--.  .-'),-----.,------. ,--.    \     .'_  
/    _ | | \-.  \|   \ |  |\|'--...__( OO'  .-.  `-/    _ |       |      |  | ( OO'  .-.  |   /`. '|  |.-'),`'--..._) 
\  :` `.-'-'  |  |    \|  | '--.  .--/   |  | |  | \  :` `.       |  |   |  |,/   |  | |  |  /  | ||  | OO |  |  \  ' 
 '..`''.\| |_.'  |  .     |/   |  |  \_) |  |\|  |  '..`''.)      |  |.'.|  |_\_) |  |\|  |  |_.' ||  |`-' |  |   ' | 
.-._)   \|  .-.  |  |\    |    |  |    \ |  | |  | .-._)   \      |         |   \ |  | |  |  .  '.(|  '---.|  |   / : 
\       /|  | |  |  | \   |    |  |     `'  '-'  ' \       /      |   ,'.   |    `'  '-'  |  |\  \ |      ||  '--'  / 
 `-----' `--' `--`--'  `--'    `--'       `-----'   `-----'       '--'   '--'      `-----'`--' '--'`------'`-------'  
 
    )EOF");
    printf("\nWelcome to Santo's World!");
    White;
    printf("\n");
    printf("Please choose your input... \n");
    Red;
    printf("START ");
    Green;
    printf("LOAD\n");
}