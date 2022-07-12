#include <xc.h> // Load the proper header for the processor
#include "NU32.h"
//#include "constants.h"
#include "interrupts.h"
#include <math.h>
#include <stdio.h>
#include "accel.h"

#define BUF_SIZE 200

char message[BUF_SIZE], option[BUF_SIZE];
int i; // generic variable
char buffer[200];
unsigned char accels_raw[6];
float accels[3];
unsigned char accel_reg[6] = { OUT_X_H_A, OUT_X_L_A, OUT_Y_H_A, OUT_Y_L_A, OUT_Z_H_A, OUT_Z_L_A} ;
unsigned char status_reg[1] = {STATUS_REG};
unsigned char RDY_Flag[1];
unsigned char who_am_i[1] = {WHO_AM_I};
unsigned char who_val[1];
unsigned char timestamp_reg[4] = {TIMESTAMP0, TIMESTAMP1, TIMESTAMP2, TIMESTAMP3};
unsigned char timestamp_raw[4];
float timestamp;
int main()
{

    __builtin_disable_interrupts();
    acc_setup();      
    NU32_Startup();


  
    __builtin_enable_interrupts();

    NU32_ReadUART3(message, BUF_SIZE);
    sprintf(message, "%s\r\n", "CONNECTED");
    NU32_WriteUART3(message);

    while (1)
    {

        sprintf(message, "case?\r\n");
        NU32_WriteUART3(message);

        NU32_ReadUART3(message, BUF_SIZE);
        sscanf(message, "%s", &option);

        switch (option[0])
        {
        default:
        {
            NU32_LED2 = 0; // turn off LED2 to indicate an error
            break;
        }
        case 'b': // set individual node
        {
            sprintf(message, "in case b.\r\n"); // check in right case
            NU32_WriteUART3(message);
            

            while (1){
                //acc_read_register(who_am_i, who_val, 1);
                //sprintf(buffer,"who am I %d\r\n", who_val[0]);
                //NU32_WriteUART3(buffer);
                acc_read_register(status_reg, RDY_Flag, 1);
                //start = 1;
                //sprintf(buffer,"data ready flag %d\r\n", RDY_Flag[0]);
                //NU32_WriteUART3(buffer);
                if (RDY_Flag[0] | 0 != 0) {
                    acc_read_register(accel_reg, accels_raw, 6);
                    casting(accels_raw, 6, accels);
                    acc_read_register(timestamp_reg, timestamp_raw, 4);
                    time_casting(timestamp_raw, 4 , timestamp);
                    sprintf(buffer,"%f %f %f %f\r\n",timestamp, accels[0], accels[1], accels[2]);
                    NU32_WriteUART3(buffer);
                    RDY_Flag[0] = 0;
                 }
                else {
                     continue;
                 }
                //_CP0_SET_COUNT(0);
                //while(_CP0_GET_COUNT() < 40000000) { ; }
            }
            break;
        }




        

        

        
        }
    }
}
