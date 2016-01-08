set inmax_emmc_delay         7.0;         
set inmin_emmc_delay        -1.5;
set outmax_emmc_delay        2.5;
set outmin_emmc_delay       -2.5;
set outmax_emmc_cmd_delay    3.0;
set outmin_emmc_cmd_delay   -3.0;
set inmax_emmc_cmd_delay     7.0;
set inmin_emmc_cmd_delay    -2.5;

set inmax_sd_delay          7.0;         
set inmin_sd_delay         -1.5;
set outmax_sd_delay         3.0;
set outmin_sd_delay        -0.8;
set outmax_sd_cmd_delay     3.0;
set outmin_sd_cmd_delay    -0.8;
set inmax_sd_cmd_delay      7.0;
set inmin_sd_cmd_delay     -1.5;

set sd_clk_fb_en            0;
set ddr_en                  0;



derive_pll_clocks -create_base_clocks
derive_clock_uncertainty


## Assign path where sls_tcl_functions.tcl is stored.
set scripts [file dirname [file normalize [info script]]]

##Read sls_tcl_functions.tcl 
source $scripts/sls_tcl_functions.tcl

set corename "sls_sdhc_top"
set instance_list [get_core_instance_list $corename]

foreach inst $instance_list {

  ## Find avalon bus clock
  
  set main_clk [clk_constraint $inst|sls_sdhc_cntrl_inst|rx_cmp_pulse_f1|clk] 
  array set clk_array [list]

  set clk_array($inst) $main_clk

  set node_type [get_node_info -type $clk_array($inst)]

  ##Define variable for ip_clk
  
  array set ip_clk_array [list]
  set ip_clk_array($inst) ${inst}_ip_clk

  ##Define variable for sd_clk
  
  array set sd_clk_array [list]
  set sd_clk_array($inst) ${inst}_sd_clk

  ##Define variable for sd_clk output port
  
  array set sd_clk_out_array [list]
  set sd_clk_out_array($inst) ${inst}_sd_clk_out

  ##Find mapping of sd_clk to the top level output port
  
  set sd_clk_port [map_node_to_outport $inst|sls_sdhc_cntrl_inst|sls_sdhc_clkgen|SD_CLK|q]
  array set sd_clk_port_array [list]
  set sd_clk_port_array($inst) $sd_clk_port
  
  ##Find mapping of sd_clk_fb to the top level input port
  
  array set sd_clk_fb_port_array [list]
  set sd_clk_fb_port_array($inst) [map_node_to_inport $inst|sls_sdhc_cntrl_inst|sls_sdhc_cmd_inst|sdc_res_fb_f1|clk]

  ##Define variable for sd_clk_fb input port
  
  array set sd_clk_fb_array [list]
  set sd_clk_fb_array($inst) ${inst}_sd_clk_fb
  
  ##Find mapping of sd_data port to the top level io port
  
  set sd_data_port [map_node_to_outport $inst|sls_sdhc_cntrl_inst|sls_sdhc_data_inst|sls_sdhc_rddata_cntrl_inst|sls_sdhc_sddata_ddio_bidir_inst|ALTDDIO_BIDIR_component|auto_generated|ddio_outa[*]|dataout]
  array set sd_data_port_array [list]
  set sd_data_port_array($inst) $sd_data_port
  
  ##Find the value of DATA_INTERFACE parameter.
  
  foreach_in_collection out [all_outputs] {
    set outport [get_port_info -name $out]
    if {$outport == $sd_data_port_array($inst)} {
	   set ddr_en 1
    }
  }
  
  ##Find the value of SD_EMMC_SEL parameter
  
  if {$ddr_en} {
    set data_bits [get_pins -compatibility $inst|sls_sdhc_cntrl_inst|sls_sdhc_data_inst|sls_sdhc_rddata_cntrl_inst|sls_sdhc_sddata_ddio_bidir_inst|ALTDDIO_BIDIR_component|auto_generated|ddio_outa[*]|dataout]    
  } else {
    set data_bits [get_pins -compatibility $inst|sls_sdhc_cntrl_inst|sls_sdhc_data_inst|sd_data_out[*]|q]    
  }
  set sd_emmc_sel [get_collection_size $data_bits]  
  if {$sd_emmc_sel == 4} {
    set sd_emmc_sel "SD"
  } else {
    set sd_emmc_sel "eMMC"
  }
  
  ##Clock Constraint
      
  if {$node_type == "port"} {
    create_generated_clock -name $ip_clk_array($inst)     -source [get_ports $clk_array($inst)] -divide_by 2 [get_nets $inst|sls_sdhc_cntrl_inst|sls_sdhc_clkgen|ip_clk_divided]
    create_generated_clock -name $sd_clk_array($inst)     -source [get_ports $clk_array($inst)] -divide_by 2 [get_nets $inst|sls_sdhc_cntrl_inst|sls_sdhc_clkgen|SD_CLK]
    create_generated_clock -name $sd_clk_out_array($inst) -source [get_nets  $inst|sls_sdhc_cntrl_inst|sls_sdhc_clkgen|SD_CLK] [get_ports $sd_clk_port_array($inst)]
  } else {
    create_generated_clock -name $ip_clk_array($inst)     -source [get_pins $clk_array($inst)] -divide_by 2 [get_nets $inst|sls_sdhc_cntrl_inst|sls_sdhc_clkgen|ip_clk_divided]
    create_generated_clock -name $sd_clk_array($inst)     -source [get_pins $clk_array($inst)] -divide_by 2 [get_nets $inst|sls_sdhc_cntrl_inst|sls_sdhc_clkgen|SD_CLK]
    create_generated_clock -name $sd_clk_out_array($inst) -source [get_nets $inst|sls_sdhc_cntrl_inst|sls_sdhc_clkgen|SD_CLK] [get_ports $sd_clk_port_array($inst)]  
  }

  set ip_clk_period [get_clock_info -period $ip_clk_array($inst)]
  
  ##Virtual Clock Constraint
  
  create_clock -name vir_tx -period $ip_clk_period
  
  ##Find the value of SD_FEEDBACK_CLK parameter.
  
  foreach_in_collection in [all_inputs] {
    set inport [get_port_info -name $in]
    if {$inport == $sd_clk_fb_port_array($inst)} {
      set sd_clk_period [get_clock_info -period $sd_clk_array($inst)]
      create_clock -name $sd_clk_fb_array($inst) -period $sd_clk_period [get_ports $sd_clk_fb_port_array($inst)]
	   set sd_clk_fb_en 1
    }
  }
  
   
  if {$sd_clk_fb_en} {
    set in_clk [get_clock_info -name $sd_clk_fb_array($inst)]
  } else {
	 set in_clk [get_clock_info -name $sd_clk_out_array($inst)]  
  }
  
  set out_clk vir_tx
  
  ##Set value for Input/Output max/min delay. 
  
  if {$sd_emmc_sel == "SD"} {
    set outmax_data_delay $outmax_sd_delay
	 set outmin_data_delay $outmin_sd_delay
	 set inmax_data_delay  $inmax_sd_delay
	 set inmin_data_delay  $inmin_sd_delay
	 set outmax_cmd_delay  $outmax_sd_cmd_delay
	 set outmin_cmd_delay  $outmin_sd_cmd_delay
	 set inmax_cmd_delay   $inmax_sd_cmd_delay
	 set inmin_cmd_delay   $inmin_sd_cmd_delay
  } else {
     set outmax_data_delay $outmax_emmc_delay
	 set outmin_data_delay $outmin_emmc_delay  
	 set inmax_data_delay  $inmax_emmc_delay
	 set inmin_data_delay  $inmin_emmc_delay
	 set outmax_cmd_delay  $outmax_emmc_cmd_delay
	 set outmin_cmd_delay  $outmin_emmc_cmd_delay
	 set inmax_cmd_delay   $inmax_emmc_cmd_delay
	 set inmin_cmd_delay   $inmin_emmc_cmd_delay	 
  }
  
  ##Input/Output Constraint
  
  ioport_constraint $inst|sls_sdhc_cntrl_inst|sls_sdhc_cmd_inst|cmd_tx_frame_f2[47]|q 0 $out_clk $outmax_cmd_delay $outmin_cmd_delay $in_clk $inmax_cmd_delay $inmin_cmd_delay
  if {$ddr_en} {
    ioport_constraint $inst|sls_sdhc_cntrl_inst|sls_sdhc_data_inst|sls_sdhc_rddata_cntrl_inst|sls_sdhc_sddata_ddio_bidir_inst|ALTDDIO_BIDIR_component|auto_generated|ddio_outa[*]|dataout 1 $out_clk $outmax_data_delay $outmin_data_delay $in_clk $inmax_data_delay $inmin_data_delay   
  } else {
    ioport_constraint $inst|sls_sdhc_cntrl_inst|sls_sdhc_data_inst|sd_data_out[*]|q 0 $out_clk $outmax_data_delay $outmin_data_delay $in_clk $inmax_data_delay $inmin_data_delay
  }

  ##Set Clock Execption Constraint
  
  if {$ddr_en} {
    

 	set_false_path -setup -rise_from [get_clocks $ip_clk_array($inst)] -fall_to [get_clocks $out_clk]
    set_false_path -setup -fall_from [get_clocks $ip_clk_array($inst)] -rise_to [get_clocks $out_clk]
    set_false_path -hold  -fall_from [get_clocks $ip_clk_array($inst)] -fall_to [get_clocks $out_clk]
    set_false_path -hold  -rise_from [get_clocks $ip_clk_array($inst)] -rise_to [get_clocks $out_clk]

    if {$sd_clk_fb_en} {
      set_false_path -setup -rise_from [get_clocks $sd_clk_fb_array($inst)] -fall_to [get_clocks $sd_clk_fb_array($inst)]
      set_false_path -setup -fall_from [get_clocks $sd_clk_fb_array($inst)] -rise_to [get_clocks $sd_clk_fb_array($inst)]
      set_false_path -hold  -fall_from [get_clocks $sd_clk_fb_array($inst)] -fall_to [get_clocks $sd_clk_fb_array($inst)]
      set_false_path -hold  -rise_from [get_clocks $sd_clk_fb_array($inst)] -rise_to [get_clocks $sd_clk_fb_array($inst)]
	 
      set_clock_groups -asynchronous \
	     -group $sd_clk_fb_array($inst) \
	     -group $ip_clk_array($inst) \	          
	 
    } else {
		
      set_false_path -setup -rise_from [get_clocks $sd_clk_out_array($inst)] -fall_to [get_clocks $sd_clk_array($inst)]
      set_false_path -setup -fall_from [get_clocks $sd_clk_out_array($inst)] -rise_to [get_clocks $sd_clk_array($inst)]
      set_false_path -hold  -fall_from [get_clocks $sd_clk_out_array($inst)] -fall_to [get_clocks $sd_clk_array($inst)]
      set_false_path -hold  -rise_from [get_clocks $sd_clk_out_array($inst)] -rise_to [get_clocks $sd_clk_array($inst)]  

		
    }

	 ##False Path Constraint
	 
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*cmd_CS*}]
    set_false_path -from [get_keepers {*res_timeout_cnt*}] -to [get_keepers {*cmd_CS*}] 
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*cmd_tx_frame_f2*}]
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*res_bit*}]
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*busy_en*}]
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*ResponseReg*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*sdclk_sd_mode*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*baudcount_int*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*int_sdclk_stable*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*div_count*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*ip_clk_divided*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*SD_CLK*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*sdclk_fb_ddr_en*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*sdclk_fb_sd_mode*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*sdclk_fb_block_length*}]
    set_false_path -from [get_keepers {*av_control_o*}] -to [get_keepers {*ddr_en*}]
    set_false_path -from [get_keepers {*sd_volt_sw_op_en*}] -to [get_keepers {*sdclk_volt_sw_op_en*}] 
    set_false_path -from [get_keepers {*res_timeout_cnt*}] -to [get_keepers {*timeout_cnt*}] 
    set_false_path -from [get_keepers {*res_timeout_cnt*}] -to [get_keepers {*timeout_pl_1*}] 
    set_false_path -from [get_keepers {*tx_timeout_cnt*}] -to [get_keepers {*sdclk_wr_timeout_cnt*}] 
    set_false_path -from [get_keepers {*tx_timeout_cnt*}] -to [get_keepers {*sdclk_wr_timeout_err*}] 
    set_false_path -from [get_keepers {*tx_timeout_cnt*}] -to [get_keepers {*CS_write*}] 	
    set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*sdclk_rd_timeout_cnt*}] 
    set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*sdclk_timeout_err*}] 
	set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*CS_read*}] 
	set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*sdclk_rd_en*}] 
    set_false_path -from [get_keepers {*sig_input_f1*}] -to [get_keepers {*sig_out_f1*}]
    set_false_path -from [get_keepers {*av_block_length_o*}] -to [get_keepers {*sdclk_fb_block_length*}]
    set_false_path -from [get_keepers {*av_block_length_o*}] -to [get_keepers {*sdclk_block_length*}]
    set_false_path -from [get_keepers {*sig_out_f1*}] -to [get_keepers {*sig_out_f2*}]
	set_false_path -from [get_keepers {*reset_n*}] -to * 	 
  } else {
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*cmd_CS*}]
    set_false_path -from [get_keepers {*res_timeout_cnt*}] -to [get_keepers {*cmd_CS*}] 
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*cmd_tx_frame_f2*}]
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*res_bit*}]
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*busy_en*}]
    set_false_path -from [get_keepers {*command*}] -to [get_keepers {*ResponseReg*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*sdclk_sd_mode*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*baudcount_int*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*int_sdclk_stable*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*div_count*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*ip_clk_divided*}]
    set_false_path -from [get_keepers {*control*}] -to [get_keepers {*SD_CLK*}]
    set_false_path -from [get_keepers {*res_timeout_cnt*}] -to [get_keepers {*timeout_cnt*}] 
    set_false_path -from [get_keepers {*res_timeout_cnt*}] -to [get_keepers {*timeout_pl_1*}] 
    set_false_path -from [get_keepers {*tx_timeout_cnt*}] -to [get_keepers {*sdclk_wr_timeout_cnt*}] 
    set_false_path -from [get_keepers {*tx_timeout_cnt*}] -to [get_keepers {*sdclk_wr_timeout_err*}] 
    set_false_path -from [get_keepers {*tx_timeout_cnt*}] -to [get_keepers {*CS_write*}] 
    set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*sdclk_rd_timeout_cnt*}] 
	set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*sdclk_timeout_err*}] 
	set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*CS_read*}] 
	set_false_path -from [get_keepers {*rx_timeout_cnt*}] -to [get_keepers {*sdclk_rd_en*}]    
    set_false_path -from [get_keepers {*sig_input_f1*}] -to [get_keepers {*sig_out_f1*}]
	set_false_path -from [get_keepers {*sig_out_f1*}] -to [get_keepers {*sig_out_f2*}]
	set_false_path -from [get_keepers {*av_block_length_o*}] -to [get_keepers {*sdclk_block_length*}]
    set_false_path -from [get_keepers {*reset_n*}] -to * 	   
  
  }

  set sd_clk_fb_en 0   
  set ddr_en       0
	
} 

