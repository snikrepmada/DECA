#switch_to_rev_c.tcl
#this TCL file will change pin assignments to support DECA REV_C development boards
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_A[3] -remove
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_ODT -remove
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_CS_n -remove
set_instance_assignment -name IO_MAXIMUM_TOGGLE_RATE "0 MHz" -to DDR3_BA[0] -remove
set_location_assignment PIN_D19 -to DDR3_BA[0]
set_location_assignment PIN_F22 -to DDR3_CS_n
set_location_assignment PIN_G22 -to DDR3_ODT
set_location_assignment PIN_C20 -to DDR3_A[3]
Set_location_assignmetn PIN_AB5 -to GSENSOR_PD -remove
Set_location_assignmetn PIN_AA5 -to GSENSOR_ST -remove


set_location_assignment PIN_B5 -to G_SENSOR_SCLK
set_location_assignment PIN_E8 -to G_SENSOR_INT1
set_location_assignment PIN_D5 -to G_SENSOR_SDO
set_location_assignment PIN_E9 -to G_SENSOR_CS_n
set_location_assignment PIN_D7 -to G_SENSOR_INT2
set_location_assignment PIN_C6 -to G_SENSOR_SDI
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_SCLK
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_INT1
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_SDO
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_CS_n
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_INT2
set_instance_assignment -name IO_STANDARD "1.2 V" -to G_SENSOR_SDI