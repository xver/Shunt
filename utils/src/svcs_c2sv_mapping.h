/* 
 ============================================================================
 File        : svcs_c2sv_mapping.h
 Author      : Victor Besyakov
 Version     : 0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : "C" to system verilog mapping util
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
  
  (end)
*/

//Section:  Integer vector type

 /*
   (start code)
   
   bit[N:0] 
   reg[N:0]
   logic[N:0] 
   
   (end)
   
*/

 //Section: Non integer type IEEE 754

 /*
   
 (start code) 
 
 shortreal 
 real 
 realtime 
 
 string 
 string[N] 
 chandle 
 
(end)

 */

 //Section: Aggregate data types

 /*

 (start code) 
 
  Unpacked structures 
  
  Packed structures 
  
  Unpacked union 
  Packed  union 
  
  Unpacked arrays 
  
  Packed arrays 

  enum 
  
  fixed-size arrays 
  dynamic arrays 
  associative arrays 
  queues 
  
  multi-dimensioned packed/unpacked arrays 
  bit-stream 
  
  (end)

 */

#endif

