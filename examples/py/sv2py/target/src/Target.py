"""
============================================================================
 File        : Target.py
 Version     : 0.1
 Copyright (c) 2016-2023 IC Verimeter. All rights reserved.
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

class Target:
    
    def __init__(self):
        self.lib= Shunt()
        self.String = ""
        self.Socket = 0
        self.h_trnx = None  # Assuming cs_header_t is defined somewhere
        self.h_data = None  # Assuming cs_data_header_t is defined somewhere

    def init_target(self, portno, hostname):
        socket_id = 0
        socket_id = self.lib.shunt_py_target_init(portno, hostname)
        return socket_id
    
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

    def print_shunt_header(self, h_, name_in="", i_am=""):
        print(f"\n{i_am} {name_in}.trnx_type  = {h_.trnx_type}")
        print(f"\n{i_am} {name_in}.trnx_id    = {h_.trnx_id}")
        print(f"\n{i_am} {name_in}.data_type  = {h_.data_type}")
        print(f"\n{i_am} {name_in}.n_payloads = {h_.n_payloads}")

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

