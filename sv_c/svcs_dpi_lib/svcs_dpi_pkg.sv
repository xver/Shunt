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

    
   
   import "DPI-C" function int svcs_dpi_hs_send_byte  (input int sockid,input cs_header_t h_trnx,input byte Array[]);
   import "DPI-C" function int svcs_dpi_hs_recv_byte  (input int sockid,input cs_header_t h_trnx,inout byte Array[]);
   
   import "DPI-C" function int svcs_dpi_hs_send_int   (input int sockid,input cs_header_t h_trnx,input int  Array[]);
   import "DPI-C" function int svcs_dpi_hs_recv_int   (input int sockid,input cs_header_t h_trnx,inout int  Array[]);
   
   import "DPI-C" function int svcs_dpi_hs_send_real  (input int sockid,input cs_header_t h_trnx,input real Array[]);
   import "DPI-C" function int svcs_dpi_hs_recv_real  (input int sockid,input cs_header_t h_trnx,inout real Array[]);
   
   function int svcs_hs_send_byteA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input byte Array[][]);
      cs_header_t h_trnx_;
      int 	 Result_;
      string 	 s_me;
      s_me = "\nsvcs_hs_send_byteA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
	 Result_=  svcs_dpi_hs_send_byte  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : svcs_hs_send_byteA
   
   function int svcs_hs_recv_byteA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,inout byte Array[][]);
      cs_header_t h_trnx_;
      int Result_;
      string 	 s_me;
      s_me = "\nsvcs_hs_recv_byteA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 Result_= svcs_dpi_hs_recv_byte(sockid,h_trnx_,Array[i]);
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
      end
      return (Result_);
   endfunction : svcs_hs_recv_byteA

   function int svcs_hs_send_intA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input int Array[][]);
      cs_header_t h_trnx_;
      int 	 Result_;
      string 	 s_me;
      s_me = "\nsvcs_hs_send_intA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
	 Result_=  svcs_dpi_hs_send_int  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : svcs_hs_send_intA
   
   function int svcs_hs_recv_intA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,inout int Array[][]);
      cs_header_t h_trnx_;
      int Result_;
      string 	 s_me;
      s_me = "\nsvcs_hs_recv_intA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 Result_= svcs_dpi_hs_recv_int(sockid,h_trnx_,Array[i]);
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
      end
      return (Result_);
   endfunction : svcs_hs_recv_intA
 
   function int svcs_hs_send_realA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input real Array[][]);
      cs_header_t h_trnx_;
      int 	 Result_;
      string 	 s_me;
      s_me = "\nsvcs_hs_send_realA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
	 Result_=  svcs_dpi_hs_send_real  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : svcs_hs_send_realA
   
   function int svcs_hs_recv_realA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,inout real Array[][]);
      cs_header_t h_trnx_;
      int Result_;
      string 	 s_me;
      s_me = "\nsvcs_hs_recv_realA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 Result_= svcs_dpi_hs_recv_real(sockid,h_trnx_,Array[i]);
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
      end
      return (Result_);
   endfunction : svcs_hs_recv_realA
  //  
endpackage : svcs_dpi_pkg
   
  
