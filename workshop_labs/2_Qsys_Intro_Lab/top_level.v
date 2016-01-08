module top_level
(
    input   wire                MAX10_CLK1_50,
    input   wire                SW0,
    input   wire                KEY0,
    inout   wire                TEMP_SIO,

    output  wire                TEMP_SC,
    output  wire                TEMP_CS_n,
    output  wire    [ 7 : 0 ]   LED
);

wire wTEMP_MOSI;
wire [7:0] led_pio;
wire reset_n;

assign LED = ~led_pio;
assign reset_n = ~SW0;


test_sys_top_qsys u0 (
		.clk_50m_clk_in_clk                      (MAX10_CLK1_50),                      //                   clk_50m_clk_in.clk
		.led_pio_out8_external_connection_export (led_pio), // led_pio_out8_external_connection.export
		.pb_pio_in1_external_connection_export   (KEY0),   //   pb_pio_in1_external_connection.export
		.reset_0_reset_n                         (reset_n),                         //                          reset_0.reset_n
		.temp_lm71cimf_0_conduit_end_cs_n        (TEMP_CS_n),        //      temp_lm71cimf_0_conduit_end.cs_n
		.temp_lm71cimf_0_conduit_end_sc          (TEMP_SC),          //                                 .sc
		.temp_lm71cimf_0_conduit_end_sio         (TEMP_SIO)          //                                 .sio
	);


endmodule
