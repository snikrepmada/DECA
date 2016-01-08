set_instance_assignment -name IO_STANDARD "1.5 V SCHMITT TRIGGER" -to SW0


set_instance_assignment -name IO_STANDARD "1.5 V SCHMITT TRIGGER" -to KEY0

set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[0]
set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[1]
set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[2]
set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[3]
set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[4]
set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[5]
set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[6]
set_instance_assignment -name IO_STANDARD "1.2 V" -to LED[7]

set_instance_assignment -name IO_STANDARD "2.5 V" -to MAX10_CLK1_50

set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to TEMP_CS_n
set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to TEMP_SC
set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to TEMP_SIO

set_location_assignment PIN_J21 -to SW0

set_location_assignment PIN_H21 -to KEY0

set_location_assignment PIN_C7 -to LED[0]
set_location_assignment PIN_C8 -to LED[1]
set_location_assignment PIN_A6 -to LED[2]
set_location_assignment PIN_B7 -to LED[3]
set_location_assignment PIN_C4 -to LED[4]
set_location_assignment PIN_A5 -to LED[5]
set_location_assignment PIN_B4 -to LED[6]
set_location_assignment PIN_C5 -to LED[7]

set_location_assignment PIN_M8 -to MAX10_CLK1_50

set_location_assignment PIN_AB4 -to TEMP_CS_n
set_location_assignment PIN_AA1 -to TEMP_SC
set_location_assignment PIN_Y2 -to TEMP_SIO