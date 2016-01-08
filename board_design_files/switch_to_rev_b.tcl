#switch_to_rev_b.tcl
#this TCL file will change pin assignments to support DECA REV_B development boards
set_location_assignment PIN_F21 -to DDR3_ODT
set_location_assignment PIN_F20 -to DDR3_CS_n
set_location_assignment PIN_F18 -to DDR3_A[3]
set_location_assignment PIN_E19 -to DDR3_BA[0]
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_A[3]
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_ODT
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_CS_n
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_BA[0]

set_location_assignment PIN_B5 -to G_SENSOR_SCLK -remove
set_location_assignment PIN_E8 -to G_SENSOR_INT1 -remove
set_location_assignment PIN_D5 -to G_SENSOR_SDO  -remove
set_location_assignment PIN_E9 -to G_SENSOR_CS_n -remove
set_location_assignment PIN_D7 -to G_SENSOR_INT2 -remove
set_location_assignment PIN_C6 -to G_SENSOR_SDI  -remove
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_SCLK -remove
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_INT1 -remove
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_SDO -remove
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_CS_n -remove
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_INT2 -remove
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_SDI -remove
