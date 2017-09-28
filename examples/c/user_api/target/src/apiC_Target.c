
/* 
   ============================================================================
   File        : apiC_Target.c
   Version     : 1.0.0
   Copyright (c) 2016-2017 IC Verimeter. All rights reserved.  
   Licensed under the MIT License. 
   See LICENSE file in the project root for full license information.  
   Description :TCP/IP SystemVerilog SHUNT
               An example of API functions-Target(client) 
*/

#include "shunt_user_api.h"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\napiC_Target start");
  int socket;
  char *hostname;
  int port;
  int success=1;
  int sum =0;
  //
  cs_header      h_trnx;
  cs_data_header h_data;
  int* IntA;
  //
  SHUNT_INSTR_HASH_INDEX_DEFINE;
  
  port = MY_PORT;
  hostname =   MY_HOST;
  //
  socket= shunt_prim_init_target(port,hostname);
  
  if (socket<0) {
    printf("\napiC_Target::FATAL ERROR");
    success=0;
  }
  
  if (success>0) {
    h_trnx.trnx_type = rand();
    h_trnx.trnx_id   = rand();
    h_trnx.data_type = shunt_cs_data_type_hash(SHUNT_HEADER_ONLY,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
    h_trnx.n_payloads = -1;
    
    //Int Test
    //Int Array
    //recv
    char* msg = "target: recv trnx_header";
    
    //recv headers
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    
    h_data.trnx_payload_sizes = malloc(h_trnx.n_payloads*sizeof(int));
    if (shunt_cs_recv_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n target data_header fail to recv");
    //shunt_cs_print_data_header(&h_trnx,&h_data,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
    
    sum = 0;
    for (int i=0;i< h_trnx.n_payloads;i++) {
      sum =sum+ 	h_data.trnx_payload_sizes[i];
    }
    IntA = (int *)malloc(sum * sizeof(int));
    //recv data
    if (shunt_api_recv(socket,&h_trnx,&h_data,IntA)<=0) success = 0;
    if (success == 0 )  printf("\n target Int data fail to recv");
    msg = "target: data_exp";
    //shunt_cs_print_intA   (h_trnx.n_payloads,&h_data,&(IntA[0]),msg);
    
    //send loopback
    //send header
    msg = "target: loopback send header ";
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    
    // send data header
    if (shunt_cs_send_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    
    //
    //send data
    shunt_api_send(socket,&h_trnx,&h_data,IntA);

    //Int vector
    int* IntV;
    
    //recv
    //header
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    //data
    IntV = (int *)malloc(h_trnx.n_payloads* sizeof(int));
    if (shunt_api_recv(socket,&h_trnx,IntV)<=0) success = 0;
    if (success == 0 )  printf("\n target Int data fail to recv");
    
    //send loopback
    //header
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to send");
    //data
    if (shunt_api_send(socket,&h_trnx,IntV)<=0) success = 0;
    if (success == 0 )  printf("\n target Int data fail to send");
    ////////////////////////////////////    
    
    //Double Test
    //Double Array
        
    //recv
    
    double* DoubleA;
    msg = "target: recv trnx_header";
    
    //recv headers
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    
    h_data.trnx_payload_sizes = malloc(h_trnx.n_payloads*sizeof(int));
    if (shunt_cs_recv_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n target data_header fail to recv");
        
    sum = 0;
    for (int i=0;i< h_trnx.n_payloads;i++) {
      sum =sum+ 	h_data.trnx_payload_sizes[i];
    }
    DoubleA = (double *)malloc(sum * sizeof(double));
    //recv data
    if (shunt_api_recv(socket,&h_trnx,&h_data,DoubleA)<=0) success = 0;
    if (success == 0 )  printf("\n target Int data fail to recv");
    msg = "target: data_exp";
        
    //send loopback
    //send header
    msg = "target: loopback send header ";
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    
    // send data header
    if (shunt_cs_send_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    //
    //send data
    shunt_api_send(socket,&h_trnx,&h_data,DoubleA);
    
    //Double vector
    double* DoubleV;
    
    //recv
    //header
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    //data
    DoubleV = (double *)malloc(h_trnx.n_payloads* sizeof(double));
    if (shunt_api_recv(socket,&h_trnx,DoubleV)<=0) success = 0;
    if (success == 0 )  printf("\n target Double data fail to recv");
    
    //send loopback
    //header
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to send");
    //data
    if (shunt_api_send(socket,&h_trnx,DoubleV)<=0) success = 0;
    if (success == 0 )  printf("\n target Double data fail to send");
    
    //String
    //char* msg = "target: recv double_header";
    char* String;
    
    //recv
    //header
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    //data
    String = (char *)malloc(h_trnx.n_payloads* sizeof(char));
    if(shunt_api_recv(socket,&h_trnx,String)<=0) success = 0;
    if (success == 0 )  printf("\n target String data fail to recv");
    
    //send loopback
    //header
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to send");
    //data
    if (shunt_api_send(socket,&h_trnx,String)<=0) success = 0;
    if (success == 0 )  printf("\n target String data fail to send");
    
    //String Array
    
    //recv
    
    char* StringA;
    msg = "target: recv trnx_header";
    
    //recv
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    
    h_data.trnx_payload_sizes = malloc(h_trnx.n_payloads*sizeof(int));
    if (shunt_cs_recv_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n target data_header fail to recv");
    sum = 0;
    for (int i=0;i< h_trnx.n_payloads;i++) {
      sum =sum+ 	h_data.trnx_payload_sizes[i];
    }
    StringA = (char *)malloc(sum * sizeof(char));
    shunt_api_recv (socket,&h_trnx,&h_data,&(StringA[0]));
    
    //send
    //send header
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n%s trnx_header fail send",msg);
    //
    msg = "Target: data_type ";
    if (shunt_cs_send_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n%s data_header fail send",msg);
    shunt_api_send (socket,&h_trnx,&h_data,StringA);
    
    ////////////////////////////////////
    //puts("\napiC_Target end");
  }
  
  if ( success >0)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}

