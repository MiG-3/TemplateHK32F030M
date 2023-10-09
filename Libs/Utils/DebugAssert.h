/*
 * DebugAssert.h
 *
 *  Created on: 16 мая 2017 г.
 *      Author: PaskalAV
 */

#ifndef UTILS_DEBUGASSERT_H
#define UTILS_DEBUGASSERT_H

#ifdef USE_FULL_ASSERT

#define DEBUG_ASSERT(EXPR) {\
	if(!(EXPR)) {\
		asm("	BKPT #1");\
	}\
}

#define DEBUG_STOP asm("  BKPT #1")

/*
#define DEBUG_ASSERT(EXPR) {\
	if(!(EXPR)) {\
		__asm volatile("ebreak");\
	}\
}

#define DEBUG_STOP __asm volatile("ebreak")
*/

#else
#define DEBUG_ASSERT(EXP) ((void)0U)
#define DEBUG_STOP   ((void)0U)
#endif


#define assert_param(expr) DEBUG_ASSERT(expr)


#endif /* UTILS_DEBUGASSERT_HP */
