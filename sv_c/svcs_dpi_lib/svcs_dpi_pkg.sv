/*
============================================================================
 File        : svcs_dpi_pkg.sv
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : System Verilog client server handshake (SVCS) library SV domain
 ============================================================================
*/
package svcs_dpi_pkg; 

`define SVCS_MAX_SIZE = 4096;
   //Title: 5. Utilites: "C" to System Verilog mapping
   

   
   
   import "DPI-C" function int svcs_dpi_server_init (input int portno);
   import "DPI-C" function int svcs_dpi_client_init (input int portno,input string hostname);
   
   //Section: integer_atom_type 
   
   /*
    Functions:  svcs_dpi_send_short
    map shortint 2-state data type,16-bit signed integer 
    see SV LRM 6.11 Integer data types shortint/short int*
    
    Parameters:
    sockfd - socket id
    Short - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_short  (input int sockfd,input  shortint Short);
   
   /*
    Functions:  svcs_dpi_recv_short
    map shortint 2-state data type,16-bit signed integer 
    see SV LRM 6.11 Integer data types shortint/short int*
    
    Parameters:
    sockfd - socket id
    Short - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_recv_short  (input int sockfd,output shortint Short);
   
   /*
    Functions:  svcs_dpi_send_int 
    map int 2-state data type,32-bit signed integer 
    LRM 6.11 Integer data types int/int*
    
    Parameters:
    sockfd - socket id
    Int - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_int    (input int sockfd,input  int Int);
   
   /*
    Functions: svcs_dpi_recv_int 
    map int 2-state data type,32-bit signed integer 
    LRM 6.11 Integer data types int/int*
    
    Parameters:
    sockfd - socket id
    Short - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_recv_int    (input int sockfd,output int Int);
   
   /*
    Functions:  svcs_dpi_send_long
    map longintlongint 2-state data type,64-bit signed integer
    see SV LRM 6.11 Integer data types longint/long int*
    
    Parameters:
    sockfd - socket id
    Long - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_long  (input int sockfd,input  longint Long);
   
   /*
    Functions:  svcs_dpi_recv_long
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
   import "DPI-C" function int svcs_dpi_recv_long  (input int sockfd,output longint Long);
   
   /*
    Functions:  svcs_dpi_send_byte
    map byte 2-state data type, 8-bit signed integer or ASCII character  
    LRM 6.11 Integer data types char/char*
    
    Parameters:
    sockfd - socket id
    Byte - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_byte   (input int sockfd,input  byte Byte);
  
   /*
    Functions:  svcs_dpi_recv_byte
    map byte 2-state data type, 8-bit signed integer or ASCII character  
    LRM 6.11 Integer data types char/char*
        
    Parameters:
    sockfd - socket id
    Byte - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
  
   /*
    Functions:  svcs_dpi_send_integer
    map integer  4-state data type,32-bit signed integer 
    LRM 6.11 Integer data types
    
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_integer (input int sockfd,input integer Int);
   
   /*
    Functions:  svcs_dpi_recv_integer
    map integer  4-state data type,32-bit signed integer 
    LRM 6.11 Integer data types
        
    Parameters:
    sockfd - socket id
    Integer - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   
   import "DPI-C" function int svcs_dpi_recv_integer (input int sockfd,inout integer Int);
   import "DPI-C" function int svcs_dpi_recv_byte   (input int sockfd,output byte Byte);
  
   /*
    Functions:  svcs_dpi_send_time
    map time  4-state data type, 64-bit unsigned integer 
    LRM 6.11 
    
    Parameters:
    sockfd - socket id
    Time - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_time (input int sockfd,input time Time);
   /*
    Functions:  svcs_dpi_recv_time
    map time  4-state data type, 64-bit unsigned integer 
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Time - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_recv_time (input int sockfd,inout time Time);
    
   /*
    Functions:  svcs_dpi_send_bit
    map bit 2-state data type,user-defined vector size unsigned 
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_bit (input int sockfd,input bit Bit);
   
   /*
    Functions:  svcs_dpi_recv_bit
    mapbit 2-state data type,user-defined vector size unsigned 
    LRM 6.11 
            
    Parameters:
    sockfd - socket id
    Bit - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_recv_bit (input int sockfd,inout bit Bit);

   
  
/*
    Functions:  svcs_dpi_send_reg,svcs_dpi_send_logic
    map reg/logic 4-state data type
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_send_reg   (input int sockfd,input reg Reg);
   import "DPI-C" function int svcs_dpi_send_logic (input int sockfd,input logic Logic);
   /*
    Functions:  svcs_dpi_recv_reg ,svcs_dpi_recv_logic
    map reg/logic 4-state data type
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_recv_reg   (input int sockfd,inout reg Reg);
   import "DPI-C" function int svcs_dpi_recv_logic (input int sockfd,inout logic Logic);
   
   //Section: integer_vector_type    
   
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
    Functions: svcs_dpi_hs_send_bitN
    map bit[N:0]  2-state data type packed array of scalar bit types
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_hs_send_bitN(input int sockfd,input cs_header_t h_trnx,input bit[] bitN);
   
   /*
    Functions: svcs_dpi_hs_recv_bitN
    map bit[N:0] 2-state data type packed array of scalar bit types
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_hs_recv_bitN  (input int sockfd,input cs_header_t h_trnx,inout bit[] bitN);
 
    /*
    Functions: svcs_dpi_hs_send_regN, svcs_dpi_hs_send_reg4s, svcs_dpi_hs_send_logicN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned 
    LRM 6.11 
        
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */
   import "DPI-C" function int svcs_dpi_hs_send_reg4s  (input int sockfd,input cs_header_t h_trnx,input reg[] Reg);
   import "DPI-C" function int svcs_dpi_hs_send_regN   (input int sockfd,input cs_header_t h_trnx,input reg[] Reg);
   import "DPI-C" function int svcs_dpi_hs_send_logicN (input int sockfd,input cs_header_t h_trnx,input logic[] Reg);
   /*
    Functions: svcs_dpi_hs_recv_regN,svcs_dpi_hs_recv_reg4s,svcs_dpi_hs_recv_logicN
    map reg[N:0] or logic[N:0]  4-state data type,packed array,user-defined vector size, unsigned
    LRM  6.11 
            
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_hs_recv_reg4s  (input int sockfd,input cs_header_t h_trnx,inout reg[] Reg);
   import "DPI-C" function int svcs_dpi_hs_recv_regN   (input int sockfd,input cs_header_t h_trnx,inout reg[] Reg);
   import "DPI-C" function int svcs_dpi_hs_recv_logicN (input int sockfd,input cs_header_t h_trnx,inout logic[] Reg);
   
   //Section: non_integer_type IEEE 754
   
   /* -----\/----- EXCLUDED -----\/-----
  -----/\----- EXCLUDED -----/\----- */
   
   /*
    Functions: svcs_dpi_send_real,svcs_dpi_send_realtime
    map real data type is the same as a C double 8 byte 
    LRM 6.12
           
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been sent : success > 0
    */ 
   import "DPI-C" function int svcs_dpi_send_real      (input int sockfd,input  real Real);
   //import "DPI-C" function int svcs_dpi_send_realtime  (input int sockfd,input  realtime Real);
   import "DPI-C" function int svcs_dpi_send_shortreal (input int sockfd,input  shortreal Real);
   /*
    Functions: svcs_dpi_recv_real,svcs_dpi_recv_realtime
    map real data type is the same as a C double 8 byte  
    LRM 6.12
    
    Parameters:
    sockfd - socket id
    Reg,Logic - data
    
    Returns: 
    number of bytes have been recv : success > 0
    */
   import "DPI-C" function int svcs_dpi_recv_real      (input int sockfd,output real Real);
   //import "DPI-C" function int svcs_dpi_recv_realtime  (input int sockfd,output realtime Real);
   import "DPI-C" function int svcs_dpi_recv_shortreal (input int sockfd,output shortreal Real);
   //////////////////END/////////////////////////////////////////////////////////////////////
     
  

   import "DPI-C" function int svcs_dpi_send_intV   (input int sockid,input int size,input  int Int[]);
   import "DPI-C" function int svcs_dpi_recv_intV   (input int sockid,input int size,output int Int[]);
   
   import "DPI-C" function int svcs_dpi_send_realV  (input int sockid,input int size,input  real Real[]);
   import "DPI-C" function int svcs_dpi_recv_realV  (input int sockid,input int size,output real Real[]);

   import "DPI-C" function int svcs_dpi_send_string (input int sockid,input int size,input  string String);
   import "DPI-C" function int svcs_dpi_recv_string (input int sockid,input int size,inout  string String);

   //4 state  
   import "DPI-C" function int svcs_dpi_send_byte4s (input int sockfd,input reg[7:0] Byte);
   import "DPI-C" function int svcs_dpi_recv_byte4s (input int sockfd,inout reg[7:0] Byte);
   
   import "DPI-C" function int svcs_dpi_send_int4s (input int sockfd,input reg[31:0] Int);
   import "DPI-C" function int svcs_dpi_recv_int4s (input int sockfd,inout reg[31:0] Int);
  //   
   //////////////////////

   
   
 
   import "DPI-C" function real svcs_dpi_hash(input string str);
   
   import "DPI-C" function int svcs_dpi_send_header
     (	
	input int sockid,
	input cs_header_t h
	);
   
   import "DPI-C" function int svcs_dpi_send_data_header
     (
      input int sockid,
      input cs_header_t h,
      input real data_type,
      input int  trnx_payload_sizes[]
      );
   
   import "DPI-C" function int svcs_dpi_recv_header
     (
      input int sockid,
      output cs_header_t h
      );
   
   import "DPI-C" function int svcs_dpi_recv_data_header    
     (
      input int  sockid,
      input      cs_header_t h,
      inout real data_type,
      inout int  trnx_payload_sizes[]
      );

    
   
   import "DPI-C" function int svcs_dpi_hs_send_byte   (input int sockid,input cs_header_t h_trnx,input byte Array[]);
   import "DPI-C" function int svcs_dpi_hs_recv_byte   (input int sockid,input cs_header_t h_trnx,inout byte Array[]);
   
   import "DPI-C" function int svcs_dpi_hs_send_int    (input int sockid,input cs_header_t h_trnx,input int  Array[]);
   import "DPI-C" function int svcs_dpi_hs_recv_int    (input int sockid,input cs_header_t h_trnx,inout int  Array[]);
   
   import "DPI-C" function int svcs_dpi_hs_send_real   (input int sockid,input cs_header_t h_trnx,input real Array[]);
   import "DPI-C" function int svcs_dpi_hs_recv_real   (input int sockid,input cs_header_t h_trnx,inout real Array[]);
   
endpackage : svcs_dpi_pkg


