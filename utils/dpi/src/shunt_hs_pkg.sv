/*
============================================================================
 File        : shunt_hs_pkg.sv
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : SystemVerilog to/from C  Data types mapping by using basic handshake 
               System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT) 
 ============================================================================
*/
package shunt_hs_pkg;

   import shunt_dpi_pkg::*;
  
   /*
    Function: shunt_hs_send_byteA
    send data to TCP/IP socket
    byte Array[][] is input veriloig data
    
    Parameters:
    
    sockid - socket id from init sever/client
    h_trnx - cs_header structure
    h_data - cs_data_header  structure
        
    
    Returns:
    number of elements have been received  : success > 0
    
    */
   function int shunt_hs_send_byteA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input byte Array[][]);
      cs_header_t h_trnx_;
      int 	 Result_;
      string 	 s_me;
      s_me = "\nshunt_hs_send_byteA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
	 Result_=  shunt_dpi_hs_send_byte  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_send_byteA
   
   /*
    Function: shunt_hs_recv_byteA
    fetch data from TCP/IP socket
    byte Array[][] is output veriloig data
    
    Parameters:
    
    sockid - socket id from init sever/client
    h_trnx - cs_header structure
    h_data - cs_data_header  structure
    Array[][] -  Data received
    
    
    Returns:
    number of elements have been received  : success > 0
    
    */
   function int shunt_hs_recv_byteA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,inout byte Array[][]);
      cs_header_t h_trnx_;
      int Result_;
      string s_me;
      s_me = "\nshunt_hs_recv_byteA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 Result_= shunt_dpi_hs_recv_byte(sockid,h_trnx_,Array[i]);
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_recv_byteA
  
     /*
    Function: shunt_hs_send_intA
    send data to TCP/IP socket
    int Array[][] is input veriloig data
    
    Parameters:
    
    sockid - socket id from init sever/client
    h_trnx - cs_header structure
    h_data - cs_data_header  structure
        
    
    Returns:
    number of elements have been received  : success > 0
    
    */   
   function int shunt_hs_send_intA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input int Array[][]);
      cs_header_t h_trnx_;
      int 	 Result_;
      string 	 s_me;
      s_me = "\nshunt_hs_send_intA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
	 Result_=  shunt_dpi_hs_send_int  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_send_intA
  
   /*
    Function: shunt_hs_recv_intA
    fetch data from TCP/IP socket
    int Array[][] is output veriloig data
    
    Parameters:
    
    sockid - socket id from init sever/client
    h_trnx - cs_header structure
    h_data - cs_data_header  structure
    Array[][] -  Data received
    
    
    Returns:
    number of elements have been received  : success > 0
    
    */
   function int shunt_hs_recv_intA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,inout int Array[][]);
      cs_header_t h_trnx_;
      int Result_;
      string s_me;
      s_me = "\nshunt_hs_recv_intA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 Result_= shunt_dpi_hs_recv_int(sockid,h_trnx_,Array[i]);
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_recv_intA
  
  /*
    Function: shunt_hs_send_realA
    send data to TCP/IP socket
    real Array[][] is input veriloig data
    
    Parameters:
    
    sockid - socket id from init sever/client
    h_trnx - cs_header structure
    h_data - cs_data_header  structure
        
    
    Returns:
    number of elements have been received  : success > 0
    
    */   
   function int shunt_hs_send_realA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input real Array[][]);
      cs_header_t h_trnx_;
      int 	 Result_;
      string 	 s_me;
      s_me = "\nshunt_hs_send_realA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
	 Result_=  shunt_dpi_hs_send_real  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_send_realA
   
 /*
    Function: shunt_hs_recv_realA
    fetch data from TCP/IP socket
    real Array[][] is output veriloig data
    
    Parameters:
    
    sockid - socket id from init sever/client
    h_trnx - cs_header structure
    h_data - cs_data_header  structure
    Array[][] -  Data received
    
    
    Returns:
    number of elements have been received  : success > 0
    
    */
   function int shunt_hs_recv_realA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,inout real Array[][]);
      cs_header_t h_trnx_;
      int Result_;
      string s_me;
      s_me = "\nshunt_hs_recv_realA::";
      
      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
	 h_trnx_.trnx_type  = h_trnx.trnx_type;
	 h_trnx_.trnx_id    = h_trnx.trnx_id;
	 h_trnx_.data_type  = h_data.data_type;
	 h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
	 Result_= shunt_dpi_hs_recv_real(sockid,h_trnx_,Array[i]);
	 //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",s_me,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
	 //$display("%s Array[%0d]=%s ",s_me,i,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_recv_realA   

     
   /*
    Function: shunt_dpi_4state_send_byte
    send 4-state verilog "byte" over TCP/IP
    
    Parameters:
    sockid - socket id
    
    Byte  - data to send
    
    Returns:
    number of 4 state variable byte size have been sent : success =1
    
    see (shunt_prim_send_byte)
    */
   
   function int shunt_hs_send_byte4s (input int sockid,input reg[7:0] Byte[]);
      int Result_;
      Result_ = 1; 
      foreach(Byte[i]) if(!shunt_dpi_send_byte4s(sockid,Byte[i])) Result_ =0;
      return Result_;
   endfunction : shunt_hs_send_byte4s
  
   /*
    Function: shunt_dpi_4state_recv_byte
    recv 4-state verilog "byte" over TCP/IP
    
    Parameters:
    sockid - socket id
    Byte  - data to recv
    
    Returns:
    number of 4 state variable byte size have been sent : success =1
    
    see (shunt_prim_recv_byte)
    */
   
   function int shunt_hs_recv_byte4s (input int sockid,inout reg[7:0] Byte[]);
      int Result_;
      Result_ = 1; 
      foreach(Byte[i]) if(!shunt_dpi_recv_byte4s(sockid,Byte[i])) Result_ =0;
      return Result_;
   endfunction : shunt_hs_recv_byte4s
   
   function int shunt_send_realtime  (input int sockfd,input  realtime Real);
      real Real_; 
      int  Result_;
      Real_ = Real;
      Result_ = shunt_dpi_send_real(sockfd,Real_);
      return  Result_;
   endfunction : shunt_send_realtime
   
   function int shunt_recv_realtime  (input int sockfd,output realtime Real);
      real Real_; 
      int  Result_;
      Result_ = shunt_dpi_recv_real(sockfd,Real_);
      Real = Real_;
      return  Result_;
   endfunction : shunt_recv_realtime
   
  
endpackage : shunt_hs_pkg
   
   
  
