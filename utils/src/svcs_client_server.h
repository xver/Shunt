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
  Verilog Data Types Vectors: 
    
   Integer 2 states:
   SVCS_INT         - int            function :svcs_cs_xxxx_intV
   SVCS_SHORTINT    - shortint       function :svcs_cs_xxxx_shortV
   SVCS_LONGINT     - longint        function :svcs_cs_xxxx_longV
   SVCS_BYTE        - byte           function :svcs_cs_xxxx_byte
   SVCS_BIT         - bit            function :svcs_cs_xxx_bitN
   
   Integer 4 states:
   SVCS_INTEGER     - integer,time   function :svcs_cs_xxxx_integerV
   SVCS_REG         - reg,logic      function :svcs_cs_xxx_regN
   
   Non integer types IEEE 754:  
   SVCS_REAL        - real,realtime  function :svcs_cs_xxxx_doubleV
   SVCS_SHORTREAL   - shortreal      function :svcs_cs_xxxx_floatV
   SVCS_STRING      - string (N/A)   function :svcs_cs_xxx_byteV
   
   SVCS_A_STRUCTURE - complex data types/user defined data types : arrays/struct,union,enums (N/A)
   SVCS_HEADER_ONLY - cs_header_t header only                                                (N/A)
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



typedef enum {SVCS_INT,SVCS_REAL,SVCS_SHORTREAL,SVCS_STRING,SVCS_A_STRUCTURE,SVCS_INTEGER,SVCS_BYTE,SVCS_REG,SVCS_BIT,SVCS_SHORTINT,SVCS_LONGINT,SVCS_HEADER_ONLY} SVCV_INSTR_ENUM;
#define SVCV_INSTR_HASH_INDEX_DEFINE char* SVCV_INSTR_ENUM_NAMES[] = {"SVCS_INT","SVCS_REAL","SVCS_SHORTREAL","SVCS_STRING","SVCS_A_STRUCTURE","SVCS_INTEGER","SVCS_BYTE","SVCS_REG","SVCS_BIT","SVCS_SHORTINT","SVCS_LONGINT","SVCS_HEADER_ONLY"}



//-------------
//prototypes
//-------------

//Title: 3. Utilites: Client-Servercs_header

/*
  
Section: Data exchange utilities (header)

(start code)

typedef enum {SVCS_INT,SVCS_REAL,SVCS_SHORTREAL,SVCS_STRING,SVCS_A_STRUCTURE,SVCS_INTEGER,SVCS_BYTE,SVCS_REG,SVCS_BIT,SVCS_SHORTINT,SVCS_LONGINT,SVCS_HEADER_ONLY} SVCV_INSTR_ENUM;
#define SVCV_INSTR_HASH_INDEX_DEFINE char* SVCV_INSTR_ENUM_NAMES[] = {"SVCS_INT","SVCS_REAL","SVCS_SHORTREAL","SVCS_STRING","SVCS_A_STRUCTURE","SVCS_INTEGER","SVCS_BYTE","SVCS_REG","SVCS_BIT","SVCS_SHORTINT","SVCS_LONGINT","SVCS_HEADER_ONLY"}



typedef struct cs_header_t {
double   trnx_type;       // user defined transaction attribute
double   trnx_id;         // user defined unique transaction number
double   data_type;       // see SVCV_INSTR_ENUM
int      n_payloads;      // number of data payloads (for Array number of vectors)
} cs_header;

//  Array header extension
typedef struct cs_data_header_t {
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





// Section: Data exchange utilities (element)


/*
Function: svcs_cs_send_intV, svcs_cs_send_shortV,svcs_cs_send_longV
  send SVCS transaction with "int" ,"shortint","longint" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int,Short,Long   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_intV   (int sockid, const cs_header* header,const int* Int);
int svcs_cs_send_shortV (int sockid, const cs_header* header,const short int* Short);
int svcs_cs_send_longV  (int sockid, const cs_header* header,const long int* Long);

/*
  Function: svcs_cs_recv_intV,svcs_cs_recv_shortV,svcs_cs_recv_longV
  fetch SVCS transaction with "int","shortint","longint" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Int,Short,Long   - Data received
  
  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_intV   (int sockid, cs_header* header,int* Int);
int svcs_cs_recv_shortV (int sockid, cs_header* header,short int* Short);
int svcs_cs_recv_longV  (int sockid, cs_header* header,long int* Long);



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
  Function: svcs_cs_send_floatV
  send SVCS transaction with "float" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Float - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_floatV   (int sockid,const cs_header* header,const float* Float);

/*
  Function: svcs_cs_recv_floatV
  fetch SVCS transaction with "float" elements vector from TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  Float  - Data received
  
  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_floatV   (int sockid,cs_header* header,float* Float);

/*
  Function: svcs_cs_send_byteV
  send SVCS transaction with verilog byteV/string/C char* elements over TCP/IP
  
  Parameters:
  sockid - socket id
  header - cs_header structure
  byteV  - data to send
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_byteV   (int sockid,const cs_header* header,const char* byteV);

/*
  Function: svcs_cs_recv_byteV
  fetch SVCS transaction with verilog byteV/string/C char* elements from TCP/IP
  
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
                         data_type   - hash ("SVCS_A_STRUCTURE")
                         trnx_id    - random double
          payload->   size  > 1
          data - vector
---------------------------------------------------------------
 (end)

 */
