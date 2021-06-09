#include "pch.h"

#include "Xen.h"

/*
Check Xen NIC MAC address
*/
bool xen_check_mac()
{
	return check_mac_addr("\x00\x16\x3E");
}