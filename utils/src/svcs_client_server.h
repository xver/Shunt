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

typedef enum {SVCS_V_INT,SVCS_V_DOUBLE,SVCS_V_STRING,SVCS_A_STRUCTURE,SVCS_HEADER_ONLY} SVCV_INSTR_ENUM;
#define SVCV_INSTR_HASH_INDEX_DEFINE char* SVCV_INSTR_ENUM_NAMES[] = {"SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING","SVCS_A_STRUCTURE","SVCS_HEADER_ONLY"}

#include "svcs_primitives.h"
//-------------
//prototypes
//-------------

//Title: 3. Utilites: Client-Servercs_header

/*

Section: Data exchange utilities (header)

(start code)

typedef enum {SVCS_V_INT,SVCS_V_DOUBLE,SVCS_V_STRING,SVCS_A_STRUCTURE,SVCS_HEADER_ONLY} SVCV_INSTR_ENUM;
char* SVCV_INSTR_ENUM_NAMES[] = {"SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING","SVCS_A_STRUCTURE","SVCS_HEADER_ONLY"}

typedef struct cs_header_t {
cs_trnx_header trnx; //transaction header structure (see cs_trnx_header_t)
cs_data_header data; //data payload header structure (see cs_data_header_t)
} cs_header;

typedef struct cs_trnx_header_t {
//int      sockid;          // socket id from init sever/client
double   trnx_type;       // user defined transaction attribute
double   trnx_id;         // user defined unique transaction number
double   data_type;       // see SVCV_INSTR_ENUM
} cs_trnx_header;

typedef struct cs_data_header_t {
int      n_payloads;         // number of data payloads
int     *trnx_payload_sizes; // array of payload sizes, number of array elements are equal to n_payloads array of payload sizes, number of array elements are equal to n_payloads
} cs_data_header;


 (end)
*/

typedef struct cs_data_header_t {
  int      n_payloads;
  int     *trnx_payload_sizes;
} cs_data_header;

typedef struct cs_trnx_header_t {
  //int      sockid;
  double   trnx_type;
  double   trnx_id;
  double   data_type;
} cs_trnx_header;

 typedef struct cs_header_t {
   cs_trnx_header trnx;
   cs_data_header data;
 } cs_header;

//
/*
  Function: svcs_cs_data_type_hash
  map data_type enum to the corresponding hash
  
  Parameters:
  data_type/trnx_type - for valid data_type see SVCV_INSTR_ENUM
  data_type_names - data_type (see SVCV_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  
  Returns:
  hash index
*/
double svcs_cs_data_type_hash(int data_type,char* data_type_names[],int last_enum);

/*
  Function: svcs_cs_data_type
  map data_type hash to the corresponding enum
  
  Parameters:
  data_type - hash index
  data_type_names - data_type (see SVCV_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  
  Returns:
  valid data_type see SVCV_INSTR_ENUM
  -1 - No enum
*/
int svcs_cs_data_type(double hash,char* data_type_names[],int last_enum);

//
/*
  Function: svcs_cs_print_header
  print out SVCS header 
  
  Parameters:
  header - cs_header structure
  data_type_names - data_type (see SVCV_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  msg    - header print out prefix
  
  Returns:
  void
*/

void svcs_cs_print_header    (cs_header* h,char* data_type_names[],int last_enum,char* msg);

/*
  Function: svcs_cs_print_trnx_header
  print out SVCS header 
  
  Parameters:
  h - cs_trnx_header structure
  data_type_names - data_type (see SVCV_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  msg    - header print out prefix
  
  Returns:
  void
*/
void svcs_cs_print_trnx_header    (cs_trnx_header* h,char* data_type_names[],int last_enum,char* msg);


/*
  Function: svcs_cs_print_data_header
  print out SVCS header 
  
  Parameters:
  h   - cs_data_header structure
  msg - header print out prefix
  Returns:
  void
*/
void svcs_cs_print_data_header    (cs_data_header* h,char* msg);

//
/*
  Function: svcs_cs_send_header
  send SVCS header over TCP/IP
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_header structure
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_header    (int sockid,cs_header* h);

/*
  Function: svcs_cs_send_trnx_header
  send SVCS header over TCP/IP
  
  Parameters:
   sockid - socket id from init sever/client 
   h - cs_trnx_header structure

  Returns:
  number of elements have been sent  : success > 0
*/

int svcs_cs_send_trnx_header    (int sockid,cs_trnx_header* h);

