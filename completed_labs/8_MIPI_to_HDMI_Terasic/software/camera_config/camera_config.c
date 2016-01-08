/*
 * config_reg.c
 *
 *  Created on: 2015/3/27
 *      Author: User
 */

#include <stdio.h>
#include "I2C_core.h"
#include "terasic_includes.h"
#include "system.h"
#include "camera_config.h"




alt_u16 SWAP16(alt_u16 x){
	alt_u16 y;
	//y =  (((x) >> 8) & 0xff) | (((x) & 0xff) << 8);
	y = (x >> 8) & 0x00ff;
	y |= (x << 8) & 0xff00;
	return y;
}




#define Sleep(x)	usleep(x*1000)
#define AR0833DB(x) printf(x)

void AR0833_write_cmos_sensor(alt_u16 Addr, alt_u16 Value){
	const alt_u8 device_address = MIPI_I2C_ADDR;
	//OC_I2CL_Write(I2C_OPENCORES_MIPI_BASE, device_address, SWAP16(Addr), (alt_u8 *)&Value, sizeof(Value));
	OC_I2CL_Write(I2C_OPENCORES_MIPI_BASE, device_address, Addr, (alt_u8 *)&Value, sizeof(Value));

}

void AR0833_write_cmos_sensor_8(alt_u16 Addr, alt_u8 Value){
	const alt_u8 device_address = MIPI_I2C_ADDR;
	//OC_I2CL_Write(I2C_OPENCORES_MIPI_BASE, device_address, SWAP16(Addr), (alt_u8 *)&Value, sizeof(Value));
	OC_I2CL_Write(I2C_OPENCORES_MIPI_BASE, device_address, Addr, (alt_u8 *)&Value, sizeof(Value));

}





