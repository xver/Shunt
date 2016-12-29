/*
** stat_cov_cocket_utils.h
*/
#ifndef STAT_COV_COCKET_UTILS_H_
#define STAT_COV_COCKET_UTILS_H_

#include "stat_cov_client_server.h"

#if 0
/*
 * Structs exported from in.h
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr;
};

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif

//-------------
//prototype
//-------------
void *get_in_addr(struct sockaddr *sa);
void error(char *msg);
//
void  put_string     (const int sockfd,const char *string);
char* get_string     (const int sockfd);

void  put_long       (const int sockfd,const long Long);
long* get_Long       (const int sockfd);

void  put_int        (const int sockfd,const int* Int);
int* get_int         (const int sockfd);
//
int*  get_stringArray(const int sockfd,char ArrayNtoC[MAXBUFLEN][MAXBUFLEN]);
void  put_stringArray(const int sockfd,const int size,const char ArrayNtoC[MAXBUFLEN][MAXBUFLEN]);
//
void put_intArray(const int sockfd,const int size,const int ArrayInt[size]);
int* get_intArray(const int sockfd,int ArrayInt[MAXBUFLEN]);
//
unsigned int  init_tcpserver(const unsigned int portno);
unsigned int  init_tcpclient(const unsigned int portno,char *hostname);
//
char buf[MAXBUFLEN];
//------------------
//FUNCTIONS
//------------------

// get sockaddr, IPv4 or IPv6:
/*
 * error - wrapper for perror
 */
void error(char *msg) {
  extern int errno;
  //printf("Value of errno: %d\n", errno);
  if (errno==0) {
   printf("DPI application Error : %s\n", msg);
  }
  else perror(msg);
  exit(1);
}

void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

//-------------
void put_string(const int sockfd,const char *str)
{
  
  int numbytes;
  int length = strlen(str);
  //intf("will send string  (%s) of %d bytes\n",str,length);
  put_int(sockfd,length);
  numbytes = send(sockfd, str,length, 0);
  if (numbytes<0) error("Error in put_str");
}

char* get_string(const int sockfd)
{
  int numbytes;
  char *buf_ = (char*) malloc(sizeof(char)*MAXBUFLEN);
  bzero(buf_, MAXBUFLEN);
  int* length = get_int(sockfd);
  numbytes = recv(sockfd, buf_,length, 0);
  printf("get string length(%0d) (%s) \n",length,buf_);
  if (numbytes < 0) error("ERROR in get_string");
  buf_[numbytes] = '\0';
  return buf_;
}

void put_long(const int sockfd,const long Long)
{
  int numbytes;
  numbytes = send(sockfd, &Long, sizeof(Long), 0);
  if (numbytes < 0) error("ERROR in put_long");
}

long* get_long(const unsigned int sockfd)
{
  
  unsigned int numbytes;
  long* Long = (long*)malloc(sizeof(long));
  
  numbytes = recv(sockfd, &Long,sizeof(Long) , 0);
  if (numbytes < 0) error("ERROR in get_long");
  return Long;
}

void put_int(const int sockfd,const int* Int)
{
  int numbytes;
  int Int_ =malloc(sizeof(int)); 
  Int_ = Int; 
  //printf("will send int(%d) of %d bytes\n",Int_,sizeof(int));
  numbytes = send(sockfd,&Int_, sizeof(int), 0);
  if (numbytes < 0)  error("put_int");
}

void put_intArray(const int sockfd,const int size,const int ArrayInt[size])
{
  int i=0;
  put_int(sockfd,size);
  for(i = 0 ; i < size; ++i){put_int(sockfd,ArrayInt[i]);}
}
int* get_intArray(const int sockfd,int ArrayInt[MAXBUFLEN])
{
  int i=0;
  int* size_ = get_int(sockfd);
  for (i=0;i<size_;i++) {ArrayInt[i] = get_int(sockfd);}
  return size_;
}

int* get_int(const int sockfd)
{
  unsigned int numbytes;
  int* Int = (int*)malloc(sizeof(int));
  
  numbytes = recv(sockfd, &Int,sizeof(int) , 0);
  //printf("get int  (%0d) \n",Int);
  if (numbytes < 0) error("ERROR in get_int");
  return Int;
}


void put_stringArray(const int sockfd,const int size,const char ArrayNtoC[MAXBUFLEN][MAXBUFLEN])
{
  int i=0;
  char *buf_ = (char*) malloc(sizeof(char)*MAXBUFLEN);
  bzero(buf_, MAXBUFLEN);
  int size_ = size;
  put_int(sockfd,size_);
  for(i = 0 ; i < size_; ++i)
    {
      //printf("put_string:size(%0d) Array ArrayNtoC[%0d]=%s\n",size_,i,ArrayNtoC[i]);
      put_string(sockfd,ArrayNtoC[i]);
      }
}

int* get_stringArray(const int sockfd,char ArrayNtoC[MAXBUFLEN][MAXBUFLEN])
{
  int i=0;
  char *buf_ = (char*) malloc(sizeof(char)*MAXBUFLEN);
  bzero(buf_, MAXBUFLEN);
  int* size_ = get_int(sockfd);
  printf("get_string:size(%0d) ",size_);
  for (i=0;i<size_;i++)
    {
      buf_ = get_string(sockfd);
      strcpy(ArrayNtoC[i],buf_);
    }
  printf(" %s \n",buf_);
  return size_;
}
//-------------------
unsigned int  init_tcpclient(const unsigned int portno,char *hostname) {
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
//--------------------
unsigned int  init_tcpserver(const unsigned int portno) {
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  //int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buffer */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */
  
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
   * main loop: wait for a connection request, echo input line,
   * then close connection.
   */
  clientlen = sizeof(clientaddr);
  // while (1) {
  
  /*
   * accept: wait for a connection request
   */
  childfd = accept(parentfd, (struct sockaddr *) &clientaddr, &clientlen);
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
//--------------------
#endif  /*STAT_COV_COCKET_UTILS_H_*/

 
