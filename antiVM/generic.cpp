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

bool mouse_movement(){
    /*
    * this function return true if mouse is moved inside a time window of 5 second, false is same position is detected
    * use case: a sandbox or an emulator should be able to emulate the movement of the mouse, a malicious program could disable its malicious functionalities
    * if no mouse movements are detected
    */
    int exitStatus = 0;
	std::string result = execCommand("xdotool getmouselocation", exitStatus);
	sleep(5);
	return result != execCommand("xdotool getmouselocation", exitStatus) ?  true :  false;
}

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

    printf("Proc Count:%d\n", procCount);
    if (procCount < 2)
		return true;
	else
		return false;
}

bool idt_trick()
{
	uint idt_base = get_idt_base();
	if ((idt_base >> 24) == 0xff)
		return true;

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