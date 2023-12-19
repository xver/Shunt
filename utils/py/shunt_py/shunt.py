#============================================================================
#   File        : shunt.py
#   Version     : 0.0.1
#   Copyright (c) 2016-2023 IC Verimeter. All rights reserved.
#   Licensed under the MIT License.
#   See LICENSE file in the project root for full license information.
#  Description :  TCP/IP Python  SHUNT module
#============================================================================

import os
import random
import sys
import ctypes
import random

"""
Class:  cs_data_header
 A ctypes Structure representing  <cs_data_header> data header.
 This structure contains fields for transaction payload sizes and data type.

- data_type  SHUNT_INSTR_ENUM

- trnx_payload_sizes  array of payload sizes, number of array elements are equal to n_payloads

see <cs_header_t>
"""

class cs_data_header(ctypes.Structure):
    
    _fields_ = [
        ("trnx_payload_sizes", ctypes.POINTER(ctypes.c_int)),
         ("data_type", ctypes.c_long),
    ]
    def __getitem__(self, key):
        if self.trnx_payload_sizes is not None and 0 <= key < len(self.trnx_payload_sizes):
            return self.trnx_payload_sizes[key]
        else:
            raise IndexError("Index out of range")
    def __init__(self, data_type=0, trnx_payload_sizes=None):
        super(cs_data_header, self).__init__()
        self.data_type = data_type
        self.trnx_payload_sizes = trnx_payload_sizes

    def __str__(self):
        return (
            f"cs_data_header(data_type={self.data_type}, "
            f"trnx_payload_sizes={self.trnx_payload_sizes})"
        )

    @property
    def data_type(self):
        return self._data_type

    @data_type.setter
    def data_type(self, value):
        self._data_type = value

    @property
    def trnx_payload_sizes(self):
        return self._trnx_payload_sizes

    @trnx_payload_sizes.setter
    def trnx_payload_sizes(self, value):
        if value is not None:
            self._trnx_payload_sizes = (ctypes.c_int * len(value))(*value)
        else:
            self._trnx_payload_sizes = None

    """
    function: print_structure
    Prints cs_data_header structure.
    """
    def print_structure(self):
        print(f"data_type: {self.data_type}")
        if self.trnx_payload_sizes is not None:
            print("trnx_payload_sizes:")
            for i, size in enumerate(self.trnx_payload_sizes):
                print(f"  Element {i + 1}: {size}")
        else:
            print("trnx_payload_sizes: None")

"""
class: cs_header
A ctypes Structure representing  <cs_header> communication protocol.
This structure includes fields for transaction type, ID, data type, and number of payloads.

- trnx_type  user defined transaction attribute

- trnx_id  user defined unique transaction number

- data_type  <SHUNT_INSTR_ENUM>

- n_payloads  number of data payloads (for Array number of vectors)

see <cs_header> <cs_header_t>
"""

class cs_header(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("n_payloads", ctypes.c_long),
        ("data_type", ctypes.c_long),
        ("trnx_id", ctypes.c_long),
        ("trnx_type", ctypes.c_long),
    ]

    def __init__(self, trnx_type=0, trnx_id=0, data_type=0, n_payloads=0):
        super(cs_header, self).__init__()
        self.trnx_type = trnx_type
        self.trnx_id = trnx_id
        self.data_type = data_type
        self.n_payloads = n_payloads

    def __str__(self):
        return (
            f"class cs_header(trnx_type={self.trnx_type}, "
            f"trnx_id={self.trnx_id}, data_type={self.data_type}, "
            f"n_payloads={self.n_payloads})"
        )
    def __getitem__(self, key):
        if key == 0:
            return self.trnx_type
        elif key == 1:
            return self.trnx_id
        elif key == 2:
            return self.data_type
        elif key == 3:
            return self.n_payloads
        else:
            raise IndexError("Index out of range")
    
    @property
    def trnx_type(self):
        return self._trnx_type

    @trnx_type.setter
    def trnx_type(self, value):
        self._trnx_type = value

    @property
    def trnx_id(self):
        return self._trnx_id

    @trnx_id.setter
    def trnx_id(self, value):
        self._trnx_id = value

    @property
    def data_type(self):
        return self._data_type

    @data_type.setter
    def data_type(self, value):
        self._data_type = value

    @property
    def n_payloads(self):
        return self._n_payloads

    @n_payloads.setter
    def n_payloads(self, value):
        self._n_payloads = value
 
    """    
    function: print_structure
    Prints cs_header structure.
    """
    def print_structure(self):
        print(f"trnx_type: {self.trnx_type}")
        print(f"trnx_id: {self.trnx_id}")
        print(f"data_type: {self.data_type}")
        print(f"n_payloads: {self.n_payloads}")

