/*
============================================================================
Title: shunt_dpi_pkg.sv
 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : shunt dpi bridge
               System Verilog target/initiator handshake (TCP/IP SystemVerilog SHUNT)
 ============================================================================
*/
package shunt_dpi_pkg;

`define SHUNT_MAX_SIZE = 4096;

   //Title: Utilites: System Verilog to C dpi bridge

   //Section: Data exchange structures and utilities

   /*
    Variable: shunt_signal_type_e
    (start code)
    *Integer 2 states:*

    SHUNT_INT     - int
    SHUNT_SHORTINT    - shortint
    SHUNT_LONGINT     - longint
    SHUNT_BYTE    - byte
    SHUNT_BIT     - bit

    *Integer 4 states:*

    SHUNT_INTEGER     - integer,time
    SHUNT_REG     - reg,logic

    *Non integer types IEEE 754:*

    SHUNT_REAL    - real,realtime
    SHUNT_SHORTREAL   - shortreal
    SHUNT_STRING      - string

    SHUNT_A_STRUCTURE - complex data types/user defined data types : arrays/struct,union,enums
    SHUNT_HEADER_ONLY - cs_header_t header only.

    typedef enum {SHUNT_NA,SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_LOGIC,SHUNT_BIT,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} shunt_signal_type_e;
    (end)
    */

   /* verilator lint_off UNDRIVEN */
   typedef enum {SHUNT_NA,SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_LOGIC,SHUNT_BIT,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} shunt_signal_type_e;
   /* verilator lint_on UNDRIVEN */

   //Section: TCP/IP target/initiator init

   /*
    Function: shunt_dpi_initiator_init
    TCP/IP initiator initialization

    Parameters:
    portno - socket port

    Returns:
    socket id

    See Also:
    <shunt_prim_init_initiator>

    (start code)
    //Example:
    #define MY_HOST "localhost"
    #define MY_PORT  3450

    int port;
    port = MY_PORT;

    shunt_prim_init_initiator(port);

    (end)

    Disable function `define:  NO_SHUNT_DPI_INITIATOR_INIT
    */
`ifndef NO_SHUNT_DPI_INITIATOR_INIT
   import "DPI-C" function int shunt_dpi_initiator_init (input int portno);
`endif

   /*
    Function: shunt_dpi_target_init
    TCP/IP target initialization

    portno - socket port
    hostname - initiator name

    Returns:
    socket id

    See Also:
    <shunt_prim_init_target>

    (start code)
    //Example:
    #define MY_HOST "localhost"
    #define MY_PORT  3450

    char* hostname;
    int port;
    port = MY_PORT;
    hostname =   MY_HOST;

    shunt_prim_init_tcptarget(port,hostname);
    (end)

    Disable function `define:  NO_SHUNT_DPI_TARGET_INIT
    */
`ifndef NO_SHUNT_DPI_TARGET_INIT
   import "DPI-C" function int shunt_dpi_target_init (input int portno,input string hostname);
`endif

   /*
    Function: shunt_dpi_close_socket
    terminaties TCP socket

    Parameters:

    fd - socket id

    Returns:
    N/A

    Disable function `define: NO_SHUNT_DPI_CLOSE_SOCKET
    */
 `ifndef NO_SHUNT_DPI_CLOSE_SOCKET
   import "DPI-C" function void shunt_dpi_close_socket(int fd);
 `endif


/*
    Function: shunt_dpi_unblock_socket
    sets TCP socket unblocked mode

    Parameters:
    flag -  1/0- unblocked(deafult)/blocked
    fd - socket id

    Returns:
    N/A

    Disable function `define: NO_SHUNT_DPI_UNBLOCK_SOCKET
    */
 `ifndef NO_SHUNT_DPI_UNBLOCK_SOCKET
   import "DPI-C" function void shunt_dpi_unblock_socket(int flag, int fd);
 `endif


   /*
    Function: shunt_dpi_get_status_socket
    returns status for TCP socket <event> on a fd <soket>

    Parameters:
    sockfd - socket
    short event-  the <evnt> mask is specifying following

  - 0- is equal equal POLLIN, data is ready to recv(),

  - 1- is equal to POLLOUT, socket can send() data to this socket without blocking

  - else is equal to POLLNVAL, function returns "process failed" status;

  Returns:
  socket even status

  -  "0"- No <evnt>

  -  "-1"- <evnt> process has failed

  -  "1"- <evnt> occurs

     Disable function `define: NO_SHUNT_DPI_GET_STATUS_SOCKET
    */

 `ifndef NO_SHUNT_DPI_GET_STATUS_SOCKET
   import "DPI-C" function  int shunt_dpi_get_status_socket(int fd,int evnt);
 `endif

   /*

    Function: shunt_dpi_tcp_nodelay_socket

    enable/disable Nagle algorithm (TCP_NODELAY)

    Parameters:

    sockfd - socket
    flag -  1/0- enable/disable Nagle algorithm (TCP_NODELAY)
    Returns:
    N/A

    Disable function `define: NO_SHUNT_DPI_TCP_NODELAY_SOCKET
    */
 `ifndef  NO_SHUNT_DPI_TCP_NODELAY_SOCKET
   import "DPI-C" function void  shunt_dpi_tcp_nodelay_socket(int flag, int sockfd);
 `endif

   /*
    Function: shunt_dpi_listener_init
    Multi-Slave TCP IP initialisation, create TCP/IP a parent(listener) and start listening for client connections

    Parameters:
    portno - socket port

    Returns:
    socket id - parent socket id

    Disable function `define: NO_SHUNT_DPI_LISTENER_INIT
    */
 `ifndef NO_SHUNT_DPI_LISTENER_INIT
   import "DPI-C" function int shunt_dpi_listener_init(int portno);
 `endif

   /*
    Function: shunt_dpi_tcp_connect
    Multi-Slave TCP IP initialisation, establish TCP/IP  initiator-target connection

    Parameters:
    socket id - parent socket id

    Returns:
    socket id - child socket id

    Disable function `define: NO_SHUNT_DPI_TCP_CONNECT
    */
 `ifndef NO_SHUNT_DPI_TCP_CONNECT
   import "DPI-C" function int shunt_dpi_tcp_connect(int parentfd);
 `endif

   /*
    Function: shunt_dpi_tcp_get_port
    Finds TCP/IP port  with the specified socket id

    Parameters:

    socket  -- socket id

    Returns:
    a corresponding TCP/IP port

    Disable function `define: NO_SHUNT_DPI_TCP_GET_PORT

    Also see <shunt_cs_update_dynamic_port>

*/
 `ifndef NO_SHUNT_DPI_TCP_GET_PORT
   import "DPI-C" function int shunt_dpi_tcp_get_port(int socket);
 `endif


 /*
 Function:  shunt_dpi_tcp_parent_init_initiator_dpa
 is DPI equivalent of the <shunt_cs_tcp_parent_init_initiator_dpa>

Parameters:

 N/A

 Returns:

 socket id -- DPA parent socket id
  Disable function `define: NO_SHUNT_DPI_TCP_GET_PORT
*/
 `ifndef NO_SHUNT_DPI_TCP_PARENT_INIT_INITIATOR_DPA
   import "DPI-C" function int shunt_dpi_tcp_parent_init_initiator_dpa();
 `endif

   //Section: Integer types

   /*
    Functions:  shunt_dpi_send_short
    map shortint 2-state data type,16-bit signed integer
    see SV LRM 6.11 Integer data types shortint/short int*

    Parameters:
    sockid - socket id
    Short - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_SHORT
    */
