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
//Title: 6. DPI Direct Link

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

/*
 Function: svcs_dpi_send_byte
  send verilog "byte"/C "char" over TCP/IP

  Parameters:
   sockfd - socket id
   Byte  - data to send

  Returns:
    number of bytes have been sent : success =1

    see (svcs_prim_send_byte)
*/

int svcs_dpi_send_byte    (const unsigned int sockfd,const char Byte);

/*
  Function: svcs_dpi_recv_byte
  fetch verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Byte - data from socket

  Returns:
 number of bytes have been sent : success = 1

    see (svcs_prim_recv_byte)
*/
int svcs_dpi_recv_byte    (const unsigned int sockfd,char* Byte);

/*
  Function: svcs_dpi_send_intV
  send SVCS transaction with "int" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  size   - number of vector elements
  Int    - data
  
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
  size - number of vector elements
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
  Function: svcs_dpi_send_realV
  send SVCS transaction with "real" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of vector elements
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
  size - number of vector elements
  Real  - Data received
  
  Returns:
  number of elements have been received  : success > 0

  see ( svcs_cs_recv_doubleV )
*/
int svcs_dpi_recv_realV   (int sockid,int size,svOpenArrayHandle Real);


/*
  Function: svcs_dpi_send_string
  send SVCS transaction with verilog string/C char* elements over TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of string elements
  string  - data to send
  
  Returns:
  number of elements have been sent  : success > 0

  see ( svcs_cs_send_string )
*/
int svcs_dpi_send_string   (int sockid,int size,char* string);

/*
  Function: svcs_dpi_recv_string
  fetch SVCS transaction with verilog string/C char* elements from TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of string elements
  string  - Data received
  
 Returns:
 number of elements have been received  : success > 0

 see ( svcs_cs_recv_string )
*/

int svcs_dpi_recv_string   (int sockid,int size,char** string);

//////////////////////

/*
  Function: svcs_dpi_hash 
  simple hash function 
  
  Parameters: 
  str - hash key
  
  Returns: 
  hash value
*/

double svcs_dpi_hash(const char *str);

/*
  Function: svcs_dpi_send_header
  send SVCS header over TCP/IP
  
  Parameters:
  
  sockid - socket id from init sever/client 
  h - cs_header structure
  
  Returns:
  
  number of elements have been sent  : success > 0
*/

int svcs_dpi_send_header    (int sockid,cs_header* h);

/*
  Function: svcs_dpi_send_data_header
  send SVCS header over TCP/IP
  
  Parameters:
  
  sockid - socket id from init sever/client 
  h - cs_header structure
  n_payloads - number of data payloads
  
  Returns:
  
  number of elements have been sent  : success > 0
*/
//int svcs_dpi_send_data_header    (int sockid,cs_header* h,double data_type,int* trnx_payload_sizes);
int svcs_dpi_send_data_header (int sockid,cs_header* h,double data_type,svOpenArrayHandle trnx_payload_sizes);
/*
  Function: svcs_dpi_recv_header
  fetch SVCS transaction header from TCP/IP socket
  
  Parameters:
  
  sockid - socket id from init sever/client 
  header - cs_header structure
  
  Returns:
  
  number of elements have been received  : success > 0
  
*/
int svcs_dpi_recv_header   (int sockid,cs_header* h);

/*
  Function: svcs_dpi_recv_data_header
  fetch SVCS transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int svcs_dpi_recv_data_header   (int sockid,cs_header* h,double* data_type,svOpenArrayHandle**  trnx_payload_sizes);
/*
  Function: svcs_dpi_hs_send

  send data over TCP/IP.
  Supported data types are:
  int , intV ,double ,doubleV

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


int svcs_dpi_hs_send      (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int svcs_dpi_hs_send_int  (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int svcs_dpi_hs_send_byte (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int svcs_dpi_hs_send_real (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);

/*
  Function: svcs_dpi_hs_recv
  fetch data from TCP/IP socket
  Supported data types are:
  int , intV ,double ,doubleV,string,

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
int svcs_dpi_hs_recv      (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int svcs_dpi_hs_recv_int  (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int svcs_dpi_hs_recv_byte (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int svcs_dpi_hs_recv_real (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);

/*
 Function: svcs_dpi_4state_send_byte
  send 4-stae verilog "byte" over TCP/IP

  Parameters:
   sockfd - socket id
   Byte  - data to send

  Returns:
    number of 4 state variable byte size have been sent : success =1

    see (svcs_prim_send_byte)
*/
int svcs_dpi_hs_send_byte4s (const unsigned int sockfd,svLogicVecVal* Byte);

/*
 Function: svcs_dpi_4state_recv_byte
  recv 4-stae verilog "byte" over TCP/IP

  Parameters:
   sockfd - socket id
   Byte  - data to recv

  Returns:
    number of 4 state variable byte size have been sent : success =1

    see (svcs_prim_recv_byte)
*/
int svcs_dpi_hs_recv_byte4s (const unsigned int sockfd,svLogicVecVal** Byte);

#endif /* SVCS_DPI_H_ */
