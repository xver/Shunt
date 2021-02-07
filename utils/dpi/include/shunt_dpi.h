/*
=========================================================
 File        : shunt_dpi.h
 Copyright (c) 2016-2021 IC Verimeter. All rights reserved.
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

  See Also:
  - <shunt_prim_init_target>

*/
unsigned int shunt_dpi_target_init(const unsigned int portno,const char *hostname);


/*
  Function: shunt_dpi_initiator_init
  TCP/IP  "one server" - "one target" poit-to-point initiator  initialization

  Parameters:

  portno - socket port

  Returns:

  socket id

  See Also:
  - <shunt_prim_init_initiator>

*/
unsigned int shunt_dpi_initiator_init(const unsigned int portno);


/*
 Function: shunt_dpi_close_socket
 terminates TCP socket

 Parameters:

  fd - socket id

 Returns:
 N/A

*/
void shunt_dpi_close_socket(int fd);

/*
 Function: shunt_dpi_unblock_socket
 sets TCP socket unblocked mode

 Parameters:
  flag -  1/0- unblocked(deafult)/blocked
  fd - socket id

 Returns:

 N/A

*/
void shunt_dpi_unblock_socket(int flag,int fd);



/*
  Function: shunt_dpi_tcp_nodelay_socket

  enable/disable Nagle algorithm (TCP_NODELAY)

  Parameters:

  sockfd - socket
  flag -  1/0- enable/disable Nagle algorithm (TCP_NODELAY)

  Returns:
  N/A

*/
void shunt_dpi_tcp_nodelay_socket(int flag, int sockfd);

/*
  Function: shunt_dpi_get_status_socket
  returns status for <fd> TCP socket <event>

  Parameters:
  sockfd - socket
  short event-  the <event> mask is specifying following

  - 0- is equal equal POLLIN, data is ready to recv(),

  - 1- is equal to POLLOUT, socket can send() data to this socket without blocking

  - else is equal to POLLNVAL, function returns "process failed" status;

  Returns:
  socket even status

  -  "0"- No <event>

  -  "-1"- <event> process has failed

  -  "1"- <event> occurs

*/

int shunt_dpi_get_status_socket(int fd,int event);


/*
  Function: shunt_dpi_listener_init
  Multi-Slave TCP IP initialisation, create TCP/IP a parent(listener) and start listening for client connections

  Parameters:

  portno - socket port

  Returns:

  socket id -  parent socket id
*/
unsigned int shunt_dpi_listener_init(const unsigned int portno);

/*
  Function: shunt_dpi_tcp_connect
  Multi-Slave TCP IP initialisation, establish TCP/IP  initiator-target connection

  Parameters:
  socket id - parent socket id

  Returns:
   socket id - child socket id
 */
unsigned int shunt_dpi_tcp_connect(const unsigned int parentfd);

// Section: Data exchange (prim)

/*
  Function: shunt_dpi_send_short
  send verilog"shortint" /C "short int" data over TCP/IP

  Parameters:
  sockfd - socket id
  Short  -   data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  - <shunt_prim_send_short>
  - <shunt_dpi_recv_short>
*/
int shunt_dpi_send_short  (const int sockfd,const short int Short);

/*
  Function: shunt_dpi_recv_short
  fetch verilog"shortint"/C "short int" data from TCP/IP socket

  Parameters:
  sockfd - socket id
  Short - data

  Returns:
  number of bytes have been received  : success > 0


  See Also:
  - <shunt_prim_recv_short>
  - <shunt_dpi_send_short>

*/
int shunt_dpi_recv_short  (int sockfd,short int* Short);

/*
  Function: shunt_dpi_send_long
  send verilog"longint" /C "long" data over TCP/IP

  Parameters:
  sockfd - socket id
  Long  -   data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  - <shunt_prim_send_long>
  - <shunt_dpi_recv_long>
*/
int shunt_dpi_send_long  (const int sockfd,const long Long);


/*
  Function: shunt_dpi_recv_long
  fetch verilog"longint"/C "long" data from TCP/IP socket

  Parameters:
  sockfd - socket id
  Long - data

  Returns:
  number of bytes have been received  : success > 0


  See Also:
  - <shunt_prim_recv_long>
  - <shunt_dpi_send_long>
*/
int shunt_dpi_recv_long  (int sockfd,long* Long);