`ifndef NO_SHUNT_DPI_SEND_SHORT
   import "DPI-C" function int shunt_dpi_send_short  (input int sockid,input  shortint Short);
`endif

   /*
    Functions:  shunt_dpi_recv_short
    map shortint 2-state data type,16-bit signed integer
    see SV LRM 6.11 Integer data types shortint/short int*

    Parameters:
    sockid - socket id
    Short - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_SHORT
    */
`ifndef NO_SHUNT_DPI_RECV_SHORT
   import "DPI-C" function int shunt_dpi_recv_short  (input int sockid,output shortint Short);
`endif

   /*
    Functions:  shunt_dpi_send_int
    map int 2-state data type,32-bit signed integer
    LRM 6.11 Integer data types int/int*

    Parameters:
    sockid - socket id
    Int - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_INT
    */
`ifndef NO_SHUNT_DPI_SEND_INT
   import "DPI-C" function int shunt_dpi_send_int    (input int sockid,input  int Int);
`endif

   /*
    Functions: shunt_dpi_recv_int
    map int 2-state data type,32-bit signed integer
    LRM 6.11 Integer data types int/int*

    Parameters:
    sockid - socket id
    Int - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_INT
    */
`ifndef NO_SHUNT_DPI_RECV_INT
   import "DPI-C" function int shunt_dpi_recv_int    (input int sockid,output int Int);
`endif

   /*
    Functions:  shunt_dpi_send_long
    map longint 2-state data type,64-bit signed integer
    see SV LRM 6.11 Integer data types longint/long int*

    Parameters:
    sockid - socket id
    Long - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_LONG
    */
`ifndef NO_SHUNT_DPI_SEND_LONG
   import "DPI-C" function int shunt_dpi_send_long  (input int sockid,input  longint Long);
`endif

   /*
    Functions:  shunt_dpi_recv_long
    map longint 2-state data type,64-bit signed integer
    see SV LRM 6.11 Integer data types longint/long int*

    Parameters:
    sockid - socket id
    Long - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_LONG
    */
`ifndef NO_SHUNT_DPI_RECV_LONG
   import "DPI-C" function int shunt_dpi_recv_long  (input int sockid,output longint Long);
`endif

   /*
    Functions:  shunt_dpi_send_byte
    map byte 2-state data type, 8-bit signed integer or ASCII character
    LRM 6.11 Integer data types char/char*

    Parameters:
    sockid - socket id
    Byte - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_BYTE
    */
`ifndef NO_SHUNT_DPI_SEND_BYTE
   import "DPI-C" function int shunt_dpi_send_byte   (input int sockid,input  byte Byte);
`endif

   /*
    Functions:  shunt_dpi_recv_byte
    map byte 2-state data type, 8-bit signed integer or ASCII character
    LRM 6.11 Integer data types char/char*

    Parameters:
    sockid - socket id
    Byte - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_BYTE
    */
`ifndef NO_SHUNT_DPI_RECV_BYTE
   import "DPI-C" function int shunt_dpi_recv_byte   (input int sockid,output byte Byte);
`endif

   /*
    Functions:  shunt_dpi_send_integer
    map integer  4-state data type,32-bit signed integer
    LRM 6.11 Integer data types

    Parameters:
    sockid - socket id
    Integer - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_INTEGER
    */
`ifndef NO_SHUNT_DPI_SEND_INTEGER
   import "DPI-C" function int shunt_dpi_send_integer (input int sockid,input integer Integer);
`endif


   /*
    Functions:  shunt_dpi_recv_integer
    map integer  4-state data type,32-bit signed integer
    LRM 6.11 Integer data types

    Parameters:
    sockid - socket id
    Integer - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_INTEGER
    */

`ifndef NO_SHUNT_DPI_RECV_INTEGER
   import "DPI-C" function int shunt_dpi_recv_integer (input int sockid,inout integer Integer);
`endif


   /*
    Functions:  shunt_dpi_send_time
    map time  4-state data type, 64-bit unsigned integer
    LRM 6.11

    Parameters:
    sockid - socket id
    Time - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_TIME
    */
`ifndef NO_SHUNT_DPI_SEND_TIME
   import "DPI-C" function int shunt_dpi_send_time (input int sockid,input time Time);
`endif

   /*
    Functions:  shunt_dpi_recv_time
    map time  4-state data type, 64-bit unsigned integer
    LRM 6.11

    Parameters:
    sockid - socket id
    Time - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_TIME
    */
`ifndef NO_SHUNT_DPI_RECV_TIME
   import "DPI-C" function int shunt_dpi_recv_time (input int sockid,inout time Time);
`endif

   /*
    Functions:  shunt_dpi_send_bit
    map bit 2-state data type,user-defined vector size unsigned
    LRM 6.11

    Parameters:
    sockid - socket id
    Bit - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_BIT
    */
`ifndef NO_SHUNT_DPI_SEND_BIT
   import "DPI-C" function int shunt_dpi_send_bit (input int sockid,input bit Bit);
`endif

   /*
    Functions:  shunt_dpi_recv_bit
    mapbit 2-state data type,user-defined vector size unsigned
    LRM 6.11

    Parameters:
    sockid - socket id
    Bit - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_BIT
    */
`ifndef NO_SHUNT_DPI_RECV_BIT
   import "DPI-C" function int shunt_dpi_recv_bit (input int sockid,inout bit Bit);
`endif



