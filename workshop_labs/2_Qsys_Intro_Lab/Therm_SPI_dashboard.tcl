namespace eval thermSPI {

    variable initialized 0
    variable thermRaw 0
    variable dash_path ""
    variable dashboardActive 0

proc dashBoard {} {


	#determine available services for System Console
	get_service_paths master

	#set the master service path. The name "jtag_master" is a name only.    The name jtag_master is then used in this TCL file as a reference name
	set jtag_master [lindex [get_service_paths master] 0]

	#open the service path (master path).
	open_service master $jtag_master

	#assert the chip select to the device
	#master_write_32 $jtag_master  0x40C 0x400

	# write all f's to the device, this line is opendrain so it allows the thermometer to be read
	#master_write_32 $jtag_master  0x404 0xFFFF
	
	# read the returned read data and throw it away
	#master_read_32 $jtag_master  0x400 1
	source Therm_SPI_setup.tcl

	#read the spi data register, this is the thermal sample
	set ::thermSPI::thermRaw [master_read_32 $jtag_master 0x400 1 ]

	# write all 0's to the thermometer so that it continuously samples
	 master_write_32 $jtag_master  0x404 0x0000


	# deassert the chip select to the device
	master_write_32 $jtag_master  0x40C 0x000

	#set the variable for the initialized
     set ::thermSPI::initialized 1

      set ::thermSPI::dashboardActive 1
        #
        # Create dashboard
        #
        variable ::thermSPI::dash_path [ add_service dashboard thermSPI "thermSPI" "Tools/thermSPI"]

        #
        # Set dashboard properties
        #
        dashboard_set_property ${::thermSPI::dash_path} self developmentMode true
        dashboard_set_property ${::thermSPI::dash_path} self itemsPerRow 1
        dashboard_set_property ${::thermSPI::dash_path} self visible true

        #
        # top group widget
        #
        dashboard_add ${::thermSPI::dash_path} topGroup group self
        dashboard_set_property ${::thermSPI::dash_path} topGroup expandableX false
        dashboard_set_property ${::thermSPI::dash_path} topGroup expandableY false
        dashboard_set_property ${::thermSPI::dash_path} topGroup itemsPerRow 1
        dashboard_set_property ${::thermSPI::dash_path} topGroup title ""

        #
        # dial widget
        #
        dashboard_add ${::thermSPI::dash_path} thermDial dial topGroup
        dashboard_set_property ${::thermSPI::dash_path} thermDial min 0
        dashboard_set_property ${::thermSPI::dash_path} thermDial max 200
   #     dashboard_set_property ${::thermSPI::dash_path} thermDial title "Fahrenheit"
 	     dashboard_set_property ${::thermSPI::dash_path} thermDial title "Celsius"


        dashboard_set_property ${::thermSPI::dash_path} thermDial expandableX true
        dashboard_set_property ${::thermSPI::dash_path} thermDial expandableY true
        dashboard_set_property ${::thermSPI::dash_path} thermDial minHeight 200
        dashboard_set_property ${::thermSPI::dash_path} thermDial minWidth 200
        dashboard_set_property ${::thermSPI::dash_path} thermDial enabled true
        dashboard_set_property ${::thermSPI::dash_path} thermDial tickSize 10
        dashboard_set_property ${::thermSPI::dash_path} thermDial value 0

        #
        # history widgets
        #
        dashboard_add ${::thermSPI::dash_path} thermChart timeChart topGroup
        dashboard_set_property ${::thermSPI::dash_path} thermChart expandableX true
        dashboard_set_property ${::thermSPI::dash_path} thermChart expandableY true
        dashboard_set_property ${::thermSPI::dash_path} thermChart labelX "Time"
        dashboard_set_property ${::thermSPI::dash_path} thermChart labelY "Raw"
        dashboard_set_property ${::thermSPI::dash_path} thermChart maximumItemCount [ expr 3 * 120 ]
        dashboard_set_property ${::thermSPI::dash_path} thermChart title "Raw Thermal History"
        dashboard_set_property ${::thermSPI::dash_path} thermChart latest 3750

        after idle ::thermSPI::updateDashboard

	close_service master $jtag_master

        return -code ok
    }



proc updateDashboard {} {


        if { ${::thermSPI::dashboardActive} > 0 } {

            if { ${::thermSPI::initialized} > 0 } {
                	dashboard_set_property ${::thermSPI::dash_path} thermDial title "Celsius"
                dashboard_set_property ${::thermSPI::dash_path} thermChart latest ${::thermSPI::thermRaw}
              # dashboard_set_property ${::thermSPI::dash_path} thermDial value [ expr ((((${::thermSPI::thermRaw} / 4) * 0.03125) * 9) / 5) + 32 ]
			 dashboard_set_property ${::thermSPI::dash_path} thermDial value [ expr (((${::thermSPI::thermRaw} / 4) * 0.03125) * 1)]


              # after 300 ::thermSPI::updateDashboard
           } else {
            #    dashboard_set_property ${::thermSPI::dash_path} thermDial title "Uninitialized"
            #    after 1000 ::thermSPI::updateDashboard
            }
        }
    }



send_message info "ending System Console"

#close the master service
#close_service master $master_0


	}


