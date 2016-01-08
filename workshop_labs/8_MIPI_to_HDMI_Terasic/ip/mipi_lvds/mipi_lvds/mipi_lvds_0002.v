//altlvds_rx BUFFER_IMPLEMENTATION="RAM" CBX_DECLARE_ALL_CONNECTED_PORTS="OFF" CBX_SINGLE_OUTPUT_FILE="ON" COMMON_RX_TX_PLL="OFF" CYCLONEII_M4K_COMPATIBILITY="ON" DATA_ALIGN_ROLLOVER=8 DATA_RATE="732.0 Mbps" DESERIALIZATION_FACTOR=2 DEVICE_FAMILY="MAX 10" DPA_INITIAL_PHASE_VALUE=0 DPLL_LOCK_COUNT=0 DPLL_LOCK_WINDOW=0 ENABLE_DPA_ALIGN_TO_RISING_EDGE_ONLY="OFF" ENABLE_DPA_CALIBRATION="ON" ENABLE_DPA_INITIAL_PHASE_SELECTION="OFF" ENABLE_DPA_MODE="OFF" ENABLE_DPA_PLL_CALIBRATION="OFF" ENABLE_SOFT_CDR_MODE="OFF" IMPLEMENT_IN_LES="ON" INCLOCK_BOOST=0 INCLOCK_DATA_ALIGNMENT="EDGE_ALIGNED" INCLOCK_PERIOD=2732 INCLOCK_PHASE_SHIFT=0 INPUT_DATA_RATE=732 NUMBER_OF_CHANNELS=4 OUTCLOCK_RESOURCE="AUTO" PLL_SELF_RESET_ON_LOSS_LOCK="OFF" PORT_RX_CHANNEL_DATA_ALIGN="PORT_UNUSED" PORT_RX_DATA_ALIGN="PORT_UNUSED" REGISTERED_DATA_ALIGN_INPUT="OFF" REGISTERED_OUTPUT="ON" SIM_DPA_IS_NEGATIVE_PPM_DRIFT="OFF" SIM_DPA_NET_PPM_VARIATION=0 SIM_DPA_OUTPUT_CLOCK_PHASE_SHIFT=0 USE_CORECLOCK_INPUT="OFF" USE_DPLL_RAWPERROR="OFF" USE_EXTERNAL_PLL="OFF" USE_NO_PHASE_SHIFT="ON" X_ON_BITSLIP="ON" rx_cda_reset rx_channel_data_align rx_data_align rx_data_align_reset rx_in rx_inclock rx_locked rx_out rx_outclock CARRY_CHAIN="MANUAL" CARRY_CHAIN_LENGTH=48 LOW_POWER_MODE="AUTO" ALTERA_INTERNAL_OPTIONS=AUTO_SHIFT_REGISTER_RECOGNITION=OFF
//VERSION_BEGIN 15.0 cbx_altaccumulate 2015:03:11:18:11:18:SJ cbx_altclkbuf 2015:03:11:18:11:18:SJ cbx_altddio_in 2015:03:11:18:11:18:SJ cbx_altddio_out 2015:03:11:18:11:18:SJ cbx_altiobuf_bidir 2015:03:11:18:11:18:SJ cbx_altiobuf_in 2015:03:11:18:11:18:SJ cbx_altiobuf_out 2015:03:11:18:11:18:SJ cbx_altlvds_rx 2015:03:11:18:11:18:SJ cbx_altpll 2015:03:11:18:11:18:SJ cbx_altsyncram 2015:03:11:18:11:18:SJ cbx_arriav 2015:03:11:18:11:13:SJ cbx_cyclone 2015:03:11:18:11:18:SJ cbx_cycloneii 2015:03:11:18:11:18:SJ cbx_lpm_add_sub 2015:03:11:18:11:18:SJ cbx_lpm_compare 2015:03:11:18:11:18:SJ cbx_lpm_counter 2015:03:11:18:11:18:SJ cbx_lpm_decode 2015:03:11:18:11:18:SJ cbx_lpm_mux 2015:03:11:18:11:18:SJ cbx_lpm_shiftreg 2015:03:11:18:11:18:SJ cbx_maxii 2015:03:11:18:11:18:SJ cbx_mgl 2015:03:11:18:14:52:SJ cbx_stratix 2015:03:11:18:11:19:SJ cbx_stratixii 2015:03:11:18:11:19:SJ cbx_stratixiii 2015:03:11:18:11:19:SJ cbx_stratixv 2015:03:11:18:11:19:SJ cbx_util_mgl 2015:03:11:18:11:19:SJ  VERSION_END
// synthesis VERILOG_INPUT_VERSION VERILOG_2001
// altera message_off 10463