/*
    Functions:  shunt_dpi_send_reg
    map reg/logic 4-state data type
    LRM 6.11

    Parameters:
    sockid - socket id
    Reg - data

    Returns:
    number of bytes have been sent : success > 0

 Disable function `define:  NO_SHUNT_DPI_SEND_REG
 */
`ifndef NO_SHUNT_DPI_SEND_REG
   import "DPI-C" function int shunt_dpi_send_reg   (input int sockid,input reg Reg);
`endif

   /*
    Functions:  shunt_dpi_recv_reg
    map reg/logic 4-state data type
    LRM  6.11

    Parameters:
    sockid - socket id
    Reg - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_REG
    */
`ifndef NO_SHUNT_DPI_RECV_REG
   import "DPI-C" function int shunt_dpi_recv_reg   (input int sockid,inout reg Reg);
`endif

   /*
    Functions:  shunt_dpi_send_logic
    map reg/logic 4-state data type
    LRM 6.11

    Parameters:
    sockid - socket id
    Logic - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_LOGIC
    */
`ifndef NO_SHUNT_DPI_SEND_LOGIC
   import "DPI-C" function int shunt_dpi_send_logic (input int sockid,input logic Logic);
`endif


   /*
    Functions: shunt_dpi_recv_logic
    map reg/logic 4-state data type
    LRM  6.11

    Parameters:
    sockid - socket id
    Logic - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_LOGIC
    */
`ifndef NO_SHUNT_DPI_RECV_LOGIC
   import "DPI-C" function int shunt_dpi_recv_logic (input int sockid,inout logic Logic);
`endif


   //Section: non_integer_type IEEE 754

   /*
    Functions: shunt_dpi_send_real
    map real data type is the same as a C double 8 byte
    LRM 6.12

    Parameters:
    sockid - socket id
    Real - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_REAL
    */
`ifndef NO_SHUNT_DPI_SEND_REAL
   import "DPI-C" function int shunt_dpi_send_real      (input int sockid,input  real Real);
`endif

    /*
    Functions: shunt_dpi_recv_real
    map real data type is the same as a C double 8 byte
    LRM 6.12

    Parameters:
    sockid - socket id
    Real - data

    Returns:
    number of bytes have been recv : success > 0

     ND    disable function `define:  NO_SHUNT_DPI_RECV_REAL
     */
`ifndef NO_SHUNT_DPI_RECV_REAL
   import "DPI-C" function int shunt_dpi_recv_real      (input int sockid,output real Real);
`endif

   /*
    Functions: shunt_dpi_send_shortreal
    map real data type is the same as a C float
    LRM 6.12

    Parameters:
    sockid - socket id
    Real - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_SHORTREAL
    */
`ifndef NO_SHUNT_DPI_SEND_SHORTREAL
   import "DPI-C" function int shunt_dpi_send_shortreal (input int sockid,input  shortreal Real);
`endif

   /*
    Functions: shunt_dpi_recv_shortreal
    map real data type is the same as a C float
    LRM 6.12

    Parameters:
    sockid - socket id
    Real - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_SHORTREAL
    */
`ifndef NO_SHUNT_DPI_RECV_SHORTREAL
   import "DPI-C" function int shunt_dpi_recv_shortreal (input int sockid,output shortreal Real);
`endif


   //Section: Vectors





   /*
    Functions: shunt_dpi_send_bitN

    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11

    Parameters:
    sockid - socket id
    bitN - data
    size - number of vector elements

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_BITN
    */
`ifndef NO_SHUNT_DPI_SEND_BITN
   import "DPI-C" function int shunt_dpi_send_bitN(input int sockid,input int size,input bit[] bitN);
`endif

   /*
    Functions: shunt_dpi_recv_bitN
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11

    Parameters:
    sockid - socket id
    bitN - data
    size - number of vector elements

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_BITN
    */

`ifndef NO_SHUNT_DPI_RECV_BITN
   import "DPI-C" function int shunt_dpi_recv_bitN  (input int sockid,input int size,inout bit[] bitN);
`endif
   /*
    Functions: shunt_dpi_send_string
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes
    LRM 6.16

    Parameters:
    sockid - socket id
    String - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_STRING
    */
`ifndef NO_SHUNT_DPI_SEND_STRING
   import "DPI-C" function int shunt_dpi_send_string (input int sockid,input int size,input  string String);
`endif

   /*
    Functions: shunt_dpi_recv_string
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes
    LRM 6.16

    Parameters:
    sockid - socket id
    String - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_STRING
    */
`ifndef NO_SHUNT_DPI_RECV_STRING
   import "DPI-C" function int shunt_dpi_recv_string (input int sockid,input int size,inout  string String);
`endif

   //Section: Integer vector types

   /*
    Functions:  shunt_dpi_send_intV
    map unpacked "int" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Int - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_INTV
    */
`ifndef NO_SHUNT_DPI_SEND_INTV
   import "DPI-C" function int shunt_dpi_send_intV   (input int sockid,input int size,input  int Int[]);
`endif

   /*
    Functions:  shunt_dpi_recv_intV
    map unpacked "int" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Int - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_INTV
    */
`ifndef NO_SHUNT_DPI_RECV_INTV
   import "DPI-C" function int shunt_dpi_recv_intV   (input int sockid,input int size,output int Int[]);
`endif


   /*
    Functions:  shunt_dpi_send_shortV
    map unpacked "shortint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Int - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_SHORTV
    */
`ifndef NO_SHUNT_DPI_SEND_SHORTV
   import "DPI-C" function int shunt_dpi_send_shortV (input int sockid,input int size,input  shortint Int[]);
`endif

   /*
    Functions:  shunt_dpi_recv_shortV
    map unpacked "shortint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Int - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_SHORTV
    */
`ifndef NO_SHUNT_DPI_RECV_SHORTV
   import "DPI-C" function int shunt_dpi_recv_shortV (input int sockid,input int size,output shortint Int[]);
`endif

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

    Disable function `define:  NO_SHUNT_DPI_SEND_LONGV
    */
`ifndef NO_SHUNT_DPI_SEND_LONGV
   import "DPI-C" function int shunt_dpi_send_longV (input int sockid,input int size,input  longint Int[]);
`endif

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

    Disable function `define:  NO_SHUNT_DPI_RECV_LONGV
    */
`ifndef NO_SHUNT_DPI_RECV_LONGV
   import "DPI-C" function int shunt_dpi_recv_longV (input int sockid,input int size,output longint Int[]);
`endif


    /*
    Functions: shunt_dpi_send_realV
    map unpacked "real" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Real - data

    Returns:
    number of bytes have been recv : success > 0

     ND    disable function `define:  NO_SHUNT_DPI_SEND_REALV
     */
