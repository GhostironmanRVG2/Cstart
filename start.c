#include <stdio.h>
#include <time.h>
int piso,linha,coluna;
int historicDynamic=1;
//MAIN DO PROGRAMA
int main()
{
 linha=2;
 piso=2;
 coluna=3;  
 setTamanho(2,2,3); 
//INICIALIZACAO DO NOSSO ARRAY TIPO PARKING TRIDIMENCIONAL
parking parque[piso][linha][coluna];
//INICIALIZACAO DO ARRAY DE REGISTO HISTORICO
parking historico[historicDynamic];

Estacionar(1,1,1,"PP-OO-PP",0,parque);
L_livres(parque);
Estacionar(1,1,2,"PP-OO-PP",1,parque);
L_ocupados(parque);
L_livres(parque);
//Destacionar(1,1,1,0,parque,historico);
//printf("%f",historico[0].pagamento);
Lavagem(1,1,1,parque);
printf("\n%d", parque[1][1][1].veiculo.n_lavagens);
Destacionar(1,1,1,0,parque,historico);
printf("\n%f",parque[1][1][1].veiculo.pagamento);
L_livres(parque);
inicializar(parque);
printf("alo %s",parque[0][0][0].veiculo.matricula);


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
