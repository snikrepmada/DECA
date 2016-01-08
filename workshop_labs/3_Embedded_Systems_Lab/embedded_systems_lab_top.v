// ============================================================================
// Copyright (c) 2014 by Terasic Technologies Inc.
// ============================================================================
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
// ============================================================================
//
//  Terasic Technologies Inc
//  9F., No.176, Sec.2, Gongdao 5th Rd, East Dist, Hsinchu City, 30070. Taiwan
//
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// ============================================================================
//Date:  Fri Oct 24 14:09:29 2014
// ============================================================================


//`define ENABLE_AUDIO
`define ENABLE_CAP_TOUCH
//`define ENABLE_DDR3
`define ENABLE_SFLASH
//`define ENABLE_GPIO
//`define ENABLE_HDMI
//`define ENABLE_MIPI
//`define ENABLE_ENET
//`define ENABLE_SD
//`define ENABLE_USB


module embedded_systems_lab_top(

      ///////// ADC /////////
      input              ADC_CLK_10,

`ifdef ENABLE_AUDIO
      ///////// AUDIO /////////
      inout              AUDIO_BCLK,
      output             AUDIO_DIN_MFP1,
      input              AUDIO_DOUT_MFP2,
      inout              AUDIO_GPIO_MFP5,
      output             AUDIO_MCLK,
      input              AUDIO_MISO_MFP4,
      inout              AUDIO_RESET_n,
      output             AUDIO_SCLK_MFP3,
      output             AUDIO_SCL_SS_n,
      inout              AUDIO_SDA_MOSI,
      output             AUDIO_SPI_SELECT,
      inout              AUDIO_WCLK,
`endif /*ENABLE_AUDIO*/

`ifdef ENABLE_CAP_TOUCH
      ///////// CAP /////////
      inout              CAP_SENSE_I2C_SCL,
      inout              CAP_SENSE_I2C_SDA,
`endif /* ENABLE_CAP_TOUCH */

`ifdef ENABLE_DDR3
      ///////// DDR3 /////////
      output      [14:0] DDR3_A,
      output      [2:0]  DDR3_BA,
      output             DDR3_CAS_n,
      output             DDR3_CKE,
      inout              DDR3_CK_n,
      inout              DDR3_CK_p,
      input              DDR3_CLK_50,
      output             DDR3_CS_n,
      output      [1:0]  DDR3_DM,
      inout       [15:0] DDR3_DQ,
      inout       [1:0]  DDR3_DQS_n,
      inout       [1:0]  DDR3_DQS_p,
      output             DDR3_ODT,
      output             DDR3_RAS_n,
      output             DDR3_RESET_n,
      output             DDR3_WE_n,
`endif /*ENABLE_DDR3*/

`ifdef ENABLE_SFLASH
      ///////// FLASH /////////
		output				 FLASH_DATA_0,
		input					 FLASH_DATA_1,
		output				 FLASH_DATA_2,
		output				 FLASH_DATA_3,
      output             FLASH_DCLK,
      output             FLASH_NCSO,
      output             FLASH_RESET_n,
`endif /* ENABLE_SFLASH */

`ifdef ENABLE_GPIO
      ///////// GPIO0 /////////
      inout       [43:0] GPIO0_D,

      ///////// GPIO1 /////////
      inout       [22:0] GPIO1_D,
`endif /* GPIO */

      ///////// GSENSOR /////////
      output             GSENSOR_PD,
      output             GSENSOR_ST,

`ifdef ENABLE_HDMI
      ///////// HDMI /////////
      inout              HDMI_I2C_SCL,
      inout              HDMI_I2C_SDA,
      inout       [3:0]  HDMI_I2S,
      inout              HDMI_LRCLK,
      inout              HDMI_MCLK,
      inout              HDMI_SCLK,
      output             HDMI_TX_CLK,
      output      [23:0] HDMI_TX_D,
      output             HDMI_TX_DE,
      output             HDMI_TX_HS,
      input              HDMI_TX_INT,
      output             HDMI_TX_VS,
`endif /*HDMI*/

      ///////// KEY /////////
      input       [1:0]  KEY,

      ///////// LED /////////
      output      [7:0]  LED,

      ///////// LIGHT /////////
      output             LIGHT_I2C_SCL,
      inout              LIGHT_I2C_SDA,
      inout              LIGHT_INT,

      ///////// MAX10 /////////
      input              MAX10_CLK1_50,
      input              MAX10_CLK2_50,

 `ifdef ENABLE_MIPI
      ///////// MIPI /////////
      output             MIPI_CORE_EN,
      output             MIPI_I2C_SCL,
      inout              MIPI_I2C_SDA,
      input              MIPI_LP_MC_n,
      input              MIPI_LP_MC_p,
      input       [3:0]  MIPI_LP_MD_n,
      input       [3:0]  MIPI_LP_MD_p,
      output             MIPI_MCLK,
      input              MIPI_MC_p,
      input       [3:0]  MIPI_MD_p,
      output             MIPI_RESET_n,
      output             MIPI_WP,
`endif /* ENABLE_MIPI */

`ifdef ENABLE_ENET
      ///////// NET /////////
      input              NET_COL,
      input              NET_CRS,
      output             NET_MDC,
      inout              NET_MDIO,
      output             NET_PCF_EN,
      output             NET_RESET_n,
      input       [3:0]  NET_RXD,
      input              NET_RX_CLK,
      input              NET_RX_DV,
      input              NET_RX_ER,
      output      [3:0]  NET_TXD,
      input              NET_TX_CLK,
      output             NET_TX_EN,
`endif /* ENABLE_ENET */

      ///////// PMONITOR /////////
      input              PMONITOR_ALERT,
      output             PMONITOR_I2C_SCL,
      inout              PMONITOR_I2C_SDA,

      ///////// RH /////////
      input              RH_TEMP_DRDY_n,
      output             RH_TEMP_I2C_SCL,
      inout              RH_TEMP_I2C_SDA,

`ifdef ENABLE_SD
      ///////// SD /////////
      output             SD_CLK,
      inout              SD_CMD,
      output             SD_CMD_DIR,
      output             SD_D0_DIR,
      inout              SD_D123_DIR,
      inout       [3:0]  SD_DAT,
      input              SD_FB_CLK,
      output             SD_SEL,
`endif /* ENABLE_SD */

      ///////// SW /////////
      input       [1:0]  SW,


      ///////// TEMP /////////
      output             TEMP_CS_n,
      output             TEMP_SC,
      inout              TEMP_SIO,

`ifdef ENABLE_USB
      ///////// USB /////////
      input              USB_CLKIN,
      output             USB_CLKOUT,
      output             USB_CLKOUT_NOPLL,
      output             USB_CS,
      inout       [7:0]  USB_DATA,
      input              USB_DIR,
      input              USB_FAULT_n,
      input              USB_NXT,
      output             USB_RESET_n,
      output             USB_STP,
`endif /* ENABLE_USB */


      ///////// BBB /////////
      input              BBB_PWR_BUT,
      input              BBB_SYS_RESET_n

);