`ifndef NO_SHUNT_DPI_SEND_REALV
   import "DPI-C" function int shunt_dpi_send_realV  (input int sockid,input int size,input  real Real[]);
`endif
   /*
    Functions: shunt_dpi_recv_realV
    map unpacked "real" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Real - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_REALV
    */
`ifndef NO_SHUNT_DPI_RECV_REALV
   import "DPI-C" function int shunt_dpi_recv_realV  (input int sockid,input int size,output real Real[]);
`endif

    /*
    Functions: shunt_dpi_send_shortrealV
    map unpacked "shortreal" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Shortreal - data

    Returns:
    number of bytes have been recv : success > 0

     Disable function `define:  NO_SHUNT_DPI_SEND_SHORTREALV
     */
`ifndef NO_SHUNT_DPI_SEND_SHORTREALV
   import "DPI-C" function int shunt_dpi_send_shortrealV  (input int sockid,input int size,input  shortreal Shortreal[]);
`endif
   /*
    Functions: shunt_dpi_recv_shortrealV
    map unpacked "shortreal" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    Shortreal - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_SHORTREALV
    */
`ifndef NO_SHUNT_DPI_RECV_SHORTREALV
   import "DPI-C" function int shunt_dpi_recv_shortrealV  (input int sockid,input int size,output shortreal Shortreal[]);
`endif


  /*
    Functions: shunt_dpi_send_integerV
    map unpacked "integer" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    IntegerV - data

    Returns:
    number of bytes have been recv : success > 0

   Disable function `define:  NO_SHUNT_DPI_SEND_INTEGERV
   */

`ifndef NO_SHUNT_DPI_SEND_INTEGERV
   import "DPI-C"  function int shunt_dpi_send_integerV (input int sockid,input int size,input integer IntegerV[]);
`endif

   /*
    Functions: shunt_dpi_recv_integerV
    map unpacked "integer" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    size - number of vector elements
    IntegerV - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_INTEGERV
    */
`ifndef NO_SHUNT_DPI_RECV_INTEGERV
   import "DPI-C"  function int shunt_dpi_recv_integerV (input  int sockid,input int size,output integer IntegerV[]);
`endif

   //Section: Integer/Non integer dynamic vectors

   // Variable: cs_header_t
   typedef struct packed {
      longint     trnx_type;
      longint     trnx_id;
      longint     data_type;
      longint     n_payloads;
   } cs_header_t;

   // Variable: cs_data_header_t
   // See Also:
   // <Data exchange structures and utilities>
/*

 Disable structure `define:   NO_CS_DATA_HEADER_T
 */
`ifndef  NO_CS_DATA_HEADER_T
   typedef struct{
      longint    data_type;
      int        trnx_payload_sizes[];
   }cs_data_header_t;
`endif

   /*
    Function: shunt_dpi_hash
    simple hash function

    Parameters:
    str - hash key

    Returns:
    hash value

    See Also:
    <shunt_prim_hash>

    Disable function `define:  NO_SHUNT_DPI_HASH
    */
`ifndef NO_SHUNT_DPI_HASH
   import "DPI-C" function longint shunt_dpi_hash(input string str);
`endif


   /*
    Function: shunt_dpi_send_header
    send SHUNT header over TCP/IP

    Parameters:

    sockid - socket id from init initiator/target
    h - cs_header verilog structure <cs_header_t>

    See Also:
    <Data exchange structures and utilities>

    Returns:
    number of elements have been sent  : success > 0

    Disable function `define:  NO_SHUNT_DPI_SEND_HEADER
    */
`ifndef NO_SHUNT_DPI_SEND_HEADER
   import "DPI-C" function int shunt_dpi_send_header(input int sockid,input cs_header_t h);
`endif

   /*
    Function: shunt_dpi_recv_header
    fetch SHUNT transaction header from TCP/IP socket

    Parameters:

    sockid - socket id from init initiator/target
    h - cs_header verilog structure <cs_header_t>

    See Also:
    <Data exchange structures and utilities>

    Returns:
    number of elements have been sent  : success > 0

    Disable function `define:  NO_SHUNT_DPI_RECV_HEADER
    */
`ifndef NO_SHUNT_DPI_RECV_HEADER
   import "DPI-C" function int shunt_dpi_recv_header(input int sockid,output cs_header_t h);
`endif


   /*
    Function: shunt_dpi_send_data_header
    send SHUNT data header over TCP/IP

    Parameters:
    sockid - socket id from init initiator/target
    h      - cs_header structure <cs_data_header_t>
    data_type - cs_data_header_t.data_type
    trnx_payload_sizes -cs_data_header_t.trnx_payload_sizes, number of data payloads.trnx_payload_sizes

    Returns:

    number of elements have been sent  : success > 0

    See Also:
    <Data exchange structures and utilities>

    Disable function `define:  NO_SHUNT_DPI_SEND_DATA_HEADER
    */
`ifndef NO_SHUNT_DPI_SEND_DATA_HEADER
   import "DPI-C" function int shunt_dpi_send_data_header(input int sockid,input cs_header_t h,input real data_type,input int trnx_payload_sizes[]);
`endif

   /*
    Function: shunt_dpi_recv_data_header
    fetch SHUNT transaction data header from TCP/IP socket

    Parameters:
    sockid - socket id from init initiator/target <cs_data_header_t>
    h      - cs_header structure <cs_header_t>
    data_type - cs_data_header_t.data_type
    trnx_payload_sizes -cs_data_header_t.trnx_payload_sizes, number of data payloads.trnx_payload_sizes

    Returns:

    number of elements have been sent  : success > 0

    See Also:
    <Data exchange structures and utilities>

    Disable function `define:  NO_SHUNT_DPI_RECV_DATA_HEADER
    */
`ifndef NO_SHUNT_DPI_RECV_DATA_HEADER
   import "DPI-C" function int shunt_dpi_recv_data_header(input int sockid,input cs_header_t h,inout real data_type,inout int  trnx_payload_sizes[]);
`endif


   /*
    Functions: shunt_dpi_hs_send_short
    map unpacked dynamic "shortint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_SHORT
    */
`ifndef NO_SHUNT_DPI_HS_SEND_SHORT
   import "DPI-C" function int shunt_dpi_hs_send_short     (input int sockid,input cs_header_t h_trnx,input shortint Array[]);
`endif

   /*
    Functions:  shunt_dpi_hs_recv_short
    map unpacked dynamic  "shortint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_SHORT
    */
