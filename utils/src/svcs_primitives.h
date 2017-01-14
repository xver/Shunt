/* 
 ============================================================================
 File        : svcs_primitives.h
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : Client-Server utils   
               System Verilog client server handshake (SVCS)
******************************************************
Data Types: integer,  double
 ============================================================================
 */

#ifndef  SVCS_PRIMITIVES_H
#define  SVCS_PRIMITIVES_H

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


//-------------
//prototypes
//-------------

//Title: 2. Client-Server Primitives

  
///////////////////////////////
//Section:  Common Functions 

/*
  Function: svcs_prim_hash 
  simple hash function 
  
  Parameters: 
  str - hash key
  
  Returns: 
  hash value
*/
double svcs_prim_hash(const char *str);

/*
  Function: svcs_prim_error 
  perror wrapper
 
  Parameters:
  str - error message
  
  Returns: 
  void
 */
void svcs_prim_error(char *msg);

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
 Function: svcs_prim_init_tcpserver 
 TCP/IP server initialization
 
 Parameters: 
 portno - socket port
  
 Returns:  
 socket id
   
*/
unsigned int svcs_prim_init_tcpserver(const unsigned int portno);

/*
 Function: svcs_prim_init_tcpclient 
 TCP/IP client initialization
 
 Parameters:
 
 portno - socket port
 hostname - server name
 
 Returns: 
 socket id 
   
*/
unsigned int svcs_prim_init_tcpclient(const unsigned int portno,const char *hostname);

/*
Function: Example:  tcpclient,tcpserver init 

(start code)    
 #define MY_HOST "localhost"
 #define MY_PORT  3450
 char *hostname; 
 int port;
 port = MY_PORT;
 hostname =   MY_HOST;
  
 svcs_prim_init_tcpserver(hostname);
 svcs_prim_init_tcpclient(port,hostname);
(end)
 */


//Section: Data exchange primitives


/*
 Function: svcs_prim_send_int
  send verilog/C "int" data over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Int  -   data
  
  Returns:
    void
*/
void svcs_prim_send_int    (const int sockfd,const int* Int);

/*
 Function: svcs_prim_recv_int
  fetch verilog/C "int" data from TCP/IP socket
  
  Parameters:
   sockfd - socket id
   Int - data from socket 
     
  Returns: 
    void
    
*/
void svcs_prim_recv_int    (const int sockfd,int* Int);

/*
 Function: svcs_prim_send_double
  send verilog "real"/C "double" over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Double  - data to send
  
  Returns:
    void
*/

void svcs_prim_send_double    (const int sockfd,const double* Double);

/*
  Function: svcs_prim_recv_double
  fetch verilog "real"/C "double" over TCP/IP 
  
  Parameters:
  sockfd - socket id
  Double - data from socket 
  
  Returns: 
  void
    
*/
void svcs_prim_recv_double    (const int sockfd,double* Doubl);


#endif
