/*
============================================================================
 File        : shunt_fringe_if .sv
 Version     : 1.0.1
 Copyright (c) 2018 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : SV interface for the Fringe TCP handshake framework
 ============================================================================
*/
`ifndef SHUNT_FRINGE_IF
`define SHUNT_FRINGE_IF
  
/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */
/* verilator lint_off UNOPTFLAT */


`include "cs_common.svh"


interface shunt_fringe_if (input clk_i);

   //Title: Plug-n-Play(PnP)  handshake framework (Fring)
   
   //Section:
   
   //  
   localparam N_OF_SRCDSTS  = `FRNG_N_OF_SRCDSTS;
   localparam N_OF_SIGNALS  = `FRNG_N_OF_SIGNALS;
   localparam N_OF_PAYLOADS = `FRNG_N_OF_PAYLOADS;
   localparam MAX_N_OF_BITS_PER_SIGNAL =  `FRNG_MAX_N_OF_BITS_PER_SIGNAL;
   localparam N_OF_BITS_PER_PAYLOAD = `FRNG_N_OF_BITS_PER_PAYLOAD;
   localparam MAX_N_OF_PAYLOADS_PER_SIGNAL =`FRNG_MAX_N_OF_PAYLOADS_PER_SIGNAL;
   localparam TCP_PORT = `MY_PORT;
   localparam TCP_HOST = `MY_HOST;
   
  //shunt protocol
   import  shunt_dpi_pkg::*;
   import  shunt_fringe_pkg::*; 
     
   int 		      childfd_array[N_OF_SRCDSTS] = '{default:-1};

   //debugging
   bit [8:0] 	      shuntbox[3:0];
   
   //function returns placeholders
   bit 		      frng_success;
   int 		      frng_Result;
   

   //data_in_t put;
   //data_in_t get;
   
   /* verilator lint_on UNPACKED */
   
   //
   //Sim DB
   //fringe_signals_descriptor_t Signal;
   //fringe_SrcDsts_descriptor_t SrcDst;
   int 			       n_of_srcdsts;
   int                         n_of_signals;
   //Fringe DB
   //About: Fringe SrsDst DB 
   /*
    *(start code)
    *fringe_SrcDsts_descriptor_t SrcDsts_db[N_OF_SRCDSTS];//main entry descriptor
    *string 	__SrcDsts_name_db [N_OF_SRCDSTS];       //Source and Destinations namea   
    *(end code)
    */ 
   fringe_SrcDsts_descriptor_t SrcDsts_db[N_OF_SRCDSTS];//main entry 
   string 	__SrcDsts_name_db [N_OF_SRCDSTS];       //Source and Destinations namea  
   
   //Signals DB 
   //About: Fringe Signals DB 
   /*
    *(start code)
    *fringe_signals_descriptor_t signals_db[N_OF_SIGNALS];             //main descriptor
    *string 	               __signals_db_SrcDst_name[N_OF_SIGNALS]; //TODO !!!!
    *string 	               __signals_db_name[N_OF_SIGNALS];        //signal names 
    * //Paylod db
    *signal_db_data_in_t 		signals_db_payloads[N_OF_PAYLOADS];               //payload DB
    *longint 		signals_db_id_payloads[N_OF_PAYLOADS];          //signals Id DB TODO!!! 
    *(end code) 
    */
   fringe_signals_descriptor_t signals_db[N_OF_SIGNALS];               //main descriptor
   //string 	               __signals_db_SrcDst_name[N_OF_SIGNALS]; //TODO !!!!
   string 	              __signals_db_name[N_OF_SIGNALS];        //signal names 
   //Paylod db
   signal_db_data_in_t 		signals_db_payloads[N_OF_PAYLOADS];            //payload DB
   //longint 		signals_db_id_payloads[N_OF_PAYLOADS];         //signals Id DB TODO!!!
   
   longint              clk_i_cnt=0;

   string 		i_am="NA";
   string               my_source="NA";
   int                  my_parent_fd=-1;
   
   int 			sim_id=0;
   
   fringe_SrcDst_status_e my_status = FRNG_SRCDST_IDLE;
   put_get_status_t    put_status; //put data sevice request signal
   put_get_status_t    get_status; //get data sevice request signal
  
   

   always @(posedge clk_i) begin
      clk_i_cnt<=clk_i_cnt+1;
   end


    generate
      genvar genvar_put_i;
      for (genvar_put_i = 0; genvar_put_i < N_OF_SRCDSTS; genvar_put_i++) begin
	 always @(posedge clk_i) begin
	    put_status <= fringe_signal_db_put (genvar_put_i,put_status);
	 end
      end
   endgenerate

   
   generate
      genvar genvar_get_i;
      for (genvar_get_i = 0; genvar_get_i < N_OF_SRCDSTS; genvar_get_i++) begin
	 always @(posedge clk_i) begin
	    get_status <= fringe_signal_db_get(genvar_get_i,get_status);
	 end
      end
   endgenerate
 
   
   
   //
   
   //protocol Shunt functions
   
   
   ////////////////////
   //Sim general
   ///////////////////
     
   //About: Fringe EP general setting  
   /*
    Function: who_iam
    returning fringe interface instantance name set by <set_iam> function
    Parameters: N/A
    
    Returns: string instance name  
    */
   function automatic string who_iam();
      string s_me = "who_iam()";
      
      return i_am;
   endfunction : who_iam

   /*
    Function: set_iam 
    set fringe interface instantance name.
    NOTE:: name equal to "NA" resets instans name.
    Parameters: string name - instance name
    
    Returns: bit success - success=1 instance name has been accepted 
                           success=0 instance name has been rejected.
    */
   function automatic  bit set_iam(string i_am_inpit);
      string s_me = "set_iam()";
      bit success;
      success = 1;
      if(i_am == "NA" || i_am_inpit=="NA") i_am = i_am_inpit;
      else success =0;
      return success; 
   endfunction : set_iam
   
   /*
    Function: set_simid
    set sim_id.
    Parameter: sim_id_in
    NOTE: sim_id equal to 0 resets simid.
    Parameters: sim_id_in
    
    Returns: bit success - success=1  id has been accepted 
                           success=0  id has been rejected.
    */
   function automatic  bit set_simid(longint sim_id_in);
      string s_me = "set_simid()";
      /* verilator lint_off WIDTH */
      bit success;
      success = 1;
      if(sim_id == 0 ||  sim_id_in == 0) sim_id = sim_id_in;
      else success =0;
      return success;
      /* verilator lint_on WIDTH */
   endfunction : set_simid
   
   /*
    Function: get_simid
    returning fringe interface sim_id sets by <set_simid> function
    Parameters: N/A
    Returns: string instance name  
    */
   function automatic string get_simid();
      string s_me="get_simid()";
      return sim_id;
   endfunction : get_simid

   /*
    Function: set_mystatus
    set my_status ref to  <fringe_SrcDst_status_e>
    NOTE: my_status_in equal to "FRNG_SRCDST_IDLE" resets my_status
    Parameters:my_status_in
    
    Returns: bit success - success=1  new my_status has been accepted 
                           success=0  new my_status  has been rejected.
    */
   function automatic  bit set_mystatus(fringe_SrcDst_status_e my_status_in);
      string s_me = "set_mystatus()";
      /* verilator lint_off WIDTH */
      bit success;
      success = 1;
      if(my_status == FRNG_SRCDST_IDLE ||  my_status_in == FRNG_SRCDST_IDLE) my_status = my_status_in;
      else success =0;
      return success;
      /* verilator lint_on WIDTH */
   endfunction : set_mystatus
   
   /*
    Function: fring_eos
    end of simulation: close all socket;
    Parameters: N/A
    Returns: N/A
    */
   function automatic void fring_eos();
      string s_me = "fringe_eos()";
      for (int i=0; i < N_OF_SRCDSTS; i++)  shunt_dpi_close_socket(SrcDsts_db[i].socket_id);
      return;
   endfunction : fring_eos
   
   /*
    Function: get_mystatus
    returning fringe interface my_status sets by <set_simid> function
    Parameters: N/A
    Returns: fringe_SrcDst_status_e my_status
    */
   function automatic fringe_SrcDst_status_e get_mystatus();
      string s_me = "get_mystatus()";
      return my_status;
   endfunction : get_mystatus
   
   /*
    Function: get_time
    returning fringe interface internal clock counter
    Parameters: N/A
    Returns: clk_i_cnt
    */
   function automatic longint get_time();
      return clk_i_cnt;
   endfunction : get_time

   /*
    Function: print_shunt_header (cs_header_t h_,string name_in="");
    printing SHUNT header 
    Parameters: N/A
    Returns:N/A
    */
   function automatic void print_shunt_header(cs_header_t h_,string name_in="");
     //   typedef struct{		
     // longint 	 trnx_type;
     // longint 	 trnx_id;
     // longint 	 data_type;
     // int 	 n_payloads;
      //} cs_header_t;
      $display("\n%s  %s.trnx_type  = %0h",i_am,name_in, h_.trnx_type);
      $display("\n%s  %s.trnx_id    = %0h",i_am,name_in, h_.trnx_id);
      $display("\n%s  %s.data_type  = %0h",i_am,name_in, h_.data_type);
      $display("\n%s  %s.n_payloads = %0d",i_am,name_in, h_.n_payloads);
   endfunction : print_shunt_header 
   
   /*
    Function: print_localparam
    printing FRNG localparams
    Parameters: N/A
    Returns:N/A
    */
   function automatic void print_localparams();
      $display("\n%s localparam N_OF_SRCDSTS  = `FRNG_N_OF_SRCDSTS (%0d)",i_am,N_OF_SRCDSTS);
      $display("%s localparam N_OF_SIGNALS  = `FRNG_N_OF_SIGNALS (%0d)",i_am,N_OF_SIGNALS);
      $display("%s localparam N_OF_PAYLOADS = `FRNG_N_OF_PAYLOADS(%0d)",i_am,N_OF_PAYLOADS);
      $display("%s localparam MAX_N_OF_BITS_PER_SIGNAL =  `FRNG_MAX_N_OF_BITS_PER_SIGNAL(%0d)",i_am, MAX_N_OF_BITS_PER_SIGNAL);
      $display("%s localparam MAX_N_OF_PAYLOADS_PER_SIGNAL =`FRNG_MAX_N_OF_PAYLOADS_PER_SIGNAL (%0d)",i_am,MAX_N_OF_PAYLOADS_PER_SIGNAL);
      $display("%s localparam N_OF_BITS_PER_PAYLOAD = `FRNG_N_OF_BITS_PER_PAYLOAD(%0d)",i_am, N_OF_BITS_PER_PAYLOAD);
      $display("%s localparam TCP_PORT = `MY_PORT (%0d)",i_am,TCP_PORT);
      $display("%s localparam TCP_HOST = `MY_HOST (%s)",i_am,TCP_HOST);
   endfunction : print_localparams
   
   /*
    Function: print_put_get_status;
    printingput_get_status_t structure
    Parameters: N/A
    Returns:N/A
    */
   function automatic void print_put_get_status(put_get_status_t in,string name_in="");
      string s_me = "print_put_get_status()";
      
      $display("%s %s %s.success      = %0d",i_am,s_me,name_in, in.success);  
      $display("%s %s %s.signal_index = %0d",i_am,s_me,name_in, in.signal_index );
      $display("%s %s %s.event_cnt    = %0d",i_am,s_me,name_in, in.event_cnt);
     
   endfunction : print_put_get_status
   

   /*
    Function: hash2data_type
    hash to shunt_signal_type_e converter
    Parameters: hash_in - data type hash tag 
    Returns:    hash in to shunt_signal_type_e data  
    */
   function automatic shunt_signal_type_e hash2data_type(longint hash_in);
      shunt_signal_type_e data_out;
      int    n_enum;
      n_enum = data_out.num();
      data_out = data_out.first();
      
      for(int i=0;i<n_enum;i++) begin 
	 if(hash_in == shunt_dpi_hash(data_out.name())) break;
      end
      return  data_out;
      
   endfunction :  hash2data_type
   
   
     
   ////////////////
   //Sim DB
   ///////////////
   
   

   //About: SrcDsts DB init utils  
   /*
    Function:  init_SrcDsts_db
    initialisation or reset SrcDsts_db.
    Parameters:  n_of_srcdsts - number of endpoints (EP).
    Returns: bit success - success=1  status OK
                           success=0  status ERROR
    */
   function automatic  bit init_SrcDsts_db(int n_of_srcdsts_in);
      string s_me = "init_SrcDsts_db()";
      bit success;
      
      success = 1;
      n_of_srcdsts = n_of_srcdsts_in;
      
      for(int i=0;i<n_of_srcdsts_in;i++) begin
 	 SrcDsts_db[i].SrcDst_id  = -1;
 	 SrcDsts_db[i].n_signals  = -1;//SrcDsts_n_signals[i];
 	 SrcDsts_db[i].status     = FRNG_SRCDST_IDLE; //not active
 	 SrcDsts_db[i].socket_id  = -1;
	 SrcDsts_db[i].index_signal = -1;//set by init_signals_db
 	 //
 	 __SrcDsts_name_db[i]       = "NA"; //SrcDsts[i];
 	 if (get_mystatus()== FRNG_INITIATOR_ACTIVE) SrcDsts_db[i].SrcDst_id  = {$random,$random};
      end
      return success; 
   endfunction : init_SrcDsts_db

   /*
    Function:  set_SrcDsts_id
    set  a complete SrcDsts_db(i_in<0) or SrcDsts_db entry SrcDsts_id field(i>=0). 
    Parameters: i_in - number of endpoints index
    Returns: bit success - success=1  set_SrcDsts_id status OK
                           success=0  set_SrcDsts_id status ERROR
    */
    function automatic  bit set_SrcDsts_id(int i_in=-1);
      string s_me = "set_SrcDsts_id()";
       bit success;
       int i_first=0;
       int i_last=n_of_srcdsts;
       
       if (i_in >= 0) i_first =i_in;
       if (i_in >= 0) i_last = i_in+1;               
       
       success = 1;
       if (i_last > n_of_srcdsts || get_mystatus() != FRNG_INITIATOR_ACTIVE ) success = 0; 
       if (success ) begin
	  for(int i=i_first;i<i_last;i++) SrcDsts_db[i].SrcDst_id  = {$random,$random};
       end
       
       return success; 
    endfunction :set_SrcDsts_id
   
   /*
    Function:  set_SrcDst_n_signals
    set  a complete SrcDsts_db or SrcDsts_db entry SrcDst_n_signals field. 
    Parameters: int n_signals_in[N_OF_SRCDSTS] array 
    Returns: bit success - success=1  set_SrcDst_n_signals status OK
                           success=0  set_SrcDst_n_signals status ERROR
    */
    function automatic  bit set_SrcDst_n_signals(int i_in=-1,int n_signals_in[N_OF_SRCDSTS]);
      string s_me = "set_SrcDst_n_signals()";
       bit success;
       int i_first=0;
       int i_last=n_of_srcdsts;
       
       if (i_in >= 0) i_first =i_in;
       if (i_in >= 0) i_last = i_in+1;               
       
       success = 1;
       if (i_last > n_of_srcdsts) success = 0; 
       if (success ) begin
	  for(int i=i_first;i<i_last;i++) SrcDsts_db[i].n_signals  = n_signals_in[i];
       end
       
       return success; 
    endfunction :set_SrcDst_n_signals
   
   /*
    Function:  set_SrcDst_name
    set  a complete __SrcDsts_name_db or __SrcDsts_name_db  entry. 
    Parameters: string name_in[N_OF_SRCDSTS] array 
    Returns: bit success - success=1  set_SrcDst_name status OK
                           success=0  set_SrcDst_name status ERROR
    */
   function automatic  bit set_SrcDst_name(int i_in=-1,string name_in[N_OF_SRCDSTS]);
      string s_me = "set_SrcDst_name()";
      bit success;
      int i_first=0;
      int i_last=n_of_srcdsts;
      
      if (i_in >= 0) i_first =i_in;
      if (i_in >= 0) i_last = i_in+1;               
      
      success = 1;
      if (i_last > n_of_srcdsts) success = 0; 
      if (success ) begin
	 for(int i=i_first;i<i_last;i++) __SrcDsts_name_db[i]  = name_in[i];
      end
      
      return success; 
   endfunction : set_SrcDst_name
   
   /*
    Function:   fringe_api_get_by_signal_index
    PnP "play" function recieves a signal <signal name> , from a source <source_name> to the specified data output <data>
    Parameters: 
    string source_name - data source (from)   
    string signal_name - data source signal name 
    data_in_t data     - data output
    Returns: success bit 1-ok , 0- ERROR 
    */
   function automatic bit  fringe_api_get_by_signal_index (int source_signals_db_index,inout data_in_t data);
      bit     success;
      string  s_me;
      longint source_signal_id;
      longint SrcDst_parent_id;
      int     source_SrcDst_db_index;
      int     signals_db_index_payload;
      int     number_payloads;
      data_in_t	  data_;
                  
      s_me = "fringe_api_get_by_signal_index()";
      data_.data_bit   = 0;
      data_.data_logic = 0;
      //
      success =1;
      //
      source_signal_id            = signals_db[source_signals_db_index].signal_id;
      SrcDst_parent_id            = signals_db[source_signals_db_index].SrcDst_parent_id;
      
      source_SrcDst_db_index      = get_index_by_id_SrcDsts_db(SrcDst_parent_id);
      signals_db_index_payload    = signals_db[source_signals_db_index].index_payloads;
      number_payloads             = signals_db[source_signals_db_index].number_payloads;
      
      //$display("%s  %s source_signal_id=%0h",i_am,s_me,source_signal_id);
      //$display("%s  %s source_SrcDst_db_index=%0d",i_am,s_me,source_SrcDst_db_index);
      //$display("%s  %s source_signals_db_index=%0d",i_am,s_me,source_signals_db_index);
      //$display("%s  %s signals_db_index_payload=%0d",i_am,s_me,signals_db_index_payload);
      //$display("%s  %s number_payloads=%0d",i_am,s_me,number_payloads);
      
      if (source_signal_id<0 && source_SrcDst_db_index<0 && signals_db_index_payload <0 && number_payloads<0) success =0;
      if (signals_db[source_signals_db_index].signal_valid != FRNG_SIGNAL_VALID_GET)  success =0;
      //
      if (success) begin
	 for(int i=0;i<number_payloads;i++) begin
	    //$display("%s  %s signals_db_payloads[%0d]=%h",i_am,s_me,signals_db_index_payload+i,signals_db_payloads[signals_db_index_payload+i].data_bit);
	    data_.data_bit   = data_.data_bit    >> N_OF_BITS_PER_PAYLOAD;
	    data_.data_logic = data_.data_logic  >> N_OF_BITS_PER_PAYLOAD;
	    //$display("%s  %s shift data_.data_bit= %h ,signal_db=%h",i_am,s_me,data_.data_bit,signals_db_payloads[signals_db_index_payload+i].data_bit);
	    data_.data_bit[MAX_N_OF_BITS_PER_SIGNAL-1:MAX_N_OF_BITS_PER_SIGNAL-N_OF_BITS_PER_PAYLOAD] = signals_db_payloads[signals_db_index_payload+i].data_bit;
	    //$display("%s  %s data_.data_bit= %h ,signal_db=%h",i_am,s_me,data_.data_bit,signals_db_payloads[signals_db_index_payload+i].data_bit);
	 end // for (int i=signals_db_index_payload;i<signals_db_index_payload+number_payloads;i++)
	 signals_db[source_signals_db_index].signal_valid = FRNG_SIGNAL_IDLE;
	 SrcDsts_db[source_SrcDst_db_index].signal_status = FRNG_SIGNAL_IDLE;
	 if (signals_db[source_signals_db_index].signal_port_type == FRNG_PORT_NA)signals_db[source_signals_db_index].signal_port_type =FRNG_PORT_INPUT;
	 if (signals_db[source_signals_db_index].signal_port_type != FRNG_PORT_INPUT) $display(" ERROR: %s %s signal_port_type should be FRNG_PORT_INPUT ",i_am,s_me);
	 data= data_;
      end // if (success && signals_db[source_signals_db_index].signal_valid == FRNG_SIGNAL_VALID_GET)
      //$display("%s  %s output data.data_bit= %0h(%0h)",i_am,s_me,data.data_bit,data_.data_bit);
      return success;
      
