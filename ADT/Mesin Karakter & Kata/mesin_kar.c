#include <stdio.h>
#include "mesin_kar.h"


int main(){
	static FILE *pita;
	static int retval;
	
	void START (char* filename){
		pita = fopen("pitakar.txt","r"); /* file pitakar.txt hanya diread*/
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
	
}
