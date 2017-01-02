/* 
 =======svcs_cs=====================================================================
 File        : svcs_client_server.h
 Author      : Victor Besyakov
 Version     : 0.0.0
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

#include "svcs_primitives.h"

typedef enum {SVCS_V_INT,SVCS_V_DOUBLE,SVCS_V_STRING,SVCS_A_STRUCTURE} SVCV_INSTR_ENUM;
#define SVCV_INSTR_HASH_INDEX_DEFINE char* SVCV_INSTR_ENUM_NAMES[] = {"SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING","SVCS_A_STRUCTURE"}


//-------------
//prototypes
//-------------

//Title: 3. Utilites: Client-Server


///////////////////////////////


/*

Section: Data exchange utilities (header)

(start code)

  typedef struct cs_header_t {
    int      sockid; 
    double   trnx_atribute;
    double   trnx_type;
    double   trnx_id;
    //
    int      trnx_payload_size 
  } cs_header;

 (end)
*/
  typedef struct cs_header_t {
    int      sockid; 
    double   trnx_atribute;
    double   trnx_type;
    double   trnx_id;
    //
    int      trnx_payload_size;
  } cs_header;
 
/*
   Function: svcs_cs_print_header
    print out SVCS header 

    Parameters:
     header - cs_header structure

    Returns:
      void
  */

  void svcs_cs_print_header    (cs_header* header);

  /*
   Function: svcs_cs_send_header
    send SVCS header over TCP/IP

    Parameters:
     header - cs_header structure

    Returns:
      void
  */

  void svcs_cs_send_header    (cs_header* header);
  /*
   Function: svcs_cs_recv_header
    fetch SVCS transaction header from TCP/IP socket

    Parameters:
      header - cs_header structure

    Returns:
      header - cs_header structure

  */
  void svcs_cs_recv_header   (cs_header* header);
/*

Section: Data exchange utilities (element)

(start code)
-------------------------------------------------------
SVCS element transaction structure :

element -> sockid - int socket id 
           header ->  trnx_atribute     - hash index /random double
                      trnx_type         - hash index ("SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING")
                      trnx_id           - random double
	  payload ->  size  - number of data elements, size= 1
                      data element
---------------------------------------------------------------
 (end)
*/

/*
 Function: svcs_cs_send_int
  send SVCS transaction "int" over TCP/IP 
  
  Parameters:
   header - cs_header structure
   Int    -  trnx payload (size+data)
   
  Returns:
    void
*/

void svcs_cs_send_int    (const cs_header* header,const int* Int);

/*
 Function: svcs_cs_recv_int
  fetch SVCS transaction "int" from TCP/IP socket
  

  Parameters:
    header - cs_header structure

  Returns: 
    data 
    
*/
int* svcs_cs_recv_int    (cs_header* header);

/*
 Function: svcs_cs_send_double
  send  SVCS transaction with verilog "real"/C "double" data over TCP/IP 
  
  Parameters:
   header - cs_header structure
   Double  - data to send
  
  Returns:
    void
*/

void svcs_cs_send_double    (const cs_header* header,const double Double);

/*
  Function: svcs_cs_recv_double
  fetch SVCS transaction with verilog "real"/C "double" data over TCP/IP 
  
  Parameters:
   header - cs_header structure

  Returns: 
  Double - data from socket 
  and header atributes (cs_header)
    
*/
double* svcs_cs_recv_double    (cs_header* header);




/*
 Section: Data exchange utilities (vector)

(start code)
-------------------------------------------------------
vector ->  sockid - socket id
           header ->  trnx_atribute - hash/random double
                      trnx_type     - hash ("SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING")
                      trnx_id       - random double

          payload -> size          - number of data elements,size >1
                     data elements 
---------------------------------------------------------------
(end)
*/

/*
 Function: svcs_cs_send_intV
  send SVCS transaction with "int" elements vector over TCP/IP 
  
  Parameters:
   
   header - cs_header structure
   Int   - data
    
   Returns:
   void
*/
void svcs_cs_send_intV   (const cs_header* header,const int* Int);

