#include <xc.h>
#include "var.h"
#include "comandos.h"
#include "display.h"
#include <plib/usart.h>
#include <p18f4550.h>
#include "xlcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#pragma CONFIG WDT = OFF
#pragma config PBADEN = OFF
#define _XTAL_FREQ 20000000 //The speed of your internal(or)external oscillator

void main(void) {
    iniciaPic();
    init_XLCD();

    controi_tank();
   // obstaculo();


    while (1) {
        //executa_comando();
        //controi_tank();
        /*if(PORTDbits.RD3 || PORTDbits.RD1){
        obstaculo();
        }*/

        if (PORTDbits.RD3) {
            while (PORTDbits.RD3);
            btnDireito();
        }
        if (PORTDbits.RD1) {
            while (PORTDbits.RD1);
            btnEsquerdo();
        }

        if (PORTDbits.RD2) {
            while (PORTDbits.RD2);
            btnAtira();
            //obstaculo();
        }
    }
}

void interrupt InterruptPic(void) {
    if (TMR0IF) {
        x++;
        TMR0 = 46005;
        INTCONbits.TMR0IF = 0;
        if (PORTDbits.RD3 == 1) {
            while (PORTDbits.RD3);
            btnDireito();
        }
        if (PORTDbits.RD1 == 1) {
            while (PORTDbits.RD1);
            btnEsquerdo();
        }

        if (PORTDbits.RD2 == 1) {
            while (PORTDbits.RD2);
            btnAtira();
            //obstaculo();
        }

        if (x == 10) {
            x = 0;
            rotina_segundo();
        }
    }
}