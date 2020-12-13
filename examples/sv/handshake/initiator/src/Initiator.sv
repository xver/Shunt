/*
============================================================================
 File        : Initiator.sv
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
 Licensed under the MIT License.
 See LICENSE file in the project root for full license information.
 Description : TCP/IP SystemVerilog SHUNT
 SystemVerilog initiator/target handshake examle  -Initiator(server)
 ============================================================================
 */

`include "../../includes/cs_common.svh"

module automatic Initiator;

   import shunt_dpi_pkg::*;
   import shunt_hs_pkg::*;

   int Socket;
   cs_header_t      h_trnx_exp;
   cs_data_header_t h_data_exp;
   cs_header_t      h_trnx_act;
   cs_data_header_t h_data_act;



   initial
     begin
    int Pass;
    string Status;
    string Test_name;

    Pass   = 1;
    Socket = 0;

    $display("Initiator: START");

    Test_name = "\tinit_initiator";

    Socket = init_initiator(`MY_PORT);
    if (!Socket) Pass=0;
    $display("\tInitiator: socket=%0d",Socket);
    print_status(Test_name,Pass);


    Test_name = "\tint_loopback";
    Pass=int_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\tint vector loopback";
    Pass=int_loopback_test(Socket,9);
    print_status(Test_name,Pass);

    Test_name = "\tshort_loopback";
    Pass=short_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\tshort vector loopback";
    Pass=short_loopback_test(Socket,11);
    print_status(Test_name,Pass);

    Test_name = "\tlong_loopback";
    Pass=long_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\tint vector loopback";
    Pass=long_loopback_test(Socket,7);
    print_status(Test_name,Pass);

    Test_name = "\tbyte loopback";
    Pass=byte_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\tbyte vector loopback";
    Pass=byte_loopback_test(Socket,15);
    print_status(Test_name,Pass);

    Test_name = "\tbit loopback";
    Pass=bit_loopback_test(Socket);
    print_status(Test_name,Pass);

    Test_name = "\tinteger loopback";
    Pass=integer_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\tinteger vector loopback";
    Pass=integer_loopback_test(Socket,23);
    print_status(Test_name,Pass);

    Test_name = "\treg loopback";
    Pass=reg_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\tlogic loopback";
    Pass=logic_loopback_test(Socket);
    print_status(Test_name,Pass);

        Test_name = "\treal_loopback";
    Pass=real_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\treal vector loopback";
    Pass=real_loopback_test(Socket,11);

        Test_name = "\tshortreal_loopback";
    Pass=shortreal_loopback_test(Socket);
    print_status(Test_name,Pass);
    Test_name = "\tshortreal vector loopback";
    Pass=shortreal_loopback_test(Socket,11);

        Test_name = "\tstring_loopback";
    Pass=string_loopback_test(Socket);
    print_status(Test_name,Pass);

    // *****************END**********************************
    Test_name = "Initiator";
    print_status(Test_name,Pass);

     end


   function int init_initiator(int portno);
      begin
     int socket_id;
     socket_id=0;
     socket_id = shunt_dpi_initiator_init(portno);
     return socket_id;
      end
   endfunction : init_initiator

   function int byte_loopback_test(int socket_id,int n_payloads=1);
      begin
     int success;
         byte Byte_exp[];
     byte Byte_act[];
         string Test_name = "initiator byte_loopback_test";
     Byte_exp = new[n_payloads];
     success =1;
     for(int i=0;i<n_payloads;i++) Byte_exp[i] = "A"+i;
     Byte_exp[n_payloads] = "\0";

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_BYTE");
     h_trnx_exp.n_payloads = n_payloads;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_byte  (socket_id,h_trnx_exp,Byte_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     Byte_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_byte(socket_id,h_trnx_act,Byte_act)<= 0) success = 0;
     if (success == 0 )  $display("\nByte loopback fail recv");

     for(int i=0;i<n_payloads;i++)  if (Byte_exp[i] != Byte_act[i])success=0;
         return  success;
      end
   endfunction : byte_loopback_test


   function int int_loopback_test(int socket_id,int n_payloads=1);
      begin
     int success;
         int Int_exp[];
     int Int_act[];
         string Test_name = "initiator int_loopback_test";
     Int_exp = new[n_payloads];
     success =1;
     for(int i=0;i<n_payloads;i++) Int_exp[i] = 100 +i;
     Int_exp[n_payloads] = "\0";

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_INT");
     h_trnx_exp.n_payloads = n_payloads;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_int  (socket_id,h_trnx_exp,Int_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     Int_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_int(socket_id,h_trnx_act,Int_act)<= 0) success = 0;
     if (success == 0 )  $display("\nInt loopback fail recv");

     for(int i=0;i<n_payloads;i++)  if (Int_exp[i] != Int_act[i])success=0;
         return  success;

      end
   endfunction : int_loopback_test

   function int short_loopback_test(int socket_id,int n_payloads=1);
      begin
     int success;
         shortint Short_exp[];
     shortint Short_act[];
         string Test_name = "initiator short_loopback_test";
     Short_exp = new[n_payloads];
     success =1;
     for(int i=0;i<n_payloads;i++) Short_exp[i] = 300 +i;
     Short_exp[n_payloads] = "\0";

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_SHORTINT");
     h_trnx_exp.n_payloads = n_payloads;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_short  (socket_id,h_trnx_exp,Short_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     Short_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_short(socket_id,h_trnx_act,Short_act)<= 0) success = 0;
     if (success == 0 )  $display("\nInt loopback fail recv");

     for(int i=0;i<n_payloads;i++)  if (Short_exp[i] != Short_act[i])success=0;
         return  success;

      end
   endfunction : short_loopback_test

   function int string_loopback_test(int socket_id);
      begin
     int success;
     int i;
         string String_exp;
     string String_act;
        string Test_name = "string_loopback_test";
     String_exp = `STRING_MESSAGE;
     String_act = `STRING_MESSAGE1;
     success =1;
     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_STRING");
     h_trnx_exp.n_payloads = String_exp.len();

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_string  (socket_id,h_trnx_exp,String_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     String_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_string(socket_id,h_trnx_act,String_act)<= 0) success = 0;

     foreach(String_exp[i]) if(String_act[i] != String_exp[i]) success =0;
     return  success;
      end
   endfunction : string_loopback_test

   function int long_loopback_test(int socket_id,int n_payloads=1);
      begin
     int success;
         longint Long_exp[];
     longint Long_act[];
         string Test_name = "initiator long_loopback_test";
     Long_exp = new[n_payloads];
     success =1;
     for(int i=0;i<n_payloads;i++) Long_exp[i] = 1000 +i;
     Long_exp[n_payloads] = "\0";

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_LONGINT");
     h_trnx_exp.n_payloads = n_payloads;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_long  (socket_id,h_trnx_exp,Long_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     Long_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_long(socket_id,h_trnx_act,Long_act)<= 0) success = 0;
     if (success == 0 )  $display("\nInt loopback fail recv");

     for(int i=0;i<n_payloads;i++)  if (Long_exp[i] != Long_act[i])success=0;
         return  success;
      end
   endfunction : long_loopback_test

   function int real_loopback_test(int socket_id,int n_payloads=1);
      begin
     int success;
         real Real_exp[];
     real Real_act[];
         string Test_name = "initiator real_loopback_test";
     Real_exp = new[n_payloads];
     success =1;
     for(int i=0;i<n_payloads;i++) Real_exp[i] = 300.123+i;
     Real_exp[n_payloads] = "\0";

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_REAL");
     h_trnx_exp.n_payloads = n_payloads;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_real  (socket_id,h_trnx_exp,Real_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     Real_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_real(socket_id,h_trnx_act,Real_act)<= 0) success = 0;

     for(int i=0;i<n_payloads;i++)  if (Real_exp[i] != Real_act[i])success=0;
         return  success;
      end
   endfunction : real_loopback_test

   function int shortreal_loopback_test(int socket_id,int n_payloads=1);
      begin
     int success;
         shortreal Shortreal_exp[];
     shortreal Shortreal_act[];
         string Test_name = "initiator shortreal_loopback_test";
     Shortreal_exp = new[n_payloads];
     success =1;
     for(int i=0;i<n_payloads;i++) Shortreal_exp[i] = 300.123+i;
     Shortreal_exp[n_payloads] = "\0";

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_SHORTREAL");
     h_trnx_exp.n_payloads = n_payloads;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_shortreal  (socket_id,h_trnx_exp,Shortreal_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     Shortreal_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_shortreal(socket_id,h_trnx_act,Shortreal_act)<= 0) success = 0;

     foreach (Shortreal_exp[i])  begin
        real zero_ = 0;
        zero_ = Shortreal_exp[i] - Shortreal_act[i];
        if (zero_ < 0)  zero_ = Shortreal_act[i] - Shortreal_exp[i];
        if (zero_ > 0.0001) success=0;
     end

         return  success;
      end
   endfunction : shortreal_loopback_test

   function int intV_loopback_test(int socket_id);
      begin
     int success;
     int i;
         int IntV_exp[`V_SIZE];
     int IntV_act[`V_SIZE];

     success =1;

     foreach(IntV_exp[i]) IntV_exp[i] = 100+(i+1);
     foreach(IntV_act[i]) IntV_act[i] = 300+(i+1);
     if(!shunt_dpi_send_intV(socket_id,`V_SIZE,IntV_exp)) success =0;
     if(!shunt_dpi_recv_intV(socket_id,`V_SIZE,IntV_act)) success =0;
     foreach(IntV_exp[i]) if(IntV_act[i] != IntV_exp[i]) success =0;
     return  success;
      end
   endfunction: intV_loopback_test

   function int realV_loopback_test(int socket_id);
      begin
     int success;
     int i;
         real RealV_exp[`V_SIZE];
     real RealV_act[`V_SIZE];

     success =1;

     foreach(RealV_exp[i]) RealV_exp[i] = 100+(i+1);
     foreach(RealV_act[i]) RealV_act[i] = 300+(i+1);
     if(!shunt_dpi_send_realV(socket_id,`V_SIZE,RealV_exp))  success =0;
     if(!shunt_dpi_recv_realV(socket_id,`V_SIZE,RealV_act))  success =0;
     foreach(RealV_exp[i]) if(RealV_act[i] != RealV_exp[i]) success =0;
     return  success;
      end
   endfunction : realV_loopback_test




   function int   byteA_loopback_test(int socket_id,int n_payloads=1);
      int   success;
      byte  Byte_exp[][];
      byte  Byte_act[][];
      string    Test_name = "initiator byteA_loopback_test";
      success =1;

      //set up data
      Byte_exp = new[n_payloads];
      foreach(Byte_exp[i]) Byte_exp[i] = new[n_payloads];
      foreach(Byte_exp[i]) foreach(Byte_exp[j]) Byte_exp[i][j]= "A"+(i*10)+j;

      //set up trnx header
      h_trnx_exp.trnx_type = $urandom;
      h_trnx_exp.trnx_id   = $urandom;
      h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_A_STRUCTURE");
      h_trnx_exp.n_payloads = n_payloads;
      //set up data header
      h_data_exp.data_type = shunt_dpi_hash("SHUNT_BYTE");
      h_data_exp.trnx_payload_sizes = new[n_payloads];
      foreach(h_data_exp.trnx_payload_sizes[i]) h_data_exp.trnx_payload_sizes[i] = n_payloads;

      //send
      //send trnx header
      if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send trnx header ");
      //send data header
      if (shunt_dpi_send_data_header(socket_id,h_trnx_exp,h_data_exp.data_type,h_data_exp.trnx_payload_sizes)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send data header");
      //send data
      if (shunt_hs_send_byteA(socket_id,h_trnx_exp,h_data_exp,Byte_exp)<=0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send data");

      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail rcv trnx header ");
      //recv data header
      h_data_act.trnx_payload_sizes = new[h_trnx_act.n_payloads];
      for(int i=0;i<h_trnx_act.n_payloads;i++) h_data_act.trnx_payload_sizes[i]=0;
      if(shunt_dpi_recv_data_header(socket_id,h_trnx_act,h_data_act.data_type,h_data_act.trnx_payload_sizes)<=0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail rcv data header ");
      //recv data
      Byte_act   = new[h_trnx_act.n_payloads];
      foreach(Byte_act[i]) Byte_act[i] = new[h_data_act.trnx_payload_sizes[i]];
      if(shunt_hs_recv_byteA  (socket_id,h_trnx_act,h_data_act,Byte_act)<=0) $display("%s recv_byteA TEST FAIL",Test_name);

      //comp
      foreach(Byte_act[i]) foreach(Byte_act[j]) if(Byte_act[i][j] !=Byte_exp[i][j]) success = 0;
      if (success == 0 )  $display("\ninitiator: fail comp data header ");
      return  success;

   endfunction :byteA_loopback_test

   function int   intA_loopback_test(int socket_id,int n_payloads=1);
      int   success;
      int   Int_exp[][];
      int   Int_act[][];
      string    Test_name = "initiator intA_loopback_test";
      success =1;

      //set up data
      Int_exp = new[n_payloads];
      foreach(Int_exp[i]) Int_exp[i] = new[n_payloads];
      foreach(Int_exp[i]) foreach(Int_exp[j]) Int_exp[i][j]= 0+(i*100)+10*j;

      //set up trnx header
      h_trnx_exp.trnx_type = $urandom;
      h_trnx_exp.trnx_id   = $urandom;
      h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_A_STRUCTURE");
      h_trnx_exp.n_payloads = n_payloads;
      //set up data header
      h_data_exp.data_type = shunt_dpi_hash("SHUNT_INT");
      h_data_exp.trnx_payload_sizes = new[n_payloads];
      foreach(h_data_exp.trnx_payload_sizes[i]) h_data_exp.trnx_payload_sizes[i] = n_payloads;

      //send
      //send trnx header
      if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send trnx header ");
      //send data header
      if (shunt_dpi_send_data_header(socket_id,h_trnx_exp,h_data_exp.data_type,h_data_exp.trnx_payload_sizes)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send data header");
      //send data
      if (shunt_hs_send_intA(socket_id,h_trnx_exp,h_data_exp,Int_exp)<=0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send data");

      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail rcv trnx header ");
      //recv data header
      h_data_act.trnx_payload_sizes = new[h_trnx_act.n_payloads];
      for(int i=0;i<h_trnx_act.n_payloads;i++) h_data_act.trnx_payload_sizes[i]=0;
      if(shunt_dpi_recv_data_header(socket_id,h_trnx_act,h_data_act.data_type,h_data_act.trnx_payload_sizes)<=0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail rcv data header ");
      //recv data
      Int_act   = new[h_trnx_act.n_payloads];
      foreach(Int_act[i]) Int_act[i] = new[h_data_act.trnx_payload_sizes[i]];
      if(shunt_hs_recv_intA  (socket_id,h_trnx_act,h_data_act,Int_act)<=0) $display("%s recv_intA TEST FAIL",Test_name);

      //comp
      foreach(Int_act[i]) foreach(Int_act[j]) if(Int_act[i][j] !=Int_exp[i][j]) success = 0;
      if (success == 0 )  $display("\ninitiator: fail comp data header ");
      return  success;

   endfunction :intA_loopback_test

   function int   realA_loopback_test(int socket_id,int n_payloads=1);
      int   success;
      real  Real_exp[][];
      real  Real_act[][];
      string    Test_name = "initiator realA_loopback_test";
      success =1;

      //set up data
      Real_exp = new[n_payloads];
      foreach(Real_exp[i]) Real_exp[i] = new[n_payloads];
      foreach(Real_exp[i]) foreach(Real_exp[j]) Real_exp[i][j]= 12.123+(i*1000)+100*j;

      //set up trnx header
      h_trnx_exp.trnx_type = $urandom;
      h_trnx_exp.trnx_id   = $urandom;
      h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_A_STRUCTURE");
      h_trnx_exp.n_payloads = n_payloads;
      //set up data header
      h_data_exp.data_type = shunt_dpi_hash("SHUNT_REAL");
      h_data_exp.trnx_payload_sizes = new[n_payloads];
      foreach(h_data_exp.trnx_payload_sizes[i]) h_data_exp.trnx_payload_sizes[i] = n_payloads;

      //send
      //send trnx header
      if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send trnx header ");
      //send data header
      if (shunt_dpi_send_data_header(socket_id,h_trnx_exp,h_data_exp.data_type,h_data_exp.trnx_payload_sizes)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send data header");
      //send data
      if (shunt_hs_send_realA(socket_id,h_trnx_exp,h_data_exp,Real_exp)<=0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail send data");

      //recv
      if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail rcv trnx header ");
      //recv data header
      h_data_act.trnx_payload_sizes = new[h_trnx_act.n_payloads];
      for(int i=0;i<h_trnx_act.n_payloads;i++) h_data_act.trnx_payload_sizes[i]=0;
      if(shunt_dpi_recv_data_header(socket_id,h_trnx_act,h_data_act.data_type,h_data_act.trnx_payload_sizes)<=0) success = 0;
      if (success == 0 )  $display("\ninitiator: fail rcv data header ");
      //recv data
      Real_act   = new[h_trnx_act.n_payloads];
      foreach(Real_act[i]) Real_act[i] = new[h_data_act.trnx_payload_sizes[i]];
      if(shunt_hs_recv_realA  (socket_id,h_trnx_act,h_data_act,Real_act)<=0) $display("%s recv_realA TEST FAIL",Test_name);

      //comp
      foreach(Real_act[i]) foreach(Real_act[j]) if(Real_act[i][j] !=Real_exp[i][j]) success = 0;
      if (success == 0 )  $display("\ninitiator: fail comp data");
      return  success;

   endfunction :realA_loopback_test
   //


   function int reg_loopback_test(int socket_id,int n_payloads=1);
      begin
     localparam N = 133;//N 4*32 bit max

     int success;
     int i;
     reg [N-1:0] XReg_exp;
         reg [N-1:0] Reg_exp;
     reg [N-1:0] Reg_act;
     string    s_me = "reg_loopback_test";
     success =1;

     //data set
     XReg_exp = 'hx;
     Reg_exp =  {$urandom(),$urandom(),$urandom(),$urandom()}& XReg_exp;
     Reg_exp =   Reg_exp | {$urandom(),$urandom(),$urandom(),$urandom()};

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_REG");
     h_trnx_exp.n_payloads = N;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if(!shunt_dpi_hs_send_regN(socket_id,h_trnx_exp,Reg_exp))  success =0;

     //recv
     if (shunt_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
     if(!shunt_dpi_hs_recv_regN(socket_id,h_trnx_act,Reg_act))  success =0;
     //
     if(Reg_act !== Reg_exp) success =0;
     return  success;
      end
   endfunction : reg_loopback_test

   function int logic_loopback_test(int socket_id,int n_payloads=1);
      begin
     localparam N = 76;//N 4*32 bit max

     int success;
     int i;
     logic [N-1:0] XLogic_exp;
         logic [N-1:0] Logic_exp;
     logic [N-1:0] Logic_act;
     string    s_me = "logic_loopback_test";
     success =1;

     //data set
     XLogic_exp = 'hx;
     Logic_exp =  {$urandom(),$urandom(),$urandom(),$urandom()}& XLogic_exp;
     Logic_exp =   Logic_exp | {$urandom(),$urandom(),$urandom(),$urandom()};

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_REG");
     h_trnx_exp.n_payloads = N;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if(!shunt_dpi_hs_send_logicN(socket_id,h_trnx_exp,Logic_exp))  success =0;

     //recv
     if (shunt_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
     if(!shunt_dpi_hs_recv_logicN(socket_id,h_trnx_act,Logic_act))  success =0;
     //
     if(Logic_act !== Logic_exp) success =0;
     return  success;
      end
   endfunction : logic_loopback_test
   //
   function int bit_loopback_test(int socket_id,int n_payloads=1);
      begin
     localparam N = 133;//N 4*32 bit max

     int success;
     int i;
     bit [N-1:0] Bit_exp;
     bit [N-1:0] Bit_act;
     string    s_me = "bit_loopback_test";
     success =1;

     //data set
     Bit_exp =  {$urandom(),$urandom(),$urandom(),$urandom()};

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_BIT");
     h_trnx_exp.n_payloads = N;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if(!shunt_dpi_hs_send_bitN(socket_id,h_trnx_exp,Bit_exp))  success =0;

     //recv
     if (shunt_dpi_recv_header(socket_id,h_trnx_act)<= 0) success = 0;
     if(!shunt_dpi_hs_recv_bitN(socket_id,h_trnx_act,Bit_act))  success =0;
     //
     if(Bit_act !== Bit_exp) success =0;
     return  success;
      end
   endfunction : bit_loopback_test

 function int integer_loopback_test(int socket_id,int n_payloads=1);
      begin
     int success;
         integer Integer_exp[];
     integer Integer_act[];
         string Test_name = "initiator integer_loopback_test";
     Integer_exp = new[n_payloads];
     success =1;
     for(int i=0;i<n_payloads;i++) Integer_exp[i] = "A"+i;
     //data set

         foreach(Integer_exp[i]) begin
        integer X = 'hx;
        Integer_exp[i] =  $urandom()& X;
        Integer_exp[i] =  Integer_exp[i] | $urandom();
     end

     //set up header
     h_trnx_exp.trnx_type = $urandom;
     h_trnx_exp.trnx_id   = $urandom;
     h_trnx_exp.data_type = shunt_dpi_hash("SHUNT_INTEGER");
     h_trnx_exp.n_payloads = n_payloads;

     //send
     if (shunt_dpi_send_header(socket_id,h_trnx_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send header ");
     if (shunt_dpi_hs_send_integer  (socket_id,h_trnx_exp,Integer_exp)<= 0) success = 0;
     if (success == 0 )  $display("\ninitiator: fail send data");

     //recv
     if (shunt_dpi_recv_header (socket_id,h_trnx_act)<= 0) success = 0;
     Integer_act = new[h_trnx_act.n_payloads];
     if (shunt_dpi_hs_recv_integer(socket_id,h_trnx_act,Integer_act)<= 0) success = 0;
     if (success == 0 )  $display("\nInteger loopback fail recv");
     for(int i=0;i<n_payloads;i++)  if (Integer_exp[i] !== Integer_act[i])success=0;
         return  success;
      end
 endfunction : integer_loopback_test

//
   function void print_status(string Test_name,int Status_int);
      begin
     string Status;
     if (!Status_int) Status = "FAIL";
     else  Status = "PASS";
     $display("%s TEST %s",Test_name,Status);
      end
   endfunction : print_status

endmodule : Initiator

