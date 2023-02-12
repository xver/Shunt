/*
 ============================================================================
 File        : shunt_primitives.c
 Version     : 1.0.0
 Copyright (c) 2016-2023 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : target-initiator Primitives is a minimum set of the data exchage over TCP/IP base methods

               System Verilog target initiator handshake (TCP/IP SystemVerilog SHUNT)
 ============================================================================
 */

#ifndef  SHUNT_PRIMITIVES_C
#define  SHUNT_PRIMITIVES_C
#include "shunt_primitives.h"

#define on_error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

//Common Functions

INLINE shunt_long_t shunt_prim_hash(const char *str) {
  shunt_long_t hash = 5381;
  int c;

  while (( c = *str++) )
      hash = (  (hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

INLINE void shunt_prim_error(const char *msg) {
  #ifndef __cplusplus
  extern int errno;
  #endif
  if(errno==0) {
    printf(" ERROR: shunt_cs:: %s\n", msg);
  }
  else perror(msg);
  exit(1);
}

INLINE int  shunt_prim_rand_delay (int up, int low) {
  int delay = rand() % (up + low);
  struct timespec sleep_time;
  sleep_time.tv_sec = delay / 1000;
  sleep_time.tv_nsec = (delay % 1000) * 1000000;
  nanosleep(&sleep_time, NULL);
    // code to be executed after delay
    //none
    return(delay);
}
//TCP/IP Functions

INLINE unsigned int  shunt_prim_init_initiator(const unsigned int portno) {

  //portno = MY_PORT;
  unsigned int parentfd = -1;
  unsigned int childfd  = -1;
  //
  parentfd = shunt_prim_tcp_parent_init_initiator(portno);
  childfd  = shunt_prim_tcp_child_init_initiator(parentfd);
  //
  return  childfd;
}


INLINE unsigned int shunt_prim_tcp_parent_init_initiator(const unsigned int portno) {
  int parentfd; /* parent socket */
  int success;   
  char host[256];
  char *hostIP;
  struct hostent *host_entry;/*host info */
  
  struct sockaddr_in sin;
  socklen_t len;

  struct sockaddr_in initiatoraddr; /* initiator's addr */
  int optval; /* flag value for setsockopt */


  //portno = MY_PORT;
  parentfd = -1;
 
  /*
   * socket: create the parent socket
   */
  
   //
  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  
  if(parentfd < 0) {
      shunt_prim_error("shunt_prim_tcp_parent_init_initiator opening socket<0");
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
  success=0;
  int count =0;
  srand(time(NULL));
  int delay_sum=0;
  while (success==0 && count >=0 ) {
    if(bind(parentfd, (struct sockaddr *) &initiatoraddr, sizeof(initiatoraddr)) < 0)  {
      int delay;
      //shunt_prim_error("shunt_prim_tcp_parent_init_initiator on binding");
      delay=shunt_prim_rand_delay (SHUNT_DEFAULT_COLLISION_UP, SHUNT_DEFAULT_COLLISION_LOW);
      delay_sum =  delay_sum +delay; 
      count++;
      printf("\nCollision resolution of the occupied server TCP/IP port(%0d) on bind attempt(%0d) delay %0d msec",portno,count,delay);
      if(count>SHUNT_DEFAULT_COLLISION_ATTEMPT_LIMIT) count = -1;
    }
    else { 
      printf("\nSuccess: Collision resolution server connect TCP/IP port(%0d) attempt(%0d) total delay %0d msec",initiatoraddr.sin_port,count,delay_sum);
      success=1;
    }
  }
  if(success==0) { 
    shunt_prim_error("shunt_prim_tcp_parent_init_initiator on binding");
    parentfd = -1;
  }
 
  /*
   * listen: make this socket ready to accept connection requests
   */
  if(listen(parentfd, 5) < 0) /* allow 5 requests to queue up */ {
    shunt_prim_error("shunt_prim_tcp_parent_init_initiator on listen");
  }
  
  len = sizeof(sin); 
  
  if (getsockname(parentfd, (struct sockaddr *)&sin, &len) == -1)
    perror("getsockname");
  else {
    gethostname(host, sizeof(host)); //find the host name
    host_entry = gethostbyname(host); //find host information
    hostIP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
    printf("\nCurrent Host Name: %s\n", host);
    printf("Host IP: %s\n", hostIP);
    printf("parentfd=%d port number %d\n",parentfd ,ntohs(sin.sin_port));
  }
  return parentfd ;
}

INLINE unsigned int shunt_prim_tcp_child_init_initiator(const unsigned int parentfd ) {
  int childfd; /* child socket */
  int targetlen; /* byte size of target's address */
  struct sockaddr_in targetaddr; /* target addr */
  struct sockaddr_in sin; /* target addr */
  struct hostent *hostp; /* target host info */
  char *hostaddrp; /* dotted decimal host addr string */
  const char *hostname = "N/A";  /* host name */
  /*
   * wait for a connection request
   */
  targetlen = sizeof(targetaddr);

  childfd = -1;

  childfd = accept(parentfd, (struct sockaddr *) &targetaddr, (socklen_t *)&targetlen);
  if(childfd < 0) {
    shunt_prim_error("shunt_prim_tcp_child_init_initiator on accept");
  }

  /*
   * gethostbyaddr: determine who sent the message
   */
  hostp = gethostbyaddr((const char *)&targetaddr.sin_addr.s_addr,
                        sizeof(targetaddr.sin_addr.s_addr), AF_INET);
  if(hostp != NULL) {
    hostname = hostp->h_name;
  }

  hostaddrp = inet_ntoa(targetaddr.sin_addr);
  if(hostaddrp == NULL) {
    shunt_prim_error("shunt_prim_tcp_child_init_initiator on inet_ntoa\n");
    return -1;
  }
  else {
    socklen_t len = sizeof(sin);   
    getsockname(parentfd, (struct sockaddr *)&sin, &len);
    printf("\ninitiator established connection with Hostname(%s) IP(%s) Port(%d)\n",
           hostname, hostaddrp, ntohs(sin.sin_port)); }
  return childfd;
}

INLINE unsigned int shunt_prim_init_target(const unsigned int portno,const char *hostname) {
  int sockfd;
  struct sockaddr_in initiatoraddr;
  struct hostent *initiator;
  int success;

  /* socket: create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    shunt_prim_error("shunt_prim_init_target opening socket<0");
    return -1;
  }
  /* gethostbyname: get the initiator's DNS entry */
  initiator = gethostbyname(hostname);
  if(initiator == NULL) {
    fprintf(stderr,"shunt_prim_init_target no such host as %s\n", hostname);
    return -1;
  }

  /* build the initiator's Internet address */
  bzero((char *) &initiatoraddr, sizeof(initiatoraddr));
  initiatoraddr.sin_family = AF_INET;
  bcopy((char *)initiator->h_addr,(char *)&initiatoraddr.sin_addr.s_addr, initiator->h_length);
  initiatoraddr.sin_port = htons(portno);
  success=0;
  int count =0;
  int delay=0;
  int delay_sum=0;
  srand(time(NULL));
  while (success==0 && count >=0 ) 
    {
      /* connect: create a connection with the initiator */
      if(connect(sockfd, (struct sockaddr *)&initiatoraddr, sizeof(initiatoraddr)) < 0) {
        delay=shunt_prim_rand_delay (SHUNT_DEFAULT_COLLISION_UP, SHUNT_DEFAULT_COLLISION_LOW);
        delay_sum =  delay_sum +delay; 
        count++;
        printf("\nCollision resolution client connect TCP/IP port(%0d) on client connect  attempt(%0d) delay %0d msec",initiatoraddr.sin_port,count,delay);
        if(count>SHUNT_DEFAULT_COLLISION_ATTEMPT_LIMIT) count = -1;
      }
      else {
        printf("\nSuccess: Collision resolution client connect TCP/IP port(%0d) attempt(%0d) total delay %0d msec",initiatoraddr.sin_port,count,delay_sum);
        success=1;
      }
    }
  
  if(success==0) { 
    shunt_prim_error("shunt_prim_init_target connecting");
    sockfd = -1;
  }
  return sockfd;
}


INLINE int shunt_prim_get_status_socket(int fd,int event) {
  struct pollfd fds_;
  int time_;
  int Result_;

  Result_=-1;

  time_=0;
  fds_.events = POLLNVAL;

  fds_.fd    = fd;
  if(event==0)fds_.events =  POLLIN;
  if(event==1)fds_.events =  POLLOUT;

  if(fds_.events != POLLNVAL) {
    Result_ = poll(&fds_,1,time_);
    if(Result_ == POLLERR )    printf("POLL_ERR(%0d) Error on poll fd(%0d) ",Result_,fd);
  }
  return Result_;
}

INLINE void shunt_prim_unblock_socket(int flag, int sockfd) {
  int flags_in;
  int flags_out;

  flags_in = fcntl(sockfd, F_GETFL, 0);
  if(flags_in < 0) on_error("shunt_prim_unblock_socket() Could not get server socket flags: %s\n", strerror(errno))
  if(flag >  0)  flags_out =  flags_in |  O_NONBLOCK;
  if(flag == 0)  flags_out =  flags_in | ~O_NONBLOCK;
  if(fcntl(sockfd, F_SETFL, flags_out)<0)  on_error("shunt_prim_unblock_socket() Could set server socket: %s\n", strerror(errno));

  return;
}


INLINE void shunt_prim_tcp_nodelay_socket(int flag, int sockfd) {
  int err= setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (const char *)&flag, sizeof(int));
    if(err == -1){
       perror("setsockopt");
       exit(1);
     }
  return;
}


//ref to https://stackoverflow.com/questions/12730477/close-is-not-closing-socket-properly
INLINE int shunt_prim_get_socket_error(int fd) {
   int err = 1;
   socklen_t len = sizeof err;
   if(-1 == getsockopt(fd, SOL_SOCKET, SO_ERROR, (char *)&err, &len))
      shunt_prim_error("shunt_prim_get_socket_error");
   if(err)
      errno = err;              // set errno to the socket SO_ERROR
   return err;
}

INLINE void shunt_prim_close_socket(int fd) {
   if(fd >= 0) {
      shunt_prim_get_socket_error(fd); // first clear any errors, which can cause close to fail
      if(shutdown(fd, SHUT_RDWR) < 0) // secondly, terminate the 'reliable' delivery
         if(errno != ENOTCONN && errno != EINVAL) // SGI causes EINVAL
           shunt_prim_error("shutdown");
      if(close(fd) < 0) // finally call close()
        shunt_prim_error("close");
   }
   return;
}

//Data exchange primitives

INLINE int shunt_prim_send_short(const int sockfd,const short int* Short) {
  int numbytes;

  numbytes = send(sockfd,Short, sizeof(short int), 0);
  if(numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_short : numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_recv_short    (const int sockfd, short int* Short) {

  int numbytes;

  numbytes = recv(sockfd, Short,sizeof(short int) , 0);
  if(numbytes < 0) shunt_prim_error("\nERROR in shunt_prim_recv_short : numbytes < 0 ");
  return numbytes;
  }

INLINE int shunt_prim_send_int(const int sockfd,const int* Int) {
  int numbytes;

  numbytes = send(sockfd,Int, sizeof(int), 0);
  if(numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_int : numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_recv_int    (const int sockfd, int* Int) {

  int numbytes;

  numbytes = recv(sockfd, Int,sizeof(int) , 0);
  if(numbytes < 0) shunt_prim_error("\nERROR in shunt_prim_recv_int : numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_send_long(const int sockfd,const shunt_long_t* Long) {
  int numbytes;

  numbytes = send(sockfd,Long, sizeof(shunt_long_t), 0);
  if(numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_long : numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_recv_long    (const int sockfd, shunt_long_t* Long) {

  int numbytes;

  numbytes = recv(sockfd, Long,sizeof(shunt_long_t) , 0);
  if(numbytes < 0) shunt_prim_error("\nERROR in shunt_prim_recv_long : numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_send_double    (const int sockfd,const double* Double) {

  int numbytes;
  numbytes = send(sockfd, Double, sizeof(double), 0);
  if(numbytes < 0) shunt_prim_error("ERROR shunt_cs_send_double: numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_send_float    (const int sockfd,const float* Float) {

  int numbytes;
  numbytes = send(sockfd, Float, sizeof(float), 0);
  if(numbytes < 0) shunt_prim_error("ERROR shunt_cs_send_float: numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_recv_double    (const int sockfd,double* Double) {
 int numbytes;

 numbytes = recv(sockfd, Double,sizeof(double) , 0);
 if(numbytes < 0) shunt_prim_error("ERROR in shunt_prim_recv_double : numbytes < 0 ");
 return numbytes;
}

INLINE int shunt_prim_recv_float    (const int sockfd,float* Float) {
  int numbytes;

  numbytes = recv(sockfd, Float,sizeof(float) , 0);
  if(numbytes < 0) shunt_prim_error("ERROR in shunt_prim_recv_float : numbytes < 0 ");
  return numbytes;
}


INLINE int shunt_prim_send_byte(const int sockfd,const char* Byte) {
  int numbytes;

  numbytes = send(sockfd,Byte, sizeof(char), 0);
  if(numbytes < 0)  shunt_prim_error("\nERROR in shunt_prim_send_byte : numbytes < 0 ");
  return numbytes;
}

INLINE int shunt_prim_recv_byte    (const int sockfd, char* Byte) {

  int numbytes=0;

  numbytes = recv(sockfd, Byte,sizeof(char) , 0);
  if(numbytes < 0) {
    shunt_prim_error("\nERROR in shunt_prim_recv_byte : numbytes < 0 ");
  }

  return numbytes;
  }

INLINE int shunt_prim_send_integer (const unsigned int sockfd,const svLogicVecVal* Int) {
 int Result_;

 Result_ = 1;
 if(shunt_prim_send_int (sockfd,(int *)(&Int->aval))<=0) Result_=0 ;
 if(shunt_prim_send_int (sockfd,(int *)(&Int->bval))<=0) Result_=0 ;

 return Result_;
}

INLINE int shunt_prim_recv_integer (const unsigned int sockfd,svLogicVecVal* Int) {
  int Result_;
  Result_ = 1;

  if(shunt_prim_recv_int (sockfd,(int *)(&Int->aval))<=0) Result_=0 ;
  if(shunt_prim_recv_int (sockfd,(int *)(&Int->bval))<=0) Result_=0 ;

 return Result_;
}

#endif










