#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct zip_file_hdr {
	int signature;
	short version;
	short flags;
	short compression;
	short mod_time;
	short mod_date;
	int crc;
	int compressed_size;
	int uncompressed_size;
	short name_length;
	short extra_field_length;
} __attribute__ ((packed));

int main(int argc, char* argv[]){
	// lear nome do arquivo 
	FILE *zip_file = fopen(argv[1], "rb");
	struct zip_file_hdr *file_hdr = malloc(sizeof(struct zip_file_hdr));
	
	// printf(" --> Assinatura: %.8x", file_hdr->signature);
	// printf(" --> Tamanho Compactado: %d\n", file_hdr->compressed_size);
	
	int num_arquivo = 1;

	while(!feof(zip_file)){
		fread(file_hdr, sizeof(struct zip_file_hdr), 1, zip_file);
		if(file_hdr->signature == 0x04034b50){
			char* nome_arquivo = malloc(file_hdr->name_length+1);
			fread(nome_arquivo, file_hdr->name_length, 1, zip_file);
			nome_arquivo[file_hdr->name_length] = '\0';
			printf("Arquivo %d ..\n", num_arquivo);
			num_arquivo++;
			printf("	--> Nome do Arquivo: %s\n	--> Tamanho Compactado: %d\n	--> Tamanho Descompactado: %d\n", nome_arquivo, file_hdr->compressed_size, file_hdr->uncompressed_size);
			free(nome_arquivo);
			fseek(zip_file, file_hdr->extra_field_length + file_hdr->compressed_size, SEEK_CUR);
		}
	}
	return EXIT_SUCCESS;
}