/*
  Function: shunt_dpi_send_int
  send verilog/C "int" data over TCP/IP

  Parameters:
  sockfd - socket id
  Int  -   data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  - <shunt_prim_send_int>
  - <shunt_dpi_recv_int>
*/
int shunt_dpi_send_int    (const unsigned int sockfd,const int Int);

/*
  Function: shunt_dpi_recv_int
  fetch verilog/C "int" data from TCP/IP socket

  Parameters:
  sockfd - socket id
  Int - data

  Returns:
  number of bytes have been received  : success > 0


  See Also:
  - <shunt_prim_recv_int>
  - <shunt_dpi_send_int>

*/
int shunt_dpi_recv_int (const unsigned int sockfd,int* Int);

/*
  Function: shunt_dpi_send_real
  send verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real  - data

  Returns:
  number of bytes have been sent : success > 0


  See Also:
  - <shunt_prim_send_double>
  - <shunt_dpi_recv_real>

*/
int shunt_dpi_send_real      (const unsigned int sockfd,const double Real);

/*
  Function: shunt_dpi_recv_real
  fetch verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real - data

  Returns:
  number of bytes have been sent : success > 0


  See Also:
  - <shunt_prim_recv_double>
  - <shunt_dpi_send_real>
*/
int shunt_dpi_recv_real      (const unsigned int sockfd,double* Real);

/*
  Function: shunt_dpi_send_realtime
  send verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real  - data

  Returns:
  number of bytes have been sent : success > 0


  See Also:
  - <shunt_prim_send_double>
  - <shunt_dpi_recv_realtime>
*/
int shunt_dpi_send_realtime  (const unsigned int sockfd,const double Real);

/*
  Function: shunt_dpi_recv_realtime
  fetch verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real - data

  Returns:
  number of bytes have been sent : success > 0


  See Also:
  - <shunt_prim_recv_double>
  - <shunt_dpi_send_realtime>
*/
int shunt_dpi_recv_realtime  (const unsigned int sockfd,double* Real);

/*
  Function: shunt_dpi_send_shortreal
  send verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real  - data

  Returns:
  number of bytes have been sent : success > 0


  See Also:
  - <shunt_prim_send_float>
  - <shunt_dpi_recv_shortreal>
*/
int shunt_dpi_send_shortreal (const unsigned int sockfd,const float Real);


/*
  Function: shunt_dpi_recv_shortreal
  fetch verilog "real"/C "double" over TCP/IP

  Parameters:
  sockfd - socket id
  Real - data

  Returns:
  number of bytes have been sent : success > 0


  See Also:
  - <shunt_prim_recv_float>
  - <shunt_dpi_send_shortrea>
*/
int shunt_dpi_recv_shortreal (const unsigned int sockfd,float* Real);

/*
  Function: shunt_dpi_send_byte
  send verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Byte  - data

  Returns:
  number of bytes have been sent : success =1


  See Also:
  - <shunt_prim_send_byte>
  - <shunt_dpi_recv_byte>

*/
int shunt_dpi_send_byte    (const unsigned int sockfd,const char Byte);

/*
  Function: shunt_dpi_recv_byte
  fetch verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Byte - data

  Returns:
  number of bytes have been sent : success = 1


  See Also:
  - <shunt_prim_recv_byte>
  - <shunt_dpi_send_byte>
*/
int shunt_dpi_recv_byte    (const unsigned int sockfd,char* Byte);

/*
  Function: shunt_dpi_send_bit
  send verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Bit  - data

  Returns:
  number of bytes have been sent : success =1


  See Also:
  - <shunt_prim_send_byte>
  - <shunt_dpi_recv_bit>
*/
int shunt_dpi_send_bit     (const unsigned int sockfd,const svBit Bit);

/*
  Function: shunt_dpi_recv_bit
  fetch verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Bit - data

  Returns:
  number of bytes have been sent : success = 1


  See Also:
  - <shunt_prim_recv_byte>
  - <shunt_dpi_send_bit >
*/
int shunt_dpi_recv_bit     (const unsigned int sockfd,svBit* Bit);

