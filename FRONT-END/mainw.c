#include <stdio.h>
#include <Windows.h>
#include "../BACK-END/parking.c"
//INSTANCIA
HINSTANCE g_hinst;
void loadLivre(HWND listalivres);
void loadOcupado(HWND listaocupado);
LRESULT CALLBACK Wnd(HWND, UINT, WPARAM, LPARAM);
void DisableMaximizeButton(HWND hwnd);
//DEFINIR O ID DE CADA UM DOS ITENS
#define ID_LISTA_LIVRES 11
#define ID_LISTA_ESTACIONADOS 22
#define ID_LISTA_HISTORICO 33
#define ID_INPUT_LIVRES 21
#define ID_INPUT_ESTACIONADOS 22
#define ID_INPUT_HISTORICO 23
#define ID_BUTTON_LIVRES 31
#define ID_BUTTON_ESTACIONADOS 32
#define ID_BUTTON_HISTORICO 33
#define ID_BUTTON_LAVAGEM 34
#define ID_BUTTON_FIND 35
#define ID_COMBO 40
#define TITLES 50
typedef struct ware{
parking (*point)[30][30];
}ware;
ware warehouse;
int helas;
int verifymatric(char matric[]);
void mainw(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow,parking parque[][30][30],int helicopter_lenght);
void mainw(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow,parking parque[][30][30],int helicopter_lenght){
MSG msg;
helas=helicopter_lenght;
//PASSAR POINTER
warehouse.point=parque;
//PASSAR INSTANCIA
g_hinst = hInstance;
//CLASSE DA WINDOW
WNDCLASSEX wc;
//REGISTAR A WINDOWS CLASS
wc.cbSize        = sizeof(WNDCLASSEX);
wc.style         = 0;
wc.lpfnWndProc   = Wnd;
wc.cbClsExtra    = 0;
wc.cbWndExtra    = 0;
wc.hInstance     = hInstance;
wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
wc.lpszMenuName  = NULL;
wc.lpszClassName = TEXT("mainw");
wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
RegisterClassEx(&wc);
//CRIAR A WINDOW
HWND hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("mainw"),TEXT("KARGA"), WS_VISIBLE | WS_OVERLAPPEDWINDOW|SW_MAXIMIZE,CW_USEDEFAULT, CW_USEDEFAULT, 370, 230, NULL, NULL, hInstance, NULL);
ShowWindow(hwnd,SW_MAXIMIZE);
//LOOP DE MENSAGENS
while(GetMessage(&msg, NULL, 0, 0) > 0)
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}
}


//WINDOW PROC
LRESULT CALLBACK Wnd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{ 
  //Inicializar as listas/buttons e inputs  
  HWND static lista_livres,lista_estacionados,lista_historico;
  HWND static input_livres,input_estacionados,input_historico;
  HWND button_livres,button_estacionados,button_historico,button_lavar,button_encontrar;
  static HWND combo;
switch(msg)
{
case WM_CREATE:
//ICON
{
		
			HICON hIcon, hIconSm;
			hIcon = (HICON)LoadImage(NULL,"../Cstart/FRONT-END/icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
			if(hIcon)
			{
				SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			}
			else
			{
				MessageBox(hwnd, "Could not load large icon! Is it in the current working directory?", "Error", MB_OK | MB_ICONERROR);
			}

		}
//LISTA LIVRES & titulo
lista_livres = CreateWindow(TEXT("ListBox"), TEXT(""), 
WS_CHILD | WS_VISIBLE | LBS_NOTIFY| WS_BORDER | WS_VSCROLL
,100, 50, 400,560, hwnd, (HMENU)ID_LISTA_LIVRES, g_hinst, NULL);
CreateWindowW(L"static", L"LISTA DE LUGARES VAGOS",
        WS_CHILD | WS_VISIBLE,
        200, 30, 180,20, 
        hwnd, (HMENU)TITLES , NULL, NULL);
//DAR LOAD DA LISTA
loadLivre(lista_livres);
//INPUT DOS LIVRES
 input_livres = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                108, 620,85,23, hwnd, (HMENU)ID_INPUT_LIVRES,
                NULL, NULL);
CreateWindowW(L"static", L"MATRICULA",
        WS_CHILD | WS_VISIBLE,
        110,600, 80,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
//COMBO LIVRES
 combo = CreateWindowW(L"Combobox", NULL, 
                    WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
                    235, 610, 120, 200, hwnd, (HMENU)ID_COMBO, g_hinst, NULL);
//ENCHER BUFFER  
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"DEFICIENTE");
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"CARRO");
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"CARAVANA");
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"BUS/CAMI");
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"HELICOPTERO");
//BUTTON DOS LIVRES
button_livres = CreateWindowW(L"button", L"ESTACIONAR",
                WS_VISIBLE | WS_CHILD, 390, 600, 100, 42,
                hwnd, (HMENU) ID_BUTTON_LIVRES, NULL, NULL);

