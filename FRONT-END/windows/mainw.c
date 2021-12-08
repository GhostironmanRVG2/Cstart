#include <stdio.h>
#include <Windows.h>
LRESULT CALLBACK Wnd(HWND, UINT, WPARAM, LPARAM);
void DisableMaximizeButton(HWND hwnd);
void mainw(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
MSG msg;
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
switch(msg)
{
case WM_CREATE:

break;
case WM_COMMAND:
//responds to button click
if (HIWORD(wParam) == BN_CLICKED) {
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