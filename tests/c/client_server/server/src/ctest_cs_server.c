
#include "svcs_client_server.c"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\nctest_cs_server start");
  int  socket;
  int  port;
  int success = 1;
  cs_header header;

  header.sockid = rand();
  header.trnx_atribute = rand();
  header.trnx_id = rand();
  header.trnx_payload_size =rand();
  header.trnx_type = rand();
  
  port =       MY_PORT;
  socket= svcs_prim_init_tcpserver(port);
  if (socket<0) {
    printf("ctest_cs_server::FATAL ERROR");
    success = 0;
  }

  printf("\nctest_cs_server::socket=%d", socket);
  
  if (success>0) 
    {
      puts("\nctest_cs_server start: Echo loopback server test start");
      
      
      /*     INTV Test */
      success =1;
      //Int Array
      int IntVexp[17];
      int n = sizeof(IntVexp)/sizeof(IntVexp[0]);
      for (int i = 0; i < n; i++) {
	  IntVexp[i] = rand();
	 //printf("\nserver IntVexp[%0d]=%d",i,IntVexp[i]);
      }
      
      //set up header
      header.sockid = socket;
      header.trnx_id = rand();
      header.trnx_payload_size = n;
      header.trnx_type = SVCS_V_INT;
      
      //send
      if (svcs_cs_send_header(&header)<= 0) success = 0;
      if (svcs_cs_send_intV (&header,IntVexp)<= 0) success = 0;
      if (success == 0 )  printf("\nIntV loopback fail send");
      //recv
      if (svcs_cs_recv_header (&header)<= 0) success = 0;
      int* IntVact;
      IntVact = malloc(sizeof(int)*header.trnx_payload_size);
      if (svcs_cs_recv_intV  (&header,IntVact)<= 0) success = 0;
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
      
      ////////////////////////////////////////////
      /*     DOUBLEV Test */
      success =1;
      //Double Array
      double DoubleVexp[17];
      n = sizeof(DoubleVexp)/sizeof(DoubleVexp[0]);
      for (int i = 0; i < n; i++) {
	DoubleVexp[i] = rand();
	//printf("\nserver DoubleVexp[%0d]=%f",i,DoubleVexp[i]);
      }
      
      //set up header
      header.sockid = socket;
      header.trnx_id = rand();
      header.trnx_payload_size = n;
      header.trnx_type = SVCS_V_DOUBLE;
      
      //send
      if (svcs_cs_send_header(&header)<= 0) success = 0;
      if (svcs_cs_send_doubleV (&header,DoubleVexp)<= 0) success = 0;
      if (success == 0 )  printf("\nDoubleV loopback fail send");
      //recv
      if (svcs_cs_recv_header (&header)<= 0) success = 0;
      double* DoubleVact;
      DoubleVact = malloc(sizeof(double)*header.trnx_payload_size);
      if (svcs_cs_recv_doubleV  (&header,DoubleVact)<= 0) success = 0;
      if (success == 0 )  printf("\nDoubleV loopback fail recv");
      
      //compare
      if (sizeof(DoubleVexp) == sizeof(DoubleVact)) {
	for (int i = 0; i < n; i++) {
	  if(DoubleVexp[i] != DoubleVact[i]) {
	    success = 0;
	    printf("\nDoubleV loopback fail DoubleVact[%0d]=%f doubleVexp=%f",i,DoubleVact[i],DoubleVact[i]);
	  }
	}
      }
      if (success > 0 )  printf("\ndoubleV loopback pass");
      else  printf("\nDoubleV loopback fail");
     
      ///////////////////////////////////////////
      puts("\nctest_cs_server end\n");
    }

  if ( success >0)
    return EXIT_SUCCESS;
  else {
    return EXIT_FAILURE;
  }
}

