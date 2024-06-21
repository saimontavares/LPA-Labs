#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

struct chunk {
	int tamanho;
	char tipo[4];
} __attribute__ ((packed));

struct chunkIHDR {
	int width;
	int height;
	char bit_depth;
	char color_type;
	char comp_met;
	char fil_met;
	char int_met;
} __attribute__ ((packed));

int main(int argc, char* argv[]){
	// ler nome do arquivo 
	FILE *png_file = fopen(argv[1], "rb");
	struct chunk *chunk = malloc(sizeof(struct chunk));
	struct chunkIHDR *chunkIHDR = malloc(sizeof(struct chunkIHDR));
	fseek(png_file, 8, SEEK_CUR);
	int i = 1;
	while(!feof(png_file)){
		printf("Lendo Chunk %d:\n", i);
		fread(chunk, sizeof(struct chunk), 1, png_file);
		printf("\t--> Tamanho:\t%d\n", ntohl(chunk->tamanho));
		printf("\t--> Tipo:\t%.4s\n", chunk->tipo);
		if(strcmp(chunk->tipo, "IHDR") == 0){
			fread(chunkIHDR, sizeof(struct chunkIHDR), 1, png_file);
			printf("\t\t--> Largura:\t%d\n", ntohl(chunkIHDR->width));
			printf("\t\t--> Altura:\t%d\n", ntohl(chunkIHDR->height));
			fseek(png_file, 4, SEEK_CUR);
		}
		else if(strcmp(chunk->tipo, "IEND") == 0){
			break;
		}
		else{
			fseek(png_file, ntohl(chunk->tamanho)+4, SEEK_CUR);
		}
		i++;
	}
	return EXIT_SUCCESS;
}
	