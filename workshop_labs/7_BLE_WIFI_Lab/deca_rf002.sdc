create_clock -name adc_clk_in -period 100.000 [get_ports {ADC_CLK_10}]
create_clock -name sys_clk_in -period 20.000 [get_ports {MAX10_CLK1_50}]

derive_pll_clocks

derive_clock_uncertainty

 