/*
  Function: shunt_dpi_send_reg
  send verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Reg  - data

  Returns:
  number of bytes have been sent : success =1


  See Also:
  - <shunt_prim_send_byte>
  - <shunt_dpi_recv_reg>
*/
int shunt_dpi_send_reg     (const unsigned int sockfd,const svLogic Reg);

/*
  Function: shunt_dpi_recv_reg
  fetch verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Reg - data

  Returns:
  number of bytes have been sent : success = 1


  See Also:
  - <shunt_prim_recv_byte>
  - <shunt_dpi_send_reg>
*/
int shunt_dpi_recv_reg     (const unsigned int sockfd,svLogic* Reg);

/*
  Function: shunt_dpi_send_logic
  send verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Logic  - data

  Returns:
  number of bytes have been sent : success =1


  See Also:
  - <shunt_prim_send_byte>
  - <shunt_dpi_recv_logic>
*/
int shunt_dpi_send_logic   (const unsigned int sockfd,const svLogic Logic);

/*
  Function: shunt_dpi_recv_logic
  fetch verilog "byte"/C "char" over TCP/IP

  Parameters:
  sockfd - socket id
  Logic - data

  Returns:
  number of bytes have been sent : success = 1


  See Also:
  - <shunt_prim_recv_byte>
  - <shunt_dpi_send_logic>
*/
int shunt_dpi_recv_logic  (const unsigned int sockfd,svLogic* Logic);

/*
  Function: shunt_dpi_send_integer
  send  verilog "reg[31:0] 4 state aval,bval" over TCP/IP

  Parameters:
  sockfd - socket id
  Int  -   data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  - <shunt_prim_send_integer>
  - <shunt_dpi_recv_integer>
*/
int shunt_dpi_send_integer (const unsigned int sockfd,svLogicVecVal* Int);

/*
  Function: shunt_dpi_recv_integer
  fetch verilog "reg[31:0] 4 state aval,bval" from TCP/IP

  Parameters:
  sockfd - socket id
  Int - data

  Returns:
  number of bytes have been received  : success > 0


  See Also:
  - <shunt_prim_recv_integer>
  - <shunt_dpi_send_integer>
*/
int shunt_dpi_recv_integer (const unsigned int sockfd,svLogicVecVal* Int);

/*
  Function: shunt_dpi_send_time
  send  verilog "reg[31:0] 4 state aval,bval" over TCP/IP

  Parameters:
  sockfd - socket id
  Time  -   data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  - <shunt_prim_send_int>
  - <shunt_dpi_recv_time>
*/
int shunt_dpi_send_time    (const unsigned int sockfd,svLogicVecVal* Time);

/*
  Function: shunt_dpi_recv_time
  fetch verilog "reg[31:0] 4 state aval,bval" from TCP/IP

  Parameters:
  sockfd - socket id
  Time - data

  Returns:
  number of bytes have been received  : success > 0


  See Also:
  - <shunt_prim_recv_int>
  - <shunt_dpi_send_time>
*/
int shunt_dpi_recv_time    (const unsigned int sockfd,svLogicVecVal* Time);

// Section: Data exchange (cs)
/*
  Function: shunt_dpi_send_intV
  send SHUNT transaction with "int" elements vector over TCP/IP

  Parameters:
  sockid - socket id
  size   - number of vector elements
  Int    - data

  Returns:
  number of elements have been sent  : success > 0

  See Also:
  - <shunt_cs_send_intV>
  - <shunt_dpi_recv_intV>
*/
int shunt_dpi_send_intV   (int sockid, const int size,const svOpenArrayHandle Int);

/*
  Function: shunt_dpi_recv_intV
  fetch SHUNT transaction with "int" elements vector  elements from TCP/IP

  Parameters:
  sockid - socket id
  size - number of vector elements
  IntV  - data

  Returns:
  number of elements have been received  : success > 0

  See Also:
  - <shunt_cs_recv_intV>
  - <shunt_dpi_send_intV>
*/
int shunt_dpi_recv_intV(int sockid,int size,svOpenArrayHandle Int);

