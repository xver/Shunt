# Welcome to the **SystemVerilog/SystemC/Python "TCP/IP Shunt"**! [![](https://img.shields.io/static/v1?label=Sponsor&message=%E2%9D%A4&logo=GitHub&color=%23fe8e86)](https://github.com/sponsors/xver)

![](https://github.com/xver/Shunt/blob/master/doc/shut_log_min.png)


The **Shunt** is an Open Source Client/Server TCP/IP socket-based communication library designed for integrating **SystemVerilog** simulations with external applications in **C**, **SystemC**, and **Python**.

* It aims to enable quick and easy development of communication between stand-alone SystemVerilog/SystemC simulations and/or external applications

* It provides a common SystemVerilog/C API and supports mostly all System Verilog data types and data structures.

The **Shunt** is available under a "MIT" License. It can be used without restriction in an open-source or commercial application.

### Articles/Conference papers
*  Shunt Introduction:
   - Victor Besyakov "TCP/IP Socket Based Communication for SystemVerilog Simulation" SNUG, Boston 2018 
   https://www.researchgate.net/publication/325206338_TCPIP_Socket_Based_Communication_for_SystemVerilog_Simulation
*  Shunt Applications:
   - Rob Grant, Victor Besyakov, Adrian Amanci, Jingting Liu "A HYBRID CO-SIMULATION FRAMEWORK FOR SUBSYSTEM FIRMWARE DEVELOPMENT" SNUG, US 2024
   https://www.researchgate.net/publication/379329186_A_HYBRID_CO-SIMULATION_FRAMEWORK_FOR_SUBSYSTEM_FIRMWARE_DEVELOPMENT

   - Victor Besyakov "Enhanced Dynamic Hybrid Simulation Framework for Hardware-Software Verification" DVCon, US 2023
   https://www.researchgate.net/publication/359009820_Enhanced_Dynamic_Hybrid_Simulation_Framework_for_Hardware-Software_Verification

### Shunt documentation
*  API specification  -- https://raw.githack.com/xver/Shunt/master/doc/index.html

### Commercial support
Starting from version 2.2.0, **"IC VERIMETER"** is pleased to announce the availability of commercial support. 
Whether you need assistance with the **Shunt** integration into your project or customization, please contact us at icshunt.help@gmail.com

We have received numerous requests for new features and extensions beyond the initial scope of the product. To continue to keep "TCP/IP Shunt" as an open tool and address all extension requests, we are seeking funding to support the project's growth and development.
You can support us through this link:  [:heart: Sponsor](https://github.com/sponsors/xver)

#### Please, report bugs to [Issues](https://github.com/xver/Shunt/issues).


# Getting Started [![](https://img.shields.io/static/v1?label=Sponsor&message=%E2%9D%A4&logo=GitHub&color=%23fe8e86)](https://github.com/sponsors/xver)
### Install the following  prerequisites:

- Verilator up to 5.019 : https://www.veripool.org/verilator/
- SystemC up to 2.3.3  -Accellera : https://systemc.org/resources/standards/
- Python3 up to Python 3.10.12

### Library Installation

Download Shunt from https://github.com/xver/Shunt

Setup following variables:
 - **“SHUNT_HOME”**  to the SHUNT home directory.
 - **“SHUNT_SVDPI”** to the location of svdpi.h file

### Library compilation
 - cd to ``` $SHUNT_HOME/utils/makedir/ ```
 - run  ``` make clean;make all ```
Compile result will be placed under ***${SHUNT_HOME}/bin with dpi:“libutils.so” and without dpi:”libCutils.so”*** 

NOTE: use the USER_OPT to add compiler options. (Example **all debug options:**  ```make USER_OPT='-g3 -DSHUNT_CLIENT_SERVER_C_DEBUG -DSHUNT_TLM_DEBUG -DSHUNT_DPI_C_DEBUG -DSHUNT_PRIMITIVES_C_DEBUG')  ```

### Compile and run all examples (SV/C/SC/PY)
- cd to ```$SHUNT_HOME/examples/makedir```
- run ```./run_examples ``` or ```./run_examples_debug ``` 

### Compile and run Python examples
- cd  to example makedir root directory. (Example: ``` $SHUNT_HOME/examples/py/sv2py/makedir ```)
- To compile the library and launch test run ```./run ``

### Compile and run C examples
- cd  to example makedir root directory. (Example: ``` $SHUNT_HOME/examples/c/primitives/makedir ```)
- To compile the library and launch test run ``` make all ```

### Compile and run SV examples
 - cd  to example makedir root directory. (Example: ``` $SHUNT_HOME/examples/sv/sv2c/makedir/```)
-  To compile the library and launch test run ```./run```
 
### TLM-2.0 over TCP/IP "loosely timed model"  SystemC-to-SystemC and SystemC-to-SV examples 

SystemC to SystemC  b_transport over TCP/IP :  
 - cd to ```$SHUNT_HOME/examples/sc/LT_simple_cs/makedir``` 
 - run  ```make all```

SystemC to SV  b_transport over TCP/IP :
 - cd to ```$SHUNT_HOME/examples/sc/LT_simple_sv/makedir ```
 - run  ```make all```
 
# Release History: [![](https://img.shields.io/static/v1?label=Sponsor&message=%E2%9D%A4&logo=GitHub&color=%23fe8e86)](https://github.com/sponsors/xver)
-----------------------
v3.0.0 (Current Version) System Verilog - Python integration

v2.3.0 - Regression mode support: Simultaneous allocation of TCP/IP ports.

v2.2.1 - cumulative updates: c++ namespaces no extern "C" & minor cosmetic updates

v2.2.0 - The ARM AXI (Advanced eXtensible Interface) bus support & cumulative bug fixes, cleanups, and updates. 
 
2.1.2 -  Cumulative release: cleanup & SystemC related fixes

2.1.1 - SystemC compile/link cleanup: tab & trailing whitespaces, c++ compile/link -Wall -Werror -Wpedantic -Wextra -Wno-odr

2.1.0  - System Verilog TLM-2.0 generic payload over TCP/IP  

2.0.0 - SystemC TLM-2.0 over TCP/IP 

1.2.0 - TCP/IP optimization ,new fixed size packet communication functions,big/little endian support.examples and doc updates

1.1.2 - various accumulated fixes and verilator 4.20 support  

1.1.1 - TCP/IP socket manipulation: block/unblock , tcp delay/nodelay, get socket status

1.1.0 - TCP/IP socket manipulation: new Multi-Slave support and close socket functions

1.0.3 - API docs update  

1.0.2  - shunt-verilator integration update: 
                          long(longint) header & hash data type 
                          was: real,double is: long,longint
                          
1.0.1  - shunt-verilator integration 
                          Verilator 3.916 2017-11-25 rev verilator_3_916
        
1.0.0 - initial release

-------------------------
!["Copyright (c) 2023 IC Verimeter"](https://github.com/xver/Shunt/blob/master/doc/IcVerimeter_logo.png)
Copyright (c) 2016-2023 IC Verimeter
 
 [![](https://img.shields.io/static/v1?label=Sponsor&message=%E2%9D%A4&logo=GitHub&color=%23fe8e86)](https://github.com/sponsors/xver)
