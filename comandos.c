#include <xc.h>
#include "var.h"
#include "comandos.h"
#include <plib/usart.h>
#include <p18f4550.h>
#include "display.h"
#include "xlcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <delays.h>

#define FREQ 20000000  //20MHz
#define baud 19200
#define spbrg_value (((FREQ/64)/baud)-1)  //Refer to the formula for Baud rate calculation in Description tab

void iniciaPic() {
    SPBRG = spbrg_value; // Fill the SPBRG register to set the Baud Rate

    RCSTA = 0b10010000; // 0x90 (SPEN RX9 SREN CREN ADEN FERR OERR RX9D)
    TXSTA = 0b00100000; // 0x20 (CSRC TX9 TXEN SYNC - BRGH TRMT TX9D)
    TRISCbits.RC6 = 0; //TX pin set as output
    TRISCbits.RC7 = 1; //RX pin set as input

    //compare with the table above
    RCIF = 0; //reseta o pino de flag RX
    RCIP = 0; //Not high priority
    RCIE = 1; //Ativa interrupção em RX 
    PEIE = 1; //Enable pheripheral interrupt (serial port is a pheripheral)

    T0CONbits.TMR0ON = 0; //desabilita timer0    
    INTCONbits.TMR0IE = 1; //Habilita interupção TMR0
    INTCONbits.TMR0IF = 0; // limpa flag de interrupção    
    T0CONbits.T08BIT = 0; // temporizador/contador de 16 bits
    T0CONbits.PSA = 0;
    T0CONbits.T0PS0 = 0; //configura prescaler como 1:16;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0CS = 0; //utiliza clock interno    
    TMR0 = 46005;
    T0CONbits.TMR0ON = 1; //habilita timer0    
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
}

void mudaTela() {
    tela++;
    if (tela == 6) {
        tela = 0;
    }
}

void rotina_segundo() {
    //incrementar segundo no display
    cont_seg++;
}

void trocarTela() {
    switch (tela) {
        case 0:
            //telaInicial();
            break;
        case 1:
            //telaJogo();
            btnDireito();
            break;
        case 2:
            //telaFim();
            btnEsquerdo();
            break;
    }
}

void controi_tank() {
    char pos_vet[] = {0x80, 0xC0, 0x94, 0xD4};
    i = 0;
    //if (i == 0) {
    SetDDRamAddr(0x80);
    putrsXLCD(" ");
    SetDDRamAddr(0xC0);
    putrsXLCD(" ");
    SetDDRamAddr(0x94);
    putrsXLCD(" ");
    SetDDRamAddr(0xD4);
    putrsXLCD(" ");
    SetDDRamAddr(pos_vet[i]);
    putrsXLCD("D");
    //}
}

void btnDireito() {
    if(i==0){
    SetDDRamAddr(0x00); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x40); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x14); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x54); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x40); //Primeira linha
    putrsXLCD("D");
    }
    if(i==1){
    SetDDRamAddr(0x00); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x40); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x14); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x54); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x14); //Primeira linha
    putrsXLCD("D");
    }
    if(i==2){
    SetDDRamAddr(0x00); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x40); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x14); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x54); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x54); //Primeira linha
    putrsXLCD("D");
    }
    if(i==3){
    SetDDRamAddr(0x00); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x40); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x14); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x54); //Primeira linha
    putrsXLCD(" ");
    SetDDRamAddr(0x54); //Primeira linha
    putrsXLCD("D");
    }
    i++;
    if(i==4){
    i = 3;
    }
}

void btnEsquerdo() {

    if (i == 0) {
        SetDDRamAddr(0x80); //Primeira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xC0); //Segunda linha
        putrsXLCD(" ");
        SetDDRamAddr(0x94); //Terceira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xD4); //Quarta linha
        putrsXLCD(" ");
        SetDDRamAddr(0x80); // linha
        putrsXLCD("D");
    }
    if (i == 1) {
        SetDDRamAddr(0x80); //Primeira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xC0); //Segunda linha
        putrsXLCD(" ");
        SetDDRamAddr(0x94); //Terceira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xD4); //Quarta linha
        putrsXLCD(" ");
        SetDDRamAddr(0x80); //Primeira linha
        putrsXLCD("D");
    }
    if (i == 2) {
        SetDDRamAddr(0x80); //Primeira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xC0); //Segunda linha
        putrsXLCD(" ");
        SetDDRamAddr(0x94); //Terceira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xD4); //Quarta linha
        putrsXLCD(" ");
        SetDDRamAddr(0xC0); //Primeira linha
        putrsXLCD("D");
    }
    if (i == 3) {
        SetDDRamAddr(0x80); //Primeira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xC0); //Segunda linha
        putrsXLCD(" ");
        SetDDRamAddr(0x94); //Terceira linha
        putrsXLCD(" ");
        SetDDRamAddr(0xD4); //Quarta linha
        putrsXLCD(" ");
        SetDDRamAddr(0x94); //Primeira linha
        putrsXLCD("D");
    }
    i--;
    if (i == -1) {
        i = 0;
    }
}