// Copyright (C) 1991-2015 Altera Corporation. All rights reserved.
//  Your use of Altera Corporation's design tools, logic functions 
//  and other software and tools, and its AMPP partner logic 
//  functions, and any output files from any of the foregoing 
//  (including device programming or simulation files), and any 
//  associated documentation or information are expressly subject 
//  to the terms and conditions of the Altera Program License 
//  Subscription Agreement, the Altera Quartus II License Agreement,
//  the Altera MegaCore Function License Agreement, or other 
//  applicable license agreement, including, without limitation, 
//  that your use is for the sole purpose of programming logic 
//  devices manufactured by Altera and sold by Altera or its 
//  authorized distributors.  Please refer to the applicable 
//  agreement for further details.




//alt_lvds_ddio_in ADD_LATENCY_REG="FALSE" CBX_DECLARE_ALL_CONNECTED_PORTS="OFF" CBX_SINGLE_OUTPUT_FILE="ON" WIDTH=4 clock datain dataout_h dataout_l
//VERSION_BEGIN 15.0 cbx_altaccumulate 2015:03:11:18:11:18:SJ cbx_altclkbuf 2015:03:11:18:11:18:SJ cbx_altddio_in 2015:03:11:18:11:18:SJ cbx_altddio_out 2015:03:11:18:11:18:SJ cbx_altiobuf_bidir 2015:03:11:18:11:18:SJ cbx_altiobuf_in 2015:03:11:18:11:18:SJ cbx_altiobuf_out 2015:03:11:18:11:18:SJ cbx_altlvds_rx 2015:03:11:18:11:18:SJ cbx_altpll 2015:03:11:18:11:18:SJ cbx_altsyncram 2015:03:11:18:11:18:SJ cbx_arriav 2015:03:11:18:11:13:SJ cbx_cyclone 2015:03:11:18:11:18:SJ cbx_cycloneii 2015:03:11:18:11:18:SJ cbx_lpm_add_sub 2015:03:11:18:11:18:SJ cbx_lpm_compare 2015:03:11:18:11:18:SJ cbx_lpm_counter 2015:03:11:18:11:18:SJ cbx_lpm_decode 2015:03:11:18:11:18:SJ cbx_lpm_mux 2015:03:11:18:11:18:SJ cbx_lpm_shiftreg 2015:03:11:18:11:18:SJ cbx_maxii 2015:03:11:18:11:18:SJ cbx_mgl 2015:03:11:18:14:52:SJ cbx_stratix 2015:03:11:18:11:19:SJ cbx_stratixii 2015:03:11:18:11:19:SJ cbx_stratixiii 2015:03:11:18:11:19:SJ cbx_stratixv 2015:03:11:18:11:19:SJ cbx_util_mgl 2015:03:11:18:11:19:SJ  VERSION_END

