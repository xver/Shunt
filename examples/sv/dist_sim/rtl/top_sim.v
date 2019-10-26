/* verilator lint_off UNUSED */
module  top_sim (input reg clk_i);
   
   //logic clk_i;
   
   logic reset_n;
   logic [31:0] clk_cnt;
   
   always @(posedge clk_i) begin
      clk_cnt  <=  clk_cnt +1;
      if (clk_cnt > 10) reset_n <= 1;
      else  reset_n <= 0;
      if  (clk_cnt > 1000) $finish;
   end // always @ (posedge clk_i)   

   top_rtl  dut(.i_clk(clk_i),.reset_n(reset_n));
   
endmodule: top_sim
/* verilator lint_on UNUSED */
