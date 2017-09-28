/*
============================================================================
 File        : Target.sv
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : TCP/IP SystemVerilog SHUNT
              An example of primitive functions -Target(client)  
 ============================================================================
*/
`include "../../includes/cs_common.svh"

module automatic Target;
 
   import shunt_dpi_pkg::*;
   
   string String;
   int 	 Socket; 

   initial
     begin

	int Result;
		
	Socket=0;
	Result=0;
	
        #1000ns;
	
        //
	//String.toupper();	
	$display("primSV Target: START");

	Socket = init_target(`MY_PORT, `MY_HOST);
	$display("primSV Target: socket=%0d",Socket);
	byte_loopback_test(Socket);
	int_loopback_test(Socket);
	real_loopback_test(Socket);
	intV_loopback_test(Socket);
	realV_loopback_test(Socket);
	string_loopback_test(Socket);
	$display("primSV Target: END");
	
     end
 
   
   
   function int init_target(int portno,string hostname);
      int   socket_id;
      socket_id=0;
      socket_id = shunt_dpi_target_init(portno,hostname);
      return socket_id;
   endfunction : init_target
   
   //////////
   function void byte_loopback_test(int socket_id);
      byte   Byte;
      string Test_name;
   
      Test_name = "target byte_loopback_test recv";
      if (!shunt_dpi_recv_byte(socket_id,Byte)) $display("%s TEST FAIL",Test_name);
      Test_name = "target byte_loopback_test send";
      if (!shunt_dpi_send_byte(socket_id,Byte)) $display("%s TEST FAIL",Test_name);
   endfunction : byte_loopback_test
   
   function void int_loopback_test(int socket_id);
      int   Int;
      string Test_name;
   
      Test_name = "target int_loopback_test recv";
      if (!shunt_dpi_recv_int(socket_id,Int)) $display("%s TEST FAIL",Test_name);
      Test_name = "target int_loopback_test send";
      if (!shunt_dpi_send_int(socket_id,Int)) $display("%s TEST FAIL",Test_name);
   endfunction : int_loopback_test
   
   function void intV_loopback_test(int socket_id);
      int    IntV[`V_SIZE];
      string Test_name;
      
      foreach(IntV[i]) IntV[i] = 200+(i+1);
      Test_name = "target intV_loopback_test recv";
      if (!shunt_dpi_recv_intV(socket_id,`V_SIZE,IntV)) $display("%s TEST FAIL",Test_name);
      Test_name = "target intV_loopback_test send";
      if (!shunt_dpi_send_intV(socket_id,`V_SIZE,IntV)) $display("%s TEST FAIL",Test_name);
   endfunction // intV_loopback_test
   
   function void real_loopback_test(int socket_id);
      real   Real;
      string Test_name;
      
      Test_name = "target real_loopback_test recv";
      if (!shunt_dpi_recv_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
      Test_name = "target real_loopback_test send";
      if (!shunt_dpi_send_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
   endfunction : real_loopback_test
   
   function void realV_loopback_test(int socket_id);
      real   RealV[`V_SIZE];
      string Test_name;
      
      foreach(RealV[i]) RealV[i] = 200+(i+1);
      Test_name = "target realV_loopback_test recv";
      if (!shunt_dpi_recv_realV(socket_id,`V_SIZE,RealV)) $display("%s TEST FAIL",Test_name);
      Test_name = "target realV_loopback_test send";
      if (!shunt_dpi_send_realV(socket_id,`V_SIZE,RealV)) $display("%s TEST FAIL",Test_name);
   endfunction : realV_loopback_test
   
   function void string_loopback_test(int socket_id);
    
      string Test_name;
      int    size;
      int    Result_;
      
      String = `STRING_MESSAGE1;
      Test_name = "SV target string_loopback_test recv";
      
      
       //$display("SV before target String = %s",String);	
       if (shunt_dpi_recv_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
       Result_ = shunt_dpi_recv_string(socket_id,size,String);
       //$display("SV after target String = %s",String);
       Test_name = "target string_loopback_test send";
       if (shunt_dpi_send_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);

      
   endfunction : string_loopback_test
   
   

endmodule : Target