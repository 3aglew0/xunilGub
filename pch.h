// this file contains all the imports of the headers

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here



#include <string>
#include <vector>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>
#include <algorithm>
#include <cctype>
#include <experimental/filesystem>
#include <regex>

#include "shared/Utils.h"

#include "antiVM/generic.h"
#include "antiVM/VirtualBox.h"
#include "antiVM/Qemu.h"
#include "antiVM/VMWare.h"
#include "TimingAttacks/timing.h"
#include "AntiDisassm/AntiDisassm.h"

#endif //PCH_H