#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int TAM = 0;

typedef struct {
	char nome[51];
	long long int cpf;
	int idade;
} pessoa_t;

typedef struct lista_pessoas lista_pessoas_t;

struct lista_pessoas{
	pessoa_t* pessoa;
	struct lista_pessoas* prox;
};

bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista){
	lista_pessoas_t *novo = malloc(sizeof(lista_pessoas_t));
	if(novo == NULL)
        return false;
	novo->pessoa = pessoa;
	novo->prox = *lista;
	*lista = novo;
	return true;
}

void lista_pessoas_listar(lista_pessoas_t *lista){
	while(lista){
		pessoa_t *p = lista->pessoa;
		printf("- %s\t%lld\t%d\n", p->nome, p->cpf, p->idade);
		lista = lista->prox;
	}
}

typedef lista_pessoas_t** tabela_hash_t;

tabela_hash_t tabela_hash_pessoas_criar(){
	tabela_hash_t tabela = malloc(sizeof(lista_pessoas_t*)*TAM);
	for(int i = 0; i < TAM; i++)
		tabela[i] = NULL;
	return tabela;
}

int tabela_hash_pessoas_funcao(pessoa_t *pessoa){
	return pessoa->cpf % TAM;
}

bool tabela_hash_pessoas_adicionar(pessoa_t *pessoa, tabela_hash_t tabela_hash){
	int hash = tabela_hash_pessoas_funcao(pessoa);
	return lista_pessoas_adicionar(pessoa, &tabela_hash[hash]);
}

void tabela_hash_pessoas_listar(tabela_hash_t tabela_hash){
	for(int i = 0; i < TAM; i++){
		printf("POSIÇÃO %d DA TABELA HASH:\n", i);
		lista_pessoas_listar(tabela_hash[i]);
	}
}

int main(int argc, char* argv[]){
	// verificar argumentos
	if(argc != 3){
		printf("Número de argumentos errado\n");
		return 1;
	}
	sscanf(argv[1], "%d", &TAM);
	// criar tabela
	tabela_hash_t th = tabela_hash_pessoas_criar();
	// abrir arquivo
	FILE* arq_in = fopen(argv[2], "r");
	// adicionar todas as pessoas do arquivo na tabela
	while(!feof(arq_in)){
		pessoa_t* p = malloc(sizeof(pessoa_t));
		fscanf(arq_in, "%50[^\t]\t%lld\t%d\n", p->nome, &p->cpf, &p->idade);
		tabela_hash_pessoas_adicionar(p, th);
	}
	// imprimir a tabela
	tabela_hash_pessoas_listar(th);
	return 0;
}