"""
class: SVpiVecVal
A ctypes Structure representing a verilog vector  aval/bval of 4-state data type,32-bit signed integer LRM 6.11 Integer data types
Contains two 32-bit unsigned integers.

--- Code
bval aval | 4-state verilog value
----------|----------------------
  0    0  |   0
  0    1  |   1
  1    0  |   X
  1    1  |   Z
---

"""
 
class SVpiVecVal(ctypes.Structure):
    _fields_ = [
                ("bval", ctypes.c_uint32),
                ("aval", ctypes.c_uint32),
                ]

    def __getitem__(self, key):
        if key == 0:
            return self.aval
        elif key == 1:
            return self.bval
        else:
            raise IndexError("Index out of range")
    @property
    def aval(self):
        return self.aval

    @aval.setter
    def aval(self, value):

        self.aval = value

    @property
    def bval(self):
        return self.bval

    @bval.setter
    def bval(self, value):
        self.bval = value

"""
Class: Shunt
Python to System Verilog bridge

TODO:   shunt_py_tlm_send_command shunt_py_tlm_send_gp_transport shunt_py_tlm_recv_gp_transport shunt_py_tlm_recv_gp_header shunt_py_tlm_send_gp_header shunt_py_tlm_recv_axi3_header shunt_py_tlm_send_axi3_header shunt_py_tlm_recv_gp_data

TODO:  shunt_py_send_bitN shunt_py_recv_bitN  shunt_py_send_longV shunt_py_recv_longV shunt_py_send_data_header  shunt_py_recv_data_header

Not Implemented Features: shunt_py_send_realtime shunt_py_recv_realtime shunt_py_send_shortreal shunt_py_recv_shortreal

"""
class Shunt:

    def __init__(self):
        self.shunthome = os.environ['SHUNT_HOME'] + "/bin"
        sys.path.insert(0,self.shunthome)
        self.shunt_lib = ctypes.CDLL(self.shunthome + "/libCutils.so")

    """
    Function: shunt_py_target_init
    TCP/IP target initialization
    
    Parameters:
    - portno: socket port
    - hostname: initiator name
    
    Returns:
    - socket id
    
    See Also:
    - <shunt_prim_init_target>
    - <shunt_cs_init_target>
    
    NOTE:
    If portno_in = 0 -- assign a free client-server TCP port.
    SHUNT_DEFAULT_TCP_PORT is reserved for the dynamic allocation of the client-server TCP port.
    """
    def shunt_py_target_init(self, portno, hostname):
        shunt_cs_init_target = self.shunt_lib.shunt_cs_init_target
        shunt_cs_init_target.argtypes = [ctypes.c_uint, ctypes.c_char_p]
        shunt_cs_init_target.restype = ctypes.c_int

        hostname_in = ctypes.c_char_p(hostname.encode('utf-8'))
        Result_ = shunt_cs_init_target(portno, hostname_in)
        
        return Result_ 

    """
    Function: shunt_py_initiator_init
    TCP/IP "one server" - "one target" point-to-point initiator initialization
    
    Parameters:
    - portno: socket port
    
    Returns:
    - socket id
    
    See Also:
    - <shunt_prim_init_initiator>
    - <shunt_cs_init_initiator>
    
    NOTE:
    If portno_in = 0 -- assign a free client-server TCP port.
    SHUNT_DEFAULT_TCP_PORT is reserved for the dynamic allocation of the client-server TCP port.
    """
    def shunt_py_initiator_init(self, portno):        
        shunt_cs_init_initiator = self.shunt_lib.shunt_cs_init_initiator
        shunt_cs_init_initiator.argtypes = [ctypes.c_uint]
        shunt_cs_init_initiator.restype = ctypes.c_uint

        Result_ = shunt_cs_init_initiator(portno)
        return Result_

    """
    Function: shunt_py_close_socket
    Terminates TCP socket
    
    Parameters:
    - fd: socket id
    
    Returns:
    - N/A
    """
    def shunt_py_close_socket(self, fd):        
        shunt_prim_close_socket = self.shunt_lib.shunt_prim_close_socket
        shunt_prim_close_socket.argtypes = [ctypes.c_int]
        shunt_prim_close_socket.restype = None
        
        shunt_prim_close_socket(fd)

    """
    Function: shunt_py_unblock_socket
    Sets TCP socket unblocked mode
    
    Parameters:
    - flag: 1/0 - unblocked(default)/blocked
    - fd: socket id
    
    Returns:
    - N/A
    """
    def shunt_py_unblock_socket(self, flag, fd):        
        shunt_prim_unblock_socket = self.shunt_lib.shunt_prim_unblock_socket
        shunt_prim_unblock_socket.argtypes = [ctypes.c_int, ctypes.c_int]
        shunt_prim_unblock_socket.restype = None

        shunt_prim_unblock_socket(flag, fd)

    """
    Function: shunt_py_tcp_nodelay_socket
    Enable/disable Nagle algorithm (TCP_NODELAY)
    
    Parameters:
    - flag: 1/0 - enable/disable Nagle algorithm (TCP_NODELAY)
    - sockfd: socket id
    
    Returns:
    - N/A
    """

    def shunt_py_tcp_nodelay_socket(self, flag, sockfd):        
        shunt_prim_tcp_nodelay_socket = self.shunt_lib.shunt_prim_tcp_nodelay_socket
        shunt_prim_tcp_nodelay_socket.argtypes = [ctypes.c_int, ctypes.c_int]
        shunt_prim_tcp_nodelay_socket.restype = None

        shunt_prim_tcp_nodelay_socket(flag, sockfd)

    """
    Function: shunt_py_get_status_socket
    Returns status for <fd> TCP socket <event>
    
    Parameters:
    - fd: socket id
    - event: short event - the <event> mask is specifying following
    - 0 - is equal to POLLIN, data is ready to recv()
    - 1 - is equal to POLLOUT, socket can send() data to this socket without blocking
    - else is equal to POLLNVAL, function returns "process failed" status;
    
    Returns:
    - socket event status
    - "0" - No <event>
    - "-1" - <event> process has failed
    - "1" - <event> occurs
    """
    def shunt_py_get_status_socket(self, fd, event):            
        shunt_prim_get_status_socket = self.shunt_lib.shunt_prim_get_status_socket
        shunt_prim_get_status_socket.argtypes = [ctypes.c_int, ctypes.c_int]
        shunt_prim_get_status_socket.restype = ctypes.c_int

        Result_ = shunt_prim_get_status_socket(fd, event)
        return Result_  

    """
    Function: shunt_py_listener_init
    Multi-Slave TCP IP initialization, create TCP/IP a parent(listener) and start listening for client connections
    
    Parameters:
    - portno: socket port
    
    Returns:
    - socket id - parent socket id
    """
    def shunt_py_listener_init(self, portno):        
        shunt_prim_tcp_parent_init_initiator = self.shunt_lib.shunt_prim_tcp_parent_init_initiator
        shunt_prim_tcp_parent_init_initiator.argtypes = [ctypes.c_uint]
        shunt_prim_tcp_parent_init_initiator.restype = ctypes.c_uint

        Result_ = shunt_prim_tcp_parent_init_initiator(portno)
        return Result_

    """
    Function: shunt_py_tcp_connect
    Multi-Slave TCP IP initialization, establish TCP/IP initiator-target connection
    
    Parameters:
    - parentfd: socket id - parent socket id
    
    Returns:
    - socket id - child socket id
    """
    def shunt_py_tcp_connect(self, parentfd):        
        shunt_prim_tcp_child_init_initiator = self.shunt_lib.shunt_prim_tcp_child_init_initiator
        shunt_prim_tcp_child_init_initiator.argtypes = [ctypes.c_uint]
        shunt_prim_tcp_child_init_initiator.restype = ctypes.c_uint

        Result_ = shunt_prim_tcp_child_init_initiator(parentfd)
        return Result_   

    """
    Function: shunt_py_tcp_get_port
    Finds TCP/IP port with the specified socket id
    
    Parameters:
    - socket: socket id
    
    Returns:
    - a corresponding TCP/IP port
    
    Also see shunt_cs_update_dynamic_port
    """
    def shunt_py_tcp_get_port(self, socket):        
        shunt_cs_update_dynamic_port = self.shunt_lib.shunt_cs_update_dynamic_port
        shunt_cs_update_dynamic_port.argtypes = [ctypes.c_uint]
        shunt_cs_update_dynamic_port.restype = shunt_dynamic_port
        
        dynamic_port = shunt_cs_update_dynamic_port(socket)
        Result_ = dynamic_port.port_number
        return Result_

    """
    Function: shunt_py_tcp_parent_init_initiator_dpa
    PY equivalent of the shunt_cs_tcp_parent_init_initiator_dp
    
    Parameters:
    - N/A
    
    Returns:
    - socket id - DPA parent socket id
    """
    def shunt_py_tcp_parent_init_initiator_dpa(self):        
        shunt_cs_tcp_parent_init_initiator_dpa = self.shunt_lib.shunt_cs_tcp_parent_init_initiator_dpa
        shunt_cs_tcp_parent_init_initiator_dpa.argtypes = []
        shunt_cs_tcp_parent_init_initiator_dpa.restype = ctypes.c_uint

        Result_ = shunt_cs_tcp_parent_init_initiator_dpa()
        return Result_

    """
    Function: shunt_py_send_short
    Send Verilog "shortint" / C "short int" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Short: data
    
    Returns:
    - number of bytes have been sent : success > 0

    See Also:
    - <shunt_prim_send_short>
    - <shunt_dpi_recv_short>
    """
    def shunt_py_send_short(self, sockfd, Short):        
        shunt_prim_send_short = self.shunt_lib.shunt_prim_send_short
        shunt_prim_send_short.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_short)]
        shunt_prim_send_short.restype = ctypes.c_int

        short_in = ctypes.c_short();
        short_in.value=Short
        Result_ = shunt_prim_send_short(sockfd,short_in)

        return Result_
    
    """
    Function: shunt_py_recv_short
    Fetch Verilog "shortint"/C "short int" data from TCP/IP socket
    
    Parameters:
    - sockfd: socket id
    - Short: data
    
    Returns:
    - number of bytes have been received : success > 0
    - Short: data
    
    See Also:
    - <shunt_prim_recv_short>
    - <shunt_dpi_send_short>
    """
    def shunt_py_recv_short(self, sockfd):
        shunt_prim_recv_short = self.shunt_lib.shunt_prim_recv_short
        shunt_prim_recv_short.argtypes = [ctypes.c_int]
        shunt_prim_recv_short.restype = ctypes.c_int
        Short = ctypes.c_short()

        Result_ = shunt_prim_recv_short(sockfd, ctypes.byref(Short))
        value = Short.value
        return Result_,value

    """
    Function: shunt_py_send_long
    Send Verilog "longint" / C "long" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Long: data
    
    Returns:
    - number of bytes have been sent : success > 0
    
    See Also:
    - <shunt_prim_send_long>
    - <shunt_dpi_recv_long>
    """
    def  shunt_py_send_long(self,sockfd,Long):
        shunt_prim_send_long = self.shunt_lib.shunt_prim_send_long
        shunt_prim_send_long.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_ulonglong)]
        shunt_prim_send_long.restype = ctypes.c_int

        long_val = ctypes.c_ulonglong(Long)
        return shunt_prim_send_long(sockfd, ctypes.byref(long_val))

    """
    Function: shunt_py_recv_long
    Fetch Verilog "longint" / C "long" data from TCP/IP socket
    
    Parameters:
    - sockfd: socket id
     
    Returns:
    - number of bytes have been received : success > 0
    - Long: data
    
    See Also:
    - <shunt_prim_recv_long>
    - <shunt_dpi_send_long>
    """
    def shunt_py_recv_long(self,sockfd):

        shunt_prim_recv_long = self.shunt_lib.shunt_prim_recv_long
        shunt_prim_recv_long.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_ulonglong)]
        shunt_prim_recv_long.restype = ctypes.c_int
        Long = ctypes.c_ulonglong()
    
        Result_ = shunt_prim_recv_long(sockfd, ctypes.byref(Long))
        value = Long.value
        return Result_, value
    
    """
    Function: shunt_py_send_int
    Send Verilog/C "int" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Int: data
    
    Returns:
    - number of bytes have been sent : success > 0
    
    See Also:
    - <shunt_prim_send_int>
    - <shunt_dpi_recv_int>
    """
    def shunt_py_send_int(self,sockfd,Int):
        
        shunt_prim_send_int = self.shunt_lib.shunt_prim_send_int
        shunt_prim_send_int.argtypes = [ctypes.c_uint, ctypes.POINTER(ctypes.c_int)]
        shunt_prim_send_int.restype = ctypes.c_int
        int_val = ctypes.c_int(Int)
        return shunt_prim_send_int(sockfd, ctypes.byref(int_val))
    
    """
    Function: shunt_py_recv_int
    Fetch Verilog/C "int" data from TCP/IP socket
    
    Parameters:
    - sockfd: socket id
  
    Returns:
    - number of bytes have been received : success > 0
    - Int: data
    
    See Also:
    - <shunt_prim_recv_int>
    - <shunt_dpi_send_int>
    """
    def shunt_py_recv_int(self,sockfd):
        shunt_prim_recv_int = self.shunt_lib.shunt_prim_recv_int
        shunt_prim_recv_int.argtypes = [ctypes.c_uint, ctypes.POINTER(ctypes.c_int)]
        shunt_prim_recv_int.restype = ctypes.c_int
        int_val = ctypes.c_int()
        
        Result_ = shunt_prim_recv_int(sockfd, ctypes.byref(int_val))
        return Result_, int_val.value

    """
    Function: shunt_py_send_real
    Send Verilog "real"/C "double" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Real: data
    
    Returns:
    - number of bytes have been sent : success > 0
    
    See Also:
    - <shunt_prim_send_double>
    - <shunt_dpi_recv_real>
    """
    def  shunt_py_send_real(self,sockfd,Real):
        shunt_prim_send_double = self.shunt_lib.shunt_prim_send_double
        shunt_prim_send_double.argtypes = [ctypes.c_uint, ctypes.POINTER(ctypes.c_double)]
        shunt_prim_send_double.restype = ctypes.c_int
        real_in = ctypes.c_double()
        real_in.value = Real
        Result_ = shunt_prim_send_double(sockfd,real_in)
        return Result_ 

    """
    Function: shunt_py_recv_real
    Fetch Verilog "real"/C "double" data from TCP/IP socket
    
    Parameters:
    - sockfd: socket id
        
    Returns:
    - number of bytes have been sent : success > 0
    - Real: data
     
    See Also:
    - <shunt_prim_recv_double>
    - <shunt_dpi_send_real>
    """
    def shunt_py_recv_real(self,sockfd):
        shunt_prim_recv_double = self.shunt_lib.shunt_prim_recv_double
        shunt_prim_recv_double.argtypes = [ctypes.c_uint, ctypes.POINTER(ctypes.c_double)]
        shunt_prim_recv_double.restype = ctypes.c_int
        real_val = ctypes.c_double()
        
        Result_ = shunt_prim_recv_double(sockfd, real_val)
        Real = real_val.value
        return Result_,Real
    
   
    """
    Function: shunt_py_send_byte
    Send Verilog "byte"/C "char" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Byte: data
    
    Returns:
    - number of bytes have been sent : success = 1
    
    See Also:
    - <shunt_prim_send_byte>
    - <shunt_dpi_recv_byte>
    """
    def shunt_py_send_byte(self,sockfd,Byte):
        shunt_prim_send_byte = self.shunt_lib.shunt_prim_send_byte
        shunt_prim_send_byte.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_byte)]
        shunt_prim_send_byte.restype = ctypes.c_int

        byte_in = ctypes.c_byte(Byte)
        result = shunt_prim_send_byte(sockfd, ctypes.byref(byte_in))

        return result
    """
    Function: shunt_py_recv_byte
    Fetch verilog "byte"/C "char" over TCP/IP
    
    Parameters:
    - sockfd: socket id

    Returns:
    - number of bytes have been received: success = 1
    - Byte - data
    """
    def shunt_py_recv_byte(self,sockfd):
    
        shunt_prim_recv_byte = self.shunt_lib.shunt_prim_recv_byte
        shunt_prim_recv_byte.argtypes = [ctypes.c_int]
        shunt_prim_recv_byte.restype = ctypes.c_int
        Byte = ctypes.c_byte()

        Result_ = shunt_prim_recv_byte(sockfd, ctypes.byref(Byte))
        value = Byte.value
        return Result_, value    
    
    """
    Function: shunt_py_send_bit
    Send Verilog "byte"/C "char" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Bit: data
    
    Returns:
    - number of bytes have been sent : success = 1
    
    See Also:
    - <shunt_prim_send_byte>
    - <shunt_dpi_recv_bit>
    """
    def shunt_py_send_bit(self,sockfd,Bit):
        shunt_prim_send_byte = self.shunt_lib.shunt_prim_send_byte
        shunt_prim_send_byte.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_byte)]
        shunt_prim_send_byte.restype = ctypes.c_int

        Bit_in = ctypes.c_byte(Bit)
        Result_ = shunt_prim_send_byte(sockfd, ctypes.byref(Bit_in))

        return Result_
    
    """
    Function: shunt_py_recv_bit
    Fetch Verilog "byte"/C "char" data from TCP/IP socket
    
    Parameters:
    - sockfd: socket id
    
    Returns:
    - number of bytes have been sent : success = 1
    - Bit: data
    
    See Also:
    - <shunt_prim_recv_byte>
    - <shunt_dpi_send_bit>
    """
    def shunt_py_recv_bit(self,sockfd):
        shunt_prim_recv_byte = self.shunt_lib.shunt_prim_recv_byte
        shunt_prim_recv_byte.argtypes = [ctypes.c_int]
        shunt_prim_recv_byte.restype = ctypes.c_int
        Bit = ctypes.c_byte()

        Result_ = shunt_prim_recv_byte(sockfd, ctypes.byref(Bit))
        value = Bit.value
        return Result_, value
        
    """
    Function: shunt_py_send_reg
    Send Verilog "reg"/C "char" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Reg: data
    
    Returns:
    - number of bytes have been sent : success = 1
    
    See Also:
    - <shunt_prim_send_byte>
    - <shunt_dpi_recv_reg>
    """   
    def shunt_py_send_reg(self,sockfd,Reg):
        shunt_prim_send_byte = self.shunt_lib.shunt_prim_send_byte
        shunt_prim_send_byte.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_byte)]
        shunt_prim_send_byte.restype = ctypes.c_int

        Reg_in = ctypes.c_byte(Reg)
        Result_ = shunt_prim_send_byte(sockfd, ctypes.byref(Reg_in)) 
        return Result_

    """
    Function: shunt_py_recv_reg
    Fetch Verilog "reg"/C "char" data from TCP/IP socket
    
    Parameters:
    - sockfd: socket id
    
    Returns:
    - number of bytes have been sent : success = 1
    - Reg: data
    
    See Also:
    - <shunt_prim_recv_reg>
    - <shunt_dpi_send_byte>
    """    
    def shunt_py_recv_reg(self,sockfd):
        shunt_prim_recv_byte = self.shunt_lib.shunt_prim_recv_byte
        shunt_prim_recv_byte.argtypes = [ctypes.c_int]
        shunt_prim_recv_byte.restype = ctypes.c_int
        Reg = ctypes.c_byte()

        Result_ = shunt_prim_recv_byte(sockfd, ctypes.byref(Reg))
        value = Reg.value
        return Result_, value

    """
    Function: shunt_py_send_logic
    Send Verilog "byte"/C "char" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Logic: data
    
    Returns:
    - number of bytes have been sent : success = 1
    
    See Also:
    - <shunt_prim_send_byte>
    - <shunt_dpi_recv_logic>
    """
    def shunt_py_send_logic(self,sockfd,Logic):
        shunt_prim_send_byte = self.shunt_lib.shunt_prim_send_byte
        shunt_prim_send_byte.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_byte)]
        shunt_prim_send_byte.restype = ctypes.c_int

        Logic_in = ctypes.c_byte(Logic)
        Result_ = shunt_prim_send_byte(sockfd, ctypes.byref(Logic_in)) 
        return Result_

    """
    Function: shunt_py_recv_logic
    Fetch Verilog "byte"/C "char" data from TCP/IP socket
    
    Parameters:
    - sockfd: socket id
    
    Returns:
    - number of bytes have been sent : success = 1
    - Logic: data
    
    See Also:
    - <shunt_prim_recv_byte>
    - <shunt_dpi_send_logic>
    """
    def shunt_py_recv_logic(self,sockfd):
        
        shunt_prim_recv_byte = self.shunt_lib.shunt_prim_recv_byte
        shunt_prim_recv_byte.argtypes = [ctypes.c_int]
        shunt_prim_recv_byte.restype = ctypes.c_int
        Logic = ctypes.c_byte()

        Result_ = shunt_prim_recv_byte(sockfd, ctypes.byref(Logic))
        value = Logic.value
        return Result_, value

    """
    Send Verilog "int"/C "int" data over TCP/IP
    
    Parameters:
    sockfd   - socket id
    integer  - SVpiVecVal, data
    
    Returns:
    number of bytes have been sent : success > 0
    
    See Also:
    - <shunt_prim_send_integer>
    - <shunt_dpi_recv_integer>
    """
    def shunt_py_send_integer(self,sockfd,integer):
        shunt_prim_send_integer = self.shunt_lib.shunt_prim_send_integer
        shunt_prim_send_integer.argtypes = [ctypes.c_int, ctypes.POINTER(SVpiVecVal)]
        shunt_prim_send_integer.restype = ctypes.c_int

        integer_val = SVpiVecVal(aval=integer.aval, bval=integer.bval)
        Result_ = shunt_prim_send_integer(sockfd, ctypes.byref(integer_val))

        return Result_
    
    """
    Function: shunt_py_recv_integer
    Fetch Verilog "reg[31:0] 4 state aval,bval" data from TCP/IP
    
    Parameters:
    - sockfd: socket id
    
    
    Returns:
    - number of bytes have been received : success > 0
    - Integer: data

    See Also:
    - <shunt_prim_recv_integer>
    - <shunt_dpi_send_integer>
    """
    def shunt_py_recv_integer(self,sockfd):
        
        shunt_prim_recv_integer = self.shunt_lib.shunt_prim_recv_integer
        shunt_prim_recv_integer.argtypes = [ctypes.c_int]
        shunt_prim_recv_integer.restype = ctypes.c_int
        integer = SVpiVecVal()

        Result_ = shunt_prim_recv_integer(sockfd, ctypes.byref(integer))
        return Result_, integer
    
    """
    Function: shunt_py_send_time
    Send Verilog "reg[31:0] 4 state aval,bval" data over TCP/IP
    
    Parameters:
    - sockfd: socket id
    - Time: data
    
    Returns:
    - number of bytes have been sent : success > 0
    
    See Also:
    - <shunt_prim_send_int>
    - <shunt_dpi_recv_time>
    """

    def shunt_py_send_time(self,sockfd,Time):
        Result_ = 1
        for i in range(2):
            if self.shunt_dpi_send_int(sockfd, Time[i].aval) <= 0:
                Result_ = 0
            if self.shunt_dpi_send_int(sockfd, Time[i].bval) <= 0:
                Result_ = 0
        return Result_

    """
    Function: shunt_py_recv_time
    Fetch Verilog "reg[31:0] 4 state aval,bval" data from TCP/IP
    
    Parameters:
    - sockfd: socket id
    
    Returns:
    - number of bytes have been received : success > 0
     - Time: data

    See Also:
    - <shunt_prim_recv_int>
    - <shunt_dpi_send_time>
    """
    def shunt_py_recv_time(self,sockfd):
        Result_ = 1
        Time = SVpiVecVal()
        Time_aval =0
        Time_bval = 0

        Result_,Time_aval= self.shunt_py_recv_int(sockfd)
        Result_ = max(Result_, 0)
        Result_,Time_bval = self.shunt_py_recv_int(sockfd)
        Result_ = max(Result_, 0)
        Time.aval = Time_aval
        

        return Result_, Time
    
    """
    Function: shunt_py_send_string
    Send SHUNT transaction with verilog string/C char* elements over TCP/IP
        
    Parameters:
    - sockid: socket id
    - size: number of string elements
    - string: data
    
    Returns:
    - number of elements have been sent : success > 0
    
    See Also:
    - <shunt_cs_send_byteV>
    - <shunt_dpi_recv_string>
    """
    def shunt_py_send_string(self,sockfd,String):
        shunt_cs_send_byteV = self.shunt_lib.shunt_cs_send_byteV
        shunt_cs_send_byteV.argtypes = [ctypes.c_int, ctypes.POINTER(cs_header), ctypes.c_char_p]
        shunt_cs_send_byteV.restype = ctypes.c_int
        
        h_ = cs_header()
        Result_ = 0
        
        h_.trnx_type = random.randint(0,1000000)
        h_.trnx_id = random.randint(0,1000000)
        h_.data_type = self.shunt_py_hash("SHUNT_BYTE")
        h_.n_payloads = ctypes.c_longlong(len(String))

        Result_ = shunt_cs_send_byteV(sockfd,h_, String)
        return Result_
        
    """
    Function: shunt_py_recv_string
    Fetch SHUNT transaction with verilog string/C char* elements from TCP/IP
    
    Parameters:
    - sockid: socket id
    - size: number of string elements
    
    Returns:
    - number of elements have been received: success > 0
    - String: data
    
    See Also:
    - <shunt_dpi_send_string>
    - <shunt_dpi_recv_string>
    """

    def shunt_py_recv_string(self,sockfd,size):
        shunt_cs_recv_byteV = self.shunt_lib.shunt_cs_recv_byteV
        shunt_cs_recv_byteV.argtypes = [ctypes.c_int, ctypes.POINTER(cs_header), ctypes.POINTER(ctypes.c_char)]
        shunt_cs_recv_byteV.restype = ctypes.c_int
        
        h_ = cs_header()
        Result_ = 0

        h_.trnx_type = 0
        h_.trnx_id = 0
        h_.data_type = self.shunt_py_hash("SHUNT_BYTE")
        h_.n_payloads = size
        
        string = (ctypes.c_char * h_.n_payloads)()
        Result_ = shunt_cs_recv_byteV(sockfd,h_,string)
        return Result_ , string

    """
    Function: shunt_py_get_cs_header_id
    Predefined hash functions for obtaining the specific hash value.
    
    Parameters:
    - N/A
    
    Returns:
    - long: hash value
    
    See Also:
    - <shunt_cs_get_cs_header_leader>
    - <shunt_cs_get_tlm_header_leader>
    - <shunt_cs_get_tlm_data_leader>
    - <shunt_cs_get_tlm_axi3_ext_leader>
    - <shunt_cs_get_tlm_axi3_signal_leader>
    """
    def shunt_py_get_cs_header_id(self,sockfd):
        shunt_dpi_get_cs_header_id = self.shunt_lib.shunt_dpi_get_cs_header_id
        shunt_dpi_get_cs_header_id.argtypes = []
        shunt_dpi_get_cs_header_id.restype = ctypes.c_long

        Result_ = shunt_dpi_get_cs_header_id()
        return Result

    """
    Function: shunt_py_tlm_header_id
    Predefined hash functions for obtaining the specific hash value.
    
    Parameters:
    - N/A
    
    Returns:
    - long: hash value
    
    See Also:
    - <shunt_cs_get_cs_header_leader>
    - <shunt_cs_get_tlm_header_leader>
    - <shunt_cs_get_tlm_data_leader>
    - <shunt_cs_get_tlm_axi3_ext_leader>
    - <shunt_cs_get_tlm_axi3_signal_leader>
    """
    def shunt_py_tlm_header_id(self,sockfd):
        
        shunt_dpi_get_cs_header_id = self.shunt_lib.shunt_cs_get_tlm_header_leader
        shunt_cs_get_tlm_header_leader.argtypes = []
        shunt_cs_get_tlm_header_leader.restype = ctypes.c_long
    
        Result_ = shunt_cs_get_tlm_header_leader()
        return Result_

    """
    Function: shunt_py_tlm_data_id
    Predefined hash functions for obtaining the specific hash value.
    
    Parameters:
    - N/A
    
    Returns:
    - long: hash value
    
    See Also:
    - <shunt_cs_get_cs_header_leader>
    - <shunt_cs_get_tlm_header_leader>
    - <shunt_cs_get_tlm_data_leader>
    - <shunt_cs_get_tlm_axi3_ext_leader>
    - <shunt_cs_get_tlm_axi3_signal_leader>
    """
    def shunt_dpi_tlm_data_id(self,sockfd):
        shunt_dpi_get_cs_header_id = self.shunt_lib.shunt_cs_get_tlm_data_leader
        shunt_cs_get_tlm_data_leader.argtypes = []
        shunt_cs_get_tlm_data_leader.restype = ctypes.c_long
    
        Result_ = shunt_cs_get_tlm_data_leader()
        return Result_

    """
    Function: shunt_py_tlm_axi3_ext_id
    Predefined hash functions for obtaining the specific hash value.
    
    Parameters:
    - N/A
    
    Returns:
    - long: hash value
    
    See Also:
    - <shunt_cs_get_cs_header_leader>
    - <shunt_cs_get_tlm_header_leader>
    - <shunt_cs_get_tlm_data_leader>
    - <shunt_cs_get_tlm_axi3_ext_leader>
    - <shunt_cs_get_tlm_axi3_signal_leader>
    """
    def shunt_py_tlm_axi3_ext_id(self,sockfd):
        shunt_dpi_get_cs_header_id = self.shunt_lib. shunt_cs_get_tlm_axi3_ext_leader
        shunt_cs_get_tlm_axi3_ext_leader.argtypes = []
        shunt_cs_get_tlm_axi3_ext_leader.restype = ctypes.c_long
    
        Result_ =  shunt_cs_get_tlm_axi3_ext_leader()
        return Result_

    """
    Function: shunt_py_tlm_signal_id
    Predefined hash functions for obtaining the specific hash value.
    
    Parameters:
    - N/A
    
    Returns:
    - long: hash value
    
    See Also:
    - <shunt_cs_get_cs_header_leader>
    - <shunt_cs_get_tlm_header_leader>
    - <shunt_cs_get_tlm_data_leader>
    - <shunt_cs_get_tlm_axi3_ext_leader>
    - <shunt_cs_get_tlm_axi3_signal_leader>
    """
    def shunt_py_tlm_signal_id(self,sockfd):
        shunt_dpi_get_cs_header_id = self.shunt_lib.shunt_cs_get_tlm_axi3_signal_leader
        shunt_cs_get_tlm_axi3_signal_leader.argtypes = []
        shunt_cs_get_tlm_axi3_signal_leader.restype = ctypes.c_long
        
        Result_ = shunt_cs_get_tlm_axi3_signal_leader()
        return Result_

    #TODO   shunt_py_tlm_send_command shunt_py_tlm_send_gp_transport shunt_py_tlm_recv_gp_transport shunt_py_tlm_recv_gp_header shunt_py_tlm_send_gp_header shunt_py_tlm_recv_axi3_header shunt_py_tlm_send_axi3_header shunt_py_tlm_recv_gp_data 
    
    """
    Function: shunt_py_hash
    Simple hash function.
    
    Parameters:
    - s: hash key
    
    Returns:
    - hash value
    
    Example Usage:
    hash_key = "example_key" Replace with your hash key
    hash_value = shunt_dpi_hash(hash_key)
    print(f"Hash value for key '{hash_key}': {hash_value}")
    """
    def shunt_py_hash(self,string):
        shunt_prim_hash = self.shunt_lib.shunt_prim_hash
        shunt_prim_hash.argtypes = [ctypes.c_char_p]
        shunt_prim_hash.restype = ctypes.c_longlong

        Result_ = shunt_prim_hash(string.encode('utf-8'))
        return Result_

    """
    Function: shunt_py_send_header
    Send SHUNT header over TCP/IP.
    
    Parameters:
    - sockid: socket id from init server/target
    - h: cs_header structure
    
    Returns:
    - number of elements have been sent: success > 0
    """
    def shunt_py_send_header(self,sockfd,h):
        shunt_cs_send_header = self.shunt_lib.shunt_cs_send_header
        shunt_cs_send_header.argtypes = [ctypes.c_int, ctypes.POINTER(cs_header)]
        shunt_cs_send_header.restype = ctypes.c_int
        
        Result_ = shunt_cs_send_header(sockfd, h)
        return Result_

    """
    Function: shunt_py_recv_header
    Fetch SHUNT transaction header from TCP/IP socket.
    
    Parameters:
    - sockid: socket id from init server/target
        
    Returns:
    - number of elements have been received: success > 0
    - h: cs_header structure
    
    """
    def shunt_py_recv_header(self,sockfd):
        shunt_cs_recv_header = self.shunt_lib.shunt_cs_recv_header
        shunt_cs_recv_header.argtypes = [ctypes.c_int, ctypes.POINTER(cs_header)]
        shunt_cs_recv_header.restype = ctypes.c_int

        h = cs_header()

        Result_  = self.shunt_lib.shunt_cs_recv_header(sockfd, h)
        return Result_ ,h

    

   #TODO shunt_py_send_bitN shunt_py_recv_bitN  shunt_py_send_longV shunt_py_recv_longV
