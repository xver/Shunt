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

typedef enum {SVCS_INT,SVCS_DOUBLE,SVCS_STRING,SVCS_A_STRUCTURE,SVCS_HEADER_ONLY} SVCV_INSTR_ENUM;
#define SVCV_INSTR_HASH_INDEX_DEFINE char* SVCV_INSTR_ENUM_NAMES[] = {"SVCS_INT","SVCS_DOUBLE","SVCS_STRING","SVCS_A_STRUCTURE","SVCS_HEADER_ONLY"}


//-------------
//prototypes
//-------------

//Title: 3. Utilites: Client-Servercs_header

/*
  
Section: Data exchange utilities (header)

(start code)

typedef enum {SVCS_INT,SVCS_DOUBLE,SVCS_STRING,SVCS_A_STRUCTURE,SVCS_HEADER_ONLY} SVCV_INSTR_ENUM;
char* SVCV_INSTR_ENUM_NAMES[] = {"SVCS_INT","SVCS_DOUBLE","SVCS_STRING","SVCS_A_STRUCTURE","SVCS_HEADER_ONLY"}

typedef struct cs_header_t {
//int      sockid;        // socket id from init sever/client
double   trnx_type;       // user defined transaction attribute
double   trnx_id;         // user defined unique transaction number
double   data_type;       // see SVCV_INSTR_ENUM
int      n_payloads;      // number of data payloads (for Array number of vectors)
} cs_header;

//  Array header extension
typedef struct cs_data_header_t {
int      n_payloads;         // number of data payloads
double   data_type;       // see SVCV_INSTR_ENUM
int     *trnx_payload_sizes; // array of payload sizes, number of array elements are equal to n_payloads
} cs_data_header;

(end)
*/

typedef struct cs_data_header_t {
  
  double   data_type;       // see SVCV_INSTR_ENUM
  int     *trnx_payload_sizes;
} cs_data_header;

typedef struct cs_header_t {
  //int      sockid;
  double   trnx_type;
  double   trnx_id;
  double   data_type;
  int      n_payloads;
} cs_header;


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


/*
  Function: svcs_cs_print_header
  print out SVCS header 
  
  Parameters:
  h - cs_header structure
  data_type_names - data_type (see SVCV_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  msg    - print out prefix
  
  Returns:
  void
*/
void svcs_cs_print_header    (cs_header* h,char* data_type_names[],int last_enum,char* msg);


/*
  Function: svcs_cs_print_data_header
  print out SVCS header 
  
  Parameters:
  h - cs_header structure
  h_data   - cs_data_header structure
  data_type_names - data_type (see SVCV_INSTR_ENUM_NAMES[]) or trnx_type names array
  last_enum       - number of data_type_names[] elements
  msg - print out prefix
  
  Returns:
  void
*/

void svcs_cs_print_data_header (cs_header* h,cs_data_header* h_data,char* data_type_names[],int last_enum,char* msg);
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
  Function: svcs_cs_send_data_header
  send SVCS header over TCP/IP
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_header structure
  n_payloads - number of data payloads
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_data_header    (int sockid,int n_payloads,cs_data_header* h);

/*
  Function: svcs_cs_comp_header
  compare two SVCS headers

  Parameters:
  h_lhs,h_rhs - two cs headers
  Returns:
  success > 0
*/
int svcs_cs_comp_header    (cs_header h_lhs,cs_header h_rhs);

/*
  Function: svcs_cs_comp_data_header
  compare two SVCS data headers

  Parameters:
  h_lhs,h_rhs - two cs data headers
  n_payloads - number of data payloads
  Returns:
  success > 0
*/
int svcs_cs_comp_data_header (cs_data_header h_lhs,cs_data_header h_rhs,int n_payloads);

/*
  Function: svcs_cs_recv_header
  fetch SVCS transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init sever/client 
  header - cs_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int svcs_cs_recv_header   (int sockid,cs_header* h);

/*
  Function: svcs_cs_recv_data_header
  fetch SVCS transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int svcs_cs_recv_data_header   (int sockid,int n_payloads,cs_data_header* h);

/* TOODOO remove
   Function:
   svcs_cs_recv_data_header_clean
   free data header allocated memory
   
   Parameters:
   h - cs_data_header structure
   n_payloads - number of data payloads
   
   Returns:
   success > 0;

*/