/*
  Function: shunt_dpi_send_shortV
  send SHUNT transaction with "int" elements vector over TCP/IP

  Parameters:
  sockid - socket id
  size   - number of vector elements
  Int    - data

  Returns:
  number of elements have been sent  : success > 0


  See Also:
  - <shunt_cs_send_shortV>
  - <shunt_dpi_recv_shortV>
*/
int shunt_dpi_send_shortV   (int sockid, const int size,const svOpenArrayHandle Int);

/*
  Function: shunt_dpi_recv_shortV
  send SHUNT transaction with "int" elements vector over TCP/IP

  Parameters:
  sockid - socket id
  size   - number of vector elements
  Int    - data

  Returns:
  number of elements have been sent  : success > 0


  See Also:
  - <shunt_cs_send_shortV>
  - <shunt_dpi_send_shortV>
*/
int shunt_dpi_recv_shortV(int sockid,int size,svOpenArrayHandle Int);

/*
  Function: shunt_dpi_send_integerV
  send  verilog "reg[31:0] 4 state aval,bval" over TCP/IP

  Parameters:
  sockfd - socket id
  IntegerV  -   data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  - <shunt_cs_recv_integerV>
  - <shunt_dpi_send_shortV>

*/
int shunt_dpi_send_integerV (const unsigned int sockid,const int size,const svLogicVecVal* IntegerV);

/*
  Function: shunt_dpi_recv_integerV
  fetch verilog "reg[31:0] 4 state aval,bval" from TCP/IP

  Parameters:
  sockfd - socket id
  IntegerV - data

  Returns:
  number of bytes have been received  : success > 0

  See Also:
  - <shunt_cs_send_integerV>
  - <shunt_dpi_recv_integerV>
*/
int shunt_dpi_recv_integerV (const unsigned int sockid,const int size,svLogicVecVal* IntegerV);

/*
  Function: shunt_dpi_send_realV
  send SHUNT transaction with "real" elements vector over TCP/IP

  Parameters:
  sockid - socket id
  size - number of vector elements
  Real - data

  Returns:
  number of elements have been sent  : success > 0


  See Also:
  - <shunt_cs_send_doubleV>
  - <shunt_dpi_recv_realV>
*/
int shunt_dpi_send_realV   (int sockid,const int size,const svOpenArrayHandle Real);

/*
  Function: shunt_dpi_recv_realV
  fetch SHUNT transaction with "real" elements vector from TCP/IP

  Parameters:
  sockid - socket id
  size - number of vector elements
  Real  - data

  Returns:
  number of elements have been received  : success > 0


 See Also:
- <shunt_cs_recv_doubleV>
- <shunt_dpi_send_realV>

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


 See Also:
- <shunt_cs_send_floatV>
- <shunt_dpi_recv_shortrealV>
*/
int shunt_dpi_send_shortrealV   (int sockid,const int size,const svOpenArrayHandle Shortreal);

/*
  Function: shunt_dpi_recv_shortrealV
  fetch SHUNT transaction with "shortreal" elements vector from TCP/IP

  Parameters:
  sockid - socket id
  size - number of vector elements
  Shortreal  - data

  Returns:
  number of elements have been received  : success > 0


  See Also:
  - <shunt_cs_recv_floatV>
  - <shunt_dpi_send_shortrealV>
*/
int shunt_dpi_recv_shortrealV(int sockid,int size,svOpenArrayHandle Shortreal);

/*
  Function: shunt_dpi_send_string
  send SHUNT transaction with verilog string/C char* elements over TCP/IP

  Parameters:
  sockid - socket id
  size - number of string elements
  string  - data

  Returns:
  number of elements have been sent  : success > 0

  See Also:
  - <shunt_cs_send_byteV>
  - <shunt_dpi_recv_string>
*/
int shunt_dpi_send_string   (int sockid,int size,char* string);

