
/* 
   ============================================================================
   File        : ctest_cs_client.c
   Author      : Victor Besyakov
   Version     : 0.0.0
   Copyright (c) 2016 IC Verimeter. All rights reserved.  
   Licensed under the MIT License. 
   See LICENSE file in the project root for full license information.  
   Description : ctest client
   System Verilog client server handshake (SVCS)
*/

#include "svcs_client_server.h"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\nctest_cs_client start");
  int socket;
  char *hostname;
  int port;
  int success=1;
  
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  
  port = MY_PORT;
  hostname =   MY_HOST;
  //
  socket= svcs_prim_init_tcpclient(port,hostname);
  
  if (socket<0) {
    printf("\nctest_cs_client::FATAL ERROR");
    success=0;
  }
  
  if (success>0) {
    
    // Headers  Tests
    
    // trnx_header test
    cs_header h_trnx;
    
    //recv
    if (svcs_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to recv");
    //send loopback
    if (svcs_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to send");
    
    // data_header test
    cs_data_header h_data;
    
    //recv
    h_data.trnx_payload_sizes = malloc(h_trnx.n_payloads*sizeof(int));
    if (svcs_cs_recv_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to recv");
    //send loopback
    if (svcs_cs_send_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to send");
    
    //     INT Test
    //Int Array
    
    //recv
    int* IntA;
    int sum = 0;
    for (int i=0;i< h_trnx.n_payloads;i++) {
      sum =sum+ 	h_data.trnx_payload_sizes[i];
    }
    IntA = (int *)malloc(sum * sizeof(int));
    
    if (svcs_cs_recv_intA(socket,h_trnx.n_payloads,&h_data,IntA)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to recv");
    if (svcs_cs_send_intA(socket,h_trnx.n_payloads,&h_data,IntA)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to send");
    
    //Int vector
    int* IntV;
    
    //recv
    //header
    if (svcs_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to recv");
    //data
    IntV = (int *)malloc(h_trnx.n_payloads* sizeof(int));
    if (svcs_cs_recv_intV(socket,&h_trnx,IntV)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to recv");
    
    //send loopback
    //header
    if (svcs_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to send");
    //data
    if (svcs_cs_send_intV(socket,&h_trnx,IntV)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to send");
    
    
    ////////////////////////////////////    
    
    //Double Test
    //Double Array
        
    //recv
    
    double* DoubleA;
    char* msg = "client: recv trnx_header";
    
    //recv headers
    if (svcs_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to recv");
    
    h_data.trnx_payload_sizes = malloc(h_trnx.n_payloads*sizeof(int));
    if (svcs_cs_recv_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to recv");
    //svcs_cs_print_data_header(&h_trnx,&h_data,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    
    sum = 0;
    for (int i=0;i< h_trnx.n_payloads;i++) {
      sum =sum+ 	h_data.trnx_payload_sizes[i];
    }
    DoubleA = (double *)malloc(sum * sizeof(double));
    //recv data
    if (svcs_cs_recv_doubleA(socket,h_trnx.n_payloads,&h_data,DoubleA)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to recv");
    msg = "client: data_exp";
        
    //send loopback
    //send header
    msg = "client: loopback send header ";
    //svcs_cs_print_header(&h_trnx,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    if (svcs_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    
    // send data header
    if (svcs_cs_send_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    //
    //send data
    svcs_cs_send_doubleA(socket,h_trnx.n_payloads,&h_data,DoubleA);
    
    //Double vector
    double* DoubleV;
    
    //recv
    //header
    if (svcs_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to recv");
    //data
    DoubleV = (double *)malloc(h_trnx.n_payloads* sizeof(double));
    if (svcs_cs_recv_doubleV(socket,&h_trnx,DoubleV)<=0) success = 0;
    if (success == 0 )  printf("\n client Double data fail to recv");
    
    //send loopback
    //header
    if (svcs_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to send");
    //data
    if (svcs_cs_send_doubleV(socket,&h_trnx,DoubleV)<=0) success = 0;
    if (success == 0 )  printf("\n client Double data fail to send");
    
    //String
    //char* msg = "client: recv double_header";
    char* String;
    //recv
    //header
    if (svcs_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to recv");
    //data
   String = (char*)malloc(h_trnx.n_payloads*sizeof(char));

    if(svcs_cs_recv_byteV(socket,&h_trnx,String)<=0) success = 0;
    if (success == 0 )  printf("\n client String data fail to recv");
    
    //send loopback
    //header
    if (svcs_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to send");
    //data
    if (svcs_cs_send_byteV(socket,&h_trnx,String)<=0) success = 0;
    if (success == 0 )  printf("\n client String data fail to send");
    
    
    //String Array
        
    //recv

    char* StringA;
    msg = "client: recv trnx_header";
    
    //recv
    if (svcs_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to recv");
    
    h_data.trnx_payload_sizes = malloc(h_trnx.n_payloads*sizeof(int));
    if (svcs_cs_recv_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to recv");
    sum = 0;
    for (int i=0;i< h_trnx.n_payloads;i++) {
      sum =sum+ 	h_data.trnx_payload_sizes[i];
    }
    StringA = (char *)malloc(sum * sizeof(char));
    svcs_cs_recv_byteA (socket,h_trnx.n_payloads,&h_data,&(StringA[0]));
    
    //send
    //send header
    if (svcs_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    //
    msg = "Client: data_type ";
    if (svcs_cs_send_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    svcs_cs_send_byteA (socket,h_trnx.n_payloads,&h_data,StringA);
    
    ////////////////////////////////////

    
    //puts("\nctest_cs_client end");
  }
  
  if ( success >0)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}

