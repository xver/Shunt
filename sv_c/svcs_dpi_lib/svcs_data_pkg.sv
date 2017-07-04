/*
============================================================================
 File        : svcs_data_pkg.sv
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : file contains Data types mapping between SystemVerilog and C transfer methods
 ============================================================================
*/
package svcs_data_pkg;
import svcs_dpi_pkg::*;

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
      string s_me;
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
      string s_me;
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
      string s_me;
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
   
 
endpackage : svcs_data_pkg
   
  
