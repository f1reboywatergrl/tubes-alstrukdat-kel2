#include <stdio.h>
#include "../ADT/Stack/boolean.h"
#include "stdlib.h"
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

void ShowUI ();
/* Menampilkan command-command yang bisa dimasukkan pemain ketika in-game */

void MainMenu();
/* Menampilkan menu utama sebelum start/load */

void SecretShopIntro();
/* Menampilkan narasi utama ketika pertama kali mengakses SecretShop */

void LockShop(boolean *SecretShop);
/* Mengunci secret shop */

void clear();
/* Membersihkan terminal */

void EndDayMessage();
/* Menampilkan pesan ketika End day*/