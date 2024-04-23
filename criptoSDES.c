#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int p10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int p8[8] = {6, 3, 7, 4, 8, 5, 10, 9};

int IP[8] = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_inv[8] = {4, 1, 3, 5, 7, 2, 8, 6};

int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1};

int caixa_s0[4][4] = {1, 0, 3, 2, 3, 2, 1, 0, 0, 2, 1, 3, 3, 1, 3, 2};
int caixa_s1[4][4] = {1, 1, 2, 3, 2, 0, 1, 3, 3, 0, 1, 0, 2, 1, 0, 3};

int binario[2];

int p4[4] = {2, 4, 3, 1};

int t_bloco[4];
int bloco_p4[4];
int bloco_p4_sec[4];

/*####################################################*/
int para_decimal(int a, int b){
  int x;
  if(a==1 && b==1){
    x = 3;
  }else if(a==0 && b==1){
    x = 1;
  }else if(a==1 && b==0){
    x = 2;
  }else if(a==0 && b==0){
    x = 0;
  }  
  return x;
}

/*####################################################*/
void para_binario(int num){
  int x;
  if(num == 3){
    for(x=0; x<2; x++){
      binario[x] = 1;
    }
  }else if(num == 1){
    binario[0] = 0;
    binario[1] = 1;
  }else if(num == 2){
    binario[0] = 1;
    binario[1] = 0;
  }else if(num == 0){
    for(x=0; x<2; x++){
      binario[x] = 0;
    }
  }
}

/*####################################################*/
void FK(int p_bloco[], int s_bloco[], int K[]){
  int bloco_ep[8];
  int bloco_s0[4];
  int bloco_s1[4];
  int bloco_s0s1[4];
  int i = 0;
  int j = 4;

  /*E/P*/
  j=0;
  for(i=0; i<8; i++){
    bloco_ep[i] = s_bloco[EP[i]-1];
  }

  /*XOR COM A PRIMEIRA CHAVE DO PARAMENTRO*/
  for(i=0; i<8; i++){
    bloco_ep[i] = bloco_ep[i] ^ K[i];
  }
  /*CAIXAS S0 E S1*/
  i=0;
  j=4;
  while((i<4)&&(j<8)){
    bloco_s0[i] = bloco_ep[i]; 
    bloco_s1[i] = bloco_ep[j];
    i++;
    j++;
  }
  
  int lin = para_decimal(bloco_s0[0], bloco_s0[3]);
  int col = para_decimal(bloco_s0[1], bloco_s0[2]);
  int s0 = caixa_s0[lin][col];
  
  lin = para_decimal(bloco_s1[0], bloco_s1[3]);
  col = para_decimal(bloco_s1[1], bloco_s1[2]);
  int s1 = caixa_s1[lin][col];
  
  /*P4 E XOR*/
  para_binario(s0);
  bloco_s0s1[0] = binario[0];
  bloco_s0s1[1] = binario[1];
  para_binario(s1);
  bloco_s0s1[2] = binario[0];
  bloco_s0s1[3] = binario[1];
  
  for(i=0; i<4; i++){
    bloco_p4[i] = bloco_s0s1[p4[i]-1];
  }
  for(i=0; i<4; i++){
    bloco_p4[i] = bloco_p4[i] ^ p_bloco[i];
  }
}

/*####################################################*/
void SW(int K[]){
  int i;
  for(i=0; i<4; i++){
    bloco_p4_sec[i] = bloco_p4[i];
  }
  FK(t_bloco, bloco_p4, K);
}

/*###################################################*/
int permutaIPinv(){
  int resultado[8];
  int text[8];
  int i;
  int j=0;
  for(i=0; i<8; i++){
    if(i<4){
      text[i] = bloco_p4[i];
    }else{
      text[i] = bloco_p4_sec[j];
      j++;
    }
  }
  for(i=0; i<8; i++){
    resultado[i] = text[IP_inv[i]-1];
  }
  for(i=0; i<8; i++){
    printf("%d", resultado[i]);
  }
  printf("\n");
}
/*####################################################*/
void permutaIP(int bloco[], int K[]){
  int i;
  int j;
  int perm_inicial[8];
  int p_bloco[4];
  int s_bloco[4];
  for(i=0; i<8; i++){
    perm_inicial[i] = bloco[IP[i]-1];
  }
  i=0;
  j=4;
  while((i<4)&&(j<8)){
    p_bloco[i] = perm_inicial[i];
    s_bloco[i] = perm_inicial[j];
    t_bloco[i] = perm_inicial[j];
    i++;
    j++;
  }
  FK(p_bloco, s_bloco, K);
}

