/* 
   ============================================================================
   File        : shunt_client_server.c
   Version     : 1.0.0
   Copyright (c) 2016-2017 IC Verimeter. All rights reserved.  
   Licensed under the MIT License. 
   See LICENSE file in the project root for full license information.  
   Description : Target-Initiator (Client-Server aka cs) handshake utils    
   System Verilog client server handshake (TCP/IP SystemVerilog SHUNT)
   ============================================================================
*/

#ifndef  SHUNT_CLIENT_SERVER_C_
#define  SHUNT_CLIENT_SERVER_C_

#include "shunt_client_server.h"


//Data exchange utilities (header)

long shunt_cs_data_type_hash(long data_type,char* data_type_names[],int last_enum) {
  long result_ = -1;
  
  if ( data_type < last_enum+1 && data_type >= 0 ) {
    result_ = shunt_prim_hash(data_type_names[data_type]);
  }
  return result_;
};

int shunt_cs_data_type(long hash,char* trnx_type_names[],int last_enum) {
  int result_ = -1;
  int i =0;
  
  while (i < last_enum+1 && result_ < 0) {
    long hash_ = shunt_prim_hash(trnx_type_names[i]);
    if (hash == hash_) result_ = i;
    i++;
  }
  return result_;
};

void shunt_cs_print_header (cs_header* h,char* data_type_names[],int last_enum,char* msg) {
  
  printf("\n%s h_trnx->trnx_type\t(%lu)",msg,h->trnx_type);
  printf("\n%s h_trnx->trnx_id\t(%lu)",msg,h->trnx_id);
  //
  int data_type_ = shunt_cs_data_type(h->data_type,data_type_names,last_enum);
  if (data_type_>=0)
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%lu",msg,data_type_names[data_type_],data_type_,h->data_type);
  else
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%lu",msg,"N/A",data_type_,h->trnx_type);
  printf("\n%s h_trnx->n_payloads\t(%0d)",msg,h->n_payloads);
  puts("\n");
  //
}

void shunt_cs_print_data_header (cs_header* h,cs_data_header* h_data,char* data_type_names[],int last_enum,char* msg) {
  
  int data_type_ = shunt_cs_data_type(h_data->data_type,data_type_names,last_enum);
  if (data_type_>=0)
    printf("\n%s h_data->data_type\t(%s )(%d)\thash=%lu",msg,data_type_names[data_type_],data_type_,h_data->data_type);
  else
    printf("\n%s h_data->data_type\t(%s )(%d)\thash=%lu",msg,"N/A",data_type_,h_data->data_type);
  
  for(int i=0;i<h->n_payloads;i++) {
    printf("\n%s h_data->trnx_payload_sizes[%0d]=%d",msg,i,h_data->trnx_payload_sizes[i]);
  }
  puts("\n");
}

int shunt_cs_send_header    (int sockid,cs_header* h) {
  int Result_=1;
  
  if (shunt_prim_send_long(sockid,&h->trnx_type)==0) Result_=0;
  if (shunt_prim_send_long(sockid,&h->trnx_id)==0)   Result_=0;
  if (shunt_prim_send_long(sockid,&h->data_type)==0) Result_=0;
  if (shunt_prim_send_int(sockid,&h->n_payloads)==0) Result_=0;
  return Result_;
}

int shunt_cs_send_data_header(int sockid,int n_payloads,cs_data_header* h) {
  int Result_=1;
  if (shunt_prim_send_long(sockid,&h->data_type)==0) Result_=0;
  for(int i=0;i<n_payloads;i++) {
    if (shunt_prim_send_int(sockid,&h->trnx_payload_sizes[i])==0) Result_=0;
  }
  return Result_;
}

