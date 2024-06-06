#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>

int tamanhoMaximo = 3;
char caracteres[3] = "abc";
char *senhaCriptografada = "$6$7yCakIXevncmT6se$m002Lkf2BK6Qgyhc.c/PxMTvcmBAXYtIokUKvWwvB5H5zCt5HhhPOlV8ygebOcSsgNqG74whVwN.8UF9WaGfs/";
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
	for(int i = 1; i <= tamanhoMaximo; i++){
		gerarPermutacoesRecursivo(&newline, 0, i);
	}
	return 0;
}