/*
============================================================================
 File        : Target.sv
 Copyright (c) 2016-2020 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : TCP/IP SystemVerilog SHUNT
               b_transport SystemC to SystemVerilog examle  -Target(client)  
 ============================================================================
*/
`ifndef TARGET_SV
 `define TARGET_SV

module automatic Target(input reg clk_i); 
   
   import shunt_dpi_pkg::*;
   
   int clk_cnt=0;
   /* verilator lint_off UNUSED */
   /* verilator lint_off UNDRIVEN */
   //MEM
   //logic [31:0] mem [0:255]=0;
   logic [31:0] mem_data=0;
   logic [31:0] mem_byte_enable=0;
   logic [31:0] mem_addr=0;
   logic        mem_we=0;
   //logic      mem_oe;
   logic [31:0] mem_q=0;
   
   bit          end_sim =0 ;
   bit          start_sim=0;
   bit          trnx_in_progress=0;
   int          clk_next;
   
   int          sockid =0;
   cs_tlm_generic_payload_header_t h;
   
   byte         data_in[4];
   byte         byte_enable_in[4];
   
   byte         data_out[4];
   byte         byte_enable_out[4];
   
  
   /* verilator lint_on UNDRIVEN */
   /* verilator lint_on UNUSED */ 
   
   initial   begin 
      sockid = shunt_dpi_target_init(`MY_PORT,`MY_HOST);
      shunt_dpi_tlm_send_command(sockid,shunt_tlm_command_e::SHUNT_TLM_START_SIM);
      start_sim =1;
   end
   
   memory  mem(.data(mem_data),.addr(mem_addr), .we(mem_we), .clk(clk_i), .q(mem_q));
   
   /* verilator lint_off WIDTH */
   assign mem_data = {data_in[3],data_in[2],data_in[1],data_in[0]};
   assign {data_out[3],data_out[2],data_out[1],data_out[0]} = mem_q;
   //assign mem_addr = h.address;  
   //assign mem_data =  {>>{data_in}};
   
   always @(posedge clk_i) begin
      //if(trnx_in_progress) $display("\nTARGET : mem.ram[%0d]=%h mem_data=%h @%0d\n",h.address,mem.ram[h.address],mem_data,clk_cnt);
      if (end_sim)  begin
         $display("TARGET: SHUNT_TLM_END_SIM clk_cnt=%0d\n",clk_cnt);
         $finish;
      end
   end
   
      
   always @(posedge clk_i) begin
      
      if(start_sim) begin
         if(!trnx_in_progress) begin 
            shunt_dpi_tlm_recv_gp_transport(sockid,h,data_in,byte_enable_in);
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
module memory
  (
   input [31:0] data,
   input [31:0] addr,
   input we, clk,
   output [31:0] q
   );
   
   reg [31:0]      ram[255:0];
   
   /* verilator lint_off UNUSED */
   reg [31:0]      addr_reg;
   /* verilator lint_on UNUSED */
   
   initial begin
      for (int i = 0; i < 256; i++) begin
         ram[i] = 32'hAA000000 | ($random % 256);
         //$display("TARGET: ram[%0d]=%h\n",i,ram[i]);
         addr_reg = 0;
      end
   end
   
   always @ (posedge clk)
     begin
        // Write
        if (we) ram[addr] <= data;
        addr_reg <= addr;
     end
   
   assign q = ram[addr_reg];
   
endmodule : memory
/* verilator lint_on DECLFILENAME */

`endif //  `ifndef TARGET_SV







