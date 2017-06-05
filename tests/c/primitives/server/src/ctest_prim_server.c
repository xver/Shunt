
/*
============================================================================
   File        : ctest_user_prim_server.c
   Author      : Victor Besyakov
   Version     : 0.0.0
   Copyright (c) 2016 IC Verimeter. All rights reserved.
   Licensed under the MIT License.
   See LICENSE file in the project root for full license information.
   Description : ctest server
   System Verilog client server handshake (SVCS)
   */
#include "svcs_primitives.c"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\nctest_prim_server start");
  int  socket;
  int  port;
  int success = 1;
  
  port =       MY_PORT;
  socket= svcs_prim_init_tcpserver(port);
  if (socket<0) {
    printf("ctest_prim_server::FATAL ERROR");
    success = 0;
  }
  printf("\nctest_prim_server::socket=%d", socket);
  
  if (success>0) {
    puts("\nctest_prim_server start: Echo loopback server test start");
  
    //INT test
    int Int = 0xaa5555aa;
    int IntLoopBack = 0x5a5a5a5a;
    if(svcs_prim_send_int(socket,&Int)       <=0 ) success = 0;
    if(svcs_prim_recv_int(socket,&IntLoopBack)<=0) success = 0;
    if (IntLoopBack == Int && success >0)
      printf("\nint loopback pass");
    else {
      success = 0;
      printf("\nint loopback fail %x != %x \n",IntLoopBack,Int);
    }

    //DOUBLE Test
    double Double = -1234567;
    double DoubleLoopBack = 9101112;
    if(svcs_prim_send_double(socket,&Double)       <= 0 ) success = 0;
    if(svcs_prim_recv_double(socket,&DoubleLoopBack)<= 0) success = 0;
    
    if (DoubleLoopBack == Double && success >0)
      printf("\ndouble loopback pass");
    else {
      success = 0;
      printf("\ndouble loopback fail %f != %f \n",DoubleLoopBack,Double);
    }

    char Byte = 'C';
    char ByteLoopBack = 'b';
    if(svcs_prim_send_byte(socket,&Byte)       <= 0 ) success = 0;
    if(svcs_prim_recv_byte(socket,&ByteLoopBack)<= 0) success = 0;
    
    if (ByteLoopBack == Byte && success >0)
        printf("\nbyte loopback pass");
    else {
      success = 0;
      printf("\nbyte loopback fail %c != %c \n",ByteLoopBack,Byte);
    }
    ///////

    puts("\nctest_prim_server end\n");
  }

  if ( success >0)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}

