set_module_property NAME "sls_avalon_usb20sr"
set_module_property description "USB2.0 High Speed Device"
set_module_property AUTHOR "System Level Solutions (I) Pvt. Ltd."
set_module_property TOP_LEVEL_HDL_FILE hdl/sls_avalon_usb20sr.v
set_module_property TOP_LEVEL_HDL_MODULE sls_avalon_usb20sr
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property DATASHEET_URL "http://www.slscorp.com/pages/ipusb20sls.php"

add_file hdl/control_ep_reg.v {SYNTHESIS}
add_file hdl/Enum_ram.v {SYNTHESIS}
add_file hdl/ep_register.v {SYNTHESIS}
add_file hdl/ep_register_dummy.v {SYNTHESIS}
add_file hdl/memory_idma.v {SYNTHESIS}
add_file hdl/pkt_assembler.v {SYNTHESIS}
add_file hdl/pkt_deassembler.v {SYNTHESIS}
add_file hdl/proto_engine.v {SYNTHESIS}
add_file hdl/proto_layer.v {SYNTHESIS}
add_file hdl/registers.v {SYNTHESIS}
add_file hdl/SramCtrl.v {SYNTHESIS}
add_file hdl/Test_mode.v {SYNTHESIS}
add_file hdl/Test_mode_ROM.v {SYNTHESIS}
add_file hdl/Ulpi_config.v {SYNTHESIS}
add_file hdl/Ulpi_Rx.v {SYNTHESIS}
add_file hdl/Ulpi_Tx.v {SYNTHESIS}
add_file hdl/Ulpi_Wrapper.v {SYNTHESIS}
add_file hdl/usb_avalon.v {SYNTHESIS}
add_file hdl/usb_crc16.v {SYNTHESIS}
add_file hdl/usb_crc5.v {SYNTHESIS}
add_file hdl/usb_defines.v {SYNTHESIS}
add_file hdl/usb_ep0buf_cnt.v {SYNTHESIS}
add_file hdl/usb_top.v {SYNTHESIS}
add_file hdl/utmi_interface.v {SYNTHESIS}
add_file hdl/sls_avalon_usb20sr.v {SYNTHESIS}
add_file hdl/Buffer_wrapper.v {SYNTHESIS}
add_file hdl/usb20sr_debug.v {SYNTHESIS}
add_file hdl/sls_avalon_usb20sr.ocp {SYNTHESIS}
add_file hdl/sls_avalon_usb20sr.sdc {SDC}



set_module_property "display_name" "USB2.0 HS Device Controller (RAM Based-SR)"
set_module_property "group" "SLS/Communication/USB"
set_module_property "icon_path" "SLS_logo.jpg"
set_module_property "version" "1.4"


# callouts
set_module_property Validation_Callback validate
set_module_property Elaboration_Callback elaborate


# Module parameters

add_parameter "IN_DEPTH" "integer" "512" 
set_parameter_property "IN_DEPTH" "display_name" "IN Buffer Depth(x32 bits)"
set_parameter_property "IN_DEPTH" ALLOWED_RANGES {512 1024 2048 4096 8192 16384 }


add_parameter "OUT_DEPTH" "integer" "512" 
set_parameter_property "OUT_DEPTH" "display_name" "OUT Buffer Depth(x32 bits)"
set_parameter_property "OUT_DEPTH" ALLOWED_RANGES {512 1024 2048 4096 8192 16384 }




add_parameter "IN_ADR_WIDTH" "integer" "9" 
set_parameter_property "IN_ADR_WIDTH" "display_name" ""
set_parameter_property "IN_ADR_WIDTH" "visible" ""
set_parameter_property "IN_ADR_WIDTH" derived true


add_parameter "OUT_ADR_WIDTH" "integer" "9" 
set_parameter_property "OUT_ADR_WIDTH" "display_name" ""
set_parameter_property "OUT_ADR_WIDTH" "visible" ""
set_parameter_property "OUT_ADR_WIDTH" derived true


add_parameter "Simulation" "integer" "0" "0 = no simulation; 1 = simulation"
set_parameter_property "Simulation" "display_name" "Enter Simulation Option"
set_parameter_property "Simulation" ALLOWED_RANGES {0 1}



add_parameter "Interface_sel" "integer" "0" 
set_parameter_property "Interface_sel" "display_name" ""
set_parameter_property "Interface_sel" "visible" ""




add_parameter "Enum_data_file" "string" "Enum_ram.hex" ""
set_parameter_property "Enum_data_file" "displayName" "Hex File Path"

