/* verilator lint_off UNDRIVEN */
/* verilator lint_off UNUSED */
/* verilator lint_off UNOPTFLAT */
/* verilator lint_off DECLFILENAME */
module top_rtl(input reg i_clk,input reg reset_n);
  
   //reg i_clk;
   //reg reset_n;

   //reg        wen    [`N_LINK:0];
   //reg [31:0] token  [`N_LINK:0];
   //reg [31:0] clk_cnt[`N_LINK:0];
   //reg [31:0] id     [`N_LINK:0];

   reg        wen_to_link    [`N_LINK-1:0];
   reg [31:0] token_to_link  [`N_LINK-1:0];
   reg [31:0] clk_cnt_to_link[`N_LINK-1:0];
   reg [31:0] id_to_link     [`N_LINK-1:0];

   reg        wen_from_link    [`N_LINK-1:0];
   reg [31:0] token_from_link  [`N_LINK-1:0];
   reg [31:0] clk_cnt_from_link[`N_LINK-1:0];
   reg [31:0] id_from_link     [`N_LINK-1:0];

   //
   shunt_fringe_if Frng_if (i_clk); 
   //
   
   generate
      for(genvar i=0;i<`N_LINK;i++)
	begin: link 	
           link_i #(.ID(i)) link_rtl
		   (
		    .i_clk     (i_clk),		 
		    .i_rstn    (reset_n),
		    //
		    .i_wen     (wen_to_link[i]),
		    .i_token   (token_to_link[i]),
		    .i_clk_cnt (clk_cnt_to_link[i]),
		    .i_id      (id_to_link[i]),
		    //
		    .o_wen     (wen_from_link[i] ),
		    .o_token   (token_from_link[i] ),
		    .o_clk_cnt (clk_cnt_from_link[i] ),
		    .o_id      (id_from_link[i] )
		    );  
              
	      link_anchor_if #(.ASCII_NAME("link"),.ID(i)) link_if
		(
		 .i_clk(i_clk),
		 .i_rstn(reset_n),
		 //
		 //.i_wen(wen[i]),    
		 //.i_token(token[i]),   
		 //.i_clk_cnt(clk_cnt[i]), 
		 //.i_id(id[i]),
		 //      
		 //.o_wen(wen[i+1]),   
		 //.o_token(token[i+1]),   
		 //.o_clk_cnt(clk_cnt[i+1]), 
		 //.o_id(id[i+1]),
		 /////
		 .o_wen_down(wen_to_link[i]),    
		 .o_token_down(token_to_link[i]),   
		 .o_clk_cnt_down(clk_cnt_to_link[i]), 
		 .o_id_down(id_to_link[i]),
		 //      
		 .i_wen_down(wen_from_link[i] ),   
		 .i_token_down(token_from_link[i] ),   
		 .i_clk_cnt_down(clk_cnt_from_link[i] ), 
		 .i_id_down(id_from_link[i] )
		 );
	end // block: chain
      

endgenerate
   
endmodule // top_rtl

/* verilator lint_on UNDRIVEN */
/* verilator lint_on UNUSED */
/* verilator lint_on UNOPTFLAT */
/* verilator lint_on DECLFILENAME */