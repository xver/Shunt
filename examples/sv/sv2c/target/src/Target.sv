/*
============================================================================
 File        : Target.sv
 Version     : 1.0.1
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : TCP/IP SystemVerilog SHUNT
               All Types SystemVerilog examle  -Target(client)  
 History:
 1.0.0 - initial release
 1.0.1 - shunt-verilator integration 
         Version 1.0.1 : Verilator 3.916 2017-11-25 rev verilator_3_916
 ============================================================================
*/

/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */
`include "../../includes/cs_common.svh"

module automatic Target;
   
   import shunt_dpi_pkg::*;
   
   string String;
   int 	  Socket; 
   cs_header_t      h_trnx;
`ifndef NO_CS_DATA_HEADER_T
   cs_data_header_t h_data;
`endif
   
   
   initial
     begin
	
	int Result;
	
	Socket=0;
	Result=0;
	
        //#1000ns;
	
        //
	//String.toupper();	
	$display("Target: START");
	Socket = init_target(`MY_PORT, `MY_HOST);
	$display("Target: socket=%0d",Socket);
	
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
	string_loopback_test(Socket);
	shortV_loopback_test(Socket);
	longV_loopback_test(Socket);
	realV_loopback_test(Socket);
	shortrealV_loopback_test(Socket);
	integerV_loopback_test(Socket);
	shunt_dpi_close_socket(Socket);
	$finish;	
	$display("\nTarget: END");
	
     end // initial begin
   
   
   function int init_target(int portno,string hostname);
      int   socket_id;
      socket_id=0;
      socket_id = shunt_dpi_target_init(portno,hostname);
      return socket_id;
   endfunction : init_target
   
   //Functions:
   
   function void short_loopback_test(int socket_id);
      shortint Short;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_SHORT
 `ifndef NO_SHUNT_DPI_SEND_SHORT       
      Short ='hdead;
      
      Test_name = "\ntarget short_loopback_test recv";
      //recv
      if (shunt_dpi_recv_short (socket_id,Short)<= 0) $display("%s TEST FAIL",Test_name);
      $display("%s Short=%h",Test_name,Short);
      //send
      Test_name = "target short_loopback_test send";
      if (shunt_dpi_send_short(socket_id,Short)<= 0) $display("%s TEST FAIL",Test_name);
 `endif //  `ifndef NO_SHUNT_DPI_SEND_SHORT
`endif //  `ifndef NO_SHUNT_DPI_RECV_SHORT
   endfunction : short_loopback_test
   
   function void int_loopback_test(int socket_id);
      int      Int;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_INT
 `ifndef NO_SHUNT_DPI_SEND_INT       
      Int      ='hdead;
      
      Test_name = "\ntarget int_loopback_test recv";
      //recv
      if (shunt_dpi_recv_int (socket_id,Int)<= 0) $display("%s TEST FAIL",Test_name);
      $display("%s Int=%h",Test_name,Int);
      //send
      Test_name = "target int_loopback_test send";
      if (shunt_dpi_send_int(socket_id,Int)<= 0) $display("%s TEST FAIL",Test_name);
 `endif //  `ifndef NO_SHUNT_DPI_SEND_INT
`endif //  `ifndef NO_SHUNT_DPI_RECV_INT
   endfunction : int_loopback_test
   
   function void long_loopback_test(int socket_id);
      longint  Long;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_LONG
 `ifndef NO_SHUNT_DPI_SEND_LONG       
      Long ='hdead;
      
      Test_name = "\ntarget long_loopback_test recv";
      //recv
      if (shunt_dpi_recv_long (socket_id,Long)<= 0) $display("%s TEST FAIL",Test_name);
      $display("%s Long=%h",Test_name,Long);
      //send
      Test_name = "target long_loopback_test send";
      if (shunt_dpi_send_long(socket_id,Long)<= 0) $display("%s TEST FAIL",Test_name);
 `endif //  `ifndef NO_SHUNT_DPI_SEND_LONG
`endif //  `ifndef NO_SHUNT_DPI_RECV_LONG
   endfunction : long_loopback_test
   
   function void byte_loopback_test(int socket_id);
      byte     Byte;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_BYTE
 `ifndef NO_SHUNT_DPI_SEND_BYTE      
      
      Byte     ='hde;
      
      Test_name = "\ntarget byte_loopback_test recv";
      //recv
      if (shunt_dpi_recv_byte (socket_id,Byte)<= 0) $display("%s TEST FAIL",Test_name);
      $display("%s Byte=%h",Test_name,Byte);
      //send
      Test_name = "target byte_loopback_test send";
      if (shunt_dpi_send_byte(socket_id,Byte)<= 0) $display("%s TEST FAIL",Test_name);
 `endif //  `ifndef NO_SHUNT_DPI_SEND_BYTE
