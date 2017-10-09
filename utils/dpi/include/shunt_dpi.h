/*
=========================================================
 File        : shunt_dpi.h
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : shunt dpi bridge
 System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)
******************************************************
*/
#ifndef SHUNT_DPI_H_
#define SHUNT_DPI_H_

#ifdef SHUNT_SVDPI
#include "svdpi.h"
#endif

#include "shunt_primitives.h"
#include "shunt_client_server.h"
#include "shunt_user_api.h"

//-------------
//prototype
//-------------
// Title: DPI Direct Link

// Section: TCP/IP socket Target , Initiator initialization

/*
 Function: shunt_dpi_target_init 
 TCP/IP target initialization
 
 Parameters:
 
 portno   - socket port
 hostname - initiator name
 
 Returns: 
 socket id 
 
see (shunt_prim_init_tcptarget )  
*/
unsigned int shunt_dpi_target_init(const unsigned int portno,const char *hostname);


/*
 Function: shunt_dpi_initiator_init 
 TCP/IP initiator initialization
 
 Parameters: 
 portno - socket port
  
 Returns:  
 socket id
 
 see (shunt_prim_init_tcpinitiator)   
*/
unsigned int shunt_dpi_initiator_init(const unsigned int portno);

/*
 Function: shunt_dpi_send_short
  send verilog"shortint" /C "short int" data over TCP/IP

  Parameters:
   sockfd - socket id
   Short  -   data

  Returns:
   number of bytes have been sent : success > 0
   see (vcs_prim_send_short)
*/
int shunt_dpi_send_short  (const int sockfd,const short int Short);




/*
 Function: shunt_dpi_recv_short
  fetch verilog"shortint"/C "short int" data from TCP/IP socket

  Parameters:
   sockfd - socket id
   Short - data from socket

  Returns:
    number of bytes have been received  : success > 0

    see (shunt_prim_recv_in)
*/
int shunt_dpi_recv_short  (int sockfd,short int* Short);

/*
 Function: shunt_dpi_send_long
  send verilog"longint" /C "long int" data over TCP/IP

  Parameters:
   sockfd - socket id
   Long  -   data

  Returns:
   number of bytes have been sent : success > 0
   see (vcs_prim_send_long)
*/
int shunt_dpi_send_long  (const int sockfd,const long int Long);




/*
 Function: shunt_dpi_recv_long
  fetch verilog"longint"/C "long int" data from TCP/IP socket

  Parameters:
   sockfd - socket id
   Long - data from socket

  Returns:
    number of bytes have been received  : success > 0

    see (shunt_prim_recv_in)
*/
int shunt_dpi_recv_long  (int sockfd,long int* Long);

/*
 Function: shunt_dpi_send_int
  send verilog/C "int" data over TCP/IP

  Parameters:
   sockfd - socket id
   Int  -   data

  Returns:
   number of bytes have been sent : success > 0
   see (vcs_prim_send_int)

*/
int shunt_dpi_send_int    (const unsigned int sockfd,const int Int);

/*
 Function: shunt_dpi_recv_int
  fetch verilog/C "int" data from TCP/IP socket

  Parameters:
   sockfd - socket id
   Int - data from socket

  Returns:
    number of bytes have been received  : success > 0

    see (shunt_prim_recv_in)
*/
int shunt_dpi_recv_int (const unsigned int sockfd,int* Int);

/*
 Function: shunt_dpi_send_real
  send verilog "real"/C "double" over TCP/IP

  Parameters:
   sockfd - socket id
   Real  - data to send

  Returns:
  number of bytes have been sent : success > 0

    see (shunt_prim_send_double)
*/

int shunt_dpi_send_real      (const unsigned int sockfd,const double Real);
int shunt_dpi_send_realtime  (const unsigned int sockfd,const double Real);
int shunt_dpi_send_shortreal (const unsigned int sockfd,const float Real);
/*
  Function: shunt_dpi_recv_real
  fetch verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real - data from socket

  Returns:
 number of bytes have been sent : success > 0

    see (shunt_prim_recv_double)
*/
int shunt_dpi_recv_real      (const unsigned int sockfd,double* Real);
int shunt_dpi_recv_realtime  (const unsigned int sockfd,double* Real);
int shunt_dpi_recv_shortreal (const unsigned int sockfd,float* Real);
/*
 Function: shunt_dpi_send_byte
  send verilog "byte"/C "char" over TCP/IP

  Parameters:
   sockfd - socket id
   Byte  - data to send

  Returns:
    number of bytes have been sent : success =1

    see (shunt_prim_send_byte)
*/

