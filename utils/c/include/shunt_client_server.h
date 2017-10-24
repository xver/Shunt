/* 
   ============================================================================
   File        : shunt_client_server.h
   Version     : 1.0.0
   Copyright (c) 2016-2017 IC Verimeter. All rights reserved.  
   Licensed under the MIT License. 
   See LICENSE file in the project root for full license information.  
   Description : Target-Initiator (Client-Server aka cs) handshake utils   
                 System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)
*/

#ifndef SHUNT_CLIENT_SERVER_H_
#define SHUNT_CLIENT_SERVER_H_

#include "shunt_primitives.h"

//Title: Utilites: Client-Initiator cs_header

/* 
 * About: Verilog Data Types elements: 
 * 
 * Integer 2 states::
 *
 * (start code)
 *  
 *    SHUNT ENUM       |  SV type    | function
 *  ------------------------------------------------------------------------
 *  SHUNT_INT          | int         | shunt_cs_xxxx_intV
 *  SHUNT_SHORTINT     | shortint    | shunt_cs_xxxx_shortV
 *  SHUNT_LONGINT      | longint     | shunt_cs_xxxx_longV
 *  SHUNT_BYTE         | byte        | shunt_cs_xxxx_byteV
 *  SHUNT_BIT          | bit         | shunt_cs_xxxx_bitN.
 * 
 * (end code)
 *
 * Integer 4 states::
 *
 * (start code)
 *  
 *    SHUNT ENUM       |  SV type     |  function
 *  ------------------------------------------------------------------------
 *    SHUNT_INTEGER    | integer,time |  shunt_cs_xxxx_integerV
 *    SHUNT_REG        | reg,logic    |  shunt_cs_xxxx_regN
 *
 * (end code)
 * 
 * Non integer types IEEE 754::  
 *
 * (start code)
 *  
 *    SHUNT ENUM       |  SV type     |  function
 *  ------------------------------------------------------------------------
 *   SHUNT_REAL        | real,realtime| shunt_cs_xxxx_doubleV
 *   SHUNT_SHORTREAL   | shortreal    | shunt_cs_xxxx_floatV
 *   SHUNT_STRING      | string       | shunt_cs_xxxx_byteV
 *
 * (end code)
 *
 *  Special Shunt types::   
 *
 * (start code)
 *  
 *   SHUNT_A_STRUCTURE | complex data types/user defined data types : arrays/struct,union,enums (N/A)
 *
 * (end code)
*/

//-------------
//prototypes
//-------------

//Section: Data exchange structures and utilities

/*
Variable: SHUNT_INSTR_ENUM

 *Integer 2 states:*
  
  SHUNT_INT         - int
  SHUNT_SHORTINT    - shortint
  SHUNT_LONGINT     - longint
  SHUNT_BYTE        - byte
  SHUNT_BIT         - bit
  
  *Integer 4 states:*
  
  SHUNT_INTEGER     - integer,time
  SHUNT_REG         - reg,logic
  
  *Non integer types IEEE 754:*
  
  SHUNT_REAL        - real,realtime
  SHUNT_SHORTREAL   - shortreal
  SHUNT_STRING      - string
  
  SHUNT_A_STRUCTURE - complex data types/user defined data types : arrays/struct,union,enums 
  SHUNT_HEADER_ONLY - cs_header_t header only.
 
*/
typedef enum {SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_BIT,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} SHUNT_INSTR_ENUM;

/*
Variable: SHUNT_INSTR_ENUM_NAMES

> = {"SHUNT_INT","SHUNT_REAL","SHUNT_SHORTREAL","SHUNT_STRING","SHUNT_A_STRUCTURE","SHUNT_INTEGER","SHUNT_BYTE","SHUNT_REG","SHUNT_BIT","SHUNT_SHORTINT","SHUNT_LONGINT","SHUNT_HEADER_ONLY"}  

*/
#define SHUNT_INSTR_HASH_INDEX_DEFINE char* SHUNT_INSTR_ENUM_NAMES[] = {"SHUNT_INT","SHUNT_REAL","SHUNT_SHORTREAL","SHUNT_STRING","SHUNT_A_STRUCTURE","SHUNT_INTEGER","SHUNT_BYTE","SHUNT_REG","SHUNT_BIT","SHUNT_SHORTINT","SHUNT_LONGINT","SHUNT_HEADER_ONLY"}

/*
  Variable: cs_header_t
  
  - trnx_type      user defined transaction attribute
  - trnx_id        user defined unique transaction number
  - data_type      <SHUNT_INSTR_ENUM>
  - n_payloads     number of data payloads (for Array number of vectors)
  
*/
typedef struct cs_header_t {
  double   trnx_type;
  double   trnx_id;
  double   data_type;
  int      n_payloads;
} cs_header;

