#include "AntiDisassm.h"
#include <iostream>

/*
	This technique is composed of a single conditional jump instruction placed where the condition
	will always be the same.
*/
void AntiDisassmConstantCondition()
{	
    __asm__ (  "xor %edx, %edx;" 
	            "jz L_END;"			// this condition is always true
	            "movl $20, %edx;"	// junk code which creates mess to disassembler
                "L_END:;"
	            "nop;"
            );
}

/*
	The most common anti-disassembly technique seen in the wild is two back-to back
	conditional jump instructions that both point to the same target. For example,
	if a jz XYZ is followed by jnz XYZ, the location XYZ will always be jumped to
*/
void AntiDisassmAsmJmpSameTarget()
{
	__asm__ (  "jz L_END1;" 
	            "jnz L_END1;"			// this condition is always true
	            "movl $20, %edx;"		// junk code which creates mess to disassembler
                "L_END1:;"
	            "nop;"
            );
}