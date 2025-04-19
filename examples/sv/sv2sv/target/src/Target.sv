/*
============================================================================
Title: Target.sv

 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : TCP/IP SystemVerilog SHUNT
               All Types SystemVerilog examle  -Target(client)
 ============================================================================
*/

/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */

/**
 * Package: cs_common
 * 
 * Common macro and parameter definitions for the client-server implementation
 */
`include "../../includes/cs_common.svh"

/**
 * Module: Target
 * 
 * TCP/IP SystemVerilog SHUNT Target module for SystemVerilog-to-SystemVerilog communication
 * 
 * This module serves as the client in a client-server communication model
 * between two SystemVerilog domains. It connects to the Initiator and processes
 * a comprehensive suite of loopback tests for all SystemVerilog data types.
 * 
 * The module receives data from the Initiator, then sends it back to verify
 * bidirectional communication over TCP/IP.
 */
module automatic Target;

   import shunt_dpi_pkg::*;

   /**
    * Variable: String
    * String variable used for string data type tests
    */
   string String;
   
   /**
    * Variable: Socket
    * Stores the socket descriptor for TCP/IP communication
    */
   int    Socket;
   
   /**
    * Variable: h_trnx
    * Communication protocol header for transaction data
    */
   cs_header_t      h_trnx;

`ifndef NO_CS_DATA_HEADER_T
   /**
    * Variable: h_data
    * Communication protocol header for data payload
    * 
    * Only defined when NO_CS_DATA_HEADER_T is not defined
    */
   cs_data_header_t h_data;
