/*
============================================================================
 File        : svtest_hs_client.sv
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description :  hs function svcs dpi bridge test 

               System Verilog client server handshake (SVCS) library
 ============================================================================
*/
`include "../../includes/cs_common.svh"

module automatic svtest_hs_client;
 
   import svcs_dpi_pkg::*;
   import svcs_hs_pkg::*;
   
   string String;
   int 	 Socket; 
   cs_header_t      h_trnx;
   cs_data_header_t h_data;
   
   initial
     begin

	int Result;
		
	Socket=0;
	Result=0;
	
        #1000ns;
	
        //
	//String.toupper();	
	$display("svtest_hs_client: START");
	Socket = init_client(`MY_PORT, `MY_HOST);
	$display("svtest_hs_client: socket=%0d",Socket);
	
	//////////////////////////
	int_loopback_test(Socket);
	int_loopback_test(Socket);
	//////////////////////////
	short_loopback_test(Socket);
	short_loopback_test(Socket);
	//////////////////////////
        long_loopback_test(Socket);
	long_loopback_test(Socket);
	///////////////////////////
	byte_loopback_test(Socket);
	byte_loopback_test(Socket);
	///////////////////////////
	bit_loopback_test(Socket);
	///////////////////////////
	integer_loopback_test(Socket);
	integer_loopback_test(Socket);
	///////////////////////////
	reg_loopback_test(Socket);
	logic_loopback_test(Socket);
	///////////////////////////
	real_loopback_test(Socket);
	real_loopback_test(Socket);
	///////////////////////////
	shortreal_loopback_test(Socket);
	shortreal_loopback_test(Socket);
	
	// *****************END**********************************
	
	/* -----\/----- EXCLUDED -----\/-----
	byteA_loopback_test(Socket);
	byteA_loopback_test(Socket);
	//////////////////////////
	intA_loopback_test(Socket);
	intA_loopback_test(Socket);
	//////////////////////////
	realA_loopback_test(Socket);
	realA_loopback_test(Socket);
	//////////////////////////
	byte4sV_loopback_test(Socket);
	reg4sV_loopback_test(Socket);
	//////////////////////////
	 -----/\----- EXCLUDED -----/\----- */
	$display("svtest_hs_client: END");
	
     end
 
   
   
   function int init_client(int portno,string hostname);
      int   socket_id;
      socket_id=0;
      socket_id = svcs_dpi_client_init(portno,hostname);
      return socket_id;
   endfunction : init_client
   
   //////////
   function void byte_loopback_test(int socket_id);
      byte   Byte[];
      string Test_name;
   
      Test_name = "client byte_loopback_test recv";
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Byte   = new[h_trnx.n_payloads];
      if (svcs_dpi_hs_recv_byte (socket_id,h_trnx,Byte)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "client byte_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_byte(socket_id,h_trnx,Byte)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : byte_loopback_test

   function void integer_loopback_test(int socket_id);
      integer   Integer[];
      string Test_name;
   
      Test_name = "client integer_loopback_test recv";
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Integer   = new[h_trnx.n_payloads];
      if (svcs_dpi_hs_recv_integer (socket_id,h_trnx,Integer)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "client integer_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_integer(socket_id,h_trnx,Integer)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : integer_loopback_test


   
   function void byte4sV_loopback_test(int socket_id);
      reg[7:0]   Byte4sV[];
      string Test_name;
   
      Test_name = "client byte4sV_loopback_test recv";
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Byte4sV   = new[h_trnx.n_payloads];
      if (svcs_hs_recv_byte4s (socket_id,Byte4sV)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "client byte4sV_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_hs_send_byte4s(socket_id,Byte4sV)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : byte4sV_loopback_test
   
   
   
   function void int_loopback_test(int socket_id);
      int   Int[];
      string Test_name;
      //recv
      Test_name = "client int_loopback_test recv";
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Int   = new[h_trnx.n_payloads];
      if (svcs_dpi_hs_recv_int (socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
      //send       
      Test_name = "client int_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_int(socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : int_loopback_test

   function void short_loopback_test(int socket_id);
      shortint   Int[];
      string Test_name;
      //recv
      Test_name = "client short_loopback_test recv";
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Int   = new[h_trnx.n_payloads];
      if (svcs_dpi_hs_recv_short (socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
      //send       
      Test_name = "client short_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_short(socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : short_loopback_test

   function void long_loopback_test(int socket_id);
      longint   Int[];
      string Test_name;
      //recv
      Test_name = "client long_loopback_test recv";
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Int   = new[h_trnx.n_payloads];
      if (svcs_dpi_hs_recv_long (socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
      //send       
      Test_name = "client long_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_long(socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : long_loopback_test 
   
   function void real_loopback_test(int socket_id);
      real  Real[];
      string Test_name;
      
      Test_name = "client real_loopback_test recv";
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Real   = new[h_trnx.n_payloads];
      if (svcs_dpi_hs_recv_real (socket_id,h_trnx,Real)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "client real_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_real(socket_id,h_trnx,Real)<= 0) $display("%s TEST FAIL",Test_name); 
   endfunction : real_loopback_test




   function void shortreal_loopback_test(int socket_id);
      shortreal  Shortreal[];
      string Test_name;
      
      Test_name = "client shortreal_loopback_test recv";
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Shortreal   = new[h_trnx.n_payloads];
      if (svcs_dpi_hs_recv_shortreal (socket_id,h_trnx,Shortreal)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "client shortreal_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_shortreal(socket_id,h_trnx,Shortreal)<= 0) $display("%s TEST FAIL",Test_name); 
   endfunction : shortreal_loopback_test
   

   
   function void   byteA_loopback_test(int socket_id);
      byte   Byte[][];
      string Test_name;
      int    trnx_payload_sizes[];
      real   data_type;
      
      Test_name = "client byteA_loopback_test recv";
      
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s recv_header TEST FAIL",Test_name);
      //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",Test_name,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
      //recv data header 
      trnx_payload_sizes = new[h_trnx.n_payloads];
      h_data.trnx_payload_sizes = new[h_trnx.n_payloads];
      if(svcs_dpi_recv_data_header(socket_id,h_trnx,data_type,trnx_payload_sizes)<=0) $display("%s recv_data_header TEST FAIL",Test_name);
      h_data.data_type = data_type;
      for(int i=0;i<h_trnx.n_payloads;i++) h_data.trnx_payload_sizes[i]= trnx_payload_sizes[i];
      //recv data
      Byte   = new[h_trnx.n_payloads]; 
      foreach(Byte[i]) Byte[i] = new[trnx_payload_sizes[i]];
      if(svcs_hs_recv_byteA  (socket_id,h_trnx,h_data,Byte)<=0) $display("%s recv_byteA TEST FAIL",Test_name);
      //foreach(Byte[i]) foreach(Byte[j]) $display("\n %s Byte[%0d][%0d]=%c",Test_name,i,j,Byte[i][j]);
      
      //send
      //send trnx header
      if(svcs_dpi_send_header(socket_id,h_trnx)<= 0)  $display("%s send_header TEST FAIL",Test_name);
      if(svcs_dpi_send_data_header(socket_id,h_trnx,h_data.data_type,h_data.trnx_payload_sizes)<= 0)$display("%s send_data_header TEST FAIL",Test_name); 
      //send data
      if (svcs_hs_send_byteA(socket_id,h_trnx,h_data,Byte)<=0)$display("%s send_byteA TEST FAIL",Test_name); 
   
   endfunction :byteA_loopback_test
   
   function void   intA_loopback_test(int socket_id);
      int    Int[][];
      string Test_name;
      int    trnx_payload_sizes[];
      real   data_type;
      
      Test_name = "client intA_loopback_test recv";
      
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s recv_header TEST FAIL",Test_name);
      //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",Test_name,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
      //recv data header 
      trnx_payload_sizes = new[h_trnx.n_payloads];
      h_data.trnx_payload_sizes = new[h_trnx.n_payloads];
      if(svcs_dpi_recv_data_header(socket_id,h_trnx,data_type,trnx_payload_sizes)<=0) $display("%s recv_data_header TEST FAIL",Test_name);
      h_data.data_type = data_type;
      for(int i=0;i<h_trnx.n_payloads;i++) h_data.trnx_payload_sizes[i]= trnx_payload_sizes[i];
      //recv data
      Int    = new[h_trnx.n_payloads]; 
      foreach(Int[i]) Int[i] = new[trnx_payload_sizes[i]];
      if(svcs_hs_recv_intA  (socket_id,h_trnx,h_data,Int)<=0) $display("%s recv_intA TEST FAIL",Test_name);
      //foreach(Int[i]) foreach(Int[j]) $display("\n %s Int[%0d][%0d]=%d",Test_name,i,j,Int[i][j]);
      
      //send
      //send trnx header
      if(svcs_dpi_send_header(socket_id,h_trnx)<= 0)  $display("%s send_header TEST FAIL",Test_name);
      if(svcs_dpi_send_data_header(socket_id,h_trnx,h_data.data_type,h_data.trnx_payload_sizes)<= 0)$display("%s send_data_header TEST FAIL",Test_name); 
      //send data
      if (svcs_hs_send_intA(socket_id,h_trnx,h_data,Int)<=0)$display("%s send_intA TEST FAIL",Test_name); 
   endfunction :intA_loopback_test

  
   function void   realA_loopback_test(int socket_id);
      real   Real[][];
      string Test_name;
      int    trnx_payload_sizes[];
      real   data_type;
      
      Test_name = "client realA_loopback_test recv";
      
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s recv_header TEST FAIL",Test_name);
      //$display("\n%s h_trnx.trnx_type=%0f,h_trnx.trnx_id=%0f;h_trnx.data_type=%0f;h_trnx.n_payloads=%0d",Test_name,h_trnx.trnx_type,h_trnx.trnx_id,h_trnx.data_type,h_trnx.n_payloads);
      //recv data header 
      trnx_payload_sizes = new[h_trnx.n_payloads];
      h_data.trnx_payload_sizes = new[h_trnx.n_payloads];
      if(svcs_dpi_recv_data_header(socket_id,h_trnx,data_type,trnx_payload_sizes)<=0) $display("%s recv_data_header TEST FAIL",Test_name);
      h_data.data_type = data_type;
      for(int i=0;i<h_trnx.n_payloads;i++) h_data.trnx_payload_sizes[i]= trnx_payload_sizes[i];
      //recv data
      Real   = new[h_trnx.n_payloads]; 
      foreach(Real[i]) Real[i] = new[trnx_payload_sizes[i]];
      if(svcs_hs_recv_realA  (socket_id,h_trnx,h_data,Real)<=0) $display("%s recv_realA TEST FAIL",Test_name);
      //foreach(Real[i]) foreach(Real[j]) $display("\n %s Real[%0d][%0d]=%f",Test_name,i,j,Real[i][j]);
      
      //send
      //send trnx header
      if(svcs_dpi_send_header(socket_id,h_trnx)<= 0)  $display("%s send_header TEST FAIL",Test_name);
      if(svcs_dpi_send_data_header(socket_id,h_trnx,h_data.data_type,h_data.trnx_payload_sizes)<= 0)$display("%s send_data_header TEST FAIL",Test_name); 
      //send data
      if (svcs_hs_send_realA(socket_id,h_trnx,h_data,Real)<=0)$display("%s send_realA TEST FAIL",Test_name); 
   
   endfunction :realA_loopback_test
   ////////
   
   function void reg_loopback_test(int socket_id);
      reg [1024:0] Reg;
      string 	   Test_name;
      
      Test_name = "client reg_loopback_test recv";
      //recv     
      Reg = 'hz;
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_recv_regN(socket_id,h_trnx,Reg)<= 0) $display("%s TEST FAIL",Test_name);
      //$display("\n %s Reg=%h(%h)",Test_name, Reg,Reg[132:0]);
      //send
      //Test_name = "client reg_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_regN(socket_id,h_trnx,Reg)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : reg_loopback_test

    function void logic_loopback_test(int socket_id);
      logic [1024:0] Logic;
      string 	   Test_name;
      
      Test_name = "client logic_loopback_test recv";
      //recv     
      Logic = 'hz;
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_recv_logicN(socket_id,h_trnx,Logic)<= 0) $display("%s TEST FAIL",Test_name);
      //$display("\n %s Logic=%h(%h)",Test_name, Logic,Logic[132:0]);
      //send
      //Test_name = "client logic_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_logicN(socket_id,h_trnx,Logic)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : logic_loopback_test
   
   function void bit_loopback_test(int socket_id);
      bit [1024:0] Bit;
      string 	   Test_name;
      
      Test_name = "client bit_loopback_test recv";
      //recv     
      Bit = 'hz;
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_recv_bitN(socket_id,h_trnx,Bit)<= 0) $display("%s TEST FAIL",Test_name);
      //$display("\n %s Bit=%h(%h)",Test_name, Bit,Bit[132:0]);
      //send
      //Test_name = "client bit_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_bitN(socket_id,h_trnx,Bit)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : bit_loopback_test

endmodule : svtest_hs_client