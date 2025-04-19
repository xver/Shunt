/*
 ============================================================================
Title: Initiator.sv

 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : TCP/IP SystemVerilog SHUNT
 All Types SystemVerilog example  -Initiator(server)

 ============================================================================
 */

/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */
/* verilator lint_off VARHIDDEN */

/**
 * Package: cs_common
 * 
 * Common macro and parameter definitions for the client-server implementation
 */
`include "../../includes/cs_common.svh"

/**
 * Module: Initiator
 * 
 * TCP/IP SystemVerilog SHUNT Initiator module for SystemVerilog-to-Python communication
 * 
 * This module serves as the server in a client-server communication model
 * between SystemVerilog and Python domains. It demonstrates a comprehensive testing
 * of all supported data types over TCP/IP.
 * 
 * The module initializes a socket connection and performs loopback tests
 * for a wide range of data types to verify bidirectional communication.
 */
module automatic Initiator;

  import shunt_dpi_pkg::*;

  /**
   * Variable: Socket
   * Socket descriptor for TCP/IP communication
   */
  int         Socket;
  
  /**
   * Variable: Pass
   * Test pass/fail status flag
   */
  int         Pass;

  /**
   * Variable: h_trnx_exp
   * Expected transaction header for data validation
   */
  cs_header_t h_trnx_exp;
  
  /**
   * Variable: h_trnx_act
   * Actual transaction header received from the target
   */
  cs_header_t h_trnx_act;

`ifndef NO_CS_DATA_HEADER_T
  /**
   * Variable: h_data_exp
   * Expected data header for data validation
   * 
   * Only defined when NO_CS_DATA_HEADER_T is not defined
   */
  cs_data_header_t h_data_exp;
  
  /**
   * Variable: h_data_act
   * Actual data header received from the target
   * 
   * Only defined when NO_CS_DATA_HEADER_T is not defined
   */
  cs_data_header_t h_data_act;
`endif

  /**
   * Initial block: Main Execution Flow
   *
   * Establishes socket connection and runs a series of loopback tests
   * for different SystemVerilog data types supported by Python interface
   */
  initial begin
    /**
     * Variable: Status
     * Test status message
     */
    string Status;
    
    /**
     * Variable: Test_name
     * Current test name for reporting
     */
    string Test_name;

    Pass   = 1;
    Socket = 0;

    $display("Initiator: START");

    Test_name = "\tinit_initiator";
    $display("\n Test %s start", Test_name);
    Socket = init_initiator(0);
    //Socket = init_initiator(`MY_PORT);
    /* verilator lint_off WIDTH */
    if (!Socket) Pass = 0;
    /* verilator lint_on WIDTH */
    $display("\tInitiator: socket=%0d", Socket);
    print_status(Test_name, Pass);


    Test_name = "\theader_loopback loopback";
    $display("\n Test %s start", Test_name);
    Pass = header_loopback_test(Socket);
    print_status(Test_name, Pass);

`ifndef NO_SHUNT_DPI_SEND_SHORT
`ifndef NO_SHUNT_DPI_RECV_SHORT
    Test_name = "\tshort loopback";
    $display("\n Test %s start", Test_name);
    Pass = short_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_LONG
`ifndef NO_SHUNT_DPI_RECV_LONG
    Test_name = "\tint loopback";
    $display("\n Test %s start", Test_name);

    Pass = int_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_LONG
`ifndef NO_SHUNT_DPI_RECV_LONG
    Test_name = "\tlong loopback";
    $display("\n Test %s start", Test_name);

    Pass = long_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_BYTE
`ifndef NO_SHUNT_DPI_RECV_BYTE
    Test_name = "\tbyte loopback";
    $display("\n Test %s start", Test_name);

    Pass = byte_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_INTEGER
`ifndef NO_SHUNT_DPI_RECV_INTEGER
    Test_name = "\tinteger loopback";
    $display("\n Test %s start", Test_name);

    Pass = integer_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif


`ifndef NO_SHUNT_DPI_SEND_TIME
`ifndef NO_SHUNT_DPI_RECV_TIME
    Test_name = "\ttime loopback";
    $display("\n Test %s start", Test_name);

    Pass = time_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif


`ifndef NO_SHUNT_DPI_SEND_BIT
`ifndef NO_SHUNT_DPI_RECV_BIT
    Test_name = "\tbit_loopback";
    $display("\n Test %s start", Test_name);

    Pass = bit_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_REG
`ifndef NO_SHUNT_DPI_RECV_REG
    Test_name = "\treg_loopback";
    $display("\n Test %s start", Test_name);

    Pass = reg_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif


`ifndef NO_SHUNT_DPI_SEND_LOGIC
`ifndef NO_SHUNT_DPI_RECV_LOGIC
    Test_name = "\tlogic_loopback";
    $display("\n Test %s start", Test_name);

    Pass = logic_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif


`ifndef NO_SHUNT_DPI_HS_SEND_BITN
`ifndef NO_SHUNT_DPI_HS_RECV_BITN
    Test_name = "\tbitN_loopback";
    $display("\n Test %s start", Test_name);

    Pass = bitN_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

/* TODO N/A
`ifndef NO_SHUNT_DPI_HS_SEND_REGN
`ifndef NO_SHUNT_DPI_HS_RECV_REGN
    Test_name = "\tregN_loopback";
    $display("\n Test %s start", Test_name);

    Pass = regN_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_HS_SEND_LOGICN
`ifndef NO_SHUNT_DPI_HS_RECV_LOGICN
    Test_name = "\tlogicN_loopback";
    $display("\n Test %s start", Test_name);

    Pass = logicN_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif
*/

