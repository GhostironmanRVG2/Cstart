#include <stdio.h>
#include <string.h>
//OBJETO PARKING QUE VAI SER ARMAZENADO NUM ARRAY TRIDIMENCIONAL
typedef struct parking
{
 char matricula[8];
}parking;
//DECLARACAO DA FUNCAO COM OS PARAMETROS
void Estacionar(char matricula[],int estacionamento, struct parking parque[][2][2]);

//FUNCAO ESTACIONAR PARA ESTACIONAR TENDO UMA MATRICULA ,NMR DE ESTACIONAMENTO E O PARQUE
void Estacionar(char matricula[],int estacionamento, struct parking parque[][2][2]){
//ACIONAR UM METODO CONSOANTE O ESTACIONAMENTO
switch (estacionamento)
{
case 1:
strcpy(parque[0][0][0].matricula,matricula);    
break;
case 2:
   
break;

case 3:
    
break;
case 4:
    
break;
case 5:

break;
case 6:
break;
case 7:
    
break;
case 8:
    
break;
case 9:
    
break;
case 10:

break;
case 11:
    
break;

case 12:
    
break;
case 13:
    
break;

case 14:
    
break;
case 15:
    
break;

case 16:
    
break;

default:

break;
}


}


