
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
  int  socket=0;
  int  port;
  int success = 1;
  const int col_n = 3;
  const int row_n = 5;
  int sum;
  const int n=17;
  port =       MY_PORT;
  char* msg = "";
  //
  cs_header      h_trnx_exp;
  cs_header      h_trnx_act;
  cs_data_header h_data_exp;
  cs_data_header h_data_act;
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
    
    //String Array Test
    
    char  StringA_exp[row_n][col_n+1];
    char* StringA_act;
    
    msg = "Initiator: String Array Test ";
    
    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = shunt_cs_data_type_hash(SHUNT_A_STRUCTURE,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
    h_trnx_exp.n_payloads = row_n;
    
    for (int i = 0; i < row_n; i++) {
      for   (int j = 0; j < col_n+1; j++) {
	int indx =  j+(i*10) + '0';
	StringA_exp[i][j] = (char) indx;
	if (j == col_n) StringA_exp[i][col_n] = '\0';
      }
      printf("\ninitiator  StringA_exp[%0d]=%s",i,&(StringA_exp[i][0]));
    }
    
    //send header
    if (shunt_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    //
    msg = "Initiator: data_type ";
    h_data_exp.data_type = shunt_cs_data_type_hash(SHUNT_BYTE,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
    h_data_exp.trnx_payload_sizes = malloc(h_trnx_exp.n_payloads*sizeof(int));
    
    for(int i=0;i< h_trnx_exp.n_payloads;i++) {
      h_data_exp.trnx_payload_sizes[i]   = col_n+1;
    }
    msg = "Initiator: data_type ";
    
    if (shunt_cs_send_data_header(socket,h_trnx_exp.n_payloads,&h_data_exp)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    shunt_api_send (socket,&h_trnx_exp,&h_data_exp,&StringA_exp[0][0]);
    if (success == 0 )  printf("\ninitiator: fail send data");
    
    //recv
    if (shunt_cs_recv_header(socket,&h_trnx_act)<= 0) success = 0;
    if (success == 0 )  printf("\n initiator trnx_header fail to recv");
    
    h_data_act.trnx_payload_sizes = malloc(h_trnx_act.n_payloads*sizeof(int));
    if (shunt_cs_recv_data_header(socket,h_trnx_act.n_payloads,&h_data_act)<= 0) success = 0;
    if (success == 0 )  printf("\n initiator data_header fail to recv");
    
    sum = 0;
    for (int i=0;i< h_trnx_act.n_payloads;i++) {
      sum =sum+ 	h_data_act.trnx_payload_sizes[i];
    }
    StringA_act = (char *)malloc(sum * sizeof(char));
    shunt_api_recv (socket,&h_trnx_act,&h_data_act,&(StringA_act[0]));
    
    //compare
    if (shunt_cs_comp_byteV  (&h_trnx_exp,String_exp,String_act)<= 0) success = 0;
    
    msg = "Initiator: StringA Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "initiator: header trnx_exp";
      shunt_cs_print_header (&h_trnx_exp,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: header trnx_act";
      shunt_cs_print_header (&h_trnx_act,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
      msg = "initiator: data_exp";
      shunt_cs_print_byteA(h_trnx_exp.n_payloads,&h_data_exp,&(StringA_exp[0][0]),msg);
      msg = "initiator: data_act";
      shunt_cs_print_byteA(h_trnx_act.n_payloads,&h_data_act,&(StringA_act[0]),msg);
    }

    ////////////////////////////////////////
      
    puts("\n\napiC_Initiator end");
  }
  
  if ( success >0)
    return EXIT_SUCCESS;
  else {
    return EXIT_FAILURE;
  }
}


