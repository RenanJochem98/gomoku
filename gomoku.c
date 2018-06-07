#include <time.h>
#include <math.h>
# include <stdlib.h>
# include <stdio.h> //para alocacao dinamica (funcao malloc dava warning)
#include <pthread.h>

int vencedorGeral = 0;
int tamanhoMatriz;
int jogadorVez;

// funcao para imprimir a matriz na tela. Apenas para despoluir a funcao principal
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
	return NULL;
}

void *verificaVencedorVertical(void *matrizPont){
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
	return NULL;
}

void *verificaVencDiagEsqInfParaDirSup(void *matrizPont){
	int **matriz = (int **)matrizPont;
	int jogVez = jogadorVez + 1;
	int i;
	int j;
	int count = 0;
	int count2 = 0;
	int numPecas = tamanhoMatriz / 2; //para nao precisar passar mais um argumento como parametro sempre

	int primeiraLinha  = numPecas - 1;
	int ultimaColuna = tamanhoMatriz - (numPecas - 1);
	int maiorLinColMatriz = tamanhoMatriz - 1;
	int linha = 0;
	int coluna = 0;
	i = primeiraLinha;
	// for(i = primeiraLinha; i < tamanhoMatriz; i++){
	while(i < tamanhoMatriz || (linha == maiorLinColMatriz && coluna == maiorLinColMatriz)){
		linha = i;
		while(linha >= 0){
			if(matriz[linha][coluna] == jogVez){
				count++;
			}else{
				count = 0;
			}
			if(matriz[maiorLinColMatriz - coluna][maiorLinColMatriz - linha] == jogVez){
				count2++;
			}else{
				count2 = 0;
			}
			// comeca a contar as diagonais apos a diagonal secundaria
			if(count >= numPecas || count2 >= numPecas){
				break;
			}
			coluna++;
			if(linha == 0){
				coluna = 0;
			}
			linha--;
		}
		if(count >= numPecas || count2 >= numPecas){
			break;
		}

		if(linha < maiorLinColMatriz){
			i++;
		}
	}
	if(count >= numPecas || count2 >= numPecas){
		vencedorGeral = 1;
	}
	return NULL;
}

void *verificaVencDiagEsqSupParaDirInf(void *matrizPont){
	int **matriz = (int **)matrizPont;
	int jogVez = jogadorVez + 1;
	int i;
	int j;
	int count = 0;
	int numPecas = tamanhoMatriz / 2; //para nao precisar passar mais um argumento como parametro sempre

	int primeiraLinha  = numPecas - 1;
	int ultimaColuna = tamanhoMatriz - (numPecas - 1);
	int linha = 0;
	int coluna = tamanhoMatriz - 1;
	i = primeiraLinha;
	// for(i = primeiraLinha; i < tamanhoMatriz; i++){
	while(i < tamanhoMatriz || (linha == tamanhoMatriz - 1 && coluna == 0)){
		linha = i;
		while(linha >= 0){
			if(matriz[linha][coluna] == jogVez){
				count++;
			}else{
				count = 0;
			}

			if(count >= numPecas){
				break;
			}
			coluna--;
			if(linha == 0){
				coluna = tamanhoMatriz - 1;
			}
			linha--;
		}
		if(count >= numPecas){
			break;
		}
		// printf("Pulou\n");
		if(linha < tamanhoMatriz - 1){
			i++;
		}
	}
	if(count >= numPecas){
		vencedorGeral = 1;
	}
	return NULL;
}

int main(){
	int linha;
	int coluna;

	int i;
	int j;

	int jogador1 = 0;
	int jogador2 = 1;

	printf("Digite o numero de pedras: \n");
	scanf("%d", &tamanhoMatriz);

	// primeiro jogador escolhido randomicamente
	jogadorVez = (rand() % 2);

	// a matriz tem que ter o dobro de numero de pedras
	tamanhoMatriz *= 2;
	int totalPosicoesDisp = tamanhoMatriz * tamanhoMatriz; // para verificar empate

	// cria uma matriz com alocacao dinamica. Foi o unico modo que consegui criar uma matriz e passar corretamente
	// para as funcoes nas threads
	int **matriz = (int **)malloc(tamanhoMatriz * sizeof(int *));
    for (i = 0; i < tamanhoMatriz; i++){
        matriz[i] = (int *)malloc(tamanhoMatriz * sizeof(int));
	}


	// inicializa a matriz com zeros
	for(i = 0; i < tamanhoMatriz; i++){
		for(j = 0; j < tamanhoMatriz; j++){
			matriz[i][j] = 0;
		}
	}

	// enquanto nao houver vencedor... ao menos ate implementarmos isso
	while(vencedorGeral < 1 && totalPosicoesDisp > 0){
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

		// nao eh necessario usar a varivel mutex, pois as threads usam a matriz apenas para consulta
		// A unica variavel global que eh alterada, ira apenas alterada de 0 para 1, nao importa quem a altera,
		// nao tera influencia nas outras threads
		pthread_t horizontal;
		pthread_t vertical;
		pthread_t diagonal;
		pthread_t diagonalOutra;

		pthread_create(&horizontal, NULL, verificaVencedorHorizontal, matriz);
		pthread_create(&vertical, NULL, verificaVencedorVertical, matriz);
		pthread_create(&diagonal, NULL, verificaVencDiagEsqInfParaDirSup, matriz);
		pthread_create(&diagonalOutra, NULL, verificaVencDiagEsqSupParaDirInf, matriz);

		pthread_join(horizontal, NULL);
		pthread_join(vertical, NULL);
		pthread_join(diagonal, NULL);
		pthread_join(diagonalOutra, NULL);

		// define proximo jogador
		jogadorVez = alteraJogador(jogadorVez);

		totalPosicoesDisp -= 1; // tira uma posicao, quando for zero, eh empate

	}//fim whiele
	printf("\nO jogo acabou! \n");
	if(totalPosicoesDisp == 0){
	    printf("\nTemos um Empate! \n");
	} else{
    	// como o jogador da vez foi alterado dentro do while, alteramos de novo para pegar o vencedor
    	int jogadorVencedor = alteraJogador(jogadorVez);

    	printf("\nTemos um vencedor! \n");

    	escreveMatriz(matriz);

    	printf("\nJogador %d venceu! \n", jogadorVencedor + 1);
    }
	return 0;
}
