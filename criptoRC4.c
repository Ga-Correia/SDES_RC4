#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(unsigned char *x, unsigned char *y){
  unsigned char tmp = *x;
  *x = *y;
  *y = tmp;
}

void KSA(unsigned char S[], unsigned char chave[]){
  unsigned int i;
  unsigned int j = 0;
  unsigned int size_k = strlen((char*)chave);
  for(i=0; i<256; i++){
    S[i] = i;
  }
  for(i=0; i<256; i++){
    j = (j + S[i] + chave[i % size_k])%256;
    swap(&S[i], &S[j]);
  }
}

void PGRA(unsigned char S[], unsigned char texto[]){
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int h;
  unsigned int size_txt = strlen((char*)texto);
  unsigned char cifra[size_txt];
  for(h=0; h < size_txt; h++){
    i = (i+1) % 256;
    j = (j+S[i]) % 256;
    swap(&S[i], &S[j]);
    cifra[h] = S[(S[i] + S[j]) % 256] ^ texto[h];
  }
  
  for(i=0; i<size_txt; i++){
    printf("%x", cifra[i]);
  }
}

int main(int argc, char **argv) {
  unsigned char texto[256];
  unsigned char chave[256];
  unsigned char S[256];

  scanf("%s", texto);
  scanf(" %s", chave);
  
  KSA(S, chave);
  PGRA(S, texto);
  
  return 0;
}