//=======================================================
//  REG/WIRE declarations
//=======================================================


	wire 		  reset_n;
	wire [1:0] pb_pio;
	wire 		  adc_pll_locked;
	wire 		  adc_pll_phasedone;
	wire       adc_pll_areset;
	wire 		  nios_pll_locked;
	wire 		  nios_pll_phasedone;
	wire       nios_pll_areset;

	wire [7:0] led_pio;
	wire [1:0]  cap_pb_pio;

	assign reset_n = KEY[0];

	assign LED[3:0] = ~led_pio;
	assign LED[5:4] = 2'b11;		// LED's are active low, this will turn off LED[5] and LED[4]
	assign LED[7:6] = ~cap_pb_pio;

deca_top u0 (
		.clk_clk                                (MAX10_CLK1_50),
		.cap_pb_pio_external_export      		 (cap_pb_pio),
		.capsense_i2c_scl_pad_io                (CAP_SENSE_I2C_SCL),
		.capsense_i2c_sda_pad_io                (CAP_SENSE_I2C_SDA),
		.led_pio_external_export                (led_pio),
		.lm71_external_cs_n                     (TEMP_CS_n),
		.lm71_external_sc                       (TEMP_SC),
		.lm71_external_sio                      (TEMP_SIO),
		.key_pb_pio_external_export             (KEY[1]),
		.reset_reset_n                          (reset_n),
		.rh_temp_drdyn_external_export			 (RH_TEMP_DRDY_n),
		.rh_temp_i2c_scl_pad_io        			 (RH_TEMP_I2C_SCL),
      .rh_temp_i2c_sda_pad_io  		 			 (RH_TEMP_I2C_SDA)
	);


endmodule
