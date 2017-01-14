/*
 ============================================================================
 Name        : ctest_prim_client.c
 Author      : 
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */


#include "svcs_primitives.c"
#include "../../include/cs_common.h"

int main(void) {

	puts("\nctest_prim_client start");

	char *hostname;
	int port;
    int socket;

	port =       MY_PORT;
	hostname =   MY_HOST;

	socket = svcs_prim_init_tcpclient(port,hostname);
	printf("ctest_prim_client::socket=%d\n", socket);
	puts("ctest_prim_client end\n");
	return EXIT_SUCCESS;
}
