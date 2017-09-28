/* 
   ============================================================================
   File        : shunt_client_server.h
   Version     : 1.0.0
   Copyright (c) 2016-2017 IC Verimeter. All rights reserved.  
   Licensed under the MIT License. 
   See LICENSE file in the project root for full license information.  
   Description : Target-Initiator (Client-Server aka cs) handshake utils   
                 System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)
  ******************************************************
  Verilog Data Types Vectors: 
    
   Integer 2 states:
   SHUNT_INT         - int            function :shunt_cs_xxxx_intV
   SHUNT_SHORTINT    - shortint       function :shunt_cs_xxxx_shortV
   SHUNT_LONGINT     - longint        function :shunt_cs_xxxx_longV
   SHUNT_BYTE        - byte           function :shunt_cs_xxxx_byte
   SHUNT_BIT         - bit            function :shunt_cs_xxx_bitN
   
   Integer 4 states:
   SHUNT_INTEGER     - integer,time   function :shunt_cs_xxxx_integerV
   SHUNT_REG         - reg,logic      function :shunt_cs_xxx_regN
   
   Non integer types IEEE 754:  
   SHUNT_REAL        - real,realtime  function :shunt_cs_xxxx_doubleV
   SHUNT_SHORTREAL   - shortreal      function :shunt_cs_xxxx_floatV
   SHUNT_STRING      - string (N/A)   function :shunt_cs_xxx_byteV
   
   SHUNT_A_STRUCTURE - complex data types/user defined data types : arrays/struct,union,enums (N/A)
   SHUNT_HEADER_ONLY - cs_header_t header only                                                (N/A)
    ============================================================================
*/
#ifndef SHUNT_CLIENT_SERVER_H_
#define SHUNT_CLIENT_SERVER_H_

#include "shunt_primitives.h"



typedef enum {SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_BIT,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} SHUNT_INSTR_ENUM;
#define SHUNT_INSTR_HASH_INDEX_DEFINE char* SHUNT_INSTR_ENUM_NAMES[] = {"SHUNT_INT","SHUNT_REAL","SHUNT_SHORTREAL","SHUNT_STRING","SHUNT_A_STRUCTURE","SHUNT_INTEGER","SHUNT_BYTE","SHUNT_REG","SHUNT_BIT","SHUNT_SHORTINT","SHUNT_LONGINT","SHUNT_HEADER_ONLY"}



//-------------
//prototypes
//-------------

//Title: 3. Utilites: Client-Initiator cs_header

/*
  
Section: Data exchange utilities (header)

(start code)

typedef enum {SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_BIT,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} SHUNT_INSTR_ENUM;
#define SHUNT_INSTR_HASH_INDEX_DEFINE char* SHUNT_INSTR_ENUM_NAMES[] = {"SHUNT_INT","SHUNT_REAL","SHUNT_SHORTREAL","SHUNT_STRING","SHUNT_A_STRUCTURE","SHUNT_INTEGER","SHUNT_BYTE","SHUNT_REG","SHUNT_BIT","SHUNT_SHORTINT","SHUNT_LONGINT","SHUNT_HEADER_ONLY"}



typedef struct cs_header_t {
double   trnx_type;       // user defined transaction attribute
double   trnx_id;         // user defined unique transaction number
double   data_type;       // see SHUNT_INSTR_ENUM
int      n_payloads;      // number of data payloads (for Array number of vectors)
} cs_header;

//  Array header extension
typedef struct cs_data_header_t {
double   data_type;       // see SHUNT_INSTR_ENUM
int     *trnx_payload_sizes; // array of payload sizes, number of array elements are equal to n_payloads
} cs_data_header;

(end)
*/

typedef struct cs_data_header_t {
  double   data_type;       // see SHUNT_INSTR_ENUM
  int     *trnx_payload_sizes;
} cs_data_header;

typedef struct cs_header_t {
  double   trnx_type;
  double   trnx_id;
  double   data_type;
  int      n_payloads;
} cs_header;

/*
  Function: shunt_cs_data_type_hash
  map data_type enum to the corresponding hash
  
  Parameters:
  
  data_type/trnx_type - for valid data_type see SHUNT_INSTR_ENUM
  data_type_names - data_type (see SHUNT_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  
  Returns:
  
  hash index
*/
double shunt_cs_data_type_hash(int data_type,char* data_type_names[],int last_enum);

