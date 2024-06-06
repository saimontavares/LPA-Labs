#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>

int tamanhoMaximo = 10;
int tamanhoSenha = 5;
char caracteres[] = "0123456789";
char *senhaCriptografada =  "$6$l2xE4w9twgjtnZBz$9YK9krslZFraLffy5VNiahAfT.xZNvB54j91DMCMIoVFvj335ZKxb11qgVMn.KzU2GqVPPyS2FTBqPSciYq761";
char newline = '\0';
int achou = 0;

int verificaSenha(char* senhaTeste, char* senhaCriptografada) {
	char *senhaTesteCriptografada = crypt(senhaTeste, senhaCriptografada);
	return strcmp(senhaTesteCriptografada, senhaCriptografada);
}

void gerarPermutacoesRecursivo(char* pwd, int pos, int size){
	if(pos < size)
		for(int i = 0; i < tamanhoMaximo; i++){
			pwd[pos] = caracteres[i];
			gerarPermutacoesRecursivo(pwd, pos + 1, size);
			if(achou) return;
		}
	else{
		printf("%s -->", pwd);
		if(verificaSenha(pwd, senhaCriptografada) == 0){
			printf(" sim! Senha encontrada!\n");
			achou = 1;
		}
		else{
			printf(" nao\n");
		}
	}
}
int main(int argc, char* argv[]){
	for(int i = 1; i <= tamanhoSenha; i++){
		gerarPermutacoesRecursivo(&newline, 0, i);
	}
	return 0;
}