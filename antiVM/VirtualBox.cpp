#include "pch.h"
#include "VirtualBox.h"

/*
Check virtualbox NIC MAC address
*/
bool vbox_check_mac()
{
	return check_mac_addr("\x08\x00\x27");
}

/*
Check against pseaudo-devices
*/
bool vbox_check_devices(){
	std::vector<std::string> VM_dev;
    VM_dev.push_back("/dev/vboxuser");
    VM_dev.push_back("/dev/vboxguest");

	for (std::string dev : VM_dev){
		if (std::experimental::filesystem::exists(dev)){
			return true;
		}
	}
	return false;  
}


/*
Check against virtualbox blacklisted files
*/
bool vbox_check_files(){
	std::vector<std::string> VM_files;
    VM_files.push_back("/kernel/ubuntu/vbox/vboxguest");
    VM_files.push_back("/kernel/ubuntu/vbox/vboxuser");
	VM_files.push_back("/kernel/ubuntu/vbox/vboxvideo");

	std::string path = "/lib/modules/";
    for (const auto & entry : std::experimental::filesystem::directory_iterator(path)){
		for (const auto & file : VM_files){
			std::string path = entry.path();
			path += file;
			//std::cout << "Path " << path << std::endl;
			if (std::experimental::filesystem::exists(path)){
				return true;
			}
		}

	}
	return false;

}


bool vbox_check_processes(){
	std::string output = "pidof -s ";
	std::vector<std::string> VM_proc;
    VM_proc.push_back("/usr/bin/VBoxClient");
    VM_proc.push_back("/usr/bin/VBoxClient-all");
	VM_proc.push_back("/usr/bin/VBoxControl");

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

bool vbox_check_firmware(){
	std::regex vbox("VirtualBox|vbox|VBOX");
	std::smatch result;
	std::string firmware = get_system_firmware();
	std::regex_search(firmware,result,vbox);
	if (!result[0].str().empty())
		return true; // vbox string found
	else 
		return false; // vbox string not found
}