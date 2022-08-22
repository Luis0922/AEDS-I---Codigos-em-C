#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
# Entrada:
11
0 0 0 128 128 0 0 255 255 255 255
# Saída:
1 2 1 3
3 2 2 4

*/

int main(void){
  char entrada[100];
  FILE *arquivo;
  printf("Digite o nome do arquivo: ");
  scanf("%s", entrada);
  int tamanho_vetor;
  // Le o que tem dentro do arquivo
  arquivo = fopen(entrada, "r");
  fscanf(arquivo, "%i", &tamanho_vetor);
  int* vetor = malloc(sizeof (int)*tamanho_vetor);
  int i=0;
  while(!feof(arquivo)){
    fscanf(arquivo, "%i", &vetor[i]);
    i++;
  }
  fclose(arquivo);
  //-----------------------------------
  int* elemento = malloc(sizeof (int)*tamanho_vetor);
  int* segmento = malloc(sizeof (int)*tamanho_vetor);
  // Colocando todos os elementos do segmento como 0
  for(int i=0; i<tamanho_vetor; i++){
    elemento[i] = 0;
  }
  int num_segmento = 1;
  segmento[0] = vetor[0];

  // Definindo o numero de elementos de cada segmento
  int numero = 0;
  int num_inicial = vetor[0];
  for(int i=0; i<tamanho_vetor; i++){
    if(num_inicial == vetor[i]){
      elemento[numero]++;
    }
    else{
      num_inicial = vetor[i];
      segmento[num_segmento] = num_inicial;
      num_segmento++;
      numero++;
      elemento[numero]++;
    }
  }

  for(int i=0; i<num_segmento-1; i++){
    for(int j=0; j<num_segmento; j++){
      if(j != i){
        if(segmento[i] == segmento[j]){
          segmento[j] = 500;
        }
      }
    }
  }
  int aux;
  for(int i=0; i<num_segmento-1; i++){
    for(int j=0; j<num_segmento; j++){
      if(i <= j){
        if(segmento[i] > segmento[j]){
          aux = segmento[i];
          segmento[i] = segmento[j];
          segmento[j] = aux;
        }
      }
    }
  }

  // 
  int qtde_segmento = 0;
  for(int i=0; i<num_segmento; i++){
    if(segmento[i] != 500){
      qtde_segmento++;
    }
  }
  printf("Matriz:\n");
  // Variavel para auxiliar a colocar apenas um numero de cada segmento
  int ult_num = -1;
    for(int i=0; i<tamanho_vetor; i++){
      for(int j=0; j<qtde_segmento; j++){
        if(vetor[i] == segmento[j] && ult_num != vetor[i]){
          ult_num = vetor[i];
          printf("%i ", j+1);
        }
      }
    }
    printf("\n");
    for(int i=0; i<=numero; i++){
      printf("%i ", elemento[i]);
    }


  return 0;
}