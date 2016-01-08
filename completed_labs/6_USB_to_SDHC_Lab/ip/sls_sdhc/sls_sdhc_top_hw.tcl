# TCL File Generated by Component Editor 9.1sp1
# Wed Mar 31 10:51:43 IST 2010
# DO NOT MODIFY



# +-----------------------------------
# | module sls_sdhc_top
# | 
set_module_property DESCRIPTION "SD/eMMC Host Controller"
set_module_property NAME sls_sdhc_top
set_module_property VERSION 3.0
set_module_property INTERNAL false
set_module_property GROUP "SLS/Storage Media"
set_module_property AUTHOR "System Level Solutions (India) Pvt. Ltd"
set_module_property ICON_PATH hdl/sls_logo.jpg
set_module_property DISPLAY_NAME "SD/eMMC Host Controller"
set_module_property DATASHEET_URL http://www.slscorp.com/ip-cores/memory/sd-host-controller.html
set_module_property TOP_LEVEL_HDL_FILE hdl/sls_sdhc_top.v
set_module_property TOP_LEVEL_HDL_MODULE sls_sdhc_top
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE false
set_module_property ANALYZE_HDL TRUE
# | 
# +-----------------------------------

# +-----------------------------------
# | files
# | 
add_file hdl/sls_sdhc_ddio_buff.v {SYNTHESIS}
add_file hdl/sls_sdhc_rx_fifo.v {SYNTHESIS}
add_file hdl/sls_sdhc_sddata_ddio_bidir.v {SYNTHESIS}
add_file hdl/sls_sdhc_sdr_rx_fifo.v {SYNTHESIS}
add_file hdl/sls_sdhc_sdr_tx_fifo.v {SYNTHESIS}
add_file hdl/sls_sdhc_top.v {SYNTHESIS}
add_file hdl/sls_sdhc_tx_fifo.v {SYNTHESIS}
add_file hdl/sls_tcl_functions.tcl {SYNTHESIS}
add_file hdl/sls_sdhc_top.sdc {SDC}
add_file hdl/sls_sdhc_top.ocp {SYNTHESIS}


# | 
# +-----------------------------------