//synthesis_resources = reg 12 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
(* ALTERA_ATTRIBUTE = {"{-to ddio_h_reg*} PLL_COMPENSATE=ON;ADV_NETLIST_OPT_ALLOWED=\"NEVER_ALLOW\""} *)
module  mipi_lvds_0002_lvds_ddio_in_7td
	( 
	clock,
	datain,
	dataout_h,
	dataout_l) /* synthesis synthesis_clearbox=1 */;
	input   clock;
	input   [3:0]  datain;
	output   [3:0]  dataout_h;
	output   [3:0]  dataout_l;

	reg	[3:0]	dataout_l_latch;
	(* ALTERA_ATTRIBUTE = {"LVDS_RX_REGISTER=HIGH;PRESERVE_REGISTER=ON;PRESERVE_FANOUT_FREE_NODE=ON"} *)
	reg	[3:0]	ddio_h_reg;
	(* ALTERA_ATTRIBUTE = {"LVDS_RX_REGISTER=LOW;PRESERVE_REGISTER=ON;PRESERVE_FANOUT_FREE_NODE=ON"} *)
	reg	[3:0]	ddio_l_reg;

	// synopsys translate_off
	initial
		dataout_l_latch = 0;
	// synopsys translate_on
	always @ ( posedge clock)
		  dataout_l_latch <= ddio_l_reg;
	// synopsys translate_off
	initial
		ddio_h_reg = 0;
	// synopsys translate_on
	always @ ( posedge clock)
		  ddio_h_reg <= datain;
	// synopsys translate_off
	initial
		ddio_l_reg = 0;
	// synopsys translate_on
	always @ ( negedge clock)
		  ddio_l_reg <= datain;
	assign
		dataout_h = dataout_l_latch,
		dataout_l = ddio_h_reg;
endmodule //mipi_lvds_0002_lvds_ddio_in_7td

//synthesis_resources = reg 20 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
(* ALTERA_ATTRIBUTE = {"AUTO_SHIFT_REGISTER_RECOGNITION=OFF"} *)
module  mipi_lvds_0002
	( 
	rx_cda_reset,
	rx_channel_data_align,
	rx_data_align,
	rx_data_align_reset,
	rx_in,
	rx_inclock,
	rx_locked,
	rx_out,
	rx_outclock) /* synthesis synthesis_clearbox=1 */;
	input   [3:0]  rx_cda_reset;
	input   [3:0]  rx_channel_data_align;
	input   rx_data_align;
	input   rx_data_align_reset;
	input   [3:0]  rx_in;
	input   rx_inclock;
	output   rx_locked;
	output   [7:0]  rx_out;
	output   rx_outclock;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_off
`endif
	tri0   [3:0]  rx_cda_reset;
	tri0   [3:0]  rx_channel_data_align;
	tri0   rx_data_align;
	tri0   rx_data_align_reset;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_on
`endif

	wire  [3:0]   wire_lvds_ddio_in1_dataout_h;
	wire  [3:0]   wire_lvds_ddio_in1_dataout_l;
	reg	[7:0]	rxreg;
	wire  [7:0]  ddio_in_node;

	mipi_lvds_0002_lvds_ddio_in_7td   lvds_ddio_in1
	( 
	.clock(rx_inclock),
	.datain(rx_in),
	.dataout_h(wire_lvds_ddio_in1_dataout_h),
	.dataout_l(wire_lvds_ddio_in1_dataout_l));
	// synopsys translate_off
	initial
		rxreg = 0;
	// synopsys translate_on
	always @ ( posedge rx_inclock)
		  rxreg <= ddio_in_node;
	assign
		ddio_in_node = {wire_lvds_ddio_in1_dataout_l[3], wire_lvds_ddio_in1_dataout_h[3], wire_lvds_ddio_in1_dataout_l[2], wire_lvds_ddio_in1_dataout_h[2], wire_lvds_ddio_in1_dataout_l[1], wire_lvds_ddio_in1_dataout_h[1], wire_lvds_ddio_in1_dataout_l[0], wire_lvds_ddio_in1_dataout_h[0]},
		rx_out = rxreg,
		rx_outclock = rx_inclock;
endmodule //mipi_lvds_0002
//VALID FILE
