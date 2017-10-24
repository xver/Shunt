/*
============================================================================
 File        : Target.sv
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description :  hs function svcs dpi bridge test 

               System Verilog target server handshake (SVCS) library
 ============================================================================
*/
`include "../../includes/cs_common.svh"

module automatic Target;
   
   import shunt_dpi_pkg::*;
   import shunt_hs_pkg::*;
   
   string String;
   int 	  Socket; 
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
	$display("Target: START");
	Socket = init_target(`MY_PORT, `MY_HOST);
	$display("Target: socket=%0d",Socket);
	
	int_loopback_test(Socket);
	int_loopback_test(Socket);
	
	short_loopback_test(Socket);
	short_loopback_test(Socket);
	
        long_loopback_test(Socket);
	long_loopback_test(Socket);
	
	byte_loopback_test(Socket);
	byte_loopback_test(Socket);
	
	bit_loopback_test(Socket);
	
	integer_loopback_test(Socket);
	integer_loopback_test(Socket);
	
	reg_loopback_test(Socket);
	logic_loopback_test(Socket);
	
	real_loopback_test(Socket);
	real_loopback_test(Socket);
	
	shortreal_loopback_test(Socket);
	shortreal_loopback_test(Socket);
	
	string_loopback_test(Socket);
	// *****************END**********************************
	$display("Target: END");
	
     end
   
   
   
   function int init_target(int portno,string hostname);
      int   socket_id;
      socket_id=0;
      socket_id = shunt_dpi_target_init(portno,hostname);
      return socket_id;
   endfunction : init_target
   
   function void string_loopback_test(int socket_id);
      begin
	 int success;
	 int i;
         string String;
	 string Test_name = "target tring_loopback_test recv";
	 
	 String = `STRING_MESSAGE1;
	 success =1;
	 
	 //recv
	 if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
	 if (shunt_dpi_hs_recv_string(socket_id,h_trnx,String)<= 0)$display("%s TEST FAIL",Test_name);
	 //send
	 if (shunt_dpi_send_header(socket_id,h_trnx)<= 0)  $display("%s TEST FAIL",Test_name);
	 if (shunt_dpi_hs_send_string  (socket_id,h_trnx,String)<= 0) $display("%s TEST FAIL",Test_name);
      end
   endfunction : string_loopback_test
   
   function void byte_loopback_test(int socket_id);
      byte 	Byte[];
      string 	Test_name;
      
      Test_name = "target byte_loopback_test recv";
      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Byte 	= new[h_trnx.n_payloads];
      if (shunt_dpi_hs_recv_byte (socket_id,h_trnx,Byte)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "target byte_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_byte(socket_id,h_trnx,Byte)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : byte_loopback_test
   
   function void integer_loopback_test(int socket_id);
      integer   Integer[];
      string 	Test_name;
      
      Test_name = "target integer_loopback_test recv";
      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Integer   = new[h_trnx.n_payloads];
      if (shunt_dpi_hs_recv_integer (socket_id,h_trnx,Integer)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "target integer_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_integer(socket_id,h_trnx,Integer)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : integer_loopback_test
   
   function void int_loopback_test(int socket_id);
      int 	Int[];
      string 	Test_name;
      //recv
      Test_name = "target int_loopback_test recv";
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Int 	= new[h_trnx.n_payloads];
      if (shunt_dpi_hs_recv_int (socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
      //send       
      Test_name = "target int_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_int(socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : int_loopback_test
   
   function void short_loopback_test(int socket_id);
      shortint 	Int[];
      string 	Test_name;
      //recv
      Test_name = "target short_loopback_test recv";
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Int 	= new[h_trnx.n_payloads];
      if (shunt_dpi_hs_recv_short (socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
      //send       
      Test_name = "target short_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_short(socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : short_loopback_test
   
   function void long_loopback_test(int socket_id);
      longint   Int[];
      string 	Test_name;
      //recv
      Test_name = "target long_loopback_test recv";
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Int 	= new[h_trnx.n_payloads];
      if (shunt_dpi_hs_recv_long (socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
      //send       
      Test_name = "target long_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_long(socket_id,h_trnx,Int)<= 0) $display("%s TEST FAIL",Test_name);
   endfunction : long_loopback_test 
   
   function void real_loopback_test(int socket_id);
      real 	Real[];
      string 	Test_name;
      
      Test_name = "target real_loopback_test recv";
      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Real 	= new[h_trnx.n_payloads];
      if (shunt_dpi_hs_recv_real (socket_id,h_trnx,Real)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "target real_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_real(socket_id,h_trnx,Real)<= 0) $display("%s TEST FAIL",Test_name); 
   endfunction : real_loopback_test
   
   
   
   
   function void shortreal_loopback_test(int socket_id);
      shortreal Shortreal[];
      string 	Test_name;
      
      Test_name = "target shortreal_loopback_test recv";
      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      Shortreal = new[h_trnx.n_payloads];
      if (shunt_dpi_hs_recv_shortreal (socket_id,h_trnx,Shortreal)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "target shortreal_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_shortreal(socket_id,h_trnx,Shortreal)<= 0) $display("%s TEST FAIL",Test_name); 
   endfunction : shortreal_loopback_test
   
   
   
   function void   byteA_loopback_test(int socket_id);
      byte 	Byte[][];
      string 	Test_name;
      int 	trnx_payload_sizes[];
      real 	data_type;
      
      Test_name = "target byteA_loopback_test recv";
      
      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s recv_header TEST FAIL",Test_name);
      //recv data header 
      trnx_payload_sizes = new[h_trnx.n_payloads];
      h_data.trnx_payload_sizes = new[h_trnx.n_payloads];
      if(shunt_dpi_recv_data_header(socket_id,h_trnx,data_type,trnx_payload_sizes)<=0) $display("%s recv_data_header TEST FAIL",Test_name);
      h_data.data_type = data_type;
      for(int i=0;i<h_trnx.n_payloads;i++) h_data.trnx_payload_sizes[i]= trnx_payload_sizes[i];
      //recv data
      Byte 	= new[h_trnx.n_payloads]; 
      foreach(Byte[i]) Byte[i] = new[trnx_payload_sizes[i]];
      if(shunt_hs_recv_byteA  (socket_id,h_trnx,h_data,Byte)<=0) $display("%s recv_byteA TEST FAIL",Test_name);
      
      //send
      //send trnx header
      if(shunt_dpi_send_header(socket_id,h_trnx)<= 0)  $display("%s send_header TEST FAIL",Test_name);
      if(shunt_dpi_send_data_header(socket_id,h_trnx,h_data.data_type,h_data.trnx_payload_sizes)<= 0)$display("%s send_data_header TEST FAIL",Test_name); 
      //send data
      if (shunt_hs_send_byteA(socket_id,h_trnx,h_data,Byte)<=0)$display("%s send_byteA TEST FAIL",Test_name); 
      
   endfunction :byteA_loopback_test
   
   function void   intA_loopback_test(int socket_id);
      int 	Int[][];
      string 	Test_name;
      int 	trnx_payload_sizes[];
      real 	data_type;
      
      Test_name = "target intA_loopback_test recv";
      
      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s recv_header TEST FAIL",Test_name);
      
      //recv data header 
      trnx_payload_sizes = new[h_trnx.n_payloads];
      h_data.trnx_payload_sizes = new[h_trnx.n_payloads];
      if(shunt_dpi_recv_data_header(socket_id,h_trnx,data_type,trnx_payload_sizes)<=0) $display("%s recv_data_header TEST FAIL",Test_name);
      h_data.data_type = data_type;
      for(int i=0;i<h_trnx.n_payloads;i++) h_data.trnx_payload_sizes[i]= trnx_payload_sizes[i];
      //recv data
      Int 	= new[h_trnx.n_payloads]; 
      foreach(Int[i]) Int[i] = new[trnx_payload_sizes[i]];
      if(shunt_hs_recv_intA  (socket_id,h_trnx,h_data,Int)<=0) $display("%s recv_intA TEST FAIL",Test_name);
      
      //send
      //send trnx header
      if(shunt_dpi_send_header(socket_id,h_trnx)<= 0)  $display("%s send_header TEST FAIL",Test_name);
      if(shunt_dpi_send_data_header(socket_id,h_trnx,h_data.data_type,h_data.trnx_payload_sizes)<= 0)$display("%s send_data_header TEST FAIL",Test_name); 
      //send data
      if (shunt_hs_send_intA(socket_id,h_trnx,h_data,Int)<=0)$display("%s send_intA TEST FAIL",Test_name); 
   endfunction :intA_loopback_test
   
   
   function void   realA_loopback_test(int socket_id);
      real 	Real[][];
      string 	Test_name;
      int 	trnx_payload_sizes[];
      real 	data_type;
      
      Test_name = "target realA_loopback_test recv";
      
      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s recv_header TEST FAIL",Test_name);
      
      //recv data header 
      trnx_payload_sizes = new[h_trnx.n_payloads];
      h_data.trnx_payload_sizes = new[h_trnx.n_payloads];
      if(shunt_dpi_recv_data_header(socket_id,h_trnx,data_type,trnx_payload_sizes)<=0) $display("%s recv_data_header TEST FAIL",Test_name);
      h_data.data_type = data_type;
      for(int i=0;i<h_trnx.n_payloads;i++) h_data.trnx_payload_sizes[i]= trnx_payload_sizes[i];
      //recv data
      Real 	= new[h_trnx.n_payloads]; 
      foreach(Real[i]) Real[i] = new[trnx_payload_sizes[i]];
      if(shunt_hs_recv_realA  (socket_id,h_trnx,h_data,Real)<=0) $display("%s recv_realA TEST FAIL",Test_name);
      
      //send
      //send trnx header
      if(shunt_dpi_send_header(socket_id,h_trnx)<= 0)  $display("%s send_header TEST FAIL",Test_name);
      if(shunt_dpi_send_data_header(socket_id,h_trnx,h_data.data_type,h_data.trnx_payload_sizes)<= 0)$display("%s send_data_header TEST FAIL",Test_name); 
      //send data
      if (shunt_hs_send_realA(socket_id,h_trnx,h_data,Real)<=0)$display("%s send_realA TEST FAIL",Test_name); 
      
   endfunction :realA_loopback_test
   
   function void reg_loopback_test(int socket_id);
      reg [1024:0] Reg;
      string 	   Test_name;
      
      Test_name = "target reg_loopback_test recv";
      //recv     
      Reg 	   = 'hz;
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_recv_regN(socket_id,h_trnx,Reg)<= 0) $display("%s TEST FAIL",Test_name);
      
      //send
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_regN(socket_id,h_trnx,Reg)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : reg_loopback_test
   
   function void logic_loopback_test(int socket_id);
      logic [1024:0] Logic;
      string 	     Test_name;
      
      Test_name = "target logic_loopback_test recv";
      //recv     
      Logic 	     = 'hz;
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_recv_logicN(socket_id,h_trnx,Logic)<= 0) $display("%s TEST FAIL",Test_name);
      
      //send
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_logicN(socket_id,h_trnx,Logic)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : logic_loopback_test
   
   function void bit_loopback_test(int socket_id);
      bit [1024:0]   Bit;
      string 	     Test_name;
      
      Test_name = "target bit_loopback_test recv";
      //recv     
      Bit 	     = 'hz;
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_recv_bitN(socket_id,h_trnx,Bit)<= 0) $display("%s TEST FAIL",Test_name);
      
      //send
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_bitN(socket_id,h_trnx,Bit)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : bit_loopback_test
   
endmodule : Target