//LISTA ESTACIONADOS
lista_estacionados = CreateWindow(TEXT("ListBox"), TEXT(""), 
WS_CHILD | WS_VISIBLE | LBS_NOTIFY| WS_BORDER | WS_VSCROLL
,550, 50, 400,560, hwnd, (HMENU)ID_LISTA_ESTACIONADOS, g_hinst, NULL);
CreateWindowW(L"static", L"LISTA DE LUGARES OCUPADOS",
        WS_CHILD | WS_VISIBLE,
        650, 30, 210,20, 
        hwnd, (HMENU)TITLES, NULL, NULL);
//LOAD DOS OCUPADOS
loadOcupado(lista_estacionados);
//INPUT DOS LIVRES
 input_estacionados = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                557, 620,85,23, hwnd, (HMENU)ID_INPUT_ESTACIONADOS,
                NULL, NULL);
CreateWindowW(L"static", L"MATRICULA",
        WS_CHILD | WS_VISIBLE,
        560,600, 80,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
//BUTTON DOS OCUPADOS
button_estacionados = CreateWindowW(L"button", L"DESTACIONAR",
                WS_VISIBLE | WS_CHILD, 650, 600, 100, 42,
                hwnd, (HMENU) ID_BUTTON_ESTACIONADOS, NULL, NULL);
button_encontrar = CreateWindowW(L"button", L"ENCONTRAR",
                WS_VISIBLE | WS_CHILD, 750, 600, 100, 42,
                hwnd, (HMENU) ID_BUTTON_FIND, NULL, NULL);
button_lavar = CreateWindowW(L"button", L"LAVAGEM",
                WS_VISIBLE | WS_CHILD, 850, 600, 100, 42,
                hwnd, (HMENU) ID_BUTTON_LAVAGEM, NULL, NULL);                                
//LISTA HISTORICO
lista_historico = CreateWindow(TEXT("ListBox"), TEXT(""), 
WS_CHILD | WS_VISIBLE | LBS_NOTIFY| WS_BORDER | WS_VSCROLL
,1000, 50, 400,560, hwnd, (HMENU)ID_LISTA_HISTORICO, g_hinst, NULL);
CreateWindowW(L"static", L"LISTA DO HISTÓRICO",
        WS_CHILD | WS_VISIBLE,
        1130, 30, 140,20, 
        hwnd, (HMENU)TITLES, NULL, NULL);
//INPUT DO HISTORICO
 input_historico = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                1100, 620,65,23, hwnd, (HMENU)ID_INPUT_HISTORICO,
                NULL, NULL);