void BYD_CONFIG_1024x768_RAW8(bool bScale, bool bTestMode)
{
//    AR0833DB("BYD_CONFIG, Scale=%s, TestMode=%s\r\n", bScale?"yes":"no", bTestMode?"yes":"no");
	printf("=====================================\r\n");
    printf("BYD_CONFIG, Scale=%s, TestMode=%s\r\n", bScale?"yes":"no", bTestMode?"yes":"no");
	printf("=====================================\r\n");

    AR0833_write_cmos_sensor(0x301A, 0x0019); 	// RESET_REGISTER
    Sleep(100);
    AR0833_write_cmos_sensor(0x301A, 0x0218); 	// RESET_REGISTER
    AR0833_write_cmos_sensor(0x3042, 0x0000); 	// DARK_CONTROL2
    AR0833_write_cmos_sensor(0x30C0, 0x1810); 	// CALIB_CONTROL
    AR0833_write_cmos_sensor(0x30C8, 0x0018); 	// CALIB_DAC
    AR0833_write_cmos_sensor(0x30D2, 0x0000); 	// CRM_CONTROL
    AR0833_write_cmos_sensor(0x30D4, 0xD030); 	// COLUMN_CORRECTION
    AR0833_write_cmos_sensor(0x30D6, 0x2200); 	// COLUMN_CORRECTION2
    AR0833_write_cmos_sensor(0x30DA, 0x0080); 	// COLUMN_CORRECTION_CLIP2
    AR0833_write_cmos_sensor(0x30DC, 0x0080); 	// COLUMN_CORRECTION_CLIP3
    AR0833_write_cmos_sensor(0x30EE, 0x0340); 	// DARK_CONTROL3
    AR0833_write_cmos_sensor(0x316A, 0x8800); 	// DAC_RSTLO
    AR0833_write_cmos_sensor(0x316C, 0x8200); 	// DAC_TXLO
    AR0833_write_cmos_sensor(0x3172, 0x0286); 	// ANALOG_CONTROL2
    AR0833_write_cmos_sensor(0x3174, 0x8000); 	// ANALOG_CONTROL3
    AR0833_write_cmos_sensor(0x317C, 0xE103); 	// ANALOG_CONTROL7
    AR0833_write_cmos_sensor(0x3180, 0xF0FF); 	// FINEDIGCORR_CONTROL
    AR0833_write_cmos_sensor(0x31E0, 0x0741); 	// PIX_DEF_ID
    AR0833_write_cmos_sensor(0x3ECC, 0x0056); 	// DAC_LD_0_1
    AR0833_write_cmos_sensor(0x3ED0, 0xA8AA); 	// DAC_LD_4_5
    AR0833_write_cmos_sensor(0x3ED2, 0xAAA8); 	// DAC_LD_6_7
    AR0833_write_cmos_sensor(0x3ED4, 0x8ACC); 	// DAC_LD_8_9
    AR0833_write_cmos_sensor(0x3ED8, 0x7288); 	// DAC_LD_12_13
    AR0833_write_cmos_sensor(0x3EDA, 0x77CA); 	// DAC_LD_14_15
    AR0833_write_cmos_sensor(0x3EDE, 0x6664); 	// DAC_LD_18_19
    AR0833_write_cmos_sensor(0x3EE0, 0x26D5); 	// DAC_LD_20_21
    AR0833_write_cmos_sensor(0x3EE4, 0x1548); 	// DAC_LD_24_25
    AR0833_write_cmos_sensor(0x3EE6, 0xB10C); 	// DAC_LD_26_27
    AR0833_write_cmos_sensor(0x3EE8, 0x6E79); 	// DAC_LD_28_29
    AR0833_write_cmos_sensor(0x3EFE, 0x77CC); 	// DAC_LD_TXLO
    AR0833_write_cmos_sensor(0x31E6, 0x0000); 	// PIX_DEF_ID_2
    AR0833_write_cmos_sensor(0x3F00, 0x0028); 	// BM_T0
    AR0833_write_cmos_sensor(0x3F02, 0x0140); 	// BM_T1
    AR0833_write_cmos_sensor(0x3F04, 0x0002); 	// NOISE_GAIN_THRESHOLD0
    AR0833_write_cmos_sensor(0x3F06, 0x0004); 	// NOISE_GAIN_THRESHOLD1
    AR0833_write_cmos_sensor(0x3F08, 0x0008); 	// NOISE_GAIN_THRESHOLD2
    AR0833_write_cmos_sensor(0x3F0A, 0x0B09); 	// NOISE_FLOOR10
    AR0833_write_cmos_sensor(0x3F0C, 0x0302); 	// NOISE_FLOOR32
    AR0833_write_cmos_sensor(0x3F10, 0x0505); 	// SINGLE_K_FACTOR0
    AR0833_write_cmos_sensor(0x3F12, 0x0303); 	// SINGLE_K_FACTOR1
    AR0833_write_cmos_sensor(0x3F14, 0x0101); 	// SINGLE_K_FACTOR2
    AR0833_write_cmos_sensor(0x3F16, 0x2020); 	// CROSSFACTOR0
    AR0833_write_cmos_sensor(0x3F18, 0x0404); 	// CROSSFACTOR1
    AR0833_write_cmos_sensor(0x3F1A, 0x7070); 	// CROSSFACTOR2
    AR0833_write_cmos_sensor(0x3F1C, 0x003A); 	// SINGLE_MAXFACTOR
    AR0833_write_cmos_sensor(0x3F1E, 0x003C); 	// NOISE_COEF
    AR0833_write_cmos_sensor(0x3F2C, 0x2210); 	// GTH_THRES_RTN
    AR0833_write_cmos_sensor(0x3F40, 0x2020); 	// COUPLE_K_FACTOR0
    AR0833_write_cmos_sensor(0x3F42, 0x0808); 	// COUPLE_K_FACTOR1
    AR0833_write_cmos_sensor(0x3F44, 0x0101); 	// COUPLE_K_FACTOR2
    Sleep(100);

    AR0833_write_cmos_sensor_8(0x3D00, 0x04);
    AR0833_write_cmos_sensor_8(0x3D01, 0x70);
    AR0833_write_cmos_sensor_8(0x3D02, 0xC8);
    AR0833_write_cmos_sensor_8(0x3D03, 0xFF);
    AR0833_write_cmos_sensor_8(0x3D04, 0xFF);
    AR0833_write_cmos_sensor_8(0x3D05, 0xFF);
    AR0833_write_cmos_sensor_8(0x3D06, 0xFF);
    AR0833_write_cmos_sensor_8(0x3D07, 0xFF);
    AR0833_write_cmos_sensor_8(0x3D08, 0x6F);
    AR0833_write_cmos_sensor_8(0x3D09, 0x40);
    AR0833_write_cmos_sensor_8(0x3D0A, 0x14);
    AR0833_write_cmos_sensor_8(0x3D0B, 0x0E);
    AR0833_write_cmos_sensor_8(0x3D0C, 0x23);
    AR0833_write_cmos_sensor_8(0x3D0D, 0x82);
    AR0833_write_cmos_sensor_8(0x3D0E, 0x41);
    AR0833_write_cmos_sensor_8(0x3D0F, 0x5C);
    AR0833_write_cmos_sensor_8(0x3D10, 0x54);
    AR0833_write_cmos_sensor_8(0x3D11, 0x6E);
    AR0833_write_cmos_sensor_8(0x3D12, 0x42);
    AR0833_write_cmos_sensor_8(0x3D13, 0x00);
    AR0833_write_cmos_sensor_8(0x3D14, 0xC0);
    AR0833_write_cmos_sensor_8(0x3D15, 0x5D);
    AR0833_write_cmos_sensor_8(0x3D16, 0x80);
    AR0833_write_cmos_sensor_8(0x3D17, 0x5A);
    AR0833_write_cmos_sensor_8(0x3D18, 0x80);
    AR0833_write_cmos_sensor_8(0x3D19, 0x57);
    AR0833_write_cmos_sensor_8(0x3D1A, 0x84);
    AR0833_write_cmos_sensor_8(0x3D1B, 0x64);
    AR0833_write_cmos_sensor_8(0x3D1C, 0x80);
    AR0833_write_cmos_sensor_8(0x3D1D, 0x55);
    AR0833_write_cmos_sensor_8(0x3D1E, 0x86);
    AR0833_write_cmos_sensor_8(0x3D1F, 0x64);
    AR0833_write_cmos_sensor_8(0x3D20, 0x80);
    AR0833_write_cmos_sensor_8(0x3D21, 0x65);
    AR0833_write_cmos_sensor_8(0x3D22, 0x88);
    AR0833_write_cmos_sensor_8(0x3D23, 0x65);
    AR0833_write_cmos_sensor_8(0x3D24, 0x84);
    AR0833_write_cmos_sensor_8(0x3D25, 0x58);
    AR0833_write_cmos_sensor_8(0x3D26, 0x80);
    AR0833_write_cmos_sensor_8(0x3D27, 0x00);
    AR0833_write_cmos_sensor_8(0x3D28, 0xC0);
    AR0833_write_cmos_sensor_8(0x3D29, 0x80);
    AR0833_write_cmos_sensor_8(0x3D2A, 0x30);
    AR0833_write_cmos_sensor_8(0x3D2B, 0x0C);
    AR0833_write_cmos_sensor_8(0x3D2C, 0x84);
    AR0833_write_cmos_sensor_8(0x3D2D, 0x42);
    AR0833_write_cmos_sensor_8(0x3D2E, 0x82);
    AR0833_write_cmos_sensor_8(0x3D2F, 0x10);
    AR0833_write_cmos_sensor_8(0x3D30, 0x30);
    AR0833_write_cmos_sensor_8(0x3D31, 0xA6);
    AR0833_write_cmos_sensor_8(0x3D32, 0x5B);
    AR0833_write_cmos_sensor_8(0x3D33, 0x80);
    AR0833_write_cmos_sensor_8(0x3D34, 0x63);
    AR0833_write_cmos_sensor_8(0x3D35, 0x8B);
    AR0833_write_cmos_sensor_8(0x3D36, 0x30);
    AR0833_write_cmos_sensor_8(0x3D37, 0x0C);
    AR0833_write_cmos_sensor_8(0x3D38, 0xA5);
    AR0833_write_cmos_sensor_8(0x3D39, 0x59);
    AR0833_write_cmos_sensor_8(0x3D3A, 0x84);
    AR0833_write_cmos_sensor_8(0x3D3B, 0x6C);
    AR0833_write_cmos_sensor_8(0x3D3C, 0x80);
    AR0833_write_cmos_sensor_8(0x3D3D, 0x6D);
    AR0833_write_cmos_sensor_8(0x3D3E, 0x81);
    AR0833_write_cmos_sensor_8(0x3D3F, 0x5F);
    AR0833_write_cmos_sensor_8(0x3D40, 0x60);
    AR0833_write_cmos_sensor_8(0x3D41, 0x61);
    AR0833_write_cmos_sensor_8(0x3D42, 0x10);
    AR0833_write_cmos_sensor_8(0x3D43, 0x30);
    AR0833_write_cmos_sensor_8(0x3D44, 0x88);
    AR0833_write_cmos_sensor_8(0x3D45, 0x66);
    AR0833_write_cmos_sensor_8(0x3D46, 0x83);
    AR0833_write_cmos_sensor_8(0x3D47, 0x6E);
    AR0833_write_cmos_sensor_8(0x3D48, 0x80);
    AR0833_write_cmos_sensor_8(0x3D49, 0x64);
    AR0833_write_cmos_sensor_8(0x3D4A, 0x87);
    AR0833_write_cmos_sensor_8(0x3D4B, 0x64);
    AR0833_write_cmos_sensor_8(0x3D4C, 0x30);
    AR0833_write_cmos_sensor_8(0x3D4D, 0x50);
    AR0833_write_cmos_sensor_8(0x3D4E, 0xDA);
    AR0833_write_cmos_sensor_8(0x3D4F, 0x6A);
    AR0833_write_cmos_sensor_8(0x3D50, 0x83);
    AR0833_write_cmos_sensor_8(0x3D51, 0x6B);
    AR0833_write_cmos_sensor_8(0x3D52, 0xA6);
    AR0833_write_cmos_sensor_8(0x3D53, 0x30);
    AR0833_write_cmos_sensor_8(0x3D54, 0x94);
    AR0833_write_cmos_sensor_8(0x3D55, 0x67);
    AR0833_write_cmos_sensor_8(0x3D56, 0x84);
    AR0833_write_cmos_sensor_8(0x3D57, 0x65);
    AR0833_write_cmos_sensor_8(0x3D58, 0x82);
    AR0833_write_cmos_sensor_8(0x3D59, 0x4D);
    AR0833_write_cmos_sensor_8(0x3D5A, 0x83);
    AR0833_write_cmos_sensor_8(0x3D5B, 0x65);
    AR0833_write_cmos_sensor_8(0x3D5C, 0x30);
    AR0833_write_cmos_sensor_8(0x3D5D, 0x50);
    AR0833_write_cmos_sensor_8(0x3D5E, 0xA6);
    AR0833_write_cmos_sensor_8(0x3D5F, 0x58);
    AR0833_write_cmos_sensor_8(0x3D60, 0x43);
    AR0833_write_cmos_sensor_8(0x3D61, 0x06);
    AR0833_write_cmos_sensor_8(0x3D62, 0x00);
    AR0833_write_cmos_sensor_8(0x3D63, 0x8D);
    AR0833_write_cmos_sensor_8(0x3D64, 0x45);
    AR0833_write_cmos_sensor_8(0x3D65, 0xA0);
    AR0833_write_cmos_sensor_8(0x3D66, 0x45);
    AR0833_write_cmos_sensor_8(0x3D67, 0x6A);
    AR0833_write_cmos_sensor_8(0x3D68, 0x83);
    AR0833_write_cmos_sensor_8(0x3D69, 0x6B);
    AR0833_write_cmos_sensor_8(0x3D6A, 0x06);
    AR0833_write_cmos_sensor_8(0x3D6B, 0x00);
    AR0833_write_cmos_sensor_8(0x3D6C, 0x81);
    AR0833_write_cmos_sensor_8(0x3D6D, 0x43);
    AR0833_write_cmos_sensor_8(0x3D6E, 0x9C);
    AR0833_write_cmos_sensor_8(0x3D6F, 0x58);
    AR0833_write_cmos_sensor_8(0x3D70, 0x84);
    AR0833_write_cmos_sensor_8(0x3D71, 0x30);
    AR0833_write_cmos_sensor_8(0x3D72, 0x90);
    AR0833_write_cmos_sensor_8(0x3D73, 0x67);
    AR0833_write_cmos_sensor_8(0x3D74, 0x64);
    AR0833_write_cmos_sensor_8(0x3D75, 0x88);
    AR0833_write_cmos_sensor_8(0x3D76, 0x64);
    AR0833_write_cmos_sensor_8(0x3D77, 0x80);
    AR0833_write_cmos_sensor_8(0x3D78, 0x65);
    AR0833_write_cmos_sensor_8(0x3D79, 0x88);
    AR0833_write_cmos_sensor_8(0x3D7A, 0x65);
    AR0833_write_cmos_sensor_8(0x3D7B, 0x82);
    AR0833_write_cmos_sensor_8(0x3D7C, 0x10);
    AR0833_write_cmos_sensor_8(0x3D7D, 0xC0);
    AR0833_write_cmos_sensor_8(0x3D7E, 0xEB);
    AR0833_write_cmos_sensor_8(0x3D7F, 0x10);
    AR0833_write_cmos_sensor_8(0x3D80, 0xC0);
    AR0833_write_cmos_sensor_8(0x3D81, 0x66);
    AR0833_write_cmos_sensor_8(0x3D82, 0x85);
    AR0833_write_cmos_sensor_8(0x3D83, 0x64);
    AR0833_write_cmos_sensor_8(0x3D84, 0x81);
    AR0833_write_cmos_sensor_8(0x3D85, 0x17);
    AR0833_write_cmos_sensor_8(0x3D86, 0x00);
    AR0833_write_cmos_sensor_8(0x3D87, 0x80);
    AR0833_write_cmos_sensor_8(0x3D88, 0x20);
    AR0833_write_cmos_sensor_8(0x3D89, 0x0D);
    AR0833_write_cmos_sensor_8(0x3D8A, 0x80);
    AR0833_write_cmos_sensor_8(0x3D8B, 0x18);
    AR0833_write_cmos_sensor_8(0x3D8C, 0x0C);
    AR0833_write_cmos_sensor_8(0x3D8D, 0x80);
    AR0833_write_cmos_sensor_8(0x3D8E, 0x64);
    AR0833_write_cmos_sensor_8(0x3D8F, 0x30);
    AR0833_write_cmos_sensor_8(0x3D90, 0x60);
    AR0833_write_cmos_sensor_8(0x3D91, 0x41);
    AR0833_write_cmos_sensor_8(0x3D92, 0x82);
    AR0833_write_cmos_sensor_8(0x3D93, 0x42);
    AR0833_write_cmos_sensor_8(0x3D94, 0xB2);
    AR0833_write_cmos_sensor_8(0x3D95, 0x42);
    AR0833_write_cmos_sensor_8(0x3D96, 0x80);
    AR0833_write_cmos_sensor_8(0x3D97, 0x40);
    AR0833_write_cmos_sensor_8(0x3D98, 0x81);
    AR0833_write_cmos_sensor_8(0x3D99, 0x40);
    AR0833_write_cmos_sensor_8(0x3D9A, 0x80);
    AR0833_write_cmos_sensor_8(0x3D9B, 0x41);
    AR0833_write_cmos_sensor_8(0x3D9C, 0x80);
    AR0833_write_cmos_sensor_8(0x3D9D, 0x42);
    AR0833_write_cmos_sensor_8(0x3D9E, 0x80);
    AR0833_write_cmos_sensor_8(0x3D9F, 0x43);
    AR0833_write_cmos_sensor_8(0x3DA0, 0x83);
    AR0833_write_cmos_sensor_8(0x3DA1, 0x06);
    AR0833_write_cmos_sensor_8(0x3DA2, 0xC0);
    AR0833_write_cmos_sensor_8(0x3DA3, 0x88);
    AR0833_write_cmos_sensor_8(0x3DA4, 0x44);
    AR0833_write_cmos_sensor_8(0x3DA5, 0x87);
    AR0833_write_cmos_sensor_8(0x3DA6, 0x6A);
    AR0833_write_cmos_sensor_8(0x3DA7, 0x83);
    AR0833_write_cmos_sensor_8(0x3DA8, 0x6B);
    AR0833_write_cmos_sensor_8(0x3DA9, 0x92);
    AR0833_write_cmos_sensor_8(0x3DAA, 0x44);
    AR0833_write_cmos_sensor_8(0x3DAB, 0x88);
    AR0833_write_cmos_sensor_8(0x3DAC, 0x06);
    AR0833_write_cmos_sensor_8(0x3DAD, 0xC8);
    AR0833_write_cmos_sensor_8(0x3DAE, 0x81);
    AR0833_write_cmos_sensor_8(0x3DAF, 0x41);
    AR0833_write_cmos_sensor_8(0x3DB0, 0x85);
    AR0833_write_cmos_sensor_8(0x3DB1, 0x30);
    AR0833_write_cmos_sensor_8(0x3DB2, 0xA4);
    AR0833_write_cmos_sensor_8(0x3DB3, 0x67);
    AR0833_write_cmos_sensor_8(0x3DB4, 0x85);
    AR0833_write_cmos_sensor_8(0x3DB5, 0x65);
    AR0833_write_cmos_sensor_8(0x3DB6, 0x87);
    AR0833_write_cmos_sensor_8(0x3DB7, 0x65);
    AR0833_write_cmos_sensor_8(0x3DB8, 0x30);
    AR0833_write_cmos_sensor_8(0x3DB9, 0x60);
    AR0833_write_cmos_sensor_8(0x3DBA, 0x8D);
    AR0833_write_cmos_sensor_8(0x3DBB, 0x42);
    AR0833_write_cmos_sensor_8(0x3DBC, 0x82);
    AR0833_write_cmos_sensor_8(0x3DBD, 0x40);
    AR0833_write_cmos_sensor_8(0x3DBE, 0x82);
    AR0833_write_cmos_sensor_8(0x3DBF, 0x40);
    AR0833_write_cmos_sensor_8(0x3DC0, 0x80);
    AR0833_write_cmos_sensor_8(0x3DC1, 0x41);
    AR0833_write_cmos_sensor_8(0x3DC2, 0x80);
    AR0833_write_cmos_sensor_8(0x3DC3, 0x42);
    AR0833_write_cmos_sensor_8(0x3DC4, 0x80);
    AR0833_write_cmos_sensor_8(0x3DC5, 0x43);
    AR0833_write_cmos_sensor_8(0x3DC6, 0x83);
    AR0833_write_cmos_sensor_8(0x3DC7, 0x06);
    AR0833_write_cmos_sensor_8(0x3DC8, 0xC0);
    AR0833_write_cmos_sensor_8(0x3DC9, 0x88);
    AR0833_write_cmos_sensor_8(0x3DCA, 0x44);
    AR0833_write_cmos_sensor_8(0x3DCB, 0x9C);
    AR0833_write_cmos_sensor_8(0x3DCC, 0x44);
    AR0833_write_cmos_sensor_8(0x3DCD, 0x88);
    AR0833_write_cmos_sensor_8(0x3DCE, 0x06);
    AR0833_write_cmos_sensor_8(0x3DCF, 0xC8);
    AR0833_write_cmos_sensor_8(0x3DD0, 0x85);
    AR0833_write_cmos_sensor_8(0x3DD1, 0x41);
    AR0833_write_cmos_sensor_8(0x3DD2, 0x6A);
    AR0833_write_cmos_sensor_8(0x3DD3, 0x83);
    AR0833_write_cmos_sensor_8(0x3DD4, 0x6B);
    AR0833_write_cmos_sensor_8(0x3DD5, 0xA0);
    AR0833_write_cmos_sensor_8(0x3DD6, 0x42);
    AR0833_write_cmos_sensor_8(0x3DD7, 0x82);
    AR0833_write_cmos_sensor_8(0x3DD8, 0x40);
    AR0833_write_cmos_sensor_8(0x3DD9, 0x6C);
    AR0833_write_cmos_sensor_8(0x3DDA, 0x3A);
    AR0833_write_cmos_sensor_8(0x3DDB, 0xA8);
    AR0833_write_cmos_sensor_8(0x3DDC, 0x80);
    AR0833_write_cmos_sensor_8(0x3DDD, 0x28);
    AR0833_write_cmos_sensor_8(0x3DDE, 0x30);
    AR0833_write_cmos_sensor_8(0x3DDF, 0x70);
    AR0833_write_cmos_sensor_8(0x3DE0, 0x6F);
    AR0833_write_cmos_sensor_8(0x3DE1, 0x40);
    AR0833_write_cmos_sensor_8(0x3DE2, 0x14);
    AR0833_write_cmos_sensor_8(0x3DE3, 0x0E);
    AR0833_write_cmos_sensor_8(0x3DE4, 0x23);
    AR0833_write_cmos_sensor_8(0x3DE5, 0xC2);
    AR0833_write_cmos_sensor_8(0x3DE6, 0x41);
    AR0833_write_cmos_sensor_8(0x3DE7, 0x82);
    AR0833_write_cmos_sensor_8(0x3DE8, 0x42);
    AR0833_write_cmos_sensor_8(0x3DE9, 0x00);
    AR0833_write_cmos_sensor_8(0x3DEA, 0xC0);
    AR0833_write_cmos_sensor_8(0x3DEB, 0x5D);
    AR0833_write_cmos_sensor_8(0x3DEC, 0x80);
    AR0833_write_cmos_sensor_8(0x3DED, 0x5A);
    AR0833_write_cmos_sensor_8(0x3DEE, 0x80);
    AR0833_write_cmos_sensor_8(0x3DEF, 0x57);
    AR0833_write_cmos_sensor_8(0x3DF0, 0x84);
    AR0833_write_cmos_sensor_8(0x3DF1, 0x64);
    AR0833_write_cmos_sensor_8(0x3DF2, 0x80);
    AR0833_write_cmos_sensor_8(0x3DF3, 0x55);
    AR0833_write_cmos_sensor_8(0x3DF4, 0x86);
    AR0833_write_cmos_sensor_8(0x3DF5, 0x64);
    AR0833_write_cmos_sensor_8(0x3DF6, 0x80);
    AR0833_write_cmos_sensor_8(0x3DF7, 0x65);
    AR0833_write_cmos_sensor_8(0x3DF8, 0x88);
    AR0833_write_cmos_sensor_8(0x3DF9, 0x65);
    AR0833_write_cmos_sensor_8(0x3DFA, 0x82);
    AR0833_write_cmos_sensor_8(0x3DFB, 0x54);
    AR0833_write_cmos_sensor_8(0x3DFC, 0x80);
    AR0833_write_cmos_sensor_8(0x3DFD, 0x58);
    AR0833_write_cmos_sensor_8(0x3DFE, 0x80);
    AR0833_write_cmos_sensor_8(0x3DFF, 0x00);
    AR0833_write_cmos_sensor_8(0x3E00, 0xC0);
    AR0833_write_cmos_sensor_8(0x3E01, 0x86);
    AR0833_write_cmos_sensor_8(0x3E02, 0x42);
    AR0833_write_cmos_sensor_8(0x3E03, 0x82);
    AR0833_write_cmos_sensor_8(0x3E04, 0x10);
    AR0833_write_cmos_sensor_8(0x3E05, 0x30);
    AR0833_write_cmos_sensor_8(0x3E06, 0x9C);
    AR0833_write_cmos_sensor_8(0x3E07, 0x5C);
    AR0833_write_cmos_sensor_8(0x3E08, 0x80);
    AR0833_write_cmos_sensor_8(0x3E09, 0x6E);
    AR0833_write_cmos_sensor_8(0x3E0A, 0x86);
    AR0833_write_cmos_sensor_8(0x3E0B, 0x5B);
    AR0833_write_cmos_sensor_8(0x3E0C, 0x80);
    AR0833_write_cmos_sensor_8(0x3E0D, 0x63);
    AR0833_write_cmos_sensor_8(0x3E0E, 0x9E);
    AR0833_write_cmos_sensor_8(0x3E0F, 0x59);
    AR0833_write_cmos_sensor_8(0x3E10, 0x8C);
    AR0833_write_cmos_sensor_8(0x3E11, 0x5E);
    AR0833_write_cmos_sensor_8(0x3E12, 0x8A);
    AR0833_write_cmos_sensor_8(0x3E13, 0x6C);
    AR0833_write_cmos_sensor_8(0x3E14, 0x80);
    AR0833_write_cmos_sensor_8(0x3E15, 0x6D);
    AR0833_write_cmos_sensor_8(0x3E16, 0x81);
    AR0833_write_cmos_sensor_8(0x3E17, 0x5F);
    AR0833_write_cmos_sensor_8(0x3E18, 0x60);
    AR0833_write_cmos_sensor_8(0x3E19, 0x61);
    AR0833_write_cmos_sensor_8(0x3E1A, 0x88);
    AR0833_write_cmos_sensor_8(0x3E1B, 0x10);
    AR0833_write_cmos_sensor_8(0x3E1C, 0x30);
    AR0833_write_cmos_sensor_8(0x3E1D, 0x66);
    AR0833_write_cmos_sensor_8(0x3E1E, 0x83);
    AR0833_write_cmos_sensor_8(0x3E1F, 0x6E);
    AR0833_write_cmos_sensor_8(0x3E20, 0x80);
    AR0833_write_cmos_sensor_8(0x3E21, 0x64);
    AR0833_write_cmos_sensor_8(0x3E22, 0x87);
    AR0833_write_cmos_sensor_8(0x3E23, 0x64);
    AR0833_write_cmos_sensor_8(0x3E24, 0x30);
    AR0833_write_cmos_sensor_8(0x3E25, 0x50);
    AR0833_write_cmos_sensor_8(0x3E26, 0xD3);
    AR0833_write_cmos_sensor_8(0x3E27, 0x6A);
    AR0833_write_cmos_sensor_8(0x3E28, 0x6B);
    AR0833_write_cmos_sensor_8(0x3E29, 0xAD);
    AR0833_write_cmos_sensor_8(0x3E2A, 0x30);
    AR0833_write_cmos_sensor_8(0x3E2B, 0x94);
    AR0833_write_cmos_sensor_8(0x3E2C, 0x67);
    AR0833_write_cmos_sensor_8(0x3E2D, 0x84);
    AR0833_write_cmos_sensor_8(0x3E2E, 0x65);
    AR0833_write_cmos_sensor_8(0x3E2F, 0x82);
    AR0833_write_cmos_sensor_8(0x3E30, 0x4D);
    AR0833_write_cmos_sensor_8(0x3E31, 0x83);
    AR0833_write_cmos_sensor_8(0x3E32, 0x65);
    AR0833_write_cmos_sensor_8(0x3E33, 0x30);
    AR0833_write_cmos_sensor_8(0x3E34, 0x50);
    AR0833_write_cmos_sensor_8(0x3E35, 0xA7);
    AR0833_write_cmos_sensor_8(0x3E36, 0x43);
    AR0833_write_cmos_sensor_8(0x3E37, 0x06);
    AR0833_write_cmos_sensor_8(0x3E38, 0x00);
    AR0833_write_cmos_sensor_8(0x3E39, 0x8D);
    AR0833_write_cmos_sensor_8(0x3E3A, 0x45);
    AR0833_write_cmos_sensor_8(0x3E3B, 0x9A);
    AR0833_write_cmos_sensor_8(0x3E3C, 0x6A);
    AR0833_write_cmos_sensor_8(0x3E3D, 0x6B);
    AR0833_write_cmos_sensor_8(0x3E3E, 0x45);
    AR0833_write_cmos_sensor_8(0x3E3F, 0x85);
    AR0833_write_cmos_sensor_8(0x3E40, 0x06);
    AR0833_write_cmos_sensor_8(0x3E41, 0x00);
    AR0833_write_cmos_sensor_8(0x3E42, 0x81);
    AR0833_write_cmos_sensor_8(0x3E43, 0x43);
    AR0833_write_cmos_sensor_8(0x3E44, 0x8A);
    AR0833_write_cmos_sensor_8(0x3E45, 0x6F);
    AR0833_write_cmos_sensor_8(0x3E46, 0x96);
    AR0833_write_cmos_sensor_8(0x3E47, 0x30);
    AR0833_write_cmos_sensor_8(0x3E48, 0x90);
    AR0833_write_cmos_sensor_8(0x3E49, 0x67);
    AR0833_write_cmos_sensor_8(0x3E4A, 0x64);
    AR0833_write_cmos_sensor_8(0x3E4B, 0x88);
    AR0833_write_cmos_sensor_8(0x3E4C, 0x64);
    AR0833_write_cmos_sensor_8(0x3E4D, 0x80);
    AR0833_write_cmos_sensor_8(0x3E4E, 0x65);
    AR0833_write_cmos_sensor_8(0x3E4F, 0x82);
    AR0833_write_cmos_sensor_8(0x3E50, 0x10);
    AR0833_write_cmos_sensor_8(0x3E51, 0xC0);
    AR0833_write_cmos_sensor_8(0x3E52, 0x84);
    AR0833_write_cmos_sensor_8(0x3E53, 0x65);
    AR0833_write_cmos_sensor_8(0x3E54, 0xEF);
    AR0833_write_cmos_sensor_8(0x3E55, 0x10);
    AR0833_write_cmos_sensor_8(0x3E56, 0xC0);
    AR0833_write_cmos_sensor_8(0x3E57, 0x66);
    AR0833_write_cmos_sensor_8(0x3E58, 0x85);
    AR0833_write_cmos_sensor_8(0x3E59, 0x64);
    AR0833_write_cmos_sensor_8(0x3E5A, 0x81);
    AR0833_write_cmos_sensor_8(0x3E5B, 0x17);
    AR0833_write_cmos_sensor_8(0x3E5C, 0x00);
    AR0833_write_cmos_sensor_8(0x3E5D, 0x80);
    AR0833_write_cmos_sensor_8(0x3E5E, 0x20);
    AR0833_write_cmos_sensor_8(0x3E5F, 0x0D);
    AR0833_write_cmos_sensor_8(0x3E60, 0x80);
    AR0833_write_cmos_sensor_8(0x3E61, 0x18);
    AR0833_write_cmos_sensor_8(0x3E62, 0x0C);
    AR0833_write_cmos_sensor_8(0x3E63, 0x80);
    AR0833_write_cmos_sensor_8(0x3E64, 0x64);
    AR0833_write_cmos_sensor_8(0x3E65, 0x30);
    AR0833_write_cmos_sensor_8(0x3E66, 0x60);
    AR0833_write_cmos_sensor_8(0x3E67, 0x41);
    AR0833_write_cmos_sensor_8(0x3E68, 0x82);
    AR0833_write_cmos_sensor_8(0x3E69, 0x42);
    AR0833_write_cmos_sensor_8(0x3E6A, 0xB2);
    AR0833_write_cmos_sensor_8(0x3E6B, 0x42);
    AR0833_write_cmos_sensor_8(0x3E6C, 0x80);
    AR0833_write_cmos_sensor_8(0x3E6D, 0x40);
    AR0833_write_cmos_sensor_8(0x3E6E, 0x82);
    AR0833_write_cmos_sensor_8(0x3E6F, 0x40);
    AR0833_write_cmos_sensor_8(0x3E70, 0x4C);
    AR0833_write_cmos_sensor_8(0x3E71, 0x45);
    AR0833_write_cmos_sensor_8(0x3E72, 0x92);
    AR0833_write_cmos_sensor_8(0x3E73, 0x6A);
    AR0833_write_cmos_sensor_8(0x3E74, 0x6B);
    AR0833_write_cmos_sensor_8(0x3E75, 0x9B);
    AR0833_write_cmos_sensor_8(0x3E76, 0x45);
    AR0833_write_cmos_sensor_8(0x3E77, 0x81);
    AR0833_write_cmos_sensor_8(0x3E78, 0x4C);
    AR0833_write_cmos_sensor_8(0x3E79, 0x40);
    AR0833_write_cmos_sensor_8(0x3E7A, 0x8C);
    AR0833_write_cmos_sensor_8(0x3E7B, 0x30);
    AR0833_write_cmos_sensor_8(0x3E7C, 0xA4);
    AR0833_write_cmos_sensor_8(0x3E7D, 0x67);
    AR0833_write_cmos_sensor_8(0x3E7E, 0x85);
    AR0833_write_cmos_sensor_8(0x3E7F, 0x65);
    AR0833_write_cmos_sensor_8(0x3E80, 0x87);
    AR0833_write_cmos_sensor_8(0x3E81, 0x65);
    AR0833_write_cmos_sensor_8(0x3E82, 0x30);
    AR0833_write_cmos_sensor_8(0x3E83, 0x60);
    AR0833_write_cmos_sensor_8(0x3E84, 0xD3);
    AR0833_write_cmos_sensor_8(0x3E85, 0x6A);
    AR0833_write_cmos_sensor_8(0x3E86, 0x6B);
    AR0833_write_cmos_sensor_8(0x3E87, 0xAC);
    AR0833_write_cmos_sensor_8(0x3E88, 0x6C);
    AR0833_write_cmos_sensor_8(0x3E89, 0x32);
    AR0833_write_cmos_sensor_8(0x3E8A, 0xA8);
    AR0833_write_cmos_sensor_8(0x3E8B, 0x80);
    AR0833_write_cmos_sensor_8(0x3E8C, 0x28);
    AR0833_write_cmos_sensor_8(0x3E8D, 0x30);
    AR0833_write_cmos_sensor_8(0x3E8E, 0x70);
    AR0833_write_cmos_sensor_8(0x3E8F, 0x00);
    AR0833_write_cmos_sensor_8(0x3E90, 0x80);
    AR0833_write_cmos_sensor_8(0x3E91, 0x40);
    AR0833_write_cmos_sensor_8(0x3E92, 0x4C);
    AR0833_write_cmos_sensor_8(0x3E93, 0xBD);
    AR0833_write_cmos_sensor_8(0x3E94, 0x00);
    AR0833_write_cmos_sensor_8(0x3E95, 0x0E);
    AR0833_write_cmos_sensor_8(0x3E96, 0xBE);
    AR0833_write_cmos_sensor_8(0x3E97, 0x44);
    AR0833_write_cmos_sensor_8(0x3E98, 0x88);
    AR0833_write_cmos_sensor_8(0x3E99, 0x44);
    AR0833_write_cmos_sensor_8(0x3E9A, 0xBC);
    AR0833_write_cmos_sensor_8(0x3E9B, 0x78);
    AR0833_write_cmos_sensor_8(0x3E9C, 0x09);
    AR0833_write_cmos_sensor_8(0x3E9D, 0x00);
    AR0833_write_cmos_sensor_8(0x3E9E, 0x89);
    AR0833_write_cmos_sensor_8(0x3E9F, 0x04);
    AR0833_write_cmos_sensor_8(0x3EA0, 0x80);
    AR0833_write_cmos_sensor_8(0x3EA1, 0x80);
    AR0833_write_cmos_sensor_8(0x3EA2, 0x02);
    AR0833_write_cmos_sensor_8(0x3EA3, 0x40);
    AR0833_write_cmos_sensor_8(0x3EA4, 0x86);
    AR0833_write_cmos_sensor_8(0x3EA5, 0x09);
    AR0833_write_cmos_sensor_8(0x3EA6, 0x00);
    AR0833_write_cmos_sensor_8(0x3EA7, 0x8E);
    AR0833_write_cmos_sensor_8(0x3EA8, 0x09);
    AR0833_write_cmos_sensor_8(0x3EA9, 0x00);
    AR0833_write_cmos_sensor_8(0x3EAA, 0x80);
    AR0833_write_cmos_sensor_8(0x3EAB, 0x02);
    AR0833_write_cmos_sensor_8(0x3EAC, 0x40);
    AR0833_write_cmos_sensor_8(0x3EAD, 0x80);
    AR0833_write_cmos_sensor_8(0x3EAE, 0x04);
    AR0833_write_cmos_sensor_8(0x3EAF, 0x80);
    AR0833_write_cmos_sensor_8(0x3EB0, 0x88);
    AR0833_write_cmos_sensor_8(0x3EB1, 0x7D);
    AR0833_write_cmos_sensor_8(0x3EB2, 0x9E);
    AR0833_write_cmos_sensor_8(0x3EB3, 0x86);
    AR0833_write_cmos_sensor_8(0x3EB4, 0x09);
    AR0833_write_cmos_sensor_8(0x3EB5, 0x00);
    AR0833_write_cmos_sensor_8(0x3EB6, 0x87);
    AR0833_write_cmos_sensor_8(0x3EB7, 0x7A);
    AR0833_write_cmos_sensor_8(0x3EB8, 0x00);
    AR0833_write_cmos_sensor_8(0x3EB9, 0x0E);
    AR0833_write_cmos_sensor_8(0x3EBA, 0xC3);
    AR0833_write_cmos_sensor_8(0x3EBB, 0x79);
    AR0833_write_cmos_sensor_8(0x3EBC, 0x4C);
    AR0833_write_cmos_sensor_8(0x3EBD, 0x40);
    AR0833_write_cmos_sensor_8(0x3EBE, 0xBF);
    AR0833_write_cmos_sensor_8(0x3EBF, 0x70);
    AR0833_write_cmos_sensor_8(0x3EC0, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC1, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC2, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC3, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC4, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC5, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC6, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC7, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC8, 0x00);
    AR0833_write_cmos_sensor_8(0x3EC9, 0x00);
    AR0833_write_cmos_sensor_8(0x3ECA, 0x00);
    AR0833_write_cmos_sensor_8(0x3ECB, 0x00);


    AR0833_write_cmos_sensor(0x301A, 0x0018); 	// RESET_REGISTER
    AR0833_write_cmos_sensor(0x3EDE, 0x6664); 	// DAC_LD_18_19
    AR0833_write_cmos_sensor(0x3EDE, 0x6664); 	// DAC_LD_18_19
    AR0833_write_cmos_sensor(0x3EDE, 0x6664); 	// DAC_LD_18_19
    AR0833_write_cmos_sensor(0x3EDE, 0x6664); 	// DAC_LD_18_19
    AR0833_write_cmos_sensor(0x3EE0, 0x26D5); 	// DAC_LD_20_21
    AR0833_write_cmos_sensor(0x3EE0, 0x26D5); 	// DAC_LD_20_21
    AR0833_write_cmos_sensor(0x301A, 0x001C); 	// RESET_REGISTER
    AR0833_write_cmos_sensor(0x0300, 0x0005); 	// VT_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x0302, 0x0001); 	// VT_SYS_CLK_DIV
    AR0833_write_cmos_sensor(0x0304, 0x0004); 	// PRE_PLL_CLK_DIV
    AR0833_write_cmos_sensor(0x0306, 0x007A); 	// PLL_MULTIPLIER
    AR0833_write_cmos_sensor(0x0308, 0x000A); 	// OP_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x030A, 0x0001); 	// OP_SYS_CLK_DIV
    AR0833_write_cmos_sensor(0x3064, 0x7800); 	// SMIA_TEST

    // apply .ini from arrow, richard
    AR0833_write_cmos_sensor(0x0300, 0x0005); 	// VT_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x0302, 0x0001); 	// VT_SYS_CLK_DIV
    AR0833_write_cmos_sensor(0x0304, 0x0004); 	// PRE_PLL_CLK_DIV
    AR0833_write_cmos_sensor(0x0306, 0x0046); 	// PLL_MULTIPLIER
    AR0833_write_cmos_sensor(0x0308, 0x000A); 	// OP_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x030A, 0x0001); 	// OP_SYS_CLK_DIV
    //VCO =  XTCLK * pll_multiplier(R0x306) / (pre_pll_clk_div(R0x0304)) = 24MHz * 0x46 / 4 = 24 * 70 / 4 = 420MHz
    // vt_sys_clk =  VCO / (vt_sys_clk_div(R0x302) x 2) = 420 / (1 x 2) = 210Mhz

#if 1
    //  reduce clock, richard
    AR0833_write_cmos_sensor(0x0300, 0x0005); 	// VT_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x0302, 0x0001); 	// VT_SYS_CLK_DIV
    AR0833_write_cmos_sensor(0x0304, 0x0008); 	// PRE_PLL_CLK_DIV
    AR0833_write_cmos_sensor(0x0306, 0x0046); 	// PLL_MULTIPLIER
    AR0833_write_cmos_sensor(0x0308, 0x000A); 	// OP_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x030A, 0x0001); 	// OP_SYS_CLK_DIV
    //VCO = 210MHz
    // vt_sys_clk = 105Mhz
#endif

#if 0
    //  reduce clock, richard
    AR0833_write_cmos_sensor(0x0300, 0x0005); 	// VT_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x0302, 0x0001); 	// VT_SYS_CLK_DIV
    AR0833_write_cmos_sensor(0x0304, 0x0010); 	// PRE_PLL_CLK_DIV
    AR0833_write_cmos_sensor(0x0306, 0x0046); 	// PLL_MULTIPLIER
    AR0833_write_cmos_sensor(0x0308, 0x000A); 	// OP_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x030A, 0x0001); 	// OP_SYS_CLK_DIV
    //VCO = 105MHz
    // vt_sys_clk = 50.25Mhz
#endif

#if 0
    //  reduce clock, richard
    AR0833_write_cmos_sensor(0x0300, 0x0005); 	// VT_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x0302, 0x0001); 	// VT_SYS_CLK_DIV
    AR0833_write_cmos_sensor(0x0304, 0x0020); 	// PRE_PLL_CLK_DIV
    AR0833_write_cmos_sensor(0x0306, 0x0046); 	// PLL_MULTIPLIER
    AR0833_write_cmos_sensor(0x0308, 0x000A); 	// OP_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x030A, 0x0001); 	// OP_SYS_CLK_DIV
    //VCO = 105MHz
    // vt_sys_clk = 25.125Mhz
#endif

    // richard add: raw8
    AR0833_write_cmos_sensor(0x0112, 0x0808);        // CCP_DATA_FORMAT

#if 0
    //  reduce clock, richard
    AR0833_write_cmos_sensor(0x0300, 0x0005); 	// VT_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x0302, 0x0001); 	// VT_SYS_CLK_DIV
    AR0833_write_cmos_sensor(0x0304, 0x0005); 	// PRE_PLL_CLK_DIV
    AR0833_write_cmos_sensor(0x0306, 0x0046); 	// PLL_MULTIPLIER
    AR0833_write_cmos_sensor(0x0308, 0x000A); 	// OP_PIX_CLK_DIV
    AR0833_write_cmos_sensor(0x030A, 0x0001); 	// OP_SYS_CLK_DIV
    //VCO = 336MHz
    // vt_sys_clk = 168Mhz
#endif

    Sleep(1);
    AR0833_write_cmos_sensor(0x31B0, 0x0060); 	// FRAME_PREAMBLE
    AR0833_write_cmos_sensor(0x31B2, 0x0042); 	// LINE_PREAMBLE
    AR0833_write_cmos_sensor(0x31B4, 0x1C36); 	// MIPI_TIMING_0
    AR0833_write_cmos_sensor(0x31B6, 0x5218); 	// MIPI_TIMING_1
    AR0833_write_cmos_sensor(0x31B8, 0x404A); 	// MIPI_TIMING_2
    AR0833_write_cmos_sensor(0x31BA, 0x028A); 	// MIPI_TIMING_3
    AR0833_write_cmos_sensor(0x31BC, 0x0008); 	// MIPI_TIMING_4
    Sleep(1);

    AR0833_write_cmos_sensor(0x0342, 0x1000); 	// LINE_LENGTH_PCK
    AR0833_write_cmos_sensor(0x0340, 0x0556); 	// FRAME_LENGTH_LINES
    AR0833_write_cmos_sensor(0x0202, 0x0500); 	// COARSE_INTEGRATION_TIME

    AR0833_write_cmos_sensor(0x0342, 0x0ECE); 	// LINE_LENGTH_PCK
    AR0833_write_cmos_sensor(0x0340, 0x0A0F); 	// FRAME_LENGTH_LINES
    AR0833_write_cmos_sensor(0x0202, 0x0A0F); 	// COARSE_INTEGRATION_TIME

#if 0
    AR0833_write_cmos_sensor(0x0344, 0x0008); 	// X_ADDR_START
    AR0833_write_cmos_sensor(0x0348, 0x0CC7); 	// X_ADDR_END
    AR0833_write_cmos_sensor(0x0346, 0x0008); 	// Y_ADDR_START
    AR0833_write_cmos_sensor(0x034A, 0x0997); 	// Y_ADDR_END
    AR0833_write_cmos_sensor(0x034C, 0x0650); 	// X_OUTPUT_SIZE
    AR0833_write_cmos_sensor(0x034E, 0x04BC); 	// Y_OUTPUT_SIZE

    // richard add: 1280x960 (640x480 x2)
    AR0833_write_cmos_sensor(0x0344, 0x0008); 	// X_ADDR_START
    AR0833_write_cmos_sensor(0x0348, 0x0A08); 	// X_ADDR_END
    AR0833_write_cmos_sensor(0x0346, 0x0008); 	// Y_ADDR_START
    AR0833_write_cmos_sensor(0x034A, 0x0788); 	// Y_ADDR_END
    AR0833_write_cmos_sensor(0x034C, 0x0500); 	// X_OUTPUT_SIZE
    AR0833_write_cmos_sensor(0x034E, 0x03C0); 	// Y_OUTPUT_SIZE


    // richard add: 640x480
    AR0833_write_cmos_sensor(0x0344, 0x0008+(3264-640*2)/2); 	// X_ADDR_START
    AR0833_write_cmos_sensor(0x0348, 0x0508+(3264-640*2)/2); 	// X_ADDR_END
    AR0833_write_cmos_sensor(0x0346, 0x0008+(2448-480*2)/2); 	// Y_ADDR_START
//    AR0833_write_cmos_sensor(0x034A, 0x03c8); 	// Y_ADDR_END
    AR0833_write_cmos_sensor(0x034A, 0x03c9+(2448-480*2)/2); 	// Y_ADDR_END
    AR0833_write_cmos_sensor(0x034C, 0x0280); 	// X_OUTPUT_SIZE
    AR0833_write_cmos_sensor(0x034E, 0x01E0); 	// Y_OUTPUT_SIZE
#endif

#if 0

    // richard add: 1024x768
    AR0833_write_cmos_sensor(0x0344, 0x0008+(3264-1024*2)/2); 	// X_ADDR_START
    AR0833_write_cmos_sensor(0x0348, 0x0808+(3264-1024*2)/2); 	// X_ADDR_END

    AR0833_write_cmos_sensor(0x0346, 0x0008+(2448-768*2)/2); 	// Y_ADDR_START
//    AR0833_write_cmos_sensor(0x034A, 0x03c8); 	// Y_ADDR_END
    AR0833_write_cmos_sensor(0x034A, 0x0609+(2448-768*2)/2); 	// Y_ADDR_END
#endif

///////
    if (bScale){
    	AR0833_write_cmos_sensor(0x0344, 0x0008+(3264-1024*2)/2); 	// X_ADDR_START
    	AR0833_write_cmos_sensor(0x0348, 8+1024*2+1+(3264-1024*2)/2); 	// X_ADDR_END

    	AR0833_write_cmos_sensor(0x0346, 0x0008+(2448-768*2)/2); 	// Y_ADDR_START
    	AR0833_write_cmos_sensor(0x034A, 8+768*2+1+(2448-768*2)/2); 	// Y_ADDR_END

    }else{
    	AR0833_write_cmos_sensor(0x0344, 0x0008+(3264-1024)/2); 	// X_ADDR_START
    	AR0833_write_cmos_sensor(0x0348, 8+1024+1+(3264-1024)/2); 	// X_ADDR_END

    	AR0833_write_cmos_sensor(0x0346, 0x0008+(2448-768)/2); 	// Y_ADDR_START
    	AR0833_write_cmos_sensor(0x034A, 8+768+1+(2448-768)/2); 	// Y_ADDR_END
	}


    AR0833_write_cmos_sensor(0x034C, 0x0400); 	// X_OUTPUT_SIZE
    AR0833_write_cmos_sensor(0x034E, 0x0300); 	// Y_OUTPUT_SIZE


    if (bTestMode){

    	AR0833_write_cmos_sensor(0x0602, 0);  // red
    	AR0833_write_cmos_sensor(0x0604, 0);  // greenR
    	AR0833_write_cmos_sensor(0x0606, 1023);  // blue
    	AR0833_write_cmos_sensor(0x0608, 0);  // greenB
    	AR0833_write_cmos_sensor(0x0600, 0x0000); 	// 0: Normal operation, Generate output data from pixel array
    	//AR0833_write_cmos_sensor(0x0600, 0x0001); 	// 1: Solid color test pattern.
    	AR0833_write_cmos_sensor(0x0600, 0x0002); 	// 2: 100% color bar test pattern
    	//AR0833_write_cmos_sensor(0x0600, 0x0003); 	// 3: Fade to gray color bar test pattern
    }




    // gain control (white balance)
#if 0
    AR0833_write_cmos_sensor(0x3056, 0x1000); 	// green1_gain
    AR0833_write_cmos_sensor(0x3058, 0x1800); 	// blue_gain
    AR0833_write_cmos_sensor(0x305a, 0x1400); 	// red_gain
    AR0833_write_cmos_sensor(0x305c, 0x1000); 	// green2_gain
#else
 //   AR0833_write_cmos_sensor(0x0206, 0x0002); 	// analogue_gain_code_greenr (default 2)
  //  AR0833_write_cmos_sensor(0x0208, 0x0003); 	// analogue_gain_code_red (default 2)
  //  AR0833_write_cmos_sensor(0x020A, 0x0004); 	// analogue_gain_code_blue (default 2)
  //  AR0833_write_cmos_sensor(0x020C, 0x0002); 	// analogue_gain_code_greenb (default 2)

	#if 0
    AR0833_write_cmos_sensor(0x020E, 0x0180); 	// digital_gain_greenr (default 0x100)
    AR0833_write_cmos_sensor(0x0210, 0x0220); 	// digital_gain_red (default 0x100)
    AR0833_write_cmos_sensor(0x0212, 0x0200); 	// digital_gain_blue (default 0x100)
    AR0833_write_cmos_sensor(0x0214, 0x0180); 	// digital_gain_greenb (default 0x100)
	#else
    AR0833_write_cmos_sensor(0x020E, 0x0100); 	// digital_gain_greenr (default 0x100)
    AR0833_write_cmos_sensor(0x0210, 0x0180); 	// digital_gain_red (default 0x100)
    AR0833_write_cmos_sensor(0x0212, 0x0140); 	// digital_gain_blue (default 0x100)
    AR0833_write_cmos_sensor(0x0214, 0x0100); 	// digital_gain_greenb (default 0x100)
	#endif

    //AR0833_write_cmos_sensor(0x305E, 0x2000); 	// global_gain (default 0x1000)


#endif


    AR0833_write_cmos_sensor(0x3040, 0x4041 ); 	// READ_MODE

    // richard add, vertical mirrow only
    AR0833_write_cmos_sensor(0x3040, 0x8041 ); 	// READ_MODE

 //   AR0833_write_cmos_sensor(0x0400, 0x0002); 	// SCALING_MODE, 2: Enable horizontal and vertical scaling

    if (bScale)
        AR0833_write_cmos_sensor(0x0400, 0x0002); 	// SCALING_MODE, 2: Enable horizontal and vertical scaling
    else
    	AR0833_write_cmos_sensor(0x0400, 0x0000); 	// SCALING_MODE, 0: disable scaling

    AR0833_write_cmos_sensor(0x0402, 0x0000); 	// SPATIAL_SAMPLING
    AR0833_write_cmos_sensor(0x0404, 0x0020); 	// SCALE_M (default 0x0010)
    AR0833_write_cmos_sensor(0x0408, 0x0208); 	// SECOND_RESIDUAL
    AR0833_write_cmos_sensor(0x040A, 0x00C7); 	// SECOND_CROP
    AR0833_write_cmos_sensor(0x306E, 0x9090); 	// DATA_PATH_SELECT
    AR0833_write_cmos_sensor(0x301A, 0x001C); 	// RESET_REGISTER (Lock_reg & stream)




}

