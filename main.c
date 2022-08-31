/*
 * File:   main.c
 * Author: Hamilton Canoquela
 *
 * Created on 24 de Agosto de 2022, 11:03
 */

#include <xc.h>
#include "configs_bit.h"

#define _XTAL_FREQ 8000000 // 8MHz crystal
#define baud 57600
#define spbrg_value ((_XTAL_FREQ/(4*baud))-1)                   // Fórmula muda dependo dos bits SYNC, BRGH e BRG16

//unsigned char serial_data;

void configEUSART();
void configOSCI();




void main(void) {
    
    configOSCI();
    configEUSART();
     
    while(1){
           
        //while(PIR3bit.RC2IF == 0);                            
        //serial_data = RC2REG;          // Armazenar os dados a serem recebidos
        
        TX2REG = "U";                   // Armazenar os dados a serem transmitidos 
        while(PIR3bits.TX2IF == 0);     // PIR3---> Registro de Solicitação de Interrupção Periférica 3
                                        // TXxIF: Este é o bit sinalizador de interrupção do transmissor. Ele se torna alto quando o registrador TXxREG está vazio. 
                                        // RCxIF: Este é o bit sinalizador de interrupção do receptor. Torna-se alto quando o registrador RCREG está cheio.
    
        // PIE1 ---> Registro de Habilitação de Interrupção Periférica 3    
        // PIE3bits.TX2IE == 1;  TXxIE: Este bit é definido como alto para habilitar a interrupção da transmissão.
        // PIE3bits.RC2IE == 1;  RCxIE: Este bit é definido como alto para habilitar a interrupção de recepção. 
    }
 
    return;
}






void configEUSART(){
        
    // Para termos a Taxa de transmisão desejada:
    BAUD2CONbits.BRG16 = 1;                                 // Habilita/desabilita registrador de taxa de transmissão de 16 bits. BRG16 = 1 --> 16bits habilitados e a taxa é definida pelos registros SPxBRGL e SPxBRGH
    TX2STAbits.BRGH = 1;                                    // Velocidade da comunicação serial, depende do bit SYNC     
    TX2STAbits.SYNC = 0;                                    // Modo de comunicação - Assíncrono = 0; Síncrono = 1;
    SP2BRGH = 0;
    SP2BRGL = spbrg_value ;
       
    // Pino para saída da transmissão TX (RD0), placa BTC:
    TRISCbits.TRISC6 = 0;                                   // Definir a porta RC6 como saída 
    ANSELCbits.ANSELC6 = 0;                                 // Definir a porta RC6 como Digital
    RC6PPS = 0x0B;                                          // Definir a porta RC6 para saída TX 
      
    // Pino para entrada da transmissão RX (RD1), placa BTC: 
    TRISCbits.TRISC7 = 1;
    ANSELCbits.ANSELC7 = 0;
    RX2PPS = 0b00010111;                                    // Definir a porta RC7 para entrada RX PIN - bits 2:0 (111 - 7) , PORT - BITS 4:3 (10 - C), R/W ) ----- RC7
    
    // Habilitando a transmissão: 
    RC2STAbits.SPEN = 1;                    // Habilita a porta Serial
    TX2STAbits.TXEN = 1;                    // Habilita a transmissão 
    RC2STAbits.CREN = 1;                    // Habilita a recepção
            
    }


void configOSCI(){
    
    OSCFRQbits.HFFRQ = 0b0011;           // HFFEQ = 8MHZ
    OSCCON1bits.NOSC = 0b110;            // Fonte do clock --- HFINTOSC (1MHz))
    OSCCON2bits.COSC = 0b110;            // Bits de seleção da fonte do oscilador atual --- HFINTOSC
    OSCCON1bits.NDIV = 0b0000;           // Divisor do clock = 1 ------ NOSC/NDIV (1:1)
    OSCCON2bits.CDIV = 0b0000;           // Bits de seleção do divisor de corrente = 1   
    //CONFIG1bits.RSTOSC = 0b110;
    
}