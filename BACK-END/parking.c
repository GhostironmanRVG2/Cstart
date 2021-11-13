#include <stdio.h>
#include <string.h>
//OBJETO PARKING QUE VAI SER ARMAZENADO NUM ARRAY TRIDIMENCIONAL
typedef struct parking
{
 char matricula[9];
}parking;





//DECLARACAO DA FUNCAO COM OS PARAMETROS
void Estacionar(char matricula[],int estacionamento, struct parking parque[][2][2]);



//FUNCAO ESTACIONAR PARA ESTACIONAR TENDO UMA MATRICULA ,NMR DE ESTACIONAMENTO E O PARQUE
void Estacionar(char matricula[],int estacionamento, struct parking parque[][2][2]){

//ACIONAR UM METODO CONSOANTE O ESTACIONAMENTO
switch (estacionamento)
{
case 1:
//CASO SEJA O ESTACIONAMENTO 1 , ARMAZENAR ENTAO NAS COORDENADAS 0 0 0 OS DADOS!
strcpy(parque[0][0][0].matricula,matricula);
break;

case 2:
strcpy(parque[0][0][1].matricula,matricula);   
break;

case 3:
strcpy(parque[0][1][0].matricula,matricula);   
break;

case 4:
strcpy(parque[0][1][1].matricula,matricula);   
//PRIMEIRO ANDAR FEITO 
break;

case 5:
strcpy(parque[1][0][0].matricula,matricula);
break;

case 6:
strcpy(parque[1][0][1].matricula,matricula);
break;

case 7:
strcpy(parque[1][1][0].matricula,matricula);  
break;

case 8:
strcpy(parque[1][1][1].matricula,matricula); 
//PISO 2
break;

case 9:
strcpy(parque[2][0][0].matricula,matricula);
break;

case 10:
strcpy(parque[2][0][1].matricula,matricula);
break;

case 11:
strcpy(parque[2][1][0].matricula,matricula); 
break;

case 12:
strcpy(parque[2][1][1].matricula,matricula);
//PISO 3
break;

case 13:
strcpy(parque[3][0][0].matricula,matricula);
break;

case 14:
strcpy(parque[3][0][1].matricula,matricula);
break;

case 15:
strcpy(parque[3][1][0].matricula,matricula);    
break;

case 16:
strcpy(parque[3][1][1].matricula,matricula);
//PISO 4    
break;

default:
printf("Erro");
break;
}


}


