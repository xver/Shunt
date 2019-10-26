/* verilator lint_off UNUSED */
interface  link_i
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
   output logic [31:0]   o_id
   /////
   output  logic          o_clk_down,
   output  logic          o_rstn_down,
   //
   output  logic          o_wen_down,    
   output  logic [31:0]   o_token_down,   
   output  logic [31:0]   o_clk_cnt_down, 
   output  logic [31:0]   o_id_down,
   //      
   input logic          i_wen_down,   
   input logic [31:0]   i_token_down,   
   input logic [31:0]   i_clk_cnt_down, 
   input logic [31:0]   i_id_down,
              );

   parameter int 	ID = 0;
   parameter string 	ASCII_NAME = "MODULE";
   string 		my_name;
   string               my_id = "0";
   string               my_next_id = "0";
   string               my_signals    [8];
   int 			my_signal_type[8];
   int 			my_signal_size[8];
   parameter int 	ID = 0;
   parameter string 	ASCII_NAME = "MODULE";
   string 		my_name;
   string               my_id = "0";
   string               my_next_id = "0";
   string               my_signals    [8];
   int 			my_signal_type[8];
   int 			my_signal_size[8];
   
   initial  begin 
      my_id.itoa(ID);
      if (ID+1>2)my_next_id.itoa(0);
      else my_next_id.itoa(ID+1); 
      my_name = {ASCII_NAME,"_",my_id};
      //$display("link instance  %s",my_name);
      my_signals[0] = {"wen","[",my_id,"]"};
      my_signals[1] = {"token","[",my_id,"]"};
      my_signals[2] = {"clk_cnt","[",my_id,"]"};
      my_signals[3] = {"id","[",my_id,"]"};
      my_signals[4] = {"wen","[",my_next_id,"]"};
      my_signals[5] = {"token","[",my_next_id,"]"};
      my_signals[6] = {"clk_cnt","[",my_next_id,"]"};
      my_signals[7] = {"id","[",my_next_id,"]"};
      //
      my_signal_type[0] = Frng_if.SHUNT_BIT;
      my_signal_type[1] = Frng_if.SHUNT_BIT;
      my_signal_type[2] = Frng_if.SHUNT_BIT;
      my_signal_type[3] = Frng_if.SHUNT_BIT;
      my_signal_type[4] = Frng_if.SHUNT_BIT;
      my_signal_type[5] = Frng_if.SHUNT_BIT;
      my_signal_type[6] = Frng_if.SHUNT_BIT;
      my_signal_type[7] = Frng_if.SHUNT_BIT;
      //
      my_signal_size[0] = 32;
      my_signal_size[1] = 32;
      my_signal_size[2] = 32;
      my_signal_size[3] = 32;
      my_signal_size[4] = 32;
      my_signal_size[5] = 32;
      my_signal_size[6] = 32;
      my_signal_size[7] = 32;
      
      print_module_name(); 
      print_signals_names();
   end // initial begin
   
   assign o_wen    = i_wen_down;
   assign o_token  = i_token_down;
   assign o_clk_cn = i_clk_cnt_down;
   assign o_id     = i_id_dow;
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
	 $display("Frng_if.frng_success = Frng_if.set_signal_db_entry(\"%s\",\"%s\",%0d,%0d);",my_name,my_signals[i],my_signal_type[i],my_signal_size[i]);
	 $display("Frng_if.frng_success = Frng_if.set_signal_db_entry(who_iam(),\"%s\",%0d,%0d);",my_signals[i],my_signal_type[i],my_signal_size[i]);
      end
   endfunction : print_signals_names
endinterface // link_i




  


/* verilator lint_on UNUSED */

 