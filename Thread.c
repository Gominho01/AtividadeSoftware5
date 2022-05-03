#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *soma (void *arg);

int total = 0;
int linha ;
int tam;
int matriz[1000][1000];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // inicializador padrao


int main(void){
	scanf("%d ", &tam);
  
  // declaracao de variaveis
	pthread_t threads[tam];
  int i = 0;
  
  // criacao da matriz
	for(i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			scanf(" %d", &matriz[i][j]);
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

// funcao pra soma das linhas
void *soma(void *arg){
	pthread_mutex_lock(&mutex);
  int i = 0;
  int valor_linha = 0;

	for(i = 0; i < tam; i++){
		valor_linha += matriz[linha][i]; 
	}

  total += valor_linha;
  linha++;
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