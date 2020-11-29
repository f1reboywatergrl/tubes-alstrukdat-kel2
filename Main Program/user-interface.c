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