/*
  Variable: cs_data_header_t
  - data_type           <SHUNT_INSTR_ENUM>
  - trnx_payload_sizes   array of payload sizes, number of array elements are equal to n_payloads
*/
typedef struct cs_data_header_t {
  double   data_type;          // see SHUNT_INSTR_ENUM
  int     *trnx_payload_sizes; // array of payload sizes, number of array elements are equal to n_payloads
} cs_data_header;

/*
  Function: shunt_cs_data_type_hash
  map data_type enum to the corresponding hash
  
  Parameters:
  
  data_type/trnx_type - for valid data_type see <SHUNT_INSTR_ENUM>
  data_type_names     - data_type ( see <SHUNT_INSTR_ENUM_NAMES> ) or trnx_type names array 
  last_enum           - number of data_type_names[] elements
  
  Returns:
  hash index
  
  See Also:
   <shunt_cs_data_type_hash>

*/
double shunt_cs_data_type_hash(int data_type,char* data_type_names[],int last_enum);

/*
  Function: shunt_cs_data_type
  map data_type hash to the corresponding enum
  
  Parameters:
  
  data_type - hash index
  data_type_names - data_type (see <SHUNT_INSTR_ENUM_NAMES> ) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  
  Returns:
  
  valid data_type see <SHUNT_INSTR_ENUM>
  -1 - No enum
  
  See Also:
  <shunt_cs_data_type_hash>
*/
int shunt_cs_data_type(double hash,char* data_type_names[],int last_enum);

/*
  Function: shunt_cs_send_header
  send SHUNT header over TCP/IP
  
  Parameters:
  
  sockid - socket id from init Target/Initiator
  h - cs_header structure
  
  Returns:
  
  number of elements have been sent  : success > 0
  
  See Also:
  <cs_header_t>

*/
int shunt_cs_send_header    (int sockid,cs_header* h);

/*
  Function: shunt_cs_send_data_header
  send SHUNT header over TCP/IP
  
  Parameters:
  
  sockid - socket id from init Target/Initiator
  h - cs_header structure
  n_payloads - number of data payloads
  
  Returns:
  
  number of elements have been sent  : success > 0

  See Also:
  <cs_data_header_t>

*/
int shunt_cs_send_data_header    (int sockid,int n_payloads,cs_data_header* h);



/*
  Function: shunt_cs_recv_header
  fetch SHUNT transaction header from TCP/IP socket
  
  Parameters:
  
  sockid - socket id from init Target/Initiator
  header - cs_header structure
  
  Returns:
  
  number of elements have been received  : success > 0
 
 See Also:
  <cs_data_header_t>

*/
int shunt_cs_recv_header   (int sockid,cs_header* h);

/*
  Function: shunt_cs_recv_data_header
  fetch SHUNT transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init Target/Initiator
  h - cs_data_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
See Also:
  <cs_data_header_t>

*/
int shunt_cs_recv_data_header   (int sockid,int n_payloads,cs_data_header* h);

// Section: Data exchange utilities


/*
Function: shunt_cs_send_intV
  send SHUNT transaction with "int" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int - data
  
  Returns:
  number of elements have been sent  : success > 0

  See Also:
  <shunt_cs_recv_intV>

*/
int shunt_cs_send_intV   (int sockid, const cs_header* header,const int* Int);

/*
  Function: shunt_cs_recv_intV
  fetch SHUNT transaction with "int" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int   - Data received
  
  Returns:
  number of elements have been received  : success > 0
 See Also:
    <shunt_cs_send_intV>
*/
int shunt_cs_recv_intV   (int sockid, cs_header* header,int* Int);

/*
Function: shunt_cs_send_shortV
  send SHUNT transaction with "shortint" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Short   - data
  
  Returns:
  number of elements have been sent  : success > 0
  
  See Also:
  <shunt_cs_recv_shortV>

*/
int shunt_cs_send_shortV (int sockid, const cs_header* header,const short int* Short);

/*
  Function: shunt_cs_recv_shortV
  fetch SHUNT transaction with "shortint" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Short   - Data received
  
  Returns:
  number of elements have been received  : success > 0
  
  See Also:
    <shunt_cs_send_shortV>
*/
int shunt_cs_recv_shortV (int sockid, cs_header* header,short int* Short);


/*
Function: shunt_cs_send_longV
  send SHUNT transaction with "longint" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int,Short,Long   - data
  
  Returns:
  number of elements have been sent  : success > 0
  
    See Also:
    <shunt_cs_recv_longV>
*/
int shunt_cs_send_longV  (int sockid, const cs_header* header,const long int* Long);

