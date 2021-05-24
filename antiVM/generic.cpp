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