//int svcs_cs_recv_data_header_clean   (cs_data_header* h);


//////////////////////////////////////


// Section: Data exchange utilities (element)


/*
  Function: svcs_cs_send_intV
  send SVCS transaction with "int" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_intV   (int sockid, const cs_header* header,const int* Int);

/*
  Function: svcs_cs_recv_intV
  fetch SVCS transaction with "int" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  IntV  - Data received
  
  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_intV   (int sockid, cs_header* header,int* Int);

/*
  Function: svcs_cs_print_intV
  print out IntV Data

  Parameters:

  h - cs_data_header structure
  Int  - Data received
  msg    - print out prefix

  Returns:
  void
*/
void svcs_cs_print_intV   (cs_header* h,int *Int,char* msg);


/*
  Function: svcs_cs_comp_intV
  compare two intV payloads

  Parameters:
  h - cs_header
  lhs,rhs - intA data
  Returns:
  success > 0
*/
int svcs_cs_comp_intV   (cs_header* h,int *lhs,int *rhs);


/*
  Function: svcs_cs_send_doubleV
  send SVCS transaction with "double" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Double - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_doubleV   (int sockid,const cs_header* header,const double* Double);

/*
  Function: svcs_cs_recv_doubleV
  fetch SVCS transaction with "double" elements vector from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Double  - Data received
  
  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_doubleV   (int sockid,cs_header* header,double* Double);

/*
  Function: svcs_cs_send_string
  send SVCS transaction with verilog string/C char* elements over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  string  - data to send
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_string   (int sockid,const cs_header* header,const char* string);

/*
  Function: svcs_cs_recv_string
  fetch SVCS transaction with verilog string/C char* elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  string  - Data received
  
 Returns:
 number of elements have been received  : success > 0
*/
int svcs_cs_recv_string   (int sockid,cs_header* header,char* string);

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
  send SVCS transaction with "int" elements vector over TCP/IP

  Parameters:
  sockid - socket id from init sever/client
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_intA (int sockid,int n_payloads,const cs_data_header* h,const int * Int);

/*
  Function: svcs_cs_send_int
  send SVCS transaction with "int" elements vector over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  h - cs_data_header structure
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_intA   (int sockid,int n_payloads,const cs_data_header* h,const int* Int);

/*
  Function: svcs_cs_recvA
  fetch SVCS transaction with "int" elements vector  elements from TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int  - Data received
  
  Returns: 
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_intA   (int sockid,int n_payloads,cs_data_header* h,int * Int);

/*
  Function: svcs_cs_print_intA
  print out IntA Data

  Parameters:
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int  - Data received
  msg    - print out prefix
  Returns:
   void
*/
void svcs_cs_print_intA   (int n_payloads,cs_data_header* h,int *Int,char* msg);


/*
  Function: svcs_cs_comp_intA
  compare two intA payloads

  Parameters:
  n_payloads - number of data payloads
  lhs,rhs - intA data
  Returns:
  success > 0
*/
int svcs_cs_comp_intA   (int n_payloads,cs_data_header* h,int *lhs,int *rhs);


/* TODO remove
   Function:
   svcs_cs_recv_int_clean
   free data header allocated memory

   Parameters:
   Int - Int array
   
  Returns:
  success > 0;
  
*/
//int svcs_cs_recv_int_clean   (int ** Int);

/*
  Function: svcs_cs_send_doubleV
  send SVCS transaction with "double" elements vector over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure
  Double - data
  int n_payloads - number of data payloads
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_doubleA   (int sockid,int n_payloads,const cs_data_header* h,const double* Double);

/*
 Function: svcs_cs_recv_doubleV
 fetch SVCS transaction with "double" elements vector from TCP/IP 
 
 Parameters:
 sockid - socket id from init sever/client 
 h - cs_data_header structure
 Double  - Data received
 n_payloads - number of data payloads
 
 Returns:
 number of elements have been received  : success > 0
*/
int svcs_cs_recv_doubleA   (int sockid,int n_payload,cs_data_header* h,double ** Double);

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
