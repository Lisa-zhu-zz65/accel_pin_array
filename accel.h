#ifndef ACCEL__H__
#define ACCEL__H__

#include "NU32.h"
// Basic interface with an LSM303D accelerometer/compass.
// Used for both i2c and spi examples, but with different implementation (.c) files

                        // register addresses
#define CTRL1 0x10      // control register 1
#define INT1_CTRL 0x0D  // Interrupt pin 1 register
#define CTRL5 0x24      // control register 5
#define CTRL7 0x26      // control register 7
#define STATUS_REG 0x1E       // status register
#define WHO_AM_I 0X0F   // who am I
#define OUT_X_L_A 0x28  // LSB of x-axis acceleration register.
                        // accel. registers are contiguous, this is the lowest address
#define OUT_X_H_A 0x29 
#define OUT_Y_L_A 0x2A  
#define OUT_Y_H_A 0x2B 
#define OUT_Z_L_A 0x2C  
#define OUT_Z_H_A 0x2D

#define CTRL10_C 0x19
#define TIMESTAMP0 0x40
#define TIMESTAMP1 0X41
#define TIMESTAMP2 0X42
#define TIMESTAMP3 0X43

// read len bytes from the specified register into data[]
void acc_read_register(unsigned char reg[], unsigned char data[], unsigned int len); 
void casting(unsigned char data_raw[], unsigned int len, float data_processed[]);

// write to the register
void acc_write_register(unsigned char reg, unsigned char data);                    

// initialize the accelerometer
void acc_setup();

void time_casting(unsigned char data_raw[], unsigned int len, float data_processed);
// void ISR_setup();

// float buffer_read();

// void buffer_write(float data);

// int buffer_full();

// int buffer_empty();
// //void __ISR(_TIMER_1_VECTOR, IPL5SOFT) Timer1ISR(void);

// #define BUFLEN 1024
// #define NSAMPLES 5000
// static volatile int data_buf[BUFLEN];
// static volatile unsigned int read = 0, write = 0;
// static volatile int start = 0;

//
#endif