`endif //  `ifndef NO_SHUNT_DPI_RECV_BYTE
   endfunction : byte_loopback_test
   
   function void integer_loopback_test(int socket_id);
      integer  Integer;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_INTEGER
 `ifndef NO_SHUNT_DPI_SEND_INTEGER       
      Test_name = "target integer_loopback_test recv";
      //recv
      if (shunt_dpi_recv_integer (socket_id,Integer)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Integer=%h ",Test_name,Integer);
      //send
      Test_name = "target integer_loopback_test send";
      if (shunt_dpi_send_integer(socket_id,Integer)<= 0) $display("%s TEST FAIL",Test_name);
 `endif
`endif //  `ifndef NO_SHUNT_DPI_RECV_INTEGER
   endfunction : integer_loopback_test
   
   function void time_loopback_test(int socket_id);
      time     Time;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_TIME
 `ifndef NO_SHUNT_DPI_SEND_TIME       
      Test_name = "target time_loopback_test recv";
      //recv
      if (shunt_dpi_recv_time (socket_id,Time)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Time=%h ",Test_name,Time);
      //send
      Test_name = "target time_loopback_test send";
      if (shunt_dpi_send_time(socket_id,Time)<= 0) $display("%s TEST FAIL",Test_name);
 `endif
`endif //  `ifndef NO_SHUNT_DPI_RECV_TIME
   endfunction : time_loopback_test
   
   function void bit_loopback_test(int socket_id);
      bit      Bit;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_BIT
 `ifndef NO_SHUNT_DPI_SEND_BIT       
      Test_name = "target bit_loopback_test recv";
      //recv
      if (shunt_dpi_recv_bit (socket_id,Bit)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Bit=%h ",Test_name,Bit);
      //send
      Test_name = "target bit_loopback_test send";
      if (shunt_dpi_send_bit(socket_id,Bit)<= 0) $display("%s TEST FAIL",Test_name);
 `endif //  `ifndef NO_SHUNT_DPI_SEND_BIT
`endif //  `ifndef NO_SHUNT_DPI_RECV_BIT
   endfunction : bit_loopback_test
   
   function void reg_loopback_test(int socket_id);
      reg Reg  ;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_REG
 `ifndef NO_SHUNT_DPI_SEND_REG       
      Test_name = "target reg_loopback_test recv";
      //recv
      if (shunt_dpi_recv_reg (socket_id,Reg)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Reg=%h ",Test_name,Reg);
      //send
      Test_name = "target reg_loopback_test send";
      if (shunt_dpi_send_reg(socket_id,Reg)<= 0) $display("%s TEST FAIL",Test_name);
 `endif //  `ifndef NO_SHUNT_DPI_SEND_REG
`endif //  `ifndef NO_SHUNT_DPI_RECV_REG
   endfunction : reg_loopback_test
   
   function void logic_loopback_test(int socket_id);
      logic    Logic;
      string   Test_name;
      
