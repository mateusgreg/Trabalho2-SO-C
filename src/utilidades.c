/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: Funções úteis para os 3 módulos do programa. */


int getMinimumInt(){
	int nMin = 8;
	int nWidth = 8;
	
	while(0 < (nMin <<= 4)) nWidth += 4;
	
	return nMin;
}

int getMaximumInt(){
	return getMinimumInt()^-1;
}

unsigned long long int getMinimumUnsignedLongLongInt(){
	return 0;
}

unsigned long long int getMaximumUnsignedLongLongInt(){
	return 18446744073709551614;
}
