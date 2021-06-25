# Content
- [Introduction](#introduction)
- [Download, Installation and Run](#download,installationandrun)
- [Usage](#usage)
- [Features](#features)
- [Authors](#authors)

# Introduction
xunilGub is a PoC "malware" application with good intentions that aims to stress your anti-malware system. It performs a bunch of common malware tricks with the goal of seeing if you stay under the radar.

[metti foto]

# Download, Installation and Run
1. Update the system

    `sudo apt update -y`

2. Install the following dependencies for complete usage of xunilGub

    `sudo apt install xdotool`

    `sudo apt install libboost-filesystem-dev`
3. Download the source code from this github 
    
    `git clone https://github.com/3aglew0/xunilGub.git`

    `cd xunilGub`
4. To compile the project: `make`
5. To run the executable `make run`
    
    XunilGub performs some check only if it is run with super user privileges, i.e. you need to run `sudo make run`

# Usage

* You are making an anti-debug plugin and you want to check its effectiveness.
* You want to ensure that your sandbox solution is hidden enough.

    e.g. A sandbox should be able to simulate typical user behaviours, if the malware can detect there are no such behaves, it could disable its malicious functionalities. 

* Or you want to ensure that your malware analysis environment is well hidden.

Please, if you encounter any of the anti-analysis tricks which you have seen in a malware, don't hesitate to contribute.

# Features
- Debugger Detection (via *debugmenot*)
    - Ptrace (debug itself)
    - Vdso
    - Check for ASLR
    - Parent name
    - Near Heap
    - Existence of special ENV variables

- Sandbox Detection
    - Mouse movement 1
    - Mouse Movement 2
    - Number of processors
    - IDT location
    - LDT location
    - GDT location
    - Disk space
    - Time accellerated
    - Memory RAM space
    - Model Vendor Name

- Virtual Box Detection
    - Mac Address
    - Pseudo Device
    - VBox Files
    - VBox Firmware
    - VBox Processors

- VMWare Detection
    - Mac Address
    - Pseudo Device
    - VMWare Files
    - VMWare Firmware
    - VMWare Processors

- Qemu Detection
    - Qemu Firmware

- Xen Detection
    - Mac Address

- Timing attacks
    - For sleep
    - Sleep via ping

- Anti disassembler checks
    - No check, perform some anti dissasbler trick to mess with Disassbler

# Authors
- @3aglow0 (Noemi)
- @ciastron (Marco)