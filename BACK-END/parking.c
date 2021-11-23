#include <stdio.h>
#include <string.h>
#include <time.h>
int linha,coluna;
//OBJETO PARKING QUE VAI SER ARMAZENADO NUM ARRAY TRIDIMENCIONAL
typedef struct parking
{
 //MATRICULA
 char matricula[9];
 //DATA CHEGADA
 struct tm *chegada;
 //DATA SAIDA
 struct tm *saida;
 //ESTADO 0=destacionado 1=estacionado
 int estado;
}parking;

//DECLARAR FUNCAO QUE LEVA ARRAY
void Estacionar(int piso , int linha ,int coluna,char m[],parking parque[][linha][coluna]);
void Destacionar(int piso , int linha ,int coluna,int count,parking parque[][linha][coluna],parking historico[]);

//DECLARAR O TAMANHO DO ARRAY PARQUE
void setTamanho(int l,int c){
 linha=l;
 coluna=c;
}

//FUNCAO PARA SETAR OS DADOS
void Estacionar(int p , int l ,int c,char m[], parking parque[][linha][coluna]){
//INICIALIZAR DADOS DE TIME
time_t now;
time(&now);
struct tm *local = localtime(&now);
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END

    //PEGAR NA STRING MATRICULA E COLA-LA NA POSICAO INDICADA NO PARAMETRO MATRICULA 
     strcpy(parque[p][l][c].matricula,m);
    //DAY GET
    parque[p][l][c].chegada->tm_mday=local->tm_mday;
    //MOUNTH GET
    parque[p][l][c].chegada->tm_mon=local->tm_mon+1;
    //YEAR GET
    parque[p][l][c].chegada->tm_year=local->tm_year+1900;  
    //HOURS GET
    parque[p][l][c].chegada->tm_hour=local->tm_hour;
    //MINUTES GET
    parque[p][l][c].chegada->tm_min=local->tm_min;
    //ESTABLECER O ESTADO COMO ESTACIONADO
    parque[p][l][c].estado=1;

}


//FUNCAO PARA SETAR OS DADOS
void Destacionar(int p , int l ,int c,int count, parking parque[][linha][coluna],parking historico[]){
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END
    //COLOCAR O OBJETO NO HISTORICO
    historico[count]=parque[p][l][c];    
    //MUDAR O ESTADO SIMPLESMENTE PARA DESTACIONADO
    parque[p][l][c].estado=0;

}


