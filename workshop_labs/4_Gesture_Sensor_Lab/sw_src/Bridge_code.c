/*
 * Bridge_code.c
 *
 *  Created on: 2014-09-08
 *      Author: Erika
 */
#include "Bridge_code.h"
#include "i2c_opencores.h"
#include "si114x_functions.h"
#include <stdio.h>


void delay_10ms(void){
}


//#define I2C_OK (0)
//#define I2C_ACK (0)
//#define I2C_NOACK (1)
//#define I2C_ABITRATION_LOST (2)

/****************************************************************
int I2C_start
            Sets the start bit and then sends the first byte which
            is the address of the device + the write bit.
inputs
      base = the base address of the component
      add = address of I2C device
      read =  1== read    0== write
return value
       0 if address is acknowledged
       1 if address was not acknowledged
15-OCT-07 initial release
*****************************************************************/
//int I2C_start(alt_u32 base, alt_u32 add, alt_u32 read)

/****************************************************************
int I2C_write
            assumes that any addressing and start
            has already been done.
            writes one byte of data from the slave.
            If last is set the stop bit set.
inputs
      base = the base address of the component
      data = byte to write
      last = on the last read there must not be a ack

return value
       0 if address is acknowledged
       1 if address was not acknowledged
15-OCT-07 initial release
*****************************************************************/
//alt_u32 I2C_write(alt_u32 base,alt_u8 data, alt_u32 last)

/****************************************************************
int I2C_read
            assumes that any addressing and start
            has already been done.
            reads one byte of data from the slave.  on the last read
            we don't acknowldge and set the stop bit.
inputs
      base = the base address of the component
      last = on the last read there must not be a ack

return value
       byte read back.
15-OCT-07 initial release
*****************************************************************/
//alt_u32 I2C_read(alt_u32 base,alt_u32 last)


// Byte Write Access to Si114x I2C Registers

s16 Si114xWriteToRegister (HANDLE si114x_handle, u8 address, u8 value){

	int 	StepsComplete;
	int 	RequiredSteps;
	//struct SI114X_HANDLE_S *DevDat;
	alt_u32 AvalonBase;
	alt_u32 DevAdd;

	//DevDat = (struct SI114X_HANDLE_S *)si114x_handle;
	//AvalonBase = DevDat->I2C_BaseAddress;
	//DevAdd = DevDat->Si114x_7BitSlaveAddress;
	//printf("AvalonBase: %X \n DeviceBase: %X\n", AvalonBase, DevAdd );
	AvalonBase = I2C_BASEADDRESS;
	DevAdd = Si114x_7BitSLAVEADDRESS;
	//printf("AvalonBase: %X \n DeviceBase: %X\n", AvalonBase, DevAdd );

	StepsComplete = 0;
	RequiredSteps = 0;
	if(I2C_start( AvalonBase, DevAdd, I2C_WRITE ) == I2C_ACK){
		StepsComplete++;
	}

	RequiredSteps++;
	if( StepsComplete == RequiredSteps ){
		if( I2C_write( AvalonBase, (alt_u8) address, (alt_u32) FALSE) == I2C_ACK){
			StepsComplete++;
		}
	}

	RequiredSteps++;
	if( StepsComplete==RequiredSteps ){
		if( I2C_write( AvalonBase, (alt_u8) value, (alt_u32) TRUE) == I2C_ACK){
			StepsComplete++;
		}
	}
	RequiredSteps++;
	//printf("Write Required Steps: %i, Steps Completed: %i\n", RequiredSteps, StepsComplete);
	return( StepsComplete==RequiredSteps );
}


// Byte Read Access to Si114x I2C Registers
s16 Si114xReadFromRegister(HANDLE si114x_handle, u8 address) {

	s16 	ValueRead;
	int 	StepsComplete;
	int 	RequiredSteps;
	//struct SI114X_HANDLE_S *DevDat;
	alt_u32 AvalonBase;
	alt_u32 DevAdd;

	//DevDat = (struct SI114X_HANDLE_S *)si114x_handle;
	//AvalonBase = DevDat->I2C_BaseAddress;
	//DevAdd = DevDat->Si114x_7BitSlaveAddress;
	//printf("AvalonBase: %X \n DeviceBase: %X\n", AvalonBase, DevAdd );
	AvalonBase = I2C_BASEADDRESS;
	DevAdd = Si114x_7BitSLAVEADDRESS;
	//printf("AvalonBase: %X \n DeviceBase: %X\n", AvalonBase, DevAdd );


	StepsComplete = 0;
	RequiredSteps = 0;
	if(I2C_start( AvalonBase, DevAdd, I2C_WRITE ) == I2C_ACK){
		StepsComplete++;
	}

	RequiredSteps++;
	if( StepsComplete == RequiredSteps ){
		if( I2C_write( AvalonBase, (alt_u8) address, (alt_u32) FALSE) == I2C_ACK){
			StepsComplete++;
		}
	}
	RequiredSteps++;
	if( StepsComplete == RequiredSteps ){
		if(I2C_start( AvalonBase, DevAdd, I2C_READ ) == I2C_ACK){
			StepsComplete++;
		}
	}
	RequiredSteps++;
	if( StepsComplete == RequiredSteps ){
		ValueRead = I2C_read( AvalonBase, (alt_u32) TRUE);
		StepsComplete++;
	}

	RequiredSteps++;
	//printf("Read Required Steps: %i, Steps Completed: %i\n", RequiredSteps, StepsComplete);

	if( StepsComplete == RequiredSteps ){
		return ValueRead;
	}
	else{
		return -1;
	}

}

