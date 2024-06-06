#include <stdio.h>
#include <string.h>

int tamanhoMaximo = 3;
char caracteres[] = "abc";
char newline = '\0';

void gerarPermutacoesRecursivo(char* pwd, int pos, int size){
	if(pos < size)
		for(int i = 0; i < tamanhoMaximo; i++){
			pwd[pos] = caracteres[i];
			gerarPermutacoesRecursivo(pwd, pos + 1, size);
		}
	else
		printf("%s\n", pwd);
}

int main(int argc, char* argv[]){
	for(int i = 1; i <= tamanhoMaximo; i++){
		gerarPermutacoesRecursivo(&newline, 0, i);
	}
	return 0;
}