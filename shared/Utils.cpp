#include "pch.h"
#include "Utils.h"

ulong get_idt_base()
{
	// Get the base of Interupt Descriptor Table (IDT)

	u_char idtr[6];
	ulong idt = 0;

	// sidt instruction stores the contents of the IDT Register
	// (the IDTR which points to the IDT) in a processor register.

#if defined (ENV32BIT)
	_asm sidt idtr
#endif
	idt = *((unsigned long *)&idtr[2]);
	// printf("IDT base: 0x%x\n", idt);

	return idt;
}


ulong get_ldt_base()
{
	// Get the base of Local Descriptor Table (LDT)

	u_char ldtr[5] = "\xef\xbe\xad\xde";
	ulong ldt = 0;

	// sldt instruction stores the contents of the LDT Register
	// (the LDTR which points to the LDT) in a processor register.
#if defined (ENV32BIT)
	_asm sldt ldtr
#endif
	ldt = *((unsigned long *)&ldtr[0]);
	printf("LDT base: 0x%x\n", ldt);

	return ldt;
}


ulong get_gdt_base()
{
	// Get the base of Global Descriptor Table (GDT)

	u_char gdtr[6];
	ulong gdt = 0;

	// sgdt instruction stores the contents of the GDT Register
	// (the GDTR which points to the GDT) in a processor register.
#if defined (ENV32BIT)
	_asm sgdt gdtr
#endif
	gdt = *((unsigned long *)&gdtr[2]);
	// printf("GDT base: 0x%x\n", gdt);

	return gdt;
}
