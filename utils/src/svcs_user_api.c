/* 
 =======svcs_cs==================================================
 File        : svcs_user_api.c
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
               See LICENSE file in the project root for full license information.  
 Description : User API  for 
               System Verilog client server handshake (SVCS)
******************************************************
 */

#ifndef SVCS_USER_API_C_
#define SVCS_USER_API_C_

#include "svcs_user_api.h"

int svcs_api_send    (int sockid,cs_header* h_trnx,...) {
  
  SVCV_INSTR_HASH_INDEX_DEFINE;
  
  cs_data_header * h_data_;

  int*           Int_;
  short int*     Short_;
  long  int*     Long_;
  svLogicVecVal* Integer_;
  svBitVecVal*   Bit_;
  svLogicVecVal* Reg_;
  double*        Double_;
  float*         Float_;
  char*          String_;

  va_list ap;
  char * msg ="\nsvcs_api_send";
  int Result_ = 1;
  int main_data_type_ = -1; 
  int data_type_      = -1;
  
  main_data_type_  =  svcs_cs_data_type(h_trnx->data_type,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
 
  if (main_data_type_ ==  SVCS_A_STRUCTURE) {
    
    va_start( ap, h_trnx);
    h_data_ = va_arg (ap, cs_data_header*);
    data_type_ = svcs_cs_data_type(h_data_->data_type,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
  }
  else {
    data_type_ = main_data_type_;
    va_start( ap,  h_trnx);
  }
  
  //svcs_cs_print_header (h_trnx,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //if (main_data_type_ ==  SVCS_A_STRUCTURE) 
  //svcs_cs_print_data_header (h_trnx,h_data_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  
  switch (data_type_) {

  case SVCS_SHORTINT: 
    Short_ = va_arg (ap,short int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_send_shortV(sockid,h_trnx,Short_);
    else   Result_ = svcs_cs_send_shortA(sockid,h_trnx->n_payloads,h_data_,Short_);
    break;
    
  case  SVCS_INT :
    Int_ = va_arg (ap,int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_send_intV(sockid,h_trnx,Int_);
    else   Result_ = svcs_cs_send_intA(sockid,h_trnx->n_payloads,h_data_,Int_);
    break;

  case SVCS_LONGINT: 
    Long_ = va_arg (ap,long int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_send_longV(sockid,h_trnx,Long_);
    else   Result_ = svcs_cs_send_longA(sockid,h_trnx->n_payloads,h_data_,Long_);
    break;
   
  case  SVCS_STRING:
  case  SVCS_BYTE:
    String_ = va_arg (ap,char* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE) Result_ = svcs_cs_send_byteV(sockid,h_trnx,String_);
    else   Result_ = svcs_cs_send_byteA(sockid,h_trnx->n_payloads,h_data_,String_);
    break;
   
   case  SVCS_BIT :
     Bit_ = va_arg (ap,svBitVecVal*);
     if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_send_bitN(sockid,h_trnx,Bit_);
     else   Result_ = svcs_cs_send_bitA(sockid,h_trnx->n_payloads,h_data_,Bit_);
     break;
   
  case SVCS_INTEGER: 
    Integer_ = va_arg (ap,svLogicVecVal* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_send_integerV(sockid,h_trnx,Integer_);
    else   Result_ = svcs_cs_send_integerA(sockid,h_trnx->n_payloads,h_data_,Integer_);
    break;
  
  case SVCS_REG: 
    Reg_ = va_arg (ap,svLogicVecVal* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_send_regN(sockid,h_trnx,Reg_);
    else   Result_ = svcs_cs_send_regA(sockid,h_trnx->n_payloads,h_data_,Reg_);
    break;
    
  case  SVCS_REAL :
    Double_ = va_arg (ap,double* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  {  Result_ = svcs_cs_send_doubleV(sockid,h_trnx,Double_);}
    else   Result_ = svcs_cs_send_doubleA(sockid,h_trnx->n_payloads,h_data_,Double_);
    break;
 
  case  SVCS_SHORTREAL :
    Float_ = va_arg (ap,float* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  {  Result_ = svcs_cs_send_floatV(sockid,h_trnx,Float_);}
    else   Result_ = svcs_cs_send_floatA(sockid,h_trnx->n_payloads,h_data_,Float_);
    break;     

  default :
    Result_ = 0;
    printf("Error: %s unknown data type",msg);
    break;
  }
  va_end(ap);
  return Result_;
  
}


int svcs_api_recv    (int sockid,cs_header* h_trnx,...) {
  SVCV_INSTR_HASH_INDEX_DEFINE;
  
  cs_data_header * h_data_;

  int*           Int_;
  short int*     Short_;
  long  int*     Long_;
  svLogicVecVal* Integer_;
  svBitVecVal*   Bit_;
  svLogicVecVal* Reg_;
  double*        Double_;
  float*         Float_;
  char*          String_;

  va_list ap;
  char * msg ="\nsvcs_api_recv";
  int Result_ = 1;
  int main_data_type_ = -1; 
  int data_type_      = -1;
  
  main_data_type_  =  svcs_cs_data_type(h_trnx->data_type,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
 
  if (main_data_type_ ==  SVCS_A_STRUCTURE) {
    
    va_start( ap, h_trnx);
    h_data_ = va_arg (ap, cs_data_header*);
    data_type_ = svcs_cs_data_type(h_data_->data_type,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY);
  }
  else {
    data_type_ = main_data_type_;
    va_start( ap,  h_trnx);
  }
  
  //svcs_cs_print_header (h_trnx,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //if (main_data_type_ ==  SVCS_A_STRUCTURE) 
  //svcs_cs_print_data_header (h_trnx,h_data_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  
  switch (data_type_) {

  case SVCS_SHORTINT: 
    Short_ = va_arg (ap,short int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_recv_shortV(sockid,h_trnx,Short_);
    else   Result_ = svcs_cs_recv_shortA(sockid,h_trnx->n_payloads,h_data_,Short_);
    break;
    
  case  SVCS_INT :
    Int_ = va_arg (ap,int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_recv_intV(sockid,h_trnx,Int_);
    else   Result_ = svcs_cs_recv_intA(sockid,h_trnx->n_payloads,h_data_,Int_);
    break;

  case SVCS_LONGINT: 
    Long_ = va_arg (ap,long int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_recv_longV(sockid,h_trnx,Long_);
    else   Result_ = svcs_cs_recv_longA(sockid,h_trnx->n_payloads,h_data_,Long_);
    break;
   
  case  SVCS_STRING:
  case  SVCS_BYTE:
    String_ = va_arg (ap,char* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE) Result_ = svcs_cs_recv_byteV(sockid,h_trnx,String_);
    else   Result_ = svcs_cs_recv_byteA(sockid,h_trnx->n_payloads,h_data_,String_);
    break;
   
   case  SVCS_BIT :
     Bit_ = va_arg (ap,svBitVecVal*);
     if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_recv_bitN(sockid,h_trnx,Bit_);
     else   Result_ = svcs_cs_recv_bitA(sockid,h_trnx->n_payloads,h_data_,Bit_);
     break;
   
  case SVCS_INTEGER: 
    Integer_ = va_arg (ap,svLogicVecVal* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_recv_integerV(sockid,h_trnx,Integer_);
    else   Result_ = svcs_cs_recv_integerA(sockid,h_trnx->n_payloads,h_data_,Integer_);
    break;
  
  case SVCS_REG: 
    Reg_ = va_arg (ap,svLogicVecVal* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_recv_regN(sockid,h_trnx,Reg_);
    else   Result_ = svcs_cs_recv_regA(sockid,h_trnx->n_payloads,h_data_,Reg_);
    break;
    
  case  SVCS_REAL :
    Double_ = va_arg (ap,double* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  {  Result_ = svcs_cs_recv_doubleV(sockid,h_trnx,Double_);}
    else   Result_ = svcs_cs_recv_doubleA(sockid,h_trnx->n_payloads,h_data_,Double_);
    break;
 
  case  SVCS_SHORTREAL :
    Float_ = va_arg (ap,float* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  {  Result_ = svcs_cs_recv_floatV(sockid,h_trnx,Float_);}
    else   Result_ = svcs_cs_recv_floatA(sockid,h_trnx->n_payloads,h_data_,Float_);
    break;     
    
  default :
    Result_ = 0;
    printf("Error: %s unknown data type",msg);
    break;
  }
  va_end(ap);
  return Result_; 
  
}
#endif