endfunction : fringe_api_get_by_signal_index
   
   /*
    Function:  set_SrcDst_db_entry
    set  a complete __SrcDsts_name_db and SrcDsts_db  entres. 
    Parameters: string name_in[N_OF_SRCDSTS] array 
    Returns: bit success - success=1  set_SrcDst_db_entry status OK
                           success=0  set_SrcDst_db_entry status ERROR
    */
   function automatic  bit set_SrcDst_db_entry(string name_in,int n_signals_in );
      string s_me = "set_SrcDst_db_entry()";
      bit success;
      int write_index=-1;
            
      //NEW
      //Find an empty Signal_db etry
      success = 1;
      foreach(SrcDsts_db[i]) begin
	 if (__SrcDsts_name_db[i] == name_in) success = 0;
	 if (__SrcDsts_name_db[i] == "NA" && success) begin
	    write_index = i;
	    SrcDsts_db[write_index].n_signals  = n_signals_in;
 	    __SrcDsts_name_db[write_index]  = name_in;
	 end // if (__SrcDsts_name_db[i] == "NA" && success)
	 if(write_index>=0 || ! success) break;
      end // foreach (SrcDsts_db[i])
      if (write_index<0) success = 0; 
      return success; 
   endfunction : set_SrcDst_db_entry

  
   /*
    Function:  set_signal_db_entry
    set  a complete __signal_name_db & signal_db.signal_id fields or __SrcDsts_name_db&signal_db.signal_id fields  entry. 
    Parameters: string parent_name_in - a corresponding  SrcDst_parent_id , string signal_name_in[N_OF_SIGNALS] signal name array 
    Returns: bit success - success=1  set_signal_db_entry status OK
                           success=0  set_signal_db_entry status ERROR
    */
   function automatic  bit set_signal_db_entry(string parent_name_in,string signal_name_in,int signal_type_in, int signal_size_in,fringe_port_type_e signal_port_type_in=FRNG_PORT_NA);
      string s_me = "set_signal_db_entry()";
      bit success;
      int write_index;
      int index=-1; 
      int i_first;
      int i_last;
      
      
      success=0;
      write_index=-1;
     
      
      index = get_index_by_name_SrcDsts_db(parent_name_in);
      
      i_first = SrcDsts_db[index].index_signal;
      i_last  = SrcDsts_db[index].index_signal+SrcDsts_db[index].n_signals;
      if (index>=0 )success = 1;
      
      //$display("parent_name_in=%s(%h),signal_name_in=%s,signal_type_in=%0d,signal_size_in=%0d",parent_name_in,shunt_dpi_hash(parent_name_in),signal_name_in,signal_type_in,signal_size_in);
      
      if (success) begin
	 //find signal duplication
	 for(int i=i_first;i<i_last;i++) begin
	    if (__signals_db_name[i]  == signal_name_in) success = 0;
	 end
      end
      if (success ) begin
	 //find an empty signal 
	 for(int i=i_first;i<i_last;i++) begin
	     
	    if (__signals_db_name[i]  == "NA" && signals_db[i].SrcDst_parent_id == SrcDsts_db[index].SrcDst_id) begin 
	       write_index = i;
	       break;
	    end
	 end // for (int i=i_first;i<i_last;i++)
      end // if (success )
      //$display("%s parent=%s index=%0d i_first=%0d  i_last=%0d n_of_signals=%0d success=%0d write_index=%0d\n",s_me,parent_name_in,index,i_first,i_last,n_of_signals,success,write_index); 
      if  (write_index>=0)  begin 
	 success = 1;
	 __signals_db_name[write_index] = signal_name_in;
	 signals_db[write_index].signal_id  = shunt_dpi_hash({parent_name_in,".", __signals_db_name[write_index]});
	 signals_db[write_index].signal_port_type = signal_port_type_in;
	 //signals_db[write_index].SrcDst_parent_id=SrcDsts_db[j].SrcDst_id; TODO
	 //signals_db[write_index].SrcDst_call_id = -1;  TODO
	 signals_db[write_index].signal_type =signal_type_in;
	 signals_db[write_index].signal_size =signal_size_in;
      end // if (write_index>=0)
      
      return success; 
   endfunction : set_signal_db_entry
 
      /*
    Function:  print_SrcDsts_db
    print SrcDsts_db or SrcDsts_db entry.
    Parameters: i_in - SrcDst_db entry index , if i_in<0(default) print out complete DB  
    Returns: bit success - success=1  print status OK
                           success=0  print status ERROR
    */
   function automatic  bit print_SrcDsts_db(int i_in=-1);
      string s_me = "print_SrcDsts_db()";
      
      //longint 	       SrcDst_id;     // SrcDst DB entry Id, 
      //int 	               n_signals;     // SrcDst DB entry number of signals,
      //int 	               socket_id;     // SrcDst DB entry TCP_ destination socket id  
      //fringe_SrcDst_status_e   status;      // SrcDst DB entry status
      //fringe_signal_hs_e            signal_status; // SrcDst DB entry agregated signal status 
      
      bit success;
      int i_first=0;
      int i_last=n_of_srcdsts;
      
      success = 1;
      if (i_last > n_of_srcdsts) success = 0; 

      if (success) begin 
	 if (i_in>=0) i_first = i_in;
	 if (i_in>=0) i_last  = i_first+1;
	 if (i_in<0) i_last = $size(SrcDsts_db);
      	 for(int i=i_first;i<i_last;i++) begin
 	    $display("\n%s SrcDsts_db[%0d].SrcDst_id  =%0h",i_am,i,SrcDsts_db[i].SrcDst_id);
 	    $display("%s SrcDsts_db[%0d].n_signals  =%0d",i_am,i,SrcDsts_db[i].n_signals);
 	    $display("%s SrcDsts_db[%0d].socket_id  =%0d",i_am,i,SrcDsts_db[i].socket_id);
	    $display("%s SrcDsts_db[%0d].index_signal  =%0d",i_am,i,SrcDsts_db[i].index_signal);
 	    $display("%s SrcDsts_db[%0d].status     =%s",i_am,i,SrcDsts_db[i].status.name());
	    $display("%s SrcDsts_db[%0d].signal_status=%s",i_am,i,SrcDsts_db[i].signal_status.name());
	    
 	    $display("%s __SrcDst_name_db[%0d]      =%s\n",i_am,i,__SrcDsts_name_db[i]);
	 end
      end // if (success)
      
      return success; 
   endfunction : print_SrcDsts_db
   
   //About: SrcDst DB access utils    
  
   /*
    Function: get_index_by_id_SrcDsts_db 
    find SrcDst index corresponding to SrcDsts_id
    Parameters: SrcDsts_id
    Returns: int index >=0 , index<0 is  ERROR
    */ 
   function automatic  int get_index_by_id_SrcDsts_db(longint SrcDst_indx_in);
      string s_me = "get_index_by_id_SrcDsts_db()";
      int    index;
       
      index = -1;
      s_me = "get_index_by_id_SrcDsts_db()";
      
      for(int i=0;i<N_OF_SRCDSTS;i++) begin
	 if ( SrcDsts_db[i].SrcDst_id ==  SrcDst_indx_in && index<0) index = i;
      end // for (int i=0;i<N_OF_SRCDSTS;i++)
      return index;
   endfunction : get_index_by_id_SrcDsts_db
   

    /*
    Function: get_name_by_index_SrcDsts_db
    find SrcDst name by index ,name="NA" is ERROR;
    Parameters: index
    Returns: SrcDst name
    */ 
   function automatic  string get_name_by_index_SrcDsts_db(int index);
      
      string s_me;
      string Name;
      Name = "NA";
      
      s_me = "get_name_by_index_SrcDsts_db()";
      Name ="NA";
      if (index <N_OF_SRCDSTS) Name = __SrcDsts_name_db[index];
      
      return Name;
    endfunction : get_name_by_index_SrcDsts_db
   
   /*
    Function: get_index_by_name_SrcDsts_db 
    find SrcDst index corresponding to __SrcDsts_name_db entry
    Parameters: string Name)
    Returns: int index >=0 , index<0 is  ERROR
    */ 
   function automatic  int get_index_by_name_SrcDsts_db(string Name);
      string s_me;
      int    index;
   
      index = -1;
      s_me = "get_index_by_name_SrcDsts_db()";
      
      for(int i=0;i<N_OF_SRCDSTS;i++) begin
	 if (__SrcDsts_name_db[i] == Name && index<0) index = i;
	 if (index>=0) break;
      end // for (int i=0;i<N_OF_SRCDSTS;i++)
      return index;
   endfunction : get_index_by_name_SrcDsts_db
   
   /*
    Function:  get_index_by_name_hash_SrcDsts_db
    find SrcDst index corresponding to __SrcDsts_name_db entry
    Parameters: string Name)
    Returns: int index >=0 , index<0 is  ERROR
    */ 
   function automatic  int get_index_by_name_hash_SrcDsts_db(longint Name_hash);
      string s_me;
      int    index;
      longint hash_;
      
      index = -1;
      s_me = "get_index_by_name_hash_SrcDsts_db()";
      
      for(int i=0;i<N_OF_SRCDSTS;i++) begin
	 hash_ =shunt_dpi_hash(__SrcDsts_name_db[i]); 
	 if (hash_ == Name_hash && index<0) index = i;
      end // for (int i=0;i<N_OF_SRCDSTS;i++)
      return index;
   endfunction : get_index_by_name_hash_SrcDsts_db
   
   //About: Signal DB init utils     
   /*
    Function:  init_signal_db
    initialisation or reset signal_db.
    Parameters:  
    Returns: bit success - success=1  status OK
                           success=0  status ERROR
    */
   function automatic  bit init_signals_db();
      //  longint 	               signal_id;            //unique signal identifier corresponding to the full signal name
      //  longint 		       SrcDst_parent_id;     //corresponding SrcDst DB parent entry
      //  longint 		       SrcDst_coll_id;     //index pointer to the SrcDst DB correspondent id
      //  int 		               index_payloads;    //index pointer to the corresponding signal payloads_db entry  
      //  shunt_signal_type_e;   signal_type;            //signal data type
      //  int 		       signal_size;          //signal size
      //  fringe_signal_hs_e      signal_valid;           //signal handshake flag    
      //  int 		       timestamp;            //last signal event simulation time  
      //  int 		       event_cntr;           //number of signal events 
      //  fringe_signal_debug_e   debug;                //debug flag 
      bit    success;
      string s_me = "init_signals_db()";
      int    signal_index;
      
      success = 1;
      signal_index =0;
      
      foreach(SrcDsts_db[j]) begin
	 //success = print_SrcDsts_db(j);
	 SrcDsts_db[j].index_signal = signal_index;
	 for(int i=signal_index;i<signal_index+SrcDsts_db[j].n_signals;i++) begin
            //$display("for i=%0d;i<%0d",i,signal_index+SrcDsts_db[j].n_signals);
	    signals_db[i].signal_id = -1;
	    signals_db[i].SrcDst_parent_id=SrcDsts_db[j].SrcDst_id;
	    signals_db[i].SrcDst_call_id = -1;
	    //
	    signals_db[i].number_payloads = (MAX_N_OF_BITS_PER_SIGNAL/N_OF_BITS_PER_PAYLOAD);
	    //
	    if (MAX_N_OF_BITS_PER_SIGNAL%MAX_N_OF_PAYLOADS_PER_SIGNAL >0) signals_db[i].number_payloads++;
	    if (i==0) signals_db[i].index_payloads =0;
	    else signals_db[i].index_payloads = signals_db[i-1].index_payloads + signals_db[i-1].number_payloads;
	    //
	    signals_db[i].signal_type =SHUNT_NA;
	    signals_db[i].signal_size = -1;
	    signals_db[i].signal_valid = FRNG_SIGNAL_IDLE;
	    signals_db[i].signal_port_type = FRNG_PORT_NA;    //signal port type   
	    signals_db[i].event_cntr = 0;
	    signals_db[i].debug = FRNG_PRINT;
	    __signals_db_name[i] = "NA";
	     //success = print_signals_db(i);
	 end // for (i=0;i< SrcDsts_db[i].n_signals;i++)
	 signal_index = signal_index + SrcDsts_db[j].n_signals;
      end // foreach (SrcDsts_db[j])
      return success; 
   endfunction :init_signals_db


   /*
    Function:  set_signal_name_id
    set  a complete __signal_name_db & signal_db.signal_id fields or __SrcDsts_name_db&signal_db.signal_id fields  entry. 
    Parameters: string parent_name_in - a corresponding  SrcDst_parent_id , string signal_name_in[N_OF_SIGNALS] signal name array 
    Returns: bit success - success=1  set_signal_name_id status OK
                           success=0  set_signal_name_id status ERROR
    */
   function automatic  bit set_signal_name_id(string parent_name_in,string signal_name_in[N_OF_SIGNALS]);
      string s_me = "set_signal_name_id()";
      bit success;
      int i_first=0;
      int i_last=n_of_signals;
      int index;
      int index_signal_name=0;
      
      
      
      index = get_index_by_name_SrcDsts_db(parent_name_in);
      i_first=SrcDsts_db[index].n_signals*index;
      i_last =SrcDsts_db[index].n_signals*index+SrcDsts_db[index].n_signals;
      
      success = 1;
      if (i_last > n_of_signals) success = 0;
      $display("%s i_first=%0d  i_last=%0d n_of_signals=%0d success=%0d \n",s_me,i_first,i_last,n_of_signals,success);
      if (success ) begin
	 for(int i=i_first;i<i_last;i++) begin
	     __signals_db_name[i]  = signal_name_in[index_signal_name];
	    signals_db[i].signal_id  = shunt_dpi_hash({parent_name_in,".", __signals_db_name[i]});
	    index_signal_name++;
	    //$display("%s signal_name_in[%0d]=%s ",s_me,i,signal_name_in[i]);
	 end
      end
      return success; 
   endfunction : set_signal_name_id
   
   

 /*
    Function:  set_signal_type
    set a signal_db.signal fields  entry. 
    Parameters: string parent_name_in - a corresponding  SrcDst_parent_id , ,shunt_signal_type_e signal_type_in[N_OF_SIGNALS] signal name array 
    Returns: bit success - success=1  set_signal_type status OK
                           success=0  set_signal_type status ERROR
    */

   function automatic  bit set_signal_type(string parent_name_in,shunt_signal_type_e signal_type_in[N_OF_SIGNALS]);
      string s_me = "set_signal_type()";
      bit success;
      int i_first=0;
      int i_last=n_of_signals;
      int index;
      int index_signal_type=0;
      
      
      
      index = get_index_by_name_SrcDsts_db(parent_name_in);
      i_first=SrcDsts_db[index].n_signals*index;
      i_last =SrcDsts_db[index].n_signals*index+SrcDsts_db[index].n_signals;
      
      success = 1;
      if (i_last > n_of_signals) success = 0;
     
      if (success ) begin
	 for(int i=i_first;i<i_last;i++) begin
	    signals_db[i].signal_type  = signal_type_in[index_signal_type];
	    index_signal_type++;
	 end
      end
      return success; 
   endfunction : set_signal_type
   
 
  /*
    Function:  set_signal_size
    set a signal_db.signal fields  entry. 
    Parameters: string parent_name_in - a corresponding  SrcDst_parent_id ,fringe_signal_size_e signal_size_in[N_OF_SIGNALS] signal name array 
    Returns: bit success - success=1  set_signal_size status OK
                           success=0  set_signal_size status ERROR
    */

   function automatic  bit set_signal_size(string parent_name_in,int signal_size_in[N_OF_SIGNALS]);
      string s_me = "set_signal_size()";
      bit success;
      int i_first=0;
      int i_last=n_of_signals;
      int index;
      int index_signal_size=0;
                      
      index = get_index_by_name_SrcDsts_db(parent_name_in);
      i_first=SrcDsts_db[index].n_signals*index;
      i_last =SrcDsts_db[index].n_signals*index+SrcDsts_db[index].n_signals;
      
      success = 1;
      if (i_last > n_of_signals) success = 0;
     
      if (success ) begin
	 for(int i=i_first;i<i_last;i++) begin
	    int size=0;
	    signals_db[i].signal_size  = signal_size_in[index_signal_size];
	    //
	    /* -----\/----- EXCLUDED -----\/-----
	     if (signals_db[i].signal_type ==SHUNT_BIT)     size = 1*  signals_db[i].signal_size;
	     if (signals_db[i].signal_type ==SHUNT_BYTE)    size = 8*  signals_db[i].signal_size; 
	     if (signals_db[i].signal_type ==SHUNT_INTEGER) size = 32* signals_db[i].signal_size;  
	     if (signals_db[i].signal_type ==SHUNT_REG)     size = 1*  signals_db[i].signal_size;
	     -----/\----- EXCLUDED -----/\----- */
	    //
	    
	    signals_db[i].number_payloads =  (MAX_N_OF_BITS_PER_SIGNAL/N_OF_BITS_PER_PAYLOAD);
	    if (MAX_N_OF_BITS_PER_SIGNAL%MAX_N_OF_PAYLOADS_PER_SIGNAL >0) signals_db[i].number_payloads++;
	    
	    if (i==0) signals_db[i].index_payloads =0;
	    else signals_db[i].index_payloads = signals_db[i-1].index_payloads + signals_db[i-1].number_payloads;
	    
	    index_signal_size++;
	 end // for (int i=i_first;i<i_last;i++)
	 
	 
      end
      return success; 
   endfunction : set_signal_size
   
   /*
    Function: get_index_by_SrcDst_parent_id_signal_db
    find first signals_db index corresponding to SrcDsts_id
    Parameters: SrcDsts_id
    Returns: int index >=0 , index<0 is  ERROR
    */ 
   function automatic  int get_index_by_SrcDst_parent_id_signal_db(longint SrcDst_indx_in);
      string s_me;
      int    index;
       
      index = -1;
      s_me = "get_index_by_SrcDst_parent_id_signal_db";
      
      foreach(signals_db[i]) begin
	 if (signals_db[i].SrcDst_parent_id ==  SrcDst_indx_in && index<0) index = i;
	 if (index>=0) break;
      end // for (int i=0;i<N_OF_SRCDSTS;i++)
      return index;
   endfunction : get_index_by_SrcDst_parent_id_signal_db
 
 /*
    Function: get_index_by_signal_id_signals_db
    find unique signals_db index corresponding to signal_id
    Parameters: signal_id
    Returns: int index >=0 , index<0 is  ERROR
    */   
 function automatic  int get_index_by_signal_id_signals_db(longint signal_id);
    string s_me;
    int    index;
    
    index = -1;
    s_me = "get_index_by_signal_id_signals_db()";
    
    foreach(signals_db[i]) begin
       if (signals_db[i].signal_id == signal_id) index = i;
       if (index>=0) break;
    end // for (int i=0;i<N_OF_SRCDSTS;i++)
    
    return index;
 endfunction : get_index_by_signal_id_signals_db
   
  
  /*
    Function:  print_signal_db
    print signal_db or signal_db entry.
    Parameters: i_in - signal_db entry index , if i_in<0(default) print out complete DB  
    Returns: bit success - success=1  print status OK
                           success=0  print status ERROR
    */
