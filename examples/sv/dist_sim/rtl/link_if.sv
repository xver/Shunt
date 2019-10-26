interface link_modf_if (
		   input  logic          i_clk_to_link,
		   output logic          o_clk_to_link,
		   
		   input  logic          i_rstn_to_link,
		   output logic          o_rstn_to_link,
		   //
		   input  logic          i_wen_from_link,
		   output logic          o_wen_from_link,
		   
		   input  logic [31:0]   i_token_from_link,
		   output logic [31:0]   o_token_from_link,
		   
		   input  logic [31:0]   i_clk_cnt_from_link,
		   output logic [31:0]   o_clk_cnt_from_link,
		   
		   input  logic [31:0]   i_id_from_link,
		   output logic [31:0]   o_id_from_link,
		   //      
		   input  logic          i_wen_to_link,
		   output logic          o_wen_to_link,
		   
		   input  logic [31:0]   i_token_to_link,
		   output logic [31:0]   o_token_to_link,
		   
		   input  logic [31:0]   i_clk_cnt_to_link,
		   output logic [31:0]   o_clk_cnt_to_link,
		   
		   input  logic [31:0]   i_id_to_link,
		   output logic [31:0]   o_id_to_link    
              );
   parameter ID = 0;
 

assign o_clk_to_link  = i_clk_to_link;
assign o_rstn_to_link = i_rstn_to_link;
//
assign o_wen_to_link     = i_wen_to_link;
assign o_token_to_link   = i_token_to_link;
assign o_clk_cnt_to_link = i_clk_cnt_to_link;
assign o_id_to_link      = i_id_to_link;
//
assign o_wen_from_link     = i_wen_from_link;
assign o_token_from_link   = i_token_from_link;
assign o_clk_cnt_from_link = i_clk_cnt_from_link;
assign o_id_from_link      = i_id_from_link;    

   
endinterface : link_modf_if