/*
  Function: shunt_dpi_recv_string
  fetch SHUNT transaction with verilog string/C char* elements from TCP/IP

  Parameters:
  sockid - socket id
  size - number of string elements
  string  - data

  Returns:
  number of elements have been received  : success > 0

  See Also:
  - <shunt_dpi_recv_string>
  - <shunt_dpi_send_string>
*/
int shunt_dpi_recv_string   (int sockid,int size,char** string);

/*
  Function: shunt_dpi_get_cs_header_id 
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  long - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
long shunt_dpi_get_cs_header_id();

// Section: Data exchange (cs) TLM

/* Enum: shunt_dpi_tlm_command_e
 --- Code
typedef enum
  {
    SHUNT_TLM_READ_COMMAND,
    SHUNT_TLM_WRITE_COMMAND,
    SHUNT_TLM_IGNORE_COMMAND,
    //
    SHUNT_TLM_END_SIM,
    SHUNT_TLM_START_SIM
  } shunt_dpi_tlm_command_e;
---
*/

typedef enum {SHUNT_TLM_READ_COMMAND,SHUNT_TLM_WRITE_COMMAND,SHUNT_TLM_IGNORE_COMMAND,SHUNT_TLM_END_SIM,SHUNT_TLM_START_SIM} shunt_dpi_tlm_command_e;

//////
/*
  Function: shunt_dpi_tlm_header_id
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  long - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
long shunt_dpi_tlm_header_id();

/*
  Function: shunt_dpi_tlm_data_id
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  long - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
long  shunt_dpi_tlm_data_id();

/*
  Function: shunt_dpi_tlm_axi3_ext_id
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  long - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
long shunt_dpi_tlm_axi3_ext_id();

/*
  Function: shunt_dpi_tlm_signal_id
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  long - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/

long  shunt_dpi_tlm_signal_id();

//////

 /*
    Function: shunt_tlm_send_command
    send hunt_tlm_command

    Parameters:
    socket -  socket id
    Com   - <shunt_dpi_tlm_command_e>
 */
void shunt_dpi_tlm_send_command(int socket,const shunt_dpi_tlm_command_e Com);

/*
  Function: shunt_dpi_tlm_send_gp_transport
  send tlm generic payload  packet ( cs_tlm_generic_payload_header  + byte data vector + byte_enable vector )

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header
  data - data payload byte-vector pointer
  byte_enable - byte_enable vector pointer

  See Also:
  -  <shunt_cs_tlm_send_gp>
*/
void shunt_dpi_tlm_send_gp_transport(int sockid, cs_tlm_generic_payload_header* h, svOpenArrayHandle* data, svOpenArrayHandle* byte_enable);

/*
  Function: shunt_dpi_tlm_recv_gp_transport
  recv tlm generic payload  packet ( cs_tlm_generic_payload_header  + byte data vector + byte_enable vector )

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header
  data - data payload byte-vector pointer
  byte_enable - byte_enable vector pointer

  See Also:
  -  <shunt_cs_tlm_recv_gp_header> and <shunt_cs_tlm_recv_gp_data>
*/
void shunt_dpi_tlm_recv_gp_transport (int sockid, cs_tlm_generic_payload_header* h,svOpenArrayHandle data,svOpenArrayHandle byte_enable);

/*
  Function: shunt_dpi_tlm_recv_gp_header
  recieve tlm generic payload  header ( cs_tlm_generic_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (output)


*/
void shunt_dpi_tlm_recv_gp_header (int sockid, cs_tlm_generic_payload_header* h);

/*
  Function: shunt_dpi_tlm_send_gp_header
  send tlm generic payload  header ( cs_tlm_generic_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (output)


*/
void shunt_dpi_tlm_send_gp_header (int sockid, cs_tlm_generic_payload_header* h);

/*
  Function: shunt_dpi_tlm_recv_axi3_header
  recieve tlm generic payload  header ( cs_tlm_generic_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (output)


*/
void shunt_dpi_tlm_recv_axi3_header (int sockid, cs_tlm_axi3_extension_payload_header* h);

/*
  Function: shunt_dpi_tlm_send_axi3_header
  send tlm extension  header (cs_tlm_axi3_extension_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_axi3_extension_payload_header (output)


*/
void shunt_dpi_tlm_send_axi3_header (int sockid, cs_tlm_axi3_extension_payload_header* h);

