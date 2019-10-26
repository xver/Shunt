/*
============================================================================
 File        : shunt_fringe_pkg .sv
 Version     : 1.0.0
 Copyright (c) 2019 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : SV interface for the Fringe TCP handshake framework
 ============================================================================
*/
//SrcDsts
`ifndef  FRNG_N_OF_SRCDSTS
 `define FRNG_N_OF_SRCDSTS  2
`endif

`ifndef  FRNG_N_OF_SIGNALS
 `define FRNG_N_OF_SIGNALS  8
`endif

`ifndef  FRNG_MAX_N_OF_BITS_PER_SIGNAL
 `define FRNG_MAX_N_OF_BITS_PER_SIGNAL 1024 
`endif

`ifndef  FRNG_MAX_N_OF_PAYLOADS_PER_SIGNAL
 `define FRNG_MAX_N_OF_PAYLOADS_PER_SIGNAL 16
`endif

`ifndef  FRNG_N_OF_BITS_PER_PAYLOAD
 `ifdef  SHUNT_VERILATOR_DPI_H 
  `define FRNG_N_OF_BITS_PER_PAYLOAD 64
 `endif 
 `ifndef SHUNT_VERILATOR_DPI_H   
  `define FRNG_N_OF_BITS_PER_PAYLOAD `FRNG_MAX_N_OF_BITS_PER_SIGNAL
 `endif
`endif

`ifndef  FRNG_N_OF_PAYLOADS
 `define FRNG_N_OF_PAYLOADS (`FRNG_N_OF_SIGNALS*(`FRNG_MAX_N_OF_BITS_PER_SIGNAL/`FRNG_N_OF_BITS_PER_PAYLOAD))