`endif

   /**
    * Initial block: Main Execution Flow
    *
    * Establishes socket connection to the Initiator and runs a series
    * of loopback tests for different SystemVerilog data types by
    * receiving data and sending it back.
    */
   initial
     begin

    /**
     * Variable: Result
     * Stores return values from function calls to check for success
     */
    int Result;

    Socket=0;
    Result=0;

        //#1000ns;

        //
    //String.toupper();
    $display("Target: START");
    Socket = init_target(0, `MY_HOST);
    //Socket = init_target(`MY_PORT, `MY_HOST);
    $display("Target: socket=%0d",Socket);

    header_loopback_test(Socket);
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
    intV_loopback_test(Socket);
    pkt_longV_loopback_test(Socket);
    shunt_dpi_close_socket(Socket);
    $finish;
    $display("\nTarget: END");

     end // initial begin


   /**
    * Function: init_target
    *
    * Initializes the target (client) side of the socket connection
    *
    * Parameters:
    *   portno    - Port number for the socket connection
    *   hostname  - Host name or IP address to connect to
    *
    * Returns:
    *   socket_id - Socket identifier for the established connection
    */
   function int init_target(int portno,string hostname);
      int   socket_id;
      socket_id=0;
      socket_id = shunt_dpi_target_init(portno,hostname);
      return socket_id;
   endfunction : init_target

   //Functions:

   /**
    * Function: short_loopback_test
    *
    * Performs a loopback test for shortint data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a shortint from the initiator and sends it back
    */
   function void short_loopback_test(int socket_id);
      /**
       * Variable: Short
       * Shortint variable for storing the received/sent data
       */
      shortint Short;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: int_loopback_test
    *
    * Performs a loopback test for int data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives an int from the initiator and sends it back
    */
   function void int_loopback_test(int socket_id);
      /**
       * Variable: Int
       * Int variable for storing the received/sent data
       */
      int      Int;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: long_loopback_test
    *
    * Performs a loopback test for longint data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a longint from the initiator and sends it back
    */
   function void long_loopback_test(int socket_id);
      /**
       * Variable: Long
       * Longint variable for storing the received/sent data
       */
      longint  Long;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: byte_loopback_test
    *
    * Performs a loopback test for byte data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a byte from the initiator and sends it back
    */
   function void byte_loopback_test(int socket_id);
      /**
       * Variable: Byte
       * Byte variable for storing the received/sent data
       */
      byte     Byte;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: integer_loopback_test
    *
    * Performs a loopback test for integer data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives an integer from the initiator and sends it back
    */
   function void integer_loopback_test(int socket_id);
      /**
       * Variable: Integer
       * Integer variable for storing the received/sent data
       */
      integer  Integer;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: time_loopback_test
    *
    * Performs a loopback test for time data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a time value from the initiator and sends it back
    */
   function void time_loopback_test(int socket_id);
      /**
       * Variable: Time
       * Time variable for storing the received/sent data
       */
      time     Time;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: bit_loopback_test
    *
    * Performs a loopback test for bit data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a bit value from the initiator and sends it back
    */
   function void bit_loopback_test(int socket_id);
      /**
       * Variable: Bit
       * Bit variable for storing the received/sent data
       */
      bit      Bit;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: reg_loopback_test
    *
    * Performs a loopback test for reg data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a reg value from the initiator and sends it back
    */
   function void reg_loopback_test(int socket_id);
      /**
       * Variable: Reg
       * Reg variable for storing the received/sent data
       */
      reg Reg  ;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: logic_loopback_test
    *
    * Performs a loopback test for logic data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a logic value from the initiator and sends it back
    */
   function void logic_loopback_test(int socket_id);
      /**
       * Variable: Logic
       * Logic variable for storing the received/sent data
       */
      logic    Logic;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
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

   /**
    * Function: bitN_loopback_test
    *
    * Performs a loopback test for multi-bit bit vector data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a bit vector from the initiator and sends it back
    */
   function void bitN_loopback_test(int socket_id);
      /**
       * Variable: BitN
       * Bit vector variable for storing the received/sent data
       */
      bit [1024:0] BitN;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string       Test_name;

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

   /**
    * Function: regN_loopback_test
    *
    * Performs a loopback test for multi-bit reg vector data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a reg vector from the initiator and sends it back
    */
   function void regN_loopback_test(int socket_id);
      /**
       * Variable: RegN
       * Reg vector variable for storing the received/sent data
       */
      reg [1024:0] RegN;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string       Test_name;

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

   /**
    * Function: logicN_loopback_test
    *
    * Performs a loopback test for multi-bit logic vector data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a logic vector from the initiator and sends it back
    */
   function void logicN_loopback_test(int socket_id);
      /**
       * Variable: LogicN
       * Logic vector variable for storing the received/sent data
       */
      logic [1024:0] LogicN;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string         Test_name;

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

   /**
    * Function: real_loopback_test
    *
    * Performs a loopback test for real data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a real value from the initiator and sends it back
    */
   function void real_loopback_test(int socket_id);
      /**
       * Variable: Real
       * Real variable for storing the received/sent data
       */
      real       Real;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string         Test_name;

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

   /**
    * Function: shortreal_loopback_test
    *
    * Performs a loopback test for shortreal data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a shortreal value from the initiator and sends it back
    */
   function void shortreal_loopback_test(int socket_id);
  `ifndef NO_SHUNT_DPI_RECV_SHORTREAL
   `ifndef NO_SHUNT_DPI_SEND_SHORTREAL
      /**
       * Variable: Shortreal
       * Shortreal variable for storing the received/sent data
       */
      shortreal      Shortreal;
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string         Test_name;

      Test_name = "target shortreal_loopback_test recv";
      if (!shunt_dpi_recv_shortreal(socket_id,Shortreal)) $display("%s TEST FAIL",Test_name);
      $display("\n %s Shortreal=%h(%f)",Test_name,Shortreal,Shortreal);
      Test_name = "target shortreal_loopback_test send";
      if (!shunt_dpi_send_shortreal(socket_id,Shortreal)) $display("%s TEST FAIL",Test_name);
     `endif //  `ifndef NO_SHUNT_DPI_SEND_SHORTREAL
  `endif //  `ifndef NO_SHUNT_DPI_RECV_SHORTREAL
   endfunction : shortreal_loopback_test

   /**
    * Function: string_loopback_test
    *
    * Performs a loopback test for string data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a string from the initiator and sends it back
    */
   function void string_loopback_test(int socket_id);

      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string         Test_name;
      
      /**
       * Variable: size
       * Size of the string to be received/sent
       */
      int        size;
      
      /**
       * Variable: Result_
       * Result of string operations
       */
      int        Result_;

  `ifndef NO_SHUNT_DPI_RECV_STRING
   `ifndef NO_SHUNT_DPI_SEND_STRING
      String         = `STRING_MESSAGE1;
      Test_name = "target string_loopback_test recv";

      if (shunt_dpi_recv_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
      $display("\n %s String = %s",Test_name,String);
      Test_name = "target string_loopback_test send";
      if (shunt_dpi_send_string(socket_id,String.len(),String)<=0) $display("%s TEST FAIL",Test_name);
    `endif //  `ifndef NO_SHUNT_DPI_SEND_STRING
   `endif //  `ifndef NO_SHUNT_DPI_RECV_STRING
   endfunction : string_loopback_test

   /**
    * Function: shortV_loopback_test
    *
    * Performs a loopback test for shortint array data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a shortint array from the initiator and sends it back
    */
   function void shortV_loopback_test(int socket_id);
      begin
     /**
      * Variable: Test_name
      * String identifier for the test being performed
      */
     string Test_name;
     
     /**
      * Variable: ShortV
      * Array of shortint values for loopback testing
      */
     shortint ShortV[`V_SIZE];

   `ifndef NO_SHUNT_DPI_RECV_SHORTV
    `ifndef NO_SHUNT_DPI_SEND_SHORTV
     Test_name = "target shortV_loopback_test";

     if(shunt_dpi_recv_shortV(socket_id,`V_SIZE,ShortV)<=0) $display("%s TEST FAIL",Test_name);
     //foreach (ShortV[shortV_i])$display("\n %s  ShortV[%0d] = %d",Test_name,shortV_i,ShortV[shortV_i]);
     if(shunt_dpi_send_shortV(socket_id,`V_SIZE,ShortV)<=0) $display("%s TEST FAIL",Test_name);
    `endif //`ifndef NO_SHUNT_DPI_RECV_SHORTV
   `endif  //`ifndef NO_SHUNT_DPI_SEND_SHORTV
      end
   endfunction : shortV_loopback_test


   /**
    * Function: intV_loopback_test
    *
    * Performs a loopback test for int array data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives an int array from the initiator and sends it back
    */
   function void intV_loopback_test(int socket_id);
      begin
     /**
      * Variable: Test_name
      * String identifier for the test being performed
      */
     string Test_name;
     
     /**
      * Variable: IntV
      * Array of int values for loopback testing
      */
     int IntV[`V_SIZE];

   `ifndef NO_SHUNT_DPI_RECV_INTV
    `ifndef NO_SHUNT_DPI_SEND_INTV
     Test_name = "target intV_loopback_test";

     if(shunt_dpi_recv_intV(socket_id,`V_SIZE,IntV)<=0) $display("%s TEST FAIL",Test_name);
     //foreach (IntV[intV_i])$display("\n %s  IntV[%0d] = %d",Test_name,intV_i,IntV[intV_i]);
     if(shunt_dpi_send_intV(socket_id,`V_SIZE,IntV)<=0) $display("%s TEST FAIL",Test_name);
    `endif //`ifndef NO_SHUNT_DPI_RECV_INTV
   `endif  //`ifndef NO_SHUNT_DPI_SEND_INTV
      end
   endfunction : intV_loopback_test



   /**
    * Function: longV_loopback_test
    *
    * Performs a loopback test for longint array data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a longint array from the initiator and sends it back
    */
   function void  longV_loopback_test(int socket_id);
      begin
     /**
      * Variable: Test_name
      * String identifier for the test being performed
      */
     string Test_name;
     
     /**
      * Variable: LongV
      * Array of longint values for loopback testing
      */
     longint LongV[`V_SIZE];

   `ifndef NO_SHUNT_DPI_RECV_LONGV
    `ifndef NO_SHUNT_DPI_SEND_LONGV
     Test_name = "target longV_loopback_test";

     if(shunt_dpi_recv_longV(socket_id,`V_SIZE,LongV)<=0) $display("%s TEST FAIL",Test_name);
     //foreach (LongV[i])$display("\n %s  LongV[%0d] = %d",Test_name,i,LongV[i]);
     if(shunt_dpi_send_longV(socket_id,`V_SIZE,LongV)<=0) $display("%s TEST FAIL",Test_name);
    `endif // `ifndef NO_SHUNT_DPI_RECV_LONGV
   `endif  // `ifndef NO_SHUNT_DPI_SEND_LONGV

      end
   endfunction : longV_loopback_test

   /**
    * Function: realV_loopback_test
    *
    * Performs a loopback test for real array data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a real array from the initiator and sends it back
    */
   function void realV_loopback_test(int socket_id);
      /**
       * Variable: RealV
       * Array of real values for loopback testing
       */
      real   RealV[`V_SIZE];
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string     Test_name;

   `ifndef NO_SHUNT_DPI_RECV_REALV
    `ifndef NO_SHUNT_DPI_SEND_REALV
      Test_name = "target realV_loopback_test";

      if (shunt_dpi_recv_realV (socket_id,`V_SIZE,RealV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (RealV[i])$display("\n %s  RealV[%0d] = %f",Test_name,i,RealV[i]);
      if (shunt_dpi_send_realV(socket_id,`V_SIZE,RealV)<= 0) $display("%s TEST FAIL",Test_name);
    `endif // `ifndef NO_SHUNT_DPI_RECV_REALV
   `endif // `ifndef NO_SHUNT_DPI_SEND_REALV
   endfunction : realV_loopback_test

   /**
    * Function: shortrealV_loopback_test
    *
    * Performs a loopback test for shortreal array data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a shortreal array from the initiator and sends it back
    */
   function void shortrealV_loopback_test(int socket_id);
   `ifndef NO_SHUNT_DPI_RECV_SHORTREALV
    `ifndef NO_SHUNT_DPI_SEND_SHORTREALV
      /**
       * Variable: ShortrealV
       * Array of shortreal values for loopback testing
       */
      shortreal  ShortrealV[`V_SIZE];
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string     Test_name;

      Test_name = "target shortrealV_loopback_test";

      if (shunt_dpi_recv_shortrealV (socket_id,`V_SIZE,ShortrealV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (ShortrealV[i])$display("\n %s  ShortrealV[%0d] = %f",Test_name,i,ShortrealV[i]);
      if (shunt_dpi_send_shortrealV(socket_id,`V_SIZE,ShortrealV)<= 0) $display("%s TEST FAIL",Test_name);
    `endif //  `ifndef NO_SHUNT_DPI_SEND_SHORTREALV
   `endif //  `ifndef NO_SHUNT_DPI_RECV_SHORTREALV
   endfunction : shortrealV_loopback_test

   /**
    * Function: integerV_loopback_test
    *
    * Performs a loopback test for integer array data type
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives an integer array from the initiator and sends it back
    */
   function void integerV_loopback_test(int socket_id);
      /**
       * Variable: IntegerV
       * Array of integer values for loopback testing
       */
      integer    IntegerV[`V_SIZE];
      
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string     Test_name;

   `ifndef NO_SHUNT_DPI_RECV_INTEGERV
    `ifndef NO_SHUNT_DPI_SEND_INTEGERV
      Test_name = "target integerV_loopback_test";
      foreach (IntegerV[i])IntegerV[i]=-1;
      foreach (IntegerV[i])$display("\n %s  IntegerV[%0d] = %h",Test_name,i,IntegerV[i]);
      if (shunt_dpi_recv_integerV (socket_id,`V_SIZE,IntegerV)<= 0) $display("%s TEST FAIL",Test_name);
      foreach (IntegerV[i])$display("\n %s  IntegerV[%0d] = %h",Test_name,i,IntegerV[i]);
      if (shunt_dpi_send_integerV(socket_id,`V_SIZE,IntegerV)<= 0) $display("%s TEST FAIL",Test_name);

    `endif //  `ifndef NO_SHUNT_DPI_SEND_INTEGERV
   `endif //  `ifndef NO_SHUNT_DPI_RECV_INTEGERV
   endfunction : integerV_loopback_test

   /**
    * Function: pkt_longV_loopback_test
    *
    * Performs a loopback test for longint array data type with packet header
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a longint array with packet header from the initiator and sends it back
    */
   function void  pkt_longV_loopback_test(int socket_id);
      begin
     /**
      * Variable: Test_name
      * String identifier for the test being performed
      */
     string Test_name;
     
     /**
      * Variable: Pkt_longv
      * Array of longint values for packet loopback testing
      */
     longint Pkt_longv[`V_SIZE];
     
     /**
      * Variable: h_
      * Communication protocol header for the transaction
      */
     cs_header_t      h_;
     
   `ifndef NO_SHUNT_DPI_RECV_PKT_LONGV
    `ifndef NO_SHUNT_DPI_SEND_PKT_LONGV
     Test_name = "target pkt_longv_loopback_test";
     //$display("\n %s  h_trnx.n_payloads = %0d",Test_name, h_.n_payloads);
     h_trnx.trnx_type = 'h101;
     h_trnx.trnx_id   = 'h102;//{$random,$random};
     h_trnx.data_type = shunt_dpi_hash("SHUNT_LONGINT");
     h_trnx.n_payloads = `V_SIZE;
     if(shunt_dpi_recv_pkt_longV(socket_id,h_trnx,Pkt_longv)<=0) $display("%s TEST FAIL",Test_name);
     //foreach (Pkt_longv[i])$display("\n %s  Pkt_longv[%0d] = %d",Test_name,i,Pkt_longv[i]);
     if(shunt_dpi_send_pkt_longV(socket_id,h_trnx,Pkt_longv)<=0) $display("%s TEST FAIL",Test_name);

    `endif // `ifndef NO_SHUNT_DPI_RECV_PKT_LONGV
   `endif  // `ifndef NO_SHUNT_DPI_SEND_PKT_LONGV
      end
   endfunction: pkt_longV_loopback_test
   
   /**
    * Function: header_loopback_test
    *
    * Performs a loopback test for the transaction header
    *
    * Parameters:
    *   socket_id - Socket identifier for the connection
    *
    * Returns:
    *   void
    *
    * Notes:
    *   Receives a header from the initiator and sends it back
    */
   function void header_loopback_test(int socket_id);
      /**
       * Variable: Test_name
       * String identifier for the test being performed
       */
      string     Test_name;

       Test_name = "header_loopback_test recv";
       //recv
       if (shunt_dpi_recv_header (socket_id,h_trnx)<= 0) $display("%s TEST FAIL",Test_name);
       //send
       Test_name = "header_loopback_test send";
       if (shunt_dpi_send_header(socket_id,h_trnx)  <= 0) $display("%s TEST FAIL",Test_name);
    endfunction : header_loopback_test

   /**
    * Function: print_shunt_header
    *
    * Utility function to print the contents of a shunt header structure
    *
    * Parameters:
    *   h_       - cs_header_t structure to print
    *   name_in  - Optional name to identify the header in output
    *   i_am     - String identifier for the entity printing (e.g., "Target")
    *
    * Returns:
    *   void
    */
    function automatic void print_shunt_header(cs_header_t h_,string name_in="",string i_am);
      //   typedef struct{
      // longint     trnx_type;
      // longint     trnx_id;
      // longint     data_type;
      // int     n_payloads;
      //} cs_header_t;
      $display("\n%s  %s.trnx_type  = %0h",i_am,name_in, h_.trnx_type);
      $display("\n%s  %s.trnx_id    = %0h",i_am,name_in, h_.trnx_id);
      $display("\n%s  %s.data_type  = %0h",i_am,name_in, h_.data_type);
      $display("\n%s  %s.n_payloads = %0d",i_am,name_in, h_.n_payloads);
   endfunction : print_shunt_header

endmodule : Target
