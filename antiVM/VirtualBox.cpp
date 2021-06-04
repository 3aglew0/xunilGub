#include "pch.h"
#include "VirtualBox.h"

bool vbox_check_mac()
{
	// PCS Systemtechnik CmbH (VirtualBox)
	return check_mac_addr("\x08\x00\x27");
}