CreateWindowW(L"static", L"MATRICULA",
        WS_CHILD | WS_VISIBLE,
        1095,600, 80,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
button_historico = CreateWindowW(L"button", L"ENCONTRAR",
                WS_VISIBLE | WS_CHILD, 1225, 600, 100, 42,
                hwnd, (HMENU) ID_BUTTON_LAVAGEM, NULL, NULL);
//DASHBOARD BELOW LIVRES
CreateWindowW(L"static", L"NUMERO DE ESTACIONADOS:",
        WS_CHILD | WS_VISIBLE,
        100,750, 200,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
CreateWindowW(L"static", L"DINHEIRO FATURADO:",
        WS_CHILD | WS_VISIBLE,
        100,700, 150,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
//DASHBOARD BELLOW ESTACIONADOS
CreateWindowW(L"static", L"TABELAS DE PREÇOS:",
        WS_CHILD | WS_VISIBLE,
        675,650, 150,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
CreateWindowW(L"static", L"CARRO:             2,5€ CAMIAO:            10€\nAUTOCARRO:    10€  CARAVANA:        5€\n                  HELICOPTERO: 200€\n                          Por hora!\n                Lavagens VIP: 20€ cada\n  (estacionar num tipo diferente do seu\n                  paga esse dado tipo)",
        WS_CHILD | WS_VISIBLE,
        610,670,270,112, 
        hwnd, (HMENU)TITLES , NULL, NULL);
//DASHBOARD HISTORICO
CreateWindowW(L"static", L"LUGARES DISPONIVEIS:",
        WS_CHILD | WS_VISIBLE,
        1120,650, 165,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
CreateWindowW(L"static", L"CARRO:",
        WS_CHILD | WS_VISIBLE,
        1120,670, 55,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
CreateWindowW(L"static", L"CAMIAO:",
        WS_CHILD | WS_VISIBLE,
        1120,690, 55,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
CreateWindowW(L"static", L"AUTOCARRO:",
        WS_CHILD | WS_VISIBLE,
        1120,710, 90,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
CreateWindowW(L"static", L"CARAVANA:",
        WS_CHILD | WS_VISIBLE,
        1120,730,75,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);
CreateWindowW(L"static", L"HELICOPTERO:",
        WS_CHILD | WS_VISIBLE,
        1120,750, 100,17, 
        hwnd, (HMENU)TITLES , NULL, NULL);


break;
case WM_COMMAND:

//BOTAO ESTACIONAR
//SE FOR O BOTAO LIVRE..
if(LOWORD(wParam)==ID_BUTTON_LIVRES){
//SE FOI CLICADO
if (HIWORD(wParam) == BN_CLICKED) {
//INDEX DO LIVRES
int sel = (int) SendMessageW(lista_livres, LB_GETCURSEL, 0, 0);
if(sel==-1){
MessageBox(hwnd,"Por favor selecione um lugar livre","KARGA", 6);
}else{
//BUSCAR O TEXTO E GUARDAR NUMA VARIAVEL
char get[50];
SendMessage(lista_livres,LB_GETTEXT,sel,(LPARAM)get);

//IR BUSCAR CARACTERES PARA SABER A POSICAO DO ARRAY
//CRIAMOS UM INT POSI PARA PODER CONTROLAR A POSIÇÃO QUE QUEREMOS
int posi = 2;
//PISO ESTÁ NA POSIÇÃO 1
int piso_ocu=(int)get[1]-48;
//CASO O NUMERO SEJA MENOR QUE 30 SIGNIFICA QUE NAO É UM PARENTESE RETO MAS SIM UM NUMERO
//VISTO QUE [ TEM VALOR 43 E ] TEM VALOR 45
if ((int)get[posi]-48< 30){
        //SIGNIFICA QUE O PISO É CONSTITUIDO POR 2 ALGORITEMOS
        //CALCULAMOS O VALOR DO LUGAR
        piso_ocu = piso_ocu * 10;
        piso_ocu = piso_ocu + (int)get[2]-48;
        //SOMAMOS MAIS 3 POSIÇÕES IR AO PROXIMO NUMERO
        posi = posi + 3;
}else {
        //SE NAO FOR UM NUMERO SOMAMOS APENAS MAIS 2 POSIÇÕES
        posi = posi + 2; 
}
//GET DO VALOR DA LINHA
int linha_ocu=(int)get[posi]-48;
//SOMAMOS MAIS UMA POSIÇÃO PARA IR PARA APROXIMA POSIÇÃO
posi = posi + 1;
if((int)get[posi]-48<30){
        //SIGNIFICA QUE A LINHA É CONSTITUIDA POR 2 ALGORITMOS
        //CALCULAMOS O VALOR DA LINHA
        linha_ocu = linha_ocu * 10;
        linha_ocu = linha_ocu + (int)get[posi] - 48;
        //SOMAMOS MAIS 3 POSIÇÕES PARA IR AO PROXIMO NUMERO
        posi = posi + 3;
}
else {
        //SOMAMOS MAIS 2 POSIÇÕES PARA IR AO PROXIMO NUMERO
        posi = posi + 2;
}
//GET DO CALOR DA COLUNA
int coluna_ocu=(int)get[posi]-48;
//SOMAMOS MAIS UMA POSIÇÃO
posi = posi + 1;
if((int)get[posi]-48<30){
        //SIGNIFICA QUE A LINHA É CONSTITUIDA POR 2 ALGORITMOS
        //CALCULAMOS O VALOR DA COLUNA
        coluna_ocu = coluna_ocu * 10;
        coluna_ocu=coluna_ocu + (int)get[posi]-48;    
}

//IR BUSCAR A MATRICULA
char matricula[10];
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_livres,matricula,10);
//IR BUSCAR O TIPO DO CARRO
int  cursor_combo=(int)SendMessage(combo, CB_GETCURSEL, 0, 0);
if(cursor_combo==-1){
        cursor_combo=1;
}
if(verifymatric(matricula)==0){
MessageBox(hwnd,"Introduza uma matricula valida","KARGA", 6);
}
if(cursor_combo == 1 && warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo != 1 && warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo != 2 && warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo != 3){
  
   printf("%d", warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo);
   printf("%d", cursor_combo);
   MessageBox(hwnd,"O tipo Carro so pode estacionar nos lugares do tipo Carro, Caravana, Camiao", "KARGA", 6);       
}
else if(cursor_combo == 3 && warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo != 3){
        printf("%d", warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo);
   printf("%d", cursor_combo);
   MessageBox(hwnd,"O tipo Camiao so pode estacionar nos lugares tipo Camiao", "KARGA", 6);
}
else if(cursor_combo == 2 && warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo != 2){
        printf("%d", warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo);
   printf("%d", cursor_combo);
   MessageBox(hwnd,"O tipo Caravana so pode estacionar nos lugares do tipo Caravana", "KARGA", 6);       
}
else if(cursor_combo == 4 && warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo != 4){
        printf("%d", warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo);
   printf("%d", cursor_combo);
   MessageBox(hwnd,"O tipo Helicoptero so pode estacionar nos lugares do tipo Helicoptero", "KARGA", 6);       
}
else if(cursor_combo == 0 && warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo != 0){
        printf("%d", warehouse.point[piso_ocu][linha_ocu][coluna_ocu].tipo);
   printf("%d", cursor_combo);
   MessageBox(hwnd,"O tipo Deficientes so pode estacionar nos lugares tipo Deficientes", "KARGA", 6);
}else{
//ESTACIONAR
Estacionar(piso_ocu,linha_ocu,coluna_ocu,matricula,cursor_combo,warehouse.point);
//REMOVER DE UM E PASSAR PARA O OUTRO
SendMessage(lista_livres,LB_DELETESTRING,sel,0);

char tipo_estacionamento[20];
    switch (warehouse.point[piso_ocu][linha_ocu][coluna_ocu].veiculo.tipo_de_veiculo)
    {
    //TIPO DEFS
    case 0:
    strcpy(tipo_estacionamento,"Def");
    break;
    //TIPO CARAVANAS
    case 2:
    strcpy(tipo_estacionamento,"Carav");
    break;
    //TIPO BUS&CAMIOES
    case 3:
    strcpy(tipo_estacionamento,"Autoc/cam");
    break;
    //TIPO HELICOPTER
    case 4:
    strcpy(tipo_estacionamento,"Heli");
    break;
    //TIPO CARRO
    case 1:
    strcpy(tipo_estacionamento,"car");
    break;
    }
 //ADICIONAR MSG
    char ocupado[100];
    //COLOCAR DENTRO DA MSG
    snprintf(ocupado,100, "[%d][%d][%d]|%s|D.E:%d/%d/%d %d:%d:%d|%s|"
    ,piso_ocu,linha_ocu,coluna_ocu,
    tipo_estacionamento,
    warehouse.point[piso_ocu][linha_ocu][coluna_ocu].entrada.day_chegada,
    warehouse.point[piso_ocu][linha_ocu][coluna_ocu].entrada.month_chegada,
    warehouse.point[piso_ocu][linha_ocu][coluna_ocu].entrada.year_chegada,
    warehouse.point[piso_ocu][linha_ocu][coluna_ocu].entrada.hours_chegada,
    warehouse.point[piso_ocu][linha_ocu][coluna_ocu].entrada.minutes_chegada,
    warehouse.point[piso_ocu][linha_ocu][coluna_ocu].entrada.secounds_chegada,
    matricula);
    //ADICIONAR
    SendMessage(lista_estacionados,LB_ADDSTRING,0,(LPARAM)ocupado);
    //ESTACIONAR
    Estacionar(piso_ocu,linha_ocu,coluna_ocu,matricula,0,warehouse.point);
}
}
}
}






//COMMUNICATION
if (HIWORD(wParam) == CBN_SELCHANGE) {           
        LRESULT sel = SendMessage(combo, CB_GETCURSEL, 0, 0);
             }









//INTERACAO COM A LISTA
if (HIWORD(wParam) == LBN_SELCHANGE) { 
              TCHAR lbvalue[8];
             //gets index of selected listview item
            int sel = (int) SendMessageW(lista_livres, LB_GETCURSEL, 0, 0);
           //get selected text
           SendMessage(lista_livres, LB_GETTEXT, sel,(LPARAM)lbvalue);
           //sets staticbox to value of listbox text
          SendMessage(lista_livres, WM_SETTEXT, sel,(LPARAM)lbvalue);
}
break;
    //DESTRUIR A WINDOW
case WM_CLOSE:
DestroyWindow(hwnd);
break;
    //OUTRO MODO DE DESTRUIR A WINDOW
case WM_DESTROY:
PostQuitMessage(0);
break;
default:
return DefWindowProc(hwnd, msg, wParam, lParam);
}
return 0;
}


//funcao loadLivre
void loadLivre(HWND listalivres){
int contador=0;
if(helas==1){
    //ADICIONAR MSG
    char livre[50];
    snprintf(livre,50, "[%d][%d][%d]Tipo de estacionamento:%s", piso,0,0,"helicoper");
    //NAO ENCHER MAIS QUE 17997 LINHAS POIS SE ENCHER ELE BUGA
    SendMessage(listalivres,LB_ADDSTRING,0,(LPARAM)livre);     
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
    //SE O ESTADO FOR 0 ENTAO ESTA LIVRE
    if(warehouse.point[p][l][c].estado==0){
    //VERIFICAR TIPO DE ESTACIONAMENTO E ALOCAR NUMA VARIAVEL CONSOANTE O MESMO
    char tipo_estacionamento[20];
    switch (warehouse.point[p][l][c].tipo)
    {
    //TIPO DEFS
    case 0:
    strcpy(tipo_estacionamento,"Deficientes");
    break;
    //TIPO CARAVANAS
    case 2:
    strcpy(tipo_estacionamento,"Caravana");
    break;
    //TIPO BUS&CAMIOES
    case 3:
    strcpy(tipo_estacionamento,"Autocarro|Camiao");
    break;
    //TIPO HELICOPTER
    case 4:
    strcpy(tipo_estacionamento,"Helicoptero");
    break;
    //TIPO CARRO
    default:
    strcpy(tipo_estacionamento,"carro");
    break;
    }
    contador+=1;
    //ADICIONAR MSG
    char livre[50];
    snprintf(livre,50, "[%d][%d][%d]Tipo de estacionamento:%s", p,l,c,tipo_estacionamento);
    //NAO ENCHER MAIS QUE 17997 LINHAS POIS SE ENCHER ELE BUGA
    SendMessage(listalivres,LB_ADDSTRING,0,(LPARAM)livre);
    }
    
    } //
    }
}      

}


//funcao load estacionados
void loadOcupado(HWND listaocupado){

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
    //SE O ESTADO FOR 0 ENTAO ESTA LIVRE
    if(warehouse.point[p][l][c].estado==1){
    //VERIFICAR TIPO DE ESTACIONAMENTO E ALOCAR NUMA VARIAVEL CONSOANTE O MESMO
    char tipo_estacionamento[20];
    switch (warehouse.point[p][l][c].tipo)
    {
    //TIPO DEFS
    case 0:
    strcpy(tipo_estacionamento,"Deficientes");
    break;
    //TIPO CARAVANAS
    case 2:
    strcpy(tipo_estacionamento,"Caravana");
    break;
    //TIPO BUS&CAMIOES
    case 3:
    strcpy(tipo_estacionamento,"Autocarro|Camiao");
    break;
    //TIPO HELICOPTER
    case 4:
    strcpy(tipo_estacionamento,"Helicoptero");
    break;
    //TIPO CARRO
    default:
    strcpy(tipo_estacionamento,"carro");
    break;
    }
    //ADICIONAR MSG
    char ocupado[100];
    //COLOCAR DENTRO DA MSG
    snprintf(ocupado,100, "[%d][%d][%d]|T.E:%s|\nDataEntrada:%d/%d/%d %d:%d:%d|"
    ,p,l,c,
    tipo_estacionamento,
    warehouse.point[p][l][c].entrada.day_chegada,
    warehouse.point[p][l][c].entrada.month_chegada,
    warehouse.point[p][l][c].entrada.year_chegada,
    warehouse.point[p][l][c].entrada.hours_chegada,
    warehouse.point[p][l][c].entrada.minutes_chegada,
    warehouse.point[p][l][c].entrada.secounds_chegada);
    //ADICIONAR
    SendMessage(listaocupado,LB_ADDSTRING,0,(LPARAM)ocupado);
    }
    
    } 
    }
}      

}

