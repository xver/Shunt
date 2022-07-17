/*
 =========================================================
 File        : shunt_user_api.c
 Version     : 1.0.0
 Copyright (c) 2016-2022 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description : User API  for
               System Verilog client server handshake (SHUNT TCP/IP SystemVerilog SHUNT)
******************************************************
 */

#ifndef SHUNT_USER_API_C_
#define SHUNT_USER_API_C_

#include "shunt_user_api.h"

INLINE int shunt_api_send    (int sockid,cs_header* h_trnx,...) {

  SHUNT_INSTR_HASH_INDEX_DEFINE;

  int*           Int_;
  short int*     Short_;
  shunt_long_t*     Long_;
  svLogicVecVal* Integer_;
  svBitVecVal*   Bit_;
  svLogicVecVal* Reg_;
  double*        Double_;
  float*         Float_;
  char*          String_;

  va_list ap;
  const char * msg ="\nshunt_api_send";
  int Result_ = 1;
  int main_data_type_ = -1;
  int data_type_      = -1;

  main_data_type_  =  shunt_cs_data_type(h_trnx->data_type,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);

  data_type_ = main_data_type_;
  va_start( ap,  h_trnx);

  switch (data_type_) {

  case SHUNT_SHORTINT:
    Short_ = va_arg (ap,short int* );
      Result_ = shunt_cs_send_shortV(sockid,h_trnx,Short_);
    break;

  case  SHUNT_INT :
    Int_ = va_arg (ap,int* );
      Result_ = shunt_cs_send_intV(sockid,h_trnx,Int_);
    break;

  case SHUNT_LONGINT:
    Long_ = va_arg (ap,shunt_long_t* );
      Result_ = shunt_cs_send_longV(sockid,h_trnx,Long_);
    break;

  case  SHUNT_STRING:
  case  SHUNT_BYTE:
    String_ = va_arg (ap,char* );
     Result_ = shunt_cs_send_byteV(sockid,h_trnx,String_);
    break;

   case  SHUNT_BIT :
     Bit_ = va_arg (ap,svBitVecVal*);
       Result_ = shunt_cs_send_bitN(sockid,h_trnx,Bit_);
     break;

  case SHUNT_INTEGER:
    Integer_ = va_arg (ap,svLogicVecVal* );
      Result_ = shunt_cs_send_integerV(sockid,h_trnx,Integer_);
    break;

  case SHUNT_REG:
    Reg_ = va_arg (ap,svLogicVecVal* );
      Result_ = shunt_cs_send_regN(sockid,h_trnx,Reg_);
    break;

  case  SHUNT_REAL :
    Double_ = va_arg (ap,double* );
    Result_ = shunt_cs_send_doubleV(sockid,h_trnx,Double_);
    break;

  case  SHUNT_SHORTREAL :
    Float_ = va_arg (ap,float* );
      Result_ = shunt_cs_send_floatV(sockid,h_trnx,Float_);
    break;

  default :
    Result_ = 0;
    printf("Error: %s unknown data type",msg);
    break;
  }
  va_end(ap);
  return Result_;
}


