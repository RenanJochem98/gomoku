#include <pthread.h>
#include <time.h>
#include <math.h>
# include <stdio.h>

int vencedorGeral = 0;
int tamanhoMatriz;
int jogadorVez;
pthread_mutex_t mutex;
// funcao para imprimir a matriz na tela. Apenas para despoluir a funcao principal
void escreveMatriz(int matriz[tamanhoMatriz][tamanhoMatriz]){
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

int verificaVencedorHorizontal(int matriz[tamanhoMatriz][tamanhoMatriz]){
	pthread_mutex_lock(&mutex);
	int jogVez = jogadorVez + 1;
	int i;
	int j;
	int count = 0;
	int numPecas = tamanhoMatriz / 2; //para nao precisar passar mais um argumento como parametro sempre
	int vencedor = 0;

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
	printf("Vertical, jogador vez: %d \n", jogVez);
	printf("Horizontal, count: %d \n", count);
	printf("Horizontal, NumPecas: %d \n", numPecas);
	if(count >= numPecas){
		vencedor = 1;
		vencedorGeral = 1;
		printf("Vencedor geral deveria ser alterado aqui: Horizontal\n");
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	return vencedor;
}

int verificaVencedorVertical(int matriz[tamanhoMatriz][tamanhoMatriz]){
	pthread_mutex_lock(&mutex);
	int jogVez = jogadorVez + 1;
    int i;
    int j;
    int count = 0;
    int numPecas = tamanhoMatriz / 2;
    int vencedor = 0;

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
	printf("Vertical, jogador vez: %d \n", jogVez);
	printf("Vertical, count: %d \n", count);
	printf("Vertical, NumPecas: %d \n", numPecas);
	if(count >= numPecas){
		vencedor = 1;
		vencedorGeral = 1;
		printf("Vencedor geral deveria ser alterado aqui: Vertical\n");
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	return vencedor;
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

int verificaVencedor(int matriz[tamanhoMatriz][tamanhoMatriz]){
	pthread_t horizontal;
	pthread_t vertical;

	struct params {
		int matriz[tamanhoMatriz][tamanhoMatriz];
	};

	struct params p;
	p.matriz[tamanhoMatriz][tamanhoMatriz] = matriz;

	int vencedores[2] = {0, 0};

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&horizontal, NULL, verificaVencedorHorizontal, &p);
	pthread_create(&vertical, NULL, verificaVencedorVertical, &p);

	pthread_join(&horizontal, NULL);
	pthread_join(&vertical, NULL);

	pthread_mutex_destroy(&mutex);

	printf("Vencedor Geral %d\n", vencedorGeral);
	int i;
	int maior = 0;
	// for(i = 0; i < 2; i++){
	// 	// printf("Vencedor, retorno: %d \n", vencedores[i]);
	// 	if(vencedores[i] > maior){
	// 		maior = vencedores[i];
	// 	}
	// }

	return maior;
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

	int matriz[tamanhoMatriz][tamanhoMatriz];

	int contaPecaTotal = tamanhoMatriz * tamanhoMatriz;

	// inicializa a matriz
	for(i = 0; i < tamanhoMatriz; i++){
			for(j = 0; j < tamanhoMatriz; j++){
				matriz[i][j] = 0;
			}
		}

	// enquanto nao houver vencedor... ao menos ate implementarmos isso
	while(vencedor < 1 && vencedorGeral < 1){

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


		// vencedor = verificaVencedorHorizontal(tamanhoMatriz, matriz, jogadorVez + 1);
		// vencedor = verificaEmpate(contaPecaTotal, tamanhoMatriz, matriz, jogadorVez + 1);
		// vencedor = verificaVencedorVertical(tamanhoMatriz, matriz, jogadorVez + 1);
		// define proximo jogador
		vencedor = verificaVencedor(matriz);
		jogadorVez = alteraJogador(jogadorVez);

		contaPecaTotal = contaPecaTotal - 1;

	}
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