/*####################################################*/
void permutaChave(int chave[], int K1[], int K2[]){
  int key[10];
  int permuta10[10];
  int LS1_prim_quint[5];
  int LS1_sec_quint[5];
  int LS2_prim_quint[5];
  int LS2_sec_quint[5];
  int i;
  int j=5;

  for(i=0; i<10; i++){
    permuta10[i] = chave[p10[i]-1];
  }
  for(i=0; i<5; i++){
    if(i==4){
      LS1_prim_quint[i] = permuta10[0];
    }else{  
      LS1_prim_quint[i] = permuta10[i+1];
    }
  }
  for(i=0; i<5; i++){
    if(j==9){
      LS1_sec_quint[i] = permuta10[5];
    }else{  
      LS1_sec_quint[i] = permuta10[j+1];
    }
    j++;
  }
  
  i=0;
  j=5;
  while ((i<5)&&(j<10)){
    permuta10[i] = LS1_prim_quint[i];
    permuta10[j] = LS1_sec_quint[i];
    i++;
    j++;
  }
  for(i=0; i<8; i++){
    K1[i] = permuta10[p8[i]-1];
  }

  i=0;
  j=2;
  while((i<5)&&(j<7)){
    if(j==5){
      LS2_prim_quint[i] = LS1_prim_quint[0];
      LS2_sec_quint[i] = LS1_sec_quint[0];
    }else if(j==6){
      LS2_prim_quint[i] = LS1_prim_quint[1];
      LS2_sec_quint[i] = LS1_sec_quint[1];
    }else{  
      LS2_prim_quint[i] = LS1_prim_quint[j];
      LS2_sec_quint[i] = LS1_sec_quint[j];
    }
    i++;
    j++;
  }

  i=0;
  j=5;
  while ((i<5)&&(j<10)){
    permuta10[i] = LS2_prim_quint[i];
    permuta10[j] = LS2_sec_quint[i];
    i++;
    j++;
  }
  for(i=0; i<8; i++){
    K2[i] = permuta10[p8[i]-1];
  }
}

/*####################################################*/
void S_DES(char chave[], char bloco[]){
  int key[10];
  int K1[8];
  int K2[8];
  int text[8];
  int i;
  for(i=0; i<10; i++){
    if (chave[i]=='0'){
      key[i] = 0;
    }else{
      key[i] = 1;
    }
  }
  permutaChave(key, K1, K2);  
  for(i=0; i<8; i++){
    if (bloco[i]=='0'){
      text[i] = 0;
    }else{
      text[i] = 1;
    }
  }
  permutaIP(text, K1);
  SW(K2);
  permutaIPinv();
}

/*##########################################################*/
void S_DES_INV(char chave[], char bloco[]){
  int key[10];
  int K1[8];
  int K2[8];
  int text[8];
  int i;
  for(i=0; i<10; i++){
    if (chave[i]=='0'){
      key[i] = 0;
    }else{
      key[i] = 1;
    }
  }
  permutaChave(key, K1, K2);  
  for(i=0; i<8; i++){
    if (bloco[i]=='0'){
      text[i] = 0;
    }else{
      text[i] = 1;
    }
  }
  permutaIP(text, K2);
  SW(K1);
  permutaIPinv();
}

/*#########################################################*/
int main(int argc, char** argv){
  int L;
  scanf("%d", &L);
  char operacao[L];
  int i;
  int j;
  int len_chv;
  int len_bloco;
  char chave[10];
  char bloco[8];

  for(i=0; i<L; i++){
    scanf("%s", &operacao[i]);
    if(operacao[i] == 'C'){
      scanf("%s", chave);
      len_chv = sizeof(chave)/sizeof(chave[0]);
      scanf("%s", bloco);
      len_bloco = sizeof(bloco)/sizeof(bloco[0]);
      if(len_chv == 10 && len_bloco ==8){
        S_DES(chave, bloco);
      }else{
        exit(1);
      }
    }else if(operacao[i] == 'D'){
      scanf("%s", chave);
      len_chv = sizeof(chave)/sizeof(chave[0]);
      scanf("%s", bloco);
      len_bloco = sizeof(bloco)/sizeof(bloco[0]);
      if(len_chv == 10 && len_bloco == 8){
        S_DES_INV(chave, bloco);
      }else{
        exit(1);
      }
    }else{
      exit(1);
    }
  }
  return 0;
}
