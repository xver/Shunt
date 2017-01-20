
#include "svcs_primitives.c"
#include "../../includes/cs_common.h"

int main(void) {
	puts("\nctest_prim_client start");
    int socket;
    char *hostname;
    int port;
    int success;

    port = MY_PORT;
    hostname =   MY_HOST;
    //
    int Int;
    Int = 0xdeadbeaf;
	socket= svcs_prim_init_tcpclient(port,hostname);
	if (socket<0) {
			printf("ctest_prim_client::FATAL ERROR");
			return EXIT_FAILURE;
		}
	printf("ctest_prim_client::socket=%d\n", socket);
	puts("\nctest_prim_server start: Echo loopback client test start");
	success = 1;
    if (svcs_prim_recv_int(socket,&Int)<=0) success = 0;
    if (svcs_prim_send_int(socket,&Int)<=0) success = 0;
    if (success ==0 )printf("int loopback client fail\n");
	puts("ctest_prim_client end\n");
	return EXIT_SUCCESS;
}
