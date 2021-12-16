#include <stdio.h>
#include <string.h>
#include <time.h>
int piso,linha,coluna;
//STRUCT CARRO
typedef struct carro{
//ALO
//MATRICULA
char matricula[9];
//TIPO VIATURA(0 - Deficientes, 1 - Carro, 2 - Caravanas, 3- Autocarro&Camioes, 4 - Helicopteros)
int tipo_de_veiculo;
//nmr lavagens
int n_lavagens;
//pagamento
int pagamento;
}car;

typedef struct data_entrada{
    //DATA CHEGADA
 int year_chegada;
 int month_chegada;
 int day_chegada;
 int hours_chegada;
 int minutes_chegada;
 int secounds_chegada;

}data_entrada;

typedef struct data_saida{
 //DATA SAIDA
 int year_saida;
 int month_saida;
 int day_saida;
 int hours_saida;
 int minutes_saida;
 int secounds_saida;

}data_saida;

//OBJETO PARKING QUE VAI SER ARMAZENADO NUM ARRAY TRIDIMENCIONAL
typedef struct parking
{
//CARRO
 car veiculo;
 //DATA ENTRADA
 data_entrada entrada;
 //DATA SAIDA
 data_saida saida;
 //ESTADO 0=LIVRE 1=OCUPADO
 int estado;
//TIPO VIATURA(0 - Deficientes, 1 - Carro, 2 - Caravanas, 3 - Autocarro&Camioes, 4 - Helicopteros)
 int tipo;
}parking;

//DECLARAR FUNCAO QUE LEVA ARRAY
void Estacionar(int p, int l ,int c, char m[], int t, parking parque[][30][30]);
void Destacionar(int p, int l, int c,int count,parking parque[][30][30],parking historico[]);
float Pagamento(int p, int l ,int c,parking parque[][30][30]);
void Lavagem(int p, int l, int c, parking parque [][30][30]);
int L_livres(parking parque [][30][30]);
int L_ocupados(parking parque [][30][30]);
int Find_lugar(char m[], parking parque [][30][30]);
int Find_car(char m[], parking parque [][30][30]);
//DECLARAR O TAMANHO DO ARRAY PARQUE
void setTamanho(int p,int l,int c){
 piso=p;
 linha=l;
 coluna=c;
}

//FUNCAO PARA SETAR OS DADOS
void Estacionar(int p , int l ,int c,char m[], int t, parking parque[][30][30]){
//INICIALIZAR DADOS DE TIME
time_t now;
time(&now);
struct tm *local = localtime(&now);
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END

    //PEGAR NA STRING MATRICULA E COLA-LA NA POSICAO INDICADA NO PARAMETRO MATRICULA 
    strcpy(parque[p][l][c].veiculo.matricula,m);
    //PEGAR NO TIPO DE VIATURA
    parque[p][l][c].veiculo.tipo_de_veiculo=t;
    //DAY GET
    parque[p][l][c].entrada.day_chegada=local->tm_mday;
    //MOUNTH GET
    parque[p][l][c].entrada.month_chegada=local->tm_mon+1;
    //YEAR GET
    parque[p][l][c].entrada.year_chegada=local->tm_year+1900;  
    //HOURS GET
    parque[p][l][c].entrada.hours_chegada=local->tm_hour;
    //MINUTES GET
    parque[p][l][c].entrada.minutes_chegada=local->tm_min;
    //SECOUNDS GET
    parque[p][l][c].entrada.secounds_chegada=local->tm_sec;
    //ESTABLECER O ESTADO COMO ESTACIONADO
    parque[p][l][c].estado=1;

}



