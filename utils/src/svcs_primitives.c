/* 
 ============================================================================
 File        : svcs_primitives.c
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : Client-Server Primitives is a minimum set of the data exchage over TCP/hIP base methods
                    
               System Verilog client server handshake (SVCS)
******************************************************
Data Types: integer,  double
 ============================================================================
 */

#ifndef  SVCS_PRIMITIVES_C
#define  SVCS_PRIMITIVES_C

#include "svcs_primitives.h"

//-------------
//prototypes
//-------------

////////////////////////////////////
//Common Functions 

double svcs_prim_hash(const char *str) {
  long hash = 5381;
  int c;
  
  while (( c = *str++) )
	  hash = (	(hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

//
void svcs_prim_error(char *msg) {
  extern int errno;
  //printf("Value of errno: %d\n", errno);
  if (errno==0) {
    printf(" ERROR: svcs_cs:: %s\n", msg);
  }
  else perror(msg);
  exit(1);
}
//////////////////////////////////
//TCP/IP Functions

 int svcs_prim_init_tcpserver(const unsigned int portno) {
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  
  
  //portno = MY_PORT;
  
  /*
   * socket: create the parent socket
   */
  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  if (parentfd < 0) {
	  svcs_prim_error("svcs_prim_init_tcpserver opening socket<0");
	  return parentfd ;
  }

  /* Eliminates "ERROR on binding: Address already in use" error.
   */
  optval = 1;
  setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));
  
  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  
  /* this is an Internet address */
  serveraddr.sin_family = AF_INET;
  
  /* let the system figure out our IP address */
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  /* this is the port we will listen on */
  serveraddr.sin_port = htons((unsigned short)portno);
  
  /*
   * bind: associate the parent socket with a port
   */
  if (bind(parentfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) svcs_prim_error("svcs_prim_init_tcpserver on binding");
  
  /*
   * listen: make this socket ready to accept connection requests
   */
  if (listen(parentfd, 5) < 0) /* allow 5 requests to queue up */ {
    svcs_prim_error("svcs_prim_init_tcpserver on listen");
    return -1 ;
  }
  /*
   * main loop: wait for a connection request
    */
  clientlen = sizeof(clientaddr);
  childfd = accept(parentfd, (struct sockaddr *) &clientaddr, (socklen_t *)&clientlen);
  
  if (childfd < 0) {
    svcs_prim_error("svcs_prim_init_tcpserver on accept");
    return childfd;
  }
  
  /*
   * gethostbyaddr: determine who sent the message
   */
  hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                        sizeof(clientaddr.sin_addr.s_addr), AF_INET);
  if (hostp == NULL) {
    svcs_prim_error("svcs_prim_init_tcpserver on gethostbyaddr");
    return -1;
  }

  hostaddrp = inet_ntoa(clientaddr.sin_addr);
  if (hostaddrp == NULL) {
    svcs_prim_error("svcs_prim_init_tcpserver on inet_ntoa\n");
    return -1;
  }
  else
	  printf("server established connection with %s (%s)\n",
			  hostp->h_name, hostaddrp);
  	  return childfd;
}

unsigned int svcs_prim_init_tcpclient(const unsigned int portno,const char *hostname) {
  int sockfd;
  struct sockaddr_in serveraddr;
  struct hostent *server;
  
  /* socket: create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    svcs_prim_error("svcs_prim_init_tcpclient opening socket<0");
    return -1;
  }
  /* gethostbyname: get the server's DNS entry */
  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr,"svcs_prim_init_tcpclient no such host as %s\n", hostname);
    return -1;
  }
  
  /* build the server's Internet address */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,(char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(portno);
  
  /* connect: create a connection with the server */
  if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
    svcs_prim_error("svcs_prim_init_tcpclient connecting");
    return -1;
  }
  return sockfd;
}

//////////////////////////////////
//Data exchange primitives
int svcs_prim_send_int(const int sockfd,const int* Int)
{
  int numbytes;

  //printf("\nsvcs_prim_send_int:: will send int from addr %x=%x of %d bytes",Int,*Int,sizeof(int));
  numbytes = send(sockfd,Int, sizeof(int), 0);
  if (numbytes < 0)  svcs_prim_error("\nERROR in svcs_prim_send_int : numbytes < 0 ");
  return numbytes;
}

int svcs_prim_recv_int    (const int sockfd, int* Int)
{

  int numbytes;

  numbytes = recv(sockfd, Int,sizeof(int) , 0);
  //printf("\nsvcs_prim_recv_int::get int  (%x) of %0d bytes",*Int,numbytes);
  if (numbytes < 0) svcs_prim_error("\nERROR in svcs_prim_recv_int : numbytes < 0 ");
  return numbytes;
  }

int svcs_prim_send_double    (const int sockfd,const double* Double)
{

  int numbytes;
  //printf("\nsvcs_prim_send_double:Size of double pointer = %d addr = %d value=%f\n", sizeof(double),Double,*Double);
  numbytes = send(sockfd, Double, sizeof(double), 0);

  if (numbytes < 0) svcs_prim_error("ERROR svcs_cs_send_double: numbytes < 0 ");
  return numbytes;
}


int svcs_prim_recv_double    (const int sockfd,double* Double)
{
 int numbytes;
  
  numbytes = recv(sockfd, Double,sizeof(double) , 0);
  //printf("svcs_prim_recv_double::get Double  (%f) of %0d bytes\n",*Double,numbytes);
  if (numbytes < 0) svcs_prim_error("ERROR in svcs_prim_recv_double : numbytes < 0 ");
  return numbytes;
}


#endif
