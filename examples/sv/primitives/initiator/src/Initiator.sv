/*
============================================================================
 File        : Initiator.sv
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description :TCP/IP SystemVerilog SHUNT
              An example of primitive functions -Initiator(server)  
 ============================================================================
*/

`include "../../includes/cs_common.svh"

module automatic Initiator;
   
   import shunt_dpi_pkg::*;
   int Socket; 

   initial
     begin
	int Pass;
	string Status;
	string Test_name;
	
	Pass   = 1;
	Socket = 0;
	
	$display("primSV Initiator: START");
	
	///////////////////////////
	Test_name = "\tinit_initiator";

	Socket = init_initiator(`MY_PORT);
	if (!Socket) Pass=0;
	$display("\tprimSV Initiator: socket=%0d",Socket);
	print_status(Test_name,Pass);
	

	///////////////////////////
	Test_name = "\tbyte_loopback";
	Pass=byte_loopback_test(Socket);
	print_status(Test_name,Pass);
        ///////////////////////////
	Test_name = "\tint_loopback";
	Pass=int_loopback_test(Socket);
	print_status(Test_name,Pass);
        ///////////////////////////
	Test_name = "\treal_loopback";
	Pass=real_loopback_test(Socket);
	print_status(Test_name,Pass);
	////////////////////////////
	Test_name = "\tintV_loopback";
	Pass =intV_loopback_test(Socket);
	print_status(Test_name,Pass);
	////////////////////////////
	Test_name = "\trealV_loopback";
	Pass =realV_loopback_test(Socket);
	print_status(Test_name,Pass);
	////////////////////////////
	Test_name = "\tstring_loopback";
	Pass =string_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	//
	Test_name = "primSV Initiator";
	print_status(Test_name,Pass);

     end
 
   
   
   
   function int init_initiator(int portno);
      begin
	 int socket_id;
	 socket_id=0;
	 socket_id = shunt_dpi_initiator_init(portno);
	 return socket_id;
      end
   endfunction : init_initiator
  
   function int byte_loopback_test(int socket_id);
      begin
	 int success;
         byte  Byte_exp;
	 byte  Byte_act;
	 success =1;
	 Byte_exp = $urandom();
	 Byte_act = 'h15;
	 if(!shunt_dpi_send_byte(socket_id,Byte_exp)) success=0;
	 if(!shunt_dpi_recv_byte(socket_id,Byte_act)) success=0;
	
	 if (Byte_exp != Byte_act)success=0;
         return  success;
      end
   endfunction : byte_loopback_test
   
   
   function int int_loopback_test(int socket_id);
      begin
	 int success;
         int unsigned Int_exp;
	 int unsigned Int_act;
	 success =1;
	 Int_exp = $urandom();
	 if(!shunt_dpi_send_int(socket_id,Int_exp)) success=0;
	 if(!shunt_dpi_recv_int(socket_id,Int_act)) success=0;
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
	 if(!shunt_dpi_send_real(socket_id,Real_exp)) success=0;
	 if(!shunt_dpi_recv_real(socket_id,Real_act)) success=0;
	 if (Real_exp != Real_act)success=0;
	 return  success;
      end
   endfunction : real_loopback_test

   function int intV_loopback_test(int socket_id);
      begin
	 int success;
	 int i;
         int IntV_exp[`V_SIZE];
	 int IntV_act[`V_SIZE];
	 
	 success =1;
	 
	 foreach(IntV_exp[i]) IntV_exp[i] = 100+(i+1);
	 foreach(IntV_act[i]) IntV_act[i] = 300+(i+1);
	 if(!shunt_dpi_send_intV(socket_id,`V_SIZE,IntV_exp)) success =0;
	 if(!shunt_dpi_recv_intV(socket_id,`V_SIZE,IntV_act)) success =0;
	 foreach(IntV_exp[i]) if(IntV_act[i] != IntV_exp[i]) success =0;
	 return  success;
      end
   endfunction: intV_loopback_test
   
   function int realV_loopback_test(int socket_id);
      begin
	 int success;
	 int i;
         real RealV_exp[`V_SIZE];
	 real RealV_act[`V_SIZE];
	 
	 success =1;
	 
	 foreach(RealV_exp[i]) RealV_exp[i] = 100+(i+1);
	 foreach(RealV_act[i]) RealV_act[i] = 300+(i+1);
	 if(!shunt_dpi_send_realV(socket_id,`V_SIZE,RealV_exp))  success =0;
	 if(!shunt_dpi_recv_realV(socket_id,`V_SIZE,RealV_act))  success =0;
	 foreach(RealV_exp[i]) if(RealV_act[i] != RealV_exp[i]) success =0;
	 return  success;
      end
   endfunction : realV_loopback_test
   
   function int string_loopback_test(int socket_id);
      begin
	 int success;
	 int i;
         string String_exp;
	 string String_act;
	
	 String_exp = `STRING_MESSAGE;
	 String_act = `STRING_MESSAGE1;
	 success =1;
	 if(!shunt_dpi_send_string(socket_id,String_exp.len(),String_exp))  success =0;
	 if(!shunt_dpi_recv_string(socket_id,String_exp.len(),String_act))  success =0;
	 foreach(String_exp[i]) if(String_act[i] != String_exp[i]) success =0;
	 return  success;
      end
   endfunction : string_loopback_test

   
     //////////////////////
   
   function void print_status(string Test_name,int Status_int);
      begin
	 string Status;
	 if (!Status_int) Status = "FAIL";
	 else  Status = "PASS";
	 $display("%s TEST %s",Test_name,Status);
      end
   endfunction : print_status
   
  
   
endmodule :Initiator

