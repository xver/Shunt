/* 
 ============================================================================
 File        : shunt_primitives.c
 Version     : 1.0.0
 Copyright (c) 2016-2017 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : target-initiator Primitives is a minimum set of the data exchage over TCP/IP base methods
                    
               System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)
 ============================================================================
 */

#ifndef  SHUNT_PRIMITIVES_C
#define  SHUNT_PRIMITIVES_C

#include "shunt_primitives.h"

////////////////////////////////////
//Common Functions 
////////////////////////////////////

double shunt_prim_hash(const char *str) {
  long hash = 5381;
  int c;
  
  while (( c = *str++) )
	  hash = (	(hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

void shunt_prim_error(char *msg) {
  extern int errno;
  if (errno==0) {
    printf(" ERROR: shunt_cs:: %s\n", msg);
  }
  else perror(msg);
  exit(1);
}

//////////////////////////////////
//TCP/IP Functions
//////////////////////////////////

int shunt_prim_init_initiator(const unsigned int portno) {
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  int targetlen; /* byte size of target's address */
  struct sockaddr_in initiatoraddr; /* initiator's addr */
  struct sockaddr_in targetaddr; /* target addr */
  struct hostent *hostp; /* target host info */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  
  
  //portno = MY_PORT;
  
  /*
   * socket: create the parent socket
   */
  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  if (parentfd < 0) {
	  shunt_prim_error("shunt_prim_init_initiator opening socket<0");
	  return parentfd ;
  }

  /* Eliminates "ERROR on binding: Address already in use" error.
   */
  optval = 1;
  setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));
  
  /*
   * build the initiator's Internet address
   */
  bzero((char *) &initiatoraddr, sizeof(initiatoraddr));
  
  /* this is an Internet address */
  initiatoraddr.sin_family = AF_INET;
  
  /* let the system figure out our IP address */
  initiatoraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  /* this is the port we will listen on */
  initiatoraddr.sin_port = htons((unsigned short)portno);
  
  /*
   * bind: associate the parent socket with a port
   */
  if (bind(parentfd, (struct sockaddr *) &initiatoraddr, sizeof(initiatoraddr)) < 0) shunt_prim_error("shunt_prim_init_initiator on binding");
  
  /*
   * listen: make this socket ready to accept connection requests
   */
  if (listen(parentfd, 5) < 0) /* allow 5 requests to queue up */ {
    shunt_prim_error("shunt_prim_init_initiator on listen");
    return -1 ;
  }
  /*
   * wait for a connection request
    */
  targetlen = sizeof(targetaddr);
  childfd = accept(parentfd, (struct sockaddr *) &targetaddr, (socklen_t *)&targetlen);
  
  if (childfd < 0) {
    shunt_prim_error("shunt_prim_init_initiator on accept");
    return childfd;
  }
  
  /*
   * gethostbyaddr: determine who sent the message
   */
  hostp = gethostbyaddr((const char *)&targetaddr.sin_addr.s_addr,
                        sizeof(targetaddr.sin_addr.s_addr), AF_INET);
  if (hostp == NULL) {
    shunt_prim_error("shunt_prim_init_initiator on gethostbyaddr");
    return -1;
  }

  hostaddrp = inet_ntoa(targetaddr.sin_addr);
  if (hostaddrp == NULL) {
    shunt_prim_error("shunt_prim_init_initiator on inet_ntoa\n");
    return -1;
  }
  else {
	  printf("initiator established connection with %s (%s)\n",
		 hostp->h_name, hostaddrp); }
  	  return childfd;
}

unsigned int shunt_prim_init_target(const unsigned int portno,const char *hostname) {
  int sockfd;
  struct sockaddr_in initiatoraddr;
  struct hostent *initiator;
  
  /* socket: create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    shunt_prim_error("shunt_prim_init_target opening socket<0");
    return -1;
  }
  /* gethostbyname: get the initiator's DNS entry */
  initiator = gethostbyname(hostname);
  if (initiator == NULL) {
    fprintf(stderr,"shunt_prim_init_target no such host as %s\n", hostname);
    return -1;
  }
  
  /* build the initiator's Internet address */
  bzero((char *) &initiatoraddr, sizeof(initiatoraddr));
  initiatoraddr.sin_family = AF_INET;
  bcopy((char *)initiator->h_addr,(char *)&initiatoraddr.sin_addr.s_addr, initiator->h_length);
  initiatoraddr.sin_port = htons(portno);
  
  /* connect: create a connection with the initiator */
  if (connect(sockfd, (struct sockaddr *)&initiatoraddr, sizeof(initiatoraddr)) < 0) {
    shunt_prim_error("shunt_prim_init_target connecting");
    return -1;
  }
  return sockfd;
}

//////////////////////////////////
//Data exchange primitives
/////////////////////////////////

int shunt_prim_send_short(const int sockfd,const short int* Short)
{
  int numbytes;

  numbytes = send(sockfd,Short, sizeof(short int), 0);
  if (numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_short : numbytes < 0 ");
  return numbytes;
}

int shunt_prim_recv_short    (const int sockfd, short int* Short)
{

  int numbytes;

  numbytes = recv(sockfd, Short,sizeof(short int) , 0);
  if (numbytes < 0) shunt_prim_error("\nERROR in shunt_prim_recv_short : numbytes < 0 ");
  return numbytes;
  }

int shunt_prim_send_int(const int sockfd,const int* Int)
{
  int numbytes;

  numbytes = send(sockfd,Int, sizeof(int), 0);
  if (numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_int : numbytes < 0 ");
  return numbytes;
}

int shunt_prim_recv_int    (const int sockfd, int* Int)
{
  
  int numbytes;
  
  numbytes = recv(sockfd, Int,sizeof(int) , 0);
  if (numbytes < 0) shunt_prim_error("\nERROR in shunt_prim_recv_int : numbytes < 0 ");
  return numbytes;
}

int shunt_prim_send_long(const int sockfd,const long int* Long)
{
  int numbytes;

  numbytes = send(sockfd,Long, sizeof(long int), 0);
  if (numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_long : numbytes < 0 ");
  return numbytes;
}

int shunt_prim_recv_long    (const int sockfd, long int* Long)
{
  
  int numbytes;

  numbytes = recv(sockfd, Long,sizeof(long int) , 0);
  if (numbytes < 0) shunt_prim_error("\nERROR in shunt_prim_recv_long : numbytes < 0 ");
  return numbytes;
}

int shunt_prim_send_double    (const int sockfd,const double* Double)
{
  
  int numbytes;
  numbytes = send(sockfd, Double, sizeof(double), 0);
  
  if (numbytes < 0) shunt_prim_error("ERROR shunt_cs_send_double: numbytes < 0 ");
  return numbytes;
}

int shunt_prim_send_float    (const int sockfd,const float* Float)
{

  int numbytes;
  numbytes = send(sockfd, Float, sizeof(float), 0);
  
  if (numbytes < 0) shunt_prim_error("ERROR shunt_cs_send_float: numbytes < 0 ");
  return numbytes;
}

int shunt_prim_recv_double    (const int sockfd,double* Double)
{
 int numbytes;
 
 numbytes = recv(sockfd, Double,sizeof(double) , 0);
 if (numbytes < 0) shunt_prim_error("ERROR in shunt_prim_recv_double : numbytes < 0 ");
 return numbytes;
}

int shunt_prim_recv_float    (const int sockfd,float* Float)
{
  int numbytes;
  
  numbytes = recv(sockfd, Float,sizeof(float) , 0);
  if (numbytes < 0) shunt_prim_error("ERROR in shunt_prim_recv_float : numbytes < 0 ");
  return numbytes;
}


int shunt_prim_send_byte(const int sockfd,const char* Byte)
{
  int numbytes;
  
  numbytes = send(sockfd,Byte, sizeof(char), 0);
  if (numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_byte : numbytes < 0 ");
  return numbytes;
}

int shunt_prim_recv_byte    (const int sockfd, char* Byte)
{
  
  int numbytes=0;

  numbytes = recv(sockfd, Byte,sizeof(char) , 0);
  if (numbytes < 0) {
    shunt_prim_error("\nERROR in shunt_prim_recv_byte : numbytes < 0 ");
    
  }
  
  return numbytes;
  }

int shunt_prim_send_integer (const unsigned int sockfd,const svLogicVecVal* Int) {
 int Result_;
 
 Result_ = 1;
 if (shunt_prim_send_int (sockfd,(int *)(&Int->aval))<=0) Result_=0 ;
 if (shunt_prim_send_int (sockfd,(int *)(&Int->bval))<=0) Result_=0 ;
 
 return Result_;
}

int shunt_prim_recv_integer (const unsigned int sockfd,svLogicVecVal* Int) {
  int Result_;
  Result_ = 1;
   
  if (shunt_prim_recv_int (sockfd,(int *)(&Int->aval))<=0) Result_=0 ;
  if (shunt_prim_recv_int (sockfd,(int *)(&Int->bval))<=0) Result_=0 ;
  
 return Result_;
}

#endif










