#include <iostream>
#include <array>
#include "unistd.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <boost/filesystem.hpp>
#include "string.h"


std::string execCommand(const std::string, int&); 
bool mouse_movement_tool();
bool mouse_movement();
bool number_of_processors();
bool idt_trick();
bool ldt_trick();
bool gdt_trick();
bool disk_space();
bool accelerated_sleep();
bool memory_space();
bool model_computer_system();