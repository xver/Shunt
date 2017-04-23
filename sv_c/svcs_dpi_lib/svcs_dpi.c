/*
 ============================================================================
 File        : svcs_dpi.c
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : svcs dpi bridge

               System Verilog client server handshake (SVCS) library
 ============================================================================
 */

#ifndef SVCS_DPI_C_
#define SVCS_DPI_C_

#include "svcs_dpi.h"
#include <svcs_primitives.c>

unsigned int svcs_dpi_client_init(const unsigned int portno, const char *hostname) {
int RESULT_ =0;
	RESULT_ = svcs_prim_init_tcpclient(portno,hostname);
return RESULT_;
}


unsigned int svcs_dpi_server_init(const unsigned int portno) {
	int RESULT_ =0;
	RESULT_ =  svcs_prim_init_tcpserver(portno);
	return RESULT_;
}

int svcs_dpi_send_int(const  unsigned int sockfd, const int Int) {
	int RESULT_ =0;
	RESULT_ = svcs_prim_send_int(sockfd,&Int);
	return RESULT_;
}

int svcs_dpi_recv_int(const  unsigned int sockfd,int* Int) {
	int RESULT_ =0;
	RESULT_ =svcs_prim_recv_int(sockfd,Int);
	return RESULT_;
}

int svcs_dpi_send_real(const  unsigned int sockfd,double Real) {
	int RESULT_ =0;
	RESULT_ =svcs_prim_send_double(sockfd,&Real);
	return RESULT_;
}

int svcs_dpi_recv_real(const  unsigned int sockfd,double* Real) {
	int RESULT_ =0;
	RESULT_ =svcs_prim_recv_double(sockfd,Real);
    return RESULT_;
}

#endif /* SVCS_DPI_C_ */
