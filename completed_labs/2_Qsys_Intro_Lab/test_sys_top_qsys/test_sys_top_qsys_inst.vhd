	component test_sys_top_qsys is
		port (
			clk_50m_clk_in_clk                      : in    std_logic                    := 'X'; -- clk
			led_pio_out8_external_connection_export : out   std_logic_vector(7 downto 0);        -- export
			pb_pio_in1_external_connection_export   : in    std_logic                    := 'X'; -- export
			reset_0_reset_n                         : in    std_logic                    := 'X'; -- reset_n
			temp_lm71cimf_0_conduit_end_cs_n        : out   std_logic;                           -- cs_n
			temp_lm71cimf_0_conduit_end_sc          : out   std_logic;                           -- sc
			temp_lm71cimf_0_conduit_end_sio         : inout std_logic                    := 'X'  -- sio
		);
	end component test_sys_top_qsys;

	u0 : component test_sys_top_qsys
		port map (
			clk_50m_clk_in_clk                      => CONNECTED_TO_clk_50m_clk_in_clk,                      --                   clk_50m_clk_in.clk
			led_pio_out8_external_connection_export => CONNECTED_TO_led_pio_out8_external_connection_export, -- led_pio_out8_external_connection.export
			pb_pio_in1_external_connection_export   => CONNECTED_TO_pb_pio_in1_external_connection_export,   --   pb_pio_in1_external_connection.export
			reset_0_reset_n                         => CONNECTED_TO_reset_0_reset_n,                         --                          reset_0.reset_n
			temp_lm71cimf_0_conduit_end_cs_n        => CONNECTED_TO_temp_lm71cimf_0_conduit_end_cs_n,        --      temp_lm71cimf_0_conduit_end.cs_n
			temp_lm71cimf_0_conduit_end_sc          => CONNECTED_TO_temp_lm71cimf_0_conduit_end_sc,          --                                 .sc
			temp_lm71cimf_0_conduit_end_sio         => CONNECTED_TO_temp_lm71cimf_0_conduit_end_sio          --                                 .sio
		);

