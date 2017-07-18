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
   
   import "DPI-C" function int svcs_dpi_server_init (input int portno);
   import "DPI-C" function int svcs_dpi_client_init (input int portno,input string hostname);
   
   import "DPI-C" function int svcs_dpi_send_byte   (input int sockfd,input  byte Byte);
   import "DPI-C" function int svcs_dpi_recv_byte   (input int sockfd,output byte Byte);
   
   import "DPI-C" function int svcs_dpi_send_int    (input int sockfd,input  int Int);
   import "DPI-C" function int svcs_dpi_recv_int    (input int sockfd,output int Int);
   
   import "DPI-C" function int svcs_dpi_send_real   (input int sockfd,input  real Real);
   import "DPI-C" function int svcs_dpi_recv_real   (input int sockfd,output real Real);

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
   
   import "DPI-C" function int svcs_dpi_hs_send_reg4s  (input int sockfd,input cs_header_t h_trnx,input reg[] Reg);
   import "DPI-C" function int svcs_dpi_hs_recv_reg4s  (input int sockfd,input cs_header_t h_trnx,inout reg[] Reg);
   
   endpackage : svcs_dpi_pkg


