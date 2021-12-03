#include <stdio.h>
#include <Windows.h>
#define INPUT_TEXT_ONE 1
#define INPUT_TEXT_TWO 2
#define INPUT_TEXT_THREE 3
#define TEXT_OUTPUT 4
#define BUTTON_ONE 5
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DisableMaximizeButton(HWND hwnd);
MSG sizew(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
MSG msg;
WNDCLASSEX wc;
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
wc.lpszClassName = TEXT("myWindowClass");
wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
RegisterClassEx(&wc);
//CRIAR A WINDOW
HWND hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("myWindowClass"),TEXT("KARGA"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 370, 230, NULL, NULL, hInstance, NULL);
DisableMaximizeButton(hwnd);
//LOOP DE MENSAGENS
while(GetMessage(&msg, NULL, 0, 0) > 0)
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}

return msg;



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
    //output text using default font
    
    //MSGS
switch(msg)
{
case WM_CREATE:
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
//BUTTON
hwndButton = CreateWindow(TEXT("button"),
 TEXT("APPLY"),
 WS_VISIBLE |  WS_CHILD,
  125, 120, 80, 30,hwnd, (HMENU) BUTTON_ONE, NULL, NULL);//click button
break;
case WM_COMMAND:
//responds to button click
if (HIWORD(wParam) == BN_CLICKED) {
const int maxtextlength = 3;
//INPUT DO QUE VAMOS RECEBER
TCHAR piso[3] = TEXT("");
TCHAR linha[3] = TEXT("");
TCHAR coluna[3] = TEXT("");
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_one,piso, maxtextlength);
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_two, linha, maxtextlength);
//gets value of textbox and stores in  'textvalue'
GetWindowText(input_three,coluna, maxtextlength);
int piso_int,linha_int,coluna_int;
piso_int=atoi(piso);
linha_int=atoi(linha);
coluna_int=atoi(coluna);
if(piso_int==0|linha_int==0|coluna_int==0){
    MessageBox(hwnd,"Por favor introduza dados validos","KARGA", 6);
}else{
printf("%d %d %d",piso_int,linha_int,coluna_int);
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