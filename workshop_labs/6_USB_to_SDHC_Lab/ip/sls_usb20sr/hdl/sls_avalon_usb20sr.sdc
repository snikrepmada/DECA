## Generated SDC file "sls_avalon_usb20sr.sdc"

## Copyright (C) 1991-2010 Altera Corporation
## Your use of Altera Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Altera Program License 
## Subscription Agreement, Altera MegaCore Function License 
## Agreement, or other applicable license agreement, including, 
## without limitation, that your use is for the sole purpose of 
## programming logic devices manufactured by Altera and sold by 
## Altera or its authorized distributors.  Please refer to the 
## applicable agreement for further details.


## VENDOR  "Altera"
## PROGRAM "Quartus II"
## VERSION "Version 9.1 Build 350 03/24/2010 Service Pack 2 SJ Full Version"

## DATE    "Thu Jul 29 15:03:13 2010"

##
## DEVICE  "EP3C5F256C8"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3

#**************************************************************
# Create Clock
#**************************************************************

#create clock for JTAG debug clock (100Mhz).
create_clock -name {altera_reserved_tck} -period 100.000 -waveform { 0.000 50.000 } [get_ports {altera_reserved_tck}]

#create clock for ulpi interface (phy chip's clock 60Mhz).
create_clock -name {u20_sr_clk_out} -period 16.666 -waveform { 0.000 8.333 } [get_ports { u20_sr_clk_out }] -add

#create base clock & generate clocks of PLL.
derive_pll_clocks -create_base_clocks


#**************************************************************
# Create Generated Clock
#**************************************************************



#**************************************************************
# Create Virtual Clock
#**************************************************************

#create virtual fpga input clock
create_clock -name vir_osc_clk -period 20.833 -waveform {0.000 10.416}

#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************

derive_clock_uncertainty

#**************************************************************
# Set Input Delay
#**************************************************************

##############################################################################
# u20_sr_d, u20_sr_dir, u20_sr_nxt Inputs from PHY                              
#                                ________          ________          ________ 
# Phy Clock (60 MHz)            |        |        |        |        |        |    
#                               |        |________|        |________|        |____
#                                           
# 
#u20_sr_d, u20_sr_dir, 
# u20_sr_nxt intput Timing       
#                                    ________         ________         ________
#        min - 4.915 ns         XXXXX valid  XXXXXXXXX valid  XXXXXXXXX valid  XXX
#        max - 5.085 ns         XXXXX________XXXXXXXXX________XXXXXXXXX________XXX
#                                         
##############################################################################
set_input_delay -clock [get_clocks {u20_sr_clk_out}] -max 5.085 [get_ports {u20_sr_d[*] u20_sr_dir u20_sr_nxt}]
set_input_delay -clock [get_clocks {u20_sr_clk_out}] -min 4.915 [get_ports {u20_sr_d[*] u20_sr_dir u20_sr_nxt}]

#constrain the input reset port. 
set_input_delay -clock [get_clocks {vir_osc_clk}] -max 1.221 [get_ports {fpga_reset_n}]
set_input_delay -clock [get_clocks {vir_osc_clk}] -min 0.949 [get_ports {fpga_reset_n}]

#constrain the TDI input port of JTAG signals
set_input_delay -clock altera_reserved_tck 20 [get_ports altera_reserved_tdi]

#constrain the TMS input port of JTAG signals
set_input_delay -clock altera_reserved_tck 20 [get_ports altera_reserved_tms]


#**************************************************************
# Set Output Delay
#**************************************************************

##############################################################################
# u20_sr_d, u20_sr_stp outputs from PHY                              
#                                ________          ________          ________ 
# Phy Clock (60 MHz)            |        |        |        |        |        |    
#                               |        |________|        |________|        |____
#                                           
# 
#u20_sr_d, u20_sr_stp Output Timing       
#                                    ________         ________         ________
#        min - 6.613 ns         XXXXX valid  XXXXXXXXX valid  XXXXXXXXX valid  XXX
#        max - 0.443 ns         XXXXX________XXXXXXXXX________XXXXXXXXX________XXX
#                                         
##############################################################################
set_output_delay -clock [get_clocks {u20_sr_clk_out}] -max 6.613 [get_ports {u20_sr_d[*] u20_sr_stp}]
set_output_delay -clock [get_clocks {u20_sr_clk_out}] -min 0.443 [get_ports {u20_sr_d[*] u20_sr_stp}]

#constrain the output reset port which is connected to to Phy chip
set_output_delay -clock [get_clocks {u20_sr_clk_out}] -max 6.282 [get_ports {u20_sr_reset_n}]
set_output_delay -clock [get_clocks {u20_sr_clk_out}] -min 0.219 [get_ports {u20_sr_reset_n}]

#constrain the TDO port
set_output_delay -clock altera_reserved_tck 20 [get_ports altera_reserved_tdo]


#**************************************************************
# Set Clock Groups
#**************************************************************

set_clock_groups -asynchronous\
                 -group {[get_clocks {altera_reserved_tck}]}\
                 -group {[get_clocks {osc_clk}]\
                         cc_soc|the_sys_pll|sd1|pll7|clk[0]\
                         vir_osc_clk}\
                 -group {cc_soc|the_sys_pll|sd1|pll7|clk[1]}\
                 -group {cc_soc|the_sys_pll|sd1|pll7|clk[2]}\
                 -group {u20_sr_clk_out}     

#**************************************************************
# Set False Path
#**************************************************************


#**************************************************************
# Set Multicycle Path
#**************************************************************


#**************************************************************
# Set Maximum Delay
#**************************************************************


#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

