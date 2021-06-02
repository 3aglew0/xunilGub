// xunilGub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

int main(void)
{
	/* enable functions */
	// bool	ENABLE_TLS_CHECKS = true;
	bool ENABLE_DEBUG_CHECKS = true;
	// bool	ENABLE_INJECTION_CHECKS = true;
	bool ENABLE_GEN_SANDBOX_CHECKS = true;
	bool ENABLE_VBOX_CHECKS = true;
	// bool	ENABLE_VMWARE_CHECKS = true;
	// bool	ENABLE_VPC_CHECKS = true;
	// bool	ENABLE_QEMU_CHECKS = true;
	// bool	ENABLE_XEN_CHECKS = true;
	// bool	ENABLE_WINE_CHECKS = true;
	// bool	ENABLE_PARALLELS_CHECKS = true;
	// bool	ENABLE_CODE_INJECTIONS = false;
	// bool	ENABLE_TIMING_ATTACKS = true;
	// bool	ENABLE_DUMPING_CHECK = true;
	// bool	ENABLE_ANALYSIS_TOOLS_CHECK = true;
	// bool	ENABLE_ANTI_DISASSM_CHECKS = true;
	


	// /* Resize the console window for better visibility */
	// resize_console_window();

	// /* Display general informations */
	// _tprintf(_T("[al-khaser version 0.80]"));

	// print_category(TEXT("Initialisation"));
	// API::Init();
	// print_os();
	// API::PrintAvailabilityReport();

	// /* Are we running under WoW64 */
	// if (IsWoW64())
	// 	_tprintf(_T("Process is running under WOW64\n\n"));

	// if (ENABLE_DEBUG_CHECKS) PageExceptionInitialEnum();

	// /* TLS checks */
	// if (ENABLE_TLS_CHECKS) {
	// }

	/* Debugger Detection */
	if (ENABLE_DEBUG_CHECKS) {
		std::cout << "Debugger Detection" << std::endl;
		std::system("./debugmenot/src/debugmenot");
		//exec_check(&IsDebuggerPresentAPI, TEXT("Checking IsDebuggerPresent API "));
	}

	// if (ENABLE_INJECTION_CHECKS) {
	// }

	// /* Generic sandbox detection */
	if (ENABLE_GEN_SANDBOX_CHECKS) {
		std::string res;
		std::cout << "Sandbox Detection" << std::endl;
		std::cout << " Mouse movement " <<  std::flush << ((mouse_movement() == 0) ? "PASS" : "FAIL") << std::endl; // check again if logic is correct: move -> PASS, not move -> FAIL
		std::cout << " Checking Number of processors in machine " << number_of_processors() << std::endl;
		std::cout << " Checking Interupt Descriptor Table location " << idt_trick() << std::endl;
		std::cout << " Checking Local Descriptor Table location " << ldt_trick() << std::endl;
		std::cout << " Checking Global Descriptor Table location " << gdt_trick() << std::endl;
		std::cout << " Checking memory space using std::filesystem::space_info " << ((memory_space() == 0) ? "PASS" : "FAIL") << std::endl; // true -> fail, false -> pass
	}

	/* VirtualBox Detection */
	if (ENABLE_VBOX_CHECKS) {
		
	}

	// /* VMWare Detection */
	// if (ENABLE_VMWARE_CHECKS) {
	// }

	// /* Virtual PC Detection */
	// if (ENABLE_VPC_CHECKS) {
	// }

	// /* QEMU Detection */
	// if (ENABLE_QEMU_CHECKS) {
	// }

	// /* Xen Detection */
	// if (ENABLE_XEN_CHECKS) {
	// }

	// /* Wine Detection */
	// if (ENABLE_WINE_CHECKS) {
	// }

	// /* Paralles Detection */
	// if (ENABLE_PARALLELS_CHECKS) {
	// }

	// /* Code injections techniques */
	// if (ENABLE_CODE_INJECTIONS) {
	// }

	// /* Timing Attacks */
	// if (ENABLE_TIMING_ATTACKS) {
	// }

	// /* Malware analysis tools */
	// if (ENABLE_ANALYSIS_TOOLS_CHECK) {
	// }

	// /* Anti disassembler tricks */
	// if (ENABLE_ANTI_DISASSM_CHECKS) {
	// }

	// /* Anti Dumping */
	// if (ENABLE_DUMPING_CHECK) {
	// }

    
	std::cout << "\n\nAnalysis done, I hope you didn't get red flags :)" << std::endl;

	return 0;
}