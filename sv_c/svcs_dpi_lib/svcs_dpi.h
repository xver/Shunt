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
#include <svcs_client_server.h>
#include <svcs_user_api.h>

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

//////////////
/*
  Function: svcs_dpi_send_intV
  send SVCS transaction with "int" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
  
  see ( svcs_cs_send_intV )
*/
int svcs_dpi_send_intV   (int sockid, const int size,const svOpenArrayHandle Int);

/*
  Function: svcs_dpi_recv_intV
  fetch SVCS transaction with "int" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  IntV  - Data received
  
  Returns:
  number of elements have been received  : success > 0

*/
int svcs_dpi_recv_intV(int sockid,int size,svOpenArrayHandle Int);
/*
  Function: svcs_dpi_print_intV
  print out IntV Data

  Parameters:

  h - cs_data_header structure
  Int  - Data to print
  msg  - print out prefix

  Returns:
  
  see ( svcs_cs_print_intV )
*/
void svcs_dpi_print_intV   (cs_header* h,int *Int,char* msg);


/*
  Function: svcs_dpi_comp_intV
  compare two intV payloads

  Parameters:
  h - cs_header
  lhs,rhs - intA data
  Returns:
  success > 0

  see ( svcs_cs_comp_intV )
*/
int svcs_dpi_comp_intV   (cs_header* h,int *lhs,int *rhs);


/*
  Function: svcs_dpi_send_realV
  send SVCS transaction with "real" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Real - data
  
  Returns:
  number of elements have been sent  : success > 0

  see ( svcs_cs_send_doubleV )
*/
int svcs_dpi_send_realV   (int sockid,const int size,const svOpenArrayHandle Real);

/*
  Function: svcs_dpi_recv_realV
  fetch SVCS transaction with "real" elements vector from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Real  - Data received
  
  Returns:
  number of elements have been received  : success > 0

  see ( svcs_cs_recv_doubleV )
*/
int svcs_dpi_recv_realV   (int sockid,int size,svOpenArrayHandle Real);

/*
  Function: svcs_dpi_comp_realV
  compare two realV payloads

  Parameters:
  h - cs_header
  lhs,rhs - real V data
  Returns:
  success > 0

  see ( svcs_cs_comp_doubleV )
*/
int svcs_dpi_comp_realV   (cs_header* h,double *lhs,double *rhs);


/*
  Function: svcs_dpi_print_realV
  print out RealV Data

  Parameters:

  h - cs_data_header structure
  Real  - Data received
  msg    - print out prefix

  Returns:
  void

  see ( svcs_cs_print_doubleV )
*/
void svcs_dpi_print_realV   (cs_header* h,double *Real,char* msg);


/*
  Function: svcs_dpi_send_string
  send SVCS transaction with verilog string/C char* elements over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  string  - data to send
  
  Returns:
  number of elements have been sent  : success > 0

  see ( svcs_cs_send_string )
*/
int svcs_dpi_send_string   (int sockid,const cs_header* header,const char* string);

/*
  Function: svcs_dpi_recv_string
  fetch SVCS transaction with verilog string/C char* elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  string  - Data received
  
 Returns:
 number of elements have been received  : success > 0

 see ( svcs_cs_recv_string )
*/

int svcs_dpi_recv_string   (int sockid,cs_header* header,char* string);
/*
  Function: svcs_dpi_comp_string
  compare two char * payloads

  Parameters:
  h - cs_header
  lhs,rhs - string
  Returns:
  success > 0

  see ( svcs_cs_comp_string )
*/
int svcs_dpi_comp_string   (cs_header* h,char *lhs,char *rhs);

#endif /* SVCS_DPI_H_ */
