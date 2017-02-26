
/* 
============================================================================
 File        : ctest_cs_client.c
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
  puts("\nctest_cs_client start");
  int socket;
  char *hostname;
  int port;
  int success=1;
  
  //
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  port = MY_PORT;
  hostname =   MY_HOST;
  //
  socket= svcs_prim_init_tcpclient(port,hostname);
  
  if (socket<0) {
    printf("\nctest_cs_client::FATAL ERROR");
    success=0;
  }
  //printf("\nctest_cs_client::socket=%d", socket);
  
  if (success>0) {
    //puts("\nctest_cs_client start: Echo loopback client test start");
    
    // Headers  Tests
    
    // trnx_header test
    cs_trnx_header h_trnx;
    //char* msg = "client: recv trnx_header";
    //recv
    if (svcs_cs_recv_trnx_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to recv");
    //send loopback
    if (svcs_cs_send_trnx_header(socket,&h_trnx)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to send");
    
    // data_header test
    cs_data_header h_int;
    //char* msg = "client: recv data_header";
    //recv+
    if (svcs_cs_recv_data_header(socket,&h_int)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to recv");
    //send loopback
    if (svcs_cs_send_data_header(socket,&h_int)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to send");
    //
     if (svcs_cs_recv_data_header_clean(&h_int)<=0) success = 0;
    //cs_header test
    cs_header h;
    //char* msg = "client: recv cs_header";
    //recv
    if (svcs_cs_recv_header(socket,&h)<= 0) success = 0;
    if (success == 0 )  printf("\n client cs_header fail to recv");
    //svcs_cs_print_header (&h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    //send loopback
    if (svcs_cs_send_header(socket,&h)<= 0) success = 0;
    if (success == 0 )  printf("\n client trnx_header fail to send");
    
    //     INTV Test
    //Int Array
    //char* msg = "client: recv int_header";
    //cs_data_header h_int;
    //recv

    int* IntA;
    if (svcs_cs_recv_data_header(socket,&h_int)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to recv");
    if (svcs_cs_recv_intV(socket,&h_int,&IntA)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to recv");
    //send
    if (svcs_cs_send_data_header(socket,&h_int)<= 0)  printf("\nclient cs_header fail send");
    if (success == 0 )  printf("\nclient cs_header fail send");
    if (svcs_cs_send_intV(socket,&h_int,IntA)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail send");
    //
    if (svcs_cs_recv_data_header_clean(&h_int)<=0) success = 0;
    //if (svcs_cs_recv_int_clean(&IntA)<=0) success = 0;

    //Int Vector
    int* IntV;
    //recv
    if (svcs_cs_recv_data_header(socket,&h_int)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to recv");
    if (svcs_cs_recv_intV(socket,&h_int,&IntV)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to recv");

    //send
    if (svcs_cs_send_data_header(socket,&h_int)<= 0)  printf("\nclient cs_header fail send");
    if (success == 0 )  printf("\nclient cs_header fail send");
    if (svcs_cs_send_intV(socket,&h_int,(int *)IntV)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail send");
    //
    if (svcs_cs_recv_data_header_clean(&h_int)<=0) success = 0;
    if (svcs_cs_recv_int_clean(&IntV)<=0) success = 0;

    //Int value

    int *IntI;
    //recv
    if (svcs_cs_recv_data_header(socket,&h_int)<= 0) success = 0;
    if (success == 0 )  printf("\n client data_header fail to recv");
    if (svcs_cs_recv_intV(socket,&h_int,&IntI)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail to recv");

    //send
    if (svcs_cs_send_data_header(socket,&h_int)<= 0)  printf("\nclient cs_header fail send");
    if (success == 0 )  printf("\nclient cs_header fail send");
    if (svcs_cs_send_intV(socket,&h_int,IntI)<=0) success = 0;
    if (success == 0 )  printf("\n client Int data fail send");
        //
    if (svcs_cs_recv_data_header_clean(&h_int)<=0) success = 0;
    if (svcs_cs_recv_int_clean(&IntI)<=0) success = 0;
   /*
    int indx=0;
    for(int i=0;i<h_int.n_payloads;i++) {
     //Result_ = send(h->sockid,&Int,h->trnx_payload_sizes[i]*sizeof(int), 0);
     for (int j=0;j< h_int.trnx_payload_sizes[i];j++) {
     printf("\n client recv intA (%0d) IntA[%0d][%0d]=%d",indx,i,j,IntA[indx]);
     indx++;
       	    }
   	    }
   	    */
/*
  for(int i=0;i<h_int.n_payloads;i++) {
  //Result_ = send(h->sockid,&Int,h->trnx_payload_sizes[i]*sizeof(int), 0);
  for (int j=0;j< h_int.trnx_payload_sizes[i];j++) {
  printf("\n client recv intA (%0d) Int[%0d][%0d]=%d",indx,i,j,IntA[indx]);
  indx++;
    	    }
	    }
*/
    //puts("\n");
    /*
    //     INTV Test
    cs_header header;
    success=1;
    header.sockid = socket;
    svcs_cs_recv_header (&header);
    //svcs_cs_print_header(&header,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);

    
     int sum =0;
     for(int i=0;i< header.n_payloads;i++) {
     sum = sum+header.trnx_payload_sizes[i];
     }
     int* IntV;
     IntV = malloc(sizeof(int)*sum);

     if (svcs_cs_recv_intV  (&header,IntV)<= 0) success = 0;
     if (success == 0 )  printf("\nIntV client fail recv");
     /-*
     for (int i = 0; i < header.trnx_payload_sizes[0]; i++) { int indx= 0;
       printf("\nclient IntV[%0d]=%d",i,IntV[i]);
         }
     *-/

     svcs_cs_send_header(&header);
     if (svcs_cs_send_intV (&header,IntV)<= 0) success = 0;
     if (success == 0 )  printf("\nIntV client fail send");
     */
     /////////////////////////////////////
     /* cs_header header_A; */
/*      success=1; */
/*      header_A.sockid = socket; */
/*      svcs_cs_recv_header (&header_A); */
/*      svcs_cs_print_header(&header_A,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY); */
     /////////////////////////////////////
/*     ///////////////////////////////////// */
/*     DOUBLEV Test */
/*     success=1; */
/*     header.sockid = socket; */
/*     svcs_cs_recv_header (&header); */
/*     //svcs_cs_print_header(&header); */
    
/*     double* DoubleV; */
/*     DoubleV = malloc(sizeof(double)*header.n_payloads); */
/*     if (svcs_cs_recv_doubleV  (&header,DoubleV)<= 0) success = 0; */
/*     if (success == 0 )  printf("\nDoubleV client fail recv"); */

/*     for (int i = 0; i < header.trnx_payload_size; i++) { */
/*        	printf("\nserver DoubleV[%0d]=%d",i,DoubleV[i]); */
/*           } */

/*     svcs_cs_send_header(&header); */
/*     if (svcs_cs_send_doubleV (&header,DoubleV)<= 0) success = 0; */
/*     if (success == 0 )  printf("\nDoubleV client fail send"); */
/*     //////////////////////////////////// */
/*    String Test */
/*     success =1; */
/*     //String */

/*     svcs_cs_recv_header (&header); */
/*     //svcs_cs_print_header(&header); */
/*     char* String; */
/*     String = malloc(sizeof(char)*header.n_payloads); */
/*     if (svcs_cs_recv_string  (&header,String)<= 0) success = 0; */
/*     //printf("client string length(%0d) (%s) \n",header.trnx_payload_size,String); */
/*      if (success == 0 )  printf("\nString client fail recv");  */
/*      svcs_cs_send_header(&header); */
/*      if (svcs_cs_send_string (&header,String)<= 0) success = 0; */
/*     if (success == 0 )  printf("\nString client fail send"); */
/*     //////////////////////////////////// */
    //puts("\nctest_cs_client end");
  }
  if ( success >0)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}
