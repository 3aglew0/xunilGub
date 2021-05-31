#include <iostream>
#include <array>
#include "unistd.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

std::string execCommand(const std::string, int&); 
bool mouse_movement();
bool mouse_movement_notool();