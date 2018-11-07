#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded. 

void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);
void init_XLCD(void);
void mostrar_data();
void mostrarDataHora();
void mostrarClima();
void mostrarInfo();
void mostrar_relogio();

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */