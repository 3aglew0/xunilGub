#include "pch.h"

#include "Xen.h"

/*
Check Xen NIC MAC address
*/
bool xen_check_mac()
{
	return check_mac_addr("00:16:3e");
}