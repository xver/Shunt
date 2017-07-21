/*
============================================================================
 File        : svtest_sv2c_server.sv
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description :  sv2c function svcs dpi bridge test 

               System Verilog client server handshake (SVCS) library
 ============================================================================
*/

`include "../../includes/cs_common.svh"

module automatic svtest_sv2c_server;
   
   import svcs_dpi_pkg::*;
   import svcs_hs_pkg::*;
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
	
	$display("svtest_sv2c_server: START");
	
	///////////////////////////
	Test_name = "\tinit_server";
	Socket = init_server(`MY_PORT);
	if (!Socket) Pass=0;
	$display("\tsvtest_sv2c_server: socket=%0d",Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tshort loopback";
	Pass=short_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	/* -----\/----- EXCLUDED -----\/-----
	 Test_name = "\tbyte loopback";
	 Pass=byte_loopback_test(Socket);
	 print_status(Test_name,Pass);
	 Test_name = "\tbyte vector loopback";
	 Pass=byte_loopback_test(Socket,15);
	 print_status(Test_name,Pass);
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
	 ////////////////////////////
	 Test_name = "\tintA loopback";
	 Pass=intA_loopback_test(Socket);
	 print_status(Test_name,Pass);
	 Test_name = "\tintA loopback";
	 Pass=intA_loopback_test(Socket,21);
	 print_status(Test_name,Pass);
	 ////////////////////////////
	 Test_name = "\trealA loopback";
	 Pass=realA_loopback_test(Socket);
	 print_status(Test_name,Pass);
	 Test_name = "\trealA loopback";
	 Pass=realA_loopback_test(Socket,5);
	 print_status(Test_name,Pass);
	 ///////////////////////////
	 Test_name = "\tbyte4sV loopback";
	 Pass=byte4sV_loopback_test(Socket,5);
	 print_status(Test_name,Pass);
	 //////////////////////////
	 Test_name = "\treg4sV loopback";
	 Pass=reg4sV_loopback_test(Socket,5);
	 print_status(Test_name,Pass);
	 //////////////////////////
	 -----/\----- EXCLUDED -----/\----- */
	Test_name = "svtest_sv2c_server";
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
   ////////////////////////////////////////////
   function int short_loopback_test(int socket_id);
      begin
	 int success;
         shortint Short_exp;
	 shortint Short_act;
         string Test_name = "server short_loopback_test";
	 
	 success = 1;
	 Short_exp = 16'hbeef;//$urandom();
	 
	 //send
	 if (svcs_dpi_send_short (socket_id,Short_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send data");
	 //recv
	 if (svcs_dpi_recv_short(socket_id,Short_act)<= 0) success = 0;
	 if (success == 0 )  $display("\nShort loopback fail recv");
	 //$display("\n%s Short_exp=%h  Short_act=%h",Test_name,Short_exp,Short_act);
	 if (Short_exp !== Short_act)success=0;
	 return  success;
      end
   endfunction : short_loopback_test
   ////////////////////////////////////////////
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
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_REAL");
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
      int 	success;
      byte 	Byte_exp[][];
      byte 	Byte_act[][];
      string 	Test_name = "server byteA_loopback_test";
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
      
   endfunction :byteA_loopback_test
   
   function int   intA_loopback_test(int socket_id,int n_payloads=1);
      int 	success;
      int 	Int_exp[][];
      int 	Int_act[][];
      string 	Test_name = "server intA_loopback_test";
      success =1;
      
      //set up data
      Int_exp = new[n_payloads]; 
      foreach(Int_exp[i]) Int_exp[i] = new[n_payloads];
      foreach(Int_exp[i]) foreach(Int_exp[j]) Int_exp[i][j]= 0+(i*100)+10*j;
      //foreach(Int_exp[i]) foreach(Int_exp[j]) $display("\n %s Int_exp[%0d][%0d]=%d",Test_name,i,j,Int_exp[i][j]);
      
      //set up trnx header
      h_trnx_exp.trnx_type = $urandom;
      h_trnx_exp.trnx_id   = $urandom;
      h_trnx_exp.data_type = svcs_dpi_hash("SVCS_A_STRUCTURE");
      h_trnx_exp.n_payloads = n_payloads;
      //set up data header
      h_data_exp.data_type = svcs_dpi_hash("SVCS_INT");
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
      if (svcs_hs_send_intA(socket_id,h_trnx_exp,h_data_exp,Int_exp)<=0) success = 0;
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
      Int_act   = new[h_trnx_act.n_payloads]; 
      foreach(Int_act[i]) Int_act[i] = new[h_data_act.trnx_payload_sizes[i]];
      if(svcs_hs_recv_intA  (socket_id,h_trnx_act,h_data_act,Int_act)<=0) $display("%s recv_intA TEST FAIL",Test_name);
      //foreach(Int_act[i]) foreach(Int_act[j]) $display("\n %s Int_act[%0d][%0d]=%d",Test_name,i,j,Int_act[i][j]);
      
      //comp
      foreach(Int_act[i]) foreach(Int_act[j]) if(Int_act[i][j] !=Int_exp[i][j]) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data header ");
      return  success;
      
   endfunction :intA_loopback_test
   
   function int   realA_loopback_test(int socket_id,int n_payloads=1);
      int 	success;
      real 	Real_exp[][];
      real 	Real_act[][];
      string 	Test_name = "server realA_loopback_test";
      success =1;
      
      //set up data
      Real_exp = new[n_payloads]; 
      foreach(Real_exp[i]) Real_exp[i] = new[n_payloads];
      foreach(Real_exp[i]) foreach(Real_exp[j]) Real_exp[i][j]= 12.123+(i*1000)+100*j;
      //foreach(Real_exp[i]) foreach(Real_exp[j]) $display("\n %s Real_exp[%0d][%0d]=%f",Test_name,i,j,Real_exp[i][j]);
      
      //set up trnx header
      h_trnx_exp.trnx_type = $urandom;
      h_trnx_exp.trnx_id   = $urandom;
      h_trnx_exp.data_type = svcs_dpi_hash("SVCS_A_STRUCTURE");
      h_trnx_exp.n_payloads = n_payloads;
      //set up data header
      h_data_exp.data_type = svcs_dpi_hash("SVCS_REAL");
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
      if (svcs_hs_send_realA(socket_id,h_trnx_exp,h_data_exp,Real_exp)<=0) success = 0;
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
      Real_act   = new[h_trnx_act.n_payloads]; 
      foreach(Real_act[i]) Real_act[i] = new[h_data_act.trnx_payload_sizes[i]];
      if(svcs_hs_recv_realA  (socket_id,h_trnx_act,h_data_act,Real_act)<=0) $display("%s recv_realA TEST FAIL",Test_name);
      //foreach(Real_act[i]) foreach(Real_act[j]) $display("\n %s Real_act[%0d][%0d]=%f",Test_name,i,j,Real_act[i][j]);
      
      //comp
      foreach(Real_act[i]) foreach(Real_act[j]) if(Real_act[i][j] !=Real_exp[i][j]) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data");
      return  success;
      
   endfunction :realA_loopback_test
   //  
   
   //////////////////////////////////
   function int byte4sV_loopback_test(int socket_id,int n_payloads=1);
      begin
	 int success;
	 int i;
         reg [7:0] Byte4sV_exp[];
	 reg [7:0] Byte4sV_act[];
	 string    s_me = "byte4sV_loopback_test";
	 success =1;
	 Byte4sV_exp = new[ n_payloads];
	 //Byte4sV_act = new[ n_payloads];
	 foreach(Byte4sV_exp[i]) begin  
	    if (i==0) Byte4sV_exp[i] =   8'bzx00_0111;
	    else Byte4sV_exp[i] = Byte4sV_exp[i-1] ^ 1'b1;   
	 end
	 //foreach(Byte4sV_exp[i])  $display("\n %s Byte4sV_exp[%0d]=%b",s_me,i, Byte4sV_exp[i]);
	 foreach(Byte4sV_act[i]) Byte4sV_act[i] = 8'b100_0000 +300+(i+1);
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_BYTE4S");
	 h_trnx_exp.n_payloads = n_payloads;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if(!svcs_hs_send_byte4s(socket_id,Byte4sV_exp))  success =0;
	 //
	 if (svcs_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
	 Byte4sV_act   = new[h_trnx_act.n_payloads];
         if(!svcs_hs_recv_byte4s(socket_id,Byte4sV_act))  success =0;
	 foreach(Byte4sV_exp[i]) if(Byte4sV_act[i] !== Byte4sV_exp[i]) success =0;
	 //foreach(Byte4sV_exp[i]) $display("\n %s Byte4sV_act[%0d]=%b vs %b",s_me,i, Byte4sV_act[i], Byte4sV_exp[i]);
	 return  success;
      end
   endfunction : byte4sV_loopback_test
   /////////////////////////////////
   function int reg4sV_loopback_test(int socket_id,int n_payloads=1);
      begin
	 localparam N = 133;//N 4*32 bit max
	 
	 int success;
	 int i;
	 reg [N-1:0] XReg4sV_exp;
         reg [N-1:0] Reg4sV_exp;
	 reg [N-1:0] Reg4sV_act;
	 string    s_me = "reg4sV_loopback_test";
	 success =1;
	 
	 //data set
	 XReg4sV_exp = 'hx;
	 Reg4sV_exp =  {$urandom(),$urandom(),$urandom(),$urandom()}& XReg4sV_exp;
	 Reg4sV_exp =   Reg4sV_exp | {$urandom(),$urandom(),$urandom(),$urandom()};
	 
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_REG4S");
	 h_trnx_exp.n_payloads = N;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if(!svcs_dpi_hs_send_reg4s(socket_id,h_trnx_exp,Reg4sV_exp))  success =0;
	 
	 //recv
	 if (svcs_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
	 if(!svcs_dpi_hs_recv_reg4s(socket_id,h_trnx_act,Reg4sV_act))  success =0;
	 //
	 if(Reg4sV_act !== Reg4sV_exp) success =0;
	 //$display("\n %s Reg4sV_act=\n%h vs \n%h",s_me, Reg4sV_act, Reg4sV_exp);
	 return  success;
      end
   endfunction : reg4sV_loopback_test
   //  
   function void print_status(string Test_name,int Status_int);
      begin
	 string Status;
	 if (!Status_int) Status = "FAIL";
	 else  Status = "PASS";
	 $display("%s TEST %s",Test_name,Status);
      end
   endfunction : print_status  
   
endmodule : svtest_sv2c_server

