/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu_qsys_gen2' in SOPC Builder design 'usb20sr_refdes'
 * SOPC Builder design path: ../../usb20sr_refdes.sopcinfo
 *
 * Generated: Mon Apr 27 15:46:00 EDT 2015
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
#define ALT_CPU_DATA_ADDR_WIDTH 0x1a
#define ALT_CPU_DCACHE_BYPASS_MASK 0x80000000
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 8192
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
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
#define ALT_CPU_ICACHE_SIZE 2048
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x13
#define ALT_CPU_NAME "cpu_qsys_gen2"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


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
#define NIOS2_DATA_ADDR_WIDTH 0x1a
#define NIOS2_DCACHE_BYPASS_MASK 0x80000000
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 8192
#define NIOS2_EXCEPTION_ADDR 0x00000020
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
#define NIOS2_ICACHE_SIZE 2048
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x13
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_DMA
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTPLL
#define __SLS_AVALON_USB20SR
#define __SLS_SDHC_TOP


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
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x2000040
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x2000040
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x2000040
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "usb20sr_refdes"


/*
 * altpll_0 configuration
 *
 */

#define ALTPLL_0_BASE 0x410a0
#define ALTPLL_0_IRQ -1
#define ALTPLL_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTPLL_0_NAME "/dev/altpll_0"
#define ALTPLL_0_SPAN 16
#define ALTPLL_0_TYPE "altpll"
#define ALT_MODULE_CLASS_altpll_0 altpll


/*
 * dma_0 configuration
 *
 */

#define ALT_MODULE_CLASS_dma_0 altera_avalon_dma
#define DMA_0_ALLOW_BYTE_TRANSACTIONS 1
#define DMA_0_ALLOW_DOUBLEWORD_TRANSACTIONS 1
#define DMA_0_ALLOW_HW_TRANSACTIONS 1
#define DMA_0_ALLOW_QUADWORD_TRANSACTIONS 1
#define DMA_0_ALLOW_WORD_TRANSACTIONS 1
#define DMA_0_BASE 0x41080
#define DMA_0_IRQ 3
#define DMA_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define DMA_0_LENGTHWIDTH 13
#define DMA_0_MAX_BURST_SIZE 128
#define DMA_0_NAME "/dev/dma_0"
#define DMA_0_SPAN 32
#define DMA_0_TYPE "altera_avalon_dma"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x2000040
#define JTAG_UART_0_IRQ 1
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * onchip_memory configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory altera_avalon_onchip_memory2
#define ONCHIP_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY_BASE 0x1000000
#define ONCHIP_MEMORY_CONTENTS_INFO ""
#define ONCHIP_MEMORY_DUAL_PORT 0
#define ONCHIP_MEMORY_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY_INIT_CONTENTS_FILE "usb20sr_refdes_onchip_memory"
#define ONCHIP_MEMORY_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY_IRQ -1
#define ONCHIP_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY_NAME "/dev/onchip_memory"
#define ONCHIP_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY_SIZE_VALUE 133120
#define ONCHIP_MEMORY_SPAN 133120
#define ONCHIP_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY_WRITABLE 1


/*
 * onchip_memory configuration as viewed by dma_0_read_master
 *
 */

#define DMA_0_READ_MASTER_ONCHIP_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_BASE 0x0
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_CONTENTS_INFO ""
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_DUAL_PORT 0
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_GUI_RAM_BLOCK_TYPE "AUTO"
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_INIT_CONTENTS_FILE "usb20sr_refdes_onchip_memory"
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_INIT_MEM_CONTENT 1
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_INSTANCE_ID "NONE"
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_IRQ -1
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_NAME "/dev/onchip_memory"
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_RAM_BLOCK_TYPE "AUTO"
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_SINGLE_CLOCK_OP 0
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_SIZE_MULTIPLE 1
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_SIZE_VALUE 133120
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_SPAN 133120
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define DMA_0_READ_MASTER_ONCHIP_MEMORY_WRITABLE 1


/*
 * onchip_memory configuration as viewed by dma_0_write_master
 *
 */

#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_BASE 0x0
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_CONTENTS_INFO ""
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_DUAL_PORT 0
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_GUI_RAM_BLOCK_TYPE "AUTO"
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_INIT_CONTENTS_FILE "usb20sr_refdes_onchip_memory"
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_INIT_MEM_CONTENT 1
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_INSTANCE_ID "NONE"
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_IRQ -1
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_NAME "/dev/onchip_memory"
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_RAM_BLOCK_TYPE "AUTO"
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_SINGLE_CLOCK_OP 0
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_SIZE_MULTIPLE 1
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_SIZE_VALUE 133120
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_SPAN 133120
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define DMA_0_WRITE_MASTER_ONCHIP_MEMORY_WRITABLE 1


