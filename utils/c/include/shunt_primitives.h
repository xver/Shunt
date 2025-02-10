/*
 ============================================================================
Title: shunt_primitives.h

 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : target-initiator primitive(basic) utils
               System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)

 ============================================================================
 */

#ifndef  SHUNT_PRIMITIVES_H
#define  SHUNT_PRIMITIVES_H
#include "shunt_typedef.h"

//-------------
//prototypes
//-------------

//Title: Client-Server Primitives

/*
 * About: Verilog Data Types elements:
 *
 * Integer 2 states::
 *
 * (start code)
 *
 *    SHUNT ENUM       |  SV type    | function
 *  ------------------------------------------------------------------------
 *  SHUNT_INT          | int         | shunt_prim_xxxx_int
 *  SHUNT_SHORTINT     | shortint    | shunt_prim_xxxx_short
 *  SHUNT_LONGINT      | longint     | shunt_prim_xxxx_long
 *  SHUNT_BYTE         | byte        | shunt_prim_xxxx_byte
 *  SHUNT_BIT          | bit         | N/A see shunt_client_server.c shunt_cs_xxx_bitN.
 *
 * (end code)
 *
 * Integer 4 states::
 *
 * (start code)
 *
 *    SHUNT ENUM       |  SV type     |  function
 *  ------------------------------------------------------------------------
 *    SHUNT_INTEGER    | integer,time |  shunt_prim_xxxx_integer
 *    SHUNT_REG        | reg,logic    |  N/A see  shunt_client_server.c shunt_cs_xxx_regN
 *
 * (end code)
 *
 * Non integer types IEEE 754::
 *
 * (start code)
 *
 *    SHUNT ENUM       |  SV type     |  function
 *  ------------------------------------------------------------------------
 *   SHUNT_REAL        | real,realtime| shunt_prim_xxxx_double
 *   SHUNT_SHORTREAL   | shortreal    | shunt_prim_xxxx_float
 *   SHUNT_STRING      | string (N/A) | shunt_client_server.c shunt_cs_xxx_byte
 *
 * (end code)
 *
 *  Special Shunt types::
 *
 * (start code)
 *
 *   SHUNT_A_STRUCTURE | complex data types/user defined data types : arrays/struct,union,enums (N/A)
 *   SHUNT_HEADER_ONLY | cs_header_t header only                                                (N/A)
 *
 * (end code)
*/

//Section:  Common Functions

/*
  Function: shunt_prim_hash
  simple hash function

  Parameters:
  str - hash key

  Returns:
  hash value
*/
INLINE shunt_long_t shunt_prim_hash(const char *str);

/*
  Function: shunt_prim_error
  perror wrapper

  Parameters:
  str - error message

  Returns:
  void
 */
INLINE void shunt_prim_error(const char *msg);

/*
  Function: shunt_prim_rand_delay
  implements in millisecond random interval delay between the lower and upper limit.
  Parameters:
   low - low limit in msec
   up - up limit in msec
  Returns:
  delay in msec
 */
INLINE int shunt_prim_rand_delay (int up, int low);


//Section: TCP/IP Functions
/*
 Function: shunt_prim_init_initiator
 TCP/IP initiator initialization

 Parameters:

 portno - socket port

 Returns:

 socket id

*/
INLINE unsigned int shunt_prim_init_initiator(const unsigned int portno);

/*
  Function: shunt_prim_tcp_parent_init_initiator
  Multi-Slave TCP IP initialisation, create TCP/IP a parent/listener and start listening for client connections


  Parameters:

  portno - socket port


  Returns:

  socket id - parent socket id

*/
INLINE unsigned int shunt_prim_tcp_parent_init_initiator(const unsigned int portno);

/*
  Function: shunt_prim_tcp_child_init_initiator
  Multi-Slave TCP IP initialisation, establish TCP/IP  initiator-target connection

  Parameters:

  socket id - parent socket id

  Returns:

  child socket id
 */
INLINE unsigned int shunt_prim_tcp_child_init_initiator(const unsigned int parentfd);

/*
 Function: shunt_prim_init_target
 TCP/IP target initialization

 Parameters:

 parentfd - parent socket

 hostname - initiator name

 Returns:

 socket id

*/
INLINE unsigned int shunt_prim_init_target(const unsigned int portno,const char *hostname);

/*
 Function: shunt_prim_get_socket_error
 An auxiliary function: to clear any errors, which can cause close(fd) to fail
 ref to https://stackoverflow.com/questions/12730477/close-is-not-closing-socket-properly

Parameters:

 fd - socket

 Returns:

 err - error if err<0

*/
INLINE int shunt_prim_get_socket_error(int fd);

/*
 Function: shunt_prim_close_socket
 terminates TCP socket

 Parameters:

  fd - socket

 Returns:

 N/A

*/
INLINE void shunt_prim_close_socket(int fd);

/*
 Function: shunt_prim_unblock_socket
 sets TCP socket unblocked mode

 Parameters:
 flag -  1/0- unblocked(default)/blocked
 fd - socket

 Returns:

 N/A

*/
INLINE void shunt_prim_unblock_socket(int flag , int sockfd);



/*
  Function: shunt_prim_tcp_nodelay_socket

  enable/disable Nagle algorithm (TCP_NODELAY)

  Parameters:

  sockfd - socket
  flag -  1/0- enable/disable Nagle algorithm (TCP_NODELAY)

  Returns:

  N/A

*/
INLINE void shunt_prim_tcp_nodelay_socket(int flag, int sockfd);

