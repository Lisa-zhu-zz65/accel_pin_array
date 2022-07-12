#include "accel.h"
#include "NU32.h"
// interface with the LSM303D accelerometer/magnetometer using spi
// Wire GND to GND, VDD to 3.3V, Vin is disconnected (on Pololu breakout board)
// SDO4 (F5) ->  SDI (labeled SDA on Pololu board),
// SDI4 (F4) -> SDO
// SCK4 (B14) -> SCL
// RB8 -> CS
#define CS LATBbits.LATB8        // use RB8 as CS

// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI4BUF = o;
  while(!SPI4STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI4BUF;
}

// read data from the accelerometer, given the starting register address.
// return the data in data
void acc_read_register(unsigned char reg[], unsigned char data[], unsigned int len)
{
  unsigned int i;
  for (i = 0; i != len; ++i){ 
    CS = 0;
    reg[i] |= 0x80;
    spi_io(reg[i]);
    data[i] = spi_io(0);
    CS = 1;
  }
  
}
void casting(unsigned char data_raw[], unsigned int len, float data_processed[]){
    unsigned int i;
    for (i = 0; i != len; ++i){ 
        if ((i + 1) % 2 == 0 ){
            data_processed[(i-1)/2] = 0.000122*((short) ((data_raw[i-1]<<8) | data_raw[i]));
        }
    }
}

void time_casting(unsigned char data_raw[], unsigned int len, float data_processed){
    data_processed=(float)((((((data_raw[3] << 8) | data_raw[2]) << 8) | data_raw[1]) << 8) | data_raw[0]);
    data_processed *= 25*10^(-3);
}
void acc_write_register(unsigned char reg, unsigned char data)
{
  CS = 0;               // bring CS low to activate SPI
  spi_io(reg);
  spi_io(data);
  CS = 1;               // complete the command
}

void acc_setup() {      // setup the accelerometer, using SPI 4
  TRISBbits.TRISB8 = 0;
  CS = 1;

  // Master - SPI4, pins are: SDI4(F4), SDO4(F5), SCK4(B14).  
  // we manually control SS4 as a digital output (B8)
  // since the PIC is just starting, we know that spi is off. We rely on defaults here
 
  // setup SPI4
  SPI4CON = 0;              // turn off the SPI module and reset it
  SPI4BUF;                  // clear the rx buffer by reading from it
  SPI4BRG = 6060;            // baud rate to 10MHz [SPI4BRG = (80000000/(2*desired))-1]
  SPI4STATbits.SPIROV = 0;  // clear the overflow bit
  SPI4CONbits.CKE = 0;      // data changes when clock goes from high (idle) to low (active)
  SPI4CONbits.CKP = 1;      // clock is idle high
  SPI4CONbits.MSTEN = 1;    // master operation
  SPI4CONbits.ON = 1;       // turn on SPI 4
 
  // set the accelerometer data rate to 1600 Hz. Do not update until we read values
  //acc_write_register(INT1_CTRL, 0x1); // send data ready signal of accelerometer to interrupt pin 1
  acc_write_register(CTRL1, 0xA8); // setting 6.66kHz, +/- 4g 
  acc_write_register(CTRL10_C, 0x20);// enable timestamp
}