/*
  Function: shunt_dpi_tlm_recv_gp_data
  recieve tlm generic payload  packet (byte data vector + byte_enable vector )

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (input only) should have a valid data length and byte_enable_length
  data - data payload byte-vector pointer  (output)
  byte_enable - byte_enable vector pointer (output)
*/
void  shunt_dpi_tlm_recv_gp_data (int sockid, cs_tlm_generic_payload_header* h,svOpenArrayHandle data,svOpenArrayHandle byte_enable);

// Section: Data exchange (hs)
/*
  Function: shunt_dpi_hash
  simple hash function

  Parameters:
  str - hash key

  Returns:
  hash value

  See Also:
  - <shunt_prim_hash>
*/
long shunt_dpi_hash(const char *str);

/*
  Function: shunt_dpi_send_header
  send SHUNT header over TCP/IP

  Parameters:

  sockid - socket id from init sever/target
  h - cs_header structure

  Returns:
  number of elements have been sent  : success > 0

  See Also:
  - <shunt_cs_send_header>
  - <shunt_dpi_recv_header>
*/
int shunt_dpi_send_header    (int sockid,cs_header* h);

/*
  Function: shunt_dpi_recv_header
  fetch SHUNT transaction header from TCP/IP socket

  Parameters:

  sockid - socket id from init sever/target
  header - cs_header structure

  Returns:
  number of elements have been received  : success > 0

  See Also:
  - <shunt_cs_recv_header>
  - <shunt_dpi_send_header>
*/
int shunt_dpi_recv_header   (int sockid,cs_header* h);

/*
  Function: shunt_dpi_send_data_header
  send SHUNT header over TCP/IP

  Parameters:

  sockid - socket id from init sever/target
  h - cs_header structure
  n_payloads - number of data payloads

  Returns:
  number of elements have been sent  : success > 0

  See Also:
  - <shunt_cs_send_header>
  - <shunt_dpi_recv_data_header>
*/
int shunt_dpi_send_data_header (int sockid,cs_header* h,long data_type,svOpenArrayHandle trnx_payload_sizes);

/*
  Function: shunt_dpi_recv_data_header
  fetch SHUNT transaction header from TCP/IP socket

  Parameters:
  sockid - socket id from init sever/target
  h - cs_data_header structure

  Returns:
  number of elements have been received  : success > 0

  See Also:
  - <shunt_cs_recv_data_header>
  - <shunt_dpi_send_data_header>
*/
int shunt_dpi_recv_data_header   (int sockid,cs_header* h,long* data_type,svOpenArrayHandle**  trnx_payload_sizes);

/*
  Function: shunt_dpi_hs_send
  variadic function,send data over TCP/IP.
  Supported data types are:int,shortint,longint,byte,string,integer,real,shortreal

  Parameters:

  Named arguments:

  sockid - socket id from init sever/target
  h_trnx - cs_header structure

  Unnamed argument:

  svOpenArrayHandle Array or char* Array

  Returns:
  number of elements have been sent  : success > 0

  See Also:

  - <shunt_dpi_hs_send_short>
  - <shunt_dpi_hs_send_int>
  - <shunt_dpi_hs_send_long>
  - <shunt_dpi_hs_send_byte>
  - <shunt_dpi_hs_send_string>
  - <shunt_dpi_hs_send_integer>
  - <shunt_dpi_hs_send_real>
  - <shunt_dpi_hs_send_shortreal>

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

  variadic function, fetch data from TCP/IP socket
  Supported data types are:int,shortint,longint,byte,string,integer,real,shortreal

  Parameters:

  Named arguments:

  sockid - socket id from init sever/target
  h_trnx - cs_header structure

  Unnamed argument:

  svOpenArrayHandle Array or char* Array

  Returns:

  number of elements have been received  : success > 0

  See Also:

  - <shunt_dpi_hs_recv_short>
  - <shunt_dpi_hs_recv_int>
  - <shunt_dpi_hs_recv_long>
  - <shunt_dpi_hs_recv_byte>
  - <shunt_dpi_hs_recv_string>
  - <shunt_dpi_hs_recv_integer>
  - <shunt_dpi_hs_recv_real>
  - <shunt_dpi_hs_recv_shortreal>
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
  Reg  - data

  Returns:
  number of 4 state variable byte size have been sent : success > 0


  See Also:
  - <shunt_cs_send_regN>
  - <shunt_dpi_hs_send_logicN>

*/
int shunt_dpi_hs_send_regN   (const unsigned int sockfd,cs_header* h_trnx,const svLogicVecVal* Reg);
int shunt_dpi_hs_send_logicN (const unsigned int sockfd,cs_header* h_trnx,const svLogicVecVal* Reg);



