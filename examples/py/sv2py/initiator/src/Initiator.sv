/*
 ============================================================================
Title: Initiator.sv
1.0.1
 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : TCP/IP SystemVerilog SHUNT
 All Types SystemVerilog examle  -Initiator(server)
 History:
  - initial release
 1.0.1 - shunt-verilator integration
 Version 1.0.1 : Verilator 3.916 2017-11-25 rev verilator_3_916
 ============================================================================
 */

/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */
/* verilator lint_off VARHIDDEN */
`include "../../includes/cs_common.svh"

module automatic Initiator;

  import shunt_dpi_pkg::*;

  int         Socket;
  int         Pass;

  cs_header_t h_trnx_exp;
  cs_header_t h_trnx_act;
`ifndef NO_CS_DATA_HEADER_T
  cs_data_header_t h_data_exp;
  cs_data_header_t h_data_act;
`endif

  initial begin
    string Status;
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

  function int init_initiator(int portno);
    begin
      int socket_id;
      socket_id = 0;
      socket_id = shunt_dpi_initiator_init(portno);
      return socket_id;
    end
  endfunction : init_initiator


  function int short_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORT
`ifndef NO_SHUNT_DPI_RECV_SHORT
    shortint Short_exp;
    shortint Short_act;
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

  function int int_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INT
`ifndef NO_SHUNT_DPI_RECV_INT
    int    Int_exp;
    int    Int_act;
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

  function int long_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_LONG
`ifndef NO_SHUNT_DPI_RECV_LONG
    longint Long_exp;
    longint Long_act;
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

  function int byte_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_BYTE
`ifndef NO_SHUNT_DPI_RECV_BYTE

    byte   Byte_exp;
    byte   Byte_act;
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

  function int integer_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INTEGER
`ifndef NO_SHUNT_DPI_RECV_INTEGER

    integer Integer_exp;
    integer Integer_act;

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

  function int time_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_TIME
`ifndef NO_SHUNT_DPI_RECV_TIME

    time   Time_exp;
    time   Time_act;

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

  function int bit_loopback_test(int socket_id);
    int success;

`ifndef NO_SHUNT_DPI_SEND_BIT
`ifndef NO_SHUNT_DPI_RECV_BIT
    bit    Bit_exp;
    bit    Bit_act;

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

  function int reg_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_REG
`ifndef NO_SHUNT_DPI_RECV_REG

    reg    Reg_exp;
    reg    Reg_act;

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

  function int logic_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_LOGIC
`ifndef NO_SHUNT_DPI_RECV_LOGIC

    logic  Logic_exp;
    logic  Logic_act;

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

  function int bitN_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_HS_SEND_BITN
`ifndef NO_SHUNT_DPI_HS_RECV_BITN
    localparam N = 133;  //N 4*32 bit max

    int            i;
    bit    [N-1:0] BitN_exp;
    bit    [N-1:0] BitN_act;
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


  function int regN_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_HS_SEND_REGN
`ifndef NO_SHUNT_DPI_HS_RECV_REGN
    localparam N = 133;  //N 4*32 bit max
    int            i;
    reg    [N-1:0] XRegNV_exp;
    reg    [N-1:0] RegNV_exp;
    reg    [N-1:0] RegNV_act;
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

  function int logicN_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_HS_SEND_LOGICN
`ifndef NO_SHUNT_DPI_HS_RECV_LOGICN
    localparam N = 133;  //N 4*32 bit max
    int            i;
    logic  [N-1:0] XLogicN_exp;
    logic  [N-1:0] LogicN_exp;
    logic  [N-1:0] LogicN_act;
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

  function int real_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_REAL
`ifndef NO_SHUNT_DPI_RECV_REAL
    real   Real_exp;
    real   Real_act;
    int    Result;
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

  function int shortreal_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORTREAL
`ifndef NO_SHUNT_DPI_RECV_SHORTREAL
    shortreal Shortreal_exp;
    shortreal Shortreal_act;
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

  function int string_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_STRING
`ifndef NO_SHUNT_DPI_RECV_STRING
    int    i;
    string Test_name;
    string String_exp;
    string String_act;
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

  function int shortV_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORTV
`ifndef NO_SHUNT_DPI_RECV_SHORTV
    int      shortV_i;
    shortint ShortV_exp                    [`V_SIZE];
    shortint ShortV_act                    [`V_SIZE];
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

  function int intv_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INTV
`ifndef NO_SHUNT_DPI_RECV_INTV
    int    intv_i;
    int    Intv_exp                    [`V_SIZE];
    int    Intv_act                    [`V_SIZE];
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




  function int longV_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_LONGV
`ifndef NO_SHUNT_DPI_RECV_LONGV
    /* verilator lint_off WIDTH */
    int     i_;
    longint LongV_exp                    [`V_SIZE];
    longint LongV_act                    [`V_SIZE];
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

  function int realV_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_SEND_REALV
`ifndef NO_SHUNT_DPI_RECV_REALV
    int    i;
    real   RealV_exp                                   [`V_SIZE];
    real   RealV_act                                   [`V_SIZE];
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


  function int shortrealV_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_SEND_SHORTREALV
`ifndef NO_SHUNT_DPI_RECV_SHORTREALV
    int       i;
    shortreal ShortrealV_exp                                   [`V_SIZE];
    shortreal ShortrealV_act                                   [`V_SIZE];
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

  function int integerV_loopback_test(int socket_id, int n_payloads = 1);
    int success;
`ifndef NO_SHUNT_DPI_SEND_INTEGERV
`ifndef NO_SHUNT_DPI_RECV_INTEGERV
    int     i_;
    integer IntegerV_exp                                   [`V_SIZE];
    integer IntegerV_act                                   [`V_SIZE];
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

  function int pkt_longV_loopback_test(int socket_id);
    int success;
`ifndef NO_SHUNT_DPI_SEND_PKT_LONGV
`ifndef NO_SHUNT_DPI_RECV_PKT_LONGV
    /* verilator lint_off WIDTH */
    int     i_;
    longint Pkt_longv_exp                              [`V_SIZE];
    longint Pkt_longv_act                              [`V_SIZE];
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


  function int header_loopback_test(int socket_id, int n_payloads = 1);
    string s_me = "header_loopback_test()";
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

  function void print_status(string Test_name, int Status_int);
    string Status;
    /* verilator lint_off WIDTH */
    if (!Status_int) Status = "FAIL";
    /* verilator lint_on WIDTH */
    else
      Status = "PASS";
    $display("%s TEST %s", Test_name, Status);
  endfunction : print_status


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

  function automatic bit compare_shunt_header(cs_header_t lhs, cs_header_t rls);
    string s_me = "compare_shunt_header(lhs,rls)";
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
