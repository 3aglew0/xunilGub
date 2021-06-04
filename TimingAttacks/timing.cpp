#include "timing.h"

bool timing_sleep_loop (int delayInMillis)
{
	/* 
	This trick is about performing a low number of seconds to sleep but in a loop,
	the reason behind that sandboxes tries to avoid patching such sleeps is because it
	could lead to race conditions and also because it is just negliable. However,
	when you do it in a loop, you can make the sandboxe to reach its timeout.
	*/

	/* Example: we want to sleep 300 seeconds, then we can sleep
	0.3s for 1000 times which is like: 300 seconds = 5 minues */
	for (int i = 0; i < 1000; i++) 
		usleep(delayInMillis); // 1000*delayInMicros = delayInMillis
    

	// hoping the previous code is able to makes the sandbox reaching its timeout
    // Malicious code goes here

	return false;
}

/*
Another timinig attack using the ping command line which takes a TimeOut 
in second as a parameter, to wait for IPv4 ICMP packets replies.
e.g. ping -w 5 244.0.0.0 >> wait 5 seconds till reply
*/
bool timing_IcmpSendEcho(int delaySeconds)
{
    std::string command = "ping -w ";
    command.append(std::to_string(delaySeconds));
    command.append(" 244.0.0.0 > /dev/null 2>&1");
    int x = system(command.c_str());

    // If the system returns zero, then it means that command processor does not exist and the system() function cannot be called.
    return (x == 0) ? true : false;
}