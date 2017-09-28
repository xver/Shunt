/*
============================================================================
 File        : shunt_dpi_pkg.sv
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : shunt dpi bridge
               System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT) 
 
 Verilog Data Types : 
    
   Integer 2 states:
   SHUNT_INT         - int            function :shunt_cs_xxxx_int
   SHUNT_SHORTINT    - shortint       function :shunt_cs_xxxx_short
   SHUNT_LONGINT     - longint        function :shunt_cs_xxxx_long
   SHUNT_BYTE        - byte           function :shunt_cs_xxxx_byte
   SHUNT_BIT         - bit            function :shunt_cs_xxx_bitN
   
   Integer 4 states:
   SHUNT_INTEGER     - integer,time   function :shunt_cs_xxxx_integer
   SHUNT_REG         - reg,logic      function :shunt_cs_xxx_regN
   
   Non integer types IEEE 754:  
   SHUNT_REAL        - real,realtime  function :shunt_cs_xxxx_real
   SHUNT_SHORTREAL   - shortreal      function :shunt_cs_xxxx_shortreal
   SHUNT_STRING      - string (N/A)   function :shunt_cs_xxx_string
   
   SHUNT_A_STRUCTURE - complex data types/user defined data types : arrays/struct,union,enums (N/A)
   SHUNT_HEADER_ONLY - cs_header_t header only                                                (N/A)
 ============================================================================
*/
package shunt_dpi_pkg; 