/*
  Function: shunt_cs_data_type
  map data_type hash to the corresponding enum
  
  Parameters:
  
  data_type - hash index
  data_type_names - data_type (see SHUNT_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  
  Returns:
  
  valid data_type see SHUNT_INSTR_ENUM
  -1 - No enum
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
  
*/
int shunt_cs_recv_data_header   (int sockid,int n_payloads,cs_data_header* h);





// Section: Data exchange utilities (element)


/*
Function: shunt_cs_send_intV, shunt_cs_send_shortV,shunt_cs_send_longV
  send SHUNT transaction with "int" ,"shortint","longint" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int,Short,Long   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_send_intV   (int sockid, const cs_header* header,const int* Int);
int shunt_cs_send_shortV (int sockid, const cs_header* header,const short int* Short);
int shunt_cs_send_longV  (int sockid, const cs_header* header,const long int* Long);

/*
  Function: shunt_cs_recv_intV,shunt_cs_recv_shortV,shunt_cs_recv_longV
  fetch SHUNT transaction with "int","shortint","longint" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int,Short,Long   - Data received
  
  Returns:
  number of elements have been received  : success > 0
*/
int shunt_cs_recv_intV   (int sockid, cs_header* header,int* Int);
int shunt_cs_recv_shortV (int sockid, cs_header* header,short int* Short);
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
*/



/*
 Section: Data exchange utilities (array)
 
 (start code)
NOTE: Not suported with 1.0 release
 ---------------------------------------------------------------
array ->  sockid - socket id
          header ->   trnx_atribute - hash/random double
                         data_type   - hash ("SHUNT_A_STRUCTURE")
                         trnx_id    - random double
          payload->   size  > 1
          data - vector
---------------------------------------------------------------
 (end)

 */
/*
    Functions: shunt_dpi_cs_send_regA
    send SHUNT transaction with "reg" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Reg - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_send_regA(int sockid,int n_payloads,const cs_data_header* h,const svLogicVecVal* Reg);

/*
    Functions: shunt_dpi_cs_send_bitA
    send SHUNT transaction with "bit" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_send_bitA(int sockid,int n_payloads,const cs_data_header* h,const  svBitVecVal* Bit);

/*
    Functions: shunt_dpi_cs_send_integerA
    send SHUNT transaction with "integer" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_send_integerA(int sockid,int n_payloads,const cs_data_header* h,const  svLogicVecVal* Integer);

/*
    Functions: shunt_dpi_cs_send_floatA
    send SHUNT transaction with "shortreal" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_send_floatA (int sockid,int n_payloads,const cs_data_header* h,const float* Float);

/*
  Function: shunt_cs_send_shortA
  send SHUNT transaction with "int" elements vector over TCP/IP
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init Target-Initiator (Client-Server)
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_send_shortA  (int sockid,int n_payloads,const cs_data_header* h,const short int * Int);


/*
  Function: shunt_cs_send_intA
  send SHUNT transaction with "int" elements vector over TCP/IP

  Parameters:
  sockid - socket id from init Target-Initiator (Client-Server)
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_send_intA (int sockid,int n_payloads,const cs_data_header* h,const int * Int);

/*
  Function: shunt_cs_send_longA
  send SHUNT transaction with "int" elements vector over TCP/IP
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init Target-Initiator (Client-Server)
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_send_longA (int sockid,int n_payloads,const cs_data_header* h,const long int * Int);

/*
    Functions: shunt_dpi_cs_recv_regA
    SHUNT transaction with "reg" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Reg - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_recv_regA(int sockid,int n_payloads,const cs_data_header* h,svLogicVecVal* Reg);

/*
    Functions: shunt_dpi_cs_recv_bitA
    SHUNT transaction with "bit" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_recv_bitA(int sockid,int n_payloads,const cs_data_header* h, svBitVecVal* Bit);

/*
    Functions: shunt_dpi_cs_recv_integerA
    SHUNT transaction with "integer" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_recv_integerA(int sockid,int n_payloads,const cs_data_header* h, svLogicVecVal* Integer);

/*
    Functions: shunt_dpi_cs_recv_floatA
    SHUNT transaction with "shortreal" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_recv_floatA (int sockid,int n_payloads,const cs_data_header* h,float* Float);

/*
  Function: shunt_cs_recv_shortA
  SHUNT transaction with "int" elements vector from TCP/IP socket
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init Target-Initiator (Client-Server)
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_recv_shortA  (int sockid,int n_payloads,const cs_data_header* h,short int * Int);


/*
  Function: shunt_cs_recv_intA
  SHUNT transaction with "int" elements vector from TCP/IP socket

  Parameters:
  sockid - socket id from init Target-Initiator (Client-Server)
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_recv_intA(int sockid,int n_payloads,const cs_data_header* h,int * Int);

/*
  Function: shunt_cs_recv_longA
  SHUNT transaction with "int" elements vector from TCP/IP
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init Target-Initiator (Client-Server)
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_recv_longA (int sockid,int n_payloads,const cs_data_header* h,long int * Int);


/*
  Function: shunt_cs_send_doubleV
  send SHUNT transaction with "double" elements vector over TCP/IP 
  
  Parameters:
  sockid - socket id from init Target/Initiator
  h - cs_data_header structure
  Double - data
  int n_payloads - number of data payloads
  
  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_cs_send_doubleA   (int sockid,int n_payloads,const cs_data_header* h,const double* Double);

/*
 Function: shunt_cs_recv_doubleV
 fetch SHUNT transaction with "double" elements vector from TCP/IP 
 
 Parameters:
 sockid - socket id from init Target/Initiator
 h - cs_data_header structure
 Double  - Data received
 n_payloads - number of data payloads
 
 Returns:
 number of elements have been received  : success > 0
*/
int  shunt_cs_recv_doubleA    (int sockid,int n_payloads,cs_data_header* h,double* Double);



