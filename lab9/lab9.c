#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	FILE *mpeg_file = fopen(argv[1], "rb");
	unsigned char aux[4];
	FILE *parte = fopen("video_parte_1.mpg", "wb");
	unsigned char *buffer = malloc(atoi(argv[2])*1024*1024);
	int tamanho_saida= 0;
	int tamanho_max = atoi(argv[2])*1024*1024; // MB para bytes
	int tamanho_buffer = 0;
	int i = 2;
	unsigned char sequencecode[4] = {0x00, 0x00, 0x01, 0xB3};
	printf("Criando arquivo video_parte_%d.mpg ..\n", 1);
	while(1){
		fread(aux, 4, 1, mpeg_file);
		if(!feof(mpeg_file) && memcmp(aux, sequencecode, 4) != 0){
			buffer[tamanho_buffer] = aux[0];
			fseek(mpeg_file, -3, SEEK_CUR);
			tamanho_buffer++;
			continue;
		}
		if(tamanho_saida + tamanho_buffer > tamanho_max){
			fclose(parte);
			printf("Criando arquivo video_parte_%d.mpg ..\n", i);
			char nome_saida[19];
			sprintf(nome_saida, "video_parte_%d.mpg", i);
			parte = fopen(nome_saida, "wb");
			fwrite(buffer, tamanho_buffer, 1, parte);
			tamanho_saida = tamanho_buffer;
			//tamanho_buffer = 0;
			i++;
		}
		else{
			fwrite(buffer, tamanho_buffer, 1, parte);
			tamanho_saida += tamanho_buffer;
			//tamanho_buffer = 0;
		}
		if(feof(mpeg_file)){
			fclose(parte);
			break;
		}
		// sequence
		memcpy(buffer, sequencecode, 4);
		tamanho_buffer = 4;
	}
	free(buffer);
	fclose(mpeg_file);
	return 0;
}
