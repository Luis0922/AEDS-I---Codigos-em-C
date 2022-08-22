#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/*
Caso teste:
01111tinhkn#ftyH#y#Xwfxfitufjxmsfk#jrqjzjytrhjr#fwfiknxji#v#sjx#nhjy#w#f#jsju#t#xjcjjih#wkfw#F
*/

//Função que le o arquivo
char *ler_arquivo(char* entrada, char* mensagem){
  FILE *arquivo;
  //Ler o arquivo
  arquivo = fopen(entrada, "r");
  if (arquivo == NULL){
    return 0;
  }
  //Salvar o codigo em uma string 'mensagem'
  int i = 0;
  while(!feof(arquivo)){
    fscanf(arquivo, "%c ", &mensagem[i]);
    i++;
  }
  fclose(arquivo);
  if(mensagem[strlen(mensagem)] == 35){
    mensagem[strlen(mensagem)] = '\0';
  }
  printf("%s\n", mensagem);
  return mensagem;
}

// Função que apaga os num binarios
char *del_numeros(char* mensagem, int numeros){
  // Apaga os num binarios
  for(int i=0; i<strlen(mensagem); i++){
    mensagem[i] = mensagem[i+numeros];
  }
  return mensagem;
}

//Funcao que deleta o carac extra
char *del_extra(char* mensagem){
  int numeros = 0;
  int posicao = 0;
  //percorre toda a string e conta qtos 1 e 0 possui
  for(int i=0; i<strlen(mensagem);i++){
    //retorno = strcmp(mensagem[i], "0");
    if(mensagem[i] == '1' || mensagem[i] == '0' ){
      numeros++;
    }
  }
  //transforma binario em decimal
  int exp=0;
  for(int i=numeros-1; i>=0;i--){
    if(mensagem[i] == '1'){
      posicao = posicao + 1*pow(2,exp);
    }
    exp++;
  }
  //Chama a função para apagar os num binarios
  mensagem = del_numeros(mensagem, numeros);
  // Apaga o carac extra
  for(int i=posicao-1; i<strlen(mensagem); i++){
    mensagem[i] = mensagem[i+1];
  }
  return mensagem;
}

char *criptografia(char* mensagem){
  int aux;
  // Pega as 2 ultimas letras e troca com as 2 primeiras
  int j = 2;
  for(int i=0; i<(int)(strlen(mensagem)/2); i++){
    if(i % 4 == 0){
      aux = mensagem[i];
      mensagem[i] = mensagem[i+strlen(mensagem)-j];
      mensagem[i+strlen(mensagem)-j] = aux;
      aux = mensagem[i+1];
      mensagem[i+1] = mensagem[i+1+strlen(mensagem)-j];
      mensagem[i+1+strlen(mensagem)-j] = aux;
      j+=8;
    }
  }
  //Inverte as letras a cada dupla
  for(int i=0; i<strlen(mensagem); i++){
    if(i % 2 == 0){
      aux = mensagem[i];
      mensagem[i] = mensagem[i+1];
      mensagem[i+1] = aux;
    }
  }
  return mensagem;
}

char posicao_letra(char letra){
  char alfabeto[54] = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char cifrado[54] = "fghijklmnopqrstuvwxyzabcde#FGHIJKLMNOPQRSTUVWXYZABCDE";
  // Olha a posicao da letra no cifrado e pega letra correspondente do alfabeto
  for(int i=0; i<strlen(cifrado);i++){
    if(letra == cifrado[i]){
      return alfabeto[i];
    }
  }
  return 0;
}

void mensagem_original(char* mensagem){
  char *traducao = malloc(sizeof(100));
  for(int i=0; i<strlen(mensagem);i++){
    // Pega a letra do alfabeto correspondente
    traducao[i] = posicao_letra(mensagem[i]);
  }
  //Traduz a mensagem codificada para a original
  for(int i=0; i<strlen(mensagem);i++){
    mensagem[i]=traducao[i];
  }
  printf("\n----------------------\n");
  printf("Mensagem decodificada:");
  printf("\n----------------------\n");
  printf("%s\n", mensagem);
}

int main(void) {
  char entrada[100];
  char mensagem[10000] = {'\0'};
  printf("Digite o nome do arquivo: ");
  scanf("%s", entrada);
  printf("\n--------------------\n");
  printf("Mensagem codificada:");
  printf("\n--------------------\n");
  // Funcao que lê o arquivo: ler_arquivo

  //Funcao que exclui o carac extra: del_extra

  // Funcao que descodifica a mensagem: criptografia

  // Funcao que traduz a mensagem codificada para original: mensagem_original
  mensagem_original(criptografia(del_extra(ler_arquivo(entrada, mensagem))));
return 0;
}