/*
============================================================================
 File        : shunt_hs_pkg.sv
 Version     : 1.0.0
 Copyright (c) 2016-2023 IC Verimeter. All rights reserved.
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


    Parameters:

    sockid - socket id from init sever/client
    h_trnx - <cs_header_t> structure
    h_data - <cs_data_header_t>  structure
    Array  - data

    Returns:
    number of elements have been received  : success > 0

    */
   function int shunt_hs_send_byteA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input byte Array[][]);
      cs_header_t h_trnx_;
      int    Result_;
      string     s_me;
      s_me = "\nshunt_hs_send_byteA::";

      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
     h_trnx_.trnx_type  = h_trnx.trnx_type;
     h_trnx_.trnx_id    = h_trnx.trnx_id;
     h_trnx_.data_type  = h_data.data_type;
     h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
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
    h_trnx - <cs_header_t> structure
    h_data - <cs_data_header_t>  structure
    Array -  Data

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
      end
      return (Result_);
   endfunction : shunt_hs_recv_byteA

   /*
    Function: shunt_hs_send_intA
    send data to TCP/IP socket

    Parameters:

    sockid - socket id from init sever/client
    h_trnx - <cs_header_t> structure
    h_data - <cs_data_header_t>  structure
    Array  - data

    Returns:
    number of elements have been received  : success > 0

    */
   function int shunt_hs_send_intA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input int Array[][]);
      cs_header_t h_trnx_;
      int    Result_;
      string     s_me;
      s_me = "\nshunt_hs_send_intA::";

      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
     h_trnx_.trnx_type  = h_trnx.trnx_type;
     h_trnx_.trnx_id    = h_trnx.trnx_id;
     h_trnx_.data_type  = h_data.data_type;
     h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
     Result_=  shunt_dpi_hs_send_int  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_send_intA

   /*
    Function: shunt_hs_recv_intA
    fetch data from TCP/IP socket


    Parameters:

    sockid - socket id from init sever/client
    h_trnx - <cs_header_t> structure
    h_data - <cs_data_header_t>  structure
    Array -  data


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
      end
      return (Result_);
   endfunction : shunt_hs_recv_intA

   /*
    Function: shunt_hs_send_realA
    send data to TCP/IP socket


    Parameters:

    sockid - socket id from init sever/client
    h_trnx - <cs_header_t> structure
    h_data - <cs_data_header_t>  structure
    Array  - data

    Returns:
    number of elements have been received  : success > 0

    */
   function int shunt_hs_send_realA  (input int sockid,input cs_header_t h_trnx,input cs_data_header_t h_data,input real Array[][]);
      cs_header_t h_trnx_;
      int    Result_;
      string     s_me;
      s_me = "\nshunt_hs_send_realA::";

      Result_ =0;
      foreach(h_data.trnx_payload_sizes[i])  begin
     h_trnx_.trnx_type  = h_trnx.trnx_type;
     h_trnx_.trnx_id    = h_trnx.trnx_id;
     h_trnx_.data_type  = h_data.data_type;
     h_trnx_.n_payloads = h_data.trnx_payload_sizes[i];
     Result_=  shunt_dpi_hs_send_real  (sockid,h_trnx_,Array[i]);
      end
      return (Result_);
   endfunction : shunt_hs_send_realA

   /*
    Function: shunt_hs_recv_realA
    fetch data from TCP/IP socket

    Parameters:

    sockid - socket id from init sever/client
    h_trnx - <cs_header_t> structure
    h_data - <cs_data_header_t>  structure
    Array  - data


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
      end
      return (Result_);
   endfunction : shunt_hs_recv_realA


   /*
    Function: shunt_send_realtime
    send verilog realtime

    Parameters:
    sockid - socket id
    Real  - data

    Returns:
    number of bytes have been sent : success > 0

    See Also:
    <shunt_dpi_send_real>
    */

   function int shunt_send_realtime  (input int sockfd,input  realtime Real);
      real Real_;
      int  Result_;
      Real_ = Real;
      Result_ = shunt_dpi_send_real(sockfd,Real_);
      return  Result_;
   endfunction : shunt_send_realtime

   /*
    Function: shunt_recv_realtime
    recv verilog realtime

    Parameters:
    sockid - socket id
    Real  - data

    Returns:
    number of bytes have been receved : success > 0

    See Also:
    <shunt_dpi_recv_real>
    */
   function int shunt_recv_realtime  (input int sockfd,output realtime Real);
      real Real_;
      int  Result_;
      Result_ = shunt_dpi_recv_real(sockfd,Real_);
      Real = Real_;
      return  Result_;
   endfunction : shunt_recv_realtime

endpackage : shunt_hs_pkg



