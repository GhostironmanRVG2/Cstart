_int)*(linha_int)||bus_int+defs_int>(coluna_int)*(linha_int)||caravana_int>(linha_int)*(coluna_int)){
    
MessageBox(hwnd,"defs,defs+bus/camiao,bus/camiao,caravana, nao podem ser maiores que o numero de lugares por piso!!!","KARGA", 6);
}else{
//ARMAZENAR VALORES NO ARRAY QUE VAI RETORNAR DEPOIS DA FUN