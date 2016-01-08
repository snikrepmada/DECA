/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2' in SOPC Builder design 'mipi_vip'
 * SOPC Builder design path: ../../mipi_vip.sopcinfo
 *
 * Generated: Fri May 15 09:38:13 EDT 2015
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00040820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x13
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x00020020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x13
#define ALT_CPU_NAME "nios2_gen2"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00020000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00040820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x13
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x00020020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x13
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00020000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTPLL
#define __ALT_VIP_CL_MIXER
#define __ALT_VIP_CL_TPG
#define __I2C_OPENCORES


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "MAX 10"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/null"
#define ALT_STDERR_BASE 0x0
#define ALT_STDERR_DEV null
#define ALT_STDERR_TYPE ""
#define ALT_STDIN "/dev/null"
#define ALT_STDIN_BASE 0x0
#define ALT_STDIN_DEV null
#define ALT_STDIN_TYPE ""
#define ALT_STDOUT "/dev/null"
#define ALT_STDOUT_BASE 0x0
#define ALT_STDOUT_DEV null
#define ALT_STDOUT_TYPE ""
#define ALT_SYSTEM_NAME "mipi_vip"


/*
 * altpll_mipi configuration
 *
 */

#define ALTPLL_MIPI_BASE 0x410a0
#define ALTPLL_MIPI_IRQ -1
#define ALTPLL_MIPI_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTPLL_MIPI_NAME "/dev/altpll_mipi"
#define ALTPLL_MIPI_SPAN 16
#define ALTPLL_MIPI_TYPE "altpll"
#define ALT_MODULE_CLASS_altpll_mipi altpll


/*
 * ddr3_status configuration
 *
 */

#define ALT_MODULE_CLASS_ddr3_status altera_avalon_pio
#define DDR3_STATUS_BASE 0x50000
#define DDR3_STATUS_BIT_CLEARING_EDGE_REGISTER 0
#define DDR3_STATUS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DDR3_STATUS_CAPTURE 0
#define DDR3_STATUS_DATA_WIDTH 4
#define DDR3_STATUS_DO_TEST_BENCH_WIRING 0
#define DDR3_STATUS_DRIVEN_SIM_VALUE 0
#define DDR3_STATUS_EDGE_TYPE "NONE"
#define DDR3_STATUS_FREQ 100000000
#define DDR3_STATUS_HAS_IN 1
#define DDR3_STATUS_HAS_OUT 0
#define DDR3_STATUS_HAS_TRI 0
#define DDR3_STATUS_IRQ -1
#define DDR3_STATUS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DDR3_STATUS_IRQ_TYPE "NONE"
#define DDR3_STATUS_NAME "/dev/ddr3_status"
#define DDR3_STATUS_RESET_VALUE 0
#define DDR3_STATUS_SPAN 64
#define DDR3_STATUS_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * i2c_opencores_mipi configuration
 *
 */

#define ALT_MODULE_CLASS_i2c_opencores_mipi i2c_opencores
#define I2C_OPENCORES_MIPI_BASE 0x41040
#define I2C_OPENCORES_MIPI_IRQ 1
#define I2C_OPENCORES_MIPI_IRQ_INTERRUPT_CONTROLLER_ID 0
#define I2C_OPENCORES_MIPI_NAME "/dev/i2c_opencores_mipi"
#define I2C_OPENCORES_MIPI_SPAN 128
#define I2C_OPENCORES_MIPI_TYPE "i2c_opencores"


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x410b8
#define JTAG_UART_IRQ 0
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 32
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * led configuration
 *
 */

#define ALT_MODULE_CLASS_led altera_avalon_pio
#define LED_BASE 0x41070
#define LED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_CAPTURE 0
#define LED_DATA_WIDTH 8
#define LED_DO_TEST_BENCH_WIRING 0
#define LED_DRIVEN_SIM_VALUE 0
#define LED_EDGE_TYPE "NONE"
#define LED_FREQ 50000000
#define LED_HAS_IN 0
#define LED_HAS_OUT 1
#define LED_HAS_TRI 0
#define LED_IRQ -1
#define LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_IRQ_TYPE "NONE"
#define LED_NAME "/dev/led"
#define LED_RESET_VALUE 0
#define LED_SPAN 64
#define LED_TYPE "altera_avalon_pio"


/*
 * mipi_core_en configuration
 *
 */

