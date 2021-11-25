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
 int year_chegada;
 int month_chegada;
 int day_chegada;
 int hours_chegada;
 int minutes_chegada;
 int secounds_chegada;
 //DATA SAIDA
 int year_saida;
 int month_saida;
 int day_saida;
 int hours_saida;
 int minutes_saida;
 int secounds_saida;
 //ESTADO 0=destacionado 1=estacionado
 int estado;
 //PAGAMENTO
 float pagamento;
}parking;

//DECLARAR FUNCAO QUE LEVA ARRAY
void Estacionar(int piso , int linha ,int coluna,char m[],parking parque[][linha][coluna]);
void Destacionar(int piso , int linha ,int coluna,int count,parking parque[][linha][coluna],parking historico[]);
float Pagamento(int p , int l ,int c,parking parque[][linha][coluna]);
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
    parque[p][l][c].day_chegada=local->tm_mday;
    //MOUNTH GET
    parque[p][l][c].month_chegada=local->tm_mon+1;
    //YEAR GET
    parque[p][l][c].year_chegada=local->tm_year+1900;  
    //HOURS GET
    parque[p][l][c].hours_chegada=local->tm_hour;
    //MINUTES GET
    parque[p][l][c].minutes_chegada=local->tm_min;
    //SECOUNDS GET
    parque[p][l][c].secounds_chegada=local->tm_sec;
    //ESTABLECER O ESTADO COMO ESTACIONADO
    parque[p][l][c].estado=1;

}


//FUNCAO PARA DETERMINAR O PAGAMENTO DO PARQUE
float Pagamento(int p , int l ,int c,parking parque[][linha][coluna]){
    float min, horas, dia, mes, ano,sec;
    float total;
    
    //TOTAL DE HORAS PASSADAS
    ano = (float)parque[p][l][c].year_saida - (float)parque[p][l][c].year_chegada;   
    //TOTAL DE MESES PASSADOS
    mes = (float)parque[p][l][c].month_saida - (float)parque[p][l][c].month_chegada;
    //TOTAL DE DIAS PASSADOS
    dia = (float)parque[p][l][c].day_saida - (float)parque[p][l][c].day_chegada;
    //TOTAL DE HORAS PASSADOS
    horas = (float)parque[p][l][c].day_saida - (float)parque[p][l][c].day_chegada;
    //TOTAL DE MINUTOS PASSADOS
    min = (float)parque[p][l][c].day_saida - (float)parque[p][l][c].day_chegada;
    //SECOUNDS GET
    sec = (float)parque[p][l][c].secounds_saida - (float)parque[p][l][c].secounds_chegada;
    //DETERMINAMOS O NUMERO TOTAL DE HORAS E MULTIPLACAMOS PELO TOTAL A PAGAR
    total = (ano * 8640) + (mes * 744) + (dia * 24) + horas + (min / 60);    
    total = total * 2.50;
    
    return total;

}










//FUNCAO PARA SETAR OS DADOS
void Destacionar(int p , int l ,int c,int count, parking parque[][linha][coluna],parking historico[]){
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END  
    //MUDAR O ESTADO SIMPLESMENTE PARA DESTACIONADO
    parque[p][l][c].estado=0;
    //INICIALIZAR DADOS DE TIME PARA SABER A DATA ATUAL
    time_t now;
    time(&now);
    struct tm *data_saida = localtime(&now);
    //DAY GET
    parque[p][l][c].day_saida=data_saida->tm_mday;
    //MOUNTH GET
    parque[p][l][c].month_saida=data_saida->tm_mon+1;
    //YEAR GET
    parque[p][l][c].year_saida=data_saida->tm_year+1900; 
    //HOURS GET
    parque[p][l][c].hours_saida=data_saida->tm_hour;
    //MINUTES GET
    parque[p][l][c].minutes_saida=data_saida->tm_min;
    //SECOUNDS GET
    parque[p][l][c].secounds_saida=data_saida->tm_sec;
    
    //INICIALIZAR FUNCAO PAGAMENTO COM PARAMETROS , DATA DE CHEGADA E DATA DE SAIDA;ARMAZENAR NA ABA "PAGAMENTO"
    parque[p][l][c].pagamento=Pagamento(p,l,c,parque);
    //COLOCAR O OBJETO NO HISTORICO
    historico[count]=parque[p][l][c];  


}



