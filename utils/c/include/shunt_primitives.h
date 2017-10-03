/* 
 ============================================================================
 File        : shunt_primitives.h
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : target-initiator primitive(basic) utils
               System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)
******************************************************
Verilog Data Types elements: 

Integer 2 states:
SHUNT_INT         - int            function :shunt_prim_xxxx_intV
SHUNT_SHORTINT    - shortint       function :shunt_prim_xxxx_shortV
SHUNT_LONGINT     - longint        function :shunt_prim_xxxx_long
SHUNT_BYTE        - byte           function :shunt_prim_xxxx_byte
SHUNT_BIT         - bit            function :N/A see shunt_client_server.c shunt_cs_xxx_bitN

Integer 4 states:
SHUNT_INTEGER     - integer,time   function :shunt_prim_xxxx_integer
SHUNT_REG         - reg,logic      function :N/A see  shunt_client_server.c shunt_cs_xxx_regN

Non integer types IEEE 754:  
SHUNT_REAL        - real,realtime  function :shunt_prim_xxxx_double
SHUNT_SHORTREAL   - shortreal      function :shunt_prim_xxxx_float
SHUNT_STRING      - string (N/A)   function :shunt_client_server.c shunt_cs_xxx_byteV

SHUNT_A_STRUCTURE - complex data types/user defined data types : arrays/struct,union,enums (N/A)
SHUNT_HEADER_ONLY - cs_header_t header only                                                (N/A)    
 ============================================================================
 */

#ifndef  SHUNT_PRIMITIVES_H
#define  SHUNT_PRIMITIVES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <stdarg.h>
#include <stdint.h>

#ifdef SHUNT_SVDPI
#include "svdpi.h"

#else
#ifndef INCLUDED_SVDPI

typedef uint8_t svScalar;
typedef svScalar svLogic; /* scalar */
typedef svScalar svBit; /* scalar */
typedef uint32_t svBitVecVal;
typedef void* svOpenArrayHandle;

typedef struct t_vpi_vecval {
uint32_t aval;
uint32_t bval;
} s_vpi_vecval, *p_vpi_vecval;
typedef s_vpi_vecval svLogicVecVal;
#endif
#endif

//-------------
//prototypes
//-------------

//Title: Client-Server Primitives

  
///////////////////////////////
//Section:  Common Functions 

/*
  Function: shunt_prim_hash 
  simple hash function 
  
  Parameters: 
  str - hash key
  
  Returns: 
  hash value
*/
double shunt_prim_hash(const char *str);

/*
  Function: shunt_prim_error 
  perror wrapper
 
  Parameters:
  str - error message
  
  Returns: 
  void
 */
void shunt_prim_error(char *msg);

/////////////////////////////
//Section: TCP/IP Functions

#if 0
/*
 * Structs exported from in.h
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr;
};

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif
/*
 Function: shunt_prim_init_initiator
 TCP/IP initiator initialization
 
 Parameters: 
 portno - socket port
  
 Returns:  
 socket id
   
*/
int shunt_prim_init_initiator(const unsigned int portno);

/*
 Function: shunt_prim_init_target
 TCP/IP target initialization
 
 Parameters:
 
 portno - socket port
 hostname - initiator name
 
 Returns: 
 socket id 
   
*/
unsigned int shunt_prim_init_target(const unsigned int portno,const char *hostname);

/*
Function: Example:  target,initiator init

(start code)    
 #define MY_HOST "localhost"
 #define MY_PORT  3450
 char* hostname; 
 int port;
 port = MY_PORT;
 hostname =   MY_HOST;
  
 shunt_prim_init_initiator(port);
 shunt_prim_init_target(port,hostname);
(end)
 */


//Section: Data exchange primitives


/*
 Function: shunt_prim_send_int
  send verilog/C "int" data over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Int  -   data
  
  Returns:
   number of bytes have been sent : success > 0
*/
int shunt_prim_send_int    (const int sockfd,const int* Int);

/*
 Function: shunt_prim_recv_int
  fetch verilog/C "int" data from TCP/IP socket
  
  Parameters:
   sockfd - socket id
   Int - data from socket 
     
  Returns: 
    number of bytes have been received  : success > 0
    
*/
int shunt_prim_recv_int    (const int sockfd,int* Int);

/*
 Function: shunt_prim_send_double
  send verilog "real"/"shortreal"/"realtime"/C "double"/"float","double" over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Double  - data to send
  
  Returns:
    number of bytes have been sent : success > 0
*/

int shunt_prim_send_double    (const int sockfd,const double* Double);
int shunt_prim_send_float     (const int sockfd,const float* Float);
/*
  Function: shunt_prim_recv_double
  fetch verilog "real"/"shortreal"/"realtime"/C "double"/"float","double" from TCP/IP 
  
  Parameters:
  sockfd - socket id
  Double - data from socket 
  
  Returns: 
 number of bytes have been sent : success > 0
    
*/
int shunt_prim_recv_double   (const int sockfd,double* Double);
int shunt_prim_recv_float    (const int sockfd,float* Float);

/*
 Function: shunt_prim_send_short
  send verilog "shortint"/C "short int" over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Short  - data to send
  
  Returns:
    number of bytes have been sent : success > 0
*/

int shunt_prim_send_short (const int sockfd,const short int* Short);

/*
  Function: shunt_prim_recv_short
  fetch verilog "shortint"/C "short int" over TCP/IP 
  
  Parameters:
  sockfd - socket id
  Short - data from socket 
  
  Returns: 
 number of bytes have been sent : success > 0
    
*/
int shunt_prim_recv_short    (const int sockfd,short int* Short);


/*
 Function: shunt_prim_send_long
  send verilog "longint"/C "long int" over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Long  - data to send
  
  Returns:
    number of bytes have been sent : success > 0
*/

int shunt_prim_send_long    (const int sockfd,const long int* Long);

/*
  Function: shunt_prim_recv_long
  fetch verilog "longint"/C "long int" over TCP/IP 
  
  Parameters:
  sockfd - socket id
  Long - data from socket 
  
  Returns: 
 number of bytes have been sent : success > 0
    
*/
int shunt_prim_recv_long    (const int sockfd,long int* Long);

/*
 Function: shunt_prim_send_byte
  send verilog/C "Byte/Char" data over TCP/IP

  Parameters:
   sockfd - socket id
   Byte  -   data

  Returns:
   number of bytes have been sent : success > 0
*/
int shunt_prim_send_byte    (const int sockfd,const char* Byte);

/*
 Function: shunt_prim_recv_byte
  fetch verilog/C "Byte/Char" data from TCP/IP socket

  Parameters:
   sockfd - socket id
   Byte - data from socket

  Returns:
    number of bytes have been received  : success > 0

*/
int shunt_prim_recv_byte    (const int sockfd,char* Byte);

/*
 Function: shunt_prim_send_integer
  send  verilog "reg[31:0] 4 state aval,bval" over TCP/IP

  Parameters:
   sockfd - socket id
   Int  -   data

  Returns:
   number of bytes have been sent : success > 0
   see (vcs_prim_send_int)

*/
int shunt_prim_send_integer(const unsigned int sockfd,const svLogicVecVal* Int);

/*
 Function:  shunt_prim_recv_integer
  fetch verilog "reg[31:0] 4 state aval,bval" from TCP/IP

  Parameters:
   sockfd - socket id
   Int - data from socket

  Returns:
    number of bytes have been received  : success > 0

    see (shunt_prim_recv_in)
*/
int shunt_prim_recv_integer (const unsigned int sockfd,svLogicVecVal* Int);
#endif