
#include "../lib/include.h"


extern void Configurar_UART2(void)
{
    SYSCTL->RCGCUART |= 0x00000004; //Habilito UART2
    SYSCTL->RCGCGPIO |= 0x00000001; //Puerto A
    //                    PA7      PA6
    GPIOA_AHB->AFSEL |= (1<<7) | (1<<6);
    GPIOA_AHB->DIR   |= (1<<7) | (0<<6);
    GPIOA_AHB->PUR   |= (0<<7) | (0<<6);
    GPIOA_AHB->PDR   |= (0<<7) | (0<<6);
    GPIOA_AHB->AMSEL |= (0<<7) | (0<<6);
    GPIOA_AHB->DEN   |= (1<<7) | (1<<6);
    GPIOA_AHB->PCTL   = (GPIOA_AHB->PCTL & 0xF00FFFFF) | 0x011000000; //bit 6 y 7

    //baudrate 115,200 frecuencia reloj 80,000,000 Hz
    // BRD = 80,000,000 / (16*115200) = 43.40277
    // UARTFBRD[DIVFRAC] = integer(0.40277 * 64 + 0.5) = 26

    //              RX       TX     UARTEN
    UART2->CTL |= (0<<8) | (0<<9) | (0<<0); //Deshabilito
    UART2->IBRD = 43;
    UART2->FBRD = 26;
    UART2->LCRH = (0x3<<5) | (1<<4); //8 bits y pila
    Habilitar_IntUART();
    UART2->CC   = 0x0;
    UART2->CTL |= (1<<9) | (1<<0) | (1<<8); //Habilito
    UART2->DR = 0x00000000;
}

extern char readChar(void)
{
    int32_t v;
    char c;
    while((UART2->FR & (1<<4))!=0);
    v = UART2->DR & 0xFF;
    c = v;
    return c;
}

extern void writeChar(char c)
{
    while((UART2->FR & (1<<5)) != 0);
    UART2->DR = c;
}


extern char * readText(void)
{
    uint32_t i=0;
    char c;
    char *string = (char*)calloc(1,sizeof(char));
    while((UART2->FR & (1<<4)) == 0)
    {
        if (i>=1)
        {
            string = realloc(string,(i+1)*sizeof(char));
        }
        c = readChar();
        *(string + i) = c;
        i++;
    }
    return string;

}

extern void writeString(char * S)
{
    while(*S)
    {
        writeChar(*(S++));
    }
    writeChar('\n');

}

extern void Habilitar_IntUART(void)
{
    UART2->IFLS = (UART2->IFLS & 0x00) | 0x1;
    UART2->IM   = (1<<5) | (1<<4);
    NVIC->IP[8] = (NVIC->IP[8] & 0xFFFF00FF) | 0x00004000;
    NVIC->ISER[1]  = 0x0000002;
}

extern void UART2_ISR(void)
{

    char a;
    if((UART2->RIS & (1<<4)))
    {
        a = (int)readText();
        //readText();
        UART2->ICR |= (1<<4);
    }
    if(UART2->RIS & (1<<5))
    {
        UART2->ICR |= (1<<5);
    }
}



