# TCL that writes to the LED pio which is defined at a specific base address in the Qsys system

# Where is the LED pio base address:
set led_base_addr 0x420


# Set the values to write to the LED pio.
set led_vals {1 2 4 8 16 32 64 128 128 64 32 16 8 4 2 1}
set delay 30000
set cycles 2
set max_loop_count [ expr $cycles * 16 ]

#select the master service type and check the different service paths available
#There will only be one master.  The master name will correspond to the JTAG Master in the Qsys window (eg master_0 if the name of the JTAG to Avalon Master is called master_0)
get_service_paths master

#set the service path (master path).  The name "jtag_master" is a name only.    The name jtag_master is then used in this TCL file as a reference name.
set jtag_master [lindex [get_service_paths master] 0]

#opens the service master (needed for system console)
open_service master $jtag_master

#sets up loop value
set loopcount 0

#writes to LEDs going through the above array values

while {$loopcount < $max_loop_count} {
	foreach val $led_vals {
		master_write_8 $jtag_master $led_base_addr $val
		#delay:
		 for { set i 1 } { $i <= $delay } { incr i } {}

	incr loopcount
	}
}

#print out a message that the test is done
send_message info "LED_counting.tcl done"

#closes service master (needed for system console)
close_service master $jtag_master