/*
  Function: shunt_dpi_hs_recv_regN
  fetch 4-state verilog reg[n:0] variable from TCP/IP socket

  Parameters:
  sockid - socket id
  h_trnx - trnx header
  Reg  - data

  Returns:
  number of 4 state variable byte size have been recie   : success > 0


  See Also:
  - <shunt_cs_recv_regN>
  - <shunt_dpi_hs_recv_logicN>
*/
int shunt_dpi_hs_recv_regN    (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);
int shunt_dpi_hs_recv_logicN  (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);


/*
  Functions: shunt_dpi_send_bitN
  map bit[N:0]  2-state data type packed array of scalar bit types
  LRM 6.11

  Parameters:
  sockfd - socket id
  bitN - data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  - <shunt_cs_send_bitN>
  - <shunt_dpi_hs_send_bitN>
*/
int shunt_dpi_send_bitN  (const int sockfd,const int size,const svBitVecVal* bitN);
int shunt_dpi_hs_send_bitN  (const int sockfd,const cs_header* h_trnx,const svBitVecVal* bitN);

/*
  Functions: shunt_dpi_recv_bitN
  map bit[N:0] 2-state data type packed array of scalar bit types
  LRM  6.11

  Parameters:
  sockfd - socket id
  bitN - data

  Returns:
  number of bytes have been recv : success > 0

  See Also:
  - <shunt_cs_recv_bitN>
  - <shunt_dpi_hs_recv_bitN>

*/
int shunt_dpi_recv_bitN     (const int sockfd,const int size,svBitVecVal* bitN);
int shunt_dpi_hs_recv_bitN  (const int sockfd,const cs_header* h_trnx,svBitVecVal* bitN);

/*
    Functions:   shunt_dpi_send_longV
    map unpacked "longint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Int - data

    Returns:
    number of bytes have been recv : success > 0
*/
int shunt_dpi_send_longV(int sockid, const int size,const svOpenArrayHandle Int);

 /*
    Functions: shunt_dpi_recv_longV
    map unpacked "longint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Int - data

    Returns:
    number of bytes have been recv : success > 0

 */
int shunt_dpi_recv_longV(int sockid,int size,svOpenArrayHandle Int);


/*
  Function: shunt_dpi_send_pkt_longV
   map unpacked "longint" paket (cs_header structure + one-dimensional data payload array)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_header structure
  longV - data payload

  Returns:
  number of elements have been sent  : success > 0
*/
int shunt_dpi_send_pkt_longV  (int sockid, const cs_header* h,const  svOpenArrayHandle Long);

/*
  Function:  shunt_dpi_recv_pkt_longV
  map unpacked "longint" packet (cs_header structure + one-dimensional data payload array)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_header structure
  longV -  data payload

  Returns:
  number of elements have been received  : success > 0
*/
int shunt_dpi_recv_pkt_longV  (int sockid, cs_header* h, svOpenArrayHandle Long);

// Section: System (non TCP) utils

/*
  Function:  shunt_dpi_gettimeofday_sec
  maps linux  gettimeofday function ,

  Parameters:

  Returns: longint the number of seconds since the Epoch
  longint a
*/
long shunt_dpi_gettimeofday_sec();

/*
  Function:  shunt_dpi_gettimeofday_usec
  maps linux  gettimeofday function ,

  Parameters:

  Returns: longint the number of microsecond since the Epoch
  longint a
*/
long shunt_dpi_gettimeofday_usec();





#endif /* SHUNT_DPI_H_ */
