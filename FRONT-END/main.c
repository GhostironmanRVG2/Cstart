#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "../FRONT-END/windows/sizepark.c"
#include "../FRONT-END/windows/mainw.c"
#include "../BACK-END/parking.c"
FILE *file;
int piso=0,linha=0,coluna=0;
sizepark t;
//MAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
//LER OS DADOS
file=fopen("../BACK-END/logs/filedb.txt","rb");
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
file=fopen("../BACK-END/logs/filedb.txt","wb");
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
parking parque[linha][piso][coluna];
mainw(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
printf("O parque foi inicialiado com %d pisos , %d linhas e %d colunas",piso,linha,coluna);
}else{
//MSG DE ERRO CASO NAO DE PARA SER INICIADO
printf("Erro , nao deu para inicializar");
}

}