int shunt_dpi_send_byte    (const unsigned int sockfd,const char Byte);
int shunt_dpi_send_bit     (const unsigned int sockfd,const svBit Bit);
int shunt_dpi_send_reg     (const unsigned int sockfd,const svLogic Reg);
int shunt_dpi_send_logic   (const unsigned int sockfd,const svLogic Logic);
/*
  Function: shunt_dpi_recv_byte
  fetch verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Byte - data from socket

  Returns:
 number of bytes have been sent : success = 1

    see (shunt_prim_recv_byte)
*/
int shunt_dpi_recv_byte    (const unsigned int sockfd,char* Byte);
int shunt_dpi_recv_bit     (const unsigned int sockfd,svBit* Bit);
int shunt_dpi_recv_reg     (const unsigned int sockfd,svLogic* Reg);
int shunt_dpi_reccv_logic  (const unsigned int sockfd,svLogic* Logic);
/*
  Function: shunt_dpi_send_intV,shunt_dpi_send_shortV
  send SHUNT transaction with "int" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  size   - number of vector elements
  Int    - data
  
  Returns:
  number of elements have been sent  : success > 0
  
  see ( shunt_cs_send_intV )
*/
int shunt_dpi_send_intV   (int sockid, const int size,const svOpenArrayHandle Int);
int shunt_dpi_send_shortV   (int sockid, const int size,const svOpenArrayHandle Int);

/*
 Function: shunt_dpi_send_byte4s
  send verilog "reg[7:0] 4 state aval,bval" over TCP/IP

  Parameters:
   sockfd - socket id
   Byte  - data to send

  Returns:
    number of bytes have been sent : success =1

    see (shunt_prim_send_byte)
*/

int shunt_dpi_send_byte4s (const unsigned int sockfd,svLogicVecVal* Byte);
/*
  Function: shunt_dpi_recv_byte4s
  fetch verilog "reg[7:0] 4 state aval,bval" from TCP/IP

  Parameters:
  sockfd - socket id
  Byte - data from socket

  Returns:
 number of bytes have been sent : success = 1

    see (shunt_prim_recv_byte)
*/
int shunt_dpi_recv_byte4s (const unsigned int sockfd,svLogicVecVal* Byte);

/*
 Function: shunt_dpi_send_integer
  send  verilog "reg[31:0] 4 state aval,bval" over TCP/IP

  Parameters:
   sockfd - socket id
   Int  -   data

  Returns:
   number of bytes have been sent : success > 0
   see (vcs_prim_send_int)

*/
int shunt_dpi_send_integer (const unsigned int sockfd,svLogicVecVal* Int);
int shunt_dpi_send_time    (const unsigned int sockfd,svLogicVecVal* Time);
/*
 Function: shunt_dpi_recv_integer
  fetch verilog "reg[31:0] 4 state aval,bval" from TCP/IP

  Parameters:
   sockfd - socket id
   Int - data from socket

  Returns:
    number of bytes have been received  : success > 0

    see (shunt_prim_recv_in)
*/
int shunt_dpi_recv_integer (const unsigned int sockfd,svLogicVecVal* Int);
int shunt_dpi_recv_time    (const unsigned int sockfd,svLogicVecVal* Time);
/*
 Function: shunt_dpi_send_integerV
  send  verilog "reg[31:0] 4 state aval,bval" over TCP/IP

  Parameters:
   sockfd - socket id
   Int  -   data

  Returns:
   number of bytes have been sent : success > 0
   see (vcs_prim_send_int)

*/
int shunt_dpi_send_integerV (const unsigned int sockid,const int size,const svLogicVecVal* IntegerV);

