/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */
interface  link_anchor_if
  (
   input  logic          i_clk,
   input  logic          i_rstn,
   //
   //input  logic          i_wen,    
   //input  logic [31:0]   i_token,   
   //input  logic [31:0]   i_clk_cnt, 
   //input  logic [31:0]   i_id,
   //      
   //output logic          o_wen,   
   //output logic [31:0]   o_token,   
   //output logic [31:0]   o_clk_cnt, 
   //output logic [31:0]   o_id,
   /////
   output  logic          o_wen_down,    
   output  logic [31:0]   o_token_down,   
   output  logic [31:0]   o_clk_cnt_down, 
   output  logic [31:0]   o_id_down,
   //      
   input logic          i_wen_down,   
   input logic [31:0]   i_token_down,   
   input logic [31:0]   i_clk_cnt_down, 
   input logic [31:0]   i_id_down
   );

   import shunt_dpi_pkg::*;
   import  shunt_fringe_pkg::*;
   
   bit 			start_socket =0;
   
   parameter int 	ID = 0;
   parameter string 	ASCII_NAME = "MODULE";
   
   string 		my_name;
   string               my_id = "0";
   string               my_next_id = "0";
   string               my_signals    [`FRNG_N_OF_DST_SIGNALS];
   //int 			my_signal_type[8];
   //int 			my_signal_size[8];
   int 			clk_cnt=0;
   
    shunt_fringe_if Frng_if(i_clk);
   bit 			success;
   bit 			put_success;
   bit 			get_success;

  
   
   initial  begin 
      my_id.itoa(ID);
      my_next_id.itoa(ID+1); 
      my_name = {ASCII_NAME,"_",my_id};
      //$display("link instance  %s",my_name);
      my_signals[0] = {"wen","[",my_id,"]"};
      //
      my_signals[1] = {"wen","[",my_next_id,"]"};
            
      Frng_if.frng_success = Frng_if.set_iam(my_name);
      Frng_if.frng_success = Frng_if.set_mystatus(Frng_if.FRNG_TARGET_ACTIVE);
      Frng_if.frng_success = Frng_if.set_simid(`SIM_ID);

      `ifdef DB_INIT_DEBUG
       `include "../include/db_init.svi"      
      `elsif FRNG_N_OF_DST_16
       `include "../include/db_init_16.svi"
      `elsif FRNG_N_OF_DST_8
       `include "../include/db_init_8.svi"
      `elsif FRNG_N_OF_DST_4
       `include "../include/db_init_4.svi"
      `else
       `include "../include/db_init_2.svi"	
      `endif
      
     
      $display("i am : %s (%s) source(%s) ID(%0d)",Frng_if.who_iam(),Frng_if.my_status.name(),Frng_if.my_source,ID);
   end // initial begin
  
   always @(posedge i_clk) begin
      /* verilator lint_off WIDTH */
      data_in_t  data_put;
      
      $display("------ @%0d",Frng_if.get_time());
      if(!i_rstn)  data_put.data_bit <=0;
      data_put.data_bit[0]   <= i_wen_down;
      $display("%s %s.%s data_put.data_bit=%0h @%0d",Frng_if.who_iam(),`MY_TOP_NAME ,my_signals[1],data_put.data_bit[0],Frng_if.get_time());
      put_success <= Frng_if.fringe_api_put (`MY_TOP_NAME,my_signals[1],Frng_if.SHUNT_BIT,data_put);
   end // always @ (i_wen_down)
   
   always @(posedge i_clk) begin
      data_in_t data_get;
      
      for(int i=0;i<`FRNG_N_OF_SIGNALS;i++) begin
	 if (Frng_if.signals_db[i].signal_valid == FRNG_SIGNAL_VALID_GET) begin
	    success <=  Frng_if.fringe_api_get_by_signal_index(i,data_get);
	    if (success)   begin
	       $display("%s %s.%s data_get.data_bit=%0h @%0d",Frng_if.who_iam(),`MY_TOP_NAME,Frng_if.__signals_db_name[i],data_get.data_bit[0],Frng_if.get_time());
	       o_wen_down <= data_get.data_bit[0];
	    end
	 end // if (Frng_if.signals_db[i].signal_valid == FRNG_SIGNAL_VALID_GET)
      end // for (int i=0;i<`FRNG_N_OF_SIGNALS;i++)
   end // always @ (posedge clk_i)   
   
   function string  get_module_name();
      return my_name; 
   endfunction : get_module_name
   
endinterface : link_anchor_if




/* verilator lint_on UNUSED */
/* verilator lint_on UNDRIVEN */
 