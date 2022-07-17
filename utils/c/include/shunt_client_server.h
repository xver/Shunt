/*
   ============================================================================
   File        : shunt_client_server.h
   Version     : 1.0.0
   Copyright (c) 2016-2022 IC Verimeter. All rights reserved.
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

//Section: TCP/IP Functions

/*
 Function: shunt_cs_init_initiator
 TCP/IP initiator (server) initialization

 Parameters:

 portno_in --socket port .If portno_in = 0 -- allocating a free client-server TCP port.
 
 NOTE: <SHUNT_DEFAULT_TCP_PORT> is reserved for the dynamic allocation of the client-server TCP port.

 Returns:

 socket id -- child socket id

*/
INLINE unsigned int shunt_cs_init_initiator(const unsigned int portno_in);

/*
 Function:  shunt_cs_tcp_parent_init_initiator_dpa
 - TCP/IP initiator (server) initialization 
 - TCP Dynamic Port Allocation (dpa) 
 - ready for Multi-Slave TCP IP
 
 Parameters: 
 
 N/A

 Returns: 

 socket id -- DPA parent socket id

 NOTE: <SHUNT_DEFAULT_TCP_PORT> is reserved for the dynamic allocation of the client-server TCP port.

 see  <shunt_prim_tcp_parent_init_initiator>

*/
INLINE unsigned int shunt_cs_tcp_parent_init_initiator_dpa();

/*
 Function: shunt_cs_init_target
 TCP/IP target (client) initialization
 
 Parameters:

 hostname  -- initiator (host) name
 portno_in -- TCP port. If portno_in = 0 -- allocating a free client-server TCP port.
 
 NOTE: <SHUNT_DEFAULT_TCP_PORT> is dedicated to dynamic client-server TCP port assignment.
 
 Returns:

 socket id

*/
INLINE unsigned int shunt_cs_init_target(const unsigned int portno_in ,const char *hostname);

/*
 Function: shunt_cs_tcp_parent_init_target_dpa 
 - TCP/IP target (client) initialization 
 - TCP Dynamic Port Allocation (dpa) 
 - ready for Multi-Slave TCP IP
 
 Parameters: 
 
 hostname  -- initiator (host) name
 
 Returns: 
 <shunt_dynamic_port> - shunt dynamic port allocation struct 
 

 NOTE: <SHUNT_DEFAULT_TCP_PORT> is reserved for the dynamic allocation of the client-server TCP port.

 see  <shunt_prim_tcp_parent_init_initiator>

*/
INLINE shunt_dynamic_port  shunt_cs_tcp_parent_init_target_dpa(const char *hostname);


/*
 Function: shunt_cs_update_dynamic_port
 Update the shunt_dynamic_por structure by the TCP socket.
 
 Parameters:

 socket -- parent socket id 
  
 Returns:

 shunt_dynamic_port structure see <shunt_dynamic_port>
 

*/
INLINE  shunt_dynamic_port shunt_cs_update_dynamic_port(unsigned int parentfd_0);

//Section: Data exchange structures and utilities

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
INLINE shunt_long_t shunt_cs_data_type_hash(shunt_long_t data_type,const char* data_type_names[],int last_enum);

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
INLINE int shunt_cs_data_type(shunt_long_t hash,const char* data_type_names[],int last_enum);

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
INLINE int shunt_cs_send_header    (int sockid,cs_header* h);

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
INLINE int shunt_cs_send_data_header    (int sockid,int n_payloads,cs_data_header* h);



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
INLINE int shunt_cs_recv_header   (int sockid,cs_header* h);

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
INLINE int shunt_cs_recv_data_header   (int sockid,int n_payloads,cs_data_header* h);

// Section: Data exchange utilities


/*
Function: shunt_cs_send_intV
  send SHUNT transaction with "int" elements vector over TCP/IP

  Parameters:
  sockid - socket id
  header - cs_header structure
  IntV - data array

  Returns:
  number of elements have been sent  : success > 0

  See Also:
  <shunt_cs_recv_intV>

*/
INLINE int shunt_cs_send_intV   (int sockid, const cs_header* header,const int* Int);

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
INLINE int shunt_cs_recv_intV   (int sockid, cs_header* header,int* Int);

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
INLINE int shunt_cs_send_shortV (int sockid, const cs_header* header,const short int* Short);

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
INLINE int shunt_cs_recv_shortV (int sockid, cs_header* header,short int* Short);


/*
Function: shunt_cs_send_longV
  send SHUNT transaction with "longint" elements vector over TCP/IP

  Parameters:
  sockid - socket id
  header - cs_header structure
  LongV   - data array

  Returns:
  number of elements have been sent  : success > 0

    See Also:
    <shunt_cs_recv_longV>
*/
INLINE int shunt_cs_send_longV  (int sockid, const cs_header* header,const shunt_long_t* Long);

