/*
============================================================================
 File        : svtest_prim_server.sv
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

module svtest_prim_server;
   
   import svcs_dpi_pkg::*;
      
   initial
     begin
	int Socket;
	int Pass;
	string Status;
	string Test_name;
	
	Pass   = 1;
	Socket = 0;
	
	$display("svtest_prim_server: START");
	
	///////////////////////////
	Test_name = "\tinit_server";
	Socket = init_server(`MY_PORT);
	if (!Socket) Pass=0;
	$display("\tsvtest_prim_server: socket=%0d",Socket);
	print_status(Test_name,Pass);
	
	///////////////////////////
	Test_name = "\tint_loopback";
	Pass=int_loopback_test(Socket);
	print_status(Test_name,Pass);
        ///////////////////////////
	Test_name = "\treal_loopback";
	Pass=real_loopback_test(Socket);
	print_status(Test_name,Pass);
	//
	Test_name = "svtest_prim_server";
	print_status(Test_name,Pass);
	
     end
   
   
   
   function int init_server(int portno);
      begin
	 int socket_id;
	 socket_id=0;
	 socket_id = svcs_dpi_server_init(portno);
	 return socket_id;
      end
   endfunction : init_server

   function int int_loopback_test(int socket_id);
      begin
	 int success;
         int unsigned Int_exp;
	 int unsigned Int_act;
	 success =1;
	 Int_exp = $urandom();
	 success = svcs_dpi_send_int(socket_id,Int_exp);
	 success = svcs_dpi_recv_int(socket_id,Int_act);
	 if (Int_exp != Int_act)success=0;
         return  success;
      end
   endfunction : int_loopback_test
  
   function int real_loopback_test(int socket_id);
      begin
	 int success;
         real Real_exp;
	 real Real_act;
	 success =1;
	 Real_exp = $urandom();
	 Real_act = $urandom();
	 //$display("serveer real real_exp=%f Real_act=%f",Real_exp,Real_act); 
	 success = svcs_dpi_send_real(socket_id,Real_exp);
	 success = svcs_dpi_recv_real(socket_id,Real_act);
	 if (Real_exp != Real_act)success=0;
	 //$display("serveer real real_exp=%f Real_act=%f",Real_exp,Real_act); 
         return  success;
      end
   endfunction : real_loopback_test
   
   function void print_status(string Test_name,int Status_int);
      begin
	 string Status;
	 if (!Status_int) Status = "FAIL";
	 else  Status = "PASS";
	 $display("%s TEST %s",Test_name,Status);
      end
   endfunction : print_status
   
  
   
endmodule : svtest_prim_server

