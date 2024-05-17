#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct lista_vizinhos lista_vizinhos_t;

struct lista_vizinhos{
	int id_vizinho;
    lista_vizinhos_t* prox;
};

bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista){
	lista_vizinhos_t* novo_vizinho = malloc(sizeof(lista_vizinhos_t));
	if(!novo_vizinho)
		return false;
	novo_vizinho->id_vizinho = vizinho;
	novo_vizinho->prox = *lista;
	*lista = novo_vizinho;
	return true;
} /***/

void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
	if(lista){
		printf("%d",lista->id_vizinho);
		lista = lista->prox;
	}
	while(lista){
		printf(" %d", lista->id_vizinho);
		lista = lista->prox;
	}
}

typedef struct{
	int id;
	double pos_x, pos_y;
	lista_vizinhos_t* lista_vizinhos;
} no_t;

typedef no_t* grafo_t;

grafo_t grafo_criar(int tam){
	grafo_t grafo = malloc(sizeof(no_t)*tam);
	return grafo;
}

double distancia_euclidiana(double ax, double ay, double bx, double by){
	return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
}

void grafo_atualizar_vizinhos(int tam, double raio_comunicacao, grafo_t grafo){
	for(int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			if(j!=i && distancia_euclidiana(grafo[i].pos_x, grafo[i].pos_y, grafo[j].pos_x, grafo[j].pos_y) < raio_comunicacao){
				lista_vizinhos_adicionar(i, &grafo[j].lista_vizinhos);
			}
		}
	}
}

void grafo_imprimir(int tam, grafo_t grafo){
	for(int i = 0; i < tam; i++){
		printf("NÓ %d: ", i);
		lista_vizinhos_imprimir(grafo[i].lista_vizinhos);
		printf("\n");
	}
}

int main(int argc, char* argv[]){
	// verificar argumentos
	if(argc != 2){
		printf("Número errado de argumentos\n");
		return EXIT_FAILURE;
	}
	FILE* arq_in = fopen(argv[1], "r");
	// ler primeira linha
	int num_nos;
	double raio_comunicacao;
	fscanf(arq_in, "%d\t%lf\n", &num_nos, &raio_comunicacao);
	// criar grafo
	grafo_t g = grafo_criar(num_nos);
	for(int i = 0; i < num_nos; i++){
		int id;
		double pos_x, pos_y;
		fscanf(arq_in, "%d\t%lf\n%lf", &id, &pos_x, &pos_y);
		g[i].id = id;
		g[i].pos_x = pos_x;
		g[i].pos_y = pos_y;
		g[i].lista_vizinhos = NULL;
	}
	grafo_atualizar_vizinhos(num_nos, raio_comunicacao, g);
	grafo_imprimir(num_nos, g);
	return EXIT_SUCCESS;
}