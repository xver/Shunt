"""
============================================================================
Title: Target.py

 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : TCP/IP SystemVerilog SHUNT
               All Types Python example  -Target(client)
 ============================================================================
"""

import os
import random
import sys
import struct
import ctypes

shuntpyhome =  os.environ['SHUNT_HOME'] + "/utils/py/shunt_py"
sys.path.insert(0,shuntpyhome)

from shunt import *

# Class: Target
#
# TCP/IP SystemVerilog SHUNT Target (client) implementation.
# Handles communication with Initiator and implements various data type loopback tests.
class Target:

    # Function: __init__
    #
    # Initialize Target class with default values.
    def __init__(self):
        self.lib= Shunt()
        self.String = ""
        self.Socket = 0
        self.h_trnx = None  # Assuming cs_header_t is defined somewhere
        self.h_data = None  # Assuming cs_data_header_t is defined somewhere

    # Function: init_target
    #
    # Initialize the TCP/IP socket for the Target (client).
    #
    # Parameter: portno   - Port number for the TCP/IP socket
    # Parameter: hostname - Host name or IP address to connect to
    #        
    # Returns: Socket identifier for established connection
    def init_target(self, portno, hostname):
        socket_id = 0
        socket_id = self.lib.shunt_py_target_init(portno, hostname)
        return socket_id

    # Function: header_loopback_test
    #
    # Perform loopback test for transaction header.
    # Receives a header from Initiator and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def header_loopback_test(self,socket_id):
        h_trnx = cs_header()
        # Receive
        Test_name = "\n SV2PY header_loopback_test recv"
        result,h_trnx = self.lib.shunt_py_recv_header(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

        ## Send
        Test_name = "\n SV2PY header_loopback_test send"
        result = self.lib.shunt_py_send_header(socket_id, h_trnx)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: short_loopback_test
    #
    # Perform loopback test for short data type.
    # Receives a short integer from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def short_loopback_test(self, socket_id):
        Short = 0xDEAD
        Test_name = "\n  SV2PY short_loopback_test recv"

        # recv
        result,Short = self.lib.shunt_py_recv_short(socket_id)
        if result<=0 :
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"{Test_name} Short={hex(Short)}")

        # send
        Test_name = "\n  SV2PY short_loopback_test send"
        result= self.lib.shunt_py_send_short(socket_id, Short)
        if result<=0 :
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: int_loopback_test
    #
    # Perform loopback test for int data type.
    # Receives an integer from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def int_loopback_test(self, socket_id):
        Int = 0xDEAD
        Test_name = "\n  SV2PY int_loopback_test recv"

        # recv
        result,Int = self.lib.shunt_py_recv_int(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"{Test_name} Int={Int}")

        # send
        Test_name = "\n  SV2PY int_loopback_test send"
        result = self.lib.shunt_py_send_int(socket_id, Int)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: long_loopback_test
    #
    # Perform loopback test for long data type.
    # Receives a long integer from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def long_loopback_test(self, socket_id):
        Long = 0xDEAD
        Test_name = "\n  SV2PY long_loopback_test recv"

        # recv
        result,Long = self.lib.shunt_py_recv_long(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"{Test_name} Long={Long}")

        # send
        Test_name = "\n  SV2PY long_loopback_test send"
        result = self.lib.shunt_py_send_long(socket_id, Long)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: byte_loopback_test
    #
    # Perform loopback test for byte data type.
    # Receives a byte from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def byte_loopback_test(self, socket_id):
        Byte = 0xDE
        Test_name = "\n  SV2PY byte_loopback_test recv"

        # recv
        result,Byte = self.lib.shunt_py_recv_byte(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"{Test_name} Byte={Byte}")

        # send
        Test_name = "\n  SV2PY byte_loopback_test send"
        result = self.lib.shunt_py_send_byte(socket_id, Byte)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: integer_loopback_test
    #
    # Perform loopback test for SystemVerilog integer data type.
    # Receives an SVpiVecVal integer from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def integer_loopback_test(self, socket_id):
        Integer = 0xDEAD
        Test_name = "\n  SV2PY integer_loopback_test recv"
        Integer = SVpiVecVal()
        # recv
        result,Integer = self.lib.shunt_py_recv_integer(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} Integer={Integer}")

        # send
        Test_name = "\n  SV2PY integer_loopback_test send"
        result = self.lib.shunt_py_send_integer(socket_id, Integer)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: time_loopback_test
    #
    # Perform loopback test for SystemVerilog time data type.
    # Receives a time value from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def time_loopback_test(self, socket_id):
        Time = 0xDEAD
        Test_name = "\n  SV2PY time_loopback_test recv"

        # recv
        result = self.lib.shunt_py_recv_time(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} Time={Time}")

        # send
        Test_name = "\n  SV2PY time_loopback_test send"
        result = self.lib.shunt_py_send_time(socket_id, Time)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: bit_loopback_test
    #
    # Perform loopback test for SystemVerilog bit data type.
    # Receives a bit value from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def bit_loopback_test(self, socket_id):
        Bit = 0
        Test_name = "\n  SV2PY bit_loopback_test recv"

        # recv
        result,Bit = self.lib.shunt_py_recv_bit(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} Bit={Bit}")

        # send
        Test_name = "\n  SV2PY bit_loopback_test send"
        result = self.lib.shunt_py_send_bit(socket_id, Bit)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: reg_loopback_test
    #
    # Perform loopback test for SystemVerilog reg data type.
    # Receives a reg value from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def reg_loopback_test(self, socket_id):
        Reg = 0
        Test_name = "\n  SV2PY reg_loopback_test recv"

        # recv
        result,Reg = self.lib.shunt_py_recv_reg(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} Reg={Reg}")

        # send
        Test_name = "\n  SV2PY reg_loopback_test send"
        result = self.lib.shunt_py_send_reg(socket_id, Reg)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: logic_loopback_test
    #
    # Perform loopback test for SystemVerilog logic data type.
    # Receives a logic value from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def logic_loopback_test(self, socket_id):
        Logic = 0
        Test_name = "\n  SV2PY logic_loopback_test recv"

        # recv
        result,Logic = self.lib.shunt_py_recv_logic(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} Logic={Logic}")

        # send
        Test_name = "\n  SV2PY logic_loopback_test send"
        result = self.lib.shunt_py_send_logic(socket_id, Logic)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: real_loopback_test
    #
    # Perform loopback test for floating-point real data type.
    # Receives a real value from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def real_loopback_test(self, socket_id):
        Real = 0.0  # Assuming Real is a floating point number
        Test_name = "\n  SV2PY real_loopback_test recv"

        # Receiving the real number
        result, Real = self.lib.shunt_py_recv_real(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        else:
            print(f"\n{Test_name} Real={Real}({Real})")

        # Sending the real number
        Test_name = "\n  SV2PY real_loopback_test send"
        result = self.lib.shunt_py_send_real(socket_id, Real)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: string_loopback_test
    #
    # Perform loopback test for string data type.
    # Receives a string from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def string_loopback_test(self, socket_id):
        Test_name = "\n  SV2PY string_loopback_test recv"
        String = "0000000000000000000000000000000000000000000000000000000"
        result, received_string = self.lib.shunt_py_recv_string(socket_id,len(String))
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        else:
            print(f"\n{Test_name} String = {received_string}")

        # Sending the string
        Test_name = "\n  SV2PY string_loopback_test send"
        result = self.lib.shunt_py_send_string(socket_id, received_string)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: bitN_loopback_test
    #
    # Perform loopback test for array of SystemVerilog bit data type.
    # Receives an array of bits from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def bitN_loopback_test(self, socket_id):
        BitN = [0] * 1025
        Test_name = "\n  SV2PY bitN_loopback_test recv"

        # recv
        h_trnx = cs_header()
        result,h_trnx = self.lib.shunt_py_recv_header(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        result,BitN = self.lib.shunt_py_recv_bitN(socket_id,h_trnx.n_payloads)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} BitN={BitN}")

        # send
        Test_name = "\n  SV2PY bitN_loopback_test send"
        result = self.lib.shunt_py_send_header(socket_id, h_trnx)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        result = self.lib.shunt_py_send_bitN(socket_id, h_trnx, BitN)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: regN_loopback_test
    #
    # Perform loopback test for array of SystemVerilog reg data type.
    # Receives an array of reg values from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def regN_loopback_test(self, socket_id):
        RegN = [0] * 1025
        Test_name = "\n  SV2PY regN_loopback_test recv"

        # recv
        if self.lib.shunt_py_recv_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_recv_regN(socket_id, self.h_trnx, RegN) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} RegN={RegN}")

        # send
        Test_name = "\n  SV2PY regN_loopback_test send"
        if self.lib.shunt_py_send_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_send_regN(socket_id, self.h_trnx, RegN) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: logicN_loopback_test
    #
    # Perform loopback test for array of SystemVerilog logic data type.
    # Receives an array of logic values from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def logicN_loopback_test(self, socket_id):
        LogicN = [0] * 1025
        Test_name = "\n  SV2PY logicN_loopback_test recv"

        # recv
        if self.lib.shunt_py_recv_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_recv_logicN(socket_id, self.h_trnx, LogicN) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} LogicN={LogicN}")

        # send
        Test_name = "\n  SV2PY logicN_loopback_test send"
        if self.lib.shunt_py_send_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_send_logicN(socket_id, self.h_trnx, LogicN) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: timeN_loopback_test
    #
    # Perform loopback test for array of SystemVerilog time data type.
    # Receives an array of time values from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def timeN_loopback_test(self, socket_id):
        TimeN = [0] * 1025
        Test_name = "\n  SV2PY timeN_loopback_test recv"

        # recv
        if self.lib.shunt_py_recv_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_recv_timeN(socket_id, self.h_trnx, TimeN) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} TimeN={TimeN}")

        # send
        Test_name = "\n  SV2PY timeN_loopback_test send"
        if self.lib.shunt_py_send_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_send_timeN(socket_id, self.h_trnx, TimeN) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: data_header_loopback_test
    #
    # Perform loopback test for data header.
    # Receives a data header from Initiator and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def data_header_loopback_test(self, socket_id):
        Test_name = "\n SV2PY data_header_loopback_test recv"

        # recv
        result = self.lib.shunt_py_recv_data_header(socket_id, self.h_data)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

        # send
        Test_name = "\n SV2PY data_header_loopback_test send"
        result = self.lib.shunt_py_send_data_header(socket_id, self.h_data)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: data_loopback_test
    #
    # Perform loopback test for generic data array.
    # Receives data from Initiator, displays it, and sends it back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def data_loopback_test(self, socket_id):
        Data = [0] * 1025
        Test_name = "\n  SV2PY data_loopback_test recv"

        # recv
        result,Data = self.lib.shunt_py_hs_recv_data(socket_id)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        print(f"\n{Test_name} Data={Data}")

        # send
        Test_name = "\n  SV2PY data_loopback_test send"
        result = self.lib.shunt_py_hs_send_data(socket_id, Data)
        if result <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: header_data_loopback_test
    #
    # Perform loopback test for combined header and data.
    # Receives a header and data from Initiator and sends them back.
    #
    # Parameter: socket_id - Socket identifier for the connection
    def header_data_loopback_test(self, socket_id):
        Test_name = "\n SV2PY header_data_loopback_test recv"

        # recv
        if self.lib.shunt_py_hs_recv_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_recv_data(socket_id, self.h_data) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

        # send
        Test_name = "\n SV2PY header_data_loopback_test send"
        if self.lib.shunt_py_hs_send_header(socket_id, self.h_trnx) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")
        if self.lib.shunt_py_hs_send_data(socket_id, self.h_data) <= 0:
            print(f"{Test_name} TARGET: TEST FAIL")

    # Function: print_shunt_header
    #
    # Print the contents of a SHUNT header.
    #
    # Parameter: h_      - Header structure to print
    # Parameter: name_in - Name identifier for the header
    # Parameter: i_am    - Identifier for the caller
    def print_shunt_header(self, h_, name_in="", i_am=""):
        print(f"\n{i_am} {name_in}.trnx_type  = {h_.trnx_type}")
        print(f"\n{i_am} {name_in}.trnx_id    = {h_.trnx_id}")
        print(f"\n{i_am} {name_in}.data_type  = {h_.data_type}")
        print(f"\n{i_am} {name_in}.n_payloads = {h_.n_payloads}")

    # Function: print_shunt_data_header
    #
    # Print the contents of a SHUNT data header.
    #
    # Parameter: dh_     - Data header structure to print
    # Parameter: name_in - Name identifier for the data header
    # Parameter: i_am    - Identifier for the caller
    def print_shunt_data_header(self, dh_, name_in="", i_am=""):
        print(f"\n{i_am} {name_in}.data_type  = {dh_.data_type}")
        print(f"\n{i_am} {name_in}.n_payloads = {dh_.n_payloads}")

if __name__ == "__main__":
    target = Target()

    # Initialize
    target.Socket = target.init_target(0, 'localhost')
    print(f"Target PY: socket={target.Socket}")

    # Execute tests
    target.header_loopback_test(target.Socket)
    target.short_loopback_test(target.Socket)
    target.int_loopback_test(target.Socket)
    target.long_loopback_test(target.Socket)
    target.byte_loopback_test(target.Socket)
    target.integer_loopback_test(target.Socket)
    target.bit_loopback_test(target.Socket)
    target.reg_loopback_test(target.Socket)
    target.logic_loopback_test(target.Socket)
    target.real_loopback_test(target.Socket)
    target.string_loopback_test(target.Socket)
    #target.shortV_loopback_test(target.Socket) N/A TODO
    #target.longV_loopback_test(target.Socket)
    #target.intV_loopback_test(target.Socket)
    #target.pkt_LongV_loopback_test(target.Socket)

