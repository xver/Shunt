/*
 ============================================================================
 Name        : ctest_prim_server.c
 Author      : 
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include "svcs_primitives.c"
#include "../../include/cs_common.h"

int main(void) {
	puts("\nctest_prim_server start");

    int socket;
    int port;

    port =       MY_PORT;

	socket= svcs_prim_init_tcpserver(port);
	printf("ctest_prim_server::socket=%d\n", socket);
	puts("ctest_prim_server end\n");
	return EXIT_SUCCESS;
}