// Block Write Access to Si114x I2C Registers
s16 Si114xBlockWrite(HANDLE si114x_handle, u8 address, u8 length, u8 *values) {
	int 	StepsComplete;
	int 	RequiredSteps;
	int 	BytesRemaining;
	//struct SI114X_HANDLE_S *DevDat;
	alt_u32 AvalonBase;
	alt_u32 DevAdd;

	//DevDat = (struct SI114X_HANDLE_S *)si114x_handle;
	//AvalonBase = DevDat->I2C_BaseAddress;
	//DevAdd = DevDat->Si114x_7BitSlaveAddress;
	AvalonBase = I2C_BASEADDRESS;
	DevAdd = Si114x_7BitSLAVEADDRESS;

	StepsComplete = 0;
	RequiredSteps = 0;
	if(I2C_start( AvalonBase, DevAdd, I2C_WRITE ) == I2C_ACK){
		StepsComplete++;
	}

	RequiredSteps++;
	if( StepsComplete==RequiredSteps ){
		if( I2C_write( AvalonBase, (alt_u8) address, (alt_u32) FALSE) == I2C_ACK){
			StepsComplete++;
		}
	}

	BytesRemaining = (int)length;
	while ( (++RequiredSteps == StepsComplete) && (BytesRemaining > 1) ){
		if( I2C_write( AvalonBase, (alt_u8) (*values++), (alt_u32) FALSE) == I2C_ACK){
			StepsComplete++;
			BytesRemaining--;
		}
	}

	//RequiredSteps++;
	//printf("Block Write Required Steps: %i, Steps Completed: %i\n", RequiredSteps, StepsComplete);

	if( StepsComplete==RequiredSteps ){
		if( I2C_write( AvalonBase, (alt_u8) *values, (alt_u32) TRUE) == I2C_ACK){
			BytesRemaining--;
		}
	}

	return( (s16)((int)(BytesRemaining) ));
}


// Block Read Access to Si114x I2C Registers
s16 Si114xBlockRead(HANDLE si114x_handle, u8 address, u8 length, u8 *values) {

	int 	StepsComplete;
	int 	RequiredSteps;
	int 	BytesRemaining;
	//struct SI114X_HANDLE_S *DevDat;
	alt_u32 AvalonBase;
	alt_u32 DevAdd;

	//DevDat = (struct SI114X_HANDLE_S *)si114x_handle;
	//AvalonBase = DevDat->I2C_BaseAddress;
	//DevAdd = DevDat->Si114x_7BitSlaveAddress;
	AvalonBase = I2C_BASEADDRESS;
	DevAdd = Si114x_7BitSLAVEADDRESS;

	StepsComplete = 0;
	RequiredSteps = 0;
	BytesRemaining = (int)length;

	if(I2C_start( AvalonBase, DevAdd, I2C_WRITE ) == I2C_ACK){
		StepsComplete++;
	}

	RequiredSteps++;
	if( StepsComplete==RequiredSteps ){
		if( I2C_write( AvalonBase, (alt_u8) address, (alt_u32) FALSE) == I2C_ACK){
			StepsComplete++;
		}
	}
	RequiredSteps++;
	if( StepsComplete==RequiredSteps ){
		if(I2C_start( AvalonBase, DevAdd, I2C_READ ) == I2C_ACK){
			StepsComplete++;
		}
	}

	RequiredSteps++;
	//printf("BlockRead Required Steps: %i, Steps Completed: %i\n", RequiredSteps, StepsComplete);

	if( StepsComplete==RequiredSteps ){
		while ((BytesRemaining-- > 0) ){
			*values++ = (u8)I2C_read( AvalonBase, (alt_u32) (BytesRemaining == 0) );
		}
	}

	return( (s16)((int)(length - BytesRemaining) ));

}