/*
  Function: shunt_prim_get_status_socket
  returns status for TCP socket <event> on a fd <socket>
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
INLINE int shunt_prim_get_status_socket(int fd,int event);


/*
Function: Example:  target,initiator init

(start code)
 #define MY_HOST "localhost"
 #define MY_PORT  3450
 char* hostname;
 int port;
 port = MY_PORT;
 hostname =   MY_HOST;

 shunt_prim_init_initiator(port);
 shunt_prim_init_target(port,hostname);
(end)

 */

//Section: Data exchange primitives


/*
  Function: shunt_prim_send_int
  send verilog/C "int" data over TCP/IP

  Parameters:
  sockfd - socket id
  Int  -   data

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  <shunt_prim_recv_int>
*/
INLINE int shunt_prim_send_int    (const int sockfd,const int* Int);

/*
 Function: shunt_prim_recv_int
  fetch verilog/C "int" data from TCP/IP socket

  Parameters:
  sockfd - socket id
  Int - data from socket

  Returns:
  number of bytes have been received  : success > 0

  See Also:
  <shunt_prim_send_int>
*/
INLINE int shunt_prim_recv_int    (const int sockfd,int* Int);

/*
 Function: shunt_prim_send_double
  send verilog "double" over TCP/IP

  Parameters:
   sockfd - socket id
   Double  - data to send

  Returns:
    number of bytes have been sent : success > 0

    See Also:

    <shunt_prim_recv_double>
*/
INLINE int shunt_prim_send_double    (const int sockfd,const double* Double);

/*
  Function: shunt_prim_recv_double
  fetch verilog "real"/"shortreal"/"realtime"/C "double"/"float","double" from TCP/IP

  Parameters:
  sockfd - socket id
  Double - data from socket

  Returns:
 number of bytes have been sent : success > 0

See Also:
   <shunt_prim_recv_double>

*/
INLINE int shunt_prim_recv_double   (const int sockfd,double* Double);

/*
 Function: shunt_prim_send_float
  send verilog "real"/"shortreal"/"realtime"/C "double"/"float","double" over TCP/IP

  Parameters:
   sockfd - socket id
   Double  - data to send

  Returns:
    number of bytes have been sent : success > 0

    See Also:
   <shunt_prim_recv_float>
*/
INLINE int shunt_prim_send_float     (const int sockfd,const float* Float);


/*
  Function: shunt_prim_recv_float
  fetch verilog "real"/"shortreal"/"realtime"/C "double"/"float","double" from TCP/IP

  Parameters:
  sockfd - socket id
  Double - data from socket

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  <shunt_prim_send_float>

*/
INLINE int shunt_prim_recv_float    (const int sockfd,float* Float);

/*
  Function: shunt_prim_send_short
  send verilog "shortint"/C "short int" over TCP/IP

  Parameters:
  sockfd - socket id
  Short  - data to send

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  <shunt_prim_recv_short>
*/
INLINE int shunt_prim_send_short (const int sockfd,const short int* Short);

/*
  Function: shunt_prim_recv_short
  fetch verilog "shortint"/C "short int" over TCP/IP

  Parameters:
  sockfd - socket id
  Short - data from socket

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  <shunt_prim_send_short>

*/
INLINE int shunt_prim_recv_short    (const int sockfd,short int* Short);


/*
 Function: shunt_prim_send_long
  send verilog "longint"/C "long" over TCP/IP

  Parameters:
  sockfd - socket id
  Long  - data to send

  Returns:
  number of bytes have been sent : success > 0

  See Also:
  <shunt_prim_recv_long>
*/
INLINE int shunt_prim_send_long    (const int sockfd,const shunt_long_t* Long);

/*
  Function: shunt_prim_recv_long
  fetch verilog "longint"/C "long" over TCP/IP

  Parameters:
  sockfd - socket id
  Long - data from socket

  Returns:
 number of bytes have been sent : success > 0

 See Also:
  <shunt_prim_send_long>
*/
INLINE int shunt_prim_recv_long    (const int sockfd,shunt_long_t* Long);

/*
 Function: shunt_prim_send_byte
  send verilog/C "Byte/Char" data over TCP/IP

  Parameters:
   sockfd - socket id
   Byte  -   data

  Returns:
   number of bytes have been sent : success > 0

 See Also:
  <shunt_prim_recv_byte>
*/
INLINE int shunt_prim_send_byte    (const int sockfd,const char* Byte);

/*
 Function: shunt_prim_recv_byte
  fetch verilog/C "Byte/Char" data from TCP/IP socket

  Parameters:
   sockfd - socket id
   Byte - data from socket

  Returns:
    number of bytes have been received  : success > 0
 See Also:
  <shunt_prim_send_byte>

*/
INLINE int shunt_prim_recv_byte    (const int sockfd,char* Byte);

/*
 Function: shunt_prim_send_integer
  send  verilog "reg[31:0] 4 state aval,bval" over TCP/IP

  Parameters:
   sockfd - socket id
   Int  -   data

  Returns:
   number of bytes have been sent : success > 0

   See Also:
   <shunt_prim_recv_integer>

*/
INLINE int shunt_prim_send_integer(const unsigned int sockfd,const svLogicVecVal* Int);

/*
 Function:  shunt_prim_recv_integer
  fetch verilog "reg[31:0] 4 state aval,bval" from TCP/IP

  Parameters:
   sockfd - socket id
   Int - data from socket

  Returns:
    number of bytes have been received  : success > 0

    See Also:
   <shunt_prim_send_integer>

*/
INLINE int shunt_prim_recv_integer (const unsigned int sockfd,svLogicVecVal* Int);
#endif