/*
  Function: shunt_cs_recv_longV
  fetch SHUNT transaction with "longint" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Long   - Data received
  
  Returns:
  number of elements have been received  : success > 0
 

  See Also:
    <shunt_cs_send_longV>
*/
int shunt_cs_recv_longV  (int sockid, cs_header* header,long int* Long);


/*
  Function: shunt_cs_send_doubleV
  send SHUNT transaction with "double" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Double - data
  
  Returns:
  number of elements have been sent  : success > 0

  See Also:
    <shunt_cs_recv_doubleV>
*/
int shunt_cs_send_doubleV   (int sockid,const cs_header* header,const double* Double);

/*
  Function: shunt_cs_recv_doubleV
  fetch SHUNT transaction with "double" elements vector from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Double  - Data received
  
  Returns:
  number of elements have been received  : success > 0
  
  See Also:
  <shunt_cs_send_doubleV>
 
*/
int shunt_cs_recv_doubleV   (int sockid,cs_header* header,double* Double);


/*
  Function: shunt_cs_send_floatV
  send SHUNT transaction with "float" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Float - data
  
  Returns:
  number of elements have been sent  : success > 0

  See Also:
  <shunt_cs_recv_floatV>
*/
int shunt_cs_send_floatV   (int sockid,const cs_header* header,const float* Float);

/*
  Function: shunt_cs_recv_floatV
  fetch SHUNT transaction with "float" elements vector from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Float  - Data received
  
  Returns:
  number of elements have been received  : success > 0
  
  See Also:
  <shunt_cs_send_floatV>

*/
int shunt_cs_recv_floatV   (int sockid,cs_header* header,float* Float);

/*
  Function: shunt_cs_send_byteV
  send SHUNT transaction with verilog byteV/string/C char* elements over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  byteV  - data to send
  
  Returns:
  number of elements have been sent  : success > 0
  
  See Also:
  <shunt_cs_recv_byteV>
*/
int shunt_cs_send_byteV   (int sockid,const cs_header* header,const char* byteV);

/*
  Function: shunt_cs_recv_byteV
  fetch SHUNT transaction with verilog byteV/string/C char* elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  byteV  - Data received
  
 Returns:
 number of elements have been received  : success > 0  
  
See Also:
  <shunt_cs_send_byteV>
*/
int shunt_cs_recv_byteV   (int sockid,cs_header* header,char* byteV);

/*
    Functions: shunt_cs_send_bitN
    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    
    */
int shunt_cs_send_bitN (int sockid,const cs_header* h,const svBitVecVal* bitN) ;

  /*
    Functions: shunt_cs_recv_bitN
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0  

See Also:
  <shunt_cs_recv_bitN>
    */
int shunt_cs_recv_bitN     (int sockid,const cs_header* h,svBitVecVal* bitN);

/*
    Functions: shunt_cs_send_integerV
    map verilog "reg[31:0] 4 state aval,bval
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0

See Also:
  <shunt_cs_recv_integer>
*/
int shunt_cs_send_integerV (int sockid,const cs_header* h,const svLogicVecVal* integerV) ;

/*
    Functions: shunt_cs_recv_integerV
    map verilog "reg[31:0] 4 state aval,bval
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0

See Also:
  <shunt_cs_send_integerV>
    */
int shunt_cs_recv_integerV     (int sockid,const cs_header* h,svLogicVecVal* integerV);

/*
    Functions: shunt_cs_send_regN
    
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0

See Also:
  <shunt_cs_recv_regN>
    */
int shunt_cs_send_regN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg);

/*
    Functions:  shunt_cs_recv_regN 
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0

See Also:
  <shunt_cs_send_regN>
    */
int shunt_cs_recv_regN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);

//Section: Auxiliary tasks 
/*
  Function: shunt_cs_print_header
  print out SHUNT header 
  
  Parameters:
  
  h - cs_header structure
  data_type_names - data_type (see <SHUNT_INSTR_ENUM_NAMES> ) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  msg    - print out prefix
  
  Returns:
  void
  
See Also:
  <cs_header_t>
 
*/
void shunt_cs_print_header    (cs_header* h,char* data_type_names[],int last_enum,char* msg);

/*
  Function: shunt_cs_print_data_header
  print out SHUNT header 
  
  Parameters:
  
  h - cs_header structure
  h_data   - cs_data_header structure
  data_type_names - data_type (see <SHUNT_INSTR_ENUM_NAMES> ) or trnx_type names array
  last_enum       - number of data_type_names[] elements
  msg - print out prefix
  
  Returns:
  
  void
  
See Also:
  <cs_data_header_t>
 
*/
void shunt_cs_print_data_header (cs_header* h,cs_data_header* h_data,char* data_type_names[],int last_enum,char* msg);

#endif