//FUNCAO PARA DETERMINAR O PAGAMENTO DO PARQUE
float Pagamento(int p , int l ,int c,parking parque[][30][30]){
    float min, horas, dia, mes, ano,sec;
    float total;
    int pagamento;
    
    //TOTAL DE HORAS PASSADAS
    ano = (float)parque[p][l][c].saida.year_saida - (float)parque[p][l][c].entrada.year_chegada;   
    //TOTAL DE MESES PASSADOS
    mes = (float)parque[p][l][c].saida.month_saida - (float)parque[p][l][c].entrada.month_chegada;
    //TOTAL DE DIAS PASSADOS
    dia = (float)parque[p][l][c].saida.day_saida - (float)parque[p][l][c].entrada.day_chegada;
    //TOTAL DE HORAS PASSADOS
    horas = (float)parque[p][l][c].saida.day_saida - (float)parque[p][l][c].entrada.day_chegada;
    //TOTAL DE MINUTOS PASSADOS
    min = (float)parque[p][l][c].saida.day_saida - (float)parque[p][l][c].entrada.day_chegada;
    //SECOUNDS GET
    sec = (float)parque[p][l][c].saida.secounds_saida - (float)parque[p][l][c].entrada.secounds_chegada;
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
    parque[p][l][c].veiculo.pagamento = (parque[p][l][c].veiculo.n_lavagens * 20) + total;
    return parque[p][l][c].veiculo.pagamento;
}



//FUNCAO PARA SETAR OS DADOS
void Destacionar(int p , int l ,int c,int count, parking parque[][30][30],parking historico[]){
//DAR ASIGN DOS VALORES COM PISO,LINHA E COLUNA FORNECIDOS CONSOANTE O QUE O UTILIZADOR CLICA NA FRONT-END  
    //MUDAR O ESTADO SIMPLESMENTE PARA DESTACIONADO
    parque[p][l][c].estado=0;
    //INICIALIZAR DADOS DE TIME PARA SABER A DATA ATUAL
    time_t now;
    time(&now);
    struct tm *data_saida = localtime(&now);
    //DAY GET
    parque[p][l][c].saida.day_saida=data_saida->tm_mday;
    //MOUNTH GET
    parque[p][l][c].saida.month_saida=data_saida->tm_mon+1;
    //YEAR GET
    parque[p][l][c].saida.year_saida=data_saida->tm_year+1900; 
    //HOURS GET
    parque[p][l][c].saida.hours_saida=data_saida->tm_hour;
    //MINUTES GET
    parque[p][l][c].saida.minutes_saida=data_saida->tm_min;
    //SECOUNDS GET
    parque[p][l][c].saida.secounds_saida=data_saida->tm_sec;
    
    //INICIALIZAR FUNCAO PAGAMENTO COM PARAMETROS , DATA DE CHEGADA E DATA DE SAIDA;ARMAZENAR NA ABA "PAGAMENTO"
    parque[p][l][c].veiculo.pagamento=Pagamento(p,l,c,parque);
    //COLOCAR O OBJETO NO HISTORICO
    historico[count]=parque[p][l][c];  
}



//FUNÇÃO PARA CONTAR O NUMERO DE LAVAGENS FEITAS
void Lavagem(int p, int l, int c, parking parque [][30][30]){
    //ADICIONAMOS +1 AO CONTADOR DE LAVAGENS
    parque[p][l][c].veiculo.n_lavagens = parque[p][l][c].veiculo.n_lavagens + 1;
}



