/* verilator lint_off UNUSED */
interface  link_modf_if
  (
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
   output logic [31:0]   o_id,
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

   parameter int 	ID;
   parameter string 	ASCII_NAME = "MODULE";
   string 		my_name;
   string               my_id;
   string               my_next_id;
   string               my_signals    [2];
   int 			my_signal_type[2];
   int 			my_signal_size[2];
      
   initial  begin 
      my_id.itoa(ID);
      my_next_id.itoa(ID+1); 
      my_name = {ASCII_NAME,"_",my_id};
      my_signals[0] = {"wen","[",my_id,"]"};
      my_signal_type[0] = Frng_if.SHUNT_BIT;
      my_signal_size[0] = 32;
      //
      my_signals[1] = {"wen","[",my_next_id,"]"};
      my_signal_type[1] = Frng_if.SHUNT_BIT;
      my_signal_size[1] = 32;
      //$display("link instance  %s ID(%0d)",my_name,ID);     
      
      print_module_name(); 
      print_signals_names();
   end // initial begin
   
   assign o_wen     = i_wen_down;
   assign o_token   = i_token_down;
   assign o_clk_cnt = i_clk_cnt_down;
   assign o_id      = i_id_down;
   //
   assign o_wen_down     = i_wen;
   assign o_token_down   = i_token;
   assign o_clk_cnt_down = i_clk_cnt;
   assign o_id_down      = i_id; 
   //
   function string  get_module_name();
      return my_name; 
   endfunction : get_module_name
   
   function void  print_module_name();
      $display("Frng_if.frng_success = Frng_if.set_SrcDst_db_entry(\"%s\",%0d);",my_name,$size(my_signals)); 
   endfunction : print_module_name
   
   
   function void print_signals_names();
      foreach(my_signals[i])  begin
	 string port_type;
	 if (i==0)  port_type = "FRNG_PORT_OUTPUT";
	 if (i==1)  port_type = "FRNG_PORT_INPUT";
	 
         $display("if(Frng_if.who_iam() == `MY_TOP_NAME) Frng_if.frng_success = Frng_if.set_signal_db_entry(\"%s\",\"%s\",%0d,%0d,%s);",my_name,my_signals[i],my_signal_type[i],my_signal_size[i],port_type);
	 $display("if(Frng_if.who_iam() != `MY_TOP_NAME) Frng_if.frng_success = Frng_if.set_signal_db_entry(\"%s\",\"%s\",%0d,%0d);",my_name,my_signals[i],my_signal_type[i],my_signal_size[i]);
	 if (i==0 || ID+1==`N_LINK )$display("Frng_if.frng_success = Frng_if.set_signal_db_entry(`MY_TOP_NAME,\"%s\",%0d,%0d);",my_signals[i],my_signal_type[i],my_signal_size[i]);
      end
   endfunction : print_signals_names
endinterface // link_modf_if  


/* verilator lint_on UNUSED */

 