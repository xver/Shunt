/*
============================================================================
Title: Target.sv
 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : TCP/IP SystemVerilog SHUNT
               b_transport SystemC to SystemVerilog examle  -Target(client)
 ============================================================================
*/
`ifndef TARGET_SV
 `define TARGET_SV

/**
 * Module: Target
 *
 * TLM-2.0 target implementation for SystemC-to-SystemVerilog communication
 *
 * This module implements the target side of TLM-2.0 transport protocol over TCP/IP.
 * It communicates with a SystemC initiator and demonstrates memory read/write operations.
 *
 * Parameters:
 *   clk_i - Input clock signal
 */
module automatic Target(input reg clk_i);

   import shunt_dpi_pkg::*;

   /**
    * Variable: clk_cnt
    * Clock cycle counter
    */
   int clk_cnt;
   
   /* verilator lint_off UNUSED */
   /* verilator lint_off UNDRIVEN */
   
   /**
    * Variable: mem_data
    * Memory data input
    */
   logic [31:0] mem_data;
   
   /**
    * Variable: mem_byte_enable
    * Memory byte enable signals
    */
   logic [31:0] mem_byte_enable;
   
   /**
    * Variable: mem_addr
    * Memory address for read/write operations
    */
   logic [31:0] mem_addr;
   
   /**
    * Variable: mem_we
    * Memory write enable signal
    */
   logic        mem_we;
   
   /**
    * Variable: mem_q
    * Memory data output
    */
   logic [31:0] mem_q;
   
   /**
    * Variable: end_sim
    * Flag to indicate end of simulation
    */
   bit          end_sim;
   
   /**
    * Variable: start_sim
    * Flag to indicate start of simulation
    */
   bit          start_sim;
   
   /**
    * Variable: trnx_in_progress
    * Flag to indicate a transaction is in progress
    */
   bit          trnx_in_progress;
   
   /**
    * Variable: clk_next
    * Clock cycle for next operation
    */
   int          clk_next;
   
   /**
    * Variable: sockid
    * TCP/IP socket identifier
    */
   int          sockid;

   /**
    * Variable: h
    * TLM generic payload header
    */
   cs_tlm_generic_payload_header_t h;
   
   /**
    * Variable: h_ext
    * TLM AXI3 extension payload header for incoming data
    */
   cs_tlm_axi3_extension_payload_header_t h_ext;
   
   /**
    * Variable: h_ext_out
    * TLM AXI3 extension payload header for outgoing data
    */
   cs_tlm_axi3_extension_payload_header_t h_ext_out;
   
   /**
    * Variable: data_in
    * Input data bytes
    */
   byte         data_in[4];
   
   /**
    * Variable: byte_enable_in
    * Input byte enable signals
    */
   byte         byte_enable_in[4];

   /**
    * Variable: data_out
    * Output data bytes
    */
   byte         data_out[4];
   
   /**
    * Variable: byte_enable_out
    * Output byte enable signals
    */
   byte         byte_enable_out[4];


   /* verilator lint_on UNDRIVEN */
   /* verilator lint_on UNUSED */

   /**
    * Initial block: Initialization and Socket Setup
    *
    * Initializes all variables, establishes socket connection to the SystemC initiator,
    * and prepares the AXI3 extension response header
    */
   initial   begin
       clk_cnt=0;

      mem_data=0;
      mem_byte_enable=0;
      mem_addr=0;
      mem_we=0;

      mem_q=0;

      end_sim =0;
      start_sim=0;
      trnx_in_progress=0;
      sockid =0;

      $display("TARGET: shunt_dpi_tlm_header_id()=%h",shunt_dpi_tlm_header_id());
      $display("TARGET: shunt_dpi_tlm_data_id()=%h", shunt_dpi_tlm_data_id());
      $display("TARGET: shunt_dpi_tlm_axi3_ext_id()=%h",shunt_dpi_tlm_axi3_ext_id());
      $display("TARGET: shunt_dpi_tlm_signal_id()=%h",shunt_dpi_tlm_signal_id());

      sockid = shunt_dpi_target_init(`MY_PORT,`MY_HOST);
      shunt_dpi_tlm_send_command(sockid,SHUNT_TLM_START_SIM);
      start_sim =1;
      h_ext_out.AxBURST = 0;
      h_ext_out.AxCACHE = 0;
      h_ext_out.AxID    = 11;
      h_ext_out.AxLEN   = 0;
      h_ext_out.AxLOCK  = 3;
      h_ext_out.AxPROT  = 0;
      h_ext_out.AxSIZE  = 0;
      h_ext_out.xRESP   = 3;
      h_ext_out.xSTRB   = 0;
   end

   /**
    * Instance: mem
    * Memory module instance for read/write operations
    */
   memory  mem(.data(mem_data),.addr(mem_addr), .we(mem_we), .clk(clk_i), .q(mem_q));

   /* verilator lint_off WIDTH */
   /**
    * Assign statement: Memory data concatenation
    * Converts individual bytes to 32-bit memory data word
    */
   assign mem_data = {data_in[3],data_in[2],data_in[1],data_in[0]};
   
   /**
    * Assign statement: Memory output deconstruction
    * Breaks 32-bit memory output into individual bytes
    */
   assign {data_out[3],data_out[2],data_out[1],data_out[0]} = mem_q;
   //assign mem_addr = h.address;
   //assign mem_data =  {>>{data_in}};

   /**
    * Always block: End of Simulation Detection
    *
    * Monitors the end_sim flag and terminates simulation when set
    */
   always @(posedge clk_i) begin
      //if(trnx_in_progress) $display("\nTARGET : mem.ram[%0d]=%h mem_data=%h @%0d\n",h.address,mem.ram[h.address],mem_data,clk_cnt);
      if (end_sim)  begin
         $display("\nTARGET: SHUNT_TLM_END_SIM clk_cnt=%0d\n",clk_cnt);
         $finish;
      end
   end


   /**
    * Always block: Transaction Processing
    *
    * Main transaction handling for TLM operations
    * - Receives and processes incoming TLM commands
    * - Performs memory read/write operations
    * - Sends response data back to initiator
    * - Handles end of simulation command
    */
   always @(posedge clk_i) begin

      if(start_sim) begin
         if(!trnx_in_progress) begin
            shunt_dpi_tlm_recv_gp_transport(sockid,h,data_in,byte_enable_in);
            shunt_dpi_tlm_gp_header_print (h,"TARGET: ");
            if(h.command != SHUNT_TLM_END_SIM) begin
               shunt_dpi_tlm_recv_axi3_header(sockid,h_ext);
               shunt_dpi_tlm_axi3_header_print (h_ext,"TRAGET: ");
               shunt_dpi_tlm_send_axi3_header (sockid,h_ext_out);
            end
            /* verilator lint_off BLKSEQ */
            h.response_status = SHUNT_TLM_OK_RESPONSE;
            /* verilator lint_on BLKSEQ */
            trnx_in_progress <=1;
            clk_next <= clk_cnt;
         end

         //WRITE
         if(h.command == SHUNT_TLM_WRITE_COMMAND) begin
            mem_we   <=1;
            mem_addr <= h.address;
         end

         //READ
         if(h.command == SHUNT_TLM_READ_COMMAND)  begin
            mem_addr <= h.address;
         end

         //
         if (trnx_in_progress && clk_cnt>clk_next+1) begin
            shunt_dpi_tlm_send_gp_transport(sockid,h,data_out,byte_enable_out);
            mem_we   <=0;
            trnx_in_progress <=0;
         end
         //
         if(h.command == SHUNT_TLM_END_SIM)  begin
            end_sim   <=1;
            start_sim <=0;
            trnx_in_progress <=0;
         end

      end // if (start_sim)
      clk_cnt<=clk_cnt+1;
   end // always @ (posedge clk_i)

