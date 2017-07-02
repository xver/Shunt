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
  int* Int_;
  double* Double_;
  char* String_;
  va_list ap;
  //char * msg =" svcs_api_send ";
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
  
  switch(data_type_) {
    
  case  SVCS_INT :
    Int_ = va_arg (ap,int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_send_intV(sockid,h_trnx,Int_);
    else   Result_ = svcs_cs_send_intA(sockid,h_trnx->n_payloads,h_data_,Int_);
    break;
    
  case  SVCS_DOUBLE :
    Double_ = va_arg (ap,double* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  {  Result_ = svcs_cs_send_doubleV(sockid,h_trnx,Double_);}
    else   Result_ = svcs_cs_send_doubleA(sockid,h_trnx->n_payloads,h_data_,Double_);
    break;
    
  case  SVCS_BYTE:
    String_ = va_arg (ap,char* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE) Result_ = svcs_cs_send_byteV(sockid,h_trnx,String_);
    else   Result_ = svcs_cs_send_byteA(sockid,h_trnx->n_payloads,h_data_,String_);
    break;
    
    // default :
  }
  va_end(ap);
  return Result_;
  
}

int svcs_api_recv    (int sockid,cs_header* h_trnx,...) {
  
  SVCV_INSTR_HASH_INDEX_DEFINE;
  
  cs_data_header * h_data_;
  int* Int_;
  double* Double_;
  char* String_;
  va_list ap;
  //char * msg =" svcs_api_recv ";
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
  
  switch(data_type_) {

  case  SVCS_INT :
    Int_ = va_arg (ap,int* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  Result_ = svcs_cs_recv_intV(sockid,h_trnx,Int_);
    else   Result_ = svcs_cs_recv_intA(sockid,h_trnx->n_payloads,h_data_,Int_);
    break;
    
  case  SVCS_DOUBLE :
    Double_ = va_arg (ap,double* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE)  {  Result_ = svcs_cs_recv_doubleV(sockid,h_trnx,Double_);}
    else   Result_ = svcs_cs_recv_doubleA(sockid,h_trnx->n_payloads,h_data_,Double_);
    break;
    
  case  SVCS_BYTE:
    String_ = va_arg (ap,char* );
    if (main_data_type_ !=  SVCS_A_STRUCTURE) Result_ = svcs_cs_recv_byteV(sockid,h_trnx,String_);
    else   Result_ = svcs_cs_recv_byteA(sockid,h_trnx->n_payloads,h_data_,String_);
    break;
    
    // default :
  }
  va_end(ap);
  return Result_;

}
#endif





