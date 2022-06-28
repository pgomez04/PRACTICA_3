/*
    PRACTICA 3. UART - ENVIO DE CARACTERES 
    PAULINA GOMEZ FABELA
*/


#include "lib/include.h"
int main(void)

{
    Configurar_PLL();
    Configurar_UART2();
    writeString("no quiero reprobar\n");
    //writeChar('h');

    while (1U){}
}



