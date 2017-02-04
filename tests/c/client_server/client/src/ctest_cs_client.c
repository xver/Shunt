

#include "svcs_client_server.c"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\nctest_cs_client start");
  int socket;
  char *hostname;
  int port;
  int success=1;
  cs_header header;
  
  port = MY_PORT;
  hostname =   MY_HOST;
  //
  socket= svcs_prim_init_tcpclient(port,hostname);
  
  if (socket<0) {
    printf("\nctest_cs_client::FATAL ERROR");
    success=0;
  }
  printf("\nctest_cs_client::socket=%d", socket);
  
  if (success>0) {
    puts("\nctest_cs_client start: Echo loopback client test start");
    
    /*     INTV Test */
    success=1;
    header.sockid = socket;
    svcs_cs_recv_header (&header);
    svcs_cs_print_header(&header);
    
    int* IntV;
    IntV = malloc(sizeof(int)*header.trnx_payload_size);
    if (svcs_cs_recv_intV  (&header,IntV)<= 0) success = 0;
    if (success == 0 )  printf("\nIntV client fail recv");
    /*
    for (int i = 0; i < header.trnx_payload_size; i++) {
       	printf("\nserver IntV[%0d]=%d",i,IntV[i]);
          }
    */
    svcs_cs_send_header(&header);
    if (svcs_cs_send_intV (&header,IntV)<= 0) success = 0;
    if (success == 0 )  printf("\nIntV client fail send");
    /////////////////////////////////////
    /*     DOUBLEV Test */
    success=1;
    header.sockid = socket;
    svcs_cs_recv_header (&header);
    svcs_cs_print_header(&header);
    
    double* DoubleV;
    DoubleV = malloc(sizeof(double)*header.trnx_payload_size);
    if (svcs_cs_recv_doubleV  (&header,DoubleV)<= 0) success = 0;
    if (success == 0 )  printf("\nDoubleV client fail recv");
    /*
    for (int i = 0; i < header.trnx_payload_size; i++) {
       	printf("\nserver DoubleV[%0d]=%d",i,DoubleV[i]);
          }
    */
    svcs_cs_send_header(&header);
    if (svcs_cs_send_doubleV (&header,DoubleV)<= 0) success = 0;
    if (success == 0 )  printf("\nDoubleV client fail send");
    ////////////////////////////////////
    /*    String Test */
    success =1;
    //String

    svcs_cs_recv_header (&header);
    svcs_cs_print_header(&header);
    char* String;
    String = malloc(sizeof(char)*header.trnx_payload_size);
    if (svcs_cs_recv_string  (&header,String)<= 0) success = 0;
    printf("client string length(%0d) (%s) \n",header.trnx_payload_size,String);
     if (success == 0 )  printf("\nString client fail recv"); 
     svcs_cs_send_header(&header);
     if (svcs_cs_send_string (&header,String)<= 0) success = 0;
    if (success == 0 )  printf("\nString client fail send");
    ////////////////////////////////////
    puts("\nctest_cs_client end");
  }
  if ( success >0)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}
