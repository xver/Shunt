/* 
 ============================================================================
 File        : svcs_primitives.c
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : Client-Server Primitives is a minimum set of the data exchage over TCP/IP base methods
                    
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

//
//Common Functions 

unsigned long svcs_prim_hash(const char *str)
{
  unsigned long hash = 5381;
  int c;
  
  while ( c = *str++ )
    hash = (	(hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}
//
void svcs_prim_error {
  extern int errno;
  //printf("Value of errno: %d\n", errno);
  if (errno==0) {
    printf(" ERROR: svcs_cs:: %s\n", msg);
  }
  else perror(msg);
  exit(1);
}

//TCP/IP Functions
unsigned int svcs_prim_init_tcpserver(const unsigned int portno)
{
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  //int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  //char buf[BUFSIZE]; /* message buffer */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  
  
  //portno = MY_PORT;
  
  /*
   * socket: create the parent socket
   */
  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  if (parentfd < 0)
    error("ERROR opening socket");
  
  /* setsockopt: Handy debugging trick that lets
   * us rerun the server immediately after we kill it;
   * otherwise we have to wait about 20 secs.
   * Eliminates "ERROR on binding: Address already in use" error.
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
  if (bind(parentfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) error("ERROR on binding");
  
  /*
   * listen: make this socket ready to accept connection requests
   */
  if (listen(parentfd, 5) < 0) /* allow 5 requests to queue up */
    error("ERROR on listen");
  
  /*
   * main loop: wait for a connection request
    */
  clientlen = sizeof(clientaddr);
  childfd = accept(parentfd, (struct sockaddr *) &clientaddr, (socklen_t *)&clientlen);
  
  if (childfd < 0)
    error("ERROR on accept");
  
  /*
   * gethostbyaddr: determine who sent the message
   */
  hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                        sizeof(clientaddr.sin_addr.s_addr), AF_INET);
  if (hostp == NULL)
    error("ERROR on gethostbyaddr");
  hostaddrp = inet_ntoa(clientaddr.sin_addr);
  if (hostaddrp == NULL)
    error("ERROR on inet_ntoa\n");
  printf("server established connection with %s (%s)\n",
         hostp->h_name, hostaddrp);
  return childfd;
}

unsigned int svcs_prim_init_tcpclient(const unsigned int portno,const char *hostname) {
  int sockfd, n;
  struct sockaddr_in serveraddr;
  struct hostent *server;
  char buf[BUFSIZE];

  /* check command line arguments */
  
  //hostname = MY_HOST;
  //portno = MY_PORT;
  
  
  /* socket: create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  
  /* gethostbyname: get the server's DNS entry */
  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host as %s\n", hostname);
    exit(0);
  }
  
  /* build the server's Internet address */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,(char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(portno);
  
  /* connect: create a connection with the server */
  if (connect(sockfd, &serveraddr, sizeof(serveraddr)) < 0)
    error("ERROR connecting");
  return sockfd;
}

//Data exchange primitives
void svcs_prim_send_int    (const int sockfd,const int* Int) 
{
  cs_header header_;
  int numbytes;
  int Int_ =malloc(sizeof(int)); 
  Int_ = Int; 
  //printf("will send int(%d) of %d bytes\n",Int_,sizeof(int));
  numbytes = send(sockfd,&Int_, sizeof(int), 0);
  if (numbytes < 0)  error("put_int");
  free(Int_);
  
}

int* svcs_prim_recv_int    (const int sockfd)
{
  unsigned int numbytes;
  int* Int = (int*)malloc(sizeof(int));
  
  numbytes = recv(sockfd, &Int,sizeof(int) , 0);
  //printf("get int  (%0d) \n",Int);
  if (numbytes < 0) error("ERROR in get_int");
  return Int;
}

void svcs_prim_send_double    (const int sockfd,const double Double)
{
  int numbytes;
  numbytes = send(sockfd, &Double, sizeof(Double), 0);
  if (numbytes < 0) error("ERROR svcs_cs_send_double: numbytes < 0 ");
}


double* svcs_prim_recv_double    (const int sockfd)
{
  
  unsigned int numbytes;
  long* Double = (long*)malloc(sizeof(long));
  
  numbytes = recv(sockfd, &Double,sizeof(Double) , 0);
  if (numbytes < 0) error("ERROR in get_long");
  return Double;
}


#endif
