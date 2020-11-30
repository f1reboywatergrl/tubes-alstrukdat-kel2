#include <stdio.h>
#include "../ADT/Stack/boolean.h"
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
    printf(".--------------.------------.------------------.\n");
    printf("|             What will Santo do?              |\n");
    printf(".--------------.------------.------------------.\n");
    printf("|     ");Yellow;printf("MOVE");White;printf("     |            |      ");Yellow;printf("STATUS");White;printf("      |\n");
    printf(":--------------+------------+------------------:\n");
    printf("|  ");Purple;printf("CHECKORDER");White;printf("  | ");Purple;printf("STARTBUILD");White;printf(" |    ");Purple;printf("FINISHBUILD");White;printf("   |\n");
    printf(":--------------+------------+------------------:\n");
    printf("| ");IBlue;printf("ADDCOMPONENT");White;printf(" |            |  ");IBlue;printf("REMOVECOMPONENT");White;printf(" |\n");
    printf(":--------------+------------+------------------:\n");
    printf("|     ");IYellow;printf("SHOP");White;printf("     |   ");IYellow;printf("DELIVER");White;printf("  |        ");IYellow;printf("MAP");White;printf("       |\n");
    printf(":--------------+------------+------------------:\n");
    printf("|    ");Green;printf("END_DAY");White;printf("   |            |       ");Green;printf("SAVE");White;printf("       |\n");
    printf(":--------------'------------'------------------:\n");
    printf("|                   ");Red;printf("EXIT");White;printf("                       |\n");
    printf("'----------------------------------------------'\n");
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
    printf("\nLet's play in Santo's World!");
    White;
    printf("\n");
    
    printf("//========================\\");printf("\n");
    printf("|| |  \033[0;31mSTART\033[0;37m  |   \033[0;32mLOAD\033[0;37m  | ||");printf("\n");
    printf("\\========================//");printf("\n");
    printf("Please choose your input... \n");
    Green;
}

void SecretShopIntro(){
    Yellow;
    printf("Through the Shop's back door, Santo found his way inside a secret room.\n");
    Red;
    printf("Well done, you have managed to find this room.\n");
    printf("I see your potential... so I've set a reward for you.\n");
    printf("Below are 5 goblets. Choose wisely, and a reward will be bestowed upon you.\n");
    printf("I'll give you a hint: Remember where you came from, why you're doing this, and what your goal is.\n");
    printf("Sometimes, the answer may be hiding in a different place... think about the question, not the options...\n");
    IBlue;printf("1 ");Green;printf("2 ");Yellow;printf("3 ");Purple;printf("4 ");BCyan;printf("5\n");
    Red;printf("Choose Wisely: ");
}

void LockShop(boolean *SecretShop){
    *SecretShop=!(*SecretShop);
}