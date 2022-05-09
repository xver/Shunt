
/*
   ============================================================================
   File        : csC_Target.c
   Version     : 1.0.0
   Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
   Licensed under the MIT License.
   See LICENSE file in the project root for full license information.
   Description :  TCP/IP SystemVerilog SHUNT
                  An example of client-server functions-Target(Client)

*/

#include "shunt_client_server.h"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\ncsC_Target start");
  int socket;
  char *hostname;
  int port;
  int success=1;

  //SVCV_INSTR_HASH_INDEX_DEFINE;

  port = 0;//MY_PORT;
  hostname =   MY_HOST;
  //
  socket= shunt_cs_init_target(port,hostname);

  if (socket<0) {
    printf("\ncsC_Target::FATAL ERROR");
    success=0;
  }

  if (success>0) {

    // Headers  Tests

    // trnx_header test
    cs_header h_trnx;

    //recv
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    //send loopback
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to send");

    // data_header test
    cs_data_header h_data;

    //recv
    h_data.trnx_payload_sizes = malloc(h_trnx.n_payloads*sizeof(int));
    if (shunt_cs_recv_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n target data_header fail to recv");
    //send loopback
    if (shunt_cs_send_data_header(socket,h_trnx.n_payloads,&h_data)<= 0) success = 0;
    if (success == 0 )  printf("\n target data_header fail to send");

    //     INT Test

    //Int vector
    int* IntV;

    //recv
    //header
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    //data
    IntV = (int *)malloc(h_trnx.n_payloads* sizeof(int));
    if (shunt_cs_recv_intV(socket,&h_trnx,IntV)<=0) success = 0;
    if (success == 0 )  printf("\n target Int data fail to recv");

    //send loopback
    //header
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to send");
    //data
    if (shunt_cs_send_intV(socket,&h_trnx,IntV)<=0) success = 0;
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
    if (shunt_cs_recv_doubleV(socket,&h_trnx,DoubleV)<=0) success = 0;
    if (success == 0 )  printf("\n target Double data fail to recv");

    //send loopback
    //header
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to send");
    //data
    if (shunt_cs_send_doubleV(socket,&h_trnx,DoubleV)<=0) success = 0;
    if (success == 0 )  printf("\n target Double data fail to send");

    //String
    //char* msg = "target: recv double_header";
    char* String;
    //recv
    //header
    if (shunt_cs_recv_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to recv");
    //data
   String = (char*)malloc(h_trnx.n_payloads*sizeof(char));

    if(shunt_cs_recv_byteV(socket,&h_trnx,String)<=0) success = 0;
    if (success == 0 )  printf("\n target String data fail to recv");

    //send loopback
    //header
    if (shunt_cs_send_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n target trnx_header fail to send");
    //data
    if (shunt_cs_send_byteV(socket,&h_trnx,String)<=0) success = 0;
    if (success == 0 )  printf("\n target String data fail to send");

    //puts("\ncsC_Target end");
  }

  if ( success >0)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