/*
    Functions: svcs_dpi_cs_send_regA
    send SVCS transaction with "reg" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Reg - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_send_regA(int sockid,int n_payloads,const cs_data_header* h,const svLogicVecVal* Reg);

/*
    Functions: svcs_dpi_cs_send_bitA
    send SVCS transaction with "bit" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_send_bitA(int sockid,int n_payloads,const cs_data_header* h,const  svBitVecVal* Bit);

/*
    Functions: svcs_dpi_cs_send_integerA
    send SVCS transaction with "integer" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_send_integerA(int sockid,int n_payloads,const cs_data_header* h,const  svLogicVecVal* Integer);

/*
    Functions: svcs_dpi_cs_send_floatA
    send SVCS transaction with "shortreal" elements vector over TCP/IP
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_send_floatA (int sockid,int n_payloads,const cs_data_header* h,const float* Float);

/*
  Function: svcs_cs_send_shortA
  send SVCS transaction with "int" elements vector over TCP/IP
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init sever/client
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_shortA  (int sockid,int n_payloads,const cs_data_header* h,const short int * Int);


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
  Function: svcs_cs_send_longA
  send SVCS transaction with "int" elements vector over TCP/IP
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init sever/client
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_send_longA (int sockid,int n_payloads,const cs_data_header* h,const long int * Int);

/*
    Functions: svcs_dpi_cs_recv_regA
    SVCS transaction with "reg" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Reg - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_recv_regA(int sockid,int n_payloads,const cs_data_header* h,svLogicVecVal* Reg);

/*
    Functions: svcs_dpi_cs_recv_bitA
    SVCS transaction with "bit" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_recv_bitA(int sockid,int n_payloads,const cs_data_header* h, svBitVecVal* Bit);

/*
    Functions: svcs_dpi_cs_recv_integerA
    SVCS transaction with "integer" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_recv_integerA(int sockid,int n_payloads,const cs_data_header* h, svLogicVecVal* Integer);

/*
    Functions: svcs_dpi_cs_recv_floatA
    SVCS transaction with "shortreal" elements vector from TCP/IP socket
    NOTE: function is not implemented yet    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_recv_floatA (int sockid,int n_payloads,const cs_data_header* h,float* Float);

/*
  Function: svcs_cs_recv_shortA
  SVCS transaction with "int" elements vector from TCP/IP socket
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init sever/client
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_recv_shortA  (int sockid,int n_payloads,const cs_data_header* h,short int * Int);


/*
  Function: svcs_cs_recv_intA
  SVCS transaction with "int" elements vector from TCP/IP socket

  Parameters:
  sockid - socket id from init sever/client
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_recv_intA(int sockid,int n_payloads,const cs_data_header* h,int * Int);

/*
  Function: svcs_cs_recv_longA
  SVCS transaction with "int" elements vector from TCP/IP
  NOTE: function is not implemented yet

  Parameters:
  sockid - socket id from init sever/client
  n_payloads - number of data payloads
  h - cs_data_header structure
  Int   - data
  
  Returns:
  number of elements have been sent  : success > 0
*/
int svcs_cs_recv_longA (int sockid,int n_payloads,const cs_data_header* h,long int * Int);


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
int  svcs_cs_recv_doubleA    (int sockid,int n_payloads,cs_data_header* h,double* Double);