int shunt_cs_recv_header   (int sockid,cs_header* h) {
  int Result_=1;
  
  if (shunt_prim_recv_long(sockid,&h->trnx_type)==0) Result_=0;
  if (shunt_prim_recv_long(sockid,&h->trnx_id)==0)   Result_=0;
  if (shunt_prim_recv_long(sockid,&h->data_type)==0) Result_=0;
  if (shunt_prim_recv_int(sockid,&h->n_payloads)==0) Result_=0;
  
  return Result_;
}

int shunt_cs_recv_data_header   (int sockid,int n_payloads,cs_data_header* h) {
  
  int Result_=1;
  
  shunt_prim_recv_long(sockid,&h->data_type);
  
  for(int i=0;i<n_payloads;i++) {
    if (shunt_prim_recv_int(sockid,&h->trnx_payload_sizes[i])==0) Result_=0;
  }
  return Result_;
}

// Data exchange utilities (element/vector)

int shunt_cs_send_intV (int sockid,const cs_header* h,const int* Int) {
  int Result_=-1;
  if (h->data_type==  shunt_prim_hash("SHUNT_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_send_int(sockid,&Int[i]);
    }
  }
  return Result_;
}

int shunt_cs_send_shortV (int sockid,const cs_header* h,const short int * Short) {
  int Result_=-1;
  if (h->data_type==  shunt_prim_hash("SHUNT_SHORTINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_send_short(sockid,&Short[i]);
    }
  }
  return Result_;
}

int shunt_cs_send_longV (int sockid,const cs_header* h,const long int * Long) {
  int Result_=-1;
  if (h->data_type==  shunt_prim_hash("SHUNT_LONGINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_send_long(sockid,&Long[i]);
    }
  }
  return Result_;
}

int shunt_cs_send_doubleV (int sockid,const cs_header* h,const double* Double) {
  int Result_=-1;
  
  if (h->data_type ==  shunt_prim_hash("SHUNT_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_send_double(sockid,&Double[i]);
    }
  }
  return Result_;
}

int shunt_cs_send_floatV (int sockid,const cs_header* h,const float* Float) {
  int Result_=-1;
  if (h->data_type ==  shunt_prim_hash("SHUNT_SHORTREAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_send_float(sockid,&Float[i]);
    }
  }
  return Result_;
}

int shunt_cs_send_byteV   (int sockid,const cs_header* h,const char* byteV) {
  int Result_=-1;
  char B_ = 0;
  if (h->data_type==  shunt_prim_hash("SHUNT_BYTE" )|| h->data_type==  shunt_prim_hash("SHUNT_STRING")) {
    for (int i=0;i< h->n_payloads;i++) {
      B_ = byteV[i];
      Result_ = shunt_prim_send_byte(sockid,&B_);
    }
  }
  return Result_;
}

int shunt_cs_send_integerV (int sockid,const cs_header* h,const svLogicVecVal* IntegerV) {
  int Result_=-1;
  int Size_ =   h->n_payloads;
  
  if (h->data_type==  shunt_prim_hash("SHUNT_INTEGER")) {
    for (int i=0;i<Size_;i++) {
      Result_ = shunt_prim_send_integer(sockid,&IntegerV[i]);
    }
  }
  return Result_;
}

int shunt_cs_send_regN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  int Result_;
  
  Result_ = 1;
  svLogicVecVal* Reg_ =  (svLogicVecVal* )Reg;
  
  int Size_ =h_trnx->n_payloads / 32; 
  if(h_trnx->n_payloads % 32 > 0) ++Size_;
  
  for(int i=0;i<Size_ ;i++) {
    int* Aval_ = (int*)&(Reg_[i].aval);
    int* Bval_ = (int*)&(Reg_[i].bval);
    if (shunt_prim_send_int(sockfd,Aval_)<=0) Result_=0;
    if (shunt_prim_send_int(sockfd,Bval_)<=0) Result_ =0;
  }
  return Result_;
}

