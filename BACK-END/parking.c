#include <stdio.h>
#include <string.h>
#include <time.h>
int piso,linha,coluna;
//OBJETO PARKING QUE VAI SER ARMAZENADO NUM ARRAY TRIDIMENCIONAL
typedef struct parking
{
 //MATRICULA
 char matricula[9];
 //TIPO VIATURA(0 - Deficientes, 3 - Carro, 2 - Caravanas, 1 - Autocarro&Camioes, 4 - Helicopteros)
 int tipo;
 //NUMERO DE LAVAGENS
 int n_lavagens;
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
void Estacionar(int p, int l ,int c, char m[], int t, parking parque[][linha][coluna]);
void Destacionar(int p, int l, int c,int count,parking parque[][linha][coluna],parking historico[]);
float Pagamento(int p, int l ,int c,parking parque[][linha][coluna]);
void Lavagem(int p, int l, int c, parking parque [][linha][coluna]);
int L_livres(parking parque [][linha][coluna]);
int L_ocupados(parking parque [][linha][coluna]);
int Find_lugar(char m[], parking parque [][linha][coluna]);
int Find_car(char m[], parking parque [][linha][coluna]);
//DECLARAR O TAMANHO DO ARRAY PARQUE
void setTamanho(int p,int l,int c){
 piso=p;
 linha=l;
 coluna=c;
}

//FUNCAO PARA SETAR OS DADOS
void Estacionar(int p , int l ,int c,char m[], int t, parking parque[][linha][coluna]){
//INICIALIZAR DADOS DE TIME
time_t now;
time(&now);
struct tm *local = localtime(&now);
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END

    //PEGAR NA STRING MATRICULA E COLA-LA NA POSICAO INDICADA NO PARAMETRO MATRICULA 
    strcpy(parque[p][l][c].matricula,m);
    //PEGSR NO TIPO DE VIATURA
    parque[p][l][c].tipo = t;
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
    //PAGAMENTO = 0
    parque[p][l][c].pagamento=0;
    //NUMERO DE LAVAGENS = 0
    parque[p][l][c].n_lavagens=0; 

}



//FUNCAO PARA DETERMINAR O PAGAMENTO DO PARQUE
float Pagamento(int p , int l ,int c,parking parque[][linha][coluna]){
    float min, horas, dia, mes, ano,sec;
    float total;
    int pagamento;
    
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
    
    //VERIFICAR O TIPO DE VIATURA PARA CALCULAR O PREÇO 
    switch (parque[p][l][c].tipo){
    //CASO SEJA UM CARRO DE TIPO 0 - DEFECIENTES
    case 0: 
        pagamento = 2.50;
    break;
    //CASO SEJA UM CARRO DE TIPO 1 - CAMIOES/AUTOCARROS   
     case 1: 
        pagamento = 10;
    break;
    //CASO SEJA UM CARRO DE TIPO 2 - AUTOCARAVANA
    case 2: 
        pagamento = 5;
    break;
    //CASJO SEJA UM CARRO DE TIPO 3 - CARRO
    case 3: 
        pagamento = 2.5;
    break;
    //CASO SEJA UM CAROR DE TIPO 4 - HELICOPETRO
    case 4: 
        pagamento = 200;
    break;
    //CASO O TIPO NÃO ESTEJA DEFENIDO
    default: printf("ERROR 404 - Tipo de viatura não encontrado");
    }

    //NUMERO DE HORAS VS O PREÇO À HORA DO RESPETIVO TIPO DE VEICULO
    total = total * pagamento;
    //TOTAL A PAGAR É IGUAL AO NUMERO DE LAVAGENS X 20 (PREÇO POR LAVAGEM) + O AS HORAS
    parque[p][l][c].pagamento = (parque[p][l][c].n_lavagens * 20) + total;
    return parque[p][l][c].pagamento;
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



//FUNÇÃO PARA CONTAR O NUMERO DE LAVAGENS FEITAS
void Lavagem(int p, int l, int c, parking parque [][linha][coluna]){
    //ADICIONAMOS +1 AO CONTADOR DE LAVAGENS
    parque[p][l][c].n_lavagens = parque[p][l][c].n_lavagens + 1;
}



//FUNÇÃO PARA CONTAR TODOS OS LUGARES LIVRES
int L_livres(parking parque [][linha][coluna]){
    int p = 0, l = 0, c = 0, count = 0;
    //VERIFICAMOS TODOS OS PISOS
    for (p; p <= piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE O ESTADO ESTÁ LIVRE
                if (parque[p][l][c].estado == 0){
                    //RETURNAMOS O PISO-LINHA-COLUNA
                    count = count + 1;
                }
            }
        }
    }
    printf("\n%d\n", count);
}



//FUNÇÃO PARA CONTAR TODOS OS LUGARES OCUPADOS
int L_ocupados(parking parque [][linha][coluna]){
    int p = 0, l = 0, c = 0, count = 0;
    //VERIFICAMOS TODAS OS PISOS
    for (p; p <=piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE O ESTADO ESTÁ OCUPADO
                if (parque[p][l][c].estado = 1){
                    //RETURNAMOS O PISO-LINHA-COLUNA
                    count = count + 1;
                }
            }
        }
    }
    printf("\n%d\n", count);
}



//FUNÇÃO PARA PROCURAR UMA MATRICULA
int Find_lugar(char m[], parking parque [][linha][coluna]){
        int p, l, c;
    //VERIFICAMOS TODAS OS PISOS
    for (p; p <=piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE A MATRICULA DO SITIO É IGUAL À QUE PROCURAMOS
                int valor = strcmp(parque[p][l][c].matricula, m);
                //CASO SEJA 0 É PORQUE AS DUAS STRINGS SÃO IGUAIS
                if (valor == 0){
                    //RETURNAMOS O PISO-LINHA-COLUNA
                    printf("%d-%d-%d", p,l,c);
                }
            }
        }
    }
    return 0;
}



//FUNÇÃO PARA PROCURAR UMA MATRICULA
int Find_car(char m[], parking parque [][linha][coluna]){
    int p, l, c;
    //VERIFICAMOS TODAS OS PISOS
    for (p; p <=piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE A MATRICULA DO SITIO É IGUAL À QUE PROCURAMOS
                int valor = strcmp(parque[p][l][c].matricula, m);
                //CASO SEJA 0 É PORQUE AS DUAS STRINGS SÃO IGUAIS
                if (valor == 0){
                    //RETURNAMOS OS DADOS DO CARRO COM A RESPETIVA MATRICULA
                    printf("Matricula: %s", parque[p][l][c].matricula);
                    printf("Tipo: %d", parque[p][l][c].tipo);
                    printf("Data de entrada: %d-%d-%d %d:%d:%d", parque[p][l][c].year_chegada, parque[p][l][c].month_chegada,parque[p][l][c].day_chegada,parque[p][l][c].hours_chegada,parque[p][l][c].minutes_chegada,parque[p][l][c].secounds_chegada);
                    printf("Data de saida: %d-%d-%d %d:%d:%d", parque[p][l][c].year_saida, parque[p][l][c].month_saida,parque[p][l][c].day_saida,parque[p][l][c].hours_saida,parque[p][l][c].minutes_saida,parque[p][l][c].secounds_saida);
                    printf("Pagamento: %f", parque[p][l][c].pagamento);
                }
            } 
        }
    }
    return 0;
}
