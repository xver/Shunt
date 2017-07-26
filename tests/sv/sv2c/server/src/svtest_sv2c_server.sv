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
	Test_name = "\tint loopback";
	Pass=int_loopback_test(Socket);
	print_status(Test_name,Pass);
	//////////////////////////
	Test_name = "\tlong loopback";
	Pass=long_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tbyte loopback";
	Pass=byte_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tinteger loopback";
	Pass=integer_loopback_test(Socket);
	print_status(Test_name,Pass);
 	///////////////////////////
	Test_name = "\ttime loopback";
	Pass=time_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tbit_loopback";
	Pass=bit_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\treg_loopback";
	Pass=reg_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tlogic_loopback";
	Pass=logic_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tbitN_loopback";
	Pass=bitN_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tregN_loopback";
	Pass=regN_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tlogicN_loopback";
	Pass=logicN_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\treal_loopback";
	Pass=real_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\tshortreal_loopback";
	Pass=shortreal_loopback_test(Socket);
	print_status(Test_name,Pass);
	///////////////////////////
	Test_name = "\trealtime_loopback";
	Pass=realtime_loopback_test(Socket);
	print_status(Test_name,Pass);
		
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
	 Short_exp = $urandom();
	 
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

   function int int_loopback_test(int socket_id);
      begin
	 int success;
         int Int_exp;
	 int Int_act;
         string Test_name = "server int_loopback_test";
	 
	 success = 1;
	 Int_exp = $urandom();
	 
	 //send
	 if (svcs_dpi_send_int (socket_id,Int_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send data");
	 //recv
	 if (svcs_dpi_recv_int(socket_id,Int_act)<= 0) success = 0;
	 if (success == 0 )  $display("\nInt loopback fail recv");
	 //$display("\n%s Int_exp=%h  Int_act=%h",Test_name,Int_exp,Int_act);
	 if (Int_exp !== Int_act)success=0;
	 return  success;
      end
   endfunction : int_loopback_test

   function int long_loopback_test(int socket_id);
      begin
	 int success;
         longint Long_exp;
	 longint Long_act;
         string Test_name = "server long_loopback_test";
	 
	 success = 1;
	 Long_exp = {$urandom(),$urandom()};
	 
	 //send
	 if (svcs_dpi_send_long (socket_id,Long_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send data");
	 //recv
	 if (svcs_dpi_recv_long(socket_id,Long_act)<= 0) success = 0;
	 if (success == 0 )  $display("\nLong loopback fail recv");
	 //$display("\n%s Long_exp=%h  Long_act=%h",Test_name,Long_exp,Long_act);
	 if (Long_exp !== Long_act)success=0;
	 return  success;
      end
   endfunction : long_loopback_test

   function int byte_loopback_test(int socket_id);
      begin
	 int success;
         byte Byte_exp;
	 byte Byte_act;
         string Test_name = "server byte_loopback_test";
	 
	 success = 1;
	 Byte_exp = $urandom();
	 
	 //send
	 if (svcs_dpi_send_byte (socket_id,Byte_exp)<= 0) success = 0;
	 if (success == 0 )  $display("\nserver: fail send data");
	 //recv
	 if (svcs_dpi_recv_byte(socket_id,Byte_act)<= 0) success = 0;
	 if (success == 0 )  $display("\nByte loopback fail recv");
	 //$display("\n%s Byte_exp=%h  Byte_act=%h",Test_name,Byte_exp,Byte_act);
	 if (Byte_exp !== Byte_act)success=0;
	 return  success;
      end
   endfunction : byte_loopback_test
   
   function int   integer_loopback_test(int socket_id);
      
      int 	success;
      integer   Integer_exp;
      integer   Integer_act;
      
      string 	Test_name = "server integer_loopback_test";
      success =1;
      
      //set up data
      Integer_exp = 32'hf0xx_zz5a;
      
      //send data
      if (svcs_dpi_send_integer(socket_id,Integer_exp)<=0) success = 0;
      if (svcs_dpi_recv_integer(socket_id,Integer_act)<=0) success = 0;
      
      //comp
      if(Integer_act !== Integer_exp) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data");
      //$display("\n%s Integer_exp=%h  Integer_act=%h",Test_name,Integer_exp,Integer_act);
      return  success;
   endfunction :integer_loopback_test

   function int   time_loopback_test(int socket_id);
      
      int 	success;
      time   Time_exp;
      time   Time_act;
      
      string 	Test_name = "server time_loopback_test";
      success =1;
      
      //set up data
      Time_exp =  64'hf0xx_zz5a_dezz_67xx;
      Time_act = 0;
      
      
      //send data
      if (svcs_dpi_send_time(socket_id,Time_exp)<=0) success = 0;
      if (svcs_dpi_recv_time(socket_id,Time_act)<=0) success = 0;
      
      //comp
      if(Time_act !== Time_exp) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data");
      //$display("\n%s Time_exp=%h  Time_act=%h",Test_name,Time_exp,Time_act);
   
      return  success;
   endfunction :time_loopback_test

   function int   bit_loopback_test(int socket_id);
      
      int 	success;
      bit   Bit_exp;
      bit   Bit_act;
      
      string 	Test_name = "server bit_loopback_test";
      success =1;
      
      //set up data
      Bit_exp = $random;
      Bit_act = 0;
      
      
      //send data
      if (svcs_dpi_send_bit(socket_id,Bit_exp)<=0) success = 0;
      if (svcs_dpi_recv_bit(socket_id,Bit_act)<=0) success = 0;
      
      //comp
      if(Bit_act !== Bit_exp) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data");
      //$display("\n%s Bit_exp=%h  Bit_act=%h",Test_name,Bit_exp,Bit_act);
   
      return  success;
   endfunction :bit_loopback_test
   
   function int   reg_loopback_test(int socket_id);
      
      int 	success;
      reg   Reg_exp;
      reg   Reg_act;
      
      string 	Test_name = "server reg_loopback_test";
      success =1;
      
      //set up data
      Reg_exp = 1'bz;
      Reg_act = 0;
      
      
      //send data
      if (svcs_dpi_send_reg(socket_id,Reg_exp)<=0) success = 0;
      if (svcs_dpi_recv_reg(socket_id,Reg_act)<=0) success = 0;
      
      //comp
      if(Reg_act !== Reg_exp) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data");
      //$display("\n%s Reg_exp=%h  Reg_act=%h",Test_name,Reg_exp,Reg_act);
   
      return  success;
   endfunction :reg_loopback_test

   function int   logic_loopback_test(int socket_id);
      
      int 	success;
      logic   Logic_exp;
      logic   Logic_act;
      
      string 	Test_name = "server logic_loopback_test";
      success =1;
      
      //set up data
      Logic_exp = 1'bx; //$random;
      Logic_act = 0;
      
      
      //send data
      if (svcs_dpi_send_logic(socket_id,Logic_exp)<=0) success = 0;
      if (svcs_dpi_recv_logic(socket_id,Logic_act)<=0) success = 0;
      
      //comp
      if(Logic_act !== Logic_exp) success = 0;  
      if (success == 0 )  $display("\nserver: fail comp data");
      //$display("\n%s Logic_exp=%h  Logic_act=%h",Test_name,Logic_exp,Logic_act);
   
      return  success;
   endfunction :logic_loopback_test

   function int bitN_loopback_test(int socket_id,int n_payloads=1);
      begin
	 localparam N = 133;//N 4*32 bit max
	 
	 int success;
	 int i;
	 bit [N-1:0] BitN_exp;
	 bit [N-1:0] BitN_act;
	 string    s_me = "bitN_loopback_test";
	 success =1;
	 
	 //data set
	 BitN_exp =  {$urandom(),$urandom(),$urandom(),$urandom()};
	 
	 
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_BITN");
	 h_trnx_exp.n_payloads = N;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if(!svcs_dpi_hs_send_bitN(socket_id,h_trnx_exp,BitN_exp))  success =0;
	 
	 //recv
	 if (svcs_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
	 if(!svcs_dpi_hs_recv_bitN(socket_id,h_trnx_act,BitN_act))  success =0;
	 //
	 if(BitN_act !== BitN_exp) success =0;
	 //$display("\n %s BitN_act=\n%h vs \n%h",s_me, BitN_act, BitN_exp);
	 return  success;
      end
   endfunction : bitN_loopback_test


   function int regN_loopback_test(int socket_id,int n_payloads=1);
      begin
	 localparam N = 133;//N 4*32 bit max
	 
	 int success;
	 int i;
	 reg [N-1:0] XRegNV_exp;
         reg [N-1:0] RegNV_exp;
	 reg [N-1:0] RegNV_act;
	 string    s_me = "regN_loopback_test";
	 success =1;
	 
	 //data set
	 XRegNV_exp = 'hx;
	 RegNV_exp =  {$urandom(),$urandom(),$urandom(),$urandom()}& XRegNV_exp;
	 RegNV_exp =   RegNV_exp | {$urandom(),$urandom(),$urandom(),$urandom()};
	 
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_REG4S");
	 h_trnx_exp.n_payloads = N;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if(!svcs_dpi_hs_send_regN(socket_id,h_trnx_exp,RegNV_exp))  success =0;
	 
	 //recv
	 if (svcs_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
	 if(!svcs_dpi_hs_recv_regN(socket_id,h_trnx_act,RegNV_act))  success =0;
	 //
	 if(RegNV_act !== RegNV_exp) success =0;
	 //$display("\n %s RegNV_act=\n%h vs \n%h",s_me, RegNV_act, RegNV_exp);
	 return  success;
      end
   endfunction : regN_loopback_test
   
   function int logicN_loopback_test(int socket_id,int n_payloads=1);
      begin
	 localparam N = 133;//N 4*32 bit max
	 
	 int success;
	 int i;
	 logic [N-1:0] XLogicN_exp;
         logic [N-1:0] LogicN_exp;
	 logic [N-1:0] LogicN_act;
	 string    s_me = "logicN_loopback_test";
	 success =1;
	 
	 //data set
	 XLogicN_exp = 'hx;
	 LogicN_exp =  {$urandom(),$urandom(),$urandom(),$urandom()}& XLogicN_exp;
	 LogicN_exp =   LogicN_exp | {$urandom(),$urandom(),$urandom(),$urandom()};
	 
	 //set up header
	 h_trnx_exp.trnx_type = $urandom;
	 h_trnx_exp.trnx_id   = $urandom;
	 h_trnx_exp.data_type = svcs_dpi_hash("SVCS_REG4S");
	 h_trnx_exp.n_payloads = N;
	 
	 //send
	 if (svcs_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
	 if(!svcs_dpi_hs_send_logicN(socket_id,h_trnx_exp,LogicN_exp))  success =0;
	 
	 //recv
	 if (svcs_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
	 if(!svcs_dpi_hs_recv_logicN(socket_id,h_trnx_act,LogicN_act))  success =0;
	 //
	 if(LogicN_act !== LogicN_exp) success =0;
	 //$display("\n %s LogicN_act=\n%h vs \n%h",s_me, LogicN_act, LogicN_exp);
	 return  success;
      end
   endfunction : logicN_loopback_test

   function int real_loopback_test(int socket_id);
      begin
	 int success;
         real Real_exp;
	 real Real_act;
	 string s_me = "real_loopback_test";
	 success =1;
	 Real_exp = $urandom()/7.5;
	 if(!svcs_dpi_send_real(socket_id,Real_exp)) success=0;
	 if(!svcs_dpi_recv_real(socket_id,Real_act)) success=0;
	 if (Real_exp != Real_act)success=0;
	 //$display("\n %s Real_act=\n%f vs \n%f",s_me, Real_act, Real_exp);
	 return  success;
      end
   endfunction : real_loopback_test
 
   function int realtime_loopback_test(int socket_id);
      begin
	 int success;
         realtime Realtime_exp;
	 realtime Realtime_act;
	 string s_me = "realtime_loopback_test";
	 success =1;
	 Realtime_exp =  $urandom()/7.5;
	 if(!svcs_send_realtime(socket_id,Realtime_exp)) success=0;
	 if(!svcs_recv_realtime(socket_id,Realtime_act)) success=0;
	 if (Realtime_exp != Realtime_act)success=0;
	 //$display("\n %s Realtime_act=\n%f vs \n%f",s_me, Realtime_act, Realtime_exp);
	 return  success;
      end
   endfunction : realtime_loopback_test
   
   function int shortreal_loopback_test(int socket_id);
      begin
	 int success;
         shortreal Shortreal_exp;
	 shortreal Shortreal_act;
	 string s_me = "shortreal_loopback_test";
	 success =1;
	 
	 Shortreal_exp = 123;
	 
	 
	 if(!svcs_dpi_send_shortreal(socket_id,Shortreal_exp)) success=0;
	 if(!svcs_dpi_recv_shortreal(socket_id,Shortreal_act)) success=0;
	 if (Shortreal_exp != Shortreal_act) success=0;
	 //$display("\n %s Shortreal_act=\n%f vs \n%f",s_me, Shortreal_act, Shortreal_exp);
	 return  success;
      end
   endfunction : shortreal_loopback_test
   
   ////////////////////////////////////////////
/* -----\/----- EXCLUDED -----\/-----
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
      IF (svcs_hs_send_byteA(socket_id,h_trnx_exp,h_data_exp,Byte_exp)<=0) success = 0;
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
 -----/\----- EXCLUDED -----/\----- */
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