proc elaborate {} {
	set Interface_sel [ get_parameter_value "Interface_sel" ]

	# Interface clock
	add_interface "clock" "clock" "sink" "asynchronous"
	# Ports in interface clock
	add_interface_port "clock" "clk" "clk" "input" 1
	add_interface_port "clock" "reset_n" "reset_n" "input" 1

	# Interface avalon_slave_0
	add_interface "avalon_slave_0" "avalon" "slave" "clock"
	set_interface_property "avalon_slave_0" "holdTime" "0"
	set_interface_property "avalon_slave_0" "linewrapBursts" "false"
	set_interface_property "avalon_slave_0" "minimumUninterruptedRunLength" "1"
	set_interface_property "avalon_slave_0" "isNonVolatileStorage" "false"
	set_interface_property "avalon_slave_0" "burstOnBurstBoundariesOnly" "false"
	set_interface_property "avalon_slave_0" "readLatency" "0"
	set_interface_property "avalon_slave_0" "printableDevice" "false"
	set_interface_property "avalon_slave_0" "readWaitTime" "1"
	set_interface_property "avalon_slave_0" "setupTime" "0"
	set_interface_property "avalon_slave_0" "addressAlignment" "DYNAMIC"
	set_interface_property "avalon_slave_0" "writeWaitTime" "0"
	set_interface_property "avalon_slave_0" "timingUnits" "Cycles"
	set_interface_property "avalon_slave_0" "isMemoryDevice" "false"


	set_interface_property "avalon_slave_0" "maximumPendingReadTransactions" "1"
        #set_interface_property avalon_slave_0 bridgesToMaster ""
        #set_interface_property avalon_slave_0 addressSpan 2097152


	# Ports in interface avalon_slave_0
	add_interface_port "avalon_slave_0" "address" "address" "input" 19
	add_interface_port "avalon_slave_0" "writedata" "writedata" "input" 32
	add_interface_port "avalon_slave_0" "chipselect" "chipselect" "input" 1
	add_interface_port "avalon_slave_0" "write_n" "write_n" "input" 1
	add_interface_port "avalon_slave_0" "read_n" "read_n" "input" 1
	add_interface_port "avalon_slave_0" "byteenable_n" "byteenable_n" "input" 4
	add_interface_port "avalon_slave_0" "readdata" "readdata" "output" 32
	add_interface_port "avalon_slave_0" "waitrequest" "waitrequest" "output" 1
        
        add_interface_port avalon_slave_0 readdatavalid readdatavalid Output 1

	# Interface irq0
	add_interface "irq0" "interrupt" "sender" "clock"
	set_interface_property "irq0" "associatedAddressablePoint" "avalon_slave_0"
	#
	set_interface_property "irq0" "irqScheme" "NONE"
	# Ports in interface irq0
	add_interface_port "irq0" "irq" "irq" "output" 1

	
	# interface-specific signals
	# Export signals
	add_interface conduit_end conduit end
	set_interface_property conduit_end ENABLED true
	# Data is part of both UTMI and ULPI
	add_interface_port "conduit_end" "Data" "export" "bidir" 8

        # ULPI Signals
		add_interface_port "conduit_end" "Stp" "export" "output" 1
		add_interface_port "conduit_end" "Dir" "export" "input" 1
		add_interface_port "conduit_end" "Nxt" "export" "input" 1
		add_interface_port "conduit_end" "phy_clk" "export" "input" 1
		add_interface_port "conduit_end" "phy_reset_n" "export" "output" 1
		add_interface_port "conduit_end" "phy_cs_n" "export" "output" 1
		add_interface_port "conduit_end" "Ext_reset_in" "export" "input" 1
		
	
}

# validate parameters
proc validate {} {


	set IN_DEPTH [ get_parameter_value "IN_DEPTH" ]

	if {$IN_DEPTH == 512} {
	                    set_parameter_value IN_ADR_WIDTH  9 
	                    send_message " info" "IN Buffer Memory Size = 2 KBytes "
                           }

	if {$IN_DEPTH == 1024} {
	                    set_parameter_value IN_ADR_WIDTH  10 
                            send_message " info" "IN Buffer Memory Size = 4 KBytes "
                           }
	if {$IN_DEPTH == 2048} {
	                    set_parameter_value IN_ADR_WIDTH  11 
                            send_message " info" "IN Buffer Memory Size = 8 KBytes "
                           }
	if {$IN_DEPTH == 4096} {
	                    set_parameter_value IN_ADR_WIDTH  12 
                            send_message " info" "IN Buffer Memory Size = 16 KBytes "
                           }
	if {$IN_DEPTH == 8192} {
	                    set_parameter_value IN_ADR_WIDTH  13 
                            send_message " info" "IN Buffer Memory Size = 32 KBytes "
                           }
	if {$IN_DEPTH == 16384} {
	                    set_parameter_value IN_ADR_WIDTH  14
                            send_message " info" "IN Buffer Memory Size = 64 KBytes "
                           }



	set OUT_DEPTH [ get_parameter_value "OUT_DEPTH" ]

	if {$OUT_DEPTH == 512} {
	                    set_parameter_value OUT_ADR_WIDTH  9 
	                    send_message " info" "OUT Buffer Memory Size = 2 KBytes "
                           }

	if {$OUT_DEPTH == 1024} {
	                    set_parameter_value OUT_ADR_WIDTH  10 
                            send_message " info" "OUT Buffer Memory Size = 4 KBytes "
                           }
	if {$OUT_DEPTH == 2048} {
	                    set_parameter_value OUT_ADR_WIDTH  11 
                            send_message " info" "OUT Buffer Memory Size = 8 KBytes "
                           }
	if {$OUT_DEPTH == 4096} {
	                    set_parameter_value OUT_ADR_WIDTH  12 
                            send_message " info" "OUT Buffer Memory Size = 16 KBytes "
                           }
	if {$OUT_DEPTH == 8192} {
	                    set_parameter_value OUT_ADR_WIDTH  13 
                            send_message " info" "OUT Buffer Memory Size = 32 KBytes "
                           }
	if {$OUT_DEPTH == 16384} {
	                    set_parameter_value OUT_ADR_WIDTH  14
                            send_message " info" "OUT Buffer Memory Size = 64 KBytes "
                           }





	set Simulation [ get_parameter_value "Simulation" ]
	if {$Simulation == 0} {
		send_message "info" "Disabling simulation."
	} else {
		send_message "info" "Enabling simulation."
	}

	
	set Enum_data_file [ get_parameter_value "Enum_data_file" ]
	send_message "info" "Use ' / ' instedad of ' \\ ' in Hex file path name"
	send_message "info" "Hex file : $Enum_data_file."


	
}

# custom GUI, in a future release
proc edit {} {
}