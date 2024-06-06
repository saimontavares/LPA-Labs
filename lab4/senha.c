#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
/**
* @brief Verifica se uma senha em texto é a mesma de uma senha criptografada.
*
* @param senhaTeste Senha em texto que queremos ver se corresponde à senha criptografada.
* @param senhaCriptografada Senha criptografada como no arquivo /etc/shadow.
* @return int Retorna 0 (zero) se as senhas forem iguais. Outro valor, caso contrário.
*/
int verificaSenha(char* senhaTeste, char* senhaCriptografada) {
 char *senhaTesteCriptografada = crypt(senhaTeste, senhaCriptografada);
 return strcmp(senhaTesteCriptografada, senhaCriptografada);
}
void main() {
 char *senhaTeste = "FParad0x1?";
 char *senhaCriptografada = "$6$OByk0oaCjQMb9ApC$Z4Zm.GP6/I/t2iJROFazxXEwTiVzdDJZ2"
 "FdyPdSaRnkPmH9RXdT7xjr30.uy484yx61WsqEUWuvpcqa7X/0oN1";
 if (!verificaSenha(senhaTeste, senhaCriptografada))
 printf("A senha está correta!\n");
 else
 printf("Senhas diferentes.\n");
}