# +-----------------------------------
# | parameters
# | 
add_parameter SD_EMMC_SEL STRING "SD"
set_parameter_property SD_EMMC_SEL DEFAULT_VALUE "SD"
set_parameter_property SD_EMMC_SEL DISPLAY_NAME "SD/e.MMC Host Controller Select"
set_parameter_property SD_EMMC_SEL UNITS None
set_parameter_property SD_EMMC_SEL ALLOWED_RANGES {"SD" "e.MMC"}
set_parameter_property SD_EMMC_SEL DISPLAY_HINT "Select SD or e.MMC Host Controller"
set_parameter_property SD_EMMC_SEL AFFECTS_GENERATION false
set_parameter_property SD_EMMC_SEL HDL_PARAMETER true
add_parameter SYS_FREQ_HZ INTEGER 100
set_parameter_property SYS_FREQ_HZ DEFAULT_VALUE 100
set_parameter_property SYS_FREQ_HZ DISPLAY_NAME "Avalon clock (in Hz)"
set_parameter_property SYS_FREQ_HZ TYPE INTEGER
set_parameter_property SYS_FREQ_HZ UNITS none
set_parameter_property SYS_FREQ_HZ ALLOWED_RANGES -2147483648:2147483647
set_parameter_property SYS_FREQ_HZ DISPLAY_HINT "Avalon clk From 1 to 100Mhz"
set_parameter_property SYS_FREQ_HZ AFFECTS_GENERATION false
set_parameter_property SYS_FREQ_HZ HDL_PARAMETER true
set_parameter_property SYS_FREQ_HZ SYSTEM_INFO_TYPE CLOCK_RATE
set_parameter_property SYS_FREQ_HZ SYSTEM_INFO_ARG clock
add_parameter PWR_GD_TIME_IN_uS INTEGER 100
set_parameter_property PWR_GD_TIME_IN_uS DEFAULT_VALUE 100
set_parameter_property PWR_GD_TIME_IN_uS DISPLAY_NAME "Card Power UP Timing (in uSec)"
set_parameter_property PWR_GD_TIME_IN_uS UNITS None
set_parameter_property PWR_GD_TIME_IN_uS ALLOWED_RANGES 1:500
set_parameter_property PWR_GD_TIME_IN_uS DISPLAY_HINT "Power UP timing from 1 to 500uS"
set_parameter_property PWR_GD_TIME_IN_uS AFFECTS_GENERATION false
set_parameter_property PWR_GD_TIME_IN_uS HDL_PARAMETER true
add_parameter PWR_CYC_WIDTH_IN_uS INTEGER 100
set_parameter_property PWR_CYC_WIDTH_IN_uS DEFAULT_VALUE 100
set_parameter_property PWR_CYC_WIDTH_IN_uS DISPLAY_NAME "Card Power Cycle Timing (in uSec)"
set_parameter_property PWR_CYC_WIDTH_IN_uS UNITS None
set_parameter_property PWR_CYC_WIDTH_IN_uS ALLOWED_RANGES 1:500
set_parameter_property PWR_CYC_WIDTH_IN_uS DISPLAY_HINT "Power Cycle From 1 to 500uS"
set_parameter_property PWR_CYC_WIDTH_IN_uS AFFECTS_GENERATION false
set_parameter_property PWR_CYC_WIDTH_IN_uS HDL_PARAMETER true
add_parameter SD_FEEDBACK_CLK BOOLEAN false ""
set_parameter_property SD_FEEDBACK_CLK DEFAULT_VALUE false
set_parameter_property SD_FEEDBACK_CLK DISPLAY_NAME "Feedback Clock Enable"
set_parameter_property SD_FEEDBACK_CLK TYPE BOOLEAN
set_parameter_property SD_FEEDBACK_CLK UNITS None
set_parameter_property SD_FEEDBACK_CLK DESCRIPTION ""
set_parameter_property SD_FEEDBACK_CLK DISPLAY_HINT boolean
set_parameter_property SD_FEEDBACK_CLK HDL_PARAMETER true
add_parameter DATA_INTERFACE STRING "SDR"
set_parameter_property DATA_INTERFACE DEFAULT_VALUE "SDR"
set_parameter_property DATA_INTERFACE DISPLAY_NAME "SDR/DDR Data Interface Select"
set_parameter_property DATA_INTERFACE UNITS None
set_parameter_property DATA_INTERFACE ALLOWED_RANGES {"SDR" "DDR"}
set_parameter_property DATA_INTERFACE DISPLAY_HINT "SDR/DDR Data Interface Select"
set_parameter_property DATA_INTERFACE AFFECTS_GENERATION false
set_parameter_property DATA_INTERFACE HDL_PARAMETER true


# | 
# +-----------------------------------



# +-----------------------------------
# | display items
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point clock
# | 
add_interface clock clock end

set_interface_property clock ENABLED true

add_interface_port clock clk clk Input 1
add_interface_port clock reset_n reset_n Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point control
# | 
add_interface control avalon end
set_interface_property control addressAlignment DYNAMIC
set_interface_property control associatedClock clock
set_interface_property control burstOnBurstBoundariesOnly false
set_interface_property control explicitAddressSpan 0
set_interface_property control holdTime 0
set_interface_property control isMemoryDevice false
set_interface_property control isNonVolatileStorage false
set_interface_property control linewrapBursts false
set_interface_property control maximumPendingReadTransactions 1
set_interface_property control printableDevice false
set_interface_property control readLatency 0
set_interface_property control readWaitTime 1
set_interface_property control setupTime 0
set_interface_property control timingUnits Cycles
set_interface_property control writeWaitTime 0

set_interface_property control ASSOCIATED_CLOCK clock
set_interface_property control ENABLED true

add_interface_port control AvS_address address Input 5
add_interface_port control AvS_chipselect chipselect Input 1
add_interface_port control AvS_write_n write_n Input 1
add_interface_port control AvS_read_n read_n Input 1
add_interface_port control AvS_writedata writedata Input 32
add_interface_port control AvS_readdata readdata Output 32
add_interface_port control AvS_waitrequest waitrequest Output 1
add_interface_port control AvS_readdatavalid readdatavalid Output 1

# | 
# +-----------------------------------

# +-----------------------------------
# | connection point write_master
# | 
add_interface write_master avalon start
set_interface_property write_master associatedClock clock
set_interface_property write_master burstOnBurstBoundariesOnly false
set_interface_property write_master doStreamReads false
set_interface_property write_master doStreamWrites false
set_interface_property write_master linewrapBursts false

