
module test_sys_top_qsys (
	clk_50m_clk_in_clk,
	led_pio_out8_external_connection_export,
	pb_pio_in1_external_connection_export,
	reset_0_reset_n,
	temp_lm71cimf_0_conduit_end_cs_n,
	temp_lm71cimf_0_conduit_end_sc,
	temp_lm71cimf_0_conduit_end_sio);	

	input		clk_50m_clk_in_clk;
	output	[7:0]	led_pio_out8_external_connection_export;
	input		pb_pio_in1_external_connection_export;
	input		reset_0_reset_n;
	output		temp_lm71cimf_0_conduit_end_cs_n;
	output		temp_lm71cimf_0_conduit_end_sc;
	inout		temp_lm71cimf_0_conduit_end_sio;
endmodule
