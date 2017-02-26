
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
    cs_trnx_header   h_trnx_exp;
    h_trnx_exp.trnx_type = rand();
    h_trnx_exp.trnx_id   = rand();
    h_trnx_exp.data_type = svcs_cs_data_type_hash(SVCS_V_INT,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    
    char* msg = "\nServer: Header Tests";
    puts(msg);
    //send
    if (svcs_cs_send_trnx_header(socket,&h_trnx_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ntrnx_header fail send");
    //recv
    cs_trnx_header   h_trnx_act;
    if (svcs_cs_recv_trnx_header(socket,&h_trnx_act)<= 0) success = 0;
    if (success == 0 )  printf("\ntrnx_header fail recv");
    //compare
    if (h_trnx_exp.data_type != h_trnx_act.data_type) success = 0;
    if (h_trnx_exp.trnx_id != h_trnx_act.trnx_id) success = 0;
    if (h_trnx_exp.trnx_type != h_trnx_act.trnx_type) success = 0;
    if(success <=0) {
      printf("\n  trnx_header loopback fail");
      msg = "server: trnx_exp";
      svcs_cs_print_trnx_header (&h_trnx_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: trnx_act";
      svcs_cs_print_trnx_header (&h_trnx_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    }
    else printf("\n trnx_header loopback pass");

    //data_header
    success =1;
    cs_data_header h_data_exp;
    //send
    h_data_exp.n_payloads = rand()%20;
    h_data_exp.trnx_payload_sizes = malloc(h_data_exp.n_payloads*sizeof(int));
    for(int i=0;i< h_data_exp.n_payloads;i++) {
      h_data_exp.trnx_payload_sizes[i]   = rand()%100;
    }
    if (svcs_cs_send_data_header(socket,&h_data_exp)<= 0) success = 0;
    //recv
    cs_data_header h_data_act;
    if (svcs_cs_recv_data_header(socket,&h_data_act)<= 0) success = 0;
    if (success == 0 )  printf("\n server data_header fail to recv");
    msg = "server: trnx_act recv";
    //compare
    if (h_data_exp.n_payloads != h_data_act.n_payloads) success = 0;
    else {
      for(int i=0;i<h_data_exp.n_payloads;i++) {
	if (h_data_exp.trnx_payload_sizes[i] != h_data_act.trnx_payload_sizes[i]) success = 0;
      }
    }
    if(success <=0) {
      printf("\n  data_header loopback fail");
      msg = "server: data_exp";
      svcs_cs_print_data_header (&h_data_exp,msg);
      msg = "server: data_act";
      svcs_cs_print_data_header (&h_data_act,msg);
    }
    else
    	printf("\n data_header loopback pass");
    ////////////////////////////////////////////////////
    // cs_header
    //send
    success =1;
    cs_header h_exp;
    
    h_exp.trnx.trnx_type = rand();
    h_exp.trnx.trnx_id   = rand();
    h_exp.trnx.data_type = svcs_cs_data_type_hash(SVCS_V_INT,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
    //
    h_exp.data.n_payloads = rand()%20;
    h_exp.data.trnx_payload_sizes = malloc(h_exp.data.n_payloads*sizeof(int));
    for(int i=0;i< h_exp.data.n_payloads;i++) {
      h_exp.data.trnx_payload_sizes[i]   = i;//rand()%100;
    }
    //send
    if (svcs_cs_send_header(socket,&h_exp)<= 0) success = 0;
    if (success == 0 )  printf("\ncs_header fail send");
    //recv
    cs_header   h_act;
    if (svcs_cs_recv_header(socket,&h_act)<= 0) success = 0;
    if (success == 0 )  printf("\ntrnx_header fail recv");
    //compare
    if (h_exp.trnx.data_type != h_act.trnx.data_type) success = 0;
    if (h_exp.trnx.trnx_id != h_act.trnx.trnx_id) success = 0;
    if (h_exp.trnx.trnx_type != h_act.trnx.trnx_type) success = 0;
    if (h_exp.data.n_payloads != h_act.data.n_payloads) success = 0;
    else {
      for(int i=0;i<h_exp.data.n_payloads;i++) {
	if (h_exp.data.trnx_payload_sizes[i] != h_act.data.trnx_payload_sizes[i]) success = 0;
      }
    }
    if(success <=0) {
      printf("\n  trnx_header loopback fail");
      msg = "server: h_exp";
      svcs_cs_print_header (&h_exp,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
      msg = "server: h_act";
      svcs_cs_print_header (&h_act,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
    }
    else printf("\n cs_header loopback pass");
    
    ////////////////////////////////////////////////
    //Int Test
    success =1;
    msg = "\n\nServer: Int Tests";
    puts(msg);

    //Int Array
    msg = "Server: 2D Int Array Test ";
    cs_data_header h_int_exp;
    cs_data_header h_int_act;

    const int col_n = 4;
    const int row_n = 3;
    int IntA_exp[row_n][col_n];
    int *IntA_act;
    int indx= 0;

    //send
    h_int_exp.n_payloads = row_n;
    h_int_exp.trnx_payload_sizes = malloc(h_data_exp.n_payloads*sizeof(int));

    for (int i = 0; i < row_n; i++) {
      for   (int j = 0; j < col_n; j++) {
	IntA_exp[i][j] = rand();//j+i*10;
	//printf("\nserver IntAexp[%0d][%0d]=%d",i,j,IntA_exp[isuccess = 0;][j]);
      }
    }
    for (int i = 0; i < row_n; i++) {
      h_int_exp.trnx_payload_sizes[i] =  col_n;
    }

    //svcs_cs_print_data_header (&h_int_exp,msg);
    //send
    if (svcs_cs_send_data_header(socket,&h_int_exp)<= 0) success = 0;
    if (success == 0 )  printf("\n server cs_header fail send");
    if (svcs_cs_send_int(socket,&h_int_exp,(int *)IntA_exp)<=0) success = 0;
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

    /*
    //set up header
      header.sockid = socket;
      header.trnx_id = rand();
      header.n_payloads = 1;
      header.trnx_payload_sizes[0]=n;
      header.trnx_type = svcs_cs_trnx_type_hash(SVCS_V_INT,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
      svcs_cs_print_header(&header,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);

      //send
      if (svcs_cs_send_header(&header)<= 0) success = 0;
      if (svcs_cs_send_int (&header,IntVexp)<= 0) success = 0;
      if (success == 0 )  printf("\nIntV loopback fail send");
      
      //recv
      if (svcs_cs_recv_header (&header)<= 0) success = 0;
      int sum =0;
      for(int i=0;i< header.n_payloads;i++) {
	sum = sum+header.trnx_payload_sizes[i];
      }
      int* IntVact;
       IntVact = malloc(sizeof(int)*sum);
       if (svcs_cs_recv_int  (&header,IntVact)<= 0) success = 0;
       if (success == 0 )  printf("\nIntV loopback fail recv");
       
       //compare
       if (sizeof(IntVexp) == sizeof(IntVact)) {
	 for (int i = 0; i < n; i++) {
	   if(IntVexp[i] != IntVact[i]) {
	     success = 0;
	     printf("\nIntV loopback fail IntVact[%0d]=%d intVexp=%d",i,IntVact[i],IntVact[i]);
	   }
	 }
       }
       if (success > 0 )  printf("\nintV loopback pass");
       else  printf("\nIntV loopback fail");
       */
///////////////////////////////////////////
//    int Array Test
//        success =1;
//        cs_header header_A;
//        const int col_n = 3;
//        const int row_n = 5;
//        int IntAexp[col_n][row_n];
       
//        //n = sizeof(IntAexp)/sizeof(IntAexp[0][0]);
//        //printf("\n IntAexp[7][13]; n=%0d",n);
       
//        for (int i = 0; i < col_n; i++) {
//        for   (int j = 0; j < row_n; j++) { IntAexp[i][j] = j+i*10;
// 	   printf("\nserver IntAexp[%0d][%0d]=%d",i,j,IntAexp[i][j]);
//        }
//        }
//        //set up header_A
//        //int *trnx_payload_size_ = malloc(sizeof(int)*col_n*row_n);
//        header_A.sockid = socket;
//        header_A.trnx_id = rand();
//        header_A.n_payloads = row_n;
//        //&header_A.trnx_payload_sizes = realloc(sizeof(int)*col_n*row_n);
//        for (int i=0;i<row_n;i++) {
//          header_A.trnx_payload_sizes[i]=col_n;
//          printf("\n header_A.trnx_payload_size[%0d] =%d",i,header_A.trnx_payload_sizes[i]);
//        }

//        header_A.trnx_type = svcs_cs_trnx_type_hash(SVCS_V_INT,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);//SVCS_A_STRUCTURE
//        svcs_cs_print_header(&header_A,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
//        //send
//        if (svcs_cs_send_header(&header)<= 0) success = 0;

//        //if (svcs_cs_send_int (&header,IntVexp)<= 0) success = 0;
//        //if (success == 0 )  printf("\nIntV loopback fail send");
       
//       ////////////////////////////////////////////
//     DOUBLEV Test
//       //success =1;
//       //Double Array
//       double DoubleVexp[17];
//       n = sizeof(DoubleVexp)/sizeof(DoubleVexp[0]);
//       for (int i = 0; i < n; i++) {
// 	DoubleVexp[i] = rand();
// 	//printf("\nserver DoubleVexp[%0d]=%f",i,DoubleVexp[i]);
//       }
      
//       //set up header
//       header.sockid = socket;
//       header.trnx_id = rand();
//       header.n_payloads = n;
//       header.trnx_type = SVCS_V_DOUBLE;
      
//       //send
//       if (svcs_cs_send_header(&header)<= 0) success = 0;
//       if (svcs_cs_send_doubleV (&header,DoubleVexp)<= 0) success = 0;
//       if (success == 0 )  printf("\nDoubleV loopback fail send");
//       //recv
//       if (svcs_cs_recv_header (&header)<= 0) success = 0;
//       double* DoubleVact;
//       DoubleVact = malloc(sizeof(double)*header.trnx_payload_size);
//       if (svcs_cs_recv_doubleV  (&header,DoubleVact)<= 0) success = 0;
//       if (success == 0 )  printf("\nDoubleV loopback fail recv");
      
//       //compare
//       if (sizeof(DoubleVexp) == sizeof(DoubleVact)) {
// 	for (int i = 0; i < n; i++) {
// 	  if(DoubleVexp[i] != DoubleVact[i]) {
// 	    success = 0;
// 	    printf("\nDoubleV loopback fail DoubleVact[%0d]=%f doubleVexp=%f",i,DoubleVact[i],DoubleVexp[i]);
// 	  }
// 	}
//       }
//       if (success > 0 )  printf("\ndoubleV loopback pass");
//       else  printf("\nDoubleV loopback fail");
      
//       //////////////////////////////////////////
      //    String Test
//       //success =1;
//       //String
//       const char *StringExp = "String Test send from  Server\0";
//       n = strlen(StringExp);
//       header.sockid = socket;
//       header.trnx_id = rand();
//       header.trnx_payload_size = n;
//       header.trnx_type = SVCS_V_STRING;
//       //send
//       if (svcs_cs_send_header(&header)<= 0) success = 0;
//       if (svcs_cs_send_string  (&header,StringExp)<= 0) success = 0;
//       header.trnx_type = SVCS_V_DOUBLE;

//       //recv
//       if (svcs_cs_recv_header (&header)<= 0) success = 0;
//      char* StringAct;
//      StringAct = malloc(sizeof(char)*header.trnx_payload_size);
//      if (svcs_cs_recv_string (&header,StringAct)<= 0) success = 0;
//        if (success == 0 )  printf("\nString loopback fail recv");
//       //compare
//        if (sizeof(StringExp) == sizeof(StringAct)) {
//        	for (int i = 0; i < n; i++) {
//        	  if(StringExp[i] != StringAct[i]) {
//        	    success = 0;
//        	    printf("\nString loopback fail StringAct[%0d]=%c StringExp[%0d]=%c",i,StringAct[i],i,StringExp[i]);
//        	  }
//        	}
//        }
//       if (success > 0 )  printf("\n String loopback pass");
//       else  printf("\nString loopback fail");

/////////////////////////////////////////////
      puts("\n\nctest_cs_server end");
    }

  if ( success >0)
    return EXIT_SUCCESS;
  else {
    return EXIT_FAILURE;
  }
}

