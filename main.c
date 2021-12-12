#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "../Cstart/FRONT-END/sizepark.c"
#include "../Cstart/FRONT-END/mainw.c"
FILE *file;
int piso=0,linha=0,coluna=0;
sizepark t;
//MAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
//LER OS DADOS
file=fopen("../Cstart/BACK-END/logs/db.txt","rb");
//LER
fscanf(file,"piso=%d\n",&piso);
fscanf(file,"linha=%d\n",&linha);
fscanf(file,"coluna=%d\n",&coluna);
fclose(file);
HWND hwnd;
//WINDOW size park
if(piso==0&&linha==0&&coluna==0){
t=sizew(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
}
//CASO SEJAM ATRIBUIDOS VALORES O ARRAY É INICIALIZADO
if((t.piso!=0&&t.linha!=0&&t.coluna!=0)|(piso!=0&&linha!=0&&coluna!=0)){
//ATRIBUICAO DE VALORES
if((t.piso!=0&&t.linha!=0&&t.coluna!=0)){
piso=t.piso;
linha=t.linha;
coluna=t.coluna;
}
//ARMAZENAR ESTES DADOS NUM TXT
file=fopen("../Cstart/BACK-END/logs/db.txt","wb");
    if(file==NULL){
    
    printf("\nERROR");
    exit(1);
    }
    //ESCREVER OS DADOS NO FILE
    fprintf(file,"piso=%d\n",piso);
    fprintf(file,"linha=%d\n",linha);
    fprintf(file,"coluna=%d\n",coluna);

    fclose(file);
//INICIALIZACAO DO NOSSO ARRAY TIPO PARKING TRIDIMENCIONAL
parking parque[20][30][30];
Estacionar(0,0,0,"PO-LL-22",1,parque);
mainw(hInstance,hPrevInstance,lpCmdLine,nCmdShow,parque);
printf(" derradeiro teste %d\n",parque[0][0][0].tipo);
printf("O parque foi inicialiado com %d pisos , %d linhas e %d colunas",piso,linha,coluna);
}else{
//MSG DE ERRO CASO NAO DE PARA SER INICIADO
printf("Erro , nao deu para inicializar");
}

}