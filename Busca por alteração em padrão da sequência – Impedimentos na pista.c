/****************

LAED1 - Projeto (Parte II) - Busca por padrão em sequência

Alunos(as): Luis Felipe Pessoa Lopes

Data: 21/01/2022

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
    printf("%d ", Lista.Item[Aux].Tipo);
}  /* Imprime */

/*==================================================*/

int programa(int tamanho_vetor, int* vetor_txt){
  int* elemento = malloc(sizeof (int)*tamanho_vetor);
  int* segmento = malloc(sizeof (int)*tamanho_vetor);
  int tipo[tamanho_vetor];
  // Colocando todos os elementos do segmento como 0
  for(int i=0; i<tamanho_vetor; i++){
    elemento[i] = 0;
    tipo[i] = 0;
  }
  int num_segmento = 1;

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

// Contando quantos segmentos tem 
  int qtde_segmento = 0;
  for(int i=0; i<num_segmento; i++){
    if(segmento[i] != 500){
      qtde_segmento++;
    }
  }
  for(int i=0; i<num_segmento; i++){
    if(segmento[i] == 0){
      tipo[i] = 1;
    }
    if(segmento[i] == 128){
      tipo[i] = 2;
    }
     if(segmento[i] == 255){
      tipo[i] = 3;
    }
  }
/*==================================================*/

  TipoLista lista;
  TipoItem item;
  FLVazia(&lista);
  int ponto_medio;
  ponto_medio = (tamanho_vetor-1) / 2;


  /*Insere cada chave na lista */
  for (int i=0; i<num_segmento; i++)
    { item.Chave = vetor_txt[i];
      item.Tipo = tipo[i];
      item.NumElementos = elemento[i];
      item.PontoMedio = ponto_medio;
      Insere(item, &lista);
    }
  // Procurando a sequência desejada
  // padrao = 0 pista sem impedimento
  // padrao = 1 pista com impedimento
  int padrao = 0;
  for(int i=0; i<num_segmento;i++){
    if(lista.Item[i].Tipo == 1){
      if(lista.Item[i+1].Tipo == 3){
        if(lista.Item[i+2].Tipo == 2){
          if(lista.Item[num_segmento-1].Tipo == 1){
            if(lista.Item[num_segmento-2].Tipo == 3){
              if(lista.Item[num_segmento-3].Tipo == 2 && num_segmento-3 != i+2){
                padrao = 1;
              }
            }
          }    
        }
      }
    }
  }
  return padrao;
}


int main(int argc, char *argv[])
{ 
  char entrada[100];
  FILE *arquivo;
  printf("Digite o nome do arquivo: ");
  scanf("%s", entrada);
  int tamanho_vetor;
  int L;
  // Le o que tem dentro do arquivo
  arquivo = fopen(entrada, "r");
  fscanf(arquivo, "%i", &L);
  fscanf(arquivo, "%i", &tamanho_vetor);
  int* vetor_txt = malloc(sizeof (int)*tamanho_vetor);
  int padrao;
  int cont_padrao1 = 0;
  for(int i=0; i<L; i++){
    for(int j=0; j<tamanho_vetor; j++){
      fscanf(arquivo, "%i", &vetor_txt[j]);
    }
    padrao = programa(tamanho_vetor, vetor_txt);
    if(padrao == 1){
      cont_padrao1++;
    }
    for(int j=0; j<tamanho_vetor; j++){
      vetor_txt[j] = 0;
    }
    fscanf(arquivo, "%i", &tamanho_vetor);
  }  
  fclose(arquivo);
  if(cont_padrao1 > 0){
    printf("Resultado: Pista com impedimento.");
  }
  else{
    printf("Resultado: Pista sem impedimento.");
  }
  //-----------------------------------
  return(0);
}



