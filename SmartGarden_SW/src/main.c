/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <xc.h> 
#include <sys/attribs.h>

//#pragma config FSRSSEL = PRIORITY_7     /* Assign the SRS to level 7 priority handlers */

#define LED1 PORTEbits.RE5
#define LED2 PORTEbits.RE6
#define SW1 PORTFbits.RF6
#define SYS_FREQ        4000000
#define PB_DIV          8
#define PRESCALE        256


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
void initTimer2(void);
void delay_ms(unsigned int milliseconds);

int main(void) {
    // Configurar el pin del LED como salida
    TRISEbits.TRISE5 = 0;  // Configurar el pin RB7 como salida
    TRISFbits.TRISF6=1;
    // Inicializar Timer2
    initTimer2();
    // Bucle infinito
    while (1) {
        // Encender el LED
        LED1=1;
        delay_ms(500);  // Mantener encendido durante 150ms
        LED1=0;
        delay_ms(500);  // Mantener encendido durante 150ms
    }

    return 0;
}

// Inicializar Timer2
void initTimer2(void) {
    T2CON = 0;  // Limpiar registro de configuración del Timer2
    //T2CONbits.TCKPS = 0b111;  // Configurar el preescalador a 1:256

    // Calcular el valor de PR2 para obtener una interrupción cada 300ms
    PR2 = (SYS_FREQ / (PRESCALE * 1000)) * 300;

    TMR2 = 0;  // Limpiar el contador del Timer2
    T2CONbits.ON = 1;  // Encender Timer2
}

// Función de retardo en milisegundos
void delay_ms(unsigned int milliseconds) {
    while (milliseconds) {
        if (IFS0bits.T2IF) {  // Si la bandera de interrupción del Timer2 está activa
            IFS0bits.T2IF = 0;  // Limpiar la bandera de interrupción del Timer2
            milliseconds--;  // Decrementar el contador de milisegundos
        }
    }
}


/*******************************************************************************
 End of File
*/

