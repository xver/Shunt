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


int svcs_dpi_send_intV(int sockid, const int size,const svOpenArrayHandle Int){
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_intV:";
  int* Int_ = (int *) svGetArrayPtr(Int); 
  int RESULT_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_INT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //svcs_cs_print_intV(&h_,Int_,msg);
  RESULT_ = svcs_cs_send_intV(sockid,&h_,Int_);
  return RESULT_;
}

int svcs_dpi_recv_intV(int sockid,int size,svOpenArrayHandle Int) {
  cs_header h_;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_intV:";
  int* Int_ = (int *) svGetArrayPtr(Int); 
  int RESULT_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_INT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  RESULT_ = svcs_cs_recv_intV(sockid,&h_,Int_);
  //svcs_cs_print_intV(&h_,Int_,msg);
  return RESULT_;
}

void svcs_dpi_print_intV(cs_header* h,int *Int,char* msg) {
  cs_header* h_;
  int RESULT_ =0;
  svcs_cs_print_intV(h,Int,msg);
  //return RESULT_;
}


/////////////
int svcs_dpi_send_realV(int sockid, const int size,const svOpenArrayHandle Real) {
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_realV:";
  double* Real_ = (double *) svGetArrayPtr(Real);
  int RESULT_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_DOUBLE");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //svcs_cs_print_realV(&h_,Real_,msg);
  RESULT_ = svcs_cs_send_doubleV(sockid,&h_,Real_);
  return RESULT_;
}

int svcs_dpi_recv_realV(int sockid,int size,svOpenArrayHandle Real) {
  cs_header h_;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_realV:";
  double* Real_ = (double *) svGetArrayPtr(Real);
  int RESULT_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_DOUBLE");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  RESULT_ = svcs_cs_recv_doubleV(sockid,&h_,Real_);
  //svcs_cs_print_realV(&h_,Real_,msg);
  return RESULT_;
}

int svcs_dpi_comp_realV(cs_header* h,double *lhs,double *rhs) {
  cs_header* h_;
  int RESULT_ =0;
  //RESULT_ = svcs_cs_comp_realV(h,lhs,rhs);
  return RESULT_;
}

void svcs_dpi_print_realV(cs_header* h,double *Real,char* msg) {
  cs_header* h_;
  int RESULT_ =0;
  svcs_cs_print_doubleV(h,Real,msg);
  //return RESULT_;
}

int svcs_dpi_send_string(int sockid,const cs_header* h,const char* string) {
  cs_header* h_;
  int RESULT_ =0;
  RESULT_ = svcs_cs_send_string(sockid,h,string);
  return RESULT_;
}

int svcs_dpi_recv_string(int sockid,cs_header* h,char* string) {
  cs_header* h_;
  int RESULT_ =0;
  RESULT_ = svcs_cs_recv_string(sockid,h,string);
  return RESULT_;
}

int svcs_dpi_comp_string(cs_header* h,char *lhs,char *rhs) {
  cs_header* h_;
  int RESULT_ =0;
  RESULT_ = svcs_cs_comp_string(h,lhs,rhs);
  return RESULT_;
}


#endif /* SVCS_DPI_C_ */
