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
	byte_loopback_test(Socket);
	/* -----\/----- EXCLUDED -----\/-----
	 int_loopback_test(Socket);
	 real_loopback_test(Socket);
	 intV_loopback_test(Socket);
	 realV_loopback_test(Socket);
	 string_loopback_test(Socket);
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
   
   function void intV_loopback_test(int socket_id);
      int    IntV[`V_SIZE];
      string Test_name;
      
      foreach(IntV[i]) IntV[i] = 200+(i+1);
      Test_name = "client intV_loopback_test recv";
      if (!svcs_dpi_recv_intV(socket_id,`V_SIZE,IntV)) $display("%s TEST FAIL",Test_name);
      Test_name = "client intV_loopback_test send";
      if (!svcs_dpi_send_intV(socket_id,`V_SIZE,IntV)) $display("%s TEST FAIL",Test_name);
   endfunction // intV_loopback_test
   
   function void real_loopback_test(int socket_id);
      real   Real;
      string Test_name;
      
      Test_name = "client real_loopback_test recv";
      if (!svcs_dpi_recv_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
      Test_name = "client real_loopback_test send";
      if (!svcs_dpi_send_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
   endfunction : real_loopback_test
   
   function void realV_loopback_test(int socket_id);
      real   RealV[`V_SIZE];
      string Test_name;
      
      foreach(RealV[i]) RealV[i] = 200+(i+1);
      Test_name = "client realV_loopback_test recv";
      if (!svcs_dpi_recv_realV(socket_id,`V_SIZE,RealV)) $display("%s TEST FAIL",Test_name);
      Test_name = "client realV_loopback_test send";
      if (!svcs_dpi_send_realV(socket_id,`V_SIZE,RealV)) $display("%s TEST FAIL",Test_name);
   endfunction : realV_loopback_test
   
   function void string_loopback_test(int socket_id);
    
      string Test_name;
      int    size;
      int    Result_;
      
      String = `STRING_MESSAGE1;
      Test_name = "SV client string_loopback_test recv";
      
      
       $display("SV before client String = %s",String);	
       if (svcs_dpi_recv_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
       Result_ = svcs_dpi_recv_string(socket_id,size,String);
       $display("SV after client String = %s",String);
       Test_name = "client string_loopback_test send";
       if (svcs_dpi_send_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);

      
   endfunction : string_loopback_test
   
   
endmodule : svtest_hs_client