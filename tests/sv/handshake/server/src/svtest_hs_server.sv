/*
============================================================================
 File        : svtest_hs_server.sv
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

module automatic svtest_hs_server;
   
   import svcs_dpi_pkg::*;
   int Socket;
   cs_header_t      h_trnx_exp;
   cs_data_header_t h_data_exp;
   cs_header_t      h_trnx_act;
   cs_data_header_t h_data_act;
   
   

   initial
     begin
	int Pass;
	string Status;
	string Test_name;
	
	Pass   = 1;
	Socket = 0;
	
	$display("svtest_hs_server: START");
	
	///////////////////////////
	Test_name = "\tinit_server";

	Socket = init_server(`MY_PORT);
	if (!Socket) Pass=0;
	$display("\tsvtest_hs_server: socket=%0d",Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	//Test_name = "\tbyte loopback";
	//Pass=byte_loopback_test(Socket);
	//print_status(Test_name,Pass);
	//Test_name = "\tbyte vector loopback";
	//Pass=byte_loopback_test(Socket,15);
	//print_status(Test_name,Pass);
 	///////////////////////////
	Test_name = "\tint_loopback";
	Pass=int_loopback_test(Socket);
	print_status(Test_name,Pass);
	Test_name = "\tint vector loopback";
	Pass=int_loopback_test(Socket,9);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\treal_loopback";
	Pass=real_loopback_test(Socket);
	print_status(Test_name,Pass);
	Test_name = "\treal vector loopback";
	Pass=real_loopback_test(Socket,11);
	print_status(Test_name,Pass);
	////////////////////////////
	Test_name = "\tbyteA loopback";
	Pass=byteA_loopback_test(Socket);
	print_status(Test_name,Pass);
	Test_name = "\tbyteA loopback";
	Pass=byteA_loopback_test(Socket,7);
	print_status(Test_name,Pass);
	//
	Test_name = "svtest_hs_server";
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
  
   function int byte_loopback_test(int socket_id,int n_payloads=1);
      begin
	 int success;
         byte Byte_exp[];
	 byte Byte_act[];
         string Test_name = "server byte_loopback_test";
	 Byte_exp = new[n_payloads];
	 success =1;
	 for(int i=0;i<n_payloads;i++) Byte_exp[i] = "A"+i;
	 Byte_exp[n_payloads] = "\0";
	 //for(int i=0;i<n_payloads;i++) $display("\nByte_exp[%0d]=%c",i,Byte_exp[i]);
	 //Byte_act[0] = 'h69;
	 
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_BYTE");
	 h_trnx_exp.n_payloads = n_payloads;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send header ");
	 if (svcs_dpi_hs_send_byte  (socket_id,h_trnx_exp,Byte_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send data");
	
	 //recv
	 if (svcs_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
	 Byte_act = new[h_trnx_act.n_payloads];
	 if (svcs_dpi_hs_recv_byte(socket_id,h_trnx_act,Byte_act)<= 0) success = 0;
	 if (success == 0 )  $display("\nByte loopback fail recv");
	 //$display("\n%s Byte_exp=%s  Byte_act=%s",Test_name,Byte_exp,Byte_act);
	 for(int i=0;i<n_payloads;i++)	if (Byte_exp[i] != Byte_act[i])success=0;
         return  success;
      end
   endfunction : byte_loopback_test
   
   
   function int int_loopback_test(int socket_id,int n_payloads=1);
      begin
	 int success;
         int Int_exp[];
	 int Int_act[];
         string Test_name = "server int_loopback_test";
	 Int_exp = new[n_payloads];
	 success =1;
	 for(int i=0;i<n_payloads;i++) Int_exp[i] = 100 +i;
	 Int_exp[n_payloads] = "\0";
	 //for(int i=0;i<n_payloads;i++) $display("\nInt_exp[%0d]=%c",i,Int_exp[i]);
	 //Int_act[0] = 'h69;
	 
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_INT");
	 h_trnx_exp.n_payloads = n_payloads;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send header ");
	 if (svcs_dpi_hs_send_int  (socket_id,h_trnx_exp,Int_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send data");
	
	 //recv
	 if (svcs_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
	 Int_act = new[h_trnx_act.n_payloads];
	 if (svcs_dpi_hs_recv_int(socket_id,h_trnx_act,Int_act)<= 0) success = 0;
	 if (success == 0 )  $display("\nInt loopback fail recv");
	 //for(int i=0;i<n_payloads;i++)$display("\n%s Int_exp[%0d]=%d  Int_act[%0d]=%d",Test_name,i,Int_exp[i],i,Int_act[i]);
	 for(int i=0;i<n_payloads;i++)	if (Int_exp[i] != Int_act[i])success=0;
         return  success;	 
         
      end
   endfunction : int_loopback_test
 
   
   
   function int real_loopback_test(int socket_id,int n_payloads=1);
      begin
	 int success;
         real Real_exp[];
	 real Real_act[];
         string Test_name = "server real_loopback_test";
	 Real_exp = new[n_payloads];
	 success =1;
	 for(int i=0;i<n_payloads;i++) Real_exp[i] = 300.123+i;
	 Real_exp[n_payloads] = "\0";
	 //for(int i=0;i<n_payloads;i++) $display("\nReal_exp[%0d]=%c",i,Real_exp[i]);
	 //Real_act[0] = 'h69;
	 
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_DOUBLE");
	 h_trnx_exp.n_payloads = n_payloads;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send header ");
	 if (svcs_dpi_hs_send_real  (socket_id,h_trnx_exp,Real_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send data");
	
	 //recv
	 if (svcs_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
	 Real_act = new[h_trnx_act.n_payloads];
	 if (svcs_dpi_hs_recv_real(socket_id,h_trnx_act,Real_act)<= 0) success = 0;
	 //for(int i=0;i<n_payloads;i++)$display("\n%s Real_exp[%0d]=%f  Real_act[%0d]=%f",Test_name,i,Real_exp[i],i,Real_act[i]);
	 for(int i=0;i<n_payloads;i++)	if (Real_exp[i] != Real_act[i])success=0;
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
	 if(!svcs_dpi_send_intV(socket_id,`V_SIZE,IntV_exp)) success =0;
	 if(!svcs_dpi_recv_intV(socket_id,`V_SIZE,IntV_act)) success =0;
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
	 if(!svcs_dpi_send_realV(socket_id,`V_SIZE,RealV_exp))  success =0;
	 if(!svcs_dpi_recv_realV(socket_id,`V_SIZE,RealV_act))  success =0;
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
	 if(!svcs_dpi_send_string(socket_id,String_exp.len(),String_exp))  success =0;
	 success = svcs_dpi_send_string(socket_id,String_exp.len(),String_exp);
	 if(!svcs_dpi_recv_string(socket_id,String_exp.len(),String_act))  success =0;
	 foreach(String_exp[i]) if(String_act[i] != String_exp[i]) success =0;
	 return  success;
      end
   endfunction : string_loopback_test
   
   
 function int   byteA_loopback_test(int socket_id,int n_payloads=1);
   begin
      int success;
      byte Byte_exp[][];
      byte Byte_act[][];
      string Test_name = "server byteA_loopback_test";
      success =1;
      
      //set up data
      Byte_exp = new[n_payloads]; 
      foreach(Byte_exp[i]) Byte_exp[i] = new[n_payloads];
      foreach(Byte_exp[i]) foreach(Byte_exp[j]) Byte_exp[i][j]= "A"+(i*10)+j;
      //foreach(Byte_exp[i]) foreach(Byte_exp[j]) $display("\n %s Byte_exp[%0d][%0d]=%c",Test_name,i,j,Byte_exp[i][j]);
            
      //set up trnx header
      h_trnx_exp.trnx_type = $urandom;
      h_trnx_exp.trnx_id   = $urandom;
      h_trnx_exp.data_type = svcs_dpi_hash("SVCS_A_STRUCTURE");
      h_trnx_exp.n_payloads = n_payloads;
      //set up data header
      h_data_exp.data_type = svcs_dpi_hash("SVCS_BYTE");
      h_data_exp.trnx_payload_sizes = new[n_payloads];
      foreach(h_data_exp.trnx_payload_sizes[i]) h_data_exp.trnx_payload_sizes[i] = n_payloads;
      //foreach(h_data_exp.trnx_payload_sizes[i]) $display("\n%s h_data_exp.trnx_payload_sizes[%0d]=%0d",Test_name,i,h_data_exp.trnx_payload_sizes[i]);
      
      //send
      //send trnx header
      if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
      if (success == 0 )  $display("\nserver: fail send trnx header ");
      //send data header
      if (svcs_dpi_send_data_header(socket_id,h_trnx_exp,h_data_exp.data_type,h_data_exp.trnx_payload_sizes)<= 0) success = 0;
      if (success == 0 )  $display("\nserver: fail send data header");
      //send data
      if (svcs_hs_send_byteA(socket_id,h_trnx_exp,h_data_exp,Byte_exp)<=0) success = 0;
      if (success == 0 )  $display("\nserver: fail send data");
      
      //recv
      if (svcs_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
      if (success == 0 )  $display("\nserver: fail rcv trnx header ");
      //recv data header 
      h_data_act.trnx_payload_sizes = new[h_trnx_act.n_payloads];
      for(int i=0;i<h_trnx_act.n_payloads;i++) h_data_act.trnx_payload_sizes[i]=0;
      if(svcs_dpi_recv_data_header(socket_id,h_trnx_act,h_data_act.data_type,h_data_act.trnx_payload_sizes)<=0) success = 0;
      if (success == 0 )  $display("\nserver: fail rcv data header ");
      //recv data
      Byte_act   = new[h_trnx_act.n_payloads]; 
      foreach(Byte_act[i]) Byte_act[i] = new[h_data_act.trnx_payload_sizes[i]];
      if(svcs_hs_recv_byteA  (socket_id,h_trnx_act,h_data_act,Byte_act)<=0) $display("%s recv_byteA TEST FAIL",Test_name);
      //foreach(Byte_act[i]) foreach(Byte_act[j]) $display("\n %s Byte_act[%0d][%0d]=%c",Test_name,i,j,Byte_act[i][j]);

      //comp
      foreach(Byte_act[i]) foreach(Byte_act[j]) if(Byte_act[i][j] !=Byte_exp[i][j]) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data header ");
      return  success;
   end
    
 endfunction :byteA_loopback_test
   
   function void print_status(string Test_name,int Status_int);
      begin
	 string Status;
	 if (!Status_int) Status = "FAIL";
	 else  Status = "PASS";
	 $display("%s TEST %s",Test_name,Status);
      end
   endfunction : print_status
   
  
   
endmodule : svtest_hs_server

