/*
============================================================================
 File        : svtest_sv2c_client.sv
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

module automatic svtest_sv2c_client;
 
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
	$display("svtest_sv2c_client: START");
	Socket = init_client(`MY_PORT, `MY_HOST);
	$display("svtest_sv2c_client: socket=%0d",Socket);
	///////////////////////////
	short_loopback_test(Socket);
	int_loopback_test(Socket);
	long_loopback_test(Socket);
	byte_loopback_test(Socket);
	integer_loopback_test(Socket);
	time_loopback_test(Socket);
	bit_loopback_test(Socket);
	reg_loopback_test(Socket);
	logic_loopback_test(Socket);
	bitN_loopback_test(Socket);
	regN_loopback_test(Socket);
	logicN_loopback_test(Socket);
	real_loopback_test(Socket);
	shortreal_loopback_test(Socket);
	realtime_loopback_test(Socket);
	//
 	string_loopback_test(Socket);
	shortV_loopback_test(Socket);
	longV_loopback_test(Socket);
	realV_loopback_test(Socket);
	shortrealV_loopback_test(Socket);
	///////////////////////////
	
       $display("\nsvtest_sv2c_client: END");
	
     end // initial begin

     
   function int init_client(int portno,string hostname);
      int   socket_id;
      socket_id=0;
      socket_id = svcs_dpi_client_init(portno,hostname);
      return socket_id;
   endfunction : init_client
   
   //////////////////////////////////////////////////

   function void short_loopback_test(int socket_id);
      shortint   Short;
      string Test_name;
      
      Short ='hdead;
      
      Test_name = "\nclient short_loopback_test recv";
      //recv
      if (svcs_dpi_recv_short (socket_id,Short)<= 0) $display("%s TEST FAIL",Test_name);
       $display("%s Short=%h",Test_name,Short);
      //send
      Test_name = "client short_loopback_test send";
      if (svcs_dpi_send_short(socket_id,Short)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : short_loopback_test

   function void int_loopback_test(int socket_id);
      int   Int;
      string Test_name;
      
      Int ='hdead;
      
      Test_name = "\nclient int_loopback_test recv";
      //recv
      if (svcs_dpi_recv_int (socket_id,Int)<= 0) $display("%s TEST FAIL",Test_name);
       $display("%s Int=%h",Test_name,Int);
      //send
      Test_name = "client int_loopback_test send";
      if (svcs_dpi_send_int(socket_id,Int)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : int_loopback_test

   function void long_loopback_test(int socket_id);
      longint   Long;
      string Test_name;
      
      Long ='hdead;
      
      Test_name = "\nclient long_loopback_test recv";
      //recv
      if (svcs_dpi_recv_long (socket_id,Long)<= 0) $display("%s TEST FAIL",Test_name);
       $display("%s Long=%h",Test_name,Long);
      //send
      Test_name = "client long_loopback_test send";
      if (svcs_dpi_send_long(socket_id,Long)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : long_loopback_test

   function void byte_loopback_test(int socket_id);
      byte   Byte;
      string Test_name;
      
      Byte ='hdead;
      
      Test_name = "\nclient byte_loopback_test recv";
      //recv
      if (svcs_dpi_recv_byte (socket_id,Byte)<= 0) $display("%s TEST FAIL",Test_name);
       $display("%s Byte=%h",Test_name,Byte);
      //send
      Test_name = "client byte_loopback_test send";
      if (svcs_dpi_send_byte(socket_id,Byte)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : byte_loopback_test

   function void integer_loopback_test(int socket_id);
      integer Integer;
      string  Test_name;
      
      Test_name = "client integer_loopback_test recv";
      //recv
      if (svcs_dpi_recv_integer (socket_id,Integer)<= 0) $display("%s TEST FAIL",Test_name);
      //send
      Test_name = "client integer_loopback_test send";
      if (svcs_dpi_send_integer(socket_id,Integer)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : integer_loopback_test

   function void time_loopback_test(int socket_id);
      time Time;
      string  Test_name;
      
      Test_name = "client time_loopback_test recv";
      //recv
      if (svcs_dpi_recv_time (socket_id,Time)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Time=%h ",Test_name,Time);
      //send
      Test_name = "client time_loopback_test send";
      if (svcs_dpi_send_time(socket_id,Time)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : time_loopback_test
 
   function void bit_loopback_test(int socket_id);
      bit Bit;
      string  Test_name;
      
      Test_name = "client bit_loopback_test recv";
      //recv
      if (svcs_dpi_recv_bit (socket_id,Bit)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Bit=%h ",Test_name,Bit);
      //send
      Test_name = "client bit_loopback_test send";
      if (svcs_dpi_send_bit(socket_id,Bit)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : bit_loopback_test

   function void reg_loopback_test(int socket_id);
      reg Reg;
      string  Test_name;
      
      Test_name = "client reg_loopback_test recv";
      //recv
      if (svcs_dpi_recv_reg (socket_id,Reg)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Reg=%h ",Test_name,Reg);
      //send
      Test_name = "client reg_loopback_test send";
      if (svcs_dpi_send_reg(socket_id,Reg)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : reg_loopback_test
   
   function void logic_loopback_test(int socket_id);
      logic Logic;
      string  Test_name;
      
      Test_name = "client logic_loopback_test recv";
      //recv
      if (svcs_dpi_recv_logic (socket_id,Logic)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Logic=%h ",Test_name,Logic);
      //send
      Test_name = "client logic_loopback_test send";
      if (svcs_dpi_send_logic(socket_id,Logic)<= 0) $display("%s TEST FAIL",Test_name);
      
   endfunction : logic_loopback_test

   function void bitN_loopback_test(int socket_id);
      bit [1024:0] BitN;
      string 	   Test_name;
      
      Test_name = "client bitN_loopback_test recv";
      //recv     
      BitN = 'hz;
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_recv_bitN(socket_id,h_trnx,BitN)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s BitN=%h ",Test_name,BitN);
      //send
      //Test_name = "client bitN_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_bitN(socket_id,h_trnx,BitN)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : bitN_loopback_test

   function void regN_loopback_test(int socket_id);
      reg [1024:0] RegN;
      string 	   Test_name;
      
      Test_name = "client regN_loopback_test recv";
      //recv     
      RegN = 'hz;
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_recv_regN(socket_id,h_trnx,RegN)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n %s RegN=%h(%h)",Test_name, RegN,RegN[132:0]);
      //send
      //Test_name = "client regN_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_regN(socket_id,h_trnx,RegN)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : regN_loopback_test

   function void logicN_loopback_test(int socket_id);
      logic [1024:0] LogicN;
      string 	   Test_name;
      
      Test_name = "client logicN_loopback_test recv";
      //recv     
      LogicN = 'hz;
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_recv_logicN(socket_id,h_trnx,LogicN)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n %s LogicN=%h(%h)",Test_name, LogicN,LogicN[132:0]);
      //send
      //Test_name = "client logicN_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_logicN(socket_id,h_trnx,LogicN)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : logicN_loopback_test

   function void real_loopback_test(int socket_id);
      real   Real;
      string Test_name;
      
      Test_name = "client real_loopback_test recv";
      if (!svcs_dpi_recv_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
      $display("\n %s Real=%h(%f)",Test_name,Real,Real);
      Test_name = "client real_loopback_test send";
      if (!svcs_dpi_send_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
   endfunction : real_loopback_test
  
   function void realtime_loopback_test(int socket_id);
      realtime   Realtime;
      string Test_name;
      
      Test_name = "client realtime_loopback_test recv";
      if (!svcs_recv_realtime(socket_id,Realtime)) $display("%s TEST FAIL",Test_name);
      $display("\n %s Realtime=%h(%f)",Test_name,Realtime,Realtime);
      Test_name = "client realtime_loopback_test send";
      if (!svcs_send_realtime(socket_id,Realtime)) $display("%s TEST FAIL",Test_name);
   endfunction : realtime_loopback_test
   
   function void shortreal_loopback_test(int socket_id);
      shortreal   Shortreal;
      string Test_name;
      
      Test_name = "client shortreal_loopback_test recv";
      if (!svcs_dpi_recv_shortreal(socket_id,Shortreal)) $display("%s TEST FAIL",Test_name);
      $display("\n %s Shortreal=%h(%f)",Test_name,Shortreal,Shortreal);
      Test_name = "client shortreal_loopback_test send";
      if (!svcs_dpi_send_shortreal(socket_id,Shortreal)) $display("%s TEST FAIL",Test_name);
   endfunction : shortreal_loopback_test

   function void string_loopback_test(int socket_id);
    
      string Test_name;
      int    size;
      int    Result_;
      
      String = `STRING_MESSAGE1;
      Test_name = "client string_loopback_test recv";
      
      
      //$display("SV before client String = %s",String);	
      if (svcs_dpi_recv_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
      $display("\n %s String = %s",Test_name,String);
      Test_name = "client string_loopback_test send";
      if (svcs_dpi_send_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
      
   endfunction : string_loopback_test

   function void shortV_loopback_test(int socket_id);
      begin
	 string Test_name;
	 int i;
         shortint ShortV[`V_SIZE];
	 Test_name = "client shortV_loopback_test";	 
	 
	 if(svcs_dpi_recv_shortV(socket_id,`V_SIZE,ShortV)<=0) $display("%s TEST FAIL",Test_name);
	 foreach (ShortV[i])$display("\n %s  ShortV[%0d] = %d",Test_name,i,ShortV[i]);
	 if(svcs_dpi_send_shortV(socket_id,`V_SIZE,ShortV)<=0) $display("%s TEST FAIL",Test_name);
      end
   endfunction : shortV_loopback_test
   
   function void  longV_loopback_test(int socket_id);
      begin
	 string Test_name;
	 longint LongV[`V_SIZE];
	 Test_name = "client longV_loopback_test";	 
	 
	 if(svcs_dpi_recv_longV(socket_id,`V_SIZE,LongV)<=0) $display("%s TEST FAIL",Test_name);
	 foreach (LongV[i])$display("\n %s  LongV[%0d] = %d",Test_name,i,LongV[i]);
	 if(svcs_dpi_send_longV(socket_id,`V_SIZE,LongV)<=0) $display("%s TEST FAIL",Test_name);
      end
   endfunction : longV_loopback_test

   function void realV_loopback_test(int socket_id);
      real  RealV[`V_SIZE];
      string Test_name;
      Test_name = "client realV_loopback_test";
      
      if (svcs_dpi_recv_realV (socket_id,`V_SIZE,RealV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (RealV[i])$display("\n %s  RealV[%0d] = %f",Test_name,i,RealV[i]);
      if (svcs_dpi_send_realV(socket_id,`V_SIZE,RealV)<= 0) $display("%s TEST FAIL",Test_name); 
   endfunction : realV_loopback_test
   
   function void shortrealV_loopback_test(int socket_id);
      shortreal  ShortrealV[`V_SIZE];
      string Test_name;
      Test_name = "client shortrealV_loopback_test";
      
      if (svcs_dpi_recv_shortrealV (socket_id,`V_SIZE,ShortrealV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (ShortrealV[i])$display("\n %s  ShortrealV[%0d] = %f",Test_name,i,ShortrealV[i]);
      if (svcs_dpi_send_shortrealV(socket_id,`V_SIZE,ShortrealV)<= 0) $display("%s TEST FAIL",Test_name); 
   endfunction : shortrealV_loopback_test
   /////////////////////////////////////////////////
   
 
/* -----\/----- EXCLUDED -----\/-----
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
   
   function void reg4sV_loopback_test(int socket_id);
      reg [1024:0] Reg4sV;
      string 	   Test_name;
      
      Test_name = "client reg4sV_loopback_test recv";
      //recv     
      Reg4sV = 'hz;
      if (svcs_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_recv_reg4s(socket_id,h_trnx,Reg4sV)<= 0) $display("%s TEST FAIL",Test_name);
      //$display("\n %s Reg4sV=%h(%h)",Test_name, Reg4sV,Reg4sV[132:0]);
      //send
      //Test_name = "client reg4sV_loopback_test send";
      if (svcs_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (svcs_dpi_hs_send_reg4s(socket_id,h_trnx,Reg4sV)<= 0)   $display("%s TEST FAIL",Test_name);
   endfunction : reg4sV_loopback_test
 -----/\----- EXCLUDED -----/\----- */
   
endmodule : svtest_sv2c_client