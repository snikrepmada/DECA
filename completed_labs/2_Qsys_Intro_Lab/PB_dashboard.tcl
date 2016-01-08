namespace eval pbPIO {

    variable initialized 0
    variable pbValue 0
    variable dash_path ""
    variable dashboardActive 0
 
proc dashBoard {} {

	#determine available services for System Console
	get_service_paths master

	#set the master service path. The name "jtag_master" is a name only.    The name jtag_master is then used in this TCL file as a reference name
	set jtag_master [lindex [get_service_paths master] 0]

	#open the service path (master path).  
	open_service master $jtag_master 

	#set the dashBoard variable as high
	
	set ::pbPIO::dashboardActive 1


	#set the variable to be the value from the push button.  
	#This line is important as it reads the value from the register of 0x430. 
	#The pushbutton has the base register of 430.  
	#If the base register is changed, the 0x430 will need to be changed.  
	#The master_read_32 means read the 32 bits of this register.  The 1 is the offset.  
	#The set ::pbPIO::pbValue refers to a variable that is being assigned.    

	set ::pbPIO::pbValue [master_read_32 $jtag_master 0x430 1]

	   #
        # Create dashboard 
        #
        variable ::pbPIO::dash_path [ add_service dashboard pbPIO "pbPIO" "Tools/pbPIO"]  

        #
        # Set dashboard properties
        #
        dashboard_set_property ${::pbPIO::dash_path} self developmentMode true
        dashboard_set_property ${::pbPIO::dash_path} self itemsPerRow 1
        dashboard_set_property ${::pbPIO::dash_path} self visible true
        
        #
        # top group widget
        #
        dashboard_add ${::pbPIO::dash_path} topGroup group self
        dashboard_set_property ${::pbPIO::dash_path} topGroup expandableX false
        dashboard_set_property ${::pbPIO::dash_path} topGroup expandableY false
        dashboard_set_property ${::pbPIO::dash_path} topGroup itemsPerRow 1
        dashboard_set_property ${::pbPIO::dash_path} topGroup title ""

        #
        # state group widget
        #
        dashboard_add ${::pbPIO::dash_path} stateGroup group topGroup
        dashboard_set_property ${::pbPIO::dash_path} stateGroup expandableX false
        dashboard_set_property ${::pbPIO::dash_path} stateGroup expandableY false
        dashboard_set_property ${::pbPIO::dash_path} stateGroup preferredWidth 150
        dashboard_set_property ${::pbPIO::dash_path} stateGroup itemsPerRow 1
        dashboard_set_property ${::pbPIO::dash_path} stateGroup title "PB Input Current State"

        #
        # state widgets
        #
        dashboard_add ${::pbPIO::dash_path} stateLED led stateGroup
        dashboard_set_property ${::pbPIO::dash_path} stateLED expandableX false
        dashboard_set_property ${::pbPIO::dash_path} stateLED expandableY false
        dashboard_set_property ${::pbPIO::dash_path} stateLED text "State"
        dashboard_set_property ${::pbPIO::dash_path} stateLED color "green_off"

        #
        # history widgets
        #
        dashboard_add ${::pbPIO::dash_path} historyChart timeChart topGroup 
        dashboard_set_property ${::pbPIO::dash_path} historyChart expandableX true
        dashboard_set_property ${::pbPIO::dash_path} historyChart expandableY true
        dashboard_set_property ${::pbPIO::dash_path} historyChart labelX "Time"
        dashboard_set_property ${::pbPIO::dash_path} historyChart labelY "Value"
        dashboard_set_property ${::pbPIO::dash_path} historyChart maximumItemCount [ expr 3 * 120 ]
        dashboard_set_property ${::pbPIO::dash_path} historyChart title "PB Input History"
        dashboard_set_property ${::pbPIO::dash_path} historyChart latest 0

	  #call another function
        after idle ::pbPIO::updateDashboard

        return -code ok
    }

	proc updateDashboard {} {

		#this function is not a loop, but rather it looks if a pushbutton was held/not held when this is first run in System Console
	
		#initialize the variable
		set ::pbPIO::initialized 1

		#ensure the Dashboard is active

           if { ${::pbPIO::dashboardActive} > 0 } {

		#ensure that there is a variable to be initialized

            if { ${::pbPIO::initialized} > 0 } {
                dashboard_set_property ${::pbPIO::dash_path} stateLED text "State"
                if { ${::pbPIO::pbValue} == 0 } {
                    dashboard_set_property ${::pbPIO::dash_path} stateLED color "green"
                    dashboard_set_property ${::pbPIO::dash_path} historyChart latest 1
                } else {
                    dashboard_set_property ${::pbPIO::dash_path} stateLED color "green_off"
                    dashboard_set_property ${::pbPIO::dash_path} historyChart latest 0

			  }
 			}
		    }
		}
		


 
	#close_service master $jtag_master

}
 







	