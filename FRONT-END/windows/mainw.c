#include <stdio.h>
#include <Windows.h>
//INSTANCIA
HINSTANCE g_hinst;
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

void mainw(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
MSG msg;
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
//LISTA LIVRES & titulo
lista_livres = CreateWindow(TEXT("ListBox"), TEXT(""), 
WS_CHILD | WS_VISIBLE | LBS_NOTIFY| WS_BORDER | WS_VSCROLL
,100, 50, 400,560, hwnd, (HMENU)ID_LISTA_LIVRES, g_hinst, NULL);
CreateWindowW(L"static", L"LISTA DE LUGARES VAGOS",
        WS_CHILD | WS_VISIBLE,
        200, 30, 180,20, 
        hwnd, (HMENU)TITLES , NULL, NULL);
//INPUT DOS LIVRES
 input_livres = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                115, 620,65,23, hwnd, (HMENU)ID_INPUT_LIVRES,
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
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"CARRO");
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"CAMIAO");
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"AUTOCARRO");
SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"CARAVANA");
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
//INPUT DOS LIVRES
 input_livres = CreateWindowW(L"Edit", NULL, 
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                565, 620,65,23, hwnd, (HMENU)ID_INPUT_ESTACIONADOS,
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


break;
case WM_COMMAND:
//COMMUNICATION
if (HIWORD(wParam) == CBN_SELCHANGE) {           
        LRESULT sel = SendMessage(combo, CB_GETCURSEL, 0, 0);
             }
//responds to button click
if (HIWORD(wParam) == BN_CLICKED) {
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