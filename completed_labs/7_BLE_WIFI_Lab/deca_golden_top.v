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

`define ENABLE_DDR3
//`define ENABLE_AUDIO
//`define ENABLE_CAP_TOUCH
//`define ENABLE_SFLASH
`define ENABLE_P8_P9_EXPANSION
//`define ENABLE_HDMI
//`define ENABLE_MIPI
//`define ENABLE_ENET
//`define ENABLE_SD
//`define ENABLE_USB


module DECA_golden_top(

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
      inout             DDR3_CK_n,
      inout             DDR3_CK_p,
      input              DDR3_CLK_50,
      output             DDR3_CS_n,
      output      [0:0]  DDR3_DM,
      inout       [7:0]  DDR3_DQ,
      inout       [0:0]  DDR3_DQS_n,
      inout       [0:0]  DDR3_DQS_p,
      output             DDR3_ODT,
      output             DDR3_RAS_n,
      output             DDR3_RESET_n,
      output             DDR3_WE_n,
`endif /*ENABLE_DDR3*/

`ifdef ENABLE_SFLASH
      ///////// FLASH /////////
      inout       [3:0]  FLASH_DATA,
      output             FLASH_DCLK,
      output             FLASH_NCSO,
      output             FLASH_RESET_n,
`endif /* ENABLE_SFLASH */

	//////////// G-Sensor //////////
	output		          		G_SENSOR_CS_n,
	input 		          		G_SENSOR_INT1,
	input 		          		G_SENSOR_INT2,
	inout 		          		G_SENSOR_SCLK,
	inout 		          		G_SENSOR_SDI,
	inout 		          		G_SENSOR_SDO,

`ifdef ENABLE_P8_P9_EXPANSION
      ///////// GPIO0 /////////
      //inout       [43:0] GPIO0_D,

		output 				 WIFI_SPI_CS_N,
		output 			    WIFI_SPI_SCLK,
		output 				 WIFI_SPI_MOSI,
		input 				 WIFI_SPI_MISO,
		input 				 WIFI_UART_RXD,
		output 				 WIFI_UART_TXD,
		input  				 WIFI_UART_CTS,
		output 				 WIFI_UART_RTS,
		input 				 WIFI_IRQ,
		output  				 WIFI_HIB_N,
		output 				 WIFI_ANT,

		input 			    BLE_SPI_CS_N,
		input 				 BLE_SPI_SCLK,
		input 			    BLE_SPI_MOSI,
		output 				 BLE_SPI_MISO,
		output 				 BLE_I2C_SCL,
		inout 				 BLE_I2C_SDA,
		output 				 BLE_ANT,

		input 				 BLE_DIO6,
		input 				 BLE_DIO7,
		input 				 BLE_DIO8,
		input 				 BLE_DIO9,
		input 				 BLE_DIO10,
		input 				 BLE_DIO11,
		input 	     		 BLE_DIO12,
		input 				 BLE_DIO13,
		input 				 BLE_DIO14,
		input 				 BLE_DIO15,

		output 				 EEPROM_I2C_SCL,
		inout 				 EEPROM_I2C_SDA,

`endif /* ENABLE_P8_P9_EXPANSION */

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

      ///////// BBB /////////
      input              BBB_PWR_BUT,

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
      output              BBB_SYS_RESET_n
);


//=======================================================
//  REG/WIRE declarations
//=======================================================


wire reset_n;
wire adc_clk_40m;
wire clk_50m;
wire adc_pll_locked;
wire [1:0] gsensor;
wire [1:0] cc3100_ctrl_pio;
wire [9:0] cc2650_spare_pio;
wire sysrst_n;

wire ddr3_local_init_done/*synthesis keep*/;
wire ddr3_local_cal_success/*synthesis keep*/;
wire ddr3_local_cal_fail/*synthesis keep*/;

wire [7:0] DECA_REV;



//=======================================================
//  Structural coding
//=======================================================

// Assignments
assign BBB_SYS_RESET_n = sysrst_n;
assign reset_n = KEY[0];
assign GSENSOR_ST = gsensor[0];
assign GSENSOR_PD = gsensor[1];

//=======================================================
// Expansion Header Assignments
//=======================================================


assign  WIFI_HIB_N = cc3100_ctrl_pio[0];
assign  WIFI_ANT = cc3100_ctrl_pio[1];

assign cc2650_spare_pio[0] = BLE_DIO6;
assign cc2650_spare_pio[1] = BLE_DIO7;
assign cc2650_spare_pio[2] = BLE_DIO8;
assign cc2650_spare_pio[3] = BLE_DIO9;
assign cc2650_spare_pio[4] = BLE_DIO10;
assign cc2650_spare_pio[5] = BLE_DIO11;
assign cc2650_spare_pio[6] = BLE_DIO12;
assign cc2650_spare_pio[7] = BLE_DIO13;
assign cc2650_spare_pio[8] = BLE_DIO14;
assign cc2650_spare_pio[9] = 1'b0;



ADC_PLL	ADC_PLL_inst (
	.areset ( !reset_n ),
	.inclk0 ( ADC_CLK_10 ),
	.c0 ( adc_clk_40m ),
	.c1 ( clk_50m ),
	.locked ( adc_pll_locked )
	);

WHICH_DECA_REVISION deca_rev_inst (
	.DECA_REV (DECA_REV)
	);

		RF0002_BASE u0 (
		.adc_pll_clock_clk                           (adc_clk_40m),          // adc_pll_clock.clk
		.adc_pll_locked_export                       (adc_pll_locked),       // adc_pll_locked.export
		.blue_leds_export                            (LED[7:0]),             // blue_leds.export
		.cc2650_ctrl_pio_export                      (BLE_ANT),              // cc2640_ctrl_pio.export
		.cc2650_scl_export                           (BLE_I2C_SCL),          // cc2640_scl.export
		.cc2650_sda_export                           (BLE_I2C_SDA),          // cc2640_sda.export
		.cc2650_spare_pio_export                     (cc2650_spare_pio[9:0]),// cc2640_spare_pio.export
		.cc2650_spi_MISO                             (BLE_SPI_MISO),         // cc2640_spi.MISO
		.cc2650_spi_MOSI                             (BLE_SPI_MOSI),         // MOSI
		.cc2650_spi_SCLK                             (BLE_SPI_SCLK),         // SCLK
		.cc2650_spi_SS_n                             (BLE_SPI_CS_N),         // SS_n
		.cc2650_irq_pio_export                       (BLE_DIO15),
		.cc3100_ctrl_pio_export                      (cc3100_ctrl_pio[1:0]), // cc3100_ctrl_pio.export
		.cc3100_irq_pio_export                       (WIFI_IRQ),             // cc3100_irq_pio.export
		.cc3100_wifi_spi_MISO                        (WIFI_SPI_MISO),        // cc3100_wifi_spi.MISO
		.cc3100_wifi_spi_MOSI                        (WIFI_SPI_MOSI),        // .MOSI
		.cc3100_wifi_spi_SCLK                        (WIFI_SPI_SCLK),        // .SCLK
		.cc3100_wifi_spi_SS_n                        (WIFI_SPI_CS_N),        // .SS_n
		.cc3100_wifi_uart_rxd                        (WIFI_UART_RXD),        // cc3100_wifi_uart.rxd
		.cc3100_wifi_uart_txd                        (WIFI_UART_TXD),        // .txd
		.cc3100_wifi_uart_cts_n                      (WIFI_UART_CTS),        // .cts_n
		.cc3100_wifi_uart_rts_n                      (WIFI_UART_RTS),        // .rts_n
		.clk_clk                                     (clk_50m),              // clk.clk
		.g_sensor_pio_export                         (gsensor[1:0]),         // g_sensor_pio.export
		.reset_reset_n                               (reset_n),              // reset.reset_n
		.rf002_eeprom_scl_export                     (EEPROM_I2C_SCL),       // rf002_eeprom_scl.export
		.rf002_eeprom_sda_export                     (EEPROM_I2C_SDA),       // rf002_eeprom_sda.export
		.rh_temp_drdy_export                         (RH_TEMP_DRDY_n),       // rh_temp_drdy.export
		.rh_temp_scl_export                          (RH_TEMP_I2C_SCL),      // rh_temp_scl.export
		.rh_temp_sda_export                          (RH_TEMP_I2C_SDA),      // rh_temp_sda.export
		.memory_mem_a                                (DDR3_A),               // memory.mem_a
		.memory_mem_ba                               (DDR3_BA),              // .mem_ba
		.memory_mem_ck                               (DDR3_CK_p),            // .mem_ck
		.memory_mem_ck_n                             (DDR3_CK_n),            // .mem_ck_n
		.memory_mem_cke                              (DDR3_CKE),             // .mem_cke
		.memory_mem_cs_n                             (DDR3_CS_n),            // .mem_cs_n
		.memory_mem_dm                               (DDR3_DM),              // .mem_dm
		.memory_mem_ras_n                            (DDR3_RAS_n),           // .mem_ras_n
		.memory_mem_cas_n                            (DDR3_CAS_n),           // .mem_cas_n
		.memory_mem_we_n                             (DDR3_WE_n),            // .mem_we_n
		.memory_mem_reset_n                          (DDR3_RESET_n),         // .mem_reset_n
		.memory_mem_dq                               (DDR3_DQ),              // .mem_dq
		.memory_mem_dqs                              (DDR3_DQS_p),           // .mem_dqs
		.memory_mem_dqs_n                            (DDR3_DQS_n),           // .mem_dqs_n
		.memory_mem_odt                              (DDR3_ODT),             // .mem_odt
		.mem_if_ddr3_emif_0_pll_ref_clk_clk          (DDR3_CLK_50),          // mem_if_ddr3_emif_0_pll_ref_clk.clk
		.mem_if_ddr3_emif_0_status_local_init_done   (ddr3_local_init_done), // mem_if_ddr3_emif_0_status.local_init_done
		.mem_if_ddr3_emif_0_status_local_cal_success (ddr3_local_cal_success), // .local_cal_success
		.mem_if_ddr3_emif_0_status_local_cal_fail    (ddr3_local_cal_fail),    // .local_cal_fail
		.ddr3_status_export                          ({ddr3_local_cal_success, ddr3_local_cal_fail, ddr3_local_init_done}), // ddr3_status.export
	   .sys_rst_out_n_export                        (sysrst_n),
	   .spi_gsensor_external_MISO                   (G_SENSOR_SDO),             // spi_gsensor_external.MISO
      .spi_gsensor_external_MOSI                   (G_SENSOR_SDI),             // .MOSI
      .spi_gsensor_external_SCLK                   (G_SENSOR_SCLK),            // .SCLK
      .spi_gsensor_external_SS_n                   (G_SENSOR_CS_n),             // .SS_n
		.deca_rev_pio_export									(DECA_REV)						// 8-bit input telling Nios which revision of DECA this is.
	);




endmodule