/*
 Function: shunt_dpi_recv_integerV
  fetch verilog "reg[31:0] 4 state aval,bval" from TCP/IP

  Parameters:
   sockfd - socket id
   Int - data from socket

  Returns:
    number of bytes have been received  : success > 0

    see (shunt_prim_recv_in)
*/
int shunt_dpi_recv_integerV (const unsigned int sockid,const int size,svLogicVecVal* IntegerV);

/*
  Function: shunt_dpi_recv_intV
  fetch SHUNT transaction with "int" elements vector  elements from TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of vector elements
  IntV  - Data received
  
  Returns:
  number of elements have been received  : success > 0

*/
int shunt_dpi_recv_intV(int sockid,int size,svOpenArrayHandle Int);


/*
  Function: shunt_dpi_send_realV
  send SHUNT transaction with "real" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of vector elements
  Real - data
  
  Returns:
  number of elements have been sent  : success > 0

  see ( shunt_cs_send_doubleV )
*/
int shunt_dpi_send_realV   (int sockid,const int size,const svOpenArrayHandle Real);

/*
  Function: shunt_dpi_recv_realV
  fetch SHUNT transaction with "real" elements vector from TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of vector elements
  Real  - Data received
  
  Returns:
  number of elements have been received  : success > 0

  see ( shunt_cs_recv_doubleV )
*/
int shunt_dpi_recv_realV   (int sockid,int size,svOpenArrayHandle Real);

/*
  Function: shunt_dpi_send_shortrealV
  send SHUNT transaction with "shortreal" elements vector over TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of vector elements
  Shortreal - data
  
  Returns:
  number of elements have been sent  : success > 0

  see ( shunt_cs_send_doubleV )
*/
int shunt_dpi_send_shortrealV   (int sockid,const int size,const svOpenArrayHandle Shortreal);

/*
  Function: shunt_dpi_recv_shortrealV
  fetch SHUNT transaction with "shortreal" elements vector from TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of vector elements
  Real  - Data received
  
  Returns:
  number of elements have been received  : success > 0

  see ( shunt_cs_recv_doubleV )
*/


/*
  Function: shunt_dpi_send_string
  send SHUNT transaction with verilog string/C char* elements over TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of string elements
  string  - data to send
  
  Returns:
  number of elements have been sent  : success > 0

  see ( shunt_cs_send_string )
*/
int shunt_dpi_send_string   (int sockid,int size,char* string);

/*
  Function: shunt_dpi_recv_string
  fetch SHUNT transaction with verilog string/C char* elements from TCP/IP
  
  Parameters:
  sockid - socket id
  size - number of string elements
  string  - Data received
  
 Returns:
 number of elements have been received  : success > 0

 see ( shunt_cs_recv_string )
*/

int shunt_dpi_recv_string   (int sockid,int size,char** string);



/*
  Function: shunt_dpi_hash 
  simple hash function 
  
  Parameters: 
  str - hash key
  
  Returns: 
  hash value
*/

double shunt_dpi_hash(const char *str);

/*
  Function: shunt_dpi_send_header
  send SHUNT header over TCP/IP
  
  Parameters:
  
  sockid - socket id from init sever/target 
  h - cs_header structure
  
  Returns:
  
  number of elements have been sent  : success > 0
*/

int shunt_dpi_send_header    (int sockid,cs_header* h);

/*
  Function: shunt_dpi_send_data_header
  send SHUNT header over TCP/IP
  
  Parameters:
  
  sockid - socket id from init sever/target 
  h - cs_header structure
  n_payloads - number of data payloads
  
  Returns:
  
  number of elements have been sent  : success > 0
*/
int shunt_dpi_send_data_header (int sockid,cs_header* h,double data_type,svOpenArrayHandle trnx_payload_sizes);

/*
  Function: shunt_dpi_recv_header
  fetch SHUNT transaction header from TCP/IP socket
  
  Parameters:
  
  sockid - socket id from init sever/target 
  header - cs_header structure
  
  Returns:
  
  number of elements have been received  : success > 0
  
*/
int shunt_dpi_recv_header   (int sockid,cs_header* h);

