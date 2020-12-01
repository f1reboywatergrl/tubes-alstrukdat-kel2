#include "mesinkata.h"
#include <string.h>

boolean EndKata;
Kata CKata;


void IgnoreBlank() {
/* Mengabaikan satu atau beberapa BLANK
I.S.: CC sembarang
F.S.: CC != BLANK */
/* Kamus Lokal */
/* Algoritma */
	while (CC == BLANK) {
		ADV();
	} /* CC != BLANK */
}

void STARTKATA(char *filename) {
/* I.S.: CC sembarang
F.S.: EndKata = true, dan CC = Mark;
atau EndKata = false, CKata adalah kata yang sudah
diakuisisi,
CC karakter pertama sesudah karakter terakhir kata */
/* Kamus Lokal */
/* Algoritma*/
	START(filename);
	IgnoreBlank();
	if (CC == MARK) {
		EndKata = true;
	}
	else /* CC != MARK */ {
		EndKata = false;
		SalinKata();
	}
}

void ADVKATA() {
/* I.S.: CC adalah karakter pertama kata yang akan diakuisisi
F.S.: CKata adalah kata terakhir yang sudah diakuisisi,
CC adalah karakter pertama dari kata berikutnya,
mungkin MARK
Proses: Akuisisi kata menggunakan procedure SalinKata */
/* Kamus Lokal */
/* Algoritma*/
	IgnoreBlank();
	if (CC == MARK) {
		EndKata = true;
	} 
	else /* CC != MARK */ {
		SalinKata();
	}
}

void SalinKata() {
/* Mengakuisisi kata, menyimpan dalam CKata
I.S.: CC adalah karakter pertama dari kata
F.S.: CKata berisi kata yang sudah diakuisisi;
CC = BLANK atau CC = MARK;
CC adalah karakter sesudah karakter terakhir yang
diakuisisi */
/* Kamus Lokal */
	int i; /* definisi */
/* Algoritma*/
	i = 0; /* inisialisasi */
	while ((CC != MARK) && (CC != BLANK)) {
		CKata.TabKata[i] = CC;
		ADV();
		i++;
	} /* CC = MARK or CC = BLANK */
	CKata.Length = i;
}

int Pangkat(int base, int power){
	int result = 1;
	for (int i = 0;i<power;i++){
		result = result*base;
	}
	return result;
}

void BacaInput(char Kata[100]){
	char InputCommand[100];
    scanf("%s",&InputCommand);
    char CC;
	int i;
	/* definisi */
/* Algoritma*/
	CC = InputCommand[0];
	int length = strlen(InputCommand);
	i = 0; /* inisialisasi */
	while (i < length) {
		Kata[i] = CC;
		CC = InputCommand[i+1];
		i++;
	}
	
}
