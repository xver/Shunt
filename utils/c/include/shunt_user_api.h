/*
 =========================================================
 File        : shunt_user_api.h
 Version     : 1.0.0
 Copyright (c) 2016-2023 IC Verimeter. All rights reserved.
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

//Title: Utilities: USER API

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

  variadic function,send data over TCP/IP.

  Parameters:

  *Named arguments* :

  sockid - socket id from init sever/client
  h_trnx - cs_header structure

  *Unnamed arguments* :

   - int*;
   - short int*;
   - shunt_long_t  int*;
   - svLogicVecVal* (Integer,Reg);
   - svBitVecVal*   (Bit);
   - double*;
   - float*;
   - char*         (String);

   Returns:

   number of elements have been sent  : success > 0
*/
INLINE int shunt_api_send    (int sockid,cs_header* h_trnx, ...);

/*
  Function: shunt_api_recv
  variadic function,fetch data from TCP/IP socket

  Parameters:

  *Named arguments* :

  sockid - socket id from init sever/client
  h_trnx - cs_header structure


  *Unnamed arguments* :

  - int*;
  - short int*;
  - shunt_long_t  int*;
  - svLogicVecVal* (Integer,Reg);
  - svBitVecVal*   (Bit);
  - double*;
  - float*;
  - char*         (String);


  Returns:
  number of elements have been received  : success > 0
*/
INLINE int shunt_api_recv (int sockid,cs_header* h_trnx, ...);

//Section: Fixed size packet communication Data exchange (API)

/*
  Function: shunt_pkt_send_longV
  send fixed size packet ( SHUNT cs_header + "longint" data payload vector) over TCP/IP

  Parameters:

  sockid - socket id from init sever/client
  h_trnx - cs_header structure
  longV - data payload

  Returns:
  number of elements have been sent  : success > 0
*/
INLINE int shunt_pkt_send_longV  (int sockid, const cs_header* header,const shunt_long_t* Long);

/*
  Function: shunt_pkt_rcv_longV
  fetch fixed size packet (SHUNT cs_header + "longint" data payload vector) over TCP/IP

  Parameters:

  sockid - socket id from init sever/client
  h_trnx - cs_header structure
  longV -  data payload

  Returns:
  number of elements have been received  : success > 0
*/
INLINE int shunt_pkt_recv_longV  (int sockid, cs_header* header,shunt_long_t* Long);

#endif





