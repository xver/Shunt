/*
 ============================================================================
 Name        : ctest_prim_client.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "svcs_primitives.c"
#include "../../includes/cs_common.h"

int main(void) {
	puts("\nctest_prim_client start");

    int socket;
    char *hostname;
    int port;
    port = MY_PORT;
    hostname =   MY_HOST;


	socket= svcs_prim_init_tcpclient(port,hostname);
	printf("ctest_prim_client::socket=%d\n", socket);
	puts("ctest_prim_client end\n");
	return EXIT_SUCCESS;
}
