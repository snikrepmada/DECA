#This TCL file is used to read the CC2650's MAC address

# This command isn't useful in a script but stand alone, reports the Avalon-MM masters available
get_service_paths master

# This command creates a variable pointing to the Nios Master (nm)
set nm [lindex [get_service_paths master] 0]
open_service master $nm

set ble_ssid_low 0x40800
set ble_ssid_high 0x40820

master_read_32 $nm $ble_ssid_low 2

# These lines are commented out as I don't want to execute them directly in this TCL, 
# but mainly to cut-and-paste them into the System Console window

#   master_read_32 $nm $ble_ssid_low 2   # reads two 32-bit words from the ble_ssid_low pointer from the nm address space.
#   master_read_32 $nm $ble_ssid_high 2
#   master_read_32 $nm 0x00 8					# reads the system ID and timestamp value


# 	 note, since Nios II is running, we may need to use these commands:
#      processor_stop $nm
#      processor_start $nm
#   close_service master $nm

