#include <stdio.h>
#include "BACK-END/parking.c"

//MAIN DO PROGRAMA
int main()
{
//INICIALIZACAO DO NOSSO PARQUE    
parking parque[4][2][2];   

Estacionar("10-IO-OP",1,parque);
printf("%s",parque[0][0][0].matricula);



    
}