/*
  Function: shunt_cs_send_byteA
  send SHUNT transaction with "byte" vectors array  over TCP/IP 
  
  Parameters:
  sockid - socket id from init Target/Initiator
  h - cs_data_header structure,
  n_payloads
  note: header.trnx_payload_size - The number of array entries is equal to the number of bytes 
  ArrayS  - data 

  Returns:number of elements have been sent  : success > 0
*/

int shunt_cs_send_byteA(int sockid,int n_payloads,cs_data_header* h,const char *ArrayS);



/*
  Function: shunt_cs_recv_byteA
  fetch SHUNT transaction with byte" vectors array from TCP/IP  
  
  Parameters:
  sockid - socket id from init Target/Initiator
  h - cs_data_header structure
  ArrayS  - Data received
  
  Returns:
  number of elements have been received  : success > 0
*/
int shunt_cs_recv_byteA(int sockid,int n_payloads,cs_data_header* h,char* ArrayS);



/*
    Functions: shunt_dpi_cs_send_bitN
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
    */
int shunt_cs_recv_bitN     (int sockid,const cs_header* h,svBitVecVal* bitN);


/*
    Functions: shunt_dpi_cs_send_integerV
    map verilog "reg[31:0] 4 state aval,bval
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_cs_send_integerV (int sockid,const cs_header* h,const svLogicVecVal* integerV) ;
  /*
    Functions: shunt_dpi_cs_recv_integerV
    map verilog "reg[31:0] 4 state aval,bval
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
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
    */
int shunt_cs_recv_regN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);

//Section: Auxiliary tasks 
/*
  Function: shunt_cs_print_intV
  print out IntV Data

  Parameters:

  h - cs_data_header structure
  Int  - Data to print
  msg  - print out prefix

  Returns:
  void
*/
void shunt_cs_print_intV   (cs_header* h,int *Int,char* msg);


/*
  Function: shunt_cs_comp_intV
  compare two intV payloads

  Parameters:
  h - cs_header
  lhs,rhs - intA data
  Returns:
  success > 0
*/
int shunt_cs_comp_intV   (cs_header* h,int *lhs,int *rhs);
/*
  Function: shunt_cs_comp_doubleV
  compare two doubleV payloads

  Parameters:
  h - cs_header
  lhs,rhs - double V data
  Returns:
  success > 0
*/
int shunt_cs_comp_doubleV   (cs_header* h,double *lhs,double *rhs);


