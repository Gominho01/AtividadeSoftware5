#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *soma (void *arg);

int total = 0;
int *valor;
int tam = 0;
int aux = 0;
int aux_tam;
int matriz[1000][1000];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // inicializador padrão


int main(void){
	scanf("%d ", &tam);
  aux_tam = tam;
  
  // criando o array com o tamanho da matriz
	valor = malloc(sizeof(int) * (tam * tam));
  
  // declaração de variaveis
	pthread_t threads[tam];
  int i = 0;
  int cont = 0;
  
  // criação da matriz e adicionando os valores em um array
	for(i = 0; i<tam; i++){
		for(int j = 0; j<tam; j++){
			scanf(" %d", &valor[cont]);
			matriz[i][j] = valor[j];
      cont++;
		}
	}
  
  // criando as threads
	for(i = 0; i < tam; i++){
		if(pthread_create(&(threads[i]), NULL, soma, NULL) != 0){
			printf("Thread %d not created\n", i);
		}
	}
	for(i = 0; i < tam; i++){
		pthread_join(threads[i], NULL);
	}
	printf("%d\n", total);
	return 0;
}

// função pra soma das linhas
void *soma(void *arg){
	pthread_mutex_lock(&mutex);
  int i = 0;

	for(i = aux; i < aux_tam; i++){
		total += valor[i]; 
	}
  
	aux = aux_tam;
	aux_tam += tam;
	pthread_mutex_unlock(&mutex);
	return arg;
}
/* teste 1
3
1 2 3
4 5 6
7 8 9

resultado: 45

teste 2
2
1 2
3 4

resultado: 10

teste 3
4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16

resultado: 136
*/