`ifndef NO_SHUNT_DPI_SEND_REAL
`ifndef NO_SHUNT_DPI_RECV_REAL
    Test_name = "\treal_loopback";
    $display("\n Test %s start", Test_name);

    Pass = real_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif
/*
`ifndef NO_SHUNT_DPI_SEND_SHORTREAL
`ifndef NO_SHUNT_DPI_RECV_SHORTREAL
    Test_name = "\tshortreal_loopback";
    $display("\n Test %s start", Test_name);

    Pass = shortreal_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif
*/
`ifndef NO_SHUNT_DPI_SEND_STRING
`ifndef NO_SHUNT_DPI_RECV_STRING

    Test_name = "\tstring_loopback";
    $display("\n Test %s start", Test_name);

    Pass = string_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif
/*
`ifndef NO_SHUNT_DPI_SEND_SHORTV
`ifndef NO_SHUNT_DPI_RECV_SHORTV
    Test_name = "\tshortV loopback";
    $display("\n Test %s start", Test_name);

    Pass = shortV_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_LONGV
`ifndef NO_SHUNT_DPI_RECV_LONGV
    Test_name = "\tlongV loopback";
    $display("\n Test %s start", Test_name);

    Pass = longV_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_REALV
`ifndef NO_SHUNT_DPI_RECV_REALV
    Test_name = "\trealV loopback";
    $display("\n Test %s start", Test_name);

    Pass = realV_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_SHORTREALV
`ifndef NO_SHUNT_DPI_RECV_SHORTREALV
    Test_name = "\tshortrealV loopback";
    $display("\n Test %s start", Test_name);

    Pass = shortrealV_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_INTEGERV
`ifndef NO_SHUNT_DPI_RECV_INTEGERV
    Test_name = "\tintegerV loopback";
    $display("\n Test %s start", Test_name);

    Pass = integerV_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_INTV
`ifndef NO_SHUNT_DPI_RECV_INTV
    Test_name = "\tintV loopback";
    $display("\n Test %s start", Test_name);

    Pass = intv_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif

`ifndef NO_SHUNT_DPI_SEND_PKT_LONGV
`ifndef NO_SHUNT_DPI_RECV_PKT_LONGV
    Test_name = "\tpkt LongintV loopback";
    $display("\n Test %s start", Test_name);

    Pass = pkt_longV_loopback_test(Socket);
    print_status(Test_name, Pass);
`endif
`endif
*/
    Test_name = "TEST SV2PY Initiator";
    print_status(Test_name, Pass);
    shunt_dpi_close_socket(Socket);
    $finish;
  end

  //Functions:

  /**
   * Function: init_initiator
   * 
   * Initializes the initiator (server) socket for TCP/IP communication
   * 
   * Parameters:
   *   portno - Port number to listen on. If 0, uses the default port.
   * 
   * Returns:
   *   socket_id - Socket descriptor for established connection
   */
  function int init_initiator(int portno);
    begin
      int socket_id;
      socket_id = 0;
      socket_id = shunt_dpi_initiator_init(portno);
      return socket_id;
    end
  endfunction : init_initiator


  /**
   * Function: short_loopback_test
   * 
   * Tests the loopback functionality for short (16-bit) integer data type
   * 
   * Sends a random short value to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int short_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORT
`ifndef NO_SHUNT_DPI_RECV_SHORT
    /**
     * Variable: Short_exp
     * Expected short integer value for loopback test
     */
    shortint Short_exp;
    
    /**
     * Variable: Short_act
     * Actual short integer value received from target
     */
    shortint Short_act;
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string   Test_name = "initiator short_loopback_test";

    success   = 1;
    /* verilator lint_off WIDTH */
    Short_exp = $random();
    /* verilator lint_on WIDTH */
    //send
    if (shunt_dpi_send_short(socket_id, Short_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    //recv
    if (shunt_dpi_recv_short(socket_id, Short_act) <= 0) success = 0;
    if (success == 0) $display("\nShort loopback fail recv");

    if (Short_exp !== Short_act) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_SHORT
`endif  //  `ifndef NO_SHUNT_DPI_SEND_SHORT

    return success;

  endfunction : short_loopback_test

  /**
   * Function: int_loopback_test
   * 
   * Tests the loopback functionality for int (32-bit) integer data type
   * 
   * Sends a random int value to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int int_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INT
`ifndef NO_SHUNT_DPI_RECV_INT
    /**
     * Variable: Int_exp
     * Expected int value for loopback test
     */
    int    Int_exp;
    
    /**
     * Variable: Int_act
     * Actual int value received from target
     */
    int    Int_act;
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name = "initiator int_loopback_test";

    success = 1;
    Int_exp = $random();

    //send
    if (shunt_dpi_send_int(socket_id, Int_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    //recv
    if (shunt_dpi_recv_int(socket_id, Int_act) <= 0) success = 0;
    if (success == 0) $display("\nInt loopback fail recv");

    if (Int_exp !== Int_act) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_INT
`endif  //  `ifndef NO_SHUNT_DPI_SEND_INT
    return success;
  endfunction : int_loopback_test

  /**
   * Function: long_loopback_test
   * 
   * Tests the loopback functionality for long (64-bit) integer data type
   * 
   * Sends a random long value to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int long_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_LONG
`ifndef NO_SHUNT_DPI_RECV_LONG
    /**
     * Variable: Long_exp
     * Expected longint value for loopback test
     */
    longint Long_exp;
    
    /**
     * Variable: Long_act
     * Actual longint value received from target
     */
    longint Long_act;
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string  Test_name = "initiator long_loopback_test";

    success  = 1;
    Long_exp = {$random(), $random()};

    //send
    if (shunt_dpi_send_long(socket_id, Long_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    //recv
    if (shunt_dpi_recv_long(socket_id, Long_act) <= 0) success = 0;
    if (success == 0) $display("\nLong loopback fail recv");

    if (Long_exp !== Long_act) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_LONG
`endif  //  `ifndef NO_SHUNT_DPI_SEND_LONG

    return success;
  endfunction : long_loopback_test

  /**
   * Function: byte_loopback_test
   * 
   * Tests the loopback functionality for byte (8-bit) data type
   * 
   * Sends a random byte value to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int byte_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_BYTE
`ifndef NO_SHUNT_DPI_RECV_BYTE
    /**
     * Variable: Byte_exp
     * Expected byte value for loopback test
     */
    byte   Byte_exp;
    
    /**
     * Variable: Byte_act
     * Actual byte value received from target
     */
    byte   Byte_act;
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name = "initiator byte_loopback_test";

    success  = 1;
    /* verilator lint_off WIDTH */
    Byte_exp = $random();
    /* verilator lint_on WIDTH */
    //send
    if (shunt_dpi_send_byte(socket_id, Byte_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    //recv
    if (shunt_dpi_recv_byte(socket_id, Byte_act) <= 0) success = 0;
    if (success == 0) $display("\nByte loopback fail recv");

    if (Byte_exp !== Byte_act) success = 0;
    return success;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_BYTE
`endif  //  `ifndef NO_SHUNT_DPI_SEND_BYTE

  endfunction : byte_loopback_test

  /**
   * Function: integer_loopback_test
   * 
   * Tests the loopback functionality for integer (32-bit) data type with 4-state values
   * 
   * Sends an integer value with X and Z states to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int integer_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INTEGER
`ifndef NO_SHUNT_DPI_RECV_INTEGER
    /**
     * Variable: Integer_exp
     * Expected integer value for loopback test (with X/Z values)
     */
    integer Integer_exp;
    
    /**
     * Variable: Integer_act
     * Actual integer value received from target
     */
    integer Integer_act;

    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string  Test_name = "initiator integer_loopback_test";
    success = 1;

    //set up data
    Integer_exp = 32'hf0xx_zz5a;

    //send data
    if (shunt_dpi_send_integer(socket_id, Integer_exp) <= 0) success = 0;
    if (shunt_dpi_recv_integer(socket_id, Integer_act) <= 0) success = 0;

    //comp
    if (Integer_act !== Integer_exp) success = 0;
    if (success == 0) $display("\ninitiator: fail comp data");
`endif  //  `ifndef NO_SHUNT_DPI_RECV_INTEGER
`endif  //  `ifndef NO_SHUNT_DPI_SEND_INTEGER

    return success;

  endfunction : integer_loopback_test

  /**
   * Function: time_loopback_test
   * 
   * Tests the loopback functionality for time (64-bit) data type
   * 
   * Sends a time value with X and Z states to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int time_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_TIME
`ifndef NO_SHUNT_DPI_RECV_TIME
    /**
     * Variable: Time_exp
     * Expected time value for loopback test (with X/Z values)
     */
    time   Time_exp;
    
    /**
     * Variable: Time_act
     * Actual time value received from target
     */
    time   Time_act;

    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name = "initiator time_loopback_test";
    $display("\n Start %s", Test_name);
    success  = 1;

    //set up data
    Time_exp = 64'hf0xx_zz5a_dezz_67xx;
    Time_act = 0;


    //send data
    if (shunt_dpi_send_time(socket_id, Time_exp) <= 0) success = 0;
    if (shunt_dpi_recv_time(socket_id, Time_act) <= 0) success = 0;

    //comp
    if (Time_act !== Time_exp) success = 0;
    if (success == 0) $display("\ninitiator: fail comp data");

`endif  //  `ifndef NO_SHUNT_DPI_RECV_TIME
`endif  //  `ifndef NO_SHUNT_DPI_SEND_TIME

    return success;

  endfunction : time_loopback_test

  /**
   * Function: bit_loopback_test
   * 
   * Tests the loopback functionality for bit (1-bit) data type
   * 
   * Sends a bit value to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int bit_loopback_test(int socket_id);
    int success;

`ifndef NO_SHUNT_DPI_SEND_BIT
`ifndef NO_SHUNT_DPI_RECV_BIT
    /**
     * Variable: Bit_exp
     * Expected bit value for loopback test
     */
    bit    Bit_exp;
    
    /**
     * Variable: Bit_act
     * Actual bit value received from target
     */
    bit    Bit_act;

    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name = "initiator bit_loopback_test";
    success = 1;

    //set up data
    Bit_exp = 1;  //$random;
    Bit_act = 0;


    //send data
    if (shunt_dpi_send_bit(socket_id, Bit_exp) <= 0) success = 0;
    if (shunt_dpi_recv_bit(socket_id, Bit_act) <= 0) success = 0;

    //comp
    if (Bit_act !== Bit_exp) success = 0;
    if (success == 0) $display("\ninitiator: fail comp data");
`endif  //  `ifndef NO_SHUNT_DPI_RECV_BIT
`endif  //  `ifndef NO_SHUNT_DPI_SEND_BIT

    return success;

  endfunction : bit_loopback_test

  /**
   * Function: reg_loopback_test
   * 
   * Tests the loopback functionality for reg (1-bit) data type with 4-state values
   * 
   * Sends a reg value with high-impedance (Z) state to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int reg_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_REG
`ifndef NO_SHUNT_DPI_RECV_REG
    /**
     * Variable: Reg_exp
     * Expected reg value (Z) for loopback test
     */
    reg    Reg_exp;
    
    /**
     * Variable: Reg_act
     * Actual reg value received from target
     */
    reg    Reg_act;

    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name = "initiator reg_loopback_test";
    success = 1;

    //set up data
    Reg_exp = 1'bz;
    Reg_act = 0;


    //send data
    if (shunt_dpi_send_reg(socket_id, Reg_exp) <= 0) success = 0;
    if (shunt_dpi_recv_reg(socket_id, Reg_act) <= 0) success = 0;

    //comp
    if (Reg_act !== Reg_exp) success = 0;
    if (success == 0) $display("\ninitiator: fail comp data");
`endif  //  `ifndef NO_SHUNT_DPI_RECV_REG
`endif  //  `ifndef NO_SHUNT_DPI_SEND_REG

    return success;

  endfunction : reg_loopback_test

  /**
   * Function: logic_loopback_test
   * 
   * Tests the loopback functionality for logic (1-bit) data type with 4-state values
   * 
   * Sends a logic value with unknown (X) state to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int logic_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_LOGIC
`ifndef NO_SHUNT_DPI_RECV_LOGIC
    /**
     * Variable: Logic_exp
     * Expected logic value (X) for loopback test
     */
    logic  Logic_exp;
    
    /**
     * Variable: Logic_act
     * Actual logic value received from target
     */
    logic  Logic_act;

    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name = "initiator logic_loopback_test";
    success   = 1;

    //set up data
    Logic_exp = 1'bx;
    Logic_act = 0;


    //send data
    if (shunt_dpi_send_logic(socket_id, Logic_exp) <= 0) success = 0;
    if (shunt_dpi_recv_logic(socket_id, Logic_act) <= 0) success = 0;

    //comp
    if (Logic_act !== Logic_exp) success = 0;
    if (success == 0) $display("\ninitiator: fail comp data");
`endif  //  `ifndef NO_SHUNT_DPI_RECV_LOGIC
`endif  //  `ifndef NO_SHUNT_DPI_SEND_LOGIC

    return success;

  endfunction : logic_loopback_test

  /**
   * Function: bitN_loopback_test
   * 
   * Tests the loopback functionality for multi-bit (bit vector) data type
   * 
   * Sends a bit vector of specified size to the target and validates the received response
   * Also tests transaction header communication
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   *   n_payloads - Number of payloads (default: 1)
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int bitN_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_HS_SEND_BITN
`ifndef NO_SHUNT_DPI_HS_RECV_BITN
    /**
     * Parameter: N 
     * Size of bit vector for testing (133 bits)
     */
    localparam N = 133;  //N 4*32 bit max

    /**
     * Variable: i
     * Loop index
     */
    int            i;
    
    /**
     * Variable: BitN_exp
     * Expected bit vector value for loopback test
     */
    bit    [N-1:0] BitN_exp;
    
    /**
     * Variable: BitN_act
     * Actual bit vector value received from target
     */
    bit    [N-1:0] BitN_act;
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string         s_me = "bitN_loopback_test";
    success = 1;

    //data set
    BitN_exp = {$random(), $random(), $random(), $random()};


    //set up header
    h_trnx_exp.trnx_type = $random;
    h_trnx_exp.trnx_id = $random;
    h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_BIT");
    h_trnx_exp.n_payloads = N;
    //send
    if (shunt_dpi_send_header(socket_id, h_trnx_exp) <= 0) success = 0;
    if (shunt_dpi_hs_send_bitN(socket_id, h_trnx_exp, BitN_exp) != 0) success = 0;
    //recv
    if (shunt_dpi_recv_header(socket_id, h_trnx_act) <= 0) success = 0;
    if (shunt_dpi_hs_recv_bitN(socket_id, h_trnx_act, BitN_act) != 0) success = 0;
    //
    if (BitN_act !== BitN_exp) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_HS_SEND_BITN
`endif  //  `ifndef NO_SHUNT_DPI_HS_SEND_BITN
    return success;
  endfunction : bitN_loopback_test


  /**
   * Function: regN_loopback_test
   * 
   * Tests the loopback functionality for multi-bit reg vector with 4-state values
   * 
   * Sends a reg vector with X and mixed states to the target and validates the received response
   * Also tests transaction header communication
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   *   n_payloads - Number of payloads (default: 1)
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int regN_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_HS_SEND_REGN
`ifndef NO_SHUNT_DPI_HS_RECV_REGN
    /**
     * Parameter: N 
     * Size of reg vector for testing (133 bits)
     */
    localparam N = 133;  //N 4*32 bit max
    
    /**
     * Variable: i
     * Loop index
     */
    int            i;
    
    /**
     * Variable: XRegNV_exp
     * X-state mask for reg vector
     */
    reg    [N-1:0] XRegNV_exp;
    
    /**
     * Variable: RegNV_exp
     * Expected reg vector value for loopback test
     */
    reg    [N-1:0] RegNV_exp;
    
    /**
     * Variable: RegNV_act
     * Actual reg vector value received from target
     */
    reg    [N-1:0] RegNV_act;
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string         s_me = "regN_loopback_test";
    success = 1;
    //data set
    XRegNV_exp = 'hx;
    RegNV_exp = {$random(), $random(), $random(), $random()} & XRegNV_exp;
    RegNV_exp = RegNV_exp | {$random(), $random(), $random(), $random()};
    //set up header
    h_trnx_exp.trnx_type = $random;
    h_trnx_exp.trnx_id = $random;
    h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_REG4S");
    h_trnx_exp.n_payloads = N;
    //send
    if (shunt_dpi_send_header(socket_id, h_trnx_exp) <= 0) success = 0;
    if (shunt_dpi_hs_send_regN(socket_id, h_trnx_exp, RegNV_exp) != 0) success = 0;
    //recv
    if (shunt_dpi_recv_header(socket_id, h_trnx_act) <= 0) success = 0;
    if (shunt_dpi_hs_recv_regN(socket_id, h_trnx_act, RegNV_act) != 0) success = 0;
    //
    if (RegNV_act !== RegNV_exp) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_HS_SEND_REGN
`endif  //  `ifndef NO_SHUNT_DPI_HS_SEND_REGN
    return success;
  endfunction : regN_loopback_test

  /**
   * Function: logicN_loopback_test
   * 
   * Tests the loopback functionality for multi-bit logic vector with 4-state values
   * 
   * Sends a logic vector with X and mixed states to the target and validates the received response
   * Also tests transaction header communication
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   *   n_payloads - Number of payloads (default: 1)
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int logicN_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_HS_SEND_LOGICN
`ifndef NO_SHUNT_DPI_HS_RECV_LOGICN
    /**
     * Parameter: N 
     * Size of logic vector for testing (133 bits)
     */
    localparam N = 133;  //N 4*32 bit max
    
    /**
     * Variable: i
     * Loop index
     */
    int            i;
    
    /**
     * Variable: XLogicN_exp
     * X-state mask for logic vector
     */
    logic  [N-1:0] XLogicN_exp;
    
    /**
     * Variable: LogicN_exp
     * Expected logic vector value for loopback test
     */
    logic  [N-1:0] LogicN_exp;
    
    /**
     * Variable: LogicN_act
     * Actual logic vector value received from target
     */
    logic  [N-1:0] LogicN_act;
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string         s_me = "logicN_loopback_test";
    success = 1;
    //data set
    XLogicN_exp = 'hx;
    LogicN_exp = {$random(), $random(), $random(), $random()} & XLogicN_exp;
    LogicN_exp = LogicN_exp | {$random(), $random(), $random(), $random()};
    //set up header
    h_trnx_exp.trnx_type = $random;
    h_trnx_exp.trnx_id = $random;
    h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_REG4S");
    h_trnx_exp.n_payloads = N;
    //send
    if (shunt_dpi_send_header(socket_id, h_trnx_exp) <= 0) success = 0;
    if (shunt_dpi_hs_send_logicN(socket_id, h_trnx_exp, LogicN_exp) != 0) success = 0;
    //recv
    if (shunt_dpi_recv_header(socket_id, h_trnx_act) <= 0) success = 0;
    if (shunt_dpi_hs_recv_logicN(socket_id, h_trnx_act, LogicN_act) != 0) success = 0;
    //
    if (LogicN_act !== LogicN_exp) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_HS_RECV_LOGICN
`endif  //  `ifndef NO_SHUNT_DPI_HS_SEND_LOGICN

    return success;
  endfunction : logicN_loopback_test

  /**
   * Function: real_loopback_test
   * 
   * Tests the loopback functionality for real (double precision) data type
   * 
   * Sends a random real value to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int real_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_REAL
`ifndef NO_SHUNT_DPI_RECV_REAL
    /**
     * Variable: Real_exp
     * Expected real value for loopback test
     */
    real   Real_exp;
    
    /**
     * Variable: Real_act
     * Actual real value received from target
     */
    real   Real_act;
    
    /**
     * Variable: Result
     * Difference between expected and actual values (cast to int)
     */
    int    Result;
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string s_me = "real_loopback_test";
    success  = 1;
    Real_exp = $random() / 7.5;

    if (shunt_dpi_send_real(socket_id, Real_exp) == 0) success = 0;
    if (shunt_dpi_recv_real(socket_id, Real_act) == 0) success = 0;
    Result = int'(Real_exp - Real_act);
    if (Result != 0 | success == 0) success = 0;

`endif  //  `ifndef NO_SHUNT_DPI_RECV_REAL
`endif  //  `ifndef NO_SHUNT_DPI_SEND_REAL
    return success;
  endfunction : real_loopback_test

  /**
   * Function: shortreal_loopback_test
   * 
   * Tests the loopback functionality for shortreal (single precision) data type
   * 
   * Sends a shortreal value to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int shortreal_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORTREAL
`ifndef NO_SHUNT_DPI_RECV_SHORTREAL
    /**
     * Variable: Shortreal_exp
     * Expected shortreal value for loopback test
     */
    shortreal Shortreal_exp;
    
    /**
     * Variable: Shortreal_act
     * Actual shortreal value received from target
     */
    shortreal Shortreal_act;
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string    s_me = "shortreal_loopback_test";
    success = 1;
    Shortreal_exp = 123;
    if (shunt_dpi_send_shortreal(socket_id, Shortreal_exp) != 0) success = 0;
    if (shunt_dpi_recv_shortreal(socket_id, Shortreal_act) != 0) success = 0;
    if (Shortreal_exp != Shortreal_act) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_SHORTREAL
`endif  //  `ifndef NO_SHUNT_DPI_SEND_SHORTREAL
    return success;
  endfunction : shortreal_loopback_test

  /**
   * Function: string_loopback_test
   * 
   * Tests the loopback functionality for string data type
   * 
   * Sends a predefined string to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int string_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_STRING
`ifndef NO_SHUNT_DPI_RECV_STRING
    /**
     * Variable: i
     * Loop index
     */
    int    i;
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name;
    
    /**
     * Variable: String_exp
     * Expected string value for loopback test
     */
    string String_exp;
    
    /**
     * Variable: String_act
     * Actual string value received from target
     */
    string String_act;
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string s_me = "string_loopback_test";
    String_exp = `STRING_MESSAGE;
    String_act = `STRING_MESSAGE1;
    success = 1;

    Test_name = "initiator string_loopback_test send";
    if (shunt_dpi_send_string(socket_id, String_exp.len(), String_exp) <= 0) success = 0;

    Test_name = "initiator string_loopback_test recv";
    if (shunt_dpi_recv_string(socket_id, String_exp.len(), String_act) <= 0) success = 0;
    $display("\n %s String = %s", Test_name, String_act);

    if (String_act != String_exp) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_STRING
`endif  //  `ifndef NO_SHUNT_DPI_SEND_STRING
    return success;
  endfunction : string_loopback_test

  /**
   * Function: shortV_loopback_test
   * 
   * Tests the loopback functionality for shortint vector (array) data type
   * 
   * Sends an array of shortint values to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int shortV_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORTV
`ifndef NO_SHUNT_DPI_RECV_SHORTV
    /**
     * Variable: shortV_i
     * Loop index for the shortint array
     */
    int      shortV_i;
    
    /**
     * Variable: ShortV_exp
     * Expected shortint array for loopback test
     */
    shortint ShortV_exp                    [`V_SIZE];
    
    /**
     * Variable: ShortV_act
     * Actual shortint array received from target
     */
    shortint ShortV_act                    [`V_SIZE];
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string   s_me = "shortV_loopback_test";
    success = 1;
    /* verilator lint_off WIDTH */
    foreach (ShortV_exp[shortV_i]) ShortV_exp[shortV_i] = 100 + shortint'(shortV_i + 1);
    foreach (ShortV_act[shortV_i]) ShortV_act[shortV_i] = 300 + shortint'(shortV_i + 1);
    if (shunt_dpi_send_shortV(socket_id, `V_SIZE, ShortV_exp) <= 0) success = 0;
    if (shunt_dpi_recv_shortV(socket_id, `V_SIZE, ShortV_act) <= 0) success = 0;
    foreach (ShortV_exp[shortV_i]) if (ShortV_act[shortV_i] != ShortV_exp[shortV_i]) success = 0;
    /* verilator lint_on WIDTH */
`endif  //  `ifndef NO_SHUNT_DPI_RECV_SHORTV
`endif  //  `ifndef NO_SHUNT_DPI_SEND_SHORTV
    return success;
  endfunction : shortV_loopback_test

  /**
   * Function: intv_loopback_test
   * 
   * Tests the loopback functionality for int vector (array) data type
   * 
   * Sends an array of int values to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int intv_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INTV
`ifndef NO_SHUNT_DPI_RECV_INTV
    /**
     * Variable: intv_i
     * Loop index for the int array
     */
    int    intv_i;
    
    /**
     * Variable: Intv_exp
     * Expected int array for loopback test
     */
    int    Intv_exp                    [`V_SIZE];
    
    /**
     * Variable: Intv_act
     * Actual int array received from target
     */
    int    Intv_act                    [`V_SIZE];
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string s_me = "intv_loopback_test";
    success = 1;
    foreach (Intv_exp[intv_i]) Intv_exp[intv_i] = 200 + intv_i;
    foreach (Intv_act[intv_i]) Intv_act[intv_i] = 400 + intv_i + 1;
    if (shunt_dpi_send_intV(socket_id, `V_SIZE, Intv_exp) <= 0) success = 0;
    if (shunt_dpi_recv_intV(socket_id, `V_SIZE, Intv_act) <= 0) success = 0;
    foreach (Intv_exp[intv_i]) if (Intv_act[intv_i] != Intv_exp[intv_i]) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_INTV
`endif  //  `ifndef NO_SHUNT_DPI_SEND_INTV
    return success;
  endfunction : intv_loopback_test




  /**
   * Function: longV_loopback_test
   * 
   * Tests the loopback functionality for longint vector (array) data type
   * 
   * Sends an array of longint values to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int longV_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_LONGV
`ifndef NO_SHUNT_DPI_RECV_LONGV
    /* verilator lint_off WIDTH */
    /**
     * Variable: i_
     * Loop index for the longint array
     */
    int     i_;
    
    /**
     * Variable: LongV_exp
     * Expected longint array for loopback test
     */
    longint LongV_exp                    [`V_SIZE];
    
    /**
     * Variable: LongV_act
     * Actual longint array received from target
     */
    longint LongV_act                    [`V_SIZE];
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string  s_me = "longV_loopback_test";
    success = 1;
    foreach (LongV_exp[i_]) LongV_exp[i_] = 100 + longint'(i_ + 1);
    foreach (LongV_act[i_]) LongV_act[i_] = 300 + longint'(i_ + 1);
    if (shunt_dpi_send_longV(socket_id, `V_SIZE, LongV_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    if (shunt_dpi_recv_longV(socket_id, `V_SIZE, LongV_act) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail recv data");
    foreach (LongV_exp[i_]) if (LongV_act[i_] != LongV_exp[i_]) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_LONGV
`endif  //  `ifndef NO_SHUNT_DPI_SEND_LONGV
    return success;

    /* verilator lint_on WIDTH */
  endfunction : longV_loopback_test

  /**
   * Function: realV_loopback_test
   * 
   * Tests the loopback functionality for real vector (array) data type
   * 
   * Sends an array of real values to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   *   n_payloads - Number of payloads (default: 1, not used)
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int realV_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_SEND_REALV
`ifndef NO_SHUNT_DPI_RECV_REALV
    /**
     * Variable: i
     * Loop index for the real array
     */
    int    i;
    
    /**
     * Variable: RealV_exp
     * Expected real array for loopback test
     */
    real   RealV_exp                                   [`V_SIZE];
    
    /**
     * Variable: RealV_act
     * Actual real array received from target
     */
    real   RealV_act                                   [`V_SIZE];
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string Test_name = "initiator realV_loopback_test";
    success = 1;
    for (int i = 0; i < `V_SIZE; i++) RealV_exp[i] = 300.123 + i;
    if (shunt_dpi_send_realV(socket_id, `V_SIZE, RealV_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    if (shunt_dpi_recv_realV(socket_id, `V_SIZE, RealV_act) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail recv data");
    foreach (RealV_exp[i]) if (RealV_exp[i] != RealV_act[i]) success = 0;
`endif  //  `ifndef NO_SHUNT_DPI_RECV_REALV
`endif  //  `ifndef NO_SHUNT_DPI_SEND_REALV
    return success;
  endfunction : realV_loopback_test


  /**
   * Function: shortrealV_loopback_test
   * 
   * Tests the loopback functionality for shortreal vector (array) data type
   * 
   * Sends an array of shortreal values to the target and validates the received response
   * Using tolerance check for floating-point comparison
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   *   n_payloads - Number of payloads (default: 1, not used)
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int shortrealV_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORTREALV
`ifndef NO_SHUNT_DPI_RECV_SHORTREALV
    /**
     * Variable: i
     * Loop index for the shortreal array
     */
    int       i;
    
    /**
     * Variable: ShortrealV_exp
     * Expected shortreal array for loopback test
     */
    shortreal ShortrealV_exp                                   [`V_SIZE];
    
    /**
     * Variable: ShortrealV_act
     * Actual shortreal array received from target
     */
    shortreal ShortrealV_act                                   [`V_SIZE];
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string    Test_name = "initiator shortrealV_loopback_test";
    success = 1;
    for (int i = 0; i < `V_SIZE; i++) ShortrealV_exp[i] = 540.123 + i;
    if (shunt_dpi_send_shortrealV(socket_id, `V_SIZE, ShortrealV_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    if (shunt_dpi_recv_shortrealV(socket_id, `V_SIZE, ShortrealV_act) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail recv data");
    foreach (ShortrealV_exp[i]) begin
      real zero_ = 0;
      zero_ = ShortrealV_exp[i] - ShortrealV_act[i];
      if (zero_ < 0) zero_ = ShortrealV_act[i] - ShortrealV_exp[i];
      if (zero_ > 0.0001) success = 0;
    end
    if (success == 0) $display("\ninitiator: fail comp data");
`endif  //  `ifndef NO_SHUNT_DPI_RECV_SHORTREALV
`endif  //  `ifndef NO_SHUNT_DPI_SEND_SHORTREALV
    return success;
  endfunction : shortrealV_loopback_test

  /**
   * Function: integerV_loopback_test
   * 
   * Tests the loopback functionality for integer vector (array) data type
   * 
   * Sends an array of integer values to the target and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   *   n_payloads - Number of payloads (default: 1, not used)
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int integerV_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INTEGERV
`ifndef NO_SHUNT_DPI_RECV_INTEGERV
    /**
     * Variable: i_
     * Loop index for the integer array
     */
    int     i_;
    
    /**
     * Variable: IntegerV_exp
     * Expected integer array for loopback test
     */
    integer IntegerV_exp                                   [`V_SIZE];
    
    /**
     * Variable: IntegerV_act
     * Actual integer array received from target
     */
    integer IntegerV_act                                   [`V_SIZE];
    
    /**
     * Variable: Test_name
     * Test name for reporting purposes
     */
    string  Test_name = "initiator integerV_loopback_test";
    success = 1;
    for (int i_ = 0; i_ < `V_SIZE; i_++) IntegerV_exp[i_] = 540 + i_;
    foreach (IntegerV_exp[i])
    $display("\n %s  IntegerV_exp[%0d] = %h", Test_name, i, IntegerV_exp[i]);
    if (shunt_dpi_send_integerV(socket_id, `V_SIZE, IntegerV_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    if (shunt_dpi_recv_integerV(socket_id, `V_SIZE, IntegerV_act) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail recv data");
    foreach (IntegerV_exp[i_]) if (IntegerV_act[i_] !== IntegerV_exp[i_]) success = 0;
    if (success == 0) $display("\ninitiator: fail comp data");
`endif  //  `ifndef NO_SHUNT_DPI_RECV_INTEGERV
`endif  //  `ifndef NO_SHUNT_DPI_SEND_INTEGERV
    return success;
  endfunction : integerV_loopback_test

  /**
   * Function: pkt_longV_loopback_test
   * 
   * Tests the loopback functionality for packet-based longint vector transfer
   * 
   * Sends a transaction header followed by an array of longint values, then validates the response
   * Tests both data and transaction headers
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int pkt_longV_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_PKT_LONGV
`ifndef NO_SHUNT_DPI_RECV_PKT_LONGV
    /* verilator lint_off WIDTH */
    /**
     * Variable: i_
     * Loop index for the longint array
     */
    int     i_;
    
    /**
     * Variable: Pkt_longv_exp
     * Expected longint array for loopback test
     */
    longint Pkt_longv_exp                              [`V_SIZE];
    
    /**
     * Variable: Pkt_longv_act
     * Actual longint array received from target
     */
    longint Pkt_longv_act                              [`V_SIZE];
    
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string  s_me = "initiator pkt_longV_loopback_test";
    success = 1;
    h_trnx_exp.trnx_type = 'h01;
    h_trnx_exp.trnx_id = 'h02;  //{$random,$random};
    h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_LONGINT");
    h_trnx_exp.n_payloads = `V_SIZE;
    foreach (Pkt_longv_exp[i_]) Pkt_longv_exp[i_] = 400 + longint'(i_ + 1);
    foreach (Pkt_longv_act[i_]) Pkt_longv_act[i_] = 600 + longint'(i_ + 1);
    //
    if (shunt_dpi_send_pkt_longV(socket_id, h_trnx_exp, Pkt_longv_exp) <= 0) success = 0;
    if (success == 0) $display("\ninitiator: fail send data");
    //
    h_trnx_act.trnx_type = 300;  //{$random,$random};
    h_trnx_act.trnx_id = 400;  //{$random,$random};
    h_trnx_act.data_type = shunt_dpi_hash("SHUNT_BIT");
    h_trnx_act.n_payloads = `V_SIZE;
    if (shunt_dpi_recv_pkt_longV(socket_id, h_trnx_act, Pkt_longv_act) <= 0) success = 0;
    //compare
    if (!compare_shunt_header(h_trnx_exp, h_trnx_act)) success = 0;
    if (success == 0) $display("\ninitiator: fail recv data");
    foreach (Pkt_longv_exp[i_]) if (Pkt_longv_act[i_] != Pkt_longv_exp[i_]) success = 0;

`endif  //  `ifndef NO_SHUNT_DPI_RECV_PKT_LONGV
`endif  //  `ifndef NO_SHUNT_DPI_SEND_PKT_LONGV
    return success;
    /* verilator lint_on WIDTH */
  endfunction : pkt_longV_loopback_test


  /**
   * Function: header_loopback_test
   * 
   * Tests the loopback functionality for transaction headers
   * 
   * Sends a transaction header with random fields and validates the received response
   * 
   * Parameters:
   *   socket_id - Socket descriptor for the established connection
   *   n_payloads - Number of payloads (default: 1, not used)
   * 
   * Returns:
   *   success - 1 if test passes, 0 if fails
   */
  function int header_loopback_test(int socket_id, int n_payloads = 1);
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string s_me = "header_loopback_test()";
    
    /**
     * Variable: success
     * Test result flag (1 = pass, 0 = fail)
     */
    int    success = 1;

    //set up header
    h_trnx_exp.trnx_type = {$random, $random};
    h_trnx_exp.trnx_id = {$random, $random};
    h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_HEADER_ONLY");
    h_trnx_exp.n_payloads = {$random, $random};

    h_trnx_act.trnx_type = 0;
    h_trnx_act.trnx_id = 0;
    h_trnx_act.data_type = 0;
    h_trnx_act.n_payloads = 0;
    //send
    if (shunt_dpi_send_header(socket_id, h_trnx_exp) <= 0) success = 0;
    //recv
    if (shunt_dpi_recv_header(socket_id, h_trnx_act) <= 0) success = 0;
    if (!compare_shunt_header(h_trnx_exp, h_trnx_act)) success = 0;
    //
    return success;
  endfunction : header_loopback_test

  /**
   * Function: print_status
   * 
   * Prints the status of a test (PASS or FAIL) to the simulation log
   * 
   * Parameters:
   *   Test_name - Name of the test being reported
   *   Status_int - Status flag (1 = pass, 0 = fail)
   */
  function void print_status(string Test_name, int Status_int);
    /**
     * Variable: Status
     * String representation of test status ("PASS" or "FAIL")
     */
    string Status;
    /* verilator lint_off WIDTH */
    if (!Status_int) Status = "FAIL";
    /* verilator lint_on WIDTH */
    else
      Status = "PASS";
    $display("%s TEST %s", Test_name, Status);
  endfunction : print_status


  /**
   * Function: print_shunt_header
   * 
   * Prints all fields of a cs_header_t structure to the simulation log
   * 
   * Parameters:
   *   h_ - Header structure to print
   *   name_in - Optional name to display with the header (default: "")
   *   i_am - Module/function identifier string for debug messages
   */
  function automatic void print_shunt_header(cs_header_t h_, string name_in = "", string i_am);
    //   typedef struct{
    // longint     trnx_type;
    // longint     trnx_id;
    // longint     data_type;
    // int     n_payloads;
    //} cs_header_t;
    $display("\n%s  %s.trnx_type  = %0h", i_am, name_in, h_.trnx_type);
    $display("\n%s  %s.trnx_id    = %0h", i_am, name_in, h_.trnx_id);
    $display("\n%s  %s.data_type  = %0h", i_am, name_in, h_.data_type);
    $display("\n%s  %s.n_payloads = %0d", i_am, name_in, h_.n_payloads);
  endfunction : print_shunt_header

  /**
   * Function: compare_shunt_header
   * 
   * Compares two transaction headers for equality
   * 
   * Compares all fields of the transaction headers and prints debug information
   * 
   * Parameters:
   *   lhs - Left-hand side header to compare
   *   rls - Right-hand side header to compare
   * 
   * Returns:
   *   success - 1 if headers match, 0 if different
   */
  function automatic bit compare_shunt_header(cs_header_t lhs, cs_header_t rls);
    /**
     * Variable: s_me
     * Function name for debug messages
     */
    string s_me = "compare_shunt_header(lhs,rls)";
    
    /**
     * Variable: success
     * Comparison result flag (1 = match, 0 = different)
     */
    bit    success = 1;

    if (lhs.trnx_type != rls.trnx_type) success = 0;
    if (lhs.trnx_id != rls.trnx_id) success = 0;
    if (lhs.data_type != rls.data_type) success = 0;
    if (lhs.n_payloads != rls.n_payloads) success = 0;

    if (success == 0) begin
      $display("\ninitiator: %s fail", s_me);
      print_shunt_header(lhs, "lhs", s_me);
      print_shunt_header(rls, "rhs", s_me);
    end
    if (success == 1) begin
      $display("\ninitiator: %s pass", s_me);
      print_shunt_header(lhs, "lhs", s_me);
      print_shunt_header(rls, "rhs", s_me);
    end
    return success;

  endfunction : compare_shunt_header

endmodule : Initiator
