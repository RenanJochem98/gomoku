#include <time.h>
#include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <pthread.h>

int vencedorGeral = 0;
int tamanhoMatriz;
int jogadorVez;
pthread_mutex_t mutex;
// funcao para imprimir a matriz na tela. Apenas para despoluir a funcao principal
// void escreveMatriz(int matriz[tamanhoMatriz][tamanhoMatriz]){
void escreveMatriz(void *matrizPont){
	int **matriz = (int **)matrizPont;
	int i;
	int j;
	for(i = 0; i < tamanhoMatriz; i++){
		for(j = 0; j < tamanhoMatriz; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

// como sao apenas dois jogadores, 0 e 1, para alterar entre eles basta diminuir um e pegar o valor positivo
int alteraJogador(int jogador){
	return abs(jogador - 1);
}

void *verificaVencedorHorizontal(void *matrizPont){
	pthread_mutex_lock(&mutex);
	int **matriz = (int **)matrizPont;
	int jogVez = jogadorVez + 1;
	int i;
	int j;
	int count = 0;
	int numPecas = tamanhoMatriz / 2; //para nao precisar passar mais um argumento como parametro sempre

	for(i = 0; i < tamanhoMatriz; i++){
		for(j = 0; j < tamanhoMatriz; j++){
			if(matriz[i][j] == jogVez){
				count++;
			}else{
				count = 0;
			}

			if(count >= numPecas){
				break;
			}
		}
		if(count >= numPecas){
			break;
		}
		count = 0;
	}
	if(count >= numPecas){
		vencedorGeral = 1;
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	return NULL;
}

void *verificaVencedorVertical(void *matrizPont){
	pthread_mutex_lock(&mutex);
	int **matriz = (int **)matrizPont;
	int jogVez = jogadorVez + 1;
    int i;
    int j;
    int count = 0;
    int numPecas = tamanhoMatriz / 2;

	for(i = 0; i < tamanhoMatriz; i++){
	    for(j = 0; j < tamanhoMatriz; j++){
			if(matriz[j][i] == jogVez){
				count++;
			}else{
				count = 0;
			}

			if(count >= numPecas){
				break;
			}
	    }
		if(count >= numPecas){
			break;
		}
		count = 0;
	}

	if(count >= numPecas){
		vencedorGeral = 1;
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	return NULL;
}
int verificaEmpate(int contTotalPec, int tamMatriz, int matriz[tamMatriz][tamMatriz], int jogadorVez){
    int verificaEmpate;
    if(contTotalPec == 0){
        return verificaEmpate = 1;
    }
    return verificaEmpate = 0;
}

int verificaVencDiagEsqInfParaDirSup(int tamMatriz, int matriz[tamMatriz][tamMatriz], int jogadorVez){
	int i;
	int j;
	int count = 0;
	int numPecas = tamMatriz / 2; //para nao precisar passar mais um argumento como parametro sempre
	int vencedor = 0;

	int primeiraLinha  = numPecas - 1;
	int ultimaColuna = tamMatriz - (numPecas - 1);
	int coluna = 0;

	for(i = primeiraLinha; i < tamMatriz; i++){
		int linha = i;
		while(linha > 0 && coluna <= linha){
			int posicao = matriz[linha][coluna];

			//comparo
			linha--;
			coluna++;
		}
	}

	if(count >= numPecas){
		vencedor = 1;
	}
	return vencedor;
}

int main(){
	int verificaEmpate = 0;
	int vencedor = 0;
	int linha;
	int coluna;
	// int tamanhoMatriz;

	int jogador1 = 0;
	int jogador2 = 1;

	int i;
	int j;

	printf("Digite o numero de pedras: \n");
	scanf("%d", &tamanhoMatriz);

	jogadorVez = (rand() % 2);

	// a matriz tem que ter o dobro de numero de pedras
	tamanhoMatriz *= 2;

	// int matriz[tamanhoMatriz][tamanhoMatriz];

	int **matriz = (int **)malloc(tamanhoMatriz * sizeof(int *));
    for (i = 0; i < tamanhoMatriz; i++){
        matriz[i] = (int *)malloc(tamanhoMatriz * sizeof(int));
	}

	int contaPecaTotal = tamanhoMatriz * tamanhoMatriz;

	// inicializa a matriz
	for(i = 0; i < tamanhoMatriz; i++){
		for(j = 0; j < tamanhoMatriz; j++){
			matriz[i][j] = 0;
		}
	}

	// enquanto nao houver vencedor... ao menos ate implementarmos isso
	while(vencedorGeral < 1){
		// imprime a matriz na tela
		escreveMatriz(matriz);

		// paga entrada de linha e coluna do teclado
		printf("Vez do jogador %d \n", jogadorVez + 1);
		printf("Digite a linha e a coluna: \n");
		scanf("%d %d", &linha, &coluna);

		// enquanto usuario nao digitar uma posicao valida, o algoritmo fica preso aqui, mostrando o erro e pedindo nova posicao
	    while((linha >= tamanhoMatriz || coluna >= tamanhoMatriz) || matriz[linha][coluna] != 0){
			if(linha >= tamanhoMatriz){
				printf("Voce selecionou uma linha invalida. \n");
			}

			if(coluna >= tamanhoMatriz){
				printf("Voce selecionou uma coluna invalida. \n");
			}

			if(matriz[linha][coluna] != 0){
				printf("Voce selecionou uma posicao ocupada. \n");
			}

			printf("Digite a linha e a coluna, validas: \n");
			scanf("%d %d", &linha, &coluna);
		}
		// imprime o valor referente ao jogador
		matriz[linha][coluna] = jogadorVez + 1;

		pthread_t horizontal;
		pthread_t vertical;


		pthread_mutex_init(&mutex, NULL);

		pthread_create(&horizontal, NULL, verificaVencedorHorizontal, matriz);
		pthread_create(&vertical, NULL, verificaVencedorVertical, matriz);

		pthread_join(horizontal, NULL);
		pthread_join(vertical, NULL);

		pthread_mutex_destroy(&mutex);

		// define proximo jogador
		jogadorVez = alteraJogador(jogadorVez);

		contaPecaTotal = contaPecaTotal - 1;

	}//fim whiele
	// if(verificaEmpate == 1){
	//     printf("\nTemos um Empate! \n");
	//     printf("Parou");
	// } else{
    	// como o jogador da vez foi alterado dentro do while, alteramos de novo para pegar o vencedor
    	int jogadorVencedor = alteraJogador(jogadorVez);

    	printf("\nTemos um vencedor! \n");

    	escreveMatriz(matriz);

    	printf("\nJogador %d venceu! \n", jogadorVencedor + 1);
    	printf("Parou");
    // }
	return 0;
}
