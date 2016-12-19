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
******************************************************
Data Types:
elements:         integer,  double, char
vectors:          integers, doubles , string
array/composite:  integer vectors , double vectors, messages , structure
-------------------------------------------------------
trnx -> header  ->  trnx_atribute  - hash/random double
                    trnx_type      - hash double
                    trnx_id        - random double
        payload -> size - int , >0
                   data
 ============================================================================
 */
#ifndef SVCS_C2SV_MAPPING_H_
#define SVCS_C2SV_MAPPING_H_

#include  "svcs_client_server.h"

#define MY_HOST "localhost"
#define BUFSIZE   1024
#define MAXBUFLEN 1024

//-------------
//prototypes
//-------------

//Title: Utilites: "C" to System Verilog mapping

//Section: Integer atom type

/* shortint */
/* int */
/* longint */
/* byte */
/* integer  */
/* time  */

//Section:  Integer vector type

/* bit[N:0] */
/* reg[N:0]
/* logic[N:0] */

//Section: Non integer type IEEE 754
/* shortreal */
/* real */
/* realtime */

/* string */
/* string[N] */
/* chandle */

//Section: Aggregate data types

/* Unpacked structures */

/* Packed structures */

/* Unpacked union */
/* Packed  union */

/* Unpacked arrays */

/* Packed arrays */

/* enum */

/* fixed-size arrays */
/* dynamic arrays */
/* associative arrays */
/* queues */

/* multi-dimensioned packed/unpacked arrays */
/* bit-stream */



///////////////////////////////
//Section: Example Template DEBUG !!!!!

/*
 Section: TODO

(start code)
   TODO
 (end)

 */

/*
  Function: TODO
  Parameters:
   TODO
 */

 




#endif