/*
  Function: shunt_dpi_recv_data_header
  fetch SHUNT transaction header from TCP/IP socket
  
  Parameters:
  sockid - socket id from init sever/target 
  h - cs_data_header structure
  
  Returns:
  number of elements have been received  : success > 0
  
*/
int shunt_dpi_recv_data_header   (int sockid,cs_header* h,double* data_type,svOpenArrayHandle**  trnx_payload_sizes);
/*
  Function: shunt_dpi_hs_send

  send data over TCP/IP.
  Supported data types are:
  int , intV ,double ,doubleV

  Parameters:

  Perm parameters:
   sockid - socket id from init sever/target
   h_trnx - cs_header structure

   Non-perm  parameters are:
   h_data - cs_data_header  structure
   Int,Double,String - data to send


   Returns:
  number of elements have been sent  : success > 0
*/


int shunt_dpi_hs_send           (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int shunt_dpi_hs_send_short     (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int shunt_dpi_hs_send_int       (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int shunt_dpi_hs_send_long      (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int shunt_dpi_hs_send_byte      (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int shunt_dpi_hs_send_string    (int sockid,cs_header* h_trnx,char* Array);
int shunt_dpi_hs_send_integer   (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int shunt_dpi_hs_send_real      (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);
int shunt_dpi_hs_send_shortreal (int sockid,cs_header* h_trnx,svOpenArrayHandle Array);

/*
  Function: shunt_dpi_hs_recv
  fetch data from TCP/IP socket
  Supported data types are:
  int , intV ,double ,doubleV,string,

  Parameters:

  Perm parameters:
  sockid - socket id from init sever/target
  h_trnx - cs_header structure

  Non-perm  parameters are:
  h_data - cs_data_header  structure
  Int,Double,String - Data received


  Returns:
  number of elements have been received  : success > 0

*/
int shunt_dpi_hs_recv           (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int shunt_dpi_hs_recv_short     (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int shunt_dpi_hs_recv_int       (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int shunt_dpi_hs_recv_long      (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int shunt_dpi_hs_recv_byte      (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int shunt_dpi_hs_recv_string    (int sockid,cs_header* h_trnx,char** Array);
int shunt_dpi_hs_recv_integer   (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int shunt_dpi_hs_recv_real      (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
int shunt_dpi_hs_recv_shortreal (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array);
/*
    Function: shunt_dpi_hs_send_regN
    send 4-state verilog reg[n:0] variable over TCP/IP
    
    Parameters:
    sockid - socket id
    h_trnx - trnx header 
    Reg  - data to send
    
    Returns:
    number of 4 state variable byte size have been sent : success > 0
    
    see (shunt_prim_send_byte)
    */
int shunt_dpi_hs_send_regN   (const unsigned int sockfd,cs_header* h_trnx,const svLogicVecVal* Reg);
int shunt_dpi_hs_send_logicN (const unsigned int sockfd,cs_header* h_trnx,const svLogicVecVal* Reg);



/*
    Function: shunt_dpi_hs_recv_regN
    fetch 4-state verilog reg[n:0] variable from TCP/IP socket
    
    Parameters:
    sockid - socket id
    h_trnx - trnx header 
    Reg  - data to send
    
    Returns:
    number of 4 state variable byte size have been recie   : success > 0
    
    see (shunt_prim_recv_byte)
    */
int shunt_dpi_hs_recv_regN    (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);
int shunt_dpi_hs_recv_logicN  (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);


/*
    Functions: shunt_dpi_hs_send_bitN
    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
int shunt_dpi_send_bitN  (const int sockfd,const int size,const svBitVecVal* bitN);
int shunt_dpi_hs_send_bitN  (const int sockfd,const cs_header* h_trnx,const svBitVecVal* bitN);   
   /*
    Functions: shunt_dpi_hs_recv_bitN
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
int shunt_dpi_recv_bitN     (const int sockfd,const int size,svBitVecVal* bitN);
int shunt_dpi_hs_recv_bitN  (const int sockfd,const cs_header* h_trnx,svBitVecVal* bitN);





#endif /* SHUNT_DPI_H_ */
