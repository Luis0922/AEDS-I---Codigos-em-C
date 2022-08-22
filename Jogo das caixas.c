#include <stdio.h>
#include <string.h>
/*
Arquivo teste.txt:
4
10
-15 2
3 20 -50
8 25 30 42
*/
int resultado(int tamanho, int texto[tamanho][100], int soma, int k){
  for(int i=k-1; i>=0;i--){
      for(int j=0; j<=i;j++){
        printf("%i + ", texto[i][j]);
        soma+=texto[i][j];
      }
    }
  printf("\b\b = %i ", soma);
  return soma;
}

int main(void) {
  char entrada[20];
  int resultado(int tamanho, int texto[tamanho][100], int soma, int k);
  int tamanho, i, soma, maior, maiori, maiorj;
  FILE *arquivo;
  printf("Digite o nome do arquivo de entrada: ");
  scanf("%s", entrada);
  arquivo = fopen(entrada, "r");
  fscanf(arquivo, "%i", &tamanho);
  int texto[tamanho][100];
  if (arquivo == NULL){
    return 0;
  }
  i = 0;
  while(!feof(arquivo)){
    for(int j=0;j<=i;j++){
      fscanf(arquivo, "%i ", &texto[i][j]);
    }
    i++;
  }
  fclose(arquivo);
  maior = 0;
  maiori = 0;
  maiorj = 0;
  for(int k=tamanho-1; k>=0; k--){
    for(int j=0; j<=k; j++){
      printf("\n%i + ", texto[k][j]);
      soma = resultado(tamanho, texto, texto[k][j], k);
      if(soma > maior){
        maior = soma;
        maiori = k+1;
        maiorj = j+1;
      }
    }
  }
  printf("\nResposta: %i fileira %i, caixa %i.", maior,maiori, maiorj);
return 0;
}