int shunt_cs_send_bitN (int sockid,const cs_header* h,const svBitVecVal* BitN) {
  int Result_=-1;
  int Size_ =   h->n_payloads/ 32; 
  
  if(h->n_payloads % 32 > 0) ++Size_; 
  
  int* BitN_  = (int*) BitN;  
  
  if (h->data_type==  shunt_prim_hash("SHUNT_BIT")) {
    for (int i=0;i<Size_;i++) {
      Result_ = shunt_prim_send_int(sockid,&BitN_[i]);
    }
  }
  return Result_;
}

//////////////////////////////////////////

int  shunt_cs_recv_intV    (int sockid,cs_header* h,int* Int) {
  int Result_=-1;
  if (h->data_type == shunt_prim_hash("SHUNT_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_int(sockid,&Int[i]);
    }
  }
  return Result_;
}

int  shunt_cs_recv_shortV    (int sockid,cs_header* h,short int* Shortint) {
  int Result_=-1;
  if (h->data_type == shunt_prim_hash("SHUNT_SHORTINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_short(sockid,&Shortint[i]);
    }
  }
  return Result_;
}

int  shunt_cs_recv_longV    (int sockid,cs_header* h,long int* Longint) {
  int Result_=-1;
  if (h->data_type == shunt_prim_hash("SHUNT_LONGINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_long(sockid,&Longint[i]);
    }
  }
  return Result_;
}


int  shunt_cs_recv_doubleV    (int sockid,cs_header* h,double* Double) {
  int Result_=-1;
  
  if (h->data_type ==  shunt_prim_hash("SHUNT_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_double(sockid,&Double[i]);
    }
  }
  return Result_;
}


int  shunt_cs_recv_floatV    (int sockid,cs_header* h,float* Float) {
  int Result_=-1;
  
  if (h->data_type ==  shunt_prim_hash("SHUNT_SHORTREAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_float(sockid,&Float[i]);
    }
  }
  return Result_;
}

int shunt_cs_recv_byteV   (int sockid,cs_header* h,char* byteV) {
  int Result_=-1;
  char B_=0;
  if (h->data_type == shunt_prim_hash("SHUNT_BYTE" )|| h->data_type == shunt_prim_hash("SHUNT_STRING")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_byte(sockid,&B_);
      byteV[i] = B_;
    }
  }
  return Result_;
}

int shunt_cs_recv_bitN (int sockid,const cs_header* h,svBitVecVal* BitN) {
  int Result_=-1;
  int Size_ =   h->n_payloads/ 32; 
  if(h->n_payloads % 32 > 0) ++Size_; 
  
  int* BitN_  = (int*) BitN;  
  
  if (h->data_type==  shunt_prim_hash("SHUNT_BIT")) {
    for (int i=0;i<Size_;i++) {
      Result_ = shunt_prim_recv_int(sockid,&BitN_[i]);
    }
  }
  return Result_;
}


int shunt_cs_recv_integerV (int sockid,const cs_header* h,svLogicVecVal* IntegerV) {
  int Result_=-1;
  int Size_ =   h->n_payloads; 
  
  if (h->data_type==  shunt_prim_hash("SHUNT_INTEGER")) {
    for (int i=0;i<Size_;i++) {
      Result_ = shunt_prim_recv_integer(sockid,&IntegerV[i]);
    }
  }
  return Result_;
}

int shunt_cs_recv_regN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
  int Result_;
  Result_ = 1;
  svLogicVecVal* Reg_ =  Reg;
  
  int Size_ =h_trnx->n_payloads / 32; 
  if(h_trnx->n_payloads % 32 > 0) ++Size_;
  
  for(int i=0;i<Size_ ;i++) { 
    if (shunt_prim_recv_int(sockfd,(int *)&(Reg_[i].aval))<=0) Result_=0 ; 
    if (shunt_prim_recv_int(sockfd,(int *)&(Reg_[i].bval))<=0) Result_=0 ; 
  } 
  
  return Result_; 
}

#endif


 
