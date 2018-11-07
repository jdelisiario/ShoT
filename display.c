#include <xc.h>
#include "var.h"
#include "display.h"
#include "comandos.h"
#include "xlcd.h"
#include <stdio.h>
#include <stdlib.h>

void DelayFor18TCY(void) {
    Delay10TCYx(120);
}

void DelayPORXLCD(void) {
    Delay1KTCYx(180);
    return;
}

void DelayXLCD(void) {
    Delay1KTCYx(60);
    return;
}

void init_XLCD(void) {
    OpenXLCD(FOUR_BIT & LINES_5X7);

    while (BusyXLCD());
    WriteCmdXLCD(0x06);
    WriteCmdXLCD(0x0C);
}

void mostrarInfo() {
    //   char versao[16];
    //    sprintf(versao, "      %i.%i      ", v,rev);        

    SetDDRamAddr(0x00); //Primeira linha    
    putrsXLCD("ShoT");
    SetDDRamAddr(0xC0); //Segunda linha
    //    putrsXLCD(versao);
}


/*
void btnAtira(){
    char pTiro;
    if (i==0){
    pTiro = linha1;
    }
    if (i==1){
    pTiro = 0x40+1;
    }
    if (i==2){
    pTiro = 0x14+1;
    }
    if (i==0){
    pTiro = 0x54+1;
    }
    SetDDRamAddr(pTiro); 
    putrsXLCD("=");      
    while (pTiro != SetDDRamAddr(0x13) || pTiro != SetDDRamAddr(0x53) || pTiro != SetDDRamAddr(0x27) || pTiro != SetDDRamAddr(0x67)){
       pTiro++;
       SetDDRamAddr(pTiro); 
       putrsXLCD("=");
       SetDDRamAddr(pTiro-1); 
       putrsXLCD(" ");
    }
       SetDDRamAddr(pTiro); 
       putrsXLCD(" ");
}*/