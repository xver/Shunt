/*
=======svcs_cs==================================================
 File        : svcs_dpi.h
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : svcs dpi bridge
               System Verilog client server handshake (SVCS) library
******************************************************
*/
#ifndef SVCS_DPI_H_
#define SVCS_DPI_H_

#include <svdpi.h>
#include <svcs_primitives.h>
#include "svcs_user_api.h"

//-------------
//prototype
//-------------
//Title: 6. DPI

//Section: TCP/IP socket Client , Server initialization

/*
 Function: svcs_dpi_client_init 
 TCP/IP client initialization
 
 Parameters:
 
 portno   - socket port
 hostname - server name
 
 Returns: 
 socket id 
 
see (svcs_prim_init_tcpclient )  
*/
unsigned int svcs_dpi_client_init(const unsigned int portno,const char *hostname);

/*
 Function: svcs_dpi_server_init 
 TCP/IP server initialization
 
 Parameters: 
 portno - socket port
  
 Returns:  
 socket id
 
 see (svcs_prim_init_tcpserver)   
*/
unsigned int svcs_dpi_server_init(const unsigned int portno);

/*
 Function: svcs_dpi_send_int
  send verilog/C "int" data over TCP/IP

  Parameters:
   sockfd - socket id
   Int  -   data

  Returns:
   number of bytes have been sent : success > 0
   see (vcs_prim_send_int)

*/
int svcs_dpi_send_int    (const unsigned int sockfd,const int Int);

/*
 Function: svcs_dpi_recv_int
  fetch verilog/C "int" data from TCP/IP socket

  Parameters:
   sockfd - socket id
   Int - data from socket

  Returns:
    number of bytes have been received  : success > 0

    see (svcs_prim_recv_in)
*/
int svcs_dpi_recv_int (const unsigned int sockfd,int* Int);

/*
 Function: svcs_dpi_send_real
  send verilog "real"/C "double" over TCP/IP

  Parameters:
   sockfd - socket id
   Real  - data to send

  Returns:
    number of bytes have been sent : success > 0

    see (svcs_prim_send_double)
*/

int svcs_dpi_send_real    (const unsigned int sockfd,const double Real);

/*
  Function: svcs_dpi_recv_real
  fetch verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real - data from socket

  Returns:
 number of bytes have been sent : success > 0

    see (svcs_prim_recv_double)
*/
int svcs_dpi_recv_real    (const unsigned int sockfd,double* Real);

#endif /* SVCS_DPI_H_ */
