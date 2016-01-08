create_clock -name MAX10_CLK1_50 -period 20.000 -waveform {0.000 10.000} [get_ports {MAX10_CLK1_50}]
derive_pll_clocks
derive_clock_uncertainty