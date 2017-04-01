/* 
 =======svcs_cs==================================================
 File        : svcs_user_api.h
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : User API  for 
               System Verilog client server handshake (SVCS)
******************************************************
 */

#ifndef SVCS_USER_API_H_
#define SVCS_USER_API_H_

#include "svcs_client_server.h"
#include "svcs_primitives.h"

//-------------
//prototypes
//-------------

//Title: 5. Utilites: USER API

//Section: Data exchange utilities (API)


/*
  Function: svcs_api_send
  
  send data over TCP/IP.
  Supported data types are:
  int , intV ,IntA ,double ,doublev ,DoubleA,string,stringA 
  
  Parameters:
  
  Perm parameters:  
   sockid - socket id from init sever/client 
   h_trnx - cs_header structure
   
   Non-perm  parameters are: 
   h_data - cs_data_header  structure
   Int,Double,String - data to send
   
   
   Returns:
  number of elements have been sent  : success > 0
*/

int svcs_api_send    (int sockid,cs_header* h_trnx, ...);

/*
  Function: svcs_api_recv
  fetch data from TCP/IP socket
  Supported data types are:
  int , intV ,IntA ,double ,doublev ,DoubleA,string,stringA 
  
  Parameters:
  
  Perm parameters:  
  sockid - socket id from init sever/client 
  h_trnx - cs_header structure
  
  Non-perm  parameters are: 
  h_data - cs_data_header  structure
  Int,Double,String - Data received
  
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int svcs_api_recv (int sockid,cs_header* h_trnx, ...);

#endif





