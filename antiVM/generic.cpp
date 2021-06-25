#include "generic.h"
#include "pch.h"

std::string execCommand(const std::string cmd, int& out_exitStatus)
{
    out_exitStatus = 0;
    auto pPipe = ::popen(cmd.c_str(), "r");
    if(pPipe == nullptr)
    {
        throw std::runtime_error("Cannot open pipe");
    }

    std::array<char, 256> buffer;

    std::string result;

    while(not std::feof(pPipe))
    {
        auto bytes = std::fread(buffer.data(), 1, buffer.size(), pPipe);
        result.append(buffer.data(), bytes);
    }

    auto rc = ::pclose(pPipe);

    if(WIFEXITED(rc))
    {
        out_exitStatus = WEXITSTATUS(rc);
    }

    return result;
}

bool mouse_movement_tool(){
    /*
    * to use this function must have installed xdotool (sdo apt install xdotool)
    * this function return true if mouse is moved inside a time window of 5 second, false is same position is detected
    * use case: a sandbox or an emulator should be able to emulate the movement of the mouse, a malicious program could disable its malicious functionalities
    * if no mouse movements are detected
    */
    int exitStatus = 0;
	std::string result = execCommand("xdotool getmouselocation", exitStatus);
	sleep(5);
	return result != execCommand("xdotool getmouselocation", exitStatus) ?  false :  true;
}

// detect mouse movement, no extra tool required (xdot tool)
// may require root permission to read from /dev/input/mice
// if no mouse movement detected in 5 seconds means no user interaction, probably 
// we are in sandbox -> return TRUE, 
bool mouse_movement(){
    int p = fork();
    if(p < 0){
        // error
        return -1;
    }
    else if(p == 0){
        // child
        int fd;
        unsigned char data[3];

        const char *pDevice = "/dev/input/mice";

        // Open Mouse
        fd = open(pDevice, O_RDWR);
        if(fd == -1)
        {
            std::cout << RED "ERROR Opening " << pDevice << " - " NC ;
            exit(-1);
        }
        
        
        while(1)
        {
            // Read Mouse - blocking call until mouse is moved     
            if(read(fd, data, sizeof(data)) > 0)
            {
                // mouse movement detect - we are not in emulator
                exit(0);
            }
        }
    }
    else{
        //parent
        sleep(1);
        int status;
        pid_t result = waitpid(p, &status, WNOHANG);
        if ( result == -1 ) {
            perror("waitpid failed");
            return false;
        }
        else if(result == 0){
            // child still alive - no mouse detection -> emulator
            // Mouse not moved, probably we are in VM, return TRUE
            kill(p, SIGKILL);
            return true;
        }
        else{
            // child process is finished: 
            // status == 0 -> mouse detected
            // status != 0 -> some error (e.g. no permission)
            // Probably we are not in VM, return FALSE
            return (status != 0);
        }

    }
}

/*
/ Count number of processors and check if less then 2
*/
bool number_of_processors() {
    char str[256];
    int procCount = 0;
    FILE *fp;

    if( (fp = fopen("/proc/cpuinfo", "r")) ) {
        while(fgets(str, sizeof str, fp))
            if( !memcmp(str, "processor", 9) ) 
                procCount++;
    }

    if ( !procCount ) { 
        printf("Unable to get proc count. Defaulting to 2");
        procCount=2;
    }

    //printf("Proc Count:%d\n", procCount);
    if (procCount < 2)
		return true;
	else
		return false;
}

bool idt_trick()
{
	uint idt_base = get_idt_base();
	if ((idt_base >> 24) == 0xff)
		return true; // VMvare detected

	else
		return false;
}

/*
Same for Local Descriptor Table (LDT)
*/
bool ldt_trick()
{
	uint ldt_base = get_ldt_base();

	if (ldt_base == 0xdead0000)
		return false;
	else
		return true; // VMWare detected	
}


/*
Same for Global Descriptor Table (GDT)
*/
bool gdt_trick()
{
	uint gdt_base = get_gdt_base();

	if ((gdt_base >> 24) == 0xff)
		return true; // VMWare detected	

	else
		return false;
}


/*
Check if the machine have enough memory space, usually VM get a small ammount,
one reason if because several VMs are running on the same servers so they can run
more tasks at the same time.
heuristically we say that VM has 2GB
*/
bool disk_space()
{
    int minHardDiskSize_gb = 80;
    boost::filesystem::space_info si = boost::filesystem::space(".");
    float gb = si.capacity / (1000*1000*1000);
    // std::cout << "Your system has GB " << gb << std::endl;
    return (gb <= 80); // return TRUE if space is that one of VM --> VM Detected

}

/*
Sleep and check if time have been accelerated
*/
bool accelerated_sleep()
{
	time_t dwStart = 0, dwEnd = 0, dwDiff = 0;
	int second_to_sleep =2;
    
    struct timespec ts;
    if(clock_gettime(CLOCK_MONOTONIC,&ts) != 0)
        // errror
        return false;

    dwStart = ts.tv_sec;
    sleep(second_to_sleep);
    if(clock_gettime(CLOCK_MONOTONIC,&ts) != 0)
        // error
        return false; 
    dwEnd = ts.tv_sec;
    dwDiff = dwEnd - dwStart;
    // /* If the Sleep function was patched*/
	dwDiff = dwEnd - dwStart;

	if (dwDiff >= second_to_sleep - 2) // substracted 2s just to be sure
		return false; // pass --> probably I am in normal system, no accelleration mecanishm  
	else
		return true; // bad --> probably I am not in normal system because accelleration mecanishm detected (sleep function has been accellerated)

}

/*
/  Check if RAM is less then 2 GB
*/
bool memory_space() {
    unsigned long mem_total = 0;
    
    mem_total = get_mem_total() ;
    float mem = mem_total / ((1024) * (1024));
    //std::cout << mem << std::endl;

    return (mem <= 2);
}

/*
/  Check if sys_vendor contains keywords of VMs
*/
bool model_computer_system(){
    char str[256];
    FILE *fp;

    std::vector<std::string> VM_names;
    VM_names.push_back("VirtualBox");
    VM_names.push_back("HVM domU");
    VM_names.push_back("VMWare");

    if( (fp = fopen("/sys/devices/virtual/dmi/id/sys_vendor", "r")) ) {
        fgets(str, sizeof(str), fp);
        for (std::string el : VM_names){
            if (std::string(str).find(el) != std::string::npos){
                return true;
            }
        }
        return false;
    }
    return false;
}   