`define SHUNT_MAX_SIZE = 4096;
   //Title: 5. Utilites: "C" to System Verilog mapping
   
   //Section: TCP/IP target/initiator init 
   
   /*
    Function: shunt_dpi_initiator_init
    TCP/IP initiator initialization
    
    Parameters: 
    portno - socket port
    
    Returns:  
    socket id
    (see shunt_prim_init_initiator)
    
    (start code)
    //Example:     
    #define MY_HOST "localhost"
    #define MY_PORT  3450
    
    int port;
    port = MY_PORT;
    
    shunt_prim_init_initiator(port);
    
    (end)
    
    */
  
   import "DPI-C" function int shunt_dpi_initiator_init (input int portno);
   
   /*
    Function: shunt_dpi_target_init
    TCP/IP target initialization
    
    portno - socket port
    hostname - initiator name    
    
    Returns:  
    socket id
    ( see  shunt_prim_init_tcptarget)
    
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
   
*/
   import "DPI-C" function int shunt_dpi_target_init (input int portno,input string hostname);
   
   
   //Section: Integer types 
   
   /*
    Functions:  shunt_dpi_send_short
    map shortint 2-state data type,16-bit signed integer 
    see SV LRM 6.11 Integer data types shortint/short int*
    
    Parameters:
    sockfd - socket id
    Short - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_short  (input int sockfd,input  shortint Short);
   
   /*
    Functions:  shunt_dpi_recv_short
    map shortint 2-state data type,16-bit signed integer 
    see SV LRM 6.11 Integer data types shortint/short int*
    
    Parameters:
    sockfd - socket id
    Short - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_short  (input int sockfd,output shortint Short);
   
   /*
    Functions:  shunt_dpi_send_int 
    map int 2-state data type,32-bit signed integer 
    LRM 6.11 Integer data types int/int*
    
    Parameters:
    sockfd - socket id
    Int - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_int    (input int sockfd,input  int Int);
   
   /*
    Functions: shunt_dpi_recv_int 
    map int 2-state data type,32-bit signed integer 
    LRM 6.11 Integer data types int/int*
    
    Parameters:
    sockfd - socket id
    Short - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_int    (input int sockfd,output int Int);
   
   /*
    Functions:  shunt_dpi_send_long
    map longintlongint 2-state data type,64-bit signed integer
    see SV LRM 6.11 Integer data types longint/long int*
    
    Parameters:
    sockfd - socket id
    Long - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_long  (input int sockfd,input  longint Long);
   
   /*
    Functions:  shunt_dpi_recv_long
    map longintlongint 2-state data type,64-bit signed integer
    see SV LRM 6.11 Integer data types longint/long int*
    
    Parameters:

    see SV LRM 6.11 Integer data types long int/long int*
    
    Parameters:
    sockfd - socket id
    Long - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_long  (input int sockfd,output longint Long);
   
   /*
    Functions:  shunt_dpi_send_byte
    map byte 2-state data type, 8-bit signed integer or ASCII character  
    LRM 6.11 Integer data types char/char*
    
    Parameters:
    sockfd - socket id
    Byte - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_byte   (input int sockfd,input  byte Byte);
  
   /*
    Functions:  shunt_dpi_recv_byte
    map byte 2-state data type, 8-bit signed integer or ASCII character  
    LRM 6.11 Integer data types char/char*
        
    Parameters:
    sockfd - socket id
    Byte - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
    import "DPI-C" function int shunt_dpi_recv_byte   (input int sockfd,output byte Byte);
   
   /*
    Functions:  shunt_dpi_send_integer
    map integer  4-state data type,32-bit signed integer 
    LRM 6.11 Integer data types
    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_integer (input int sockfd,input integer Int);
   
   /*
    Functions:  shunt_dpi_send_byte4s
    map reg[7:0]  4-state data type
    LRM 6.11 Integer data type
    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_byte4s (input int sockfd,input reg[7:0] Byte);
   
   /*
    Functions:  shunt_dpi_recv_integer
    map integer  4-state data type,32-bit signed integer 
    LRM 6.11 Integer data types
        
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   
   import "DPI-C" function int shunt_dpi_recv_integer (input int sockfd,inout integer Int);
   
   /*
    Functions:  shunt_dpi_recv_byte4s
    map reg[7:0]  4-state data type
    LRM 6.11 Integer data type
    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_byte4s (input int sockfd,inout reg[7:0] Byte);
  
   /*
    Functions:  shunt_dpi_send_time
    map time  4-state data type, 64-bit unsigned integer 
    LRM 6.11 
    
    Parameters:
    sockfd - socket id
    Time - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_time (input int sockfd,input time Time);
   
   /*
    Functions:  shunt_dpi_recv_time
    map time  4-state data type, 64-bit unsigned integer 
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Time - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_time (input int sockfd,inout time Time);
    
   /*
    Functions:  shunt_dpi_send_bit
    map bit 2-state data type,user-defined vector size unsigned 
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_bit (input int sockfd,input bit Bit);
   
   /*
    Functions:  shunt_dpi_recv_bit
    mapbit 2-state data type,user-defined vector size unsigned 
    LRM 6.11 
            
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_bit (input int sockfd,inout bit Bit);

   
  
/*
    Functions:  shunt_dpi_send_reg,shunt_dpi_send_logic
    map reg/logic 4-state data type
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_reg   (input int sockfd,input reg Reg);
   import "DPI-C" function int shunt_dpi_send_logic (input int sockfd,input logic Logic);
   /*
    Functions:  shunt_dpi_recv_reg ,shunt_dpi_recv_logic
    map reg/logic 4-state data type
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_reg   (input int sockfd,inout reg Reg);
   import "DPI-C" function int shunt_dpi_recv_logic (input int sockfd,inout logic Logic);
   
   //Section: Integer vector types (packed)    
   
   typedef struct{		
      real 	 trnx_type;
      real 	 trnx_id;
      real 	 data_type;
      int 	 n_payloads;
   } cs_header_t;
   
   typedef struct{
      real 	 data_type;
      int 	 trnx_payload_sizes[];
   }cs_data_header_t;
   
   /*
    Functions: shunt_dpi_hs_send_bitN
    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    h_trnx - cs_header_t structure
    Returns: 
    number of bytes have been sent : success > 0
    */
   
   import "DPI-C" function int shunt_dpi_send_bitN(input int sockfd,input int size,input bit[] bitN);
   /*
    Functions: shunt_dpi_hs_recv_bitN
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    h_trnx - cs_header_t structure
    
    Returns: 
    number of bytes have been recv : success > 0
    */
  
   import "DPI-C" function int shunt_dpi_recv_bitN  (input int sockfd,input int size,inout bit[] bitN);
   
  
  
   //Section: non_integer_type IEEE 754
      
   /*
    Functions: shunt_dpi_send_real,shunt_dpi_send_realtime
    map real data type is the same as a C double 8 byte 
    LRM 6.12
           
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */ 
   import "DPI-C" function int shunt_dpi_send_real      (input int sockfd,input  real Real);
   //import "DPI-C" function int shunt_dpi_send_realtime  (input int sockfd,input  realtime Real);
   import "DPI-C" function int shunt_dpi_send_shortreal (input int sockfd,input  shortreal Real);
   /*
    Functions: shunt_dpi_recv_real,shunt_dpi_recv_realtime
    map real data type is the same as a C double 8 byte  
    LRM 6.12
    
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_real      (input int sockfd,output real Real);
   //import "DPI-C" function int shunt_dpi_recv_realtime  (input int sockfd,output realtime Real);
   import "DPI-C" function int shunt_dpi_recv_shortreal (input int sockfd,output shortreal Real);

   //Section: special types
  
   /*
    Functions: shunt_dpi_send_string
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes 
    LRM 6.16
           
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */ 
   import "DPI-C" function int shunt_dpi_send_string (input int sockid,input int size,input  string String);
  
   /*
    Functions: shunt_dpi_recv_string
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes 
    LRM 6.16 
    
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_string (input int sockid,input int size,inout  string String);
   
   //Section: Integer vector types (unpacked)    
  
   /*
    Functions:  shunt_dpi_send_intV
    map unpacked "int" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_intV   (input int sockid,input int size,input  int Int[]);
   
   /*
    Functions:  shunt_dpi_recv_intV
    map unpacked "int" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_intV   (input int sockid,input int size,output int Int[]);

   
   /*
    Functions:  shunt_dpi_send_shorV
    map unpacked "shortint" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_shortV (input int sockid,input int size,input  shortint Int[]);
   /*
    Functions:  shunt_dpi_recv_shortV
    map unpacked "shortint" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_shortV (input int sockid,input int size,output shortint Int[]);
  
   /*
    Functions:   shunt_dpi_send_longV 
    map unpacked "longint" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_longV (input int sockid,input int size,input  longint Int[]);
   
   /*
    Functions: shunt_dpi_recv_longV
    map unpacked "longint" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_longV (input int sockid,input int size,output longint Int[]);


  
    /*
    Functions: vcs_dpi_send_realV  
    map unpacked "real" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Real - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */  
   import "DPI-C" function int shunt_dpi_send_realV  (input int sockid,input int size,input  real Real[]);
   /*
    Functions: shunt_dpi_recv_realV 
    map unpacked "real" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Real - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_realV  (input int sockid,input int size,output real Real[]);
   
    /*
    Functions: shunt_dpi_send_shortrealV  
    map unpacked "shortreal" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Shortreal - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */  
   import "DPI-C" function int shunt_dpi_send_shortrealV  (input int sockid,input int size,input  shortreal Shortreal[]);
   /*
    Functions: shunt_dpi_recv_shortrealV 
    map unpacked "shortreal" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Shortreal - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_recv_shortrealV  (input int sockid,input int size,output shortreal Shortreal[]);
    
  
  /*
    Functions: vcs_dpi_send_integerV  
    map unpacked "integer" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    IntegerV - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */  

   import "DPI-C"  function int shunt_dpi_send_integerV (input int sockid,input int size,input integer IntegerV[]);
   
   /*
    Functions: shunt_dpi_recv_integerV 
    map unpacked "integer" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    IntegerV - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C"  function int shunt_dpi_recv_integerV (input  int sockid,input int size,output integer IntegerV[]);
 
   //Section: Integer/Non integer dynamic vectors (unpacked)     

   /*
    Function: shunt_dpi_hash
    simple hash function 
    
    Parameters: 
    str - hash key
    
    Returns: 
    hash value
     see(shunt_prim_hash)
    */
   import "DPI-C" function real shunt_dpi_hash(input string str);
   
 
   /*
    Function: shunt_dpi_send_header
    send SHUNT header over TCP/IP
    
    Parameters:
    
    sockid - socket id from init initiator/target 
    h - cs_header verilog structure 
    (start code) 
     typedef struct{		
      real 	 trnx_type;  // user defined transaction attribute
      real 	 trnx_id;    // user defined unique transaction number
      real 	 data_type;  // see SHUNT_INSTR_ENUM
      int 	 n_payloads; // Victors:number of data payloads , 
                             //Arrays:number of vectors
                             //Packed Vectors:number of bits 
   } cs_header_t;
    (end)
    
    see( Data exchange utilities cs_header )      
    Returns:
    number of elements have been sent  : success > 0
    */ 
   import "DPI-C" function int shunt_dpi_send_header(input int sockid,input cs_header_t h);

   /*
    Function: shunt_dpi_recv_header
    fetch SHUNT transaction header from TCP/IP socket
    
    Parameters:
    
    sockid - socket id from init initiator/target 
    h - cs_header verilog structure 
    (start code) 
     typedef struct{		
      real 	 trnx_type;  // user defined transaction attribute
      real 	 trnx_id;    // user defined unique transaction number
      real 	 data_type;  // see SHUNT_INSTR_ENUM
      int 	 n_payloads; // Victors:number of data payloads , 
                             //Arrays:number of vectors
                             //Packed Vectors:number of bits 
   } cs_header_t;
    (end)
    
    see( Data exchange utilities cs_header )      
    Returns:
    number of elements have been sent  : success > 0
    */ 
   import "DPI-C" function int shunt_dpi_recv_header(input int sockid,output cs_header_t h);
   
   
   /*
    Function: shunt_dpi_send_data_header
    send SHUNT data header over TCP/IP
    (start code)  
     typedef struct{
      real 	 data_type;  // see SHUNT_INSTR_ENUM
      int 	 trnx_payload_sizes[]; // array of payload sizes, number of array elements are equal to n_payloads
    }cs_data_header_t;
    (end)
             
    Parameters:
    sockid - socket id from init initiator/target 
    h      - cs_header structure
    data_type - cs_data_header_t.data_type
    trnx_payload_sizes -cs_data_header_t.trnx_payload_sizes, number of data payloads.trnx_payload_sizes
    
    Returns:
    
    number of elements have been sent  : success > 0
    */
   import "DPI-C" function int shunt_dpi_send_data_header(input int sockid,input cs_header_t h,input real data_type,input int trnx_payload_sizes[]);
  
/*
    Function: shunt_dpi_recv_data_header
    fetch SHUNT transaction data header from TCP/IP socket
    (start code)  
     typedef struct{
      real 	 data_type;  // see SHUNT_INSTR_ENUM
      int 	 trnx_payload_sizes[]; // array of payload sizes, number of array elements are equal to n_payloads
    }cs_data_header_t;
    (end)
             
    Parameters:
    sockid - socket id from init initiator/target 
    h      - cs_header structure
    data_type - cs_data_header_t.data_type
    trnx_payload_sizes -cs_data_header_t.trnx_payload_sizes, number of data payloads.trnx_payload_sizes
    
    Returns:
    
    number of elements have been sent  : success > 0
    */ 
   import "DPI-C" function int shunt_dpi_recv_data_header(input int sockid,input cs_header_t h,inout real data_type,inout int  trnx_payload_sizes[]);
   
  
   /*
    Functions: shunt_dpi_hs_send_short
    map unpacked dynamic "shortint" one-dimensional array 
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_send_short     (input int sockid,input cs_header_t h_trnx,input shortint Array[]);
  
   /*
    Functions:  shunt_dpi_hs_recv_short
    map unpacked dynamic  "shortint" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */ 
   import "DPI-C" function int shunt_dpi_hs_recv_short     (input int sockid,input cs_header_t h_trnx,inout shortint Array[]); 
   
   /*
    Functions: shunt_dpi_hs_send_int 
    map unpacked dynamic "int" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_send_int       (input int sockid,input cs_header_t h_trnx,input int  Array[]);
    
   /*
    Functions:  shunt_dpi_hs_recv_int
    map unpacked dynamic "int" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_recv_int       (input int sockid,input cs_header_t h_trnx,inout int  Array[]);

    /*
    Functions: shunt_dpi_hs_send_long  
    map unpacked dynamic "longint" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_send_long      (input int sockid,input cs_header_t h_trnx,input longint Array[]);

   /*
    Functions: shunt_dpi_hs_recv_long
    map unpacked dynamic  "longint" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_recv_long      (input int sockid,input cs_header_t h_trnx,inout longint Array[]);
   
   /*
    Functions: shunt_dpi_hs_send_byte
    map  unpacked dynamic "byte" one-dimensional array 
    LRM 6.11 Integer data types char/char*
    
    Parameters:
    sockfd - socket id
    Byte - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_send_byte      (input int sockid,input cs_header_t h_trnx,input byte Array[]);
  
   /*
    Functions:  shunt_dpi_hs_recv_byte
    map  unpacked dynamic "byte" one-dimensional array 
    LRM 6.11 Integer data types char/char*
        
    Parameters:
    sockfd - socket id
    Byte - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_recv_byte      (input int sockid,input cs_header_t h_trnx,inout byte Array[]);

   /*
    Functions: shunt_dpi_hs_send_string
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes 
    LRM 6.16   
           
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    
    see(shunt_dpi_send_string)
    */ 
   import "DPI-C" function int shunt_dpi_hs_send_string    (input int sockid,input cs_header_t h_trnx,input string String);

   /*
    Functions:shunt_dpi_hs_recv_string  
    map string string is an ordered collection of characters be indexed as a unpacked array of bytes 
    LRM 6.16 
    
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    
    see(shunt_dpi_recv_string)
    */
   import "DPI-C" function int shunt_dpi_hs_recv_string    (input int sockid,input cs_header_t h_trnx,inout string String);
   
   /*
    Functions: vcs_dpi_send_integer  
    map  unpacked dynamic  "integer" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    IntegerV - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */  
   import "DPI-C" function int shunt_dpi_hs_send_integer   (input int sockid,input cs_header_t h_trnx,input integer Array[]);
   
   /*
    Functions: shunt_dpi_recv_integer 
    map unpacked  dynamic "integer" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    IntegerV - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_recv_integer   (input int sockid,input cs_header_t h_trnx,inout integer Array[]);
   
   /*
    Functions: shunt_dpi_hs_send_real
    map unpacked dynamic  "real" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Real - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */  
   import "DPI-C" function int shunt_dpi_hs_send_real      (input int sockid,input cs_header_t h_trnx,input real Array[]);
   /*
    Functions: shunt_dpi_hs_recv_real
    map unpacked  dynamic "real" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Real - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_recv_real      (input int sockid,input cs_header_t h_trnx,inout real Array[]);
    
   /*
    Functions: shunt_dpi_hs_send_shortreal
    map unpacked dynamic "shortreal" one-dimensional array
    LRM 7.4.2 
    
    Parameters:
    sockfd - socket id
    size - number of vector elements 
    Shortreal - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */  
   import "DPI-C" function int shunt_dpi_hs_send_shortreal (input int sockid,input cs_header_t h_trnx,input shortreal Array[]);
    /*
    Functions:  shunt_dpi_hs_recv_shortreal
    map unpacked dynamic "shortreal" one-dimensional array
    LRM 7.4.2 
    
    Parameters: shunt_dpi_hs_recv_shortreal
    sockfd - socket id
    size - number of vector elements 
    Shortreal - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_recv_shortreal (input int sockid,input cs_header_t h_trnx,inout shortreal Array[]);
   
   /*
    Functions: 
    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11 
        
    Parameters: shunt_dpi_hs_send_bitN 
    sockfd - socket id
    Reg,Logic - data
    h_trnx - cs_header_t structure
    Returns: 
    number of bytes have been sent : success > 0
   
    see(shunt_dpi_hs_send_bitN)
    */
   import "DPI-C" function int shunt_dpi_hs_send_bitN    (input int sockfd,input cs_header_t h_trnx,input bit[] bitN);

   /*
    Functions: shunt_dpi_hs_recv_bitN 
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    h_trnx - cs_header_t structure
    
    Returns: 
    number of bytes have been recv : success > 0
    
    see(shunt_dpi_hs_recv_bitN)
    */
   import "DPI-C" function int shunt_dpi_hs_recv_bitN    (input int sockfd,input cs_header_t h_trnx,inout bit[] bitN);
   
   
//////////////////END/////////////////////////////////////////////////////////////////////
     
   /*
    Functions: shunt_dpi_hs_send_regN, shunt_dpi_hs_send_reg4s, shunt_dpi_hs_send_logicN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned 
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    h_trnx - cs_header_t structure
      
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_send_regN   (input int sockfd,input cs_header_t h_trnx,input reg[] Reg);
   
   import "DPI-C" function int shunt_dpi_hs_send_logicN (input int sockfd,input cs_header_t h_trnx,input logic[] Reg);

    /*
    Functions: shunt_dpi_hs_recv_regN,shunt_dpi_hs_recv_reg4s,shunt_dpi_hs_recv_logicN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    h_trnx - cs_header_t structure
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int shunt_dpi_hs_recv_regN   (input int sockfd,input cs_header_t h_trnx,inout reg[] Reg);
   import "DPI-C" function int shunt_dpi_hs_recv_logicN (input int sockfd,input cs_header_t h_trnx,inout logic[] Reg);

endpackage : shunt_dpi_pkg