/*
  Function: shunt_cs_recv_longV
  fetch SHUNT transaction with "longint" elements vector  elements from TCP/IP

  Parameters:
  sockid - socket id
  header - cs_header structure
  Shunt_Long_T   - Data received

  Returns:
  number of elements have been received  : success > 0


  See Also:
    <shunt_cs_send_longV>
*/
INLINE int shunt_cs_recv_longV  (int sockid, cs_header* header,shunt_long_t* Long);


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
INLINE int shunt_cs_send_doubleV   (int sockid,const cs_header* header,const double* Double);

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
INLINE int shunt_cs_recv_doubleV   (int sockid,cs_header* header,double* Double);


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
INLINE int shunt_cs_send_floatV   (int sockid,const cs_header* header,const float* Float);

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
INLINE int shunt_cs_recv_floatV   (int sockid,cs_header* header,float* Float);

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
INLINE int shunt_cs_send_byteV   (int sockid,const cs_header* header,const char* byteV);

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
INLINE int shunt_cs_recv_byteV   (int sockid,cs_header* header,char* byteV);

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
INLINE int shunt_cs_send_bitN (int sockid,const cs_header* h,const svBitVecVal* bitN) ;

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
INLINE int shunt_cs_recv_bitN     (int sockid,const cs_header* h,svBitVecVal* bitN);

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
    <shunt_cs_send_bitN>
*/
INLINE int shunt_cs_send_integerV (int sockid,const cs_header* h,const svLogicVecVal* integerV) ;

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
INLINE int shunt_cs_recv_integerV     (int sockid,const cs_header* h,svLogicVecVal* integerV);

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
INLINE int shunt_cs_send_regN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg);

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
INLINE int shunt_cs_recv_regN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg);

//Section: Auxiliary tasks

unsigned int shunt_cs_tlm_data_payload_size(const unsigned int data_size);

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
INLINE void shunt_cs_print_header    (cs_header* h,const char* data_type_names[],int last_enum,char const *msg);

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
INLINE void shunt_cs_print_data_header (cs_header* h,cs_data_header* h_data,const char* data_type_names[],int last_enum,char* msg);

/*
  Function: shunt_cs_get_cs_header_leader 
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  shunt_long_t - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
INLINE shunt_long_t shunt_cs_get_cs_header_leader();

/*
  Function: shunt_cs_get_tlm_header_leader
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  shunt_long_t - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
INLINE shunt_long_t shunt_cs_get_tlm_header_leader();

/*
  Function: shunt_cs_get_tlm_data_leader
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  shunt_long_t - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
INLINE shunt_long_t  shunt_cs_get_tlm_data_leader();

/*
  Function: shunt_cs_get_tlm_axi3_ext_leader
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  shunt_long_t - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
INLINE shunt_long_t shunt_cs_get_tlm_axi3_ext_leader();

/*
  Function: shunt_cs_get_tlm_axi3_signal_leader
  predefined hash functions for obtain the specific hash value.  

  Parameters:
  N/A
  
  Returns:
  shunt_long_t - hash value;

See Also:
  <shunt_cs_get_cs_header_leader> <shunt_cs_get_tlm_header_leader> <shunt_cs_get_tlm_data_leader> <shunt_cs_get_tlm_axi3_ext_leader> <shunt_cs_get_tlm_axi3_signal_leader>

*/
INLINE shunt_long_t  shunt_cs_get_tlm_axi3_signal_leader();

//Section: TLM2.0 utils

/*
  Function: shunt_cs_tlm_send_gp
  send tlm generic payload  packet ( cs_tlm_generic_payload_header  + byte data vector + byte_enable vector )

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header
  data - data payload byte-vector pointer
  byte_enable - byte_enable vector pointer

*/
INLINE void shunt_cs_tlm_send_gp(int sockid, const cs_tlm_generic_payload_header* h, const unsigned char* data, const unsigned char* byte_enable);

/*
  Function: shunt_cs_tlm_recv_gp_header
  recieve tlm generic payload  header ( cs_tlm_generic_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (output)


*/
INLINE void shunt_cs_tlm_recv_gp_header (int sockid, cs_tlm_generic_payload_header* h);

/*
  Function: shunt_cs_tlm_send_gp_header
  send tlm generic payload  header ( cs_tlm_generic_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (output)


*/
INLINE void shunt_cs_tlm_send_gp_header (int sockid, cs_tlm_generic_payload_header* h);

/*
  Function: shunt_cs_tlm_recv_axi3_header
  recieve tlm generic payload  header ( cs_tlm_generic_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (output)


*/
INLINE void shunt_cs_tlm_recv_axi3_header (int sockid, cs_tlm_axi3_extension_payload_header* h);

/*
  Function: shunt_cs_tlm_send_axi3_header
  send tlm extension  header (cs_tlm_axi3_extension_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_axi3_extension_payload_header (output)


*/
INLINE void shunt_cs_tlm_send_axi3_header (int sockid, cs_tlm_axi3_extension_payload_header* h);


/*
  Function: shunt_cs_tlm_recv_gp_data
  recieve tlm generic payload  packet (byte data vector + byte_enable vector )

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (input only) should have a valid data length and byte_enable_length
  data - data payload byte-vector pointer  (output)
  byte_enable - byte_enable vector pointer (output)
*/
INLINE void  shunt_cs_tlm_recv_gp_data (int sockid, const cs_tlm_generic_payload_header* h,shunt_long_t* data,shunt_long_t* byte_enable);

#endif
