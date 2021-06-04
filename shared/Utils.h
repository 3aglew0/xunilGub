#pragma once

ulong get_idt_base();
ulong get_ldt_base();
ulong get_gdt_base();
unsigned long get_mem_total();
bool check_mac_addr(char *szMac);

// Check GCC
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif