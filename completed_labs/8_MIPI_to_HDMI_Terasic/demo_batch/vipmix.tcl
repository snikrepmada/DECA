#get_service_paths master
#use the Nios II data master to access the peripherals
set nm [lindex [get_service_paths master] 0]

# assign some variables to use later in the code or from the tcl console
set tpg   0x00000100
set mix   0x00000000

set frm0  0x00000014
set frm0x 0x0000000C
set frm0y 0x00000010

set frm1  0x00000028
set frm1x 0x00000020
set frm1y 0x00000024

open_service master $nm


#setup the TPG
master_write_32 $nm 0x00000100 1 0 0 320 240

#enable the sensor, the tpg, and the mixer output
master_write_32 $nm $frm0 1
master_write_32 $nm $frm1 1
master_write_32 $nm $mix 1

#move the cmos sensor to the middle of the screen, write to both x & y with one write
master_write_32 $nm $frm0x 128 16

#move the tpg, this shoudl center it but it could go anywhere
master_write_32 $nm $frm1x 800
master_write_32 $nm $frm1y 400


#run this command before trying to download the sof file again:
#close_service master $nm