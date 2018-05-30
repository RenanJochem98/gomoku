# include <stdio.h>
#include <time.h>
#include <math.h>
// funcao para imprimir a matriz na tela. Apenas para despoluir a funcao principal
void escreveMatriz(int tamMatriz, int matriz[tamMatriz][tamMatriz]){
	int i;
	int j;
	for(i = 0; i < tamMatriz; i++){
			for(j = 0; j < tamMatriz; j++){
				printf("%d ", matriz[i][j]);
			}
			printf("\n");
		}
}

// como sao apenas dois jogadores, 0 e 1, para alterar entre eles basta diminuir um e pegar o valor positivo
int alteraJogador(int jogador){
	return abs(jogador - 1);
}

int verificaVencedorHorizontal(int tamMatriz, int matriz[tamMatriz][tamMatriz], int jogadorVez){
	int i;
	int j;
	int count = 0;
	int numPecas = tamMatriz / 2; //para nao precisar passar mais um argumento como parametro sempre
	int vencedor = 0;
	
	for(i = 0; i < tamMatriz; i++){
		for(j = 0; j < tamMatriz; j++){
			if(matriz[i][j] == jogadorVez){
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
		vencedor = 1;
	}
	return vencedor;
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
	int vencedor = 0;
	int linha;
	int coluna;
	int tamanhoMatriz;
	
	int jogador1 = 0;
	int jogador2 = 1;
	
	int i;
	int j;
	
	printf("Digite o numero de pedras: \n");
	scanf("%d", &tamanhoMatriz);
	
	int jogadorVez = (rand() % 2);
	
	// a matriz tem que ter o dobro de numero de pedras
	tamanhoMatriz *= 2;
	
	int matriz[tamanhoMatriz][tamanhoMatriz];
	
	// inicializa a matriz
	for(i = 0; i < tamanhoMatriz; i++){
			for(j = 0; j < tamanhoMatriz; j++){
				matriz[i][j] = 0;
			}
		}
	
	// enquanto nao houver vencedor... ao menos ate implementarmos isso
	while(vencedor < 1){
		
		// imprime a matriz na tela
		escreveMatriz(tamanhoMatriz, matriz);
		
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
		
		
		vencedor = verificaVencedorHorizontal(tamanhoMatriz, matriz, jogadorVez + 1);
		
		// define proximo jogador
		jogadorVez = alteraJogador(jogadorVez);
		
		
	}
	
	// como o jogador da vez foi alterado dentro do while, alteramos de novo para pegar o vencedor
	int jogadorVencedor = alteraJogador(jogadorVez);
	
	printf("\nTemos um vencedor! \n");
	
	escreveMatriz(tamanhoMatriz, matriz);
	
	printf("\nJogador %d venceu! \n", jogadorVencedor + 1);
	printf("Parou");
	
	return 0;
}