`ifndef NO_SHUNT_DPI_RECV_LOGIC
 `ifndef NO_SHUNT_DPI_SEND_LOGIC       
      Test_name = "target logic_loopback_test recv";
      //recv
      if (shunt_dpi_recv_logic (socket_id,Logic)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s Logic=%h ",Test_name,Logic);
      //send
      Test_name = "target logic_loopback_test send";
      if (shunt_dpi_send_logic(socket_id,Logic)<= 0) $display("%s TEST FAIL",Test_name);
  `endif //  `ifndef NO_SHUNT_DPI_SEND_LOGIC
 `endif //  `ifndef NO_SHUNT_DPI_RECV_LOGIC
   endfunction : logic_loopback_test
   
   function void bitN_loopback_test(int socket_id);
      bit [1024:0] BitN;
      string 	   Test_name;
      
 `ifndef NO_SHUNT_DPI_HS_RECV_BITN
  `ifndef NO_SHUNT_DPI_HS_SEND_BITN      
      Test_name = "target bitN_loopback_test recv";
      //recv     
      BitN = 'hz;
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_recv_bitN(socket_id,h_trnx,BitN)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n%s BitN=%h ",Test_name,BitN);
      //send
      Test_name = "target bitN_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_bitN(socket_id,h_trnx,BitN)<= 0)   $display("%s TEST FAIL",Test_name);
  `endif //  `ifndef NO_SHUNT_DPI_HS_SEND_BITN
 `endif //  `ifndef NO_SHUNT_DPI_HS_RECV_BITN
   endfunction : bitN_loopback_test
   
   function void regN_loopback_test(int socket_id);
      reg [1024:0] RegN;
      string 	   Test_name;
      
 `ifndef NO_SHUNT_DPI_HS_RECV_REGN
  `ifndef NO_SHUNT_DPI_HS_SEND_REGN      
      Test_name = "target regN_loopback_test recv";
      //recv     
      RegN = 'hz;
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_recv_regN(socket_id,h_trnx,RegN)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n %s RegN=%h(%h)",Test_name, RegN,RegN[132:0]);
      //send
      Test_name = "target regN_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_regN(socket_id,h_trnx,RegN)<= 0)   $display("%s TEST FAIL",Test_name);
  `endif //  `ifndef NO_SHUNT_DPI_HS_SEND_REGN
 `endif //  `ifndef NO_SHUNT_DPI_HS_RECV_REGN
   endfunction : regN_loopback_test
   
   function void logicN_loopback_test(int socket_id);
      logic [1024:0] LogicN;
      string 	     Test_name;
      
 `ifndef NO_SHUNT_DPI_HS_RECV_LOGICN
  `ifndef NO_SHUNT_DPI_HS_SEND_LOGICN      
      Test_name = "target logicN_loopback_test recv";
      //recv     
      LogicN = 'hz;
      if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_recv_logicN(socket_id,h_trnx,LogicN)<= 0) $display("%s TEST FAIL",Test_name);
      $display("\n %s LogicN=%h(%h)",Test_name, LogicN,LogicN[132:0]);
      //send
      Test_name = "target logicN_loopback_test send";
      if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
      if (shunt_dpi_hs_send_logicN(socket_id,h_trnx,LogicN)<= 0)   $display("%s TEST FAIL",Test_name);
  `endif //  `ifndef NO_SHUNT_DPI_HS_SEND_LOGICN
 `endif //  `ifndef NO_SHUNT_DPI_HS_RECV_LOGICN
   endfunction : logicN_loopback_test
   
   function void real_loopback_test(int socket_id);
      real 	     Real;
      string 	     Test_name;
      
 `ifndef NO_SHUNT_DPI_RECV_REAL
  `ifndef NO_SHUNT_DPI_SEND_REAL      
      Test_name = "target real_loopback_test recv";
      /* verilator lint_off WIDTH */
      if (!shunt_dpi_recv_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
      
      $display("\n %s Real=%h(%f)",Test_name,Real,Real);
      Test_name = "target real_loopback_test send";
      if (!shunt_dpi_send_real(socket_id,Real)) $display("%s TEST FAIL",Test_name);
      /* verilator lint_on WIDTH */
   `endif //  `ifndef NO_SHUNT_DPI_SEND_REAL
  `endif //  `ifndef NO_SHUNT_DPI_RECV_REAL
   endfunction : real_loopback_test
   
   function void shortreal_loopback_test(int socket_id);
  `ifndef NO_SHUNT_DPI_RECV_SHORTREAL
   `ifndef NO_SHUNT_DPI_SEND_SHORTREAL       
      shortreal      Shortreal;
      string 	     Test_name;
      
      Test_name = "target shortreal_loopback_test recv";
      if (!shunt_dpi_recv_shortreal(socket_id,Shortreal)) $display("%s TEST FAIL",Test_name);
      $display("\n %s Shortreal=%h(%f)",Test_name,Shortreal,Shortreal);
      Test_name = "target shortreal_loopback_test send";
      if (!shunt_dpi_send_shortreal(socket_id,Shortreal)) $display("%s TEST FAIL",Test_name);
     `endif //  `ifndef NO_SHUNT_DPI_SEND_SHORTREAL
  `endif //  `ifndef NO_SHUNT_DPI_RECV_SHORTREAL
   endfunction : shortreal_loopback_test
   
   function void string_loopback_test(int socket_id);
      
      string 	     Test_name;
      int 	     size;
      int 	     Result_;
      
  `ifndef NO_SHUNT_DPI_RECV_STRING
   `ifndef NO_SHUNT_DPI_SEND_STRING      
      String 	     = `STRING_MESSAGE1;
      Test_name = "target string_loopback_test recv";
      
      if (shunt_dpi_recv_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
      $display("\n %s String = %s",Test_name,String);
      Test_name = "target string_loopback_test send";
      if (shunt_dpi_send_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
    `endif //  `ifndef NO_SHUNT_DPI_SEND_STRING
   `endif //  `ifndef NO_SHUNT_DPI_RECV_STRING
   endfunction : string_loopback_test
   
   function void shortV_loopback_test(int socket_id);
      begin
	 string Test_name;
	 int 	i;
         shortint ShortV[`V_SIZE];
	 
   `ifndef NO_SHUNT_DPI_RECV_SHORTV
    `ifndef NO_SHUNT_DPI_SEND_SHORTV	 
	 Test_name = "target shortV_loopback_test";	 
	 
	 if(shunt_dpi_recv_shortV(socket_id,`V_SIZE,ShortV)<=0) $display("%s TEST FAIL",Test_name);
	 foreach (ShortV[i])$display("\n %s  ShortV[%0d] = %d",Test_name,i,ShortV[i]);
	 if(shunt_dpi_send_shortV(socket_id,`V_SIZE,ShortV)<=0) $display("%s TEST FAIL",Test_name);
    `endif //`ifndef NO_SHUNT_DPI_RECV_SHORTV
   `endif  //`ifndef NO_SHUNT_DPI_SEND_SHORTV
      end
   endfunction : shortV_loopback_test
   
   function void  longV_loopback_test(int socket_id);
      begin
	 string Test_name;
	 longint LongV[`V_SIZE];
	 
   `ifndef NO_SHUNT_DPI_RECV_LONGV
    `ifndef NO_SHUNT_DPI_SEND_LONGV	 
	 Test_name = "target longV_loopback_test";	 
	 
	 if(shunt_dpi_recv_longV(socket_id,`V_SIZE,LongV)<=0) $display("%s TEST FAIL",Test_name);
	 foreach (LongV[i])$display("\n %s  LongV[%0d] = %d",Test_name,i,LongV[i]);
	 if(shunt_dpi_send_longV(socket_id,`V_SIZE,LongV)<=0) $display("%s TEST FAIL",Test_name);
    `endif // `ifndef NO_SHUNT_DPI_RECV_LONGV
   `endif  // `ifndef NO_SHUNT_DPI_SEND_LONGV
  
      end
   endfunction : longV_loopback_test
   
   function void realV_loopback_test(int socket_id);
      real 	 RealV[`V_SIZE];
      string 	 Test_name;
      
   `ifndef NO_SHUNT_DPI_RECV_REALV
    `ifndef NO_SHUNT_DPI_SEND_REALV       
      Test_name = "target realV_loopback_test";
      
      if (shunt_dpi_recv_realV (socket_id,`V_SIZE,RealV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (RealV[i])$display("\n %s  RealV[%0d] = %f",Test_name,i,RealV[i]);
      if (shunt_dpi_send_realV(socket_id,`V_SIZE,RealV)<= 0) $display("%s TEST FAIL",Test_name);
    `endif // `ifndef NO_SHUNT_DPI_RECV_REALV
   `endif // `ifndef NO_SHUNT_DPI_SEND_REALV       
   endfunction : realV_loopback_test
   
   function void shortrealV_loopback_test(int socket_id);
   `ifndef NO_SHUNT_DPI_RECV_SHORTREALV
    `ifndef NO_SHUNT_DPI_SEND_SHORTREALV        
      shortreal  ShortrealV[`V_SIZE];
      string 	 Test_name;
      
      Test_name = "target shortrealV_loopback_test";
      
      if (shunt_dpi_recv_shortrealV (socket_id,`V_SIZE,ShortrealV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (ShortrealV[i])$display("\n %s  ShortrealV[%0d] = %f",Test_name,i,ShortrealV[i]);
      if (shunt_dpi_send_shortrealV(socket_id,`V_SIZE,ShortrealV)<= 0) $display("%s TEST FAIL",Test_name);
    `endif //  `ifndef NO_SHUNT_DPI_SEND_SHORTREALV
   `endif //  `ifndef NO_SHUNT_DPI_RECV_SHORTREALV
   endfunction : shortrealV_loopback_test
   
   function void integerV_loopback_test(int socket_id);
      integer 	 IntegerV[`V_SIZE];
      string 	 Test_name;
      
   `ifndef NO_SHUNT_DPI_RECV_INTEGERV
    `ifndef NO_SHUNT_DPI_SEND_INTEGERV       
      Test_name = "target integerV_loopback_test";
      
      if (shunt_dpi_recv_integerV (socket_id,`V_SIZE,IntegerV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (IntegerV[i])$display("\n %s  IntegerV[%0d] = %h",Test_name,i,IntegerV[i]);
      if (shunt_dpi_send_integerV(socket_id,`V_SIZE,IntegerV)<= 0) $display("%s TEST FAIL",Test_name);
    `endif //  `ifndef NO_SHUNT_DPI_SEND_INTEGERV
   `endif //  `ifndef NO_SHUNT_DPI_RECV_INTEGERV
   endfunction : integerV_loopback_test
   
   
endmodule : Target
