#include "generic.h"

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

bool mouse_movement_notool(){
    // detect mouse movement, no extra tool required (xdot tool)
    // may require root permission to read from /dev/input/mice
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
            printf("ERROR Opening %s\n", pDevice);
            return -1;
        }
        
        
        while(1)
        {
            // Read Mouse - blocking call until mouse is moved     
            if(read(fd, data, sizeof(data)) > 0)
            {
                // mouse movement detect - we are not in emulator
                return 0;
            }
        }
    }
    else{
        //parent
        sleep(3);
        int status;
        pid_t result = waitpid(p, &status, WNOHANG);
        if ( result == -1 ) {
            perror("waitpid failed");
            return false;
        }
        else if(result == 0){
            // child still alive - no mouse detection -> emulator
            // Mouse not moved, probably we are in VM, return TRUE
            return true;
        }
        else{
            // child process is finished: 
            // status == 0 -> mouse detected
            // status != 0 -> some error (e.g. no permission)
            // Probably we are not in VM, return FALSE
            return false;
        }

    }
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