/*
 * rst_pio configuration
 *
 */

#define ALT_MODULE_CLASS_rst_pio altera_avalon_pio
#define RST_PIO_BASE 0x2000020
#define RST_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define RST_PIO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RST_PIO_CAPTURE 0
#define RST_PIO_DATA_WIDTH 1
#define RST_PIO_DO_TEST_BENCH_WIRING 0
#define RST_PIO_DRIVEN_SIM_VALUE 0
#define RST_PIO_EDGE_TYPE "NONE"
#define RST_PIO_FREQ 48000000
#define RST_PIO_HAS_IN 0
#define RST_PIO_HAS_OUT 1
#define RST_PIO_HAS_TRI 0
#define RST_PIO_IRQ -1
#define RST_PIO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RST_PIO_IRQ_TYPE "NONE"
#define RST_PIO_NAME "/dev/rst_pio"
#define RST_PIO_RESET_VALUE 0
#define RST_PIO_SPAN 16
#define RST_PIO_TYPE "altera_avalon_pio"


/*
 * sdhc configuration
 *
 */

#define ALT_MODULE_CLASS_sdhc sls_sdhc_top
#define SDHC_BASE 0x41000
#define SDHC_FREQ 100000000u
#define SDHC_IRQ 4
#define SDHC_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SDHC_NAME "/dev/sdhc"
#define SDHC_SPAN 128
#define SDHC_TYPE "sls_sdhc_top"


/*
 * sysid_qsys_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys_0 altera_avalon_sysid_qsys
#define SYSID_QSYS_0_BASE 0x410b0
#define SYSID_QSYS_0_ID 233612565
#define SYSID_QSYS_0_IRQ -1
#define SYSID_QSYS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_0_NAME "/dev/sysid_qsys_0"
#define SYSID_QSYS_0_SPAN 8
#define SYSID_QSYS_0_TIMESTAMP 1429780595
#define SYSID_QSYS_0_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x2000000
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 48000000
#define TIMER_0_IRQ 0
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 47999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * usb20sr configuration
 *
 */

#define ALT_MODULE_CLASS_usb20sr sls_avalon_usb20sr
#define USB20SR_BASE 0x200000
#define USB20SR_IRQ 2
#define USB20SR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define USB20SR_NAME "/dev/usb20sr"
#define USB20SR_SPAN 2097152
#define USB20SR_TYPE "sls_avalon_usb20sr"


/*
 * usb20sr configuration as viewed by dma_0_read_master
 *
 */

#define DMA_0_READ_MASTER_USB20SR_BASE 0x200000
#define DMA_0_READ_MASTER_USB20SR_IRQ -1
#define DMA_0_READ_MASTER_USB20SR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DMA_0_READ_MASTER_USB20SR_NAME "/dev/usb20sr"
#define DMA_0_READ_MASTER_USB20SR_SPAN 2097152
#define DMA_0_READ_MASTER_USB20SR_TYPE "sls_avalon_usb20sr"


/*
 * usb20sr configuration as viewed by dma_0_write_master
 *
 */

#define DMA_0_WRITE_MASTER_USB20SR_BASE 0x200000
#define DMA_0_WRITE_MASTER_USB20SR_IRQ -1
#define DMA_0_WRITE_MASTER_USB20SR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DMA_0_WRITE_MASTER_USB20SR_NAME "/dev/usb20sr"
#define DMA_0_WRITE_MASTER_USB20SR_SPAN 2097152
#define DMA_0_WRITE_MASTER_USB20SR_TYPE "sls_avalon_usb20sr"


/*
 * user_led configuration
 *
 */

#define ALT_MODULE_CLASS_user_led altera_avalon_pio
#define USER_LED_BASE 0x2000030
#define USER_LED_BIT_CLEARING_EDGE_REGISTER 0
#define USER_LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USER_LED_CAPTURE 0
#define USER_LED_DATA_WIDTH 8
#define USER_LED_DO_TEST_BENCH_WIRING 0
#define USER_LED_DRIVEN_SIM_VALUE 0
#define USER_LED_EDGE_TYPE "NONE"
#define USER_LED_FREQ 48000000
#define USER_LED_HAS_IN 0
#define USER_LED_HAS_OUT 1
#define USER_LED_HAS_TRI 0
#define USER_LED_IRQ -1
#define USER_LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USER_LED_IRQ_TYPE "NONE"
#define USER_LED_NAME "/dev/user_led"
#define USER_LED_RESET_VALUE 0
#define USER_LED_SPAN 16
#define USER_LED_TYPE "altera_avalon_pio"

#endif /* __SYSTEM_H_ */
