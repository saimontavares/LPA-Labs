#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {   
    double tempo;
    int alvo;
    int tipo;
} evento_t;

typedef struct lista_eventos lista_eventos_t;

struct lista_eventos{
    evento_t* evento;
    lista_eventos_t* prox;
};

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
    if (item_novo == NULL)
        return false;
    item_novo->evento = evento;
    item_novo->prox = *lista; 
    *lista = item_novo;
    return true;
}

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
    if (item_novo == NULL)
        return false;
	item_novo->evento = evento;
	if(*lista == NULL){
		*lista = item_novo;
		return true;
	}
	lista_eventos_t* item_atual = *lista;
	while(item_atual->prox != NULL){
		item_atual = item_atual->prox;
	}
	item_atual->prox = item_novo;
	return true;
}

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
    if (item_novo == NULL)
        return false;
	item_novo->evento = evento;
	if(*lista == NULL){
		*lista = item_novo;
		return true;
	}
    if(evento->tempo < (*lista)->evento->tempo){
        item_novo->prox = *lista;
        *lista = item_novo;
        return true;
    }
    lista_eventos_t* item_atual = *lista;
    while(item_atual->prox != NULL && item_atual->prox->evento->tempo < evento->tempo){
        item_atual = item_atual->prox;
    }
    item_novo->prox = item_atual->prox;
    item_atual->prox = item_novo;
}

void lista_eventos_listar(lista_eventos_t *lista){
    while(lista != NULL){
        printf("Tempo: %3.6lf Alvo: %d Tipo:%d\n", lista->evento->tempo, lista->evento->alvo, lista->evento->tipo);
        lista = lista->prox;
    }
}

int main(int argc, char* argv[]){
    FILE* arq = fopen(argv[1], "r+");
    double tempo;
    int alvo, tipo;
    lista_eventos_t* lista;
    while(true){
        fscanf(arq, "%lf\t%d\t%d", &tempo, &alvo, &tipo);
        if(feof(arq))
            break;
        evento_t *novo_evento = malloc(sizeof(evento_t));
        novo_evento->tempo = tempo;
        novo_evento->alvo = alvo;
        novo_evento->tipo = tipo;
        lista_eventos_adicionar_fim(novo_evento, &lista);
    }
    lista_eventos_listar(lista);
}