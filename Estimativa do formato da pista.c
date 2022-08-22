/****************

LAED1 - Projeto (Parte III) - Busca por padrão em sequência

Alunos(as): Luis Felipe Pessoa Lopes

Data: 28/01/2022

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
  TipoTipo* Tipo;
  TipoNumElementos* NumElementos;
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
    printf("%d ", Lista.Item[Aux].PontoMedio);
}  /* Imprime */

/*==================================================*/
int* calculo_num_elemento(int tamanho_vetor, int* vetor_txt){
  int* elemento = malloc(sizeof (int)*tamanho_vetor);
  // Colocando todos os elementos do segmento como 0
  for(int i=0; i<tamanho_vetor; i++){
    elemento[i] = 0;
  }

  // Definindo o numero de elementos de cada segmento
  int numero = 0;
  int num_inicial = vetor_txt[0];
  for(int i=0; i<tamanho_vetor; i++){
    if(num_inicial == vetor_txt[i]){
      elemento[numero]++;
    }
    else{
      num_inicial = vetor_txt[i];
      numero++;
      elemento[numero]++;
    }
  }
  return elemento;
}

int* programa(int tamanho_vetor, int* vetor_txt, int* tipo){
  int* segmento = malloc(sizeof (int)*tamanho_vetor);
  // Colocando todos os elementos do segmento como 0
  int num_segmento = 1;
  // Definindo o numero de elementos de cada segmento
  int num_inicial = vetor_txt[0];
  for(int i=0; i<tamanho_vetor; i++){
    if(num_inicial != vetor_txt[i]){
      num_inicial = vetor_txt[i];
      segmento[num_segmento] = num_inicial;
      num_segmento++;
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
  return tipo;
}

int calculo_ponto_medio(int* vetor_txt, int tamanho_vetor){
  int ponto_medio;
  int vermelhos = 0;
  int branco = 0;
  for(int i=0; i<tamanho_vetor; i++){
    if(vetor_txt[i] == 128 && vetor_txt[i+1] == 255){
      branco++;
    }
    if(branco < 1){
      vermelhos++;
    }
  }
  if(branco == 0){
    vermelhos = 0;
  }
  ponto_medio = vermelhos/2;
  return ponto_medio;
}


int calculo_numero_segmentos(int tamanho_vetor, int* tipo){
  int* elemento = malloc(sizeof (int)*tamanho_vetor);
  int* segmento = malloc(sizeof (int)*tamanho_vetor);
  // Colocando todos os elementos do segmento como 0
  for(int i=0; i<tamanho_vetor; i++){
    elemento[i] = 0;
  }
  int num_segmento = 0;

  // Definindo o numero de elementos de cada segmento
  int numero = 0;
  int num_inicial = tipo[0];
  for(int i=0; i<tamanho_vetor; i++){
    if(num_inicial == tipo[i]){
      elemento[numero]++;
    }
    else{
      num_inicial = tipo[i];
      segmento[num_segmento] = num_inicial;
      num_segmento++;
      numero++;
      elemento[numero]++;
    }
  }
  return num_segmento;
/*==================================================*/
}

int procura_padrao(int tamanho_vetor, int* tipo){
  int num_segmento = calculo_numero_segmentos(tamanho_vetor, tipo);
  // Procurando a sequência desejada
  // padrao = 0 nao tem pista
  // padrao = 1 tem pista
  int padrao = 0;
  for(int i=0; i<num_segmento;i++){
    if(tipo[i] == 1){
      if(tipo[i+1] == 3){
        if(tipo[i+2] == 2){
          if(tipo[num_segmento-1] == 1){
            if(tipo[num_segmento-2] == 3){
              if(tipo[num_segmento-3] == 2){
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
  TipoLista lista;
  TipoItem item;
  FLVazia(&lista);

  char entrada[100];
  FILE *arquivo;
  printf("Digite o nome do arquivo: ");
  scanf("%s", entrada);
  int tamanho_vetor;
  int L;
  int padrao = 0;
  // Le o que tem dentro do arquivo
  arquivo = fopen(entrada, "r");
  fscanf(arquivo, "%i", &L);
  fscanf(arquivo, "%i", &tamanho_vetor);
  int* vetor_txt = malloc(sizeof (int)*tamanho_vetor);
  int* tipo = malloc(sizeof (int)*tamanho_vetor);
  for(int i=0; i<L; i++){
    for(int j=0; j<tamanho_vetor; j++){
      fscanf(arquivo, "%i", &vetor_txt[j]);
    }
    item.Chave = i;
    item.Tipo = programa(tamanho_vetor, vetor_txt, tipo);
    item.NumElementos = calculo_num_elemento(tamanho_vetor, vetor_txt);
    item.PontoMedio = calculo_ponto_medio(vetor_txt, tamanho_vetor);
    padrao += procura_padrao(tamanho_vetor, tipo);
    for(int j=0; j<tamanho_vetor; j++){
      vetor_txt[j] = 0;
      tipo[j] = 0;
    } 
    fscanf(arquivo, "%i", &tamanho_vetor);
    Insere(item, &lista);
  }
  fclose(arquivo);
  int num_dif_zero = 0;
  int cont = 0;
  for(int i=0; i<L; i++){
    if(lista.Item[i].PontoMedio != 0 && cont == 0){
        num_dif_zero = i;
        cont++;
      }
  }
  for(int i=0; i<L; i++){
    if(lista.Item[L-1].PontoMedio - lista.Item[num_dif_zero].PontoMedio < 200 && lista.Item[L-1].PontoMedio - lista.Item[num_dif_zero].PontoMedio > 0 && padrao > 1){
      printf("Resultado: Pista em linha reta.");
      break;
    }
    else if(lista.Item[0].PontoMedio > lista.Item[L-1].PontoMedio && padrao > 1){
      printf("Resultado: Curva a direita.");
      break;
    }
    else if(lista.Item[0].PontoMedio < lista.Item[L-1].PontoMedio && padrao > 1){
      printf("Resultado: Curva a esquerda.");
      break;
    }
    else{
      printf("Resultado: Formato da pista nao estimado.");
      break;
    }
  }
  //-----------------------------------
  return(0);
}



