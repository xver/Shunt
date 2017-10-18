/* 
 =========================================================
 File        : shunt_user_api.h
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : User API  for 
               System Verilog client server handshake (TCP/IP SystemVerilog SHUNT)
******************************************************
 */

#ifndef SHUNT_USER_API_H_
#define SHUNT_USER_API_H_

#include "shunt_client_server.h"
#include "shunt_primitives.h"

//-------------
//prototypes
//-------------

//Title: Utilites: USER API

//Section: Data exchange utilities (API)
/*
  Topics: Supported cs_header_t data_types and corresponding verilog data types are(element and vectors):
  
  
  *Integer 2 states:*
  
  SHUNT_INT         - int
  SHUNT_SHORTINT    - shortint
  SHUNT_LONGINT     - longint
  SHUNT_BYTE        - byte
  SHUNT_BIT         - bit
  
  *Integer 4 states:*
  
  SHUNT_INTEGER     - integer,time
  SHUNT_REG         - reg,logic
  
  *Non integer types IEEE 754:*
  
  SHUNT_REAL        - real,realtime
  SHUNT_SHORTREAL   - shortreal
  SHUNT_STRING      - string
  
  SHUNT_A_STRUCTURE - N/A complex data types/user defined data types : arrays/struct,union,enums 
  SHUNT_HEADER_ONLY - cs_header_t header only. 
*/

/*
  Function: shunt_api_send
  
  send data over TCP/IP.
  
  Parameters:
  
  Perm parameters:
  
   sockid - socket id from init sever/client 
   h_trnx - cs_header structure
   
   Non-perm  parameters are:
 
   Int,Double,String - data to send
      
   Returns:

   number of elements have been sent  : success > 0
*/
int shunt_api_send    (int sockid,cs_header* h_trnx, ...);

/*
  Function: shunt_api_recv
  fetch data from TCP/IP socket
  
  Parameters:
  
  Perm parameters:
  
  sockid - socket id from init sever/client 
  h_trnx - cs_header structure
  
  Non-perm  parameters are:
 
  Int,Double,String - Data received
   
  Returns:
  number of elements have been received  : success > 0
*/
int shunt_api_recv (int sockid,cs_header* h_trnx, ...);

#endif





