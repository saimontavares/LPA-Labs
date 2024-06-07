#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
/* caso extra 1 : 0451 */
int tamanhoMaximo = 4;
int numCaracteres = 10;
char caracteres[] = "0123456789";
char *senhaCriptografada = "$6$LrSF5BAseToYYHJ0$SYY1avj8FRoRGpn.1kPXuZ6Xn5WTl2kL3"
							"hxc3yMWdDUyz4c/Ac3Av3WO8Q9LciP8o4c9WaeLcgxIXWaHpJMFb.";

/* caso extra 2 : cpp */
/*
int tamanhoMaximo = 3;
int numCaracteres = 26;
char caracteres[] = "abcdefghijklmnopqrstuvwxyz";
char *senhaCriptografada = "$6$rMAk28dVkWjpYoA3$SkWbPYqEB8O/10ryvvjm1qN9BOrkeBOXp"
							"JScVSGDL5L88OIs0UCBuP.pnd9TQ6SBx60dLKwR9WAzfnLtvjGvj.";
*/

/* caso extra 3 : 31337 */
/*
int tamanhoMaximo = 5;
int numCaracteres = 10;
char caracteres[] = "0123456789";
char *senhaCriptografada = "$6$l2xE4w9twgjtnZBz$9YK9krslZFraLffy5VNiahAfT.xZNvB54"
							"j91DMCMIoVFvj335ZKxb11qgVMn.KzU2GqVPPyS2FTBqPSciYq761";
*/

char newline = '\0';
short int encontrou = 0;

int verificaSenha(char* senhaTeste, char* senhaCriptografada) {
	char *senhaTesteCriptografada = crypt(senhaTeste, senhaCriptografada);
	return strcmp(senhaTesteCriptografada, senhaCriptografada);
}

void gerarPermutacoesRecursivo(char* pwd, int pos, int size){
	if(pos < size)
		for(int i = 0; i < numCaracteres; i++){
			pwd[pos] = caracteres[i];
			gerarPermutacoesRecursivo(pwd, pos + 1, size);
		}
	else{
		printf("%s --> ", pwd);
		if(!verificaSenha(pwd, senhaCriptografada)){
			printf("sim! Senha encontrada!\n");
			exit(0);
		}
		else
			printf("não\n");
	}
}

int main(int argc, char* argv[]){
	for(int i = 1; i <= tamanhoMaximo; i++){
		gerarPermutacoesRecursivo(&newline, 0, i);
	}
	return 0;
}