function automatic  bit print_signals_db(int i_in=-1);
      string s_me = "print_signals_db()";
   
   //  longint 	               signal_id;            //unique signal identifier corresponding to the full signal name
   //  longint 		       SrcDst_parent_id;     //corresponding SrcDst DB parent entry
   //  longint 		       SrcDst_coll_id;       //index pointer to the SrcDst DB correspondent id
   //  int 		       index_payloads;    //index pointer to the corresponding signal payloads_db entry  
   //  shunt_signal_type_e;    signal_type;          //signal data type
   //  int 		       signal_size;          //signal size
   //  fringe_signal_hs_e      signal_valid;         //data handshake flag
   //  fringe_port_type_e      signal_port_type;    //signal port type   
   //  int 		       timestamp;            //last signal event simulation time  
   //  int 		       event_cntr;           //number of signal events 
   //  fringe_signal_debug_e   debug;                //debug flag 
   
   
   bit success;
   int i_first=0;
   int i_last=N_OF_SIGNALS;
   
   success = 1;
   if (i_last > N_OF_SIGNALS) success = 0; 
   
   if (success) begin 
      if (i_in>=0) i_first = i_in;
      if (i_in>=0) i_last  = i_first+1;	
      for(int i=i_first;i<i_last;i++) begin
	 int Src_Dst_index  =  get_index_by_id_SrcDsts_db(signals_db[i].SrcDst_parent_id);
	 string parent_name =  get_name_by_index_SrcDsts_db(Src_Dst_index);
	 $display("\n%s signals_db[%0d].signal_id       = %0h",i_am,i,signals_db[i].signal_id);
	 $display("%s signals_db[%0d].SrcDst_parent_id  = %0h(%s)",i_am,i,signals_db[i].SrcDst_parent_id,parent_name);
	 $display("%s signals_db[%0d].SrcDst_call_id    = %0h",i_am,i,signals_db[i].SrcDst_call_id);
	 $display("%s signals_db[%0d].signal_type       = %s" ,i_am,i,signals_db[i].signal_type.name());
	 $display("%s signals_db[%0d].signal_size       = %0d" ,i_am,i,signals_db[i].signal_size);
	 $display("%s signals_db[%0d].signal_valid      = %s" ,i_am,i,signals_db[i].signal_valid.name());
	 $display("%s signals_db[%0d].signal_port_type  = %s" ,i_am,i,signals_db[i].signal_port_type.name());
	 $display("%s signals_db[%0d].index_payloads    = %0d",i_am,i,signals_db[i].index_payloads);
	 $display("%s signals_db[%0d].number_payloads   = %0d",i_am,i,signals_db[i].number_payloads);
	 $display("%s signals_db[%0d].timestamp         = %0d",i_am,i,signals_db[i].timestamp);
	 $display("%s signals_db[%0d].event_cntr        = %0d",i_am,i,signals_db[i].event_cntr);
 	 $display("%s  __signals_db_name[%0d]           = %s\n",i_am,i, __signals_db_name[i]);
      end
   end // if (success)
   
   return success; 
