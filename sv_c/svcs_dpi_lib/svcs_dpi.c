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
#include <svcs_client_server.c>
#include <svcs_user_api.c>

//--------------------
// TCP/IP socket init
//--------------------
unsigned int svcs_dpi_client_init(const unsigned int portno, const char *hostname) {
  int Result_ =0;
  Result_ = svcs_prim_init_tcpclient(portno,hostname);
  return Result_;
}


unsigned int svcs_dpi_server_init(const unsigned int portno) {
  int Result_ =0;
  Result_ =  svcs_prim_init_tcpserver(portno);
  return Result_;
}

//--------------------
// Direct send/recv  
//--------------------

int svcs_dpi_send_int(const  unsigned int sockfd, const int Int) {
  int Result_ =0;
  Result_ = svcs_prim_send_int(sockfd,&Int);
  return Result_;
}
int svcs_dpi_recv_int(const  unsigned int sockfd,int* Int) {
  int Result_ =0;
  Result_ =svcs_prim_recv_int(sockfd,Int);
  return Result_;
}

////Direct send/recv  
int svcs_dpi_send_byte(const  unsigned int sockfd, const char Byte) {
  int Result_ =0;
  Result_ = svcs_prim_send_byte(sockfd,&Byte);
  return Result_;
}
int svcs_dpi_recv_byte(const  unsigned int sockfd,char* Byte) {
  int Result_ =0;
  Result_ =svcs_prim_recv_byte(sockfd,Byte);
  return Result_;
}
////Direct send/recv  
int svcs_dpi_send_real(const  unsigned int sockfd,double Real) {
  int Result_ =0;
  Result_ =svcs_prim_send_double(sockfd,&Real);
  return Result_;
}
int svcs_dpi_recv_real(const  unsigned int sockfd,double* Real) {
  int Result_ =0;
  Result_ =svcs_prim_recv_double(sockfd,Real);
  return Result_;
}

////Direct send/recv  
int svcs_dpi_send_intV(int sockid, const int size,const svOpenArrayHandle Int){
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_intV:";
  
#ifndef C_TEST
  int* Int_= (int *) svGetArrayPtr(Int); 
#else
  int* Int_= (int *) Int;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_INT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //svcs_cs_print_intV(&h_,Int_,msg);
  Result_ = svcs_cs_send_intV(sockid,&h_,Int_);
  return Result_;
}

int svcs_dpi_recv_intV(int sockid,int size,svOpenArrayHandle Int) {
  cs_header h_;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_intV:";
#ifndef C_TEST
  int* Int_ = (int *) svGetArrayPtr(Int);
#else
  int* Int_= (int *) Int;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_INT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  Result_ = svcs_cs_recv_intV(sockid,&h_,Int_);
  //svcs_cs_print_intV(&h_,Int_,msg);
  return Result_;
}

void svcs_dpi_print_intV(cs_header* h,int *Int,char* msg) {

  svcs_cs_print_intV(h,Int,msg);
  //return Result_;
}

////Direct send/recv  
int svcs_dpi_send_realV(int sockid, const int size,const svOpenArrayHandle Real) {
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_realV:";
#ifndef C_TEST
  double* Real_ = (double *) svGetArrayPtr(Real);
#else
  int* Real_= (int *) Real;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_DOUBLE");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //svcs_cs_print_realV(&h_,Real_,msg);
  Result_ = svcs_cs_send_doubleV(sockid,&h_,Real_);
  return Result_;
}

int svcs_dpi_recv_realV(int sockid,int size,svOpenArrayHandle Real) {
  cs_header h_;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_realV:";
#ifndef C_TEST
  double* Real_ = (double *) svGetArrayPtr(Real);
#else
  int* Real_= (int *) Real;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_DOUBLE");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  Result_ = svcs_cs_recv_doubleV(sockid,&h_,Real_);
  //svcs_cs_print_realV(&h_,Real_,msg);
  return Result_;
}

////Direct send/recv  
int svcs_dpi_send_string(int sockid,int size,char* string) {
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_string: ";
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_BYTE");
  h_.n_payloads = strlen(string);
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //printf("before  %s string=%s of %d\n",msg,string,(int)strlen(string));
  Result_ = svcs_cs_send_byteV(sockid, &h_,string);
  return Result_;
}

int svcs_dpi_recv_string(int sockid,int size,char** string) {
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_string: ";
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_BYTE");
  h_.n_payloads = size;
  Result_ = svcs_cs_recv_byteV(sockid,&h_,*string);
  return Result_;
}


//--------------------
// HandShake(hs) send/recv
//--------------------
double svcs_dpi_hash(const char *str) {
  double Result_;
  Result_ = svcs_prim_hash(str);
  return Result_;
}
////  HandShake(hs) send/recv
int svcs_dpi_send_header         (int sockid,cs_header* h){
 int Result_ =0;
 Result_ = svcs_cs_send_header(sockid,h);
 return Result_;
}
int svcs_dpi_send_data_header    (int sockid,int n_payloads,cs_data_header* h){
 int Result_ =0;
 return Result_;
}
int svcs_dpi_recv_header         (int sockid,cs_header* h){
 int Result_ =0;
 Result_ = svcs_cs_recv_header(sockid,h);
 return Result_;
}
int svcs_dpi_recv_data_header    (int sockid,int n_payloads,cs_data_header* h){
 int Result_ =0;

 return Result_;
}

////  HandShake(hs) send/recv

int svcs_dpi_hs_send                (int sockid,cs_header* h_trnx,svOpenArrayHandle Array){
 int Result_ =0;
 Result_ = svcs_api_send (sockid,h_trnx,Array);
 return Result_;
}
int svcs_dpi_hs_send_byte (int sockid,cs_header* h_trnx,svOpenArrayHandle Array ){
  char* Byte_ = (char *) svGetArrayPtr(Array);
  return svcs_dpi_hs_send(sockid,h_trnx,Byte_);
}

int svcs_dpi_hs_send_int (int sockid,cs_header* h_trnx,svOpenArrayHandle Array ) {
 int* Int_ = (int *) svGetArrayPtr(Array);
  return svcs_dpi_hs_send(sockid,h_trnx,Int_);
}
int svcs_dpi_hs_send_real (int sockid,cs_header* h_trnx,svOpenArrayHandle Array ){
 double* Real_ = (double *) svGetArrayPtr(Array);
  return svcs_dpi_hs_send(sockid,h_trnx,Real_);
}

////  HandShake(hs) send/recv
int svcs_dpi_hs_recv (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array){
  int Result_ =0;
 Result_ = svcs_api_recv   (sockid,h_trnx,Array);
  return Result_;
}
int svcs_dpi_hs_recv_byte (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array ) {
 svOpenArrayHandle** Byte_ = svGetArrayPtr(Array);
 return svcs_dpi_hs_recv(sockid,h_trnx,Byte_);
}

int svcs_dpi_hs_recv_int (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array ) {
svOpenArrayHandle** Int_ = svGetArrayPtr(Array);
 return svcs_dpi_hs_recv(sockid,h_trnx,Int_);
}
int svcs_dpi_hs_recv_real (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array )  {
svOpenArrayHandle** Real_ = svGetArrayPtr(Array);
 return svcs_dpi_hs_recv(sockid,h_trnx,Real_);
}
#endif /* SVCS_DPI_C_ */
