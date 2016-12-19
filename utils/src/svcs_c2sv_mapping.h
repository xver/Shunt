/* 
 ============================================================================
 File        : svcs_c2sv_mapping.h
 Author      : Victor Besyakov
 Version     : 0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : "C" to "SV" mapping util
               System Verilog client server handshake (SVCS)
==============================================================================
*/

#ifndef SVCS_C2SV_MAPPING_H_
#define SVCS_C2SV_MAPPING_H_

#include  "svcs_client_server.h"

//-------------
//prototypes
//-------------

//Title: Utilites: "C" to System Verilog mapping


//Section: Integer atom type

/*
  (start code)
  shortint
  int
  longint
  byte
  integer 
  time 
  bit
  reg/logic
  (end)

*/

//Section: Integer vector type

/*
bit[N:0]
reg[N:0] or logic[N:0]
logic[N:0]
*/

//Section: Non integer type IEEE 754

/*
shortreal
real
realtime
*/

//Section: Special types

/*
string
string[N]
chandle
Enumeration
*/

//Section: Aggregate data types

/*
Unpacked structures
Packed structures
Unpacked union
Packet  union
Tagged unions
*/

//Section: Arrays

/*
Unpacked arrays
Packed arrays
fixed-size arrays
dynamic arrays
associative arrays
queues
Multidimensional arrays
*/

//Section: Type casting

/*
bit-stream
*/

#endif