/*
  Function: svcs_cs_send_byteA
  send SVCS transaction with "byte" vectors array  over TCP/IP 
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure,
  n_payloads
  note: header.trnx_payload_size - The number of array entries is equal to the number of bytes 
  ArrayS  - data 

  Returns:number of elements have been sent  : success > 0
*/

int svcs_cs_send_byteA(int sockid,int n_payloads,cs_data_header* h,const char *ArrayS);



/*
  Function: svcs_cs_recv_byteA
  fetch SVCS transaction with byte" vectors array from TCP/IP  
  
  Parameters:
  sockid - socket id from init sever/client 
  h - cs_data_header structure
  ArrayS  - Data received
  
  Returns:
  number of elements have been received  : success > 0
*/
int svcs_cs_recv_byteA(int sockid,int n_payloads,cs_data_header* h,char* ArrayS);



/*
    Functions: svcs_dpi_cs_send_bitN
    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_send_bitN (int sockid,const cs_header* h,const svBitVecVal* bitN) ;
  /*
    Functions: svcs_cs_recv_bitN
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
int svcs_cs_recv_bitN     (int sockid,const cs_header* h,svBitVecVal* bitN);


/*
    Functions: svcs_dpi_cs_send_integerV
    map verilog "reg[31:0] 4 state aval,bval
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_send_integerV (int sockid,const cs_header* h,const svLogicVecVal* integerV) ;
  /*
    Functions: svcs_dpi_cs_recv_integerV
    map verilog "reg[31:0] 4 state aval,bval
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
int svcs_cs_recv_integerV     (int sockid,const cs_header* h,svLogicVecVal* integerV);
/*
    Functions: svcs_cs_send_regN
    
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int svcs_cs_send_regN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg);
/*
    Functions:  svcs_cs_recv_regN 
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
int svcs_cs_recv_regN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);

//Section: Auxiliary tasks 
/*
  Function: svcs_cs_print_intV
  print out IntV Data

  Parameters:

  h - cs_data_header structure
  Int  - Data to print
  msg  - print out prefix

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
  Function: svcs_cs_comp_doubleV
  compare two doubleV payloads

  Parameters:
  h - cs_header
  lhs,rhs - double V data
  Returns:
  success > 0
*/
int svcs_cs_comp_doubleV   (cs_header* h,double *lhs,double *rhs);


/*
  Function: svcs_cs_print_doubleV
  print out DoubleV Data

  Parameters:

  h - cs_data_header structure
  Double  - Data received
  msg    - print out prefix

  Returns:
  void
*/
void svcs_cs_print_doubleV   (cs_header* h,double *Double,char* msg);
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
/*
  Function: svcs_cs_print_dooubleA
  print out IntA Data

  Parameters:
  n_payloads - number of data payloads
  h - cs_data_header structure
  Double  - Data received
  msg    - print out prefix
  Returns:
   void
*/
void svcs_cs_print_doubleA   (int n_payloads,cs_data_header* h,double *Double,char* msg);


/*
  Function: svcs_cs_comp_dooubleA
  compare two intA payloads

  Parameters:
  n_payloads - number of data payloads
  lhs,rhs - doubleA data
  Returns:
  success > 0
*/
int svcs_cs_comp_doubleA   (int n_payloads,cs_data_header* h,double *lhs,double *rhs);
/*
  Function: svcs_cs_print_ByteA
  print out ByteA Data

  Parameters:
  n_payloads - number of data payloads
  h - cs_data_header structure
  Byte  - Data to print
  msg    - print out prefix
  Returns:
   void
*/
void svcs_cs_print_byteA   (int n_payloads,cs_data_header* h,char *Byte,char* msg);


/*
  Function: svcs_cs_comp_ByteA
  compare two ByteA payloads

  Parameters:
  n_payloads - number of data payloads
  lhs,rhs - ByteA data
  Returns:
  success > 0
*/
int svcs_cs_comp_byteA   (int n_payloads,cs_data_header* h,char *lhs,char *rhs);
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

int svcs_cs_recv_byteV   (int sockid,cs_header* header,char* byteV);

/*
  Function: svcs_cs_comp_byteV
  compare two char * payloads

  Parameters:
  h - cs_header
  lhs,rhs - string
  Returns:
  success > 0
*/
int svcs_cs_comp_byteV   (cs_header* h,char *lhs,char *rhs);
#endif
