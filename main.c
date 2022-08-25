/*
 * File:   main.c
 * Author: mcuser
 *
 * Created on 24 de Agosto de 2022, 11:03
 */

#include <xc.h>
#include "configs_bit.h"

#define _XTAL_FREQ 20000000 // 20MHz crystal

//#define SW_B0 LATAbits.LATA0
//#define B0_LED LATBbits.LATB0


void configEUSART();



void main(void) {
    
    configEUSART();
    
    /*
    TRISAbits.TRISA0 = 1;
    TRISBbits.TRISB0 = 0;
    
    ANSELAbits.ANSELA0 = 0;
    ANSELBbits.ANSELB0 = 0;
    
    LATAbits.LATA0 = 0;
    LATBbits.LATB0 = 1;
    
    int i = 0;
    while(i<30000) i++;
    
    LATBbits.LATB0 = 0;
    
    
    while(1){
        if(LATAbits.LATA0 == 1){
            TX2REG = 1;
            LATBbits.LATB0 = 1;
            while(LATAbits.LATA0) LATBbits.LATB0 = 1;
                
                i = 0;
                while(i<3000) i++;  
                
                LATBbits.LATB0 = 0;      
        } 
    }
    */
    
    while(1){
        TX2REG = "U";
        while(PIR3bits.TX2IF == 0);
    }
    
    
    
    return;
}


void configEUSART(){
        
    // Para termos a Taxa de transmisão desejada:
    SP2BRGH = 0;
    SP2BRGL = 25;                            //9600
    TX2STAbits.BRGH = 1;
    BAUD2CONbits.BRG16 = 0;
    
    // Pino para saída da transmissão TX (RD0):
    TRISDbits.TRISD0 = 0;
    ANSELDbits.ANSELD0 = 0;
    RD0PPS = 0x0B; 
    
    // Definir a porta serial Assíncrona:
    TX2STAbits.SYNC = 0;
          
    // Pino para entrada da transmissão RX (RD1): 
    TRISDbits.TRISD1 = 1;
    ANSELDbits.ANSELD1 = 0;
    RX2PPS = 0b00011001;                // PIN - bits 2:0 (001 - 1) , PORT - BITS 4:3 (11 - D), R/W )
    
    // Habilitando a transmissão: 
    TX2STAbits.TXEN = 1;
    RC2STAbits.SPEN = 1;
            
    }
    