`endif

package  shunt_fringe_pkg;
 /* verilator lint_off UNDRIVEN */  
   import shunt_dpi_pkg::*;
   
   
   /* 
    * About: Fringe enum: 
    *
    */
   /*
    *  Fringe SrcDst DB status::
    *
    * (start code) 
    typedef enum  {FRNG_SRCDST_IDLE, FRNG_SRCDST_ACTIVE,FRNG_INITIATOR_ACTIVE,FRNG_TARGET_ACTIVE,FRNG_SRCDST_FINISH,FRNG_SRCDST_STOP} fringe_SrcDst_status_e;
    * (end code)
    *fringe_SrcDst_status_e defines PnP status flags for PnP endpoints (EP)  
    * 
    */
   typedef enum  {FRNG_SRCDST_IDLE, FRNG_SRCDST_ACTIVE,FRNG_INITIATOR_ACTIVE,FRNG_TARGET_ACTIVE,FRNG_SRCDST_FINISH,FRNG_SRCDST_STOP} fringe_SrcDst_status_e;
   
   /*
    *  Fringe data type::
    *
    * (start code) 
    * typedef enum {SHUNT_NA,SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_BIT,SHUNT_LOGIC,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} fringe_signal_type_e;  
    * (end code)
    */
   //typedef enum {SHUNT_NA,SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_BIT,SHUNT_LOGIC,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} fringe_signal_type_e;


   /*
    *  Fringe port type::
    *
    * (start code) 
    * typedef enum {FRNG_PORT_NA,FRNG_PORT_INPUT,FRNG_PORT_OUTPUT,FRNG_PORT_INOUT} fringe_port_type_e;  
    * (end code)
    */
   typedef enum {FRNG_PORT_NA,FRNG_PORT_INPUT,FRNG_PORT_OUTPUT,FRNG_PORT_INOUT} fringe_port_type_e;  
      
   /*
    *  Fringe signal handshake signals::fringe_put
    *
    * (start code) 
    *  typedef enum  {FRNG_SIGNAL_IDLE,FRNG_SIGNAL_VALID_GET,FRNG_SIGNAL_ERROR_GET,FRNG_SIGNAL_VALID_PUT,FRNG_SIGNAL_ERROR_PUT} fringe_signal_hs_e;
    * (end code)
    *  fringe_signal_hs_e defines Fringe handshake flags 
    * 
    */
   typedef enum {FRNG_SIGNAL_IDLE,FRNG_SIGNAL_VALID_GET,FRNG_SIGNAL_ERROR_GET,FRNG_SIGNAL_VALID_PUT,FRNG_SIGNAL_ERROR_PUT} fringe_signal_hs_e;

   /*
    * Fringe comunication handshake signals::
    *
    * (start code) 
    * typedef enum  {FRNG_REQ,FRNG_ACK,FRNG_PUT,FRNG_GET} fringe_protocol_e;
    * (end code)
    * fringe_protocol_e defines protocol hadshake sinals 
    * 
    */
   typedef enum  {FRNG_REQ,FRNG_ACK,FRNG_PUT,FRNG_GET} fringe_protocol_e;
   
   /*
    * Fringe debug flags::
    *
    * (start code) 
    *  typedef enum  {FRNG_NO_PRINT,FRNG_PRINT} fringe_signal_debug_e;
    * (end code)
    *  fringe_signal_debug_e - debug flags
    * 
    */
   typedef enum  {FRNG_NO_PRINT,FRNG_PRINT} fringe_signal_debug_e;
  
   
   /* verilator lint_off UNPACKED */
   
   //About: Fringe DB Structures 
   /*
    * The SrcDst DB descriptor::
    *
    * (start code) 
    * typedef struct{ 	
    *  longint 	               SrcDst_id;      // SrcDst DB entry Id, 
    *  int 	               n_signals;      // SrcDst DB entry number of signals,
    *  int 	               socket_id;      // SrcDst DB entry TCP destination socket id  
    *  fringe_SrcDst_status_e  status;         // SrcDst DB entry status
    *  fringe_signal_hs_e      signal_status; // SrcDst DB entry agregated signal status 
    *  } fringe_SrcDsts_descriptor_t; 
    * (end code)
    * fringe_SrcDsts_descriptor_t defines a main SrsDst DB entry. 
    * 
    */
   typedef struct{ 	
      longint 	               SrcDst_id;      // SrcDst DB entry Id, 
      int 	               n_signals;      // SrcDst DB entry number of signals,
      int 	               socket_id;      // SrcDst DB entry TCP destination socket id
      int 		       index_signal;   // index pointer to the  signal_db first entry
      fringe_SrcDst_status_e   status; 	       // SrcDst DB entry status
      fringe_signal_hs_e       signal_status; // SrcDst DB entry agregated signal status
   } fringe_SrcDsts_descriptor_t;	


   /*
    * The Signal DB descriptor::
    *
    *(start code) 
    *typedef struct{
    *  longint 	               signal_id;            //unique signal identifier corresponding to the full signal name
    *  longint 		       SrcDst_parent_id;     //corresponding SrcDst DB parent entry
    *  longint 		       SrcDst_call_id;       //index pointer to the SrcDst DB correspondent id
    *  int 		       index_payloads;       //index pointer to the corresponding signal payloads_db entry  
    *  shunt_signal_type_e     signal_type;          //signal signal type
    *  int 		       signal_size;          //signal size
    *  fringe_signal_hs_e      signal_valid;         //signal handshake flag
    *  fringe_port_type_e      signal_port_type;     //signal port type    
    *  int 		       timestamp;            //last signal event simulation time  
    *  int 		       event_cntr;           //number of signal events 
    *  fringe_signal_debug_e   debug;                //debug flag 
    *} fringe_signals_descriptor_t; 
    *(end code)
    * fringe_signals_descriptor_t defines a main Signal DB entry
    * 
    */
   typedef struct{
      longint 	               signal_id;          //unique signal identifier corresponding to the full signal name
      longint 		       SrcDst_parent_id;   //corresponding SrcDst DB parent entry
      longint 		       SrcDst_call_id;     //index pointer to the SrcDst DB correspondent id
      int 		       index_payloads;     //index pointer to the corresponding signal payloads_db entry 
      int 		       number_payloads;    //number payloads etries payloads_db entry 
      shunt_signal_type_e      signal_type;        //signal signal type
      int 		       signal_size;        //signal size
      fringe_signal_hs_e       signal_valid;       //signal handshake flag 
      fringe_port_type_e       signal_port_type;    //signal port type   
      int 		       timestamp;          //last signal event simulation time  
      int 		       event_cntr;         //number of signal events 
      fringe_signal_debug_e    debug;              //debug flag 
   } fringe_signals_descriptor_t;

   /*
    * The Signal status descriptor:
    *
    *(start code) 
    *typedef struct{
    *  bit 	               valid;               //Get/Put signal request flag ???
    *  int 	               signal_index;        //Signal Db index corresponding to the Signal DB entry  ???
    *  int                     event_cnt;           //number of put get requests  ???
    *} put_get_status_t
    *(end code)
    *  put_get_status_t defines put/get_status signal request ???
    * 
    */
  typedef struct{
     bit 	valid;
     bit        success;
     int        signal_index;
     longint 	event_cnt;
  } put_get_status_t;
      
  /*
   * The Data exchange descriptors:
   *  data exchange structure:
   *(start code)
   * typedef struct{
   *   bit   [FRNG_MAX_N_OF_BITS_PER_SIGNAL-1:0] data_bit;
   *   logic [FRNG_MAX_N_OF_BITS_PER_SIGNAL-1:0] data_logic;
   * } data_in_t;  
   *(end code)
   * Data Base data exchange structure:
   * (start code)
   *  typedef struct 			   {
   *   bit   [FRNG_N_OF_BITS_PER_PAYLOAD-1:0] data_bit;
   *   logic [FRNG_N_OF_BITS_PER_PAYLOAD-1:0] data_logic;
   * } signal_db_data_in_t;
   *(end code) 
   */  
  typedef struct{
      bit   [`FRNG_MAX_N_OF_BITS_PER_SIGNAL-1:0] data_bit;
      logic [`FRNG_MAX_N_OF_BITS_PER_SIGNAL-1:0] data_logic;
   } data_in_t;
   
   typedef struct 			   {
      bit   [`FRNG_N_OF_BITS_PER_PAYLOAD-1:0] data_bit;
      logic [`FRNG_N_OF_BITS_PER_PAYLOAD-1:0] data_logic;
   } signal_db_data_in_t;
 
 /* verilator lint_on UNDRIVEN */

endpackage : shunt_fringe_pkg
   


