/* verilator lint_off UNDRIVEN */
/* verilator lint_off UNUSED */
/* verilator lint_off UNOPTFLAT */
/* verilator lint_off DECLFILENAME */
module top_rtl(input reg i_clk,input reg reset_n);
   
   import shunt_dpi_pkg::*;
   import  shunt_fringe_pkg::*;
   
   reg wen        [`N_LINK:0];
   reg [31:0] token  [`N_LINK:0];
   reg [31:0] clk_cnt[`N_LINK:0];
   reg [31:0] id     [`N_LINK:0];
   // 
   string               my_id = "0";
   string     my_signals    [`FRNG_N_OF_SRC_SIGNALS];
   //
   
   //
   shunt_fringe_if Frng_if (i_clk); 
   //
   assign              wen[0] = wen[`N_LINK];
      
   initial begin
      Frng_if.frng_success = Frng_if.set_iam(`MY_TOP_NAME);
      Frng_if.frng_success = Frng_if.set_mystatus(Frng_if.FRNG_INITIATOR_ACTIVE);
      Frng_if.frng_success = Frng_if.set_simid(`SIM_ID);
      Frng_if.print_localparams();
      //
      //$display("link instance  %s",my_name);
      foreach( my_signals[i]) begin
	 my_id.itoa(i);
	 my_signals[i] = {"wen","[",my_id,"]"};
      end
      foreach( my_signals[i]) begin
	 $display("my_signals[%0d]=%s",i,my_signals[i]); 
      end

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
      
	    
      $display("i am : %s (%s) source(%s)",Frng_if.who_iam(),Frng_if.my_status.name(),Frng_if.my_source);
      Frng_if.frng_success = Frng_if.print_SrcDsts_db();
      Frng_if.frng_success = Frng_if.print_signals_db();
           
   end // initial begin

    always @(posedge i_clk) begin
	  wen[0] <= wen[`N_LINK]; 
       end
   
   /* verilator lint_off IGNOREDRETURN */    
   always @(posedge i_clk) begin
      $display("------ @%0d",Frng_if.get_time());
      data_input_loop ();
   end // always @ (posedge clk_i)

   
   generate
      for(genvar i=0;i<`FRNG_N_OF_SRC_SIGNALS;i++)
	begin: data_output  
	   always @(posedge i_clk) begin
	      data_output_loop (my_signals[i],i);
	   end // always @ (posedge i_clk)
	end // block: data_output
   endgenerate	
   
   function void data_input_loop ();
      /* verilator lint_off BLKSEQ */ 
      bit  success;
      bit  put_success;
      
      for(int i=0;i<`FRNG_N_OF_SIGNALS;i++) begin
	 if (Frng_if.signals_db[i].signal_valid == FRNG_SIGNAL_VALID_GET) begin
	    data_in_t data_get;
	    success <=  Frng_if.fringe_api_get_by_signal_index(i,data_get);
            if (success)   begin
	       string signal_name = Frng_if.__signals_db_name[i];
	       for(int signal_name_index=0;signal_name_index<`FRNG_N_OF_SRC_SIGNALS;signal_name_index++) begin
		  if (signal_name == my_signals[signal_name_index])  begin 
		     wen[signal_name_index] = data_get.data_bit[0];
		     $display("%s %s data_get.data_bit=%0h wen[%0d]=%0d @%0d",Frng_if.who_iam(),signal_name,data_get.data_bit,signal_name_index,wen[signal_name_index],Frng_if.get_time());
		  end
	       end // for (int signal_name_index=0;signal_name_index<`FRNG_N_OF_SRC_SIGNALS;signal_name_index++)
	    end // if (success)
	 end // if (Frng_if.signals_db[i].signal_valid == FRNG_SIGNAL_VALID_GET)
      end // for (int i=0;i<`FRNG_N_OF_SIGNALS;i++)
      /* verilator lint_on BLKSEQ */  
   endfunction // data_input_loop
   
   

   function void data_output_loop (string signal_name,int i_in);
      int signal_index;

      for (signal_index=0;signal_index<`FRNG_N_OF_SIGNALS;signal_index++)
	begin
	   int Src_Dst_index  =  Frng_if.get_index_by_id_SrcDsts_db(Frng_if.signals_db[signal_index].SrcDst_parent_id);
	   string parent_name =  Frng_if.get_name_by_index_SrcDsts_db(Src_Dst_index);
	   if(Frng_if.signals_db[signal_index].signal_port_type == FRNG_PORT_OUTPUT &&  
	      Frng_if.who_iam() != parent_name &&
	      signal_name == Frng_if.__signals_db_name[signal_index])
             begin
		data_in_t  data_put;
		
		data_put.data_bit[0]   = wen[i_in];
		Frng_if.fringe_api_put (parent_name,signal_name,Frng_if.SHUNT_BIT,data_put);
		$display("%s  my_signals[%0d] %s.%s data_put.data_bit=%0h %s @%0d",Frng_if.who_iam(),i_in,parent_name,signal_name,wen[i_in],Frng_if.signals_db[signal_index].signal_port_type.name(),Frng_if.get_time());
	     end // if (Frng_if.signals_db[signal_index].signal_port_type == FRNG_PORT_OUTPUT &&  Frng_if.who_iam() != parent_name &&)
	end // for (signal_index=0;signal_index<`FRNG_N_OF_SIGNALS;signal_index++)
      
   endfunction : data_output_loop
   
   
      


endmodule // top_rtl
 /* verilator lint_on IGNOREDRETURN */    
/* verilator lint_on UNDRIVEN */
/* verilator lint_on UNUSED */
/* verilator lint_on UNOPTFLAT */
/* verilator lint_on DECLFILENAME */