`ifndef NO_SHUNT_DPI_HS_RECV_SHORT
   import "DPI-C" function int shunt_dpi_hs_recv_short     (input int sockid,input cs_header_t h_trnx,inout shortint Array[]);
`endif

   /*
    Functions: shunt_dpi_hs_send_int
    map unpacked dynamic "int" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_INT
    */
`ifndef NO_SHUNT_DPI_HS_SEND_INT
   import "DPI-C" function int shunt_dpi_hs_send_int       (input int sockid,input cs_header_t h_trnx,input int  Array[]);
`endif

   /*
    Functions:  shunt_dpi_hs_recv_int
    map unpacked dynamic "int" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_INT
    */
`ifndef NO_SHUNT_DPI_HS_RECV_INT
   import "DPI-C" function int shunt_dpi_hs_recv_int       (input int sockid,input cs_header_t h_trnx,inout int  Array[]);
`endif

    /*
    Functions: shunt_dpi_hs_send_long
    map unpacked dynamic "longint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

     Disable function `define:  NO_SHUNT_DPI_HS_SEND_LONG
     */
`ifndef NO_SHUNT_DPI_HS_SEND_LONG
   import "DPI-C" function int shunt_dpi_hs_send_long      (input int sockid,input cs_header_t h_trnx,input longint Array[]);
`endif

   /*
    Functions: shunt_dpi_hs_recv_long
    map unpacked dynamic  "longint" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_LONG
    */
`ifndef NO_SHUNT_DPI_HS_RECV_LONG
   import "DPI-C" function int shunt_dpi_hs_recv_long      (input int sockid,input cs_header_t h_trnx,inout longint Array[]);
`endif

   /*
    Functions: shunt_dpi_hs_send_byte
    map  unpacked dynamic "byte" one-dimensional array
    LRM 6.11 Integer data types char/char*

    Parameters:
    sockid - socket id
    Array - data

    Returns:
    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_BYTE
    */
`ifndef NO_SHUNT_DPI_HS_SEND_BYTE
   import "DPI-C" function int shunt_dpi_hs_send_byte      (input int sockid,input cs_header_t h_trnx,input byte Array[]);
`endif

   /*
    Functions:  shunt_dpi_hs_recv_byte
    map  unpacked dynamic "byte" one-dimensional array
    LRM 6.11 Integer data types char/char*

    Parameters:
    sockid - socket id
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_BYTE
    */
`ifndef NO_SHUNT_DPI_HS_RECV_BYTE
   import "DPI-C" function int shunt_dpi_hs_recv_byte      (input int sockid,input cs_header_t h_trnx,inout byte Array[]);
`endif

   /*
    Functions: shunt_dpi_hs_send_string
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes
    LRM 6.16

    Parameters:
    sockid - socket id
    String - data

    Returns:
    number of bytes have been sent : success > 0

    See Also:
    <shunt_dpi_send_string>

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_STRING
    */
`ifndef NO_SHUNT_DPI_HS_SEND_STRING
   import "DPI-C" function int shunt_dpi_hs_send_string    (input int sockid,input cs_header_t h_trnx,input string String);
`endif

   /*
    Functions: shunt_dpi_hs_recv_string
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes
    LRM 6.16

    Parameters:
    sockid - socket id
    String - data

    Returns:
    number of bytes have been recv : success > 0

    See Also:
    <shunt_dpi_recv_string>

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_STRING
    */
`ifndef NO_SHUNT_DPI_HS_RECV_STRING
   import "DPI-C" function int shunt_dpi_hs_recv_string    (input int sockid,input cs_header_t h_trnx,inout string String);
`endif

   /*
    Functions: shunt_dpi_hs_send_integer
    map  unpacked dynamic  "integer" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_INTEGER
    */
`ifndef NO_SHUNT_DPI_HS_SEND_INTEGER
   import "DPI-C" function int shunt_dpi_hs_send_integer   (input int sockid,input cs_header_t h_trnx,input integer Array[]);
`endif

   /*
    Functions: shunt_dpi_hs_recv_integer
    map unpacked  dynamic "integer" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_INTEGER
    */
`ifndef NO_SHUNT_DPI_HS_RECV_INTEGER
   import "DPI-C" function int shunt_dpi_hs_recv_integer   (input int sockid,input cs_header_t h_trnx,inout integer Array[]);
`endif

   /*
    Functions: shunt_dpi_hs_send_real
    map unpacked dynamic  "real" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_REAL
    */
`ifndef NO_SHUNT_DPI_HS_SEND_REAL
   import "DPI-C" function int shunt_dpi_hs_send_real      (input int sockid,input cs_header_t h_trnx,input real Array[]);
`endif
   /*
    Functions: shunt_dpi_hs_recv_real
    map unpacked  dynamic "real" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_REAL
    */
`ifndef NO_SHUNT_DPI_HS_RECV_REAL
   import "DPI-C" function int shunt_dpi_hs_recv_real      (input int sockid,input cs_header_t h_trnx,inout real Array[]);
`endif

   /*
    Functions: shunt_dpi_hs_send_shortreal
    map unpacked dynamic "shortreal" one-dimensional array
    LRM 7.4.2

    Parameters:
    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:
    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_SHORTREAL
    */
`ifndef NO_SHUNT_DPI_HS_SEND_SHORTREAL
   import "DPI-C" function int shunt_dpi_hs_send_shortreal (input int sockid,input cs_header_t h_trnx,input shortreal Array[]);
`endif

   /*
    Functions:  shunt_dpi_hs_recv_shortreal
    map unpacked dynamic "shortreal" one-dimensional array
    LRM 7.4.2

    Parameters:

    sockid - socket id
    h_trnx - <cs_header_t> structure
    Array - data

    Returns:

    number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_SHORTREAL
    */
`ifndef NO_SHUNT_DPI_HS_RECV_SHORTREAL
   import "DPI-C" function int shunt_dpi_hs_recv_shortreal (input int sockid,input cs_header_t h_trnx,inout shortreal Array[]);
`endif

   /*
    Functions:  shunt_dpi_hs_send_bitN
    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11

    Parameters:

    sockid - socket id
    bitN - data
    h_trnx - <cs_header_t> structure

    Returns:

    number of bytes have been sent : success > 0


    Disable function `define:  NO_SHUNT_DPI_HS_SEND_BITN
    */