//FUNÇÃO PARA CONTAR TODOS OS LUGARES LIVRES
int L_livres(parking parque [][30][30]){
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
int L_ocupados(parking parque [][30][30]){
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
int Find_lugar(char m[], parking parque [][30][30]){
        int p, l, c;
    //VERIFICAMOS TODAS OS PISOS
    for (p; p <=piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE A MATRICULA DO SITIO É IGUAL À QUE PROCURAMOS
                int valor = strcmp(parque[p][l][c].veiculo.matricula, m);
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
int Find_car(char m[], parking parque [][30][30]){
    int p, l, c;
    //VERIFICAMOS TODAS OS PISOS
    for (p; p <=piso; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                //VERIFICAMOS SE A MATRICULA DO SITIO É IGUAL À QUE PROCURAMOS
                int valor = strcmp(parque[p][l][c].veiculo.matricula, m);
                //CASO SEJA 0 É PORQUE AS DUAS STRINGS SÃO IGUAIS
                if (valor == 0){
                    //RETURNAMOS OS DADOS DO CARRO COM A RESPETIVA MATRICULA
                    printf("Matricula: %s", parque[p][l][c].veiculo.matricula);
                    printf("Tipo: %d", parque[p][l][c].tipo);
                    printf("Data de entrada: %d-%d-%d %d:%d:%d", parque[p][l][c].entrada.year_chegada, parque[p][l][c].entrada.month_chegada,parque[p][l][c].entrada.day_chegada,parque[p][l][c].entrada.hours_chegada,parque[p][l][c].entrada.minutes_chegada,parque[p][l][c].entrada.secounds_chegada);
                    printf("Data de saida: %d-%d-%d %d:%d:%d", parque[p][l][c].saida.year_saida, parque[p][l][c].saida.month_saida,parque[p][l][c].saida.day_saida,parque[p][l][c].saida.hours_saida,parque[p][l][c].saida.minutes_saida,parque[p][l][c].saida.secounds_saida);
                    printf("Pagamento: %f", parque[p][l][c].veiculo.pagamento);
                }
            } 
        }
    }
    return 0;
}

//FUNÇAO GANHO TOTAL
float ganho(parking parque [][linha][coluna], parking historico[]){
    int p, l, c, count;
    //VERIFICAMOS TODOS OS PISOS
 for (p; p <= p; p++){
        //VERIFICAMOS TODAS AS LINHAS
        for (l; l <=linha; l++){
            //VERIFICAMOS TODAS AS COLUNAS
            for (c; c <=coluna; c++){
                 //RETURNAMOS O PISO-LINHA-COLUNA
               count = count + historico->pagamento;

            }
        }
    }
    return count;
}

//FUNCAO DE INICIALIZAR
void inicializar(int defs_number,int carv_number,int bus_number,int helicopter_number,parking parque[][30][30]){
    int counter_defs=0;
    int counter_caravanas=0;
    int counter_bus=0;
if(helicopter_number==1){
    strcpy(parque[piso][0][0].veiculo.matricula,"");
    parque[piso][0][0].tipo=4;
    parque[piso][0][0].veiculo.n_lavagens=0;
    parque[piso][0][0].entrada.year_chegada=0;
    parque[piso][0][0].entrada.month_chegada=0;
    parque[piso][0][0].entrada.day_chegada=0;
    parque[piso][0][0].entrada.hours_chegada=0;
    parque[piso][0][0].entrada.minutes_chegada=0;
    parque[piso][0][0].entrada.secounds_chegada=0;
    parque[piso][0][0].saida.year_saida=0;
    parque[piso][0][0].saida.month_saida=0;
    parque[piso][0][0].saida.day_saida=0;
    parque[piso][0][0].saida.hours_saida=0;
    parque[piso][0][0].saida.minutes_saida=0;
    parque[piso][0][0].saida.secounds_saida=0;
    parque[piso][0][0].estado=0;
    parque[piso][0][0].veiculo.pagamento=0;
}
    for (int p = 0; p <piso; p++)
{   
    //QUANDO VOLTA VOLTA AQUI MUDA O PISO
    int l=0;
    for (l;l<linha;l++)
    {
    //LINHA
    int c=0;
    
    for (c;c<coluna;c++)
    {
    //AS OPERACOES VAO EXECUTAR TODAS AQUI PORTANTO...
    //SETAR ATRIBUTOS COMO VAZIOS
    if((defs_number>0)&&(p==0)&&(defs_number!=counter_defs)){
    strcpy(parque[p][l][c].veiculo.matricula,"");
    parque[p][l][c].tipo=0;
    parque[p][l][c].veiculo.n_lavagens=0;
    parque[p][l][c].entrada.year_chegada=0;
    parque[p][l][c].entrada.month_chegada=0;
    parque[p][l][c].entrada.day_chegada=0;
    parque[p][l][c].entrada.hours_chegada=0;
    parque[p][l][c].entrada.minutes_chegada=0;
    parque[p][l][c].entrada.secounds_chegada=0;
    parque[p][l][c].saida.year_saida=0;
    parque[p][l][c].saida.month_saida=0;
    parque[p][l][c].saida.day_saida=0;
    parque[p][l][c].saida.hours_saida=0;
    parque[p][l][c].saida.minutes_saida=0;
    parque[p][l][c].saida.secounds_saida=0;
    parque[p][l][c].estado=0;
    parque[p][l][c].veiculo.pagamento=0;
    counter_defs=counter_defs+1;
    }else if(counter_bus!=bus_number&&bus_number>0&&p==0){

 strcpy(parque[p][l][c].veiculo.matricula,"");
    parque[p][l][c].tipo=3;
    parque[p][l][c].veiculo.n_lavagens=0;
    parque[p][l][c].entrada.year_chegada=0;
    parque[p][l][c].entrada.month_chegada=0;
    parque[p][l][c].entrada.day_chegada=0;
    parque[p][l][c].entrada.hours_chegada=0;
    parque[p][l][c].entrada.minutes_chegada=0;
    parque[p][l][c].entrada.secounds_chegada=0;
    parque[p][l][c].saida.year_saida=0;
    parque[p][l][c].saida.month_saida=0;
    parque[p][l][c].saida.day_saida=0;
    parque[p][l][c].saida.hours_saida=0;
    parque[p][l][c].saida.minutes_saida=0;
    parque[p][l][c].saida.secounds_saida=0;
    parque[p][l][c].estado=0;
    parque[p][l][c].veiculo.pagamento=0;
    counter_bus+=1;

    }else if(counter_caravanas!=carv_number&&carv_number>0&&p==1){


 strcpy(parque[p][l][c].veiculo.matricula,"");
    parque[p][l][c].tipo=2;
    parque[p][l][c].veiculo.n_lavagens=0;
    parque[p][l][c].entrada.year_chegada=0;
    parque[p][l][c].entrada.month_chegada=0;
    parque[p][l][c].entrada.day_chegada=0;
    parque[p][l][c].entrada.hours_chegada=0;
    parque[p][l][c].entrada.minutes_chegada=0;
    parque[p][l][c].entrada.secounds_chegada=0;
    parque[p][l][c].saida.year_saida=0;
    parque[p][l][c].saida.month_saida=0;
    parque[p][l][c].saida.day_saida=0;
    parque[p][l][c].saida.hours_saida=0;
    parque[p][l][c].saida.minutes_saida=0;
    parque[p][l][c].saida.secounds_saida=0;
    parque[p][l][c].estado=0;
    parque[p][l][c].veiculo.pagamento=0;
    counter_caravanas+=1;


    }else{
    strcpy(parque[p][l][c].veiculo.matricula,"");
    parque[p][l][c].tipo=1;
    parque[p][l][c].veiculo.n_lavagens=0;
    parque[p][l][c].entrada.year_chegada=0;
    parque[p][l][c].entrada.month_chegada=0;
    parque[p][l][c].entrada.day_chegada=0;
    parque[p][l][c].entrada.hours_chegada=0;
    parque[p][l][c].entrada.minutes_chegada=0;
    parque[p][l][c].entrada.secounds_chegada=0;
    parque[p][l][c].saida.year_saida=0;
    parque[p][l][c].saida.month_saida=0;
    parque[p][l][c].saida.day_saida=0;
    parque[p][l][c].saida.hours_saida=0;
    parque[p][l][c].saida.minutes_saida=0;
    parque[p][l][c].saida.secounds_saida=0;
    parque[p][l][c].estado=0;
    parque[p][l][c].veiculo.pagamento=0;
    }
    } 
    }
}
}