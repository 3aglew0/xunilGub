#include "AntiDisassm.h"

extern "C" void __AsmConstantCondition();
extern "C" void __AsmJmpSameTarget();
extern "C" void __AsmImpossibleDisassm();
extern "C" void __AsmFunctionPointer(unsigned int);
extern "C" void __AsmReturnPointerAbuse(unsigned int);

/*
	This technique is composed of a single conditional jump instruction placed where the condition
	will always be the same.
*/
void AntiDisassmConstantCondition()
{
     __asm__ (  "xor %eax, %eax;"
	            "jz L_END;"
	            "movl $20, %ebx;"
                "L_END:;"
	            "nop;"
                "ret;"
            );
}

/*
	The most common anti-disassembly technique seen in the wild is two back-to back
	conditional jump instructions that both point to the same target. For example,
	if a jz XYZ is followed by jnz XYZ, the location XYZ will always be jumped to
*/
void AntiDisassmAsmJmpSameTarget()
{
	// __AsmJmpSameTarget();
}

/*
	By using a data byte placed strategically after a conditional jump instruction
	with the idea that disassembly starting at this byte will prevent the real instruction
	that follows from being disassembled because the byte that inserted is the opcode for
	a multibyte instruction.

*/
void AntiDisassmImpossibleDiasassm()
{
/* 	__AsmImpossibleDisassm();
 */}


/*
	If function pointers are used in handwritten assembly or crafted in a nonstandard way
	in source code, the results can be difficult to reverse engineer without dynamic analysis.
*/
void AntiDisassmFunctionPointer()
{

/* 	unsigned int Number = 2;
	__AsmFunctionPointer(Number); */
}


/*
	The most obvious result of this technique is that the disassembler doesn�t show any
	code cross - reference to the target being jumped to.
*/
void AntiDisassmReturnPointerAbuse()
{/* 
	__AsmReturnPointerAbuse(666); */
}
