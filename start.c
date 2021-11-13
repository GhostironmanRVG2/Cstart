#include <stdio.h>
#include "BACK-END/parking.c"

//MAIN DO PROGRAMA
int main()
{
//INICIALIZACAO DO NOSSO PARQUE    
parking parque[4][2][2];
int piso;
int linha=0;
int coluna=0;
char m[9];   
printf("estacionamento?\n");
scanf("%d",&piso);
printf("Matricula?\n");
scanf("%s",&m);
printf("%s \n",m);
Estacionar(m,piso,parque);
//CUSPIR O NOSSO ARRAY
for (int i = 0; i <=3; i++)
{   
    //QUANDO VOLTA VOLTA AQUI MUDA O PISO
    linha=0;
    for (linha;linha<=1;linha++)
    {
    //LINHA
    coluna=0;
    
    for (coluna;coluna<=1;coluna++)
    {
    //COLUNA
    printf("[%d][%d][%d] matricula:%s\n",i,linha,coluna,parque[i][linha][coluna].matricula);  
       
           
    }
    
     


    }
    
    
}




    
}