#define ALT_MODULE_CLASS_mipi_core_en altera_avalon_pio
#define MIPI_CORE_EN_BASE 0x41080
#define MIPI_CORE_EN_BIT_CLEARING_EDGE_REGISTER 0
#define MIPI_CORE_EN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MIPI_CORE_EN_CAPTURE 0
#define MIPI_CORE_EN_DATA_WIDTH 1
#define MIPI_CORE_EN_DO_TEST_BENCH_WIRING 0
#define MIPI_CORE_EN_DRIVEN_SIM_VALUE 0
#define MIPI_CORE_EN_EDGE_TYPE "NONE"
#define MIPI_CORE_EN_FREQ 100000000
#define MIPI_CORE_EN_HAS_IN 0
#define MIPI_CORE_EN_HAS_OUT 1
#define MIPI_CORE_EN_HAS_TRI 0
#define MIPI_CORE_EN_IRQ -1
#define MIPI_CORE_EN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MIPI_CORE_EN_IRQ_TYPE "NONE"
#define MIPI_CORE_EN_NAME "/dev/mipi_core_en"
#define MIPI_CORE_EN_RESET_VALUE 1
#define MIPI_CORE_EN_SPAN 64
#define MIPI_CORE_EN_TYPE "altera_avalon_pio"


/*
 * mipi_reset_n configuration
 *
 */

#define ALT_MODULE_CLASS_mipi_reset_n altera_avalon_pio
#define MIPI_RESET_N_BASE 0x41090
#define MIPI_RESET_N_BIT_CLEARING_EDGE_REGISTER 0
#define MIPI_RESET_N_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MIPI_RESET_N_CAPTURE 0
#define MIPI_RESET_N_DATA_WIDTH 1
#define MIPI_RESET_N_DO_TEST_BENCH_WIRING 0
#define MIPI_RESET_N_DRIVEN_SIM_VALUE 0
#define MIPI_RESET_N_EDGE_TYPE "NONE"
#define MIPI_RESET_N_FREQ 100000000
#define MIPI_RESET_N_HAS_IN 0
#define MIPI_RESET_N_HAS_OUT 1
#define MIPI_RESET_N_HAS_TRI 0
#define MIPI_RESET_N_IRQ -1
#define MIPI_RESET_N_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MIPI_RESET_N_IRQ_TYPE "NONE"
#define MIPI_RESET_N_NAME "/dev/mipi_reset_n"
#define MIPI_RESET_N_RESET_VALUE 1
#define MIPI_RESET_N_SPAN 64
#define MIPI_RESET_N_TYPE "altera_avalon_pio"


/*
 * onchip_memory2 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_BASE 0x20000
#define ONCHIP_MEMORY2_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_DUAL_PORT 0
#define ONCHIP_MEMORY2_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_INIT_CONTENTS_FILE "mipi_vip_onchip_memory2"
#define ONCHIP_MEMORY2_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_IRQ -1
#define ONCHIP_MEMORY2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_NAME "/dev/onchip_memory2"
#define ONCHIP_MEMORY2_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_SIZE_VALUE 70000
#define ONCHIP_MEMORY2_SPAN 70000
#define ONCHIP_MEMORY2_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_WRITABLE 1


/*
 * sw configuration
 *
 */

#define ALT_MODULE_CLASS_sw altera_avalon_pio
#define SW_BASE 0x41060
#define SW_BIT_CLEARING_EDGE_REGISTER 0
#define SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_CAPTURE 0
#define SW_DATA_WIDTH 2
#define SW_DO_TEST_BENCH_WIRING 0
#define SW_DRIVEN_SIM_VALUE 0
#define SW_EDGE_TYPE "NONE"
#define SW_FREQ 50000000
#define SW_HAS_IN 1
#define SW_HAS_OUT 0
#define SW_HAS_TRI 0
#define SW_IRQ -1
#define SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SW_IRQ_TYPE "NONE"
#define SW_NAME "/dev/sw"
#define SW_RESET_VALUE 0
#define SW_SPAN 64
#define SW_TYPE "altera_avalon_pio"


/*
 * sysid_qsys configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys altera_avalon_sysid_qsys
#define SYSID_QSYS_BASE 0x410b0
#define SYSID_QSYS_ID 0
#define SYSID_QSYS_IRQ -1
#define SYSID_QSYS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_NAME "/dev/sysid_qsys"
#define SYSID_QSYS_SPAN 8
#define SYSID_QSYS_TIMESTAMP 1431696305
#define SYSID_QSYS_TYPE "altera_avalon_sysid_qsys"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x41000
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 100000000
#define TIMER_IRQ 4
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 99999
#define TIMER_MULT 0.001
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 128
#define TIMER_TICKS_PER_SEC 1000
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * tpg configuration
 *
 */

#define ALT_MODULE_CLASS_tpg alt_vip_cl_tpg
#define TPG_BASE 0x100
#define TPG_IRQ -1
#define TPG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TPG_NAME "/dev/tpg"
#define TPG_SPAN 32
#define TPG_TYPE "alt_vip_cl_tpg"


/*
 * vip_mixer configuration
 *
 */

#define ALT_MODULE_CLASS_vip_mixer alt_vip_cl_mixer
#define VIP_MIXER_BASE 0x0
#define VIP_MIXER_IRQ -1
#define VIP_MIXER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VIP_MIXER_NAME "/dev/vip_mixer"
#define VIP_MIXER_SPAN 256
#define VIP_MIXER_TYPE "alt_vip_cl_mixer"

#endif /* __SYSTEM_H_ */