/*
  Function: svcs_cs_send_data_header
  send SVCS header over TCP/IP
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_header structure
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_data_header    (int sockid,cs_data_header* h);

//
/*
  Function: svcs_cs_recv_header
  fetch SVCS transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int svcs_cs_recv_header   (int sockid,cs_header* h);

/*
  Function: svcs_cs_recv_trnx_header
  fetch SVCS transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init sever/client 
  header - cs_trnx_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int svcs_cs_recv_trnx_header   (int sockid,cs_trnx_header* h);
/*
  Function: svcs_cs_recv_data_header
  fetch SVCS transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int svcs_cs_recv_data_header   (int sockid,cs_data_header* h);

/*Function:
  svcs_cs_recv_data_header_clean
   free data header allocated memory

  Parameters:
  h - cs_data_header structure

  Returns:
  success > 0;

*/

int svcs_cs_recv_data_header_clean   (cs_data_header* h);

/*Function:
  svcs_cs_recv_int_clean
   free data header allocated memory

  Parameters:
  Int - Int array

  Returns:
  success > 0;

*/
int svcs_cs_recv_int_clean   (int ** Int);
//////////////////////////////////////


// Section: Data exchange utilities (element)


/*
 Function: svcs_cs_send_intV
  send SVCS transaction with "int" elements vector over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
   h - cs_data_header structure
   Int   - data
    
   Returns:
   number of elements have been sent  : success > 0
*/
int svcs_cs_send_intV   (int sockid,const cs_data_header* h,const int* Int);

/*
 Function: svcs_cs_recv_intV
  fetch SVCS transaction with "int" elements vector  elements from TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
     h - cs_data_header structure
     IntV  - Data received

  Returns: 
   number of elements have been received  : success > 0
*/
int svcs_cs_recv_intV   (int sockid,cs_data_header* h,int ** Int);


/*
 Function: svcs_cs_send_doubleV
  send SVCS transaction with "double" elements vector over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
     h - cs_data_header structure
     Double - data

  Returns:
    number of elements have been sent  : success > 0
*/
int svcs_cs_send_doubleV   (int sockid,const cs_data_header* h,const double* Double);

/*
 Function: svcs_cs_recv_doubleV
  fetch SVCS transaction with "double" elements vector from TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
    h - cs_data_header structure
    Double  - Data received

  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_doubleV   (int sockid,cs_data_header* h,double* Double);

/*
 Function: svcs_cs_send_string
  send SVCS transaction with verilog string/C char* elements over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
    h - cs_data_header structure
    string  - data to send

  Returns:
    number of elements have been sent  : success > 0
*/
int svcs_cs_send_string   (int sockid,const cs_data_header* h,const char* string);

/*
 Function: svcs_cs_recv_string
  fetch SVCS transaction with verilog string/C char* elements from TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
    h - cs_data_header structure
    string  - Data received

 Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_string   (int sockid,cs_data_header* h,char* string);


/*
 Section: Data exchange utilities (array)

(start code)
 ---------------------------------------------------------------
array ->  sockid - socket id
          header ->   trnx_atribute - hash/random double
                         data_type   - hash ("SVCS_A_STRUCTURE")
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
  sockid - socket id from init sever/client 
  h - cs_data_header structure,
  note: header.trnx_payload_size - The number of array entries is equal to the number of "int" vectors   
  ArrayI  - data 

  Return : number of elements have been sent  : success > 0
 */

 int svcs_cs_send_intA(int sockid, cs_data_header* h,int* ArrayI);

/*
  Function: svcs_cs_recv_intA
  fetch SVCS transaction with "int" array of "int" vectors from TCP/IP  
  
  Parameters:
  sockid - socket id from init sever/client 
    h - cs_data_header structure
    ArrayI  - Data received

  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_intA(int sockid,cs_data_header* h,int* ArrayI);

/*
  Function: svcs_cs_send_doubleA
   send SVCS transaction with "double" vector array over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure,
  note: header.trnx_payload_size  - The number of array entries is equal to the number of "double" vectors     
  ArrayD  - data 

  Returns: number of elements have been sent  : success > 0
*/
int svcs_cs_send_doubleA(int sockid,cs_data_header* h,const double* ArrayD);

/*
  Function: svcs_cs_recv_doubleA
  fetch SVCS transaction with "double" array of "double" vectors from TCP/IP  
  
  Parameters:
  sockid - socket id from init sever/client 
   h - cs_data_header structure
   ArrayD  - Data received

  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_doubleA(int sockid,cs_data_header* h,double* ArrayD);

/*
  Function: svcs_cs_send_stringA
   send SVCS transaction with "string" vectors array  over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure,
  note: header.trnx_payload_size - The number of array entries is equal to the number of strings 
  ArrayS  - data 

  Returns:number of elements have been sent  : success > 0
*/
int svcs_cs_send_stringA(int sockid,const cs_data_header* h,const char* ArrayS[]);

/*
  Function: svcs_cs_recv_stringA
  fetch SVCS transaction with string" vectors array from TCP/IP  
  
  Parameters:
  sockid - socket id from init sever/client 
    h - cs_data_header structure
    ArrayS  - Data received

 Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_stringA(int sockid,cs_data_header h,char* ArrayS[]);


#endif