void btnAtira() {

    char pos_linha0[] = {0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F};
    char pos_linha1[] = {0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF};
    char pos_linha2[] = {0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3};
    char pos_linha3[] = {0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3};

    if (i == 0) {
        SetDDRamAddr(0x81); //Primeira linha
        putrsXLCD("-");
        int coluna0 = 1;
        while (coluna0 < 15) {
            SetDDRamAddr(pos_linha0[coluna0]);
            putrsXLCD("-");
            SetDDRamAddr(pos_linha0[coluna0 - 1]);
            putrsXLCD(" ");
            coluna0++;
            Delay10KTCYx(25);
            SetDDRamAddr(pos_linha0[14]);
            putrsXLCD(" ");
        }
        matar = 0;
    }
    if (i == 1) {
        SetDDRamAddr(0xC1); //Primeira linha
        putrsXLCD("-");
        int coluna1 = 1;
        while (coluna1 < 15) {
            SetDDRamAddr(pos_linha1[coluna1]);
            putrsXLCD("-");
            SetDDRamAddr(pos_linha1[coluna1 - 1]);
            putrsXLCD(" ");
            coluna1++;
            Delay10KTCYx(25);
            SetDDRamAddr(pos_linha1[14]);
            putrsXLCD(" ");
        }
        matar = 1;
    }
    if (i == 2) {
        SetDDRamAddr(0x95); //Primeira linha
        putrsXLCD("-");
        int coluna2 = 1;
        while (coluna2 < 15) {
            SetDDRamAddr(pos_linha2[coluna2]);
            putrsXLCD("-");
            SetDDRamAddr(pos_linha2[coluna2 - 1]);
            putrsXLCD(" ");
            coluna2++;
            Delay10KTCYx(25);
            SetDDRamAddr(pos_linha2[14]);
            putrsXLCD(" ");
        }
        matar = 2;
    }
    if (i == 3) {
        SetDDRamAddr(0xD5); //Primeira linha
        putrsXLCD("-");
        int coluna3 = 1;
        while (coluna3 < 15) {
            SetDDRamAddr(pos_linha3[coluna3]);
            putrsXLCD("-");
            SetDDRamAddr(pos_linha3[coluna3 - 1]);
            putrsXLCD(" ");
            coluna3++;
            Delay10KTCYx(25);
            SetDDRamAddr(pos_linha3[14]);
            putrsXLCD(" ");
        }
        matar = 3;
    }
    if (controle >= 4) {
        controle = 0;
        //obstaculo();
    }
}

/*void obstaculo() {

    char pos_linha0[] = {0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F};
    char pos_linha1[] = {0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF};
    char pos_linha2[] = {0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3};
    char pos_linha3[] = {0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3};

    SetDDRamAddr(0x8F); //Última linha
    putrsXLCD("X");
    SetDDRamAddr(0xCF); //Última linha
    putrsXLCD("X");
    SetDDRamAddr(0xA4); //Última linha
    putrsXLCD("X");
    SetDDRamAddr(0xE3); //Última linha
    putrsXLCD("X");

    int coluna0 = 14;
    int coluna1 = 14;
    int coluna2 = 14;
    int coluna3 = 14;
    controle = 0;

    while (coluna0 >= -1) {

        if (matar != 0) {
            SetDDRamAddr(pos_linha0[coluna0]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha0[coluna0 + 1]);
            putrsXLCD(" ");
            coluna0--;
            controle++;
        }
        if (matar != 1) {
            SetDDRamAddr(pos_linha1[coluna1]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha1[coluna1 + 1]);
            putrsXLCD(" ");
            coluna1--;
            controle++;
        }
        if (matar != 2) {
            SetDDRamAddr(pos_linha2[coluna2]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha2[coluna2 + 1]);
            putrsXLCD(" ");
            coluna2--;
            controle++;
        }
        if (matar != 3) {
            SetDDRamAddr(pos_linha3[coluna3]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha3[coluna3 + 1]);
            putrsXLCD(" ");
            coluna3--;
            controle++;
        }
        Delay10KTCYx(1000);

    }

}
 */


void obstaculo() {

    char pos_linha0[] = {0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F};
    char pos_linha1[] = {0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF};
    char pos_linha2[] = {0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3};
    char pos_linha3[] = {0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3};

    if (matar != 0) {
        SetDDRamAddr(0x8F); //Primeira linha
        putrsXLCD("X");
        int coluna0 = 14;
        while (coluna0 >= -1) {
            SetDDRamAddr(pos_linha0[coluna0]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha0[coluna0 + 1]);
            putrsXLCD(" ");
            coluna0--;
            Delay10KTCYx(100);
            controle++;
        }
    }
    if (matar != 1) {
        SetDDRamAddr(0xCF); //Primeira linha
        putrsXLCD("X");
        int coluna1 = 14;
        while (coluna1 >= -1) {
            SetDDRamAddr(pos_linha1[coluna1]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha1[coluna1 + 1]);
            putrsXLCD(" ");
            coluna1--;
            Delay10KTCYx(100);
            controle++;
        }
    }
    if (matar != 2) {
        SetDDRamAddr(0xA4); //Primeira linha
        putrsXLCD("X");
        int coluna2 = 14;
        while (coluna2 >= -1) {
            SetDDRamAddr(pos_linha2[coluna2]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha2[coluna2 + 1]);
            putrsXLCD(" ");
            coluna2--;
            Delay10KTCYx(100);
            controle++;
        }
    }
    if (matar != 3) {
        SetDDRamAddr(0xE3); //Primeira linha
        putrsXLCD("X");
        int coluna3 = 14;
        while (coluna3 >= -1) {
            SetDDRamAddr(pos_linha3[coluna3]);
            putrsXLCD("X");
            SetDDRamAddr(pos_linha3[coluna3 + 1]);
            putrsXLCD(" ");
            coluna3--;
            Delay10KTCYx(100);
            controle++;
        }
    }
}







/*if(PORTDbits.RD2 == 1 && i==0){
            SetDDRamAddr(pos_linha0[0x8F]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x8E]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x8D]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x8C]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x8B]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x8A]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x89]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x88]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x87]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x86]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x85]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x84]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x83]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x82]); 
            putrsXLCD(" ");
            SetDDRamAddr(pos_linha0[0x81]); 
            putrsXLCD(" ");
            }*/
