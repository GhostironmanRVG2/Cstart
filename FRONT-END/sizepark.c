#include <stdio.h>
#include <Windows.h>
#define INPUT_TEXT_ONE 1
#define INPUT_TEXT_TWO 2
#define INPUT_TEXT_THREE 3
#define INPUT_TEXT_DEFS 8
#define INPUT_TEXT_BUS 9
#define INPUT_TEXT_CARV 10
#define TEXT_OUTPUT 4
#define BUTTON_ONE 5
#define ID_BUTTON_SIM 6
#define ID_BUTTON_NAO 7
HINSTANCE g_hinst;
int helicoptero=0;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DisableMaximizeButton(HWND hwnd);
//STRUCT PARA ARMAZENAR OS 3 NUMEROS
typedef struct sizepark
{
    int piso;
    int linha;
    int coluna;
    int defs;
    int bus;
    int carv;
    int heli;
    /* data */
}sizepark;
sizepark result;
sizepark sizew(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
MSG msg;
WNDCLASSEX wc;
g_hinst=hInstance;
//REGISTAR A WINDOWS CLASS
wc.cbSize        = sizeof(WNDCLASSEX);
wc.style         = 0;
wc.lpfnWndProc   = WndProc;
wc.cbClsExtra    = 0;
wc.cbWndExtra    = 0;
wc.hInstance     = hInstance;
wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
wc.lpszMenuName  = NULL;
wc.lpszClassName = TEXT("sizepark");
wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
RegisterClassEx(&wc);
//CRIAR A WINDOW
HWND hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("sizepark"),TEXT("KARGA"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 370, 350, NULL, NULL, hInstance, NULL);
DisableMaximizeButton(hwnd);
//LOOP DE MENSAGENS
while(GetMessage(&msg, NULL, 0, 0) > 0)
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}
//return do resultado
return result;



}


//DESATIVAR O AUMENTO DA JANELA
void DisableMaximizeButton(HWND hwnd)
{
 SetWindowLong(hwnd, GWL_STYLE,
               GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}








//WINDOW PROC
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{   //INICIALIZAR NOSSOS OBJETOS DE MENU
    static HWND input_one,input_two,input_three,hEdit,hwndButton;
    static HWND input_defs,input_cami_bus,input_caravana;
    //output text using default font
    
    //MSGS
switch(msg)
{
case WM_CREATE:
MessageBox(hwnd,TEXT("AVISO: defs e bus/camiao , se forem criados serao criados no piso zero.\nCaravanas se forem criadas serao no piso um."),"KARGA", 6);
MessageBox(hwnd,TEXT("AVISO: Existem campos nao obrigatorios que em caso de nao serem preenchidos ou preenchidos indevidamente irao inicializar como zero devido a sua natureza opcional(deficientes,bus,caravanas,helicoptero)"),"KARGA", 6);
//INPUT FIELDS
input_one = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                100, 80, 20, 20, hwnd, (HMENU) INPUT_TEXT_ONE,
                NULL, NULL);
input_two = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                180, 80, 20, 20, hwnd, (HMENU) INPUT_TEXT_TWO,
                NULL, NULL);
input_three = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                260, 80, 20, 20, hwnd, (HMENU) INPUT_TEXT_THREE,
                NULL, NULL);
input_defs = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                260, 120, 15, 15, hwnd, (HMENU) INPUT_TEXT_DEFS,
                NULL, NULL);
input_cami_bus = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                260, 140, 15, 15, hwnd, (HMENU) INPUT_TEXT_BUS,
                NULL, NULL);
input_caravana = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                260, 160, 15, 15, hwnd, (HMENU) INPUT_TEXT_CARV,
                NULL, NULL);
            
                //TEXT FIELDS
