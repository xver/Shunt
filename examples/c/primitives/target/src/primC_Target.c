/*
============================================================================
    File        : prim_CTarget.c
    Version     : 1.0.0
   Copyright (c) 2016-2017 IC Verimeter. All rights reserved.
   Licensed under the MIT License.
   See LICENSE file in the project root for full license information.
   Description :  TCP/IP SystemVerilog SHUNT
                  An example of primitive functions -Target(Client)
   */

#include <shunt_primitives.h>
#include "../../includes/cs_common.h"

int main(void) {
  puts("\nexample_prim_target start");
  int socket;
  char *hostname;
  int port;
  int success=1;
  
  port = MY_PORT;
  hostname =   MY_HOST;
  //
  socket= shunt_prim_init_target(port,hostname);
  if (socket<0) {
    printf("\nexample_prim_target::FATAL ERROR");
    success=0;
  }
  printf("\nexample_prim_target::socket=%d", socket);

  if (success>0) {
    puts("\nexample_prim_target start: Echo loopback target example start");
    
    //INT Example
    int Int;
    Int = 0xdeadbeaf;
    if (shunt_prim_recv_int(socket,&Int)<=0) success = 0;
    if (shunt_prim_send_int(socket,&Int)<=0) success = 0;
    if (success ==0 )printf("\nint loopback target fail");
    puts("\nexample_prim_target end");

    //Double Example
    double Double;
    Double = -1;

    if (shunt_prim_recv_double(socket,&Double)<=0) success = 0;
    if (shunt_prim_send_double(socket,&Double)<=0) success = 0;
    if (success ==0 ) printf("\ndouble loopback target fail");

    ////////
    //Byte Example
    char Byte;
    Byte = '$';

    if (shunt_prim_recv_byte(socket,&Byte)<=0) success = 0;
    if (shunt_prim_send_byte(socket,&Byte)<=0) success = 0;
    if (success ==0 ) printf("\nbyte loopback target fail");
    ////////
  }
  if ( success >0)
    return EXIT_SUCCESS;
  else 
    return EXIT_FAILURE;
}
