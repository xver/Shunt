/*
 =========================================================
 File        : shunt_verilator_dpi.h
 Version     : 1.0.1
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
 Licensed under the MIT License.
 See LICENSE file in the project root for full license information.
 Description : shunt verilator integration
 
 Not supported DPI functions defines:
 Version 1.0.1 : Verilator 3.916 2017-11-25 rev verilator_3_916
 
 System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)
 ******************************************************
*/

`ifndef SHUNT_VERILATOR_DPI_H
 `define  SHUNT_VERILATOR_DPI_H
  
 `define NO_CS_DATA_HEADER_T

//syntax error, unexpected ']', expecting TYPE-IDENTIFIER
 `define NO_SHUNT_DPI_HS_RECV_BITN
 `define NO_SHUNT_DPI_HS_SEND_BITN
     
 `define NO_SHUNT_DPI_HS_RECV_BYTE
 `define NO_SHUNT_DPI_HS_SEND_BYTE

 `define NO_SHUNT_DPI_HS_RECV_INT
 `define NO_SHUNT_DPI_HS_SEND_INT
 
 `define NO_SHUNT_DPI_HS_RECV_INTEGER
 `define NO_SHUNT_DPI_HS_SEND_INTEGER

 `define NO_SHUNT_DPI_HS_RECV_LOGICN
 `define NO_SHUNT_DPI_HS_SEND_LOGICN

 `define NO_SHUNT_DPI_HS_RECV_LONG
 `define NO_SHUNT_DPI_HS_SEND_LONG

 `define NO_SHUNT_DPI_HS_RECV_REAL
 `define NO_SHUNT_DPI_HS_SEND_REAL

 `define NO_SHUNT_DPI_HS_RECV_REGN
 `define NO_SHUNT_DPI_HS_SEND_REGN

 `define NO_SHUNT_DPI_HS_RECV_SHORT
 `define NO_SHUNT_DPI_HS_SEND_SHORT
 
 `define NO_SHUNT_DPI_RECV_BITN
 `define NO_SHUNT_DPI_SEND_BITN

 `define NO_SHUNT_DPI_RECV_DATA_HEADER
 `define NO_SHUNT_DPI_SEND_DATA_HEADER

 `define NO_SHUNT_DPI_RECV_INTEGERV
 `define NO_SHUNT_DPI_SEND_INTEGERV

 `define NO_SHUNT_DPI_RECV_INTV
 `define NO_SHUNT_DPI_SEND_INTV
  
 `define NO_SHUNT_DPI_RECV_LONGV
 `define NO_SHUNT_DPI_SEND_LONGV
 
 `define NO_SHUNT_DPI_RECV_REALV
 `define NO_SHUNT_DPI_SEND_REALV


 `define NO_SHUNT_DPI_RECV_SHORTREALV
 `define NO_SHUNT_DPI_SEND_SHORTREALV

 `define NO_SHUNT_DPI_RECV_SHORTV
 `define NO_SHUNT_DPI_SEND_SHORTV

//Unsupported: SystemVerilog 2005 reserved word not implemented: shortreal
 `define NO_SHUNT_DPI_RECV_SHORTREAL
 `define NO_SHUNT_DPI_SEND_SHORTREAL

// Unsupported: SystemVerilog 2005 reserved word not implemented: shortreal
 `define NO_SHUNT_DPI_HS_RECV_SHORTREAL
 `define NO_SHUNT_DPI_HS_SEND_SHORTREAL

// Unsupported: DPI argument of type BASICDTYPE 'time
 `define NO_SHUNT_DPI_RECV_TIME
 `define NO_SHUNT_DPI_SEND_TIME


// ERROR in shunt_prim_send_int : numbytes < 0 : Bad address
 `define NO_SHUNT_DPI_RECV_INTEGER
 `define NO_SHUNT_DPI_SEND_INTEGER

// internal compiler error:
 `define NO_SHUNT_DPI_RECV_BIT
 `define NO_SHUNT_DPI_SEND_BIT

 `define NO_SHUNT_DPI_RECV_REG
 `define NO_SHUNT_DPI_SEND_REG

 `define NO_SHUNT_DPI_RECV_LOGIC
 `define NO_SHUNT_DPI_SEND_LOGIC


`endif //  `ifndef SHUNT_VERILATOR_DPI_H

