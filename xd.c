#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    char m[10];
    char ma[10];
    strcpy(m,"]");
    strcpy(ma,"[");
    printf("%d\n",(int)ma[0]-48);
    printf("%d\n",(int)m[0]-48);
    
}