`ifndef NO_SHUNT_DPI_HS_SEND_BITN
   import "DPI-C" function int shunt_dpi_hs_send_bitN (input int sockid,input cs_header_t h_trnx,input bit[] bitN);
`endif

   /*
    Functions: shunt_dpi_hs_recv_bitN
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11

    Parameters:

    sockid - socket id
    bitN - data
    h_trnx - <cs_header_t> structure

    Returns:

    number of bytes have been recv : success > 0



    Disable function `define:  NO_SHUNT_DPI_HS_RECV_BITN
    */
`ifndef NO_SHUNT_DPI_HS_RECV_BITN
   import "DPI-C" function int shunt_dpi_hs_recv_bitN    (input int sockid,input cs_header_t h_trnx,inout bit[] bitN);
`endif



   /*
    Functions: shunt_dpi_hs_send_regN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned
    LRM 6.11

    Parameters:

    sockid - socket id
    Reg  - data
    h_trnx - cs_header verilog structure <cs_header_t>

    Returns:

    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_REGN
    */
`ifndef NO_SHUNT_DPI_HS_SEND_REGN
   import "DPI-C" function int shunt_dpi_hs_send_regN   (input int sockid,input cs_header_t h_trnx,input reg[] Reg);
`endif

   /*
    Functions: shunt_dpi_hs_send_logicN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned
    LRM 6.11

    Parameters:

    sockid - socket id
    Reg  - data
    h_trnx - cs_header_t structure

    Returns:

    number of bytes have been sent : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_SEND_LOGICN
    */
`ifndef NO_SHUNT_DPI_HS_SEND_LOGICN
   import "DPI-C" function int shunt_dpi_hs_send_logicN (input int sockid,input cs_header_t h_trnx,input logic[] Reg);
`endif

    /*
    Functions: shunt_dpi_hs_recv_regN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned
    LRM  6.11

    Parameters:

     sockid - socket id
    Reg - data
    h_trnx - cs_header_t structure

    Returns:

     number of bytes have been recv : success > 0

    Disable function `define:  NO_SHUNT_DPI_HS_RECV_REGN
     */
`ifndef NO_SHUNT_DPI_HS_RECV_REGN
   import "DPI-C" function int shunt_dpi_hs_recv_regN   (input int sockid,input cs_header_t h_trnx,inout reg[] Reg);
`endif

   /*
    Functions: shunt_dpi_hs_recv_logicN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned
    LRM  6.11

    Parameters:

    sockid - socket id
    Reg - data
    h_trnx - cs_header_t structure

    Returns:

    number of bytes have been recv : success > 0

    Disable function `define: switch: NO_SHUNT_DPI_HS_RECV_LOGICN
    */
`ifndef NO_SHUNT_DPI_HS_RECV_LOGICN
   import "DPI-C" function int shunt_dpi_hs_recv_logicN (input int sockid,input cs_header_t h_trnx,inout logic[] Reg);
`endif

   /*
    Function: shunt_pkt_send_longV
    map unpacked "longint" paket (cs_header structure + one-dimensional data payload array)

    Parameters:

    sockid - socket id from init sever/client
    h - cs_header structure
    longV - data payload

    Returns:
    number of elements have been sent  : success > 0
    */

`ifndef NO_SHUNT_DPI_SEND_PKT_LONGV
   import "DPI-C" function int shunt_dpi_send_pkt_longV (input int sockid,input cs_header_t h_trnx,input  longint Int[]);
`endif

   /*
    Function: shunt_pkt_send_longV
    map unpacked "longint" paket (cs_header structure + one-dimensional data payload array)

    Parameters:

    sockid - socket id from init sever/client
    h - cs_header structure
    longV - data payload

    Returns:
    number of elements have been sent  : success > 0
    */

`ifndef NO_SHUNT_DPI_RECV_PKT_LONGV
   import "DPI-C" function int shunt_dpi_recv_pkt_longV (input int sockid,inout cs_header_t h,output longint Int[]);
`endif

   // Section: System (non TCP) utils


   /*
    Function:  shunt_dpi_gettimeofday_sec
    maps linux  gettimeofday function ,

    Parameters:

    Returns: longint the number of seconds since the Epoch
    longint a
    */
`ifndef NO_SHUNT_DPI_GETTIMEOFDAY_SEC;
  import "DPI-C" function longint shunt_dpi_gettimeofday_sec();
`endif

   /*
    Function:  shunt_dpi_gettimeofday_usec
    maps linux  gettimeofday function ,

    Parameters:

    Returns: longint the number of microsecond since the Epoch
    longint a
    */
`ifndef NO_SHUNT_DPI_GETTIMEOFDAY_USEC;
   import "DPI-C" function longint shunt_dpi_gettimeofday_usec();
`endif

   //Section: Data TLM2.0 utils

   /*
    Variable:  cs_tlm_generic_payload_header_t

    *TLM 2.0 Generic Payload structure* (Ref. to TLM 2.0 Generic Payload attributes)

    - *option*       Generic payload option :

    --- Code
    enum  tlm_gp_option { SHUNT_TLM_MIN_PAYLOAD, SHUNT_TLM_FULL_PAYLOAD, SHUNT_TLM_FULL_PAYLOAD_ACCEPTED }
    ---

    - *command*     Transaction type:

    --- Code
    enum  tlm_command { SHUNT_TLM_READ_COMMAND, SHUNT_TLM_WRITE_COMMAND, SHUNT_TLM_IGNORE_COMMAND }
    ---

    - *address*      Transaction base start address (bytes)

    - *length*       Total number of bytes of the transaction.

    - *byte_enable_length*  Number of elements in the bytes enable array.

    - *streaming_width*     Number of bytes transferred on each data-beat.

    - *dmi_allowed*    DMI allowed/not allowed (bool atribute)

    - *response_status*    Transaction status:

    --- Code
    enum  tlm_response_status {
    SHUNT_TLM_OK_RESPONSE = 1, SHUNT_TLM_INCOMPLETE_RESPONSE = 0, SHUNT_TLM_GENERIC_ERROR_RESPONSE = -1, SHUNT_TLM_ADDRESS_ERROR_RESPONSE = -2,
    SHUNT_TLM_COMMAND_ERROR_RESPONSE = -3, SHUNT_TLM_BURST_ERROR_RESPONSE = -4, SHUNT_TLM_BYTE_ENABLE_ERROR_RESPONSE = -5
    }
    ---

    - *delay*      Shunt tlm header extension equal to b_transport/nb_trasport delay atribute

    - *tlm_phase*      Shunt tlm header nb_trasport atribute:

    --- Code
    enum  tlm_phase_enum {
    UNINITIALIZED_PHASE =0, BEGIN_REQ =1, END_REQ, BEGIN_RESP,END_RESP
    }
    ---

    - *tlm_sync*     shunt tlm header nb_trasport atribute:

    --- Code
    enum  tlm_sync_enum { SHUNT_TLM_ACCEPTED, SHUNT_TLM_UPDATED, SHUNT_TLM_COMPLETED }
    ---

    - *tlm_extension_id*  (long) tlm_extension id. if "0" - extension is not available
    */
   typedef struct packed {
      longint       option;
      longint       address;
      longint       command;
      longint       length;
      longint       byte_enable_length;
      longint       streaming_width;
      longint       dmi;
      longint       response_status;
      longint       delay;
      longint       tlm_phase;
      longint       tlm_sync;
      longint       tlm_extension_id;
   } cs_tlm_generic_payload_header_t;
