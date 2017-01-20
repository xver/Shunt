
#include "svcs_primitives.c"
#include "../../includes/cs_common.h"

int main(void) {
	puts("\nctest_prim_server start");
    int  Int;
    int  IntLoopBack;
    int  socket;
    int  port;
    int success;
    port =       MY_PORT;


	socket= svcs_prim_init_tcpserver(port);
	if (socket<0) {
		printf("ctest_prim_server::FATAL ERROR");
		return EXIT_FAILURE;
	}
	printf("ctest_prim_server::socket=%d\n", socket);

	puts("\nctest_prim_server start: Echo loopback server test start");

	success = 1;
	Int = 0xaa5555aa;
	IntLoopBack = 0x5a5a5a5a;
	if(svcs_prim_send_int(socket,&Int)       <=0 ) success = 0;
	if(svcs_prim_recv_int(socket,&IntLoopBack)<=0) success = 0;

	if (IntLoopBack == Int & success >0)
		printf("int loopback pass\n",IntLoopBack,Int);
	else
		printf("int loopback fail %x != %x \n",IntLoopBack,Int);

	puts("ctest_prim_server end\n");
	return EXIT_SUCCESS;

}

