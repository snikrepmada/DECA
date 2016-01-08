/******************************************************************************
 * NAME:         spi.c
 *
 * DESCRIPTION:  SPI bus driver.
 *
 * NOTES:
 *   None.
 *
 * REFERENCES:
 *   None.
 *
 * HISTORY:
 *   2015/13/2:  Initial version
 ******************************************************************************/

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/alt_irq.h>
#include <io.h>

//#include "altera_avalon_timer_regs.h"

#include "system.h"
#include "altera_avalon_spi.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_pio_regs.h"

#include "boardSL.h"


/******************************************************************************
 * DEFINES
 ******************************************************************************/


/******************************************************************************
 * TYPEDEFS
 ******************************************************************************/


/******************************************************************************
 * CONSTANTS
 ******************************************************************************/

SL_P_EVENT_HANDLER        pIrqEventHandler = 0;

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void timerInterrupt (void *unusedArg)
#else
static void timerInterrupt(void* unusedArg, alt_u32 id)
#endif
{
	/********************************************
	 * Acknowledge the interrupt
	 ********************************************/
	//IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_0_BASE, 0);

}

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void slInterrupt(void* context)
#else
static void slInterrupt(void* context, alt_u32 id)
#endif
{
	static int count = 0;

	if (pIrqEventHandler)
	{
		pIrqEventHandler(0);
	}

	count++;
	printf(" %x\n", count);

	/********************************************
	 * Acknowledge the interrupt
	 ********************************************/
	//IOWR(CC3100_IRQ_PIO_BASE, 0, 0xFF);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(CC3100_IRQ_PIO_BASE, 0xFF);

	/********************************************
	 * Allow some time
	 ********************************************/
	//IORD_ALTERA_AVALON_PIO_EDGE_CAP(CC3100_IRQ_PIO_BASE);
}

int registerInterruptHandler(SL_P_EVENT_HANDLER InterruptHdl , void* pValue)
{
    pIrqEventHandler = InterruptHdl;

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(CC3100_IRQ_PIO_BASE, 0xff);
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(CC3100_IRQ_PIO_BASE,  0xFF);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(CC3100_IRQ_PIO_BASE, 0xff);

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
	alt_ic_isr_register (CC3100_IRQ_PIO_IRQ_INTERRUPT_CONTROLLER_ID,
						 CC3100_IRQ_PIO_IRQ,
						 slInterrupt,
						 (void *)CC3100_IRQ_PIO_BASE,
						 (void *)0);
#else
	alt_irq_register (CC3100_IRQ_PIO_IRQ, CC3100_IRQ_PIO_BASE, slInterrupt);
#endif

	//alt_ic_irq_enable(CC3100_IRQ_PIO_IRQ_INTERRUPT_CONTROLLER_ID,
	//		CC3100_IRQ_PIO_IRQ);

#if 0
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
	alt_ic_isr_register (TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
						 TIMER_0_IRQ,
						 timerInterrupt,
						 (void *)TIMER_0_BASE,
						 0);
#else
	alt_irq_register (TIMER_0_IRQ, TIMER_0_BASE, timerInterrupt);
#endif
#endif

    return 0;
}

void CC3100_disable()
{

	IOWR(CC3100_CTRL_PIO_BASE, 0, 0);
}

void CC3100_enable()
{
	IOWR(CC3100_CTRL_PIO_BASE, 0, 1);
	//usleep(2);

	//IOWR(LEDS_BASE, 0, 0xf);
	//pioData = IORD(TEST_PIO_BASE, 0);

	//usleep(2);
	//usleep(2);
	//pioData = 0;
}
