#include "pch.h"

#include "Qemu.h"


bool qemu_check_firmware(){
    std::regex vbox("qemu|QEMU");
	std::smatch result;
	std::string firmware = get_system_firmware();
	std::regex_search(firmware,result,vbox);
	if (!result[0].str().empty())
		return true; // vbox string found
	else 
		return false; // vbox string not found
}