endmodule : Target

/* verilator lint_off DECLFILENAME */
/**
 * Module: memory
 *
 * Simple memory model with synchronous write and read operations
 *
 * Parameters:
 *   data - Input data for write operations
 *   addr - Memory address for read/write operations
 *   we   - Write enable signal
 *   clk  - Clock signal
 *   q    - Output data from read operations
 */
module memory
  (
   input [31:0] data,
   input [31:0] addr,
   input we, clk,
   output [31:0] q
   );

   /**
    * Variable: ram
    * Memory storage array
    */
   reg [31:0]      ram[255:0];

   /* verilator lint_off UNUSED */
   /**
    * Variable: addr_reg
    * Registered address for read operations
    */
   reg [31:0]      addr_reg;
   /* verilator lint_on UNUSED */

   /**
    * Initial block: Memory Initialization
    *
    * Initializes memory array with random data
    */
   initial begin
      for (int i = 0; i < 256; i++) begin
         ram[i] = 32'hAA000000 | ($random % 256);
         //$display("TARGET: ram[%0d]=%h\n",i,ram[i]);
         addr_reg = 0;
      end
   end

   /**
    * Always block: Memory Access
    *
    * Handles write operations and address registration for read operations
    */
   always @ (posedge clk)
     begin
        // Write
        if (we) ram[addr] <= data;
        addr_reg <= addr;
     end

   /**
    * Assign statement: Memory Read Output
    * Provides read data from the registered address
    */
   assign q = ram[addr_reg];

endmodule : memory
/* verilator lint_on DECLFILENAME */

`endif //  `ifndef TARGET_SV