endfunction : print_signals_db
    
   //About: TCP socket initialisation and PnP "plug" registration
   
   /*
    Function: pnp_init 
    set  a complete SrcDsts_db(i_in<0) or SrcDsts_db entry SrcDsts_id field(i>=0). 
    Parameters: N/A
    Returns: bit success - success=1  Plug-N-Play init  OK
                           success=0  Plug-N-Play init  ERROR 
    
    */  
   function automatic bit pnp_init();
      string 	s_me = "pnp_init()";
      bit 	success;
      int    socket = -1;
      
      success =1;
      if (get_mystatus()== FRNG_INITIATOR_ACTIVE && success==1) begin 
	 success = tcp_connect_n_frng_reg_initiator(`MY_PORT);
	 $display("INFO: Frng_if.pnp_init() %s tcp_connect_n_frng_reg_initiator my_parent_fd=%0d success=%0d",Frng_if.who_iam(),my_parent_fd,success);
      end
      if (get_mystatus()== FRNG_TARGET_ACTIVE    && success==1) begin 
	 success = tcp_connect_n_frng_reg_target (`MY_PORT,`MY_HOST);
	 $display("INFO: Frng_if.pnp_init() %s tcp_connect_n_frng_reg_target success=%0d",Frng_if.who_iam(),success);
      end
      if (success==1)  $display("\nPASS %s %s pnp_init(); ",s_me,i_am);
      else success =0;
      
      return success;
      
   endfunction : pnp_init
   
    /*
     Function:  tcp_connect_n_frng_reg_initiator
     establish a TCP socket connection (Initiator EP) 
     Parameters: portno -  A designated TCP host port  
     Returns: bit success - success=1  Plug-N-Play init  OK
                            success=0  Plug-N-Play init  ERROR 
     */
   function automatic bit tcp_connect_n_frng_reg_initiator(int portno);
      string s_me = "tcp_connect_n_frng_reg_initiator()";
      bit    success;
      int    parent_id=-1;
      int    SrcDst_db_index;
      
      int    child_id;
      
      success =0;
      if (get_mystatus()== FRNG_INITIATOR_ACTIVE)
	begin
	   parent_id = shunt_dpi_listener_init(portno);
	   //
	   //
	   success =1;
	   SrcDst_db_index = get_index_by_name_SrcDsts_db(who_iam());
	   SrcDsts_db[SrcDst_db_index].socket_id  = -1;
	   my_parent_fd = parent_id;
	   //
	   for(int i=0;i<N_OF_SRCDSTS-1;i++)  begin
	      child_id = shunt_dpi_tcp_connect(parent_id);
	      if(!SrcDst_registration_response(child_id)) begin
		 $display("\n%s ERROR: %s SrcDst_registration_response",s_me,i_am);
		 success =0;
	      end
	   end // for (int i=0;i<N_OF_SRCDSTS-1;i++)
	end // if (get_mystatus()== FRNG_INITIATOR_ACTIVE)
      return success;
   endfunction : tcp_connect_n_frng_reg_initiator
   

   /*
    Function: tcp_connect_n_frng_reg_target 
    establish a TCP socket connection (Target EP) 
    Parameters: portno - A designated TCP host port ,string hostname - A designated TCP host address
    Returns: bit success - success=1  Plug-N-Play init  OK
                           success=0  Plug-N-Play init  ERROR 
     */
   function automatic bit tcp_connect_n_frng_reg_target(int portno,string hostname);
      string s_me = "tcp_connect_n_frng_reg_target()";
      bit    success=0;
      int    socket_id=-1;
      int    SrcDst_db_index;
      
      socket_id = -1;
      SrcDst_db_index = get_index_by_name_SrcDsts_db(who_iam());
       if (get_mystatus()== FRNG_TARGET_ACTIVE)
	 begin
	    socket_id = shunt_dpi_target_init(portno,hostname);
	    $display("INFO: tcp_connect_n_frng_reg_target() %s socket_id=%0d",Frng_if.who_iam(),socket_id);
	    if(socket_id>=0) begin
   	       if(!SrcDst_registration_request(socket_id))
		 $display("\n%s ERROR:tcp_connect_n_frng_reg_target()  %s SrcDst_registration_request",s_me,i_am);
	       else begin
		  SrcDsts_db[SrcDst_db_index].socket_id  = socket_id;
		  $display("\n%s PASS:tcp_connect_n_frng_reg_target() %s SrcDst_registration_request",s_me,i_am);
		  success=1;
	       end
	    end // if (socket_id>=0)
	    
	 end // if (get_mystatus()== FRNG_TARGET_ACTIVE)
      return success;
 
   endfunction : tcp_connect_n_frng_reg_target
  
   /*
    Function:  SrcDst_registration_request
    PnP "plug" registration request-acknowledge function   
    Parameters:int socket_id - a corresponding TCP connection socket id;
    Returns: bit success - success=1 Plug-N-Play registration  OK
                           success=0 Plug-N-Play registration  ERROR 
     */  
   function automatic bit SrcDst_registration_request(int socket_id);
      bit    success;
      int    SrcDst_db_index= -1;
      cs_header_t h_;
      string s_me = "SrcDst_registration_reques()";
      
      h_.trnx_type  = shunt_dpi_hash("FRNG_REQ");
      h_.data_type  = shunt_dpi_hash(who_iam());
      h_.trnx_id    = 0;
      h_.n_payloads = sim_id;
      if (shunt_dpi_send_header(socket_id,h_)>0) success = 1;
      else success =0;
 
      //
      if(success) begin
	 if (shunt_dpi_recv_header(socket_id,h_) >0) begin
	    success=1;
	    SrcDst_db_index = get_index_by_name_hash_SrcDsts_db(h_.data_type);
	    //
	    if (h_.trnx_type == shunt_dpi_hash("FRNG_ACK") && 
		h_.n_payloads == sim_id && 
		h_.data_type == shunt_dpi_hash(who_iam()) &&
		h_.trnx_id  != -1  &&h_.trnx_id  != 0 && 
		SrcDst_db_index>=0 &&
		SrcDsts_db[SrcDst_db_index].socket_id < 0 &&
		SrcDsts_db[SrcDst_db_index].status  == FRNG_SRCDST_IDLE &&
		success
		) success = 1;
	    else success = 0;
	    
	    if (success) begin
	       SrcDsts_db[SrcDst_db_index].socket_id =  socket_id;
	       SrcDsts_db[SrcDst_db_index].status    = FRNG_SRCDST_ACTIVE;
	       SrcDsts_db[SrcDst_db_index].SrcDst_id = h_.trnx_id;
	    end
	    
	    success = 0;
	    if (shunt_dpi_recv_header(socket_id,h_) >0) success=1;
	    SrcDst_db_index = get_index_by_name_hash_SrcDsts_db(h_.data_type);
	    //
	    if (h_.trnx_type == shunt_dpi_hash("FRNG_ACK") && 
		h_.n_payloads == sim_id  &&
		h_.trnx_id  != -1  &&h_.trnx_id  != 0 &&
		success 
		) success = 1;
	    else success = 0;
	    
	    if (success) begin
	       SrcDsts_db[SrcDst_db_index].socket_id =  socket_id;
	       SrcDsts_db[SrcDst_db_index].status    = FRNG_SRCDST_ACTIVE;
	       SrcDsts_db[SrcDst_db_index].SrcDst_id = h_.trnx_id;
	       SrcDsts_db[SrcDst_db_index].socket_id =  socket_id;
	       my_source = __SrcDsts_name_db[SrcDst_db_index];
	    end
	 end // if (shunt_dpi_recv_header(socket_id,h_) >0)
      end // if (success)
      $display("\n %s %s success=%0d SrcDst_db_index=%0d\n",s_me,i_am,success,SrcDst_db_index);
      //
      return success;
   endfunction : SrcDst_registration_request

    /*
     Function:  SrcDst_registration_response
     PnP "plug" registration response-acknowledge function   
     Parameters:int socket_id - a corresponding TCP connection socket id;
     Returns: bit success - success=1 Plug-N-Play registration  OK
                            success=0 Plug-N-Play registration  ERROR 
     */  
  
  function automatic bit SrcDst_registration_response(int socket_id);
     bit    success;
     int     SrcDst_db_index=-1;
     cs_header_t h_;
     string  s_me = "SrcDst_registration_response()";
     
     success = 0;
     if (shunt_dpi_recv_header(socket_id,h_)>0)  begin 
	success = 1;
        SrcDst_db_index = get_index_by_name_hash_SrcDsts_db(h_.data_type);
	//
	if (
	    success &&
	    h_.trnx_type == shunt_dpi_hash("FRNG_REQ") && 
	    h_.n_payloads == sim_id && 
	    SrcDst_db_index>=0 &&
	    SrcDsts_db[SrcDst_db_index].socket_id < 0 &&
	    SrcDsts_db[SrcDst_db_index].status  == FRNG_SRCDST_IDLE
	    ) success = 1;
	
	if (success) SrcDsts_db[SrcDst_db_index].socket_id =  socket_id;
	if (success) SrcDsts_db[SrcDst_db_index].status  = FRNG_SRCDST_ACTIVE;
	
	//send Dst DB info
	h_.trnx_type  = shunt_dpi_hash("FRNG_ACK");
	if (success) h_.trnx_id   = SrcDsts_db[SrcDst_db_index].SrcDst_id; //FRNG_ACK OK
	else  h_.trnx_id   = -1;                                           //FRNG_ACK ERR
	h_.n_payloads = sim_id;
	if(shunt_dpi_send_header(socket_id,h_)>0 && success)success=1;
	
	//send Src DB info
	SrcDst_db_index = get_index_by_name_SrcDsts_db(who_iam());
	h_.trnx_type  = shunt_dpi_hash("FRNG_ACK");
	h_.data_type  = shunt_dpi_hash(who_iam());
	if (success) h_.trnx_id   = SrcDsts_db[SrcDst_db_index].SrcDst_id; //FRNG_ACK OK
	else  h_.trnx_id   = -1;                                           //FRNG_ACK ERR
	h_.n_payloads = sim_id;
	if(shunt_dpi_send_header(socket_id,h_)>0 && success)success=1;  
     end // if (shunt_dpi_recv_header(socket_id,h_)>0)
     //
     $display("\n %s %s success=%0d SrcDst_db_index=%0d\n",s_me,i_am,success,SrcDst_db_index);
     return success;
  endfunction : SrcDst_registration_response
   
   //About: Fringe PnP Play
   
   //About: API
    /*
    Function:  fringe_api_put
    PnP "play" function sends a data <data_in> that assosiated with a destination< destination_name> signal <signal name>
    Parameters: 
    destination_name - destination (to)
    string signal_name - signal 
    shunt_signal_type_e data_type -  defining a data structure element . It can be SHUNT_BIT (defult) or SHUNT_LOGIC.  
    data_in_t data_in   - data to send.
    
    Returns: success bit 1-ok , 0- ERROR 
     */
   function automatic bit fringe_api_put (string destination_name,string signal_name,shunt_signal_type_e data_type  = SHUNT_BIT,data_in_t data_in);
      bit     success;
      string  s_me;
      
      int     source_signals_db_index = -1;
      int     source_SrcDst_db_index = -1;
      longint source_signal_id;
      int     index_payloads;
      int     number_payloads;
      
      int     destination_SrcDst_db_index =-1;

      data_in_t data;
      
      //
      s_me = "fringe_api_put";
      success =1;
      
      destination_SrcDst_db_index = get_index_by_name_SrcDsts_db(destination_name);
      //
      source_signal_id            = shunt_dpi_hash({who_iam(),".",signal_name});
      source_SrcDst_db_index      = get_index_by_name_SrcDsts_db(who_iam());
      source_signals_db_index     = get_index_by_signal_id_signals_db(source_signal_id);
      
      index_payloads              = signals_db[source_signals_db_index].index_payloads;
      number_payloads             = signals_db[source_signals_db_index].number_payloads;
      if (signals_db[source_signals_db_index].signal_port_type != FRNG_PORT_INPUT) begin  
	 if (source_signal_id<0 &&  source_SrcDst_db_index<0 && index_payloads <0 && number_payloads<0) success =0;
	 if (signals_db[source_signals_db_index].signal_valid != FRNG_SIGNAL_IDLE) success =0;
	 if (SrcDsts_db[destination_SrcDst_db_index].socket_id <0)                 success =0;
	 if(success) begin
	    data = data_in;
	    for(int i=0;i<number_payloads;i++) begin
	       /* verilator lint_off BLKSEQ */
	       /* verilator lint_off WIDTH */
	       if(data_type == SHUNT_BIT)   signals_db_payloads[index_payloads+i].data_bit   = data.data_bit[N_OF_BITS_PER_PAYLOAD-1:0];
	       if(data_type == SHUNT_LOGIC) signals_db_payloads[index_payloads+i].data_logic = data.data_logic[N_OF_BITS_PER_PAYLOAD-1:0];
	       if(data_type == SHUNT_REG)   signals_db_payloads[index_payloads+i].data_logic = data.data_logic[N_OF_BITS_PER_PAYLOAD-1:0];
	       /* verilator lint_on WIDTH */ 
	       /* verilator lint_on BLKSEQ */
	       data.data_bit   = data.data_bit   >> N_OF_BITS_PER_PAYLOAD;
	       data.data_logic = data.data_logic >> N_OF_BITS_PER_PAYLOAD;
	    end // for (int i=0;i<number_payloads;i++)
	    
	    
	    if (success) signals_db[source_signals_db_index].signal_valid = FRNG_SIGNAL_VALID_PUT;
	    //TODO else         signals_db[source_signals_db_index].signal_valid = FRNG_SIGNAL_ERROR_PUT;
	    if (success) signals_db[source_signals_db_index].SrcDst_call_id = SrcDsts_db[destination_SrcDst_db_index].SrcDst_id;
	    if (success) SrcDsts_db[source_SrcDst_db_index].signal_status = FRNG_SIGNAL_VALID_PUT;
	    if (signals_db[source_signals_db_index].signal_port_type == FRNG_PORT_NA)signals_db[source_signals_db_index].signal_port_type = FRNG_PORT_OUTPUT;
	 end // if (success)
      end // if (signals_db[source_signals_db_index].signal_port_type != FRNG_PORT_INPUT)
      else begin
	 $display(" ERROR: %s %s signal_port_type should be FRNG_PORT_OUTPUT",i_am,s_me);
	 success = 0;
      end // else: !if(success)
      
      //TODO else         SrcDsts_db[source_SrcDst_db_index].signal_status = FRNG_SIGNAL_ERROR_PUT;
    
      return success;
      
   endfunction : fringe_api_put
   
   /*
    Function:   fringe_api_get
    PnP "play" function recieves a signal <signal name> , from a source <source_name> to the specified data output <data>
    Parameters: 
    string source_name - data source (from)   
    string signal_name - data source signal name 
    data_in_t data     - data output
    Returns: success bit 1-ok , 0- ERROR 
    */
   function automatic bit  fringe_api_get (string source_name,string signal_name,inout data_in_t data);
      bit     success;
      string  s_me;
      longint source_signal_id;
      int     source_signals_db_index;
      int     source_SrcDst_db_index;
      int     signals_db_index_payload;
      int     number_payloads;
      data_in_t	  data_;
                  
      s_me = "fringe_api_get()";
      data_.data_bit   = 0;
      data_.data_logic = 0;
      //
      success =1;
      //
      source_signal_id            = shunt_dpi_hash({source_name,".",signal_name});
      source_SrcDst_db_index      = get_index_by_name_SrcDsts_db(source_name);
      source_signals_db_index     = get_index_by_signal_id_signals_db(source_signal_id);
      signals_db_index_payload    = signals_db[source_signals_db_index].index_payloads;
      number_payloads             = signals_db[source_signals_db_index].number_payloads;
      
      //$display("%s  %s source_signal_id=%0h",i_am,s_me,source_signal_id);
      //$display("%s  %s source_SrcDst_db_index=%0d",i_am,s_me,source_SrcDst_db_index);
      //$display("%s  %s source_signals_db_index=%0d",i_am,s_me,source_signals_db_index);
      //$display("%s  %s signals_db_index_payload=%0d",i_am,s_me,signals_db_index_payload);
      //$display("%s  %s number_payloads=%0d",i_am,s_me,number_payloads);
      
      if (source_signal_id<0 && source_SrcDst_db_index<0 && signals_db_index_payload <0 && number_payloads<0) success =0;
      if (signals_db[source_signals_db_index].signal_valid != FRNG_SIGNAL_VALID_GET)  success =0;
      //
      if (success) begin
	 for(int i=0;i<number_payloads;i++) begin
	    //$display("%s  %s signals_db_payloads[%0d]=%h",i_am,s_me,signals_db_index_payload+i,signals_db_payloads[signals_db_index_payload+i].data_bit);
	    data_.data_bit   = data_.data_bit    >> N_OF_BITS_PER_PAYLOAD;
	    data_.data_logic = data_.data_logic  >> N_OF_BITS_PER_PAYLOAD;
	    //$display("%s  %s shift data_.data_bit= %h ,signal_db=%h",i_am,s_me,data_.data_bit,signals_db_payloads[signals_db_index_payload+i].data_bit);
	    data_.data_bit[MAX_N_OF_BITS_PER_SIGNAL-1:MAX_N_OF_BITS_PER_SIGNAL-N_OF_BITS_PER_PAYLOAD] = signals_db_payloads[signals_db_index_payload+i].data_bit;
	    //$display("%s  %s data_.data_bit= %h ,signal_db=%h",i_am,s_me,data_.data_bit,signals_db_payloads[signals_db_index_payload+i].data_bit);
	 end // for (int i=signals_db_index_payload;i<signals_db_index_payload+number_payloads;i++)
	 signals_db[source_signals_db_index].signal_valid = FRNG_SIGNAL_IDLE;
	 SrcDsts_db[source_SrcDst_db_index].signal_status = FRNG_SIGNAL_IDLE;
	 data= data_;
      end // if (success && signals_db[source_signals_db_index].signal_valid == FRNG_SIGNAL_VALID_GET)
      //$display("%s  %s output data.data_bit= %0h(%0h)",i_am,s_me,data.data_bit,data_.data_bit);
      return success;
      
endfunction : fringe_api_get
         
   
   /*
    Function:  fringe_signal_db_get 
    PnP "play" 
    Parameters:
    Returns: put_get_status_t put_out - new put_status; put_get_status_t 
    success=0 Plug-N-Play registration  ERROR 
    */
   function automatic put_get_status_t fringe_signal_db_get (int SrcDst_db_index_in,put_get_status_t get_in);
      put_get_status_t    get_out;
      string s_me; 
      int    signals_db_index;
      bit    success;
      int no_success_cnt_;
      //
      
      s_me = "fringe_signal_db_get";
      get_out = get_in;
      success =0;
      no_success_cnt_ =-1;
      //
      if (SrcDsts_db[SrcDst_db_index_in].signal_status == FRNG_SIGNAL_IDLE &&
	  SrcDsts_db[SrcDst_db_index_in].socket_id >=0 &&
	  __SrcDsts_name_db[SrcDst_db_index_in] != who_iam() 
	  ) begin
	 no_success_cnt_ =0;
	 signals_db_index = get_index_by_SrcDst_parent_id_signal_db(SrcDsts_db[SrcDst_db_index_in].SrcDst_id);
	 for (int j=signals_db_index;j< signals_db_index+SrcDsts_db[SrcDst_db_index_in].n_signals;j++) begin
	    if(signals_db[j].signal_valid != FRNG_SIGNAL_IDLE) no_success_cnt_++;
	 end
      	 if(no_success_cnt_  >0  ) SrcDsts_db[SrcDst_db_index_in].signal_status = FRNG_SIGNAL_VALID_GET;
	 if(no_success_cnt_ == 0 ) begin 
	    success = fringe_get(SrcDst_db_index_in);
	    get_out.success = success;
	    get_out.signal_index =SrcDst_db_index_in ; 
	    get_out.event_cnt = get_time();
	 end
      end // if (SrcDsts_db[SrcDst_db_index_in].signal_status == FRNG_SIGNAL_IDLE)
       
      return get_out;
   endfunction :  fringe_signal_db_get

   //About: TCP communication
   /*
    Function:  fringe_signal_db_put 
    PnP "play" 
    Parameters:
    Returns: put_get_status_t put_out - new put_status; put_get_status_t 
    success=0 Plug-N-Play registration  ERROR 
    */
   function automatic put_get_status_t fringe_signal_db_put (int SrcDst_db_index_in,put_get_status_t put_in);
      bit    success;
      put_get_status_t    put_out;
      string s_me; 
      int    signals_db_index;
      //
      s_me = "fringe_signal_db_put";
      success =0;
      put_out = put_in;
      //
      if (SrcDsts_db[SrcDst_db_index_in].signal_status == FRNG_SIGNAL_VALID_PUT &&
	  __SrcDsts_name_db[SrcDst_db_index_in] == who_iam() 
	  ) begin
	 int no_success_cnt_;
	 no_success_cnt_ =0;
	 signals_db_index = get_index_by_SrcDst_parent_id_signal_db(SrcDsts_db[SrcDst_db_index_in].SrcDst_id);
	 for (int j=signals_db_index;j<= signals_db_index+SrcDsts_db[SrcDst_db_index_in].n_signals;j++) begin
	    if(signals_db[j].signal_valid == FRNG_SIGNAL_VALID_PUT) begin
	       success = fringe_put(SrcDst_db_index_in,j);
	       //
	       put_out.success = success;
	       put_out.signal_index = j; 
	       put_out.event_cnt = get_time();
	       //
	       if(success) signals_db[j].signal_valid = FRNG_SIGNAL_IDLE;
	       else no_success_cnt_++;
	    end
	 end // for (int j=signals_db_index;j<= signals_db_index+SrcDsts_db[SrcDst_db_index_in].n_signals;j++)
	 if(no_success_cnt_ == 0) SrcDsts_db[SrcDst_db_index_in].signal_status = FRNG_SIGNAL_IDLE;  
      end // if (SrcDsts_db[SrcDst_db_index_in].signal_status == FRNG_SIGNAL_VALID_PUT)
      
      return put_out;
   endfunction :  fringe_signal_db_put


   
   
    /*
    Function:  fringe_put();
    PnP "play" 
    Parameters:
    Returns: bit success - success=1 Plug-N-Play registration  OK
    success=0 Plug-N-Play registration  ERROR 
    */
   function automatic bit fringe_put (int SrcDst_db_index_in,int signals_db_index_in);

      cs_header_t h_;
      //
      string 	  s_me;
      bit 	  success;
      int 	  signals_db_index;
      int 	  SrcDst_db_index;
      int 	  index_payload;
      signal_db_data_in_t	  data_;
      int 	  Result=-1;
      int 	  call_id_index =-1;
      
      //
      s_me = "fringe_tcp_put()";
      success =1;
      
      if(signals_db_index_in<0 && SrcDst_db_index_in <0) success =0;
      if (success) begin
	 signals_db_index = signals_db_index_in;
	 SrcDst_db_index  = SrcDst_db_index_in;
	 call_id_index = get_index_by_id_SrcDsts_db(signals_db[signals_db_index].SrcDst_call_id);
	 //
	 index_payload = signals_db[signals_db_index].index_payloads;
	
	 
	 //if(!print_SrcDsts_db(SrcDst_db_index)) $display("ERROR: %s %s print_SrcDsts_db(SrcDst_db_index)",i_am,s_me);
	 
	 //header tenure 
	 h_.trnx_type  = shunt_dpi_hash("FRNG_PUT");
	 h_.trnx_id    = signals_db[signals_db_index].signal_id;
	 h_.data_type  = shunt_dpi_hash(signals_db[signals_db_index].signal_type.name());
	 h_.n_payloads = signals_db[signals_db_index].number_payloads;
	 
`ifdef  SHUNT_VERILATOR_DPI_H 
	 h_.data_type  =  shunt_dpi_hash("SHUNT_LONGINT");
`endif 
	 //data tenure 
	 index_payload = signals_db[signals_db_index].index_payloads;
	 
	  //if(!print_signals_db(signals_db_index))$display("ERROR: %s %s print_signals_db(signals_db_index)",i_am,s_me);
	 
	
	 
	 case (signals_db[signals_db_index].signal_type) 
	   SHUNT_BIT: begin
	       //$display(" SHUNT_BIT : %s %s signals_db[%0d].signal_type = (%s) (%0d) ",i_am,s_me,signals_db_index,signals_db[signals_db_index].signal_type.name(),signals_db[signals_db_index].signal_type);
`ifdef  SHUNT_VERILATOR_DPI_H
	      //print_shunt_header(h_,"fringe_put h_");
	      if(shunt_dpi_send_header(SrcDsts_db[call_id_index].socket_id,h_)<=0) success = 0;
	      for(int i=0;i<h_.n_payloads;i++) begin
		 //$display("%s: %s SrcDst_db_index =%0d signals_db_index=%0d  SrcDst_name(source)=%s, signal_name=%s signal=%0d",i_am,s_me, SrcDst_db_index,signals_db_index,__SrcDsts_name_db [SrcDst_db_index], __signals_db_name[signals_db_index],signals_db_payloads[index_payload+i].data_bit);
		 //$display("%s shunt_dpi_send_long signals_db_payloads[%0d].data_bit ",s_me,index_payload+i,signals_db_payloads[index_payload+i].data_bit);
		 Result = shunt_dpi_send_long(SrcDsts_db[call_id_index].socket_id,signals_db_payloads[index_payload+i].data_bit);
	      end
`endif	      
	      
`ifndef  SHUNT_VERILATOR_DPI_H
	      Result = shunt_dpi_hs_send_bitN (SrcDsts_db[SrcDst_db_index].socket_id,h_,signals_db_payloads[index_payload].data_bit);
`endif
	   end // case: SHUNT_BIT
	 	 
	   SHUNT_LOGIC: begin
	       $display("SHUNT_LOGIC : %s %s signals_db[%0d].signal_type = (%s) (%0d) ",i_am,s_me,signals_db_index,signals_db[signals_db_index].signal_type.name(),signals_db[signals_db_index].signal_type);
	      $display("\n 6 %s ERROR: %s %s is not supported",s_me,i_am,signals_db[signals_db_index].signal_type.name());
`ifdef  SHUNT_VERILATOR_DPI_H
	      if(shunt_dpi_send_header(SrcDsts_db[SrcDst_db_index].socket_id,h_)<=0) success=0;
	      for(int i=0;i<h_.n_payloads;i++)
		Result = shunt_dpi_send_long(SrcDsts_db[SrcDst_db_index].socket_id,signals_db_payloads[index_payload+i].data_logic);
`endif
`ifndef  SHUNT_VERILATOR_DPI_H
	      Result = shunt_dpi_hs_send_regN (SrcDsts_db[SrcDst_db_index].socket_id,h_,signals_db_payloads[index_payload].data_logic);  
`endif
	   end // case: SHUNT_LOGIC,SHUNT_REG
	   	   
	   default: begin
	      success=0;
	      $display("\n %s ERROR: %s %s is not supported",s_me,i_am,signals_db[signals_db_index].signal_type.name());
	   end
	   
	 endcase // case (signals_db[signals_db_index].signal_type)
	 	 
	 if  (Result<0) success=0;
      end // if (seccess)
      return success;      
   endfunction : fringe_put
      

 /*
    Function:  fringe_get
    PnP "play" 
    Parameters:
    Returns: bit success - success=1 Plug-N-Play registration  OK
    success=0 Plug-N-Play registration  ERROR 
    */
   function automatic bit fringe_get (int SrcDst_db_index);
      
      cs_header_t h_;
      //
      bit success;
      int socket_status;
      string s_me;
      int 	  Result=-1;
      int 	  socket;
      shunt_signal_type_e     data_type;
      int 	  signals_db_index_payload;
      int 	  source_signals_db_index;
      put_get_status_t    get_out;
      //
      string 	  me = "";
      
      fringe_SrcDst_status_e temp_status;
 	   
      //
      s_me = "fringe_get()";
      success=1;
      Result = -1;
      h_ = '{default:'0};
      
      socket =SrcDsts_db[SrcDst_db_index].socket_id;
      socket_status = shunt_dpi_get_status_socket(socket,0);
      
      
`ifdef  SHUNT_VERILATOR_DPI_H
     
      if(socket_status==1) begin
	 //$display("Start %s %s SrcDst_db_index(%0d) socket_status(%0d)=%0d",s_me,who_iam(),SrcDst_db_index,socket,socket_status); 
	 if(shunt_dpi_recv_header(socket,h_)<=0) success =0;
      end
      else success =0;
      
      if(success) begin
	 //$display(" %s %s Result=%0d (success=%0d) socket=%0d ",s_me,who_iam(),Result,success,socket);
	 
         //print DEBUG
	 temp_status =get_mystatus();
	 //$display(" %s %s Result=%0d get_mystatus()=%s __SrcDsts_name_db[%0d]= %s socket=%0d",s_me,who_iam(),Result,temp_status.name(),SrcDst_db_index,__SrcDsts_name_db[SrcDst_db_index],socket);
	 //print_put_get_status(get_out,"get_out");
	 //print_shunt_header(h_,"h_");
	 source_signals_db_index  = get_index_by_signal_id_signals_db(h_.trnx_id);
	 if (source_signals_db_index<0) success =0;
	 if(h_.trnx_type  != shunt_dpi_hash("FRNG_PUT")) success =0;
	 //
	 data_type                = signals_db[source_signals_db_index].signal_type;
	 signals_db_index_payload = signals_db[source_signals_db_index].index_payloads;
	 //$display(" %s %s __SrcDsts_name_db[%0d]= %s __signals_db_SrcDst_name[%0d]=%s  socket=%0d ",s_me,who_iam(),SrcDst_db_index,__SrcDsts_name_db[SrcDst_db_index],source_signals_db_index,__signals_db_name[source_signals_db_index],socket);
	 for(int i=signals_db_index_payload;i<signals_db_index_payload+h_.n_payloads;i++) begin
	    //Result = -1;
	    /* verilator lint_off IGNOREDRETURN */
	    
	    if(data_type == SHUNT_BIT)   shunt_dpi_recv_long(socket,signals_db_payloads[i].data_bit);
	    if(data_type == SHUNT_LOGIC) shunt_dpi_recv_long(socket,signals_db_payloads[i].data_logic);
	    if(data_type == SHUNT_REG)   shunt_dpi_recv_long(socket,signals_db_payloads[i].data_logic);
	    /* verilator lint_on IGNOREDRETURN */
	    //if (Result>0) 
	    signals_db[source_signals_db_index].signal_valid = FRNG_SIGNAL_VALID_GET;//??????? TODO
	    //$display(" %s %s __SrcDsts_name_db[%0d]= %s __signals_db_SrcDst_name[%0d]=%s  socket=%0d signal=%0d",s_me,who_iam(),SrcDst_db_index,__SrcDsts_name_db[SrcDst_db_index],source_signals_db_index,__signals_db_name[source_signals_db_index],socket,signals_db_payloads[i].data_bit);
	 end // for (i=signals_db_index_payload;i<signals_db_index_payload+signals_db[source_signals_db_index].signal_size;i++)
	 
`endif //  `ifdef SHUNT_VERILATOR_DPI_H
	 
	 
`ifndef  SHUNT_VERILATOR_DPI_H
	 //TODO
`endif //  `ifndef SHUNT_VERILATOR_DPI_H
      end // if (success)
      if(success ) begin
	 //if(!print_SrcDsts_db(SrcDst_db_index))         $display("ERROR: %s %s print_SrcDsts_db(SrcDst_db_index)",i_am,s_me);
	 //if(!print_signals_db(source_signals_db_index)) $display("ERROR: %s %s print_signals_db(source_signals_db_index)",i_am,s_me);
	 /* -----\/----- EXCLUDED -----\/-----
	  for(int i=signals_db_index_payload;i<signals_db_index_payload+signals_db[source_signals_db_index].number_payloads;i++) begin
	  if(data_type == SHUNT_BIT)   
	  $display("%s signals_db_payloads[%0d].%s=%0h",s_me,i,data_type.name(),signals_db_payloads[i].data_bit);
	 end
	  -----/\----- EXCLUDED -----/\----- */
	 //print_put_get_status(get_out,"get_out");
      end // if (success )
      
      return success;
   endfunction : fringe_get
   
  
   

endinterface : shunt_fringe_if

/* verilator lint_on UNUSED */
/* verilator lint_on UNDRIVEN */
/* verilator lint_on UNOPTFLAT */
`endif //  `ifndef SHUNT_FRINGE_IF

