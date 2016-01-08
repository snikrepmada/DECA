//`define ENABLE_DDR3

module gesture_lab_top(

      ///////// ADC /////////
      input              ADC_CLK_10,

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

      ///////// CAP /////////
      inout              CAP_SENSE_I2C_SCL,
      inout              CAP_SENSE_I2C_SDA,

`ifdef ENABLE_DDR3
      ///////// DDR3 /////////
      output      [14:0] DDR3_A,
      output      [2:0]  DDR3_BA,
      output             DDR3_CAS_n,
      output             DDR3_CKE,
      output             DDR3_CK_n,
      output             DDR3_CK_p,
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

      ///////// FLASH /////////
      inout       [3:0]  FLASH_DATA,
      output             FLASH_DCLK,
      output             FLASH_NCSO,
      output             FLASH_RESET_n,

      ///////// GPIO0 /////////
      inout       [43:0] GPIO0_D,

      ///////// GPIO1 /////////
      inout       [22:0] GPIO1_D,

      ///////// GSENSOR /////////
      output             GSENSOR_PD,
      output             GSENSOR_ST,

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

      ///////// SD /////////
      output             SD_CLK,
      inout              SD_CMD,
      output             SD_CMD_DIR,
      output             SD_D0_DIR,
      inout              SD_D123_DIR,
      inout       [3:0]  SD_DAT,
      input              SD_FB_CLK,
      output             SD_SEL,

      ///////// SW /////////
      input       [1:0]  SW,

      ///////// BBB /////////
      input              BBB_SYS_RESET_n,

      ///////// TEMP /////////
      output             TEMP_CS_n,
      output             TEMP_SC,
      inout              TEMP_SIO,

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
      output             USB_STP
);


//=======================================================
//  REG/WIRE declarations
//=======================================================

	wire		pll_qsys_locked;

	wire     	si1143_i2c_scl	=	LIGHT_I2C_SCL; 
	wire		si1143_i2c_sda	=	LIGHT_I2C_SDA;
	wire		si1143_i2c_int	=	LIGHT_INT;

	wire		reset_n			=	KEY[ 0 ];


//=======================================================
//  Structural coding
//=======================================================

	// add LEDs to monitor important signals
	// such as the I2C bus, the interrupts and PLL outputs
	//assign	LED[ 0 ]	=	SIGNAL_NAME;
	//assign	LED[ 1 ]	=	SIGNAL_NAME;
	//assign	LED[ 2 ]	=	SIGNAL_NAME;
	//assign	LED[ 3 ]	=	SIGNAL_NAME;
	
	
	assign	LED[ 4 ]	=	1;
	assign	LED[ 5 ]	=	1;
	assign	LED[ 6 ]	=	1;
	assign	LED[ 7 ]	=	reset_n;

	deca_top u0 (
		.clk_clk                ( MAX10_CLK1_50 ),          //             clk.clk
		.pll_qsys_locked_export ( pll_qsys_locked ), 		// pll_qsys_locked.export
		.reset_reset_n          ( reset_n ),          		//           reset.reset_n
		.i2c_irq_export         ( LIGHT_INT ),         //         spi_irq.export
		.i2c_pins_scl_pad_io    ( LIGHT_I2C_SCL ),    		//        i2c_pins.scl_pad_io
		.i2c_pins_sda_pad_io    ( LIGHT_I2C_SDA )     		//                .sda_pad_io
	);



endmodule
