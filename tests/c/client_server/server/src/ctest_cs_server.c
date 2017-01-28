
#include "svcs_client_server.c"
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
  
  if (success>0) 
    {
      puts("\nctest_cs_server start: Echo loopback server test start");
      
      cs_header header;
      
      /*     INTV Test */
      
      header.sockid = socket;
      header.trnx_atribute = 56789.123;
      header.trnx_id = -12345;
      header.trnx_payload_size = 10;//TODO
      header.trnx_type = SVCS_V_INT;
      
      //Int Array
      int IntVexp[17];
      int n = sizeof(IntVexp)/sizeof(IntVexp[0]);
      
      for (int i = 0; i < n; i++) {
	IntVexp[i] = rand();
	 //printf("\nserver IntVexp[%0d]=%d",i,IntVexp[i]);
      }
      
      header.sockid = socket;
      header.trnx_id = -12345;
      header.trnx_payload_size = n;
      header.trnx_type = SVCS_V_INT;
      
      svcs_cs_send_header(&header);
      if (svcs_cs_send_intV (&header,IntVexp)<= 0) success = 0;
      if (success == 0 )  printf("\nIntV loopback fail send");
      
      svcs_cs_recv_header (&header);
      int* IntVact;
      IntVact = malloc(sizeof(int)*header.trnx_payload_size);
      if (svcs_cs_recv_intV  (&header,IntVact)<= 0) success = 0;
      if (success == 0 )  printf("\nIntV loopback fail recv");
      
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

      success =1;
      
      
      puts("\nctest_cs_server end\n");
    }

  if ( success >0)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}