//FUNCAO VERIFY MATRIC
int verifymatric(char matric[]){
        int lenght =strnlen(matric,10);
if(
(  (   (((int)matric[0]-48)<=9)&&( ((int)matric[0]-48)>=0)  ) ||   (   (((int)matric[0]-48)<=42)&&( ((int)matric[0]-48)>=17)  )               ) //POS 0 SEM CARACTERES ESTRANHOS
&&
(  (   (((int)matric[1]-48)<=9)&&( ((int)matric[1]-48)>=0)  ) ||   (   (((int)matric[1]-48)<=42)&&( ((int)matric[1]-48)>=17)  )  )//POS 1 SEM C.E
&&
(                    (  ((int)matric[5]-48) ==-3)                )//POS 2 COM C.E
&&
(  (   (((int)matric[3]-48)<=9)&&( ((int)matric[3]-48)>=0)  ) ||   (   (((int)matric[3]-48)<=42)&&( ((int)matric[3]-48)>=17)  )   )//POS 3 SEM C.E
&&
(  (   (((int)matric[4]-48)<=9)&&( ((int)matric[4]-48)>=0)  ) ||   (   (((int)matric[4]-48)<=42)&&( ((int)matric[4]-48)>=17)  )   )//POS 4 SEM C.E
&&
(                    (  ((int)matric[5]-48) ==-3)               )//POS 5 COM C.E
&&
(   (   (((int)matric[6]-48)<=9)&&( ((int)matric[6]-48)>=0)  ) ||   (   (((int)matric[6]-48)<=42)&&( ((int)matric[6]-48)>=17)  )  )//POS 6 SEM C.E
&&
(   (   (((int)matric[7]-48)<=9)&&( ((int)matric[7]-48)>=0)  ) ||   (   (((int)matric[7]-48)<=42)&&( ((int)matric[7]-48)>=17)  )     )//POS 7 SEM C.E  
&&
(lenght==8)
){
return 1;
 
}else{

        return 0;
}

}