/*
  Function: shunt_cs_print_doubleV
  print out DoubleV Data

  Parameters:

  h - cs_data_header structure
  Double  - Data received
  msg    - print out prefix

  Returns:
  void
*/
void shunt_cs_print_doubleV   (cs_header* h,double *Double,char* msg);
/*
  Function: shunt_cs_print_intA
  print out IntA Data

  Parameters:
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int  - Data received
  msg    - print out prefix
  Returns:
   void
*/
void shunt_cs_print_intA   (int n_payloads,cs_data_header* h,int *Int,char* msg);


/*
  Function: shunt_cs_comp_intA
  compare two intA payloads

  Parameters:
  n_payloads - number of data payloads
  lhs,rhs - intA data
  Returns:
  success > 0
*/
int shunt_cs_comp_intA   (int n_payloads,cs_data_header* h,int *lhs,int *rhs);

/*
  Function: shunt_cs_print_header
  print out SHUNT header 
  
  Parameters:
  
  h - cs_header structure
  data_type_names - data_type (see SHUNT_INSTR_ENUM_NAMES[]) or trnx_type names array 
  last_enum       - number of data_type_names[] elements
  msg    - print out prefix
  
  Returns:
  
  void
*/
void shunt_cs_print_header    (cs_header* h,char* data_type_names[],int last_enum,char* msg);


/*
  Function: shunt_cs_print_data_header
  print out SHUNT header 
  
  Parameters:
  
  h - cs_header structure
  h_data   - cs_data_header structure
  data_type_names - data_type (see SHUNT_INSTR_ENUM_NAMES[]) or trnx_type names array
  last_enum       - number of data_type_names[] elements
  msg - print out prefix
  
  Returns:
  
  void
*/

void shunt_cs_print_data_header (cs_header* h,cs_data_header* h_data,char* data_type_names[],int last_enum,char* msg);
/*
  Function: shunt_cs_print_dooubleA
  print out IntA Data

  Parameters:
  n_payloads - number of data payloads
  h - cs_data_header structure
  Double  - Data received
  msg    - print out prefix
  Returns:
   void
*/
void shunt_cs_print_doubleA   (int n_payloads,cs_data_header* h,double *Double,char* msg);


/*
  Function: shunt_cs_comp_dooubleA
  compare two intA payloads

  Parameters:
  n_payloads - number of data payloads
  lhs,rhs - doubleA data
  Returns:
  success > 0
*/
int shunt_cs_comp_doubleA   (int n_payloads,cs_data_header* h,double *lhs,double *rhs);
/*
  Function: shunt_cs_print_ByteA
  print out ByteA Data

  Parameters:
  n_payloads - number of data payloads
  h - cs_data_header structure
  Byte  - Data to print
  msg    - print out prefix
  Returns:
   void
*/
void shunt_cs_print_byteA   (int n_payloads,cs_data_header* h,char *Byte,char* msg);


/*
  Function: shunt_cs_comp_ByteA
  compare two ByteA payloads

  Parameters:
  n_payloads - number of data payloads
  lhs,rhs - ByteA data
  Returns:
  success > 0
*/
int shunt_cs_comp_byteA   (int n_payloads,cs_data_header* h,char *lhs,char *rhs);
/*
  Function: shunt_cs_comp_header
  compare two SHUNT headers

  Parameters:
  
  h_lhs,h_rhs - two cs headers
  Returns:
  
  success > 0
*/
int shunt_cs_comp_header    (cs_header h_lhs,cs_header h_rhs);

/*
  Function: shunt_cs_comp_data_header
  compare two SHUNT data headers
  
  Parameters:
  h_lhs,h_rhs - two cs data headers
  n_payloads - number of data payloads
  Returns:
  success > 0
*/
int shunt_cs_comp_data_header (cs_data_header h_lhs,cs_data_header h_rhs,int n_payloads);

int shunt_cs_recv_byteV   (int sockid,cs_header* header,char* byteV);

/*
  Function: shunt_cs_comp_byteV
  compare two char * payloads

  Parameters:
  h - cs_header
  lhs,rhs - string
  Returns:
  success > 0
*/
int shunt_cs_comp_byteV   (cs_header* h,char *lhs,char *rhs);
#endif
