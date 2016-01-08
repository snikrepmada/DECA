/**********************************************************************
 * NAME:         boardSL.h
 *
 * DESCRIPTION:
 *
 * NOTES:
 *   None.
 *
 * REFERENCES:
 *   None.
 *
 * HISTORY:
 *   2015/13/2:  Initial version
 **********************************************************************/

#ifndef _BOARDSL_H
#define _BOARDSL_H


/**********************************************************************
 * INCLUDE FILES
 **********************************************************************/

#include <stdint.h>


/**********************************************************************
 * TYPEDEFS
 **********************************************************************/
typedef void (*SL_P_EVENT_HANDLER)(void* pValue);


/**********************************************************************
 * FUNCTION PROTOTYPES
 **********************************************************************/
int registerInterruptHandler(SL_P_EVENT_HANDLER InterruptHdl , void* pValue);
void CC3100_disable();
void CC3100_enable();

#endif  // _BOARDSL_H
