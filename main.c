#include <stdio.h>
#include <windows.h>
#include "../Cstart/FRONT-END/windows/sizepark.c"
//MAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
//MENSAGEM DE SAIDA
MSG msg;
//WINDOW size park
msg=sizew(hInstance,hPrevInstance,lpCmdLine,nCmdShow);

}