set_interface_property write_master ASSOCIATED_CLOCK clock
set_interface_property write_master ENABLED true

add_interface_port write_master AvM_wr_address address Output 32
add_interface_port write_master AvM_wr_writedata writedata Output 32
add_interface_port write_master AvM_wr_write_n write_n Output 1
add_interface_port write_master AvM_wr_chipselect chipselect Output 1
add_interface_port write_master AvM_wr_waitrequest waitrequest Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point read_master
# | 
add_interface read_master avalon start
set_interface_property read_master associatedClock clock
set_interface_property read_master burstOnBurstBoundariesOnly false
set_interface_property read_master doStreamReads false
set_interface_property read_master doStreamWrites false
set_interface_property read_master linewrapBursts false

set_interface_property read_master ASSOCIATED_CLOCK clock
set_interface_property read_master ENABLED true

add_interface_port read_master AvM_rd_readdata readdata Input 32
add_interface_port read_master AvM_rd_read_n read_n Output 1
add_interface_port read_master AvM_rd_address address Output 32
add_interface_port read_master AvM_rd_waitrequest waitrequest Input 1
add_interface_port read_master AvM_rd_readdatavalid readdatavalid Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point interrupt_sender
# | 
add_interface interrupt_sender interrupt end
set_interface_property interrupt_sender associatedAddressablePoint control

set_interface_property interrupt_sender ASSOCIATED_CLOCK clock
set_interface_property interrupt_sender ENABLED true

add_interface_port interrupt_sender AvS_irq irq Output 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point conduit_end
# | 
add_interface conduit_end conduit end

set_interface_property conduit_end ASSOCIATED_CLOCK clock
set_interface_property conduit_end ENABLED true

add_interface_port conduit_end SD_CLK export Output 1
add_interface_port conduit_end SD_CMD export Bidir 1
add_interface_port conduit_end SD_DAT0 export Bidir 1
add_interface_port conduit_end SD_DAT1 export Bidir 1
add_interface_port conduit_end SD_DAT2 export Bidir 1
add_interface_port conduit_end SD_DAT3 export Bidir 1
add_interface_port conduit_end SD_IN export Input 1
add_interface_port conduit_end SD_WP export Input 1
add_interface_port conduit_end SD_BUSY export Output 1
add_interface_port conduit_end SD_EMMC_VCC_EN export Output 1
add_interface_port conduit_end EMMC_VCC_Q_EN export Output 1

# | 
# +-----------------------------------



set_module_property VALIDATION_CALLBACK my_validate_callback

proc my_validate_callback {} {
  
  set sd_emmc_select    [get_parameter_value SD_EMMC_SEL]

  if {$sd_emmc_select == "e.MMC"} {
    send_message "info" "e.MMC Host Controller is Selected."  
  } else {  
    send_message "info" "SD Host Controller is Selected."
  }
  
}

# +-----------------------------------
# | Elaboration callback Function
# | 

set_module_property ELABORATION_CALLBACK elaboration

# the elaboration callback function
proc elaboration {} {
  set sd_emmc_select_2 [get_parameter_value SD_EMMC_SEL]
  set sd_fb_clk        [get_parameter_value SD_FEEDBACK_CLK]

  if {$sd_emmc_select_2 == "SD"} {    
    add_interface_port conduit_end SD_VOLTAGE_SEL export Output 1
    add_interface_port conduit_end SD_CMD_DIR     export Output 1
    add_interface_port conduit_end SD_DATA0_DIR   export Output 1
    add_interface_port conduit_end SD_DATA123_DIR export Output 1
  } 
  if {$sd_emmc_select_2 == "e.MMC"} {
    add_interface_port conduit_end SD_DAT4    export Bidir 1
    add_interface_port conduit_end SD_DAT5    export Bidir 1
    add_interface_port conduit_end SD_DAT6    export Bidir 1
    add_interface_port conduit_end SD_DAT7    export Bidir 1
    add_interface_port conduit_end EMMC_RST_N export Output 1
  }

  if {$sd_fb_clk} {
    add_interface_port conduit_end SD_CLK_FB export Input 1
  }
  set_module_assignment embeddedsw.CMacro.FREQ [get_parameter_value SYS_FREQ_HZ]u      
}