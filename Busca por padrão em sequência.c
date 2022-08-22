/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as): Luis Felipe Pessoa Lopes

Data: 13/01/2022

****************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define INICIOARRANJO   1
#define MAXTAM          1000

typedef int TipoChave;

typedef int TipoTipo;

typedef int TipoNumElementos;

typedef int TipoPontoMedio;

typedef int TipoApontador;

typedef struct {
  TipoChave Chave;
  TipoTipo Tipo;
  TipoNumElementos NumElementos;
  TipoPontoMedio PontoMedio;
  /* outros componentes */
} TipoItem;

typedef struct {
  TipoItem Item[MAXTAM];
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/*===================================================*/

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = INICIOARRANJO;
  Lista -> Ultimo = Lista -> Primeiro;
}  /* FLVazia */

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}  /* Vazia */

void Insere(TipoItem x, TipoLista *Lista)
{ if (Lista -> Ultimo > MAXTAM) printf("Lista esta cheia\n");
  else { Lista -> Item[Lista -> Ultimo - 1] = x;
         Lista -> Ultimo++;
       }
}  /* Insere */

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ int Aux;

  if (Vazia(*Lista) || p >= Lista -> Ultimo) 
  { printf(" Erro   Posicao nao existe\n");
    return;
  }
  *Item = Lista -> Item[p - 1];
  Lista -> Ultimo--;
  for (Aux = p; Aux < Lista -> Ultimo; Aux++)
    Lista -> Item[Aux - 1] = Lista -> Item[Aux];
}  /* Retira */

void Imprime(TipoLista Lista)
{ int Aux;

  for (Aux = Lista.Primeiro - 1; Aux <= (Lista.Ultimo - 2); Aux++)
    printf("%d\n", Lista.Item[Aux].Tipo);
}  /* Imprime */

/*===================================================*/

int main(int argc, char *argv[])
{ 
  char entrada[100];
  FILE *arquivo;
  printf("Digite o nome do arquivo: ");
  scanf("%s", entrada);
  int tamanho_vetor;
  // Le o que tem dentro do arquivo
  arquivo = fopen(entrada, "r");
  fscanf(arquivo, "%i", &tamanho_vetor);
  int* vetor_txt = malloc(sizeof (int)*tamanho_vetor);
  int cont=0;
  while(!feof(arquivo)){
    fscanf(arquivo, "%i", &vetor_txt[cont]);
    cont++;
  }
  fclose(arquivo);
  //-----------------------------------
  int* elemento = malloc(sizeof (int)*tamanho_vetor);
  int* segmento = malloc(sizeof (int)*tamanho_vetor);
  int tipo[tamanho_vetor];
  // Colocando todos os elementos do segmento como 0
  for(int i=0; i<tamanho_vetor; i++){
    elemento[i] = 0;
    tipo[i] = 0;
  }
  int num_segmento = 1;
  segmento[0] = vetor_txt[0];

  // Definindo o numero de elementos de cada segmento
  int numero = 0;
  int num_inicial = vetor_txt[0];
  for(int i=0; i<tamanho_vetor; i++){
    if(num_inicial == vetor_txt[i]){
      elemento[numero]++;
    }
    else{
      num_inicial = vetor_txt[i];
      segmento[num_segmento] = num_inicial;
      num_segmento++;
      numero++;
      elemento[numero]++;
    }
  }
// Retirando numeros iguais
  for(int i=0; i<num_segmento-1; i++){
    for(int j=0; j<num_segmento; j++){
      if(j != i){
        if(segmento[i] == segmento[j]){
          segmento[j] = 500;
        }
      }
    }
  }
// Colocando em ordem crescente os números que aparecem
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

// Contando quantos segmentos tem 
  int qtde_segmento = 0;
  for(int i=0; i<num_segmento; i++){
    if(segmento[i] != 500){
      qtde_segmento++;
    }
  }
  // Variavel para auxiliar a colocar apenas um numero de cada segmento
  int cont_tipo =0;
  int ult_num = -1;
    for(int i=0; i<tamanho_vetor; i++){
      for(int j=0; j<qtde_segmento; j++){
        if(vetor_txt[i] == segmento[j] && ult_num != vetor_txt[i]){
          ult_num = vetor_txt[i];
          tipo[cont_tipo] = j+1;
          cont_tipo++;
        }
      }
    }
/*==================================================*/

  TipoLista lista;
  TipoItem item;
  FLVazia(&lista);
  int ponto_medio;
  ponto_medio = (tamanho_vetor-1) / 2;


  /*Insere cada chave na lista */
  for (int i=0; i<tamanho_vetor; i++)
    { item.Chave = vetor_txt[i];
      item.Tipo = tipo[i];
      item.NumElementos = elemento[i];
      item.PontoMedio = ponto_medio;
      Insere(item, &lista);
    }
  // Procurando a sequência desejada
  int padrao = 0;
  for(int i=0; i<tamanho_vetor;i++){
    if(lista.Item[i].Tipo == 1){
      if(lista.Item[i+1].Tipo == 3){
        if(lista.Item[i+2].Tipo == 2){
          if(lista.Item[i+3].Tipo == 3){
            if(lista.Item[i+4].Tipo == 1){
              padrao = 1;
            }
          }
        }
      }
    }
  }
  if(padrao == 1){
    printf("Resultado: Padrao encontrado.");
  }
  else{
    printf("Resultado: Padrao nao encontrado.");
  }

  return(0);
}


