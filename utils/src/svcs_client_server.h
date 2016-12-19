/* 
 ============================================================================
 File        : svcs_client_server.h
 Author      : Victor Besyakov
 Version     : 0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : Client-Server utils   
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
#ifndef SVCS_CLIENT_SERVER_H_
#define SVCS_CLIENT_SERVER_H_

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

#define MY_HOST "localhost"
#define BUFSIZE   1024
#define MAXBUFLEN 1024

typedef enum {SVCS_V_INT,SVCS_V_DOUBLE,SVCS_V_STRING,SVCS_A_STRUCTURE} SVCV_DPI_Instr_enum;
const char* SVCV_DPI_Instr_enum_names[] = {"SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING","SVCS_A_STRUCTURE"};

//-------------
//prototypes
//-------------

//Title: Utilites: Client-Server

///////////////////////////////
//Section:  Common Functions 

/*
  Function: svcs_hash 
  simple hash function 
  
  Parameters: 
  *str - hash key
  
  Returns: 
  hash value
*/
unsigned long svcs_hash(const char *str);

/*
  Function: svcs_error 
  perror wrapper
 
  Parameters:
  *str - error message
  
  Returns: 
  void
 */
void svcs_error(char *msg);
/////////////////////////////
//Section: TCP/IP Functions
/*
 Function: svcs_init_tcpserver 
 TCP/IP server initialisation 
 
 Parameters: 
 portno - socket port
  
 Returns:  
 socket id
   
*/
unsigned int svcs_init_tcpserver(const unsigned int portno);

/*
 Function: svcs_init_tcpclient 
 TCP/IP client initialisation 
 
 Parameters:
 
 portno - socket port
 *hostname - server name
 
 Returns: 
 socket id 
   
*/
unsigned int svcs_init_tcpclient(const unsigned int portno,const char *hostname);

/*
Function: Example:  svcs_init_tcpclient ,svcs_init_tcpserver 

(start code)    
 #define MY_HOST "localhost"
 #define MY_PORT  3450
 char *hostname; 
 int port;
 port = MY_PORT;
 hostname =   MY_HOST;
  
 svcs_init_tcpserver(hostname);
 svcs_init_tcpclient(port,hostname);
(end)
 */

/*

Section: Data exchange utilities (element)

(start code)
-------------------------------------------------------
element -> header ->  trnx_atribute     - hash/random double
                      trnx_type         - hash ("SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING")
                      trnx_id           - random double

	   payload ->  size  - number of data elements, size= 1
           data element 
---------------------------------------------------------------
(end)
*/

/*
 Function: svcs_send_int
  send verilog/C "int" data over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Int  -   data
  
  Returns:
    void
*/
void svcs_send_int    (const int sockfd,const int* Int);

/*
 Function: svcs_recv_int
  fetch verilog/C "int" data from TCP/IP socket
  
  Parameters:
   sockfd - socket id

  Returns: 
    data 
    
*/
int* svcs_recv_int    (const int sockfd);

/*
 Function: svcs_send_double
  send verilog "real"/C "double" over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Double  - data to send
  
  Returns:
    void
*/

void svcs_send_double    (const int sockfd,const double Double);

/*
  Function: svcs_recv_double
  fetch verilog "real"/C "double" over TCP/IP 
  
  Parameters:
  sockfd - socket id

  Returns: 
  Double - data from socket 
    
*/
double* svcs_recv_Double    (const int sockfd);




/*
 Section: Data exchange utilities (vector)

(start code)
-------------------------------------------------------
vector -> header ->  trnx_atribute - hash/random double
                     trnx_type     - hash ("SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING")
                     trnx_id       - random double

          payload -> size          - number of data elements,size >1
          data elements 
---------------------------------------------------------------
(end)
*/

/*
 Function: svcs_send_intV
  send "int" elements vector over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Int   - data
   size  - number of vector elements
 
   Returns:
   void
*/
void svcs_send_intV   (const int sockfd,const int* Int,const int size);

/*
 Function: svcs_recv_intV
  fetch "int" elements vector  elements from TCP/IP 
  
  Parameters:
   sockfd - socket id

  Returns: 
   data received from socket
    
*/
int* svcs_recv_intV   (const int sockfd);


/*
 Function: svcs_send_doubleV
  send "double" elements vector over TCP/IP 
  
  Parameters:
   sockfd - socket id
   Double   - data to send
   size   - number of vector elements 
  Returns:
    void
*/
void svcs_send_doubleV   (const int sockfd,const double* Double,const int size);

/*
 Function: svcs_recv_doubleV
  fetch  "double" elements vector from TCP/IP 
  
  Parameters:
   sockfd - socket id

  Returns: 
  double - data from socket 
    
*/
double* svcs_recv_doubleV   (const int sockfd);

/*
 Function: svcs_send_string
  send verilog string/C char* elements over TCP/IP 
  
  Parameters:
   sockfd  - socket id
   string  - data to send
   size    - string size (number of string elements), if size =0 function assumes that end of the strig is "0" 
  Returns:
    void
*/
void svcs_send_string   (const int sockfd,const char* string);

/*
 Function: svcs_recv_string
  fetch string from TCP/IP 
  
  Parameters:
   sockfd - socket id

  Returns: 
   data from socket 
    
*/
char* svcs_recv_string   (const int sockfd);


/*
 Section: Data exchange utilities (array)

(start code)
 ---------------------------------------------------------------
array -> header ->   trnx_atribute - hash/random double
                         trnx_type   - hash ("SVCS_A_STRUCTURE")
                         trnx_id    - random double
             payload->   size  > 1
             data - vector
---------------------------------------------------------------
 (end)

 */

/*
  Function: svcs_send_intA
  send "int" vectors array over TCP/IP 
  
  Parameters:
  sockfd  - socket id
  size    - The number of array entries is equal to the number of "int" vectors   
  ArrayI  - data 
 */

 void svcs_send_intA(const int sockfd,const int size,const int* ArrayI);

/*
  Function: svcs_recv_intA
  fetch "int" array of "int" vectors from TCP/IP  
  
  Parameters:
  sockfd - socket id   
  
  Returns: 
  Array of int
  
*/
int* svcs_recv_intA(const int sockfd);

/*
  Function: svcs_send_doubleA
   send "double" vector array over TCP/IP 
  
  Parameters:
  sockfd  - socket id
  size    - The number of array entries is equal to the number of "double" vectors     
  ArrayL  - data 
*/
void svcs_send_doubleA(const int sockfd,const int size,const double* ArrayL);

/*
  Function: svcs_recv_doubleA
  fetch "double" array of "double" vectors from TCP/IP  
  
  Parameters:
  sockfd - socket id   
  
  Returns: 
  Array of double 
*/
double* rec_doubleA(const int sockfd);

/*
  Function: svcs_send_stringA
   send "string" vectors array  over TCP/IP 
  
  Parameters:
  sockfd  - socket id
  size    - The number of array entries is equal to the number of strings 
  ArrayL  - data 
*/
void svcs_send_stringA(const int sockfd,const int size,const char* ArrayS);

/*
  Function: svcs_recv_stringA
  fetch string" vectors array from TCP/IP  
  
  Parameters:
  sockfd - socket id   
  
  Returns: 
  Array of strinds
  
*/
char* svcs_recv_stringA(const int sockfd);





#endif
