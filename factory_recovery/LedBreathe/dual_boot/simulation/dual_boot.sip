set_global_assignment -entity "dual_boot" -library "lib_dual_boot" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "dual_boot" -library "lib_dual_boot" -name IP_TOOL_VERSION "15.0"
set_global_assignment -entity "dual_boot" -library "lib_dual_boot" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_dual_boot" -name SPD_FILE [file join $::quartus(sip_path) "../dual_boot.spd"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "../../dual_boot.qsys"]

set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "dual_boot.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_controller.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_synchronizer.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_controller.sdc"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/mentor/altera_dual_boot.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/mentor/alt_dual_boot_avmm.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/mentor/alt_dual_boot.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/aldec/altera_dual_boot.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/aldec/alt_dual_boot_avmm.v"]
set_global_assignment -library "lib_dual_boot" -name MISC_FILE [file join $::quartus(sip_path) "submodules/aldec/alt_dual_boot.v"]
