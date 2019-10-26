//SrcDsts
//FRNG_N_OF_DST tests up to 16 only i5 VB limitaion
//`define  FRNG_N_OF_DST_16
//`define  FRNG_N_OF_DST_8
//`define  FRNG_N_OF_DST_4
`define  DB_INIT_DEBUG

`ifdef  FRNG_N_OF_DST_16
 `define FRNG_N_OF_DST  16
`elsif FRNG_N_OF_DST_8
 `define FRNG_N_OF_DST 8
`elsif FRNG_N_OF_DST_4
 `define FRNG_N_OF_DST  4
`else
 `define  FRNG_N_OF_DST  2
`endif



`ifndef  FRNG_N_OF_DST_SIGNALS
 `define FRNG_N_OF_DST_SIGNALS 2
`endif


`ifndef  FRNG_MAX_N_OF_BITS_PER_SIGNAL
 `define FRNG_MAX_N_OF_BITS_PER_SIGNAL 64
`endif

`ifndef  FRNG_MAX_N_OF_PAYLOADS_PER_SIGNAL
 `define FRNG_MAX_N_OF_PAYLOADS_PER_SIGNAL 1
`endif

`ifndef  FRNG_N_OF_BITS_PER_PAYLOAD
 `ifdef  SHUNT_VERILATOR_DPI_H 
  `define FRNG_N_OF_BITS_PER_PAYLOAD 64
 `endif

`define MY_TOP_NAME "TOP_SIM"

`define MY_HOST "localhost"
`define MY_PORT  3450

//simulation ID id
`define SIM_ID  12345678

////////////
`ifndef  FRNG_N_OF_SRC_SIGNALS
 `define FRNG_N_OF_SRC_SIGNALS  `FRNG_N_OF_DST+1
`endif

`ifndef  FRNG_N_OF_SRCDSTS
 `define FRNG_N_OF_SRCDSTS  `FRNG_N_OF_DST + 1
`endif


`define N_LINK  `FRNG_N_OF_DST


 `ifndef  FRNG_N_OF_SIGNALS
  `define FRNG_N_OF_SIGNALS `FRNG_N_OF_DST_SIGNALS*`FRNG_N_OF_DST + `FRNG_N_OF_SRC_SIGNALS 
 `endif



 `ifndef SHUNT_VERILATOR_DPI_H   
  `define FRNG_N_OF_BITS_PER_PAYLOAD `FRNG_MAX_N_OF_BITS_PER_SIGNAL
 `endif
`endif


`ifndef  FRNG_N_OF_PAYLOADS
 `define FRNG_N_OF_PAYLOADS (`FRNG_N_OF_SIGNALS*(`FRNG_MAX_N_OF_BITS_PER_SIGNAL/`FRNG_N_OF_BITS_PER_PAYLOAD))
`endif



/* -----\/----- EXCLUDED -----\/-----
`define INIT_SRCDSTS_DB string SrcDsts_name[`FRNG_N_OF_SRCDSTS];\
int SrcDsts_n_signals[`FRNG_N_OF_SRCDSTS];\
SrcDsts_name[0] = "TARGET";\
SrcDsts_n_signals[0]=4;\
SrcDsts_name[1] = "INITIATOR";\
SrcDsts_n_signals[1]=4;
`define INIT_SIGNAL_DB string SrcDsts_name[`FRNG_N_OF_SRCDSTS];\
string signal_name[`FRNG_N_OF_SIGNALS];\
string signals_SrcDsts[`FRNG_N_OF_SIGNALS];\
int signal_type[`FRNG_N_OF_SIGNALS];\
int signal_size[`FRNG_N_OF_SIGNALS];\
SrcDsts_name[0] = "TARGET";\
SrcDsts_name[1] = "INITIATOR";\
signal_name[0] = "data_clk_0";\
signal_name[1] = "data_clk_1";\
signal_name[2] = "data_clk_2";\
signal_name[3] = "data_clk_3";\
signal_type[0] = Frng_if.SHUNT_BIT;\
signal_type[1] = Frng_if.SHUNT_BIT;\
signal_type[2] = Frng_if.SHUNT_BIT;\
signal_type[3] = Frng_if.SHUNT_BIT;\
signal_size[0] = 9;\
signal_size[1] = 9;\
signal_size[2] = 9;\
signal_size[3] = 9;
 -----/\----- EXCLUDED -----/\----- */


