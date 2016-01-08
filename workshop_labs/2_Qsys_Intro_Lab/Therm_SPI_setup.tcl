get_service_paths master
set jtag_master [lindex [get_service_paths master] 0]
open_service master $jtag_master

master_write_32 $jtag_master  0x40C 0x400
master_write_32 $jtag_master  0x404 0xFFFF

master_read_32 $jtag_master  0x400 5
