
/*
============================================================================
 File        : apiC_Initiator.c
 Author      : Victor Besyakov
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description :   TCP/IP SystemVerilog SHUNT
               An example of API functions-Initiator(server)
*/
#include "shunt_user_api.h"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\napiC_Initiator start");
  int  socket;
  int  port;
  int success = 1;
  const int n=17;
  port =       MY_PORT;
  char* msg = "";
  //
  cs_header      h_trnx_exp;
  cs_header      h_trnx_act;
  //

  socket= shunt_prim_init_initiator(port);

  if (socket<0) {
    printf("apiC_Initiator::FATAL ERROR");
    success = 0;
  }

  printf("\napiC_Initiator::socket=%d", socket);

  if (success>0) {
    puts("\napiC_Initiator start: Echo loopback initiator test start");
    SHUNT_INSTR_HASH_INDEX_DEFINE;

    //Int test
    //header init

    //data init
    success =1;
    msg = "\n\nInitiator: Int Tests";
    puts(msg);



    // INTV Test
    success =1;
    //Int Vector
    int IntVexp[n];
    int* IntVact;
    msg = "Initiator: Int Vector Test ";
    for (int i = 0; i < n; i++) {
      IntVexp[i] = i+1 ;//rand();
      //printf("\ninitiator IntVexp[%0d]=%d",i,IntVexp[i]);
    }

    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = shunt_cs_data_type_hash(SHUNT_INT,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
    h_trnx_exp.n_payloads = n;

    //send
    if (shunt_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ninitiator: fail send header ");
    if (shunt_api_send  (socket,&h_trnx_exp,IntVexp)<= 0) success = 0;
    if (success == 0 )  printf("\ninitiator: fail send data");

    //recv
    if (shunt_cs_recv_header (socket,&h_trnx_act)<= 0) success = 0;
    IntVact = malloc(sizeof(int)*h_trnx_act.n_payloads);
    if (shunt_api_recv  (socket,&h_trnx_exp,IntVact)<= 0) success = 0;
    if (success == 0 )  printf("\nIntV loopback fail recv");

    //compare
    if (shunt_cs_comp_intV  (&h_trnx_exp,IntVexp,IntVact)<= 0) success = 0;

    msg = "Initiator: IntV Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "initiator: header trnx_exp";
      shunt_cs_print_header (&h_trnx_exp,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: header trnx_act";
      shunt_cs_print_header (&h_trnx_act,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: data_exp";
      shunt_cs_print_intV(&h_trnx_exp,IntVexp,msg);
      msg = "initiator: data_act";
      shunt_cs_print_intV(&h_trnx_act,IntVact,msg);
    }

    //Double test
    //header init

    //data init
    success =1;
    msg = "\n\nInitiator: Double Tests";
    puts(msg);

    // DOUBLEV Test
    success =1;
    //Double Vector
    double DoubleVexp[n];
    double* DoubleVact;
    msg = "Initiator: Double Vector Test ";
    for (int i = 0; i < n; i++) {
      DoubleVexp[i] = i+1 ;//rand();
      //printf("\ninitiator DoubleVexp[%0d]=%d",i,DoubleVexp[i]);
    }

    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = shunt_cs_data_type_hash(SHUNT_REAL,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
    h_trnx_exp.n_payloads = n;

    //send
    if (shunt_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ninitiator: fail send header ");
    if (shunt_api_send  (socket,&h_trnx_exp,DoubleVexp)<= 0) success = 0;
    if (success == 0 )  printf("\ninitiator: fail send data");

    //recv
    if (shunt_cs_recv_header (socket,&h_trnx_act)<= 0) success = 0;
    DoubleVact = malloc(sizeof(double)*h_trnx_act.n_payloads);
    if (shunt_api_recv  (socket,&h_trnx_exp,DoubleVact)<= 0) success = 0;
    if (success == 0 )  printf("\nDoubleV loopback fail recv");

    //compare
    if (shunt_cs_comp_doubleV  (&h_trnx_exp,DoubleVexp,DoubleVact)<= 0) success = 0;

    msg = "Initiator: DoubleV Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "initiator: header trnx_exp";
      shunt_cs_print_header (&h_trnx_exp,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: header trnx_act";
      shunt_cs_print_header (&h_trnx_act,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: data_exp";
      shunt_cs_print_doubleV(&h_trnx_exp,DoubleVexp,msg);
      msg = "initiator: data_act";
      shunt_cs_print_doubleV(&h_trnx_act,DoubleVact,msg);
    }

    // String Test
    success =1;
    //String
    msg = "\n\nInitiator: String Tests";
    puts(msg);
    char String_exp[n];
    char *String_act;
    msg = "Initiator: String Test ";
    for (int i = 0; i <= n; i++) {
      String_exp[i] = i + 'a';
      if (i==n) String_exp[i]='\0';
      //printf("\ninitiator String_exp[%0d]=%c",i,String_exp[i]);
    }

    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = shunt_cs_data_type_hash(SHUNT_BYTE,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
    h_trnx_exp.n_payloads = n;

    //send
    if (shunt_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ninitiator: fail send header ");
    if (shunt_api_send  (socket,&h_trnx_exp,String_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ninitiator: fail send data");

    //recv
    if (shunt_cs_recv_header (socket,&h_trnx_act)<= 0) success = 0;
    String_act = malloc(sizeof(char)*h_trnx_act.n_payloads);
    if (shunt_api_recv  (socket,&h_trnx_exp,String_act)<= 0) success = 0;
    if (success == 0 )  printf("\nString loopback fail recv");

    //compare
    if (shunt_cs_comp_byteV  (&h_trnx_exp,String_exp,String_act)<= 0) success = 0;

    msg = "Initiator: String Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "initiator: header trnx_exp";
      shunt_cs_print_header (&h_trnx_exp,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: header trnx_act";
      shunt_cs_print_header (&h_trnx_act,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: data_exp";
      printf("\n%s String_exp=%s",msg,String_exp);
      msg = "initiator: data_act";
      printf("\n%s String_act=%s",msg,String_act);
    }


    success =1;

    //header+LongV test

    shunt_long_t LongVexp[n];
    shunt_long_t * LongVact;
    msg = "Initiator: Long Int Packet Test ";
    for (int i = 0; i < n; i++) {
      LongVexp[i] = rand();
    }

    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = shunt_cs_data_type_hash(SHUNT_LONGINT,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
    h_trnx_exp.n_payloads = n;

    //send
    success=shunt_pkt_send_longV (socket, &h_trnx_exp, LongVexp);

    //recv
    LongVact = malloc(sizeof(shunt_long_t)*h_trnx_act.n_payloads);

    if (shunt_pkt_recv_longV(socket,&h_trnx_act,LongVact)<= 0) success = 0;
    if (success == 0 )  printf("\nLongV loopback fail recv");
    //compare
    if (shunt_cs_comp_longV  (&h_trnx_exp,LongVexp,LongVact)<= 0) success = 0;

    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "initiator: header trnx_exp";
      shunt_cs_print_header (&h_trnx_exp,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: header trnx_act";
      shunt_cs_print_header (&h_trnx_act,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: data_exp";
      shunt_cs_print_longV(&h_trnx_exp,LongVexp,msg);
      msg = "initiator: data_act";
      shunt_cs_print_longV(&h_trnx_act,LongVact,msg);
    }
    puts("\n\napiC_Initiator end");
  }

  if ( success >0)
    return EXIT_SUCCESS;
  else {
    return EXIT_FAILURE;
  }
}