/*
  Variable:   cs_tlm_axi3_extension_payload_header_t

   *TLM 2.0  ARM AXI3 signals extension structure*  REF to Copyright 2003, 2004, 2010, 2011 ARM. All rights reserved.ARM IHI 0022D (ID102711)

   - *AxBURST* - determines how the address for each transfer within the burst is calculated

   --- Code
   AxBURST[1:0] | Burst type
   =========================
   0b00         |  FIXED
   0b01         |  INCR
   0b10         |  WRAP
   0b11         |  Reserved
   ---

   *AxCACHE* - Memory type indicates how transactions are required to progress through a system

   --- Code
   AxCACHE | Value | Transaction attribute
    ======================================
    [0]    |   0   |    Non-bufferable
           |   1   |    Bufferable
    [1]    |   0   |    Non-cacheable
           |   1   |    Cacheable
    [2]    |   0   |    No Read-allocate
           |   1   |    Read-allocate
    [3]    |   0   |    No Write-allocate
           |   1   |    Write-allocate
   ---

   *AxID*  - is identification tag for the transaction address group.

   *AxLEN* - gives the exact number of transfers in a burst.

   *AxLOCK*  - provides additional information about the transaction atomic characteristics

   --- Code
   AxLOCK[1:0] | Access type
   =============================
   0b00        | Normal access
   0b01        | Exclusive access
   0b10        | Locked access
   0b11        | Reserved
   ---

   *AxPROT* - indicates the privilege and transaction security level.

   --- Code
    AxPROT | Value |     Function
    =====================================
    [0]    |   0   |  Unprivileged access
           |   1   |  Privileged access
    [1]    |   0   |  Secure access
           |   1   |  Non-secure access
    [2]    |   0   |  Data access
           |   1   |  Instruction access
    ---

    *AxSIZE* - indicates the size of each transfer in the burst.

    *xRESP*  - indicates the status of the read transfer.

    --- Code
    RRESP[1:0] |
    BRESP[1:0] | Response
    =====================
    0b00       | OKAY
    0b01       | EXOKAY
    0b10       | SLVERR
    0b11       | DECERR
    ---

    *xSTRB* -  indicates which byte lanes hold valid data.
*/

typedef struct packed{
  longint  AxBURST;
  longint  AxCACHE;
  longint  AxID;
  longint  AxLEN;
  longint  AxLOCK;
  longint  AxPROT;
  longint  AxSIZE;
  longint  xRESP;
  longint  xSTRB;
} cs_tlm_axi3_extension_payload_header_t;


 typedef enum {SHUNT_TLM_ACCEPTED,SHUNT_TLM_UPDATED,SHUNT_TLM_COMPLETED} shunt_tlm_sync_e;

 typedef enum {SHUNT_TLM_READ_COMMAND,SHUNT_TLM_WRITE_COMMAND,SHUNT_TLM_IGNORE_COMMAND,SHUNT_TLM_END_SIM,SHUNT_TLM_START_SIM} shunt_tlm_command_e;

 typedef enum {SHUNT_TLM_OK_RESPONSE=1,SHUNT_TLM_INCOMPLETE_RESPONSE=0,SHUNT_TLM_GENERIC_ERROR_RESPONSE=-1,
           SHUNT_TLM_ADDRESS_ERROR_RESPONSE=-2,SHUNT_TLM_COMMAND_ERROR_RESPONSE=-3,SHUNT_TLM_BURST_ERROR_RESPONSE=-4,
           SHUNT_TLM_BYTE_ENABLE_ERROR_RESPONSE=-5} shunt_tlm_response_status_e;

 typedef enum {SHUNT_TLM_MIN_PAYLOAD,SHUNT_TLM_FULL_PAYLOAD,SHUNT_TLM_FULL_PAYLOAD_ACCEPTED} shunt_tlm_gp_option_e;

 typedef enum {SHUNT_TLM_UNKNOWN_ENDIAN,SHUNT_TLM_LITTLE_ENDIAN,SHUNT_TLM_BIG_ENDIAN} shunt_tlm_endianness_e;

 typedef enum {SHUNT_TLM_UNINITIALIZED_PHASE=0,SHUNT_TLM_BEGIN_REQ=1,SHUNT_TLM_END_REQ,SHUNT_TLM_BEGIN_RESP,
           SHUNT_TLM_END_RESP} shunt_tlm_phase_e;

   /*
    Function: shunt_tlm_send_command
    send hunt_tlm_command

    Parameters:
    socket -  socket id
    Com   - <shunt_dpi_tlm_command_e>
    */
`ifndef NO_SHUNT_DPI_TLM_SEND_COMMAND
   import "DPI-C" function  void shunt_dpi_tlm_send_command(int socket,shunt_tlm_command_e Com);
`endif

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
`ifndef NO_SHUNT_DPI_TLM_HEADER_ID
   import "DPI-C" function longint shunt_dpi_tlm_header_id();
`endif

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

`ifndef  NO_SHUNT_DPI_TLM_DATA_LEADER
   import "DPI-C" function longint  shunt_dpi_tlm_data_id();
`endif

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
`ifndef NO_SHUNT_DPI_TLM_AXI3_EXT_ID
   import "DPI-C" function longint shunt_dpi_tlm_axi3_ext_id();
`endif

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

`ifndef  NO_SHUNT_DPI_TLM_SIGNAL_ID
   import "DPI-C" function longint  shunt_dpi_tlm_signal_id();
`endif

   /*
    Function: shunt_dpi_tlm_send_gp_transport
    send tlm generic payload  packet ( cs_tlm_generic_payload_header_t  + byte data vector + byte_enable vector )

    Parameters:

    sockid - socket id from init sever/client
    h - cs_tlm_generic_payload_header_t
    data - data payload array
    byte_enable - byte_enable array

    See Also:
    <shunt_cs_tlm_send_gp>
    */

