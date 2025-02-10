
/*
   ============================================================================
  Title: apiC_Target.c
  
   Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

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
  //
  cs_header      h_trnx;
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

    //Double Test
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

    //pkt LongV
    //header
    shunt_long_t * LongV;
    //data
    LongV = (shunt_long_t*)malloc(h_trnx.n_payloads* sizeof(shunt_long_t));

    success = shunt_pkt_recv_longV (socket,&h_trnx,LongV);
    if (success == 0 )  printf("\n target Long data fail to recv");
    //send loopback
    success=shunt_pkt_send_longV (socket, &h_trnx, LongV);
    if (success == 0 )  printf("\n target String data fail to send");

    puts("\napiC_Target end");
  }

  if ( success >0)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