INLINE int shunt_api_recv    (int sockid,cs_header* h_trnx,...) {
  SHUNT_INSTR_HASH_INDEX_DEFINE;

  int*           Int_;
  short int*     Short_;
  shunt_long_t*     Long_;
  svLogicVecVal* Integer_;
  svBitVecVal*   Bit_;
  svLogicVecVal* Reg_;
  double*        Double_;
  float*         Float_;
  char*          String_;

  va_list ap;
  const char * msg ="\nshunt_api_recv";
  int Result_ = 1;
  int main_data_type_ = -1;
  int data_type_      = -1;

  main_data_type_  =  shunt_cs_data_type(h_trnx->data_type,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);

  data_type_ = main_data_type_;
  va_start( ap,  h_trnx);

  switch (data_type_) {

  case SHUNT_SHORTINT:
    Short_ = va_arg (ap,short int* );
      Result_ = shunt_cs_recv_shortV(sockid,h_trnx,Short_);
    break;

  case  SHUNT_INT :
    Int_ = va_arg (ap,int* );
      Result_ = shunt_cs_recv_intV(sockid,h_trnx,Int_);
    break;

  case SHUNT_LONGINT:
    Long_ = va_arg (ap,shunt_long_t* );
      Result_ = shunt_cs_recv_longV(sockid,h_trnx,Long_);
    break;

  case  SHUNT_STRING:
  case  SHUNT_BYTE:
    String_ = va_arg (ap,char* );
     Result_ = shunt_cs_recv_byteV(sockid,h_trnx,String_);
    break;

   case  SHUNT_BIT :
     Bit_ = va_arg (ap,svBitVecVal*);
       Result_ = shunt_cs_recv_bitN(sockid,h_trnx,Bit_);
     break;

  case SHUNT_INTEGER:
    Integer_ = va_arg (ap,svLogicVecVal* );
      Result_ = shunt_cs_recv_integerV(sockid,h_trnx,Integer_);
    break;

  case SHUNT_REG:
    Reg_ = va_arg (ap,svLogicVecVal* );
      Result_ = shunt_cs_recv_regN(sockid,h_trnx,Reg_);
    break;

  case  SHUNT_REAL :
    Double_ = va_arg (ap,double* );
      Result_ = shunt_cs_recv_doubleV(sockid,h_trnx,Double_);
    break;

  case  SHUNT_SHORTREAL :
    Float_ = va_arg (ap,float* );
      Result_ = shunt_cs_recv_floatV(sockid,h_trnx,Float_);
    break;

  default :
    Result_ = 0;
    printf("Error: %s unknown data type",msg);
    printf("\n%s h_trnx->data_type(%lu)",msg,(long)h_trnx->data_type);
    break;
  }
  va_end(ap);
  return Result_;
}

INLINE int shunt_pkt_send_longV  (int sockid, const cs_header* header,const shunt_long_t* LongV) {
  int  Result_     = 0;

  //long mem/array
  //pkt size: leader +  cs_header + input array
  int  size_       = sizeof(shunt_long_t)+sizeof(*header)+ header->n_payloads*sizeof(shunt_long_t);
  int  offset      = 0;

  //send array init
  shunt_long_t leader_        = shunt_prim_hash("shunt_cs_header_leader");
  shunt_long_t* send_arr_ = (shunt_long_t*)malloc(size_); // array to hold the result
  memset(send_arr_,0,size_);
  send_arr_[offset]   = leader_;
  offset++;
  //copy/allocate
  memcpy(&send_arr_[offset], header,sizeof(*header));
  memcpy(&send_arr_[sizeof(*header)/sizeof(shunt_long_t)+offset],LongV,header->n_payloads*sizeof(shunt_long_t));

  int numbytes_ = send(sockid,send_arr_,size_, 0);
  if(numbytes_ <= 0)  shunt_prim_error("\nERROR in  shunt_pkt_send_longV()  : numbytes < 0 ");
  else  Result_=numbytes_;

  free(send_arr_);
  return Result_;
}

INLINE int shunt_pkt_recv_longV  (int sockid, cs_header* header,shunt_long_t* LongV) {
  //
  //long mem/array
  //pkt size: leader +  cs_header + input array
  int  size_        = sizeof(shunt_long_t)+sizeof(*header)+sizeof(shunt_long_t)*header->n_payloads;
  int  offset       = 0;
  int  header_size_ = sizeof(*header)/sizeof(shunt_long_t);
  int numbytes_     = -1;
  //recive array init
  shunt_long_t leader_        = shunt_prim_hash("shunt_cs_header_leader");
  shunt_long_t* recv_arr_ = (shunt_long_t*)malloc(size_); // array to hold the result
  memset(recv_arr_,0,size_);

  //
  numbytes_ =  recv(sockid,recv_arr_ ,size_ , 0);

  if(numbytes_ <= 0) shunt_prim_error("\nERROR in shunt_api_rcv_pkt_longV : numbytes < 0 ");
  if(leader_ == recv_arr_[offset]) {
    offset= offset+1;
    memcpy(header,&recv_arr_[offset],sizeof(*header));
    offset = offset +header_size_;
    memcpy(LongV,&recv_arr_[offset],header->n_payloads*sizeof(shunt_long_t));
  }
  else printf("shunt_api_rcv_pkt_longV() get bad  header=%0ld\n", (long)recv_arr_[0] );
  free(recv_arr_ );
  return  numbytes_;
}
#endif