`ifndef NO_SHUNT_DPI_TLM_SEND_GP_TRANSPORT
   import "DPI-C" function void shunt_dpi_tlm_send_gp_transport(input int sockid, inout cs_tlm_generic_payload_header_t h, inout  byte unsigned  data[], inout  byte unsigned  byte_enable[]);
`endif


/*
  Function: shunt_dpi_tlm_recv_gp_transport
  recieve tlm generic payload  packet (header + byte data vector + byte_enable vector )

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header_t (input only) should have a valid data length and byte_enable_length
  data - data payload byte-vector pointer  (output)
  byte_enable - byte_enable vector pointer (output)
*/
`ifndef NO_SHUNT_DPI_TLM_RECV_GP_TRANSPORT
   import "DPI-C"  function void  shunt_dpi_tlm_recv_gp_transport (input int sockid, inout cs_tlm_generic_payload_header_t h,inout byte unsigned data[],inout byte unsigned  byte_enable[]);
`endif

/*
  Function: shunt_dpi_tlm_recv_gp_header
  recieve tlm generic payload  header ( cs_tlm_generic_payload_header_t only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header_t (output)


*/
`ifndef NO_SHUNT_DPI_TLM_RECV_GP_HEADER
   import "DPI-C"  function void shunt_dpi_tlm_recv_gp_header (input int sockid, inout cs_tlm_generic_payload_header_t h);
`endif

/*
  Function: shunt_dpi_tlm_send_gp_header
  send tlm generic payload  header ( cs_tlm_generic_payload_header_t only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header_t (output)


*/
`ifndef NO_SHUNT_DPI_TLM_SEND_GP_HEADER
   import "DPI-C"  function void shunt_dpi_tlm_send_gp_header (input int sockid, inout cs_tlm_generic_payload_header_t h);
`endif

/*
  Function: shunt_dpi_tlm_recv_axi3_header
  recieve tlm generic payload  header ( cs_tlm_generic_payload_header_t only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header_t (output)


*/
`ifndef NO_SHUNT_DPI_TLM_RECV_AXI3_HEADER
   import "DPI-C" function void shunt_dpi_tlm_recv_axi3_header(input int sockid, inout cs_tlm_axi3_extension_payload_header_t h);
`endif

/*
  Function: shunt_dpi_tlm_send_axi3_header
  send tlm extension  header (cs_tlm_axi3_extension_payload_header only)

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_axi3_extension_payload_header_t (output)


*/
`ifndef NO_SHUNT_DPI_TLM_SEND_AXI3_HEADER
   import "DPI-C" function void shunt_dpi_tlm_send_axi3_header (input int sockid, inout cs_tlm_axi3_extension_payload_header_t h);
`endif

/*
  Function: shunt_dpi_tlm_recv_gp_data
  recieve tlm generic payload  packet (byte data vector + byte_enable vector )

  Parameters:

  sockid - socket id from init sever/client
  h - cs_tlm_generic_payload_header (input only) should have a valid data length and byte_enable_length
  data - data payload byte-vector pointer  (output)
  byte_enable - byte_enable vector pointer (output)
*/
`ifndef NO_SHUNT_DPI_TLM_RECV_GP_DATA
   import "DPI-C" function void shunt_dpi_tlm_recv_gp_data (input int sockid, input cs_tlm_generic_payload_header_t h,inout byte unsigned data[],inout byte unsigned   byte_enable[]);
`endif

   //axulary function

   function automatic void shunt_dpi_tlm_gp_header_print (cs_tlm_generic_payload_header_t csgp,string prefix="");
      /* verilator lint_off UNUSED */
      shunt_tlm_sync_e            tlm_sync_;
      shunt_tlm_command_e         command_;
      shunt_tlm_response_status_e response_status_;
      shunt_tlm_gp_option_e       option_;
      shunt_tlm_phase_e           tlm_phase_;

      tlm_sync_        = shunt_tlm_sync_e'(csgp.tlm_sync);
      command_         = shunt_tlm_command_e'(csgp.command);
      response_status_ = shunt_tlm_response_status_e'(csgp.response_status);
      option_          = shunt_tlm_gp_option_e'(csgp.option);
      tlm_phase_       = shunt_tlm_phase_e'(csgp.tlm_phase);

      $write("\n%0s option(%0s)",prefix, option_.name());
      $write(",address(%h)",csgp.address);
      $write(",command_(%s)",command_.name());
      $write(",length(%0d)",csgp.length);
      $write(",byte_enable_length(%0d)",csgp.byte_enable_length);
      $write(",streaming_width(%0d)",csgp.streaming_width);
      $write(",dmi(%0d)",csgp.dmi);
      $write(",response_status(%0d)",response_status_);
      $write(",delay(%0d)",csgp.delay);
      $write(",tlm_phase_(%0s)",tlm_phase_.name());
      $write(",tlm_sync(%0s)\n",tlm_sync_.name());
      $write(",tlm_extension_id(%0d)\n",csgp.tlm_extension_id);
      /* verilator lint_on UNUSED */
   endfunction : shunt_dpi_tlm_gp_header_print

   function automatic void shunt_dpi_tlm_axi3_header_print (cs_tlm_axi3_extension_payload_header_t h_axi3,string prefix="");
      /* verilator lint_off UNUSED */
      $write("\n%0s h_axi3.AxBURST(%0b)",prefix,h_axi3.AxBURST);
      $write(",h_axi3.AxCACHE(%0b)",h_axi3.AxCACHE);
      $write(",h_axi3.AxID(%0d)",h_axi3.AxID);
      $write(",h_axi3.AxLEN(%0d)",h_axi3.AxLEN);
      $write(",h_axi3.AxLOCK(%0b)",h_axi3.AxLOCK);
      $write(",h_axi3.AxPROT(%0b)",h_axi3.AxPROT);
      $write(",h_axi3.AxSIZE(%0d)",h_axi3.AxSIZE);
      $write(",h_axi3.xRESP(%0b)",h_axi3.xRESP);
      $write(",h_axi3.xSTRB(%0h)",h_axi3.xSTRB);
      /* verilator lint_on UNUSED */
   endfunction : shunt_dpi_tlm_axi3_header_print

endpackage : shunt_dpi_pkg
