/* 
 ============================================================================
 Name        : svcs_client_server.h
 Author      : Victor Besyakov
 Version     : 0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : System Verilog client server handshake (SVCS)
******************************************************
Data Types:
elements:         integer,  double, char
vectors:          integers, doubles , string
array/composite:  integer vectors , double vectors, messages , structure
-------------------------------------------------------
trnx -> header  ->  trnx_atribute  - hash/random double
                    trnx_type      - hash double
                    trnx_id        - random double
        payload -> size - int , >0
                   data
 ============================================================================
 */
#ifndef SVCS_CLIENT_SERVER_H_
#define SVCS_CLIENT_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#define MY_HOST "localhost"
#define BUFSIZE   1024
#define MAXBUFLEN 1024

typedef enum {SVCS_V_INT,SVCS_V_DOUBLE,SVCS_V_STRING,SVCS_A_STRUCTURE} DPI_Exchange;
const char* DPI_Exchange_Instr_Names[] = {"SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING","SVCS_A_STRUCTURE"};

//-------------
//prototypes
//-------------
//Common
unsigned long svcs_hash(const char *str);
void *svcs_get_in_addr(struct sockaddr *sa);
void svcs_error(char *msg);
unsigned int  svcs_init_tcpserver(const unsigned int portno);
unsigned int  svcs_init_tcpclient(const unsigned int portno,char *hostname);

//Data exchange utilities
/*
-------------------------------------------------------
vector
element -> header ->   trnx_atribute - hash/random double
                       trnx_type     - hash ("SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING")
                       trnx_id       - random double
           payload ->  size - if vector >1, if element = 1;
                       data element;
---------------------------------------------------------------
*/
void  svcs_put_int        (const int sockfd,const int* Int);
int*  svcs_get_int        (const int sockfd);
//vector
void  svcs_put_intV      (const int sockfd,const int* Int,const int size);
int*  svcs_get_intV      (const int sockfd);

void  svcs_put_long       (const int sockfd,const long Long);
long* svcs_get_Long       (const int sockfd);
//vector
void  svcs_put_longV      (const int sockfd,const long Long,const int size);
long* svcs_get_longV      (const int sockfd);

void  svcs_put_string     (const int sockfd,const char *string);
char* svcs_get_string     (const int sockfd);
/*
 ---------------------------------------------------------------
array
composite -> header ->     trnx_atribute - hash/random double
                           trnx_type     - hash ("SVCS_A_STRUCTURE")
                           trnx_id       - random double
             payload->     size - int , > 1
                           data - vector
---------------------------------------------------------------
 */
//Array
void svcs_put_intA(const int sockfd,const int size,const int ArrayI[size]);
int* svcs_get_intA(const int sockfd,int ArrayI[MAXBUFLEN]);

void svcs_put_longA(const int sockfd,const int size,const double ArrayD[size]);
int* get_longA(const int sockfd,double ArrayD[MAXBUFLEN]);

int*  svcs_get_stringA(const int sockfd,char ArrayS[MAXBUFLEN][MAXBUFLEN]);
void  svcs_put_stringA(const int sockfd,const char ArrayS[MAXBUFLEN][MAXBUFLEN],const int size);



#endif
