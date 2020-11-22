#include <stdio.h>
#include "mesin_kar.h"


static FILE *pita;
static int retval;
char CC;
boolean EOP;

void START (char *filename){
	pita = fopen(filename,"r"); /* file pitakar.txt hanya diread*/
	ADV();
}
void ADV (){
	retval = fscanf(pita,"%c", &CC); /* karakter pada pita dibaca dan dimasukkan ke dalam variabel CC*/
}
char GetCC(){
	return CC;
}
boolean IsEOP(){
	EOP = (CC == MARK);
	return EOP; /*EOP akan bernilai true jika CC sudah mencapai MARK*/ 
}
	
