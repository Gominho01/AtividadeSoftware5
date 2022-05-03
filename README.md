# AtividadeInfraSoftware5

## Proposito do código

>O codigo tem como objetivo criar um número de threads equivalente ao tamanho de uma matriz e fazer com que cada thread some os valores que estão nas colunas e printar seu valor total, por exemplo, se temos uma matriz de tamanho 3, com os seguintes valores (1 2 3 4 5 6 7 8 9), teremos 45 como resposta.

## Funções mínimas do makefile

> Tem 3 funções essenciais pedidas nessa tarefa, o make que compila o código e gera o binário, o make run pra compilar o código e o make clear para apagar o binário gerado.

## Declaração das variaveis globais e do mutex

```c 
int total = 0;
int *valor;
int tam = 0;
int aux = 0;
int aux_tam;
int matriz[1000][1000];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // inicializador padrão
```

## Inicio do main

```c
  scanf("%d ", &tam);
  aux_tam = tam;
  
  // criando o array com o tamanho da matriz
	valor = malloc(sizeof(int) * (tam * tam));
  
  // declaração de variaveis
	pthread_t threads[tam];
  int i = 0;
  int cont = 0;
```

## Matriz e array

```c
  // criação da matriz e adicionando os valores em um array
	for(i = 0; i<tam; i++){
		for(int j = 0; j<tam; j++){
			scanf(" %d", &valor[cont]);
			matriz[i][j] = valor[j];
      cont++;
		}
	}
```

## Thread

```c
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
```

## Função Soma

```c
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
```
