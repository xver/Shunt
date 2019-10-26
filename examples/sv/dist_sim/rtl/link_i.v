/* verilator lint_off UNUSED */
module link_i(
              input  logic          i_clk,
              input  logic          i_rstn,
              //
              input  logic          i_wen,    
              input  logic [31:0]   i_token,   
              input  logic [31:0]   i_clk_cnt, 
              input  logic [31:0]   i_id,
              //      
              output logic          o_wen,   
              output logic [31:0]   o_token,   
              output logic [31:0]   o_clk_cnt, 
              output logic [31:0]   o_id      
              );
   //
   logic [31:0]                     clk_cnt_in;
   logic [31:0]                     id_in;
   
   //
   logic [31:0]                     clk_cnt;
   
   logic [31:0]                     id;
   logic                            wen_t;
   
   parameter ID = 0;
  
   assign  id     = ID;
   assign o_clk_cnt = clk_cnt ; 
   //clk counter
   always @(posedge i_clk) begin
      if (!i_rstn)clk_cnt <=ID;
      else clk_cnt  <=  clk_cnt +1;
   end // always @ (posedge i_clk)
   
   always @(posedge i_clk) begin
      if (!i_wen) begin 
         clk_cnt_in <=0;
         id_in <=0;
         wen_t <=0;
      end
      else begin 
         clk_cnt_in  <=  i_clk_cnt;
         id_in       <=  i_id;
         wen_t       <=  i_wen;
      end
   end // always @ (posedge i_clk)
   
   always @(posedge i_clk) begin
      if (!i_rstn) o_wen <=0;
      else begin
         if(ID==0 && clk_cnt<4)  o_wen <=clk_cnt[1]&clk_cnt[0];
         else      o_wen <=wen_t;
      end
   end // always @ (posedge i_clk)
   
   always @(posedge i_clk) begin
      if (!o_wen) begin 
         o_token   <= 0;
         o_id      <= 0;
      end
      else begin         
         o_token   <= i_token;
         o_id      <= id;
      end
   end // always @ (posedge i_clk)
   
   
      
endmodule // link_i

/* verilator lint_on UNUSED */
