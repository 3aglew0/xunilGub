#include "pch.h"
#include "Utils.h"
typedef struct
{
	// Lots of *really bad* examples on the web where they use char[2]
	// to store the output of SIDT and SGDT.  This is wrong!
	//
	// In 32-bit mode, the output is 6 bytes, where the first 2 is
	// the limit and the upper 4 bytes is the 32-bit base address.
	//
	// In 64-bit mode, the output is 10 bytes, where the first 2 is
	// the limit and the upper 8 bytes is the 64-bit base address.
	//
	// This is described on page 299 of AMD64 Architecture Programmer's
	// Manual Volume 3: General-Purpose and System Instructions:
	// http://www.amd.com/us-en/assets/content_type/white_papers_and_tech_docs/24594.pdf

	ulong	limit : 16;
	ulong	base  : 64;
} __attribute__((packed)) dt;

ulong get_idt_base()
{
	// Get the base of Interupt Descriptor Table (IDT)

	unsigned long idtr;
    dt idt = {0, 0};

	// sidt instruction stores the contents of the IDT Register
	// (the IDTR which points to the IDT) in a processor register.

    asm volatile( "sidt %0" : "=m"(idt) );
    idtr = idt.base;
	//printf("IDT base: 0x%x\n", idtr);

	return idtr;
}


ulong get_ldt_base()
{
	// Get the base of Local Descriptor Table (LDT)

	u_char ldtr[5] = "\xef\xbe\xad\xde";
	ulong ldt = 0;

	// sldt instruction stores the contents of the LDT Register
	// (the LDTR which points to the LDT) in a processor register.
    asm volatile( "sldt %0" : "=m"(ldtr) );
	ldt = *((unsigned long *)&ldtr[0]);
	//printf("LDT base: 0x%x\n", ldt);

	return ldt;
}


ulong get_gdt_base()
{
	// Get the base of Global Descriptor Table (GDT)

	// sgdt instruction stores the contents of the GDT Register
	// (the GDTR which points to the GDT) in a processor register.

	dt gdt = {0, 0};
	asm volatile( "sgdt %0" : "=m"(gdt) );
	//printf( "GDT: limit=%04d, base=%016lx\n", gdt.limit, gdt.base );

	return gdt.base;
}