CreateWindowW(L"static", L"INTRODUZA O TAMANHO DO PARQUE",
        WS_CHILD | WS_VISIBLE,
        50, 25, 250,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
CreateWindowW(L"static", L"PISO",
        WS_CHILD | WS_VISIBLE,
        60, 80, 35,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
CreateWindowW(L"static", L"HORI",
        WS_CHILD | WS_VISIBLE,
        140, 80, 35,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
CreateWindowW(L"static", L"VERTI",
        WS_CHILD | WS_VISIBLE,
        220, 80, 35,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
CreateWindowW(L"static", L"LUGARES PARA DEFICIENTES",
        WS_CHILD | WS_VISIBLE,
        60, 120,200,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
CreateWindowW(L"static", L"LUGARES PARA BUS/CAMIAO",
        WS_CHILD | WS_VISIBLE,
        60, 140,200,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
CreateWindowW(L"static", L"LUGARES PARA CARAVANA",
        WS_CHILD | WS_VISIBLE,
        60, 160,200,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
CreateWindowW(L"static", L"LUGAR PARA HELICOPTERO?",
        WS_CHILD | WS_VISIBLE,
        70,195,200,20, 
        hwnd, (HMENU) TEXT_OUTPUT, NULL, NULL);
//MARK YES OR NO
CreateWindowW(L"Button", L"SIM",
                  WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                  190,220, 50, 30, hwnd, (HMENU)ID_BUTTON_SIM , g_hinst, NULL);
CreateWindowW(L"Button", L"NÃO",
                  WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                  90,220, 50, 30, hwnd, (HMENU)ID_BUTTON_NAO , g_hinst, NULL);
//BUTTON
hwndButton = CreateWindow(TEXT("button"),
 TEXT("APPLY"),
 WS_VISIBLE |  WS_CHILD,
  125,260, 80, 30,hwnd, (HMENU) BUTTON_ONE, NULL, NULL);//click button
break;
case WM_COMMAND:
//responds to button click
if(LOWORD(wParam)==BUTTON_ONE){
if (HIWORD(wParam) == BN_CLICKED) {
const int maxtextlength = 3;
//INPUT DO QUE VAMOS RECEBER
TCHAR piso[3] = TEXT("");
TCHAR linha[3] = TEXT("");
TCHAR coluna[3] = TEXT("");
TCHAR defs[3] = TEXT("");
TCHAR bus[3] = TEXT("");
TCHAR caravana[3] = TEXT("");
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_one,piso, maxtextlength);
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_two, linha, maxtextlength);
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_three,coluna, maxtextlength);
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_defs,defs, maxtextlength);
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_cami_bus,bus, maxtextlength);
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_caravana,caravana, maxtextlength);
int piso_int,linha_int,coluna_int,defs_int,bus_int,caravana_int;
piso_int=atoi(piso);
linha_int=atoi(linha);
coluna_int=atoi(coluna);
defs_int=atoi(defs);
bus_int=atoi(bus);
caravana_int=atoi(caravana);
//verificar se cumpre as normas
if(piso_int>20|linha_int>30|coluna_int>30){
MessageBox(hwnd,"Por favor introduza um valor inferior a 20 no piso , a 30 na linha e a 30 na coluna","KARGA", 6);
}
else //verificar se os valores sao legit
if(piso_int==0|linha_int==0|coluna_int==0|piso_int<0|linha_int<0|coluna_int<0){
    MessageBox(hwnd,"Por favor introduza dados validos","KARGA", 6);
    //verificar se cumpre as normas
}else if(defs_int>(coluna_int)*(linha_int)||bus_int>(coluna_int)*(linha_int)||bus_int+defs_int>(coluna_int)*(linha_int)||caravana_int>(linha_int)*(coluna_int)){
    
MessageBox(hwnd,"defs,defs+bus/camiao,bus/camiao,caravana, nao podem ser maiores que o numero de lugares por piso!!!","KARGA", 6);
}else{
//ARMAZENAR VALORES NO ARRAY QUE VAI RETORNAR DEPOIS DA FUNCAO SER EXECUTADA PARA O MAIN
result.piso=piso_int;
result.linha=linha_int;
result.coluna=coluna_int;
result.bus=bus_int;
result.carv=caravana_int;
result.defs=defs_int;
result.heli=helicoptero;
if(bus_int==0|caravana_int==0|defs_int==0|helicoptero==0){
   MessageBox(hwnd,"Existem sem preencher ou com assinaturas ilegais ou de valor zero","KARGA", 6); 
}
//DEPOIS DE ESTABLECER OS VALORES , DESTRUIR A JANELA
DestroyWindow(hwnd);
}
}
}
//BUTTON DO YES
if(LOWORD(wParam)==ID_BUTTON_SIM){
if (HIWORD(wParam) == BN_CLICKED){

    helicoptero=1;
}

}

//BUTTON DO NO
if(LOWORD(wParam)==ID_BUTTON_NAO){
if (HIWORD(wParam) == BN_CLICKED){

    helicoptero=1;
}

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