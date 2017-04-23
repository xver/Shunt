/*
============================================================================
 File        : svtest_prim_client.sv
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description :  prim function svcs dpi bridge test 

               System Verilog client server handshake (SVCS) library
 ============================================================================
*/
`include "../../includes/cs_common.svh"

module svtest_prim_client;
 
   import svcs_dpi_pkg::*;
   
   
   
   initial
     begin
	int Socket;
	int Result;
		
	Socket=0;
	Result=0;
		
	$display("svtest_prim_client: START");
	Socket = init_client(`MY_PORT, `MY_HOST);
	$display("svtest_prim_client: socket=%0d",Socket); 
	int_loopback_test(Socket);
	real_loopback_test(Socket);
	$display("svtest_prim_client: END");
     end
   
   
   function int init_client(int portno,string hostname);
      int   socket_id;
      socket_id=0;
      socket_id = svcs_dpi_client_init(portno,hostname);
      return socket_id;
   endfunction : init_client
  
   function void int_loopback_test(int socket_id);
      int   Int;
      string Test_name;
      Test_name = "client int_loopback_test recv";
      if (!svcs_dpi_recv_int(socket_id,Int)) $display("%s TEST FAIL",Test_name);
      Test_name = "client int_loopback_test send";
      if (!svcs_dpi_send_int(socket_id,Int)) $display("%s TEST FAIL",Test_name);
   endfunction : int_loopback_test
   
   function void real_loopback_test(int socket_id);
      real   Real;
      string Test_name;
      Test_name = "client real_loopback_test recv";
      if (!svcs_dpi_recv_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
      Test_name = "client real_loopback_test send";
      if (!svcs_dpi_send_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
   endfunction : real_loopback_test
    
endmodule : svtest_prim_client