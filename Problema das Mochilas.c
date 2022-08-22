  /****************

  LAED1 - Problema da Mochila

  Alunos(as):
    Luis Felipe Pessoa Lopes
  Data: 17/12/2021
  ****************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int* solucao_otima(int peso[], int valor[], int itens, int capacidade[], int quantidade){
  int *compara_valor_total = malloc(sizeof(quantidade));
  for(int i=0; i<quantidade; i++){
    compara_valor_total[i] = 0;
  }
  // Calcular qual o maior valor, no qual o peso é menor ou igual a capacidade da mochila
  for(int k=0; k<quantidade; k++){
    for(int i=0; i<itens; i++){
      // Reinicia peso_total e valor_total, sempre que mudar o primeiro numero analisado
      int peso_total = 0;
      int valor_total = 0;
      // Soma o peso_total e o valor_total com o peso e valor do primeiro numero
      peso_total += peso[i];
      valor_total += valor[i];
      for(int j=0; j<itens; j++){
        // Para não pegar o primeiro numero duas vezes
        if(j !=i){
          // Se o peso for menor ou igual que a capacidade
          if(peso_total + peso[j] <= capacidade[k]){
             // Soma o peso_total e o valor_total com o peso e valor dos outros numeros
            peso_total += peso[j];
            valor_total += valor[j];
          }
        }
      }
      // Compara o último valor_total com o maior valor_total que obtivemos na função
      if(valor_total > compara_valor_total[k]){
        compara_valor_total[k] = valor_total;
      }
    }
  }
  return compara_valor_total;
}


int main(void){
  // Ler o txt e salvar as informações
  int quantidade, itens;
  char entrada[100];
  FILE *arquivo;
  printf("Digite o nome do arquivo: ");
  scanf("%s", entrada);
  //Ler o arquivo
  arquivo = fopen(entrada, "r");
  if (arquivo == NULL){
    return 0;
  }
  // Quantidade de mochilas
  fscanf(arquivo, "%i", &quantidade);
  int capacidade[quantidade];
  // Capacidade de cada mochila
  for(int i=0; i<quantidade; i++){
    fscanf(arquivo, "%i ", &capacidade[i]);
  }
  // Numero de itens que posso colocar nas mochilas
  fscanf(arquivo, "%i", &itens);
  int peso_valor[itens*2];
  int dentro_mochila[quantidade*itens];
  // Peso de valor dos itens
  for(int i=0; i<itens*2; i++){
    fscanf(arquivo, "%i ", &peso_valor[i]);
  }
  // Os itens que tem em cada mochila
  for(int i=0; i<quantidade*itens; i++){
    fscanf(arquivo, "%i ", &dentro_mochila[i]);
  }
  fclose(arquivo);
  //--------------------------------------------
  int peso[itens], valor[itens];
  int k=0, l=0;
  for(int i=0; i < itens*2; i++){
    if(i % 2 == 0){
      // Cria o vetor peso dos itens
      peso[k] = peso_valor[i];
      k++;
    }
    else{
      // Cria o vetor valor dos itens
      valor[l] = peso_valor[i];
      l++;
    }
  }
  // OBS.: a posição do peso e do valor são as mesmas

  // itens dentro da mochila 0 ou 1
  int mochila_bin[quantidade][itens];

  // Percorrer todas as mochilas
  for(int i=0; i<quantidade; i++){
    int k=0;
    // Percorre todos os itens
    for (int j=0; j<itens; j++){
      // Se a quantidade de mochila for igual a 1 apenas pega o que foi passado
      if(quantidade == 1){
        mochila_bin[i][j] = dentro_mochila[j];
      }
      // Se a quantidade de mochila for maior que 1, separa cada iten dentro da sua respectiva mochila
      else{
        mochila_bin[i][j] = dentro_mochila[i+k];
        k+=quantidade;
      }
    }
  }

  int* compara_valor_total;
  compara_valor_total = solucao_otima(peso, valor, itens, capacidade, quantidade);
  // Percorre todas as mochilas
  for(int i=0; i<quantidade; i++){
    int valor_total = 0;
    int peso_total = 0;
    // Percorre todos os itens
    for(int j=0; j<itens; j++){
      // Se tiver o iten dentro da mochila soma o valor e o peso dele, para depois saber qual o tipo da solução
      if(mochila_bin[i][j] == 1){
        valor_total += valor[j];
        peso_total += peso[j];
      }
    }
    // Se a solução for ótima, ou seja, o valor_total é o maior e o peso_total não ultrapassa a capacidade da mochila
    if(compara_valor_total[i] <= valor_total && peso_total <= capacidade[i]){
      printf("Solucao otima.");
      break;
    }
    // Se a solução for inviavel, ou seja, o peso ultrapassa a capacidade da mochila
    else if(peso_total > capacidade[i]){
      printf("Solucao inviavel.");
      break;
    }
    // Se a solução for viavel, mas não ótima (O que sobrou)
    else{
      printf("Solucao viavel mas nao otima.");
      break;
    }
  }








  return 0;
}