/*
 * abort.cpp
 *
 *  Created on: Jun 10, 2018
 *      Author: 13774
 */

//Defined in header <stdlib.h>
//void abort(void);
//(until C11)
//_Noreturn void abort(void);


#include <cstdlib>
#include <cstdio>

void __attribute__((noreturn)) abort()
{
	puts("-- ABORT --");
	while(true){__asm__("wfi");}
}