/*
 Function: svcs_cs_recv_intV
  fetch SVCS transaction with "int" elements vector  elements from TCP/IP 
  
  Parameters:
     header - cs_header structure

  Returns: 
   data received from socket
  and header atributes (cs_header)
    
*/
int* svcs_cs_recv_intV   (cs_header* header);


/*
 Function: svcs_cs_send_doubleV
  send SVCS transaction with "double" elements vector over TCP/IP 
  
  Parameters:
     header - cs_header structure
     Double - data 
  Returns:
    void
*/
void svcs_cs_send_doubleV   (const cs_header* header,const double* Double);

/*
 Function: svcs_cs_recv_doubleV
  fetch SVCS transaction with "double" elements vector from TCP/IP 
  
  Parameters:
    header - cs_header structure

  Returns: 
  double - data from socket
  and header atributes (cs_header)
    
*/
double* svcs_cs_recv_doubleV   (cs_header* header);

/*
 Function: svcs_cs_send_string
  send SVCS transaction with verilog string/C char* elements over TCP/IP 
  
  Parameters:
    header - cs_header structure
    string  - data to send

  Returns:
    void
*/
void svcs_cs_send_string   (const cs_header* header,const char* string);

/*
 Function: svcs_cs_recv_string
  fetch SVCS transaction with verilog string/C char* elements from TCP/IP 
  
  Parameters:
    header - cs_header structure

  Returns: 
   data from socket 
  and header atributes (cs_header)
    
*/
char* svcs_cs_recv_string   (cs_header* header);


/*
 Section: Data exchange utilities (array)

(start code)
 ---------------------------------------------------------------
array ->  sockid - socket id
          header ->   trnx_atribute - hash/random double
                         trnx_type   - hash ("SVCS_A_STRUCTURE")
                         trnx_id    - random double
          payload->   size  > 1
          data - vector
---------------------------------------------------------------
 (end)

 */

/*
  Function: svcs_cs_send_intA
  send SVCS transaction with "int" vectors array over TCP/IP 
  
  Parameters:
  header - cs_header structure,
  note: header.trnx_payload_size - The number of array entries is equal to the number of "int" vectors   
  ArrayI  - data 
 */

 void svcs_cs_send_intA(const cs_header* header,const int* ArrayI);

/*
  Function: svcs_cs_recv_intA
  fetch SVCS transaction with "int" array of "int" vectors from TCP/IP  
  
  Parameters:
   header - cs_header structure
   string  - data to send
  
  Returns: 
  Array of int
  
*/
int* svcs_cs_recv_intA(cs_header* header);

/*
  Function: svcs_cs_send_doubleA
   send SVCS transaction with "double" vector array over TCP/IP 
  
  Parameters:
  header - cs_header structure,
  note: header.trnx_payload_size  - The number of array entries is equal to the number of "double" vectors     
  ArrayD  - data 
*/
void svcs_cs_send_doubleA(const int sockfd,const int size,const double* ArrayD);

/*
  Function: svcs_cs_recv_doubleA
  fetch SVCS transaction with "double" array of "double" vectors from TCP/IP  
  
  Parameters:
  header - cs_header structure

  Returns: 
  Array of double 
*/
double* svcs_cs_recv_doubleA(cs_header* header);

/*
  Function: svcs_cs_send_stringA
   send SVCS transaction with "string" vectors array  over TCP/IP 
  
  Parameters:
  header - cs_header structure,
  note: header.trnx_payload_size - The number of array entries is equal to the number of strings 
  ArrayS  - data 
*/
void svcs_cs_send_stringA(const cs_header* header,const char* ArrayS);

/*
  Function: svcs_cs_recv_stringA
  fetch SVCS transaction with string" vectors array from TCP/IP  
  
  Parameters:
  header - cs_header structure,
  
  Returns: 
  Array of strinds
  
*/
char* svcs_cs_recv_stringA(cs_header structure);





#endif
