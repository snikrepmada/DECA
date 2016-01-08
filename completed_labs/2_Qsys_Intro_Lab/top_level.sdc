create_clock -name "CLK_FPGA_50M" -period "50MHz" [ get_ports CLK_FPGA_50M ]

derive_clock_uncertainty

set_input_delay \
    -clock [ get_clocks altera_reserved_tck ] \
    10 \
    [ get_ports {
            altera_reserved_tdi
            altera_reserved_tms
        }]

set_output_delay \
    -clock [ get_clocks altera_reserved_tck ] \
    10 \
    [ get_ports {
                altera_reserved_tdo
        }]

set_false_path \
    -from [ get_ports {
                PBSW_N
                TEMP_MISO
            }]

set_false_path \
    -to [ get_ports {
                TEMP_SC
                TEMP_CS_N
                TEMP_MOSI
                F_LED[*]
            }]
