
/* 
============================================================================
 File        : ctest_cs_server.c
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : ctest server                  
System Verilog client server handshake (SVCS)
*/

#include "svcs_client_server.h"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\nctest_cs_server start");
  int  socket;
  int  port;
  int success = 1;
  const int col_n = 3;
  const int row_n = 5;

  int sum;
  port =       MY_PORT;
  char* msg = "";
  //
  cs_header      h_trnx_exp;
  cs_header      h_trnx_act;
  cs_data_header h_data_exp;
  cs_data_header h_data_act;
  //
  socket= svcs_prim_init_tcpserver(port);
  if (socket<0) {
    printf("ctest_cs_server::FATAL ERROR");
    success = 0;
  }
  
  printf("\nctest_cs_server::socket=%d", socket);
  
  if (success>0) {
    puts("\nctest_cs_server start: Echo loopback server test start");
    
    // Headers  Tests
    //trnx_header
    SVCV_INSTR_HASH_INDEX_DEFINE;
    
    //set up header
    success =1;
    //set up header
    success =1;
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_A_STRUCTURE,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_trnx_exp.n_payloads = row_n;//rand()%20;
    msg = "\nServer: Header Tests";
    puts(msg);
    //send
    if (svcs_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ntrnx_header fail send");
    //recv
    //cs_header   h_trnx_act;
    if (svcs_cs_recv_header(socket,&h_trnx_act)<= 0) success = 0;
    if (success == 0 )  printf("\ntrnx_header fail recv");
    //compare
    success = svcs_cs_comp_header(h_trnx_exp,h_trnx_act);
    
    msg = "Server: trnx header Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else {
      printf("\n  trnx_header loopback fail");
      msg = "server: trnx_exp";
      svcs_cs_print_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: trnx_act";
      svcs_cs_print_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    }
    
    //data_header
    success =1;
    
    //send
    //int n_payloads = rand()%20;
    h_data_exp.data_type = svcs_cs_data_type_hash(SVCS_INT,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_data_exp.trnx_payload_sizes = malloc(h_trnx_act.n_payloads*sizeof(int));
    
    for(int i=0;i< h_trnx_act.n_payloads;i++) {
      h_data_exp.trnx_payload_sizes[i]   = col_n;//rand()%100;
    }
    if (svcs_cs_send_data_header(socket,h_trnx_act.n_payloads,&h_data_exp)<= 0) success = 0;
    //recv
    h_data_act.data_type = svcs_cs_data_type_hash(SVCS_HEADER_ONLY,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_data_act.trnx_payload_sizes = malloc(h_trnx_act.n_payloads*sizeof(int));
    
    if (svcs_cs_recv_data_header(socket,h_trnx_act.n_payloads,&h_data_act)<= 0) success = 0;
    if (success == 0 )  printf("\n server data_header fail to recv");
    
    msg = "Server: data_header Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else {
      msg = "server: data_exp";
      svcs_cs_print_data_header(&h_trnx_exp,&h_data_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_act";
      svcs_cs_print_data_header(&h_trnx_act,&h_data_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    }
    ////////////////////////////////////////////////
    
    //Int Test
    success =1;
    msg = "\n\nServer: Int Tests";
    puts(msg);
    
    //Int Array
    msg = "Server: 2D Int Array Test ";
    
    int IntA_exp[row_n][col_n];
    int *IntA_act;
    
    for (int i = 0; i < row_n; i++) {
      for   (int j = 0; j < col_n; j++) {
	IntA_exp[i][j] = j+i*10;
	//printf("\nserver IntAexp[%0d][%0d]=%d",i,j,IntA_exp[i][j]);
      }
    }
    
    svcs_cs_send_intA(socket,h_trnx_act.n_payloads,&h_data_act,(int *)IntA_exp);
    
    sum = 0;
    for (int i=0;i< h_trnx_act.n_payloads;i++) {
      sum =sum+ 	h_data_act.trnx_payload_sizes[i];
    }
    IntA_act = (int *)malloc(sum * sizeof(int));
    
    if (svcs_cs_recv_intA(socket,h_trnx_act.n_payloads,&h_data_act,IntA_act)<=0) success = 0;
    if (success == 0 )  printf("\nserver Int data fail to recv");
    
    //compare
    if (svcs_cs_comp_intA(h_trnx_act.n_payloads,&h_data_act,(int *)IntA_exp,IntA_act)<=0)  success = 0;
    //
    msg = "Server: 2D Int Array Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else {
      msg = "server: data_exp";
      svcs_cs_print_intA(h_trnx_exp.n_payloads,&h_data_exp,(int *)IntA_exp,msg);
      msg = "server: data_act";
      svcs_cs_print_intA(h_trnx_act.n_payloads,&h_data_act,IntA_act,msg);
    }
    
    // INTV Test
    success =1;
    //Int Vector
    const int n=17;
    int IntVexp[n];
    int* IntVact;
    msg = "Server: Int Vector Test ";
    for (int i = 0; i < n; i++) {
      IntVexp[i] = i+1 ;//rand();
      //printf("\nserver IntVexp[%0d]=%d",i,IntVexp[i]);
    }
    
    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_INT,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_trnx_exp.n_payloads = n;
    
    //send
    if (svcs_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\nserver: fail send header ");
    if (svcs_cs_send_intV  (socket,&h_trnx_exp,IntVexp)<= 0) success = 0;
    if (success == 0 )  printf("\nserver: fail send data");
    
    //recv
    if (svcs_cs_recv_header (socket,&h_trnx_act)<= 0) success = 0;
    IntVact = malloc(sizeof(int)*h_trnx_act.n_payloads);
    if (svcs_cs_recv_intV  (socket,&h_trnx_exp,IntVact)<= 0) success = 0;
    if (success == 0 )  printf("\nIntV loopback fail recv");
    
    //compare
    if (svcs_cs_comp_intV  (&h_trnx_exp,IntVexp,IntVact)<= 0) success = 0;
    
    msg = "Server: IntV Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "server: header trnx_exp";
      svcs_cs_print_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: header trnx_act";
      svcs_cs_print_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_exp";
      svcs_cs_print_intV(&h_trnx_exp,IntVexp,msg);
      msg = "server: data_act";
      svcs_cs_print_intV(&h_trnx_act,IntVact,msg);
    }
    
    //Double test
    //header init
    
    //data init
    success =1;
    msg = "\n\nServer: Double Tests";
    puts(msg);
    
    //Int Array
    msg = "Server: 2D Double Array Test ";
    
    double DoubleA_exp[row_n][col_n];
    double *DoubleA_act;
    
    for (int i = 0; i < row_n; i++) {
      for   (int j = 0; j < col_n; j++) {
	DoubleA_exp[i][j] = j+i*10;
	//printf("\nserver DoubleA_exp[%0d][%0d]=%f",i,j,DoubleA_exp[i][j]);
      }
    }
    
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_A_STRUCTURE,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_trnx_exp.n_payloads = row_n;
    
    //free(h_data_exp.trnx_payload_sizes);
    
    //send header
    if (svcs_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    //
    msg = "Server: data_type ";
    h_data_exp.data_type = svcs_cs_data_type_hash(SVCS_DOUBLE,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_data_exp.trnx_payload_sizes = malloc(h_trnx_exp.n_payloads*sizeof(int));
    
    for(int i=0;i< h_trnx_exp.n_payloads;i++) {
      h_data_exp.trnx_payload_sizes[i]   = col_n;//rand()%100;
      //printf("\n%s h_data_exp.trnx_payload_sizes[%0d]=%0d",msg,i,h_data_exp.trnx_payload_sizes[i]);
    }
    msg = "Server: data_type ";
    if (svcs_cs_send_data_header(socket,h_trnx_exp.n_payloads,&h_data_exp)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    
    //send data
    svcs_cs_send_doubleA(socket,h_trnx_exp.n_payloads,&h_data_exp,(double *)DoubleA_exp);
    
    //loopback recieve
    //recv headers
    msg = "Server: recv header";
    if (svcs_cs_recv_header(socket,&h_trnx_act)<= 0) success = 0;
    if (success == 0 )  printf("\n server trnx_header fail to recv");
    //
    h_data_act.trnx_payload_sizes = malloc(h_trnx_act.n_payloads*sizeof(int));
    if (svcs_cs_recv_data_header(socket,h_trnx_act.n_payloads,&h_data_act)<= 0) success = 0;
    if (success == 0 )  printf("\n server data_header fail to recv");
    
    sum = 0;
    for (int i=0;i< h_trnx_act.n_payloads;i++) {
      sum =sum+ 	h_data_act.trnx_payload_sizes[i];
    }
    DoubleA_act = (double *)malloc(sum * sizeof(double));
    //recv data
    if (svcs_cs_recv_doubleA(socket,h_trnx_act.n_payloads,&h_data_act,DoubleA_act)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to recv");
    msg = "seerver: data_act";
    
    //compare
    if (svcs_cs_comp_doubleA   (h_trnx_act.n_payloads,&h_data_act,(double *)DoubleA_exp,DoubleA_act) <= 0)success = 0;
    
    msg = "Server: 2D Double Array Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "server: header trnx_exp";
      svcs_cs_print_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: header trnx_act";
      svcs_cs_print_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_header_exp";
      svcs_cs_print_data_header(&h_trnx_exp,&h_data_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_header_act";
      svcs_cs_print_data_header(&h_trnx_act,&h_data_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_exp";
      svcs_cs_print_doubleA(h_trnx_act.n_payloads,&h_data_act,(double *)DoubleA_exp,msg);
      msg = "server: data_act";
      svcs_cs_print_doubleA(h_trnx_act.n_payloads,&h_data_act,(double *)DoubleA_act,msg);
      
    }
    
    // DOUBLEV Test
    success =1;
    //Double Vector
    double DoubleVexp[n];
    double* DoubleVact;
    msg = "Server: Double Vector Test ";
    for (int i = 0; i < n; i++) {
      DoubleVexp[i] = i+1 ;//rand();
      //printf("\nserver DoubleVexp[%0d]=%d",i,DoubleVexp[i]);
    }
    
    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_DOUBLE,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_trnx_exp.n_payloads = n;
    
    //send
    if (svcs_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\nserver: fail send header ");
    if (svcs_cs_send_doubleV  (socket,&h_trnx_exp,DoubleVexp)<= 0) success = 0;
    if (success == 0 )  printf("\nserver: fail send data");
    
    //recv
    if (svcs_cs_recv_header (socket,&h_trnx_act)<= 0) success = 0;
    DoubleVact = malloc(sizeof(double)*h_trnx_act.n_payloads);
    if (svcs_cs_recv_doubleV  (socket,&h_trnx_exp,DoubleVact)<= 0) success = 0;
    if (success == 0 )  printf("\nDoubleV loopback fail recv");
    
    //compare
    if (svcs_cs_comp_doubleV  (&h_trnx_exp,DoubleVexp,DoubleVact)<= 0) success = 0;
    
    msg = "Server: DoubleV Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "server: header trnx_exp";
      svcs_cs_print_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: header trnx_act";
      svcs_cs_print_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_exp";
      svcs_cs_print_doubleV(&h_trnx_exp,DoubleVexp,msg);
      msg = "server: data_act";
      svcs_cs_print_doubleV(&h_trnx_act,DoubleVact,msg);
    }
    
    // String Test
    success =1;
    //String
    msg = "\n\nServer: String Tests";
    puts(msg);
    char String_exp[n];
    char *String_act;
    msg = "Server: String Test ";
    for (int i = 0; i <= n; i++) {
      String_exp[i] = i + 'a';
      if (i==n) String_exp[i]='\0';
      //printf("\nserver String_exp[%0d]=%c",i,String_exp[i]);
    }
    
    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_STRING,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_trnx_exp.n_payloads = n;
    
    //send
    if (svcs_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\nserver: fail send header ");
    if (svcs_cs_send_string  (socket,&h_trnx_exp,String_exp)<= 0) success = 0;
    if (success == 0 )  printf("\nserver: fail send data");
    
    //recv
    if (svcs_cs_recv_header (socket,&h_trnx_act)<= 0) success = 0;
    String_act = malloc(sizeof(char)*h_trnx_act.n_payloads);
    if (svcs_cs_recv_string  (socket,&h_trnx_exp,String_act)<= 0) success = 0;
    if (success == 0 )  printf("\nString loopback fail recv");
    
    //compare
    if (svcs_cs_comp_string  (&h_trnx_exp,String_exp,String_act)<= 0) success = 0;
    
    msg = "Server: String Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "server: header trnx_exp";
      svcs_cs_print_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: header trnx_act";
      svcs_cs_print_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_exp";
      printf("\n%s String_exp=%s",msg,String_exp);
      msg = "server: data_act";
      printf("\n%s String_act=%s",msg,String_act);
    }
    
    
    success =1;
    
    //String Array Test
    
    char  StringA_exp[row_n][col_n+1];
    char* StringA_act;
    
    msg = "Server: String Array Test ";
    
    //set up header
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_A_STRUCTURE,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_trnx_exp.n_payloads = row_n;
    
    for (int i = 0; i < row_n; i++) {
      for   (int j = 0; j < col_n+1; j++) {
	int indx =  j+(i*10) + '0';
	StringA_exp[i][j] = (char) indx;
	if (j == col_n) StringA_exp[i][col_n] = '\0';
      }
      //printf("\nserver  StringA_exp[%0d]=%s",i,&(StringA_exp[i][0]));
    }
    
    //send header
    if (svcs_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    //
    msg = "Server: data_type ";
    h_data_exp.data_type = svcs_cs_data_type_hash(SVCS_STRING,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_data_exp.trnx_payload_sizes = malloc(h_trnx_exp.n_payloads*sizeof(int));
    
    for(int i=0;i< h_trnx_exp.n_payloads;i++) {
      h_data_exp.trnx_payload_sizes[i]   = col_n+1;
    }
    msg = "Server: data_type ";
    
    if (svcs_cs_send_data_header(socket,h_trnx_exp.n_payloads,&h_data_exp)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    svcs_cs_send_stringA (socket,h_trnx_exp.n_payloads,&h_data_exp,&StringA_exp[0][0]);
    if (success == 0 )  printf("\nserver: fail send data");
    
    //recv
    if (svcs_cs_recv_header(socket,&h_trnx_act)<= 0) success = 0;
    if (success == 0 )  printf("\n server trnx_header fail to recv");
    //svcs_cs_print_header(&h_trnx,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    
    h_data_act.trnx_payload_sizes = malloc(h_trnx_act.n_payloads*sizeof(int));
    if (svcs_cs_recv_data_header(socket,h_trnx_act.n_payloads,&h_data_act)<= 0) success = 0;
    if (success == 0 )  printf("\n server data_header fail to recv");
    
    sum = 0;
    for (int i=0;i< h_trnx_act.n_payloads;i++) {
      sum =sum+ 	h_data_act.trnx_payload_sizes[i];
    }
    StringA_act = (char *)malloc(sum * sizeof(char));
    svcs_cs_recv_stringA (socket,h_trnx_act.n_payloads,&h_data_act,&(StringA_act[0]));
    
    //compare
    if (svcs_cs_comp_string  (&h_trnx_exp,String_exp,String_act)<= 0) success = 0;
    
    msg = "Server: StringA Test ";
    if (success > 0 )  printf("\n\t%s loopback pass",msg);
    else  {
      printf("\n %s loopback fail",msg);
      msg = "server: header trnx_exp";
      svcs_cs_print_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: header trnx_act";
      svcs_cs_print_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_exp";
      svcs_cs_print_StringA(h_trnx_exp.n_payloads,&h_data_exp,&(StringA_exp[0][0]),msg);
      msg = "server: data_act";
      svcs_cs_print_StringA(h_trnx_act.n_payloads,&h_data_act,&(StringA_act[0]),msg);
    }
    /////////////////////////////////////////

      puts("\n\nctest_cs_server end");
  }
  
  if ( success >0)
    return EXIT_SUCCESS;
  else {
    return EXIT_FAILURE;
  }
}


