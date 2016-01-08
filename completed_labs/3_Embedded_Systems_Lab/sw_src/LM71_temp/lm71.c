// --------------------------------------------------------------------
// Copyright (c) 2015 by Terasic Technologies Inc.
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h>
#include <stddef.h>
#include <unistd.h>  // usleep (unix standard?)

#include "alt_types.h"  // alt_u32
#include "altera_avalon_pio_regs.h" //IOWR_ALTERA_AVALON_PIO_DATA

#include "system.h"

#define WRITE_MODE       1
#define READ_STATUS      2
#define READ_DATA	     3

int main()
{
	alt_u16 data_id,data_temp,temp_result;
	float temp_value;
	printf ("======== DECA Temperature Sensor Test ========\n\n");

	IOWR(TEMP_LM71CIMF_BASE, WRITE_MODE, 0xffff);  //set shutdown
    while(!IORD(TEMP_LM71CIMF_BASE, READ_STATUS) ); //write over

	IOWR(TEMP_LM71CIMF_BASE, WRITE_MODE, 0x00);  //set Conversion Mode
    while(!IORD(TEMP_LM71CIMF_BASE, READ_STATUS) ); //write over
    data_id = IORD(TEMP_LM71CIMF_BASE, READ_DATA); //manufacturer's/DeviceID information
    if(data_id!=0x800f)
     printf("READ ID Fail! ID: 0x%x\n",data_id);

    while(1){

    	IOWR(TEMP_LM71CIMF_BASE, WRITE_MODE, 0x00);  //set Conversion Mode
        while(!IORD(TEMP_LM71CIMF_BASE, READ_STATUS) ); //write over

        data_temp = IORD(TEMP_LM71CIMF_BASE, READ_DATA);
       // printf("read data : 0x%x\n",data_temp);
        temp_result=data_temp>>2;
        temp_value=(float)temp_result* 0.03125;
        printf("Board temperature: %.2f*C \n",temp_value);
        usleep(300*1000);
    }

 }


