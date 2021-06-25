#include "pch.h"

#include "VMWare.h"

bool vmware_check_files(){
	std::vector<std::string> VM_files;
    VM_files.push_back("/usr/bin/vmware-vgauth-cmd");
    VM_files.push_back("/usr/bin/vmware-checkvm");
	VM_files.push_back("/usr/bin/vmware-toolbox-cmd");
	VM_files.push_back("/usr/bin/vm-support");
	VM_files.push_back("/usr/bin/vmware-hgfsclient");
	VM_files.push_back("/usr/bin/vmtoolsd");
	VM_files.push_back("/sys/kernel/debug/vmmemctl");

	
	for (const auto & file : VM_files){
		if (std::experimental::filesystem::exists(file)){
			//std::cout << "Path " << file << std::endl;
			return true;
		}
	}

	return false;
}

bool vmware_check_mac(){
    std::vector<std::string> poss_mac_addr;
    poss_mac_addr.push_back("00:05:69");
    poss_mac_addr.push_back("00:0c:29");
    poss_mac_addr.push_back("00:1c:14");
    poss_mac_addr.push_back("00:50:56");

	for (std::string mac : poss_mac_addr){
		if (check_mac_addr(mac.c_str())){
			return true;
		}
	}
    return false;
}

bool vmware_check_devices(){
	std::vector<std::string> VM_dev;
    VM_dev.push_back("/dev/vmci");

	for (std::string dev : VM_dev){
		if (std::experimental::filesystem::exists(dev)){
			return true;
		}
	}
	return false;  
}
bool vmware_check_processes(){
	std::string output = "pidof -s ";
	std::vector<std::string> VM_proc;
    VM_proc.push_back("/usr/bin/vmtoolsd");
    VM_proc.push_back("/usr/bin/VGAuthService");
	


	for (std::string proc : VM_proc){
		std::string command = output + proc;
		char line[ 15 ];
		FILE *cmd = popen( command.c_str(), "r");
		fgets( line, 15, cmd );
		pid_t pid = strtoul( line, NULL, 10 );
		pclose(cmd);
		//std::cout << "pid " << pid << std::endl;
		if (pid != 0) {
			return true;
		}
	}
	return false;
}

bool vmware_check_firmware(){
    std::regex vbox("VMware");
	std::smatch result;
	std::string firmware = get_system_firmware();
	std::regex_search(firmware,result,vbox);
	if (!result[0].str().empty())
		return true; // vbox string found
	else 
		return false; // vbox string not found
}