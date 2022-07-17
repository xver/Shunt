/*
 =========================================================
 File        : shunt_verilator_dpi.h
 Version     : 1.0.1
 Copyright (c) 2016-2022 IC Verimeter. All rights reserved.
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

 `define NO_SHUNT_DPI_RECV_REALV
 `define NO_SHUNT_DPI_SEND_REALV


//Unsupported: SystemVerilog 2005 reserved word not implemented: shortreal

 `define NO_SHUNT_DPI_RECV_SHORTREALV
 `define NO_SHUNT_DPI_SEND_SHORTREALV

 `define NO_SHUNT_DPI_RECV_SHORTREAL
 `define NO_SHUNT_DPI_SEND_SHORTREAL

// Unsupported: SystemVerilog 2005 reserved word not implemented: shortreal
 `define NO_SHUNT_DPI_HS_RECV_SHORTREAL
 `define NO_SHUNT_DPI_HS_SEND_SHORTREAL

`define NO_SHUNT_DPI_SEND_TIME
`define NO_SHUNT_DPI_RECV_TIME

`endif //  `ifndef SHUNT_VERILATOR_DPI_H



