// xunilGub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

int main(void)
{
	/* enable functions */
	bool ENABLE_DEBUG_CHECKS = true;
	bool ENABLE_GEN_SANDBOX_CHECKS = true;
	bool ENABLE_VBOX_CHECKS = true;
	bool ENABLE_VMWARE_CHECKS = true;
	bool ENABLE_QEMU_CHECKS = true;
	bool ENABLE_XEN_CHECKS = true;
	bool ENABLE_TIMING_ATTACKS = true;
	bool ENABLE_ANTI_DISASSM_CHECKS = true;
	

	/* Debugger Detection */
	if (ENABLE_DEBUG_CHECKS) {
		std::cout << CYN "\nDebugger Detection" NC << std::endl;
		std::cout << GRNB "\nRunning debugmenot ... \n" NC << std::endl;
		std::system("./debugmenot/src/debugmenot");
		std::cout << GRNB "\nEnd running debugmenot ... \n" NC << std::endl;
	}

	// /* Generic sandbox detection */
	if (ENABLE_GEN_SANDBOX_CHECKS) {
		std::cout << CYN "\nSandbox Detection" NC << std::endl;
		std::cout << std::setw(60) << " Mouse movement (check in /dev/input/mice): " <<  std::flush << ((mouse_movement() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // check again if logic is correct: move -> PASS, not move -> FAIL
		std::cout << std::setw(60) << " Mouse movement (check using xdottools): " <<  std::flush << ((mouse_movement_tool() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // check again if logic is correct: move -> PASS, not move -> FAIL		
		std::cout << std::setw(60) << " Checking Number of processors in machine: " << ((number_of_processors()== 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl;
		std::cout << std::setw(60) << " Checking Interupt Descriptor Table location: " << ((idt_trick()== 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl;
		std::cout << std::setw(60) << " Checking Local Descriptor Table location: " << ((ldt_trick()== 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl;
		std::cout << std::setw(60) << " Checking Global Descriptor Table location: " << ((gdt_trick()== 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl;
		std::cout << std::setw(60) << " Checking disk space using std::filesystem::space_info : " << ((disk_space() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Check if time has been accelerated: " << ((accelerated_sleep() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking memory ram space: " << ((memory_space() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking model vendor name: " << ((model_computer_system() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
	}

	/* VirtualBox Detection */
	if (ENABLE_VBOX_CHECKS) {
		std::cout << CYN "\n\nVirtual Box Detection" NC << std::endl;
		std::cout << std::setw(60) << " Checking mac address: " << ((vbox_check_mac() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking pseudo devices: " << ((vbox_check_devices() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking vbox files: " << ((vbox_check_files() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) <<  " Checking vbox processes: " << ((vbox_check_processes() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking vbox firmware: " << ((vbox_check_firmware() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
	}

	/* VMWare Detection */
	if (ENABLE_VMWARE_CHECKS) {
		std::cout << CYN "\n\nVMWare Detection" NC << std::endl;
		std::cout << std::setw(60) << " Checking mac address: " << ((vmware_check_mac() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking vmware firmware: " << ((vmware_check_firmware() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking vmware pseudo devices: " << ((vmware_check_devices() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking vmware files: " << ((vmware_check_files() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Checking vmware processes: " << ((vmware_check_processes() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
	}

	/* QEMU Detection */
	if (ENABLE_QEMU_CHECKS) {
		std::cout << CYN "\n\nQemu Detection" NC << std::endl;
		std::cout << std::setw(60) << " Checking qemu firmware: " << ((qemu_check_firmware() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
	}

	/* Xen Detection */
	if (ENABLE_XEN_CHECKS) {
		std::cout << CYN "\n\nXen Detection" NC << std::endl;
		std::cout << std::setw(60) << " Checking xen mac address: " << ((xen_check_mac() == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
	}

	/* Timing Attacks */
	if (ENABLE_TIMING_ATTACKS) {
		std::cout << CYN "\n\nTiming attacks" NC << std::endl;
		std::cout << std::setw(60) << " Performing a sleep() in a loop: " << ((timing_sleep_loop(1000) == 0) ? GRN "PASS" NC : RED "FAIL" NC ) << std::endl; // true -> fail, false -> pass
		std::cout << std::setw(60) << " Performing a sleep() exploiting ping command line " << ((timing_IcmpSendEcho(3) == 0) ? GRN "PASS" NC : RED "FAIL" NC  ) << std::endl; // true -> fail, false -> pass
		
		
	}

	/* Anti disassembler tricks */
	if (ENABLE_ANTI_DISASSM_CHECKS) {
		std::cout << CYN "\n\nAnti disassembler checks " NC << std::endl;
		std::cout << std::setw(60) << " Begin AntiDisassmConstantCondition" << std::endl;
		AntiDisassmConstantCondition();
		std::cout << std::setw(60) << " Begin AntiDisassmAsmJmpSameTarget" << std::endl;
		AntiDisassmAsmJmpSameTarget();
		
	}
    
	std::cout << "\n\nAnalysis done, I hope you didn't get red flags :)" << std::endl;

	return 0;
}