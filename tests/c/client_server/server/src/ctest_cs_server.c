
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
  port =       MY_PORT;
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
    cs_header   h_trnx_exp;
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_A_STRUCTURE,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    h_trnx_exp.n_payloads = row_n;//rand()%20;
    char* msg = "\nServer: Header Tests";
    puts(msg);
    //send
    if (svcs_cs_send_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ntrnx_header fail send");
    //recv
    cs_header   h_trnx_act;
    if (svcs_cs_recv_header(socket,&h_trnx_act)<= 0) success = 0;
    if (success == 0 )  printf("\ntrnx_header fail recv");
    //compare
    success = svcs_cs_comp_header(h_trnx_exp,h_trnx_act);

    if(success <=0) {
      printf("\n  trnx_header loopback fail");
      msg = "server: trnx_exp";
      svcs_cs_print_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: trnx_act";
      svcs_cs_print_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    }
    else printf("\n trnx_header loopback pass");

    //data_header
    success =1;
    cs_data_header h_data_exp;
    cs_data_header h_data_act;
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
    msg = "server: data_act";
    svcs_cs_print_data_header(&h_trnx_act,&h_data_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    if(success <=0) {
      //printf("\n  data_header loopback fail");
      msg = "server: data_exp";
      svcs_cs_print_data_header(&h_trnx_exp,&h_data_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: data_act";
      svcs_cs_print_data_header(&h_trnx_act,&h_data_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    }
    else
    	printf("\n data_header loopback pass");

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
	  printf("\nserver IntAexp[%0d][%0d]=%d",i,j,IntA_exp[i][j]);
      }
    }
/*
    //send

    if (svcs_cs_send_intA(socket,h_trnx_act.n_payloads,(int *)IntA_exp)<=0) success = 0;
    if (success == 0 )  printf("\n server Int data fail send");

    //recv
    if (svcs_cs_recv_data_header(socket,&h_int_act)<= 0) success = 0;
    if (success == 0 )  printf("\n server data_header fail to recv");
    if (svcs_cs_recv_int(socket,&h_int_act,&IntA_act)<=0) success = 0;
    if (success == 0 )  printf("\n server Int data fail to recv");

    //compare
    if (h_int_exp.n_payloads != h_int_act.n_payloads) success = 0;
    else {
      for(int i=0;i<h_int_exp.n_payloads;i++) {
	if (h_int_exp.trnx_payload_sizes[i] != h_int_act.trnx_payload_sizes[i]) success = 0;
      }
    }
    indx=0;
    for (int i = 0; i < h_int_exp.n_payloads; i++) {
      for   (int j = 0; j < h_int_exp.trnx_payload_sizes[i]; j++) {
	if(IntA_act[indx] !=  IntA_exp[i][j] ) {
      printf("\n%s server [%0d] IntA_act=%d \tIntA_exp=%d",msg,indx,IntA_act[indx],IntA_exp[i][j]) ;
	  success = 0;
	}
	indx++;
      }
    }

    //
    if (success > 0 )  printf("\n %s loopback pass",msg);
    else {
     printf("\n %s loopback fail",msg);
	 msg = "server: data_exp";
	 svcs_cs_print_data_header (&h_int_exp,msg);
	 msg = "server: data_act";
	 svcs_cs_print_data_header (&h_int_act,msg);
    }
    //clean up memory
    if (svcs_cs_recv_data_header_clean(&h_int_act)<=0) success = 0;
    if (svcs_cs_recv_data_header_clean(&h_int_exp)<=0) success = 0;
    if (svcs_cs_recv_int_clean(&IntA_act)<=0) success = 0;

    //Int Vector
    msg = "Server: Int Vector Test ";
    int const row_v = 1;
    int const col_v = 4;
    int IntV_exp[col_v];
    int *IntV_act;
    //send
    h_int_exp.n_payloads = row_v;
    h_int_exp.trnx_payload_sizes = malloc(h_data_exp.n_payloads*sizeof(int));
    h_int_exp.trnx_payload_sizes[0] =  col_v;

    for (int i = 0; i < col_v; i++) {
    	IntV_exp[i] = i;
        }

     //svcs_cs_print_data_header (&h_int_exp,msg);
     //send
     if (svcs_cs_send_data_header(socket,&h_int_exp)<= 0) success = 0;
     if (success == 0 )  printf("\n server cs_header fail send");
     if (svcs_cs_send_int(socket,&h_int_exp,(int *)IntV_exp)<=0) success = 0;
     if (success == 0 )  printf("\n server Int data fail send");
     //recv

     if (svcs_cs_recv_data_header(socket,&h_int_act)<= 0) success = 0;
     if (success == 0 )  printf("\n server data_header fail to recv");

     if (svcs_cs_recv_int(socket,&h_int_act,&IntV_act)<=0) success = 0;
     if (success == 0 )  printf("\n server Int data fail to recv");
     indx= 0;

     //compare
     if (h_int_exp.n_payloads != h_int_act.n_payloads) success = 0;
     else {
    	 for(int i=0;i<h_int_exp.n_payloads;i++) {
    		 if (h_int_exp.trnx_payload_sizes[i] != h_int_act.trnx_payload_sizes[i]) success = 0;
           }
         }
     indx=0;
     for (int i = 0; i < h_int_exp.n_payloads; i++) {
    	 for   (int j = 0; j < h_int_exp.trnx_payload_sizes[i]; j++) {
    		 if(IntV_act[indx] !=  IntV_exp[indx] )
    		 {
    			 success = 0;
    			 printf("\n%s server [%0d] IntV_act=%d \tIntV_exp=%d",msg,indx,IntV_act[indx],IntV_exp[indx]) ;
    		 }
    		 indx++;
           }
         }

     if (success > 0 )  printf("\n %s loopback pass",msg);
     else   {
    	 printf("\n %s loopback fail",msg);
    	 msg = "server: data_exp";
    	 svcs_cs_print_data_header (&h_int_exp,msg);
    	 msg = "server: data_act";
    	 svcs_cs_print_data_header (&h_int_act,msg);
     }
     //clean up memory
     if (svcs_cs_recv_data_header_clean(&h_int_act)<=0) success = 0;
     if (svcs_cs_recv_data_header_clean(&h_int_exp)<=0) success = 0;
     if (svcs_cs_recv_int_clean(&IntV_act)<=0) success = 0;

     //
     //Int value
     msg = "Server: Int Value Test ";
     int row_i = 1;
     int col_i = 1;

     int IntI_exp=rand();
     int *IntI_act;
     //send
     h_int_exp.n_payloads = row_i;
     h_int_exp.trnx_payload_sizes = malloc(h_data_exp.n_payloads*sizeof(int));
     h_int_exp.trnx_payload_sizes[0] =  col_i;

     //svcs_cs_print_data_header (&h_int_exp,msg);
     //send
     if (svcs_cs_send_data_header(socket,&h_int_exp)<= 0) success = 0;
     if (success == 0 )  printf("\n server cs_header fail send");
     if (svcs_cs_send_int(socket,&h_int_exp,&IntI_exp)<=0) success = 0;
     if (success == 0 )  printf("\n server Int data fail send");
     //recv
     if (svcs_cs_recv_data_header(socket,&h_int_act)<= 0) success = 0;
     if (success == 0 )  printf("\n server data_header fail to recv");
     if (svcs_cs_recv_int(socket,&h_int_act,&IntI_act)<=0) success = 0;
     if (success == 0 )  printf("\n server Int data fail to recv");
     indx= 0;

     //compare
     if (h_int_exp.n_payloads != h_int_act.n_payloads) success = 0;
     else {
    	 for(int i=0;i<h_int_exp.n_payloads;i++) {
    		 if (h_int_exp.trnx_payload_sizes[i] != h_int_act.trnx_payload_sizes[i]) success = 0;
    	 }
     }
     indx=0;

     if(*IntI_act !=  IntI_exp) {
    	 success = 0;
    	 printf("\n%s server IntI_act=%d \tIntI_exp=%d",msg,*IntI_act,IntI_exp) ;
     }

     if (success > 0 )  printf("\n %s loopback pass",msg);
     else   {
    	 printf("\n %s loopback fail",msg);
    	 msg = "server: data_exp";
    	 svcs_cs_print_data_header (&h_int_exp,msg);
    	 msg = "server: data_act";
    	 svcs_cs_print_data_header (&h_int_act,msg);
      }
     //clean up memory
     if (svcs_cs_recv_data_header_clean(&h_int_act)<=0) success = 0;
     if (svcs_cs_recv_data_header_clean(&h_int_exp)<=0) success = 0;
     if (svcs_cs_recv_int_clean(&IntI_act)<=0) success = 0;

*/
/////////////////////////////////////////////
      puts("\n\nctest_cs_server end");
    }

  if ( success >0)
    return EXIT_SUCCESS;
  else {
    return EXIT_FAILURE;
  }
}

