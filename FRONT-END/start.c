#include <stdio.h>
#include "../BACK-END/parking.c"
int piso,linha,coluna;
int historicDynamic=1;
//MAIN DO PROGRAMA
int main()
{
 linha=coluna=piso=2;  
 setTamanho(2,3); 
//INICIALIZACAO DO NOSSO ARRAY TIPO PARKING TRIDIMENCIONAL
parking parque[linha][piso][coluna];
//INICIALIZACAO DO ARRAY DE REGISTO HISTORICO
parking historico[historicDynamic];

Estacionar(1,1,1,"PP-OO-PP",parque);
printf("%d\n",parque[1][1][1].estado);
Destacionar(1,1,1,historicDynamic,parque,historico);
printf("%d\n",parque[1][1][1].estado);



/*CUSPIR O NOSSO ARRAY
for (int i = 0; i <=3; i++)
{   
    //QUANDO VOLTA VOLTA AQUI MUDA O PISO
    //linha=0;
    for (linha;linha<=1;linha++)
    {
    //LINHA
    //coluna=0;
    
    for (coluna;coluna<=1;coluna++)
    {
    //COLUNA
    printf("[%d][%d][%d] matricula:%s\n",i,linha,coluna,parque[i][linha][coluna].matricula);              
    } 
    }
    
    
}*/




    
}
