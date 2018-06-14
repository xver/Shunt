# Welcome to the **SystemVerilog "TCP/IP Shunt"**!

![](https://github.com/xver/Shunt/blob/master/doc/shut_log_min.png)



The **Shunt** is Open Source Client/Server TCP/IP socket based communication library for SystemVerilog simulation.

* It aims to enable quick and easy development of communication between stand-alone SystemVerilog simulations and/or external applications

* It provides a common SystemVerilog/C API and supports mostly all System Verilog data types and data structures.

The **Shunt** is available under a "MIT" License. It can be used without restriction in an open-source or commercial application.

*  Shunt Introduction (TCP/IP Socket Based Communication for SystemVerilog Simulation SNUG, Boston 2018 ): 
https://www.researchgate.net/publication/325206338_TCPIP_Socket_Based_Communication_for_SystemVerilog_Simulation
*  API specification  -- https://rawgit.com/xver/Shunt/master/doc/index.html

# Getting Started

# Library Installation

Download Shunt from https://github.com/xver/Shunt

Setup following variables:
 - **“SHUNT_HOME”**  to the SHUNT home directory.
 - **“SHUNT_SVDPI”** to the location of svdpi.h file

# Library compilation
 - Go to “$SHUNT_HOME/utils/makedir/utils/makedir“
 - Run “make clean;make all”
Compile result will be placed under ***${SHUNT_HOME}/bin as a “libutils.so”***

# Compile and run C examples
Go to example makedir root directory. 
*(Example: $SHUNT_HOME/examples/c/primitives/makedir)*
To compile the library and launch test run “make all”

# Compile and run SV examples
The Shunt includes a complete Makefile structure for the C portion of the library, but ONLY Makefile target place holders for SV domain.

 - Edit “Makefile” initiator/target “compile_sv” under initiator/target
   local makedir(Example: $SHUNT_HOME/examples/sv/sv2c/initiator/makedir)
 - Edit “run” file placeholder. Setup run command for appropriate
   source. Go to example makedir root directory run “make all” and ./run
(Example:  $SHUNT_HOME/examples/sv/sv2cmakedir)

Release History:
-----------------------

1.0.2 (Current Version) - shunt-verilator integration update: 
                          long(longint) header & hash data type 
                          was: real,double is: long,longint
1.0.1  - shunt-verilator integration 
                          Verilator 3.916 2017-11-25 rev verilator_3_916
        
1.0.0 - initial release

-------------------------

If you have any questions please contact us at icshunt.help@gmail.com

!["Copyright (c) 2016 IC Verimeter"](https://github.com/xver/Shunt/blob/master/doc/IcVerimeter_logo.png)

