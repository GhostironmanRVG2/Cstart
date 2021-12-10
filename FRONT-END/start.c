#include <stdio.h>
#include <time.h>
#include "../BACK-END/parking.c"
int piso,linha,coluna;
int historicDynamic=1;
//MAIN DO PROGRAMA
int main()
{
 linha=coluna=piso=2;  
 setTamanho(2,2,3); 
//INICIALIZACAO DO NOSSO ARRAY TIPO PARKING TRIDIMENCIONAL
parking parque[linha][piso][coluna];
//INICIALIZACAO DO ARRAY DE REGISTO HISTORICO
parking historico[historicDynamic];

Estacionar(1,1,1,"PP-OO-PP",0,parque);
Estacionar(1,1,2,"PP-OO-PP",1,parque);
//Destacionar(1,1,1,0,parque,historico);
//printf("%f",historico[0].pagamento);
Lavagem(1,1,1,parque);
printf("\n%d", parque[1][1][1].n_lavagens);
Destacionar(1,1,1,0,parque,historico);
printf("\n%f",parque[1][1][1].pagamento);


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
