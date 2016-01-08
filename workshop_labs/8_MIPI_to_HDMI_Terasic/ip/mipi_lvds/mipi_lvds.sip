set_global_assignment -entity "mipi_lvds" -library "lib_mipi_lvds" -name IP_TOOL_NAME "altera_soft_lvds"
set_global_assignment -entity "mipi_lvds" -library "lib_mipi_lvds" -name IP_TOOL_VERSION "15.0"
set_global_assignment -entity "mipi_lvds" -library "lib_mipi_lvds" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_mipi_lvds" -name SPD_FILE [file join $::quartus(sip_path) "mipi_lvds.spd"]

set_global_assignment -library "lib_mipi_lvds" -name MISC_FILE [file join $::quartus(sip_path) "mipi_lvds_sim/mipi_lvds.v"]
