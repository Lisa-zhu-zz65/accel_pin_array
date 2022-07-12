#ifndef interrupts__H__
#define interrupts__H__

#define CS1 LATBbits.LATB7 
#define CS2 LATBbits.LATB8
#define CS3 LATBbits.LATB9
#define CS4 LATBbits.LATB10
#define CS5 LATBbits.LATB11
#define CS6 LATBbits.LATB12
#define CS7 LATBbits.LATB13



void chip_write_data(int*);
void SPI_com_init();
void output_compute();
void interrupt_init();
void digital_init();


#endif
