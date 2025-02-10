
/*
============================================================================
  Title: primC_Initiator.c
  
   Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description :  TCP/IP SystemVerilog SHUNT
                  An example of primitive functions -Initiator(server)
*/
#include "shunt_primitives.h"
#include "../../includes/cs_common.h"

int main(void) {
  puts("\nexample_prim_initiator start");
  int  socket;
  int  port;
  int success = 1;

  port =       MY_PORT;
  socket= shunt_prim_init_initiator(port);
  if (socket<0) {
    printf("example_prim_initiator::FATAL ERROR");
    success = 0;
  }
  printf("\nexample_prim_initiator::socket=%d", socket);

  if (success>0) {
    puts("\nexample_prim_initiator start: Echo loopback initiator example start");

    //INT example
    int Int = 0xaa5555aa;
    int IntLoopBack = 0x5a5a5a5a;
    if(shunt_prim_send_int(socket,&Int)       <=0 ) success = 0;
    if(shunt_prim_recv_int(socket,&IntLoopBack)<=0) success = 0;
    if (IntLoopBack == Int && success >0)
      printf("\nint loopback pass");
    else {
      success = 0;
      printf("\nint loopback fail %x != %x \n",IntLoopBack,Int);
    }

    //DOUBLE Example
    double Double = -1234567;
    double DoubleLoopBack = 9101112;
    if(shunt_prim_send_double(socket,&Double)       <= 0 ) success = 0;
    if(shunt_prim_recv_double(socket,&DoubleLoopBack)<= 0) success = 0;

    if (DoubleLoopBack == Double && success >0)
      printf("\ndouble loopback pass");
    else {
      success = 0;
      printf("\ndouble loopback fail %f != %f \n",DoubleLoopBack,Double);
    }

    char Byte = 'C';
    char ByteLoopBack = 'b';
    if(shunt_prim_send_byte(socket,&Byte)       <= 0 ) success = 0;
    if(shunt_prim_recv_byte(socket,&ByteLoopBack)<= 0) success = 0;

    if (ByteLoopBack == Byte && success >0)
        printf("\nbyte loopback pass");
    else {
      success = 0;
      printf("\nbyte loopback fail %c != %c \n",ByteLoopBack,Byte);
    }

    puts("\nexample_prim_initiator end\n");
  }

  if ( success >0)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

