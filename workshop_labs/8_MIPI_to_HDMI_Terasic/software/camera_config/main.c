

#include <stdio.h>
#include "I2C_core.h"
#include "terasic_includes.h"
#include "system.h"
#include "camera_config.h"



bool DDR3_Check(void){
	bool bSuccess = FALSE;
	int Status;

	Status = IORD(DDR3_STATUS_BASE, 0x00);
	if (Status == 0x0D)
			bSuccess = TRUE;
	else
		printf("DDR3 Status(PLL_LOCK, CAL_SUCCESS, CAL_FAIL, CAL_DONE)=%xh\r\n", Status);

	return bSuccess;

}







// Default setup gives a physical 73.2 MHz internal clock for an external input clock of 24MHz.
bool MIPI_Init(bool bScale, bool bTestMode){
	bool bSuccess;
//	int i;
	alt_u16 Data16, sensor_id;
	alt_u8 Data8;
	const alt_u8 device_address = MIPI_I2C_ADDR;
	int sw;
//	int d;

	bSuccess = oc_i2c_init_ex(I2C_OPENCORES_MIPI_BASE, 50*1000*1000,400*1000); //I2C: 400K
	if (!bSuccess)
		printf("failed to init MIPI i2c\r\n");

	// init
	if (bSuccess){
		BYD_CONFIG_1024x768_RAW8(bScale, bTestMode);

		// dump setting info
		   // check version
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x00, (alt_u8 *)&Data16, sizeof(Data16))){
				sensor_id = SWAP16(Data16);
				printf("chip_version_reg:%04xh\r\n", sensor_id);
			}else{
				bSuccess = FALSE;
				printf("failed to find the camera\r\n");
			}
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x02, (alt_u8 *)&Data8, sizeof(Data8)))
				printf("revision_number:%02xh\r\n", Data8);
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x03, (alt_u8 *)&Data8, sizeof(Data8)))
				printf("manufacturer_id:%02xh\r\n", Data8);
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x04, (alt_u8 *)&Data8, sizeof(Data8)))
				printf("smia_version:%02xh\r\n", Data8);
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x05, (alt_u8 *)&Data8, sizeof(Data8)))
				printf("frame_count:%02xh\r\n", Data8);
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x06, (alt_u8 *)&Data8, sizeof(Data8)))
				printf("pixel_order:%02xh\r\n", Data8);
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x08, (alt_u8 *)&Data16, sizeof(Data16)))
				printf("data_pedestal:%04xh\r\n", SWAP16(Data16));
			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, BYD_MODE_SELECT, (alt_u8 *)&Data8, sizeof(Data8)))
				printf("mode_select:%02xh\r\n", Data8);

			if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x3024, (alt_u8 *)&Data8, sizeof(Data8))){
					printf("Pixel Order:%04xh\r\n", Data8);
					printf("00 = First row is GreenR/Red, first pixel is GreenR\r\n");
					printf("01 = First row is GreenR/Red, first pixel is Red\r\n");
					printf("02 = First row is Blue/GreenB, first pixel is Blue\r\n");
					printf("03 = First row is Blue/GreenB, first pixel is GreenB\r\n");
					printf("\r\n");
				}



		if (OC_I2CL_Read(I2C_OPENCORES_MIPI_BASE, device_address, 0x0112, (alt_u8 *)&Data16, sizeof(Data16))){
				sensor_id = SWAP16(Data16);
				printf("ccp_data_format:%04xh\r\n", sensor_id);
			}

	} //

	oc_i2c_uninit(I2C_OPENCORES_MIPI_BASE);


	return bSuccess;
}

int main()
{
	int SW, preSW;

	IOWR(LED_BASE, 0x00, 0xFF); // LED OFF

  printf("MIPI Demo\n");

  // ddr3 check
  if (!DDR3_Check())
	  printf("DDR3 Init failed!\r\n");
  else
	  printf("DDR3 Init successfully!\r\n");

  // mipi init
  SW = IORD(SW_BASE, 0x00) & 0x03;
  //SW =0x02;
  preSW = SW;
  if (!MIPI_Init(SW & 0x01, SW & 0x02)){
	  printf("MIPI_Init Init failed!\r\n");
  	  IOWR(LED_BASE, 0x00, 0xAF); // LED7/6:half light
  }else{
	  printf("MIPI_Init Init successfully!\r\n");
  	  IOWR(LED_BASE, 0x00, 0x0F); // LED7/6/5/4: full light
  }


  while(1){
	  SW = IORD(SW_BASE, 0x00) & 0x03;
	  //SW =0x02;
	  if (SW != preSW){
		  MIPI_Init(SW & 0x01, SW & 0x02);
		  preSW = SW;
	  }
  }


  return 0;
}
