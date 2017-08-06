/* 
   ============================================================================
   File        : svcs_client_server.c
   Author      : Victor Besyakov
   Version     : 0.0.0
   Copyright (c) 2016 IC Verimeter. All rights reserved.  
   Licensed under the MIT License. 
   See LICENSE file in the project root for full license information.  
   Description : Client-Server utils   
   
   System Verilog client server handshake (SVCS)
   ******************************************************
   Data Types:
   elements:         integer,  double, char
   vectors:          integers, doubles , bytes(string)
   array/composite:  integer vectors , double vectors, messages , structure
   ============================================================================
*/

#ifndef  SVCS_CLIENT_SERVER_C_
#define  SVCS_CLIENT_SERVER_C_

#include "svcs_client_server.h"


//Data exchange utilities (header)


double svcs_cs_data_type_hash(int data_type,char* data_type_names[],int last_enum) {
  double result_ = -1;
  
  if ( data_type < last_enum+1 && data_type >= 0 ) {
    result_ = svcs_prim_hash(data_type_names[data_type]);
  }
  return result_;
};


int svcs_cs_data_type(double hash,char* trnx_type_names[],int last_enum) {
  int result_ = -1;
  int i =0;
  
  //printf("\nsvcs_cs_data_type n_=%0d",hash);
  while (i < last_enum+1 && result_ < 0) {
    double hash_ = svcs_prim_hash(trnx_type_names[i]);
    if (hash == hash_) result_ = i;
    //printf("\nsvcs_cs_data_type i= %0d hash_=%f hash = %f",i,hash_,hash);
    i++;
  }
  //printf("\n result_=%f",result_);
  return result_;
  
}


void svcs_cs_print_header (cs_header* h,char* data_type_names[],int last_enum,char* msg) {
  
  //printf("\n%s h->sockid\t(%0d)",msg,h->sockid);
  
  printf("\n%s h_trnx->trnx_type\t(%f)",msg,h->trnx_type);
  printf("\n%s h_trnx->trnx_id\t(%f)",msg,h->trnx_id);
  //
  int data_type_ = svcs_cs_data_type(h->data_type,data_type_names,last_enum);
  if (data_type_>=0)
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%f",msg,data_type_names[data_type_],data_type_,h->data_type);
  else
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%f",msg,"N/A",data_type_,h->trnx_type);
  printf("\n%s h_trnx->n_payloads\t(%0d)",msg,h->n_payloads);
  puts("\n");
  //
}

int svcs_cs_comp_header  (cs_header h_lhs,cs_header h_rhs) {
  int success = 1;
  if (h_lhs.data_type != h_rhs.data_type) success = 0;
  if (h_lhs.trnx_id   != h_rhs.trnx_id) success = 0;
  if (h_lhs.trnx_type != h_rhs.trnx_type) success = 0;
  if (h_lhs.n_payloads!= h_rhs.n_payloads) success = 0;
  return success;
}
int svcs_cs_comp_data_header (cs_data_header h_lhs,cs_data_header h_rhs,int n_payloads) {
  int success = 1;
  //compare
  if (h_lhs.data_type != h_rhs.data_type) success = 0;
  else {
    for(int i=0;i<n_payloads;i++) {
      if (h_lhs.trnx_payload_sizes[i] != h_rhs.trnx_payload_sizes[i]) success = 0;
    }
  }
  return success;
}

void svcs_cs_print_data_header (cs_header* h,cs_data_header* h_data,char* data_type_names[],int last_enum,char* msg) {
  
  int data_type_ = svcs_cs_data_type(h_data->data_type,data_type_names,last_enum);
  if (data_type_>=0)
    printf("\n%s h_data->data_type\t(%s )(%d)\thash=%f",msg,data_type_names[data_type_],data_type_,h_data->data_type);
  else
    printf("\n%s h_data->data_type\t(%s )(%d)\thash=%f",msg,"N/A",data_type_,h_data->data_type);
  
  for(int i=0;i<h->n_payloads;i++) {
    printf("\n%s h_data->trnx_payload_sizes[%0d]=%d",msg,i,h_data->trnx_payload_sizes[i]);
  }
  puts("\n");
}


int svcs_cs_send_header    (int sockid,cs_header* h) {
  int Result_=1;
  
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "svcs_cs_send_trnx_header";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (svcs_prim_send_double(sockid,&h->trnx_type)==0) Result_=0;
  if (svcs_prim_send_double(sockid,&h->trnx_id)==0)   Result_=0;
  if (svcs_prim_send_double(sockid,&h->data_type)==0) Result_=0;
  if (svcs_prim_send_int(sockid,&h->n_payloads)==0) Result_=0;
  return Result_;
}

int svcs_cs_send_data_header(int sockid,int n_payloads,cs_data_header* h) {
  int Result_=1;
  if (svcs_prim_send_double(sockid,&h->data_type)==0) Result_=0;
  for(int i=0;i<n_payloads;i++) {
    if (svcs_prim_send_int(sockid,&h->trnx_payload_sizes[i])==0) Result_=0;
  }
  return Result_;
}

int svcs_cs_recv_header   (int sockid,cs_header* h) {
  int Result_=1;

  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "svcs_cs_recv_trnx_header";
  if (svcs_prim_recv_double(sockid,&h->trnx_type)==0) Result_=0;
  if (svcs_prim_recv_double(sockid,&h->trnx_id)==0)   Result_=0;
  if (svcs_prim_recv_double(sockid,&h->data_type)==0) Result_=0;
  if (svcs_prim_recv_int(sockid,&h->n_payloads)==0) Result_=0;
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  return Result_;
}


int svcs_cs_recv_data_header   (int sockid,int n_payloads,cs_data_header* h) {
  
  int Result_=1;
  
  svcs_prim_recv_double(sockid,&h->data_type);
  
  for(int i=0;i<n_payloads;i++) {
    if (svcs_prim_recv_int(sockid,&h->trnx_payload_sizes[i])==0) Result_=0;
  }
  return Result_;
}

/////////////////////////////////////////
// Data exchange utilities (element/vector)

int svcs_cs_comp_intV   (cs_header* h,int *lhs,int *rhs) {
  int success = 1;
  //compare
  if (h->data_type==  svcs_prim_hash("SVCS_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      if(lhs[i] != rhs[i]) success = 0;
    }
  }
  return success;
}

void svcs_cs_print_intV   (cs_header* h,int *Int,char* msg) {
  if (h->data_type==  svcs_prim_hash("SVCS_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      printf("\n %s IntV[%0d]=%d",msg,i,Int[i]);
    }
  }
  puts("\n");
}


int svcs_cs_send_intV (int sockid,const cs_header* h,const int* Int) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_send_intV:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (h->data_type==  svcs_prim_hash("SVCS_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      //printf("\n %s IntV[%0d]=%d",msg,i,Int[i]);
      Result_ = svcs_prim_send_int(sockid,&Int[i]);
    }
  }
  return Result_;
}

int svcs_cs_send_shortV (int sockid,const cs_header* h,const short int * Short) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_send_shortV:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (h->data_type==  svcs_prim_hash("SVCS_SHORTINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      //printf("\n %s ShortV[%0d]=%d",msg,i,Short[i]);
      Result_ = svcs_prim_send_short(sockid,&Short[i]);
    }
  }
  return Result_;
}

int svcs_cs_send_longV (int sockid,const cs_header* h,const long int * Long) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_send_longV:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (h->data_type==  svcs_prim_hash("SVCS_LONGINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      //printf("\n %s LongV[%0d]=%d",msg,i,Long[i]);
      Result_ = svcs_prim_send_long(sockid,&Long[i]);
    }
  }
  return Result_;
}

int  svcs_cs_recv_intV    (int sockid,cs_header* h,int* Int) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_recv_intV:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (h->data_type == svcs_prim_hash("SVCS_INT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_recv_int(sockid,&Int[i]);
      //printf("\n %s IntV[%0d]=%d",msg,i,Int[i]);
    }
  }
  return Result_;
  
}

int  svcs_cs_recv_shortV    (int sockid,cs_header* h,short int* Shortint) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_recv_shortintV:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (h->data_type == svcs_prim_hash("SVCS_SHORTINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_recv_short(sockid,&Shortint[i]);
      //printf("\n %s ShortintV[%0d]=%d",msg,i,Shortint[i]);
    }
  }
  return Result_;
  
}

int  svcs_cs_recv_longV    (int sockid,cs_header* h,long int* Longint) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_recv_longintV:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (h->data_type == svcs_prim_hash("SVCS_LONGINT")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_recv_long(sockid,&Longint[i]);
      //printf("\n %s LongintV[%0d]=%d",msg,i,Longint[i]);
    }
  }
  return Result_;
  
}
// **********************************************
int svcs_cs_send_doubleV (int sockid,const cs_header* h,const double* Double) {
  int Result_=-1;
  
  if (h->data_type ==  svcs_prim_hash("SVCS_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_send_double(sockid,&Double[i]);
    }
  }
  return Result_;
}

int  svcs_cs_recv_doubleV    (int sockid,cs_header* h,double* Double) {
  int Result_=-1;
  
  if (h->data_type ==  svcs_prim_hash("SVCS_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_recv_double(sockid,&Double[i]);
    }
  }
  return Result_;
  
}
int svcs_cs_comp_doubleV   (cs_header* h,double *lhs,double *rhs) {
  int success = 1;
  if (h->data_type==  svcs_prim_hash("SVCS_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      if(lhs[i] != rhs[i]) success = 0;
    }
  }
  return success;
}
void svcs_cs_print_doubleV   (cs_header* h,double *Double,char* msg) {
  
  if (h->data_type==  svcs_prim_hash("SVCS_REAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      printf("\n %s DoubleV[%0d]=%f",msg,i,Double[i]);
    }
  }
}
// ******************************************************
///////////////////////////
int svcs_cs_send_floatV (int sockid,const cs_header* h,const float* Float) {
  int Result_=-1;
  
  if (h->data_type ==  svcs_prim_hash("SVCS_SHORTREAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_send_float(sockid,&Float[i]);
    }
  }
  return Result_;
}

int  svcs_cs_recv_floatV    (int sockid,cs_header* h,float* Float) {
  int Result_=-1;
  
  if (h->data_type ==  svcs_prim_hash("SVCS_SHORTREAL")) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_recv_float(sockid,&Float[i]);
    }
  }
  return Result_;
  
}
///////////////////////////
int svcs_cs_send_byteV   (int sockid,const cs_header* h,const char* byteV) {
	int Result_=-1;
	char B_ = 0;
	//SVCV_INSTR_HASH_INDEX_DEFINE;
	//char *msg = "svcs_cs_send_byteV:: ";
	//  svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
	  if (h->data_type==  svcs_prim_hash("SVCS_BYTE")) {
	    for (int i=0;i< h->n_payloads;i++) {
	      B_ = byteV[i];
	      //printf("\n %s B_[%0d]=%x(%c)",msg,i,B_,B_);
	      Result_ = svcs_prim_send_byte(sockid,&B_);
	    }
	  }
	  return Result_;
}

int svcs_cs_recv_byteV   (int sockid,cs_header* h,char* byteV) {
	 int Result_=-1;
	  char B_=0;
	  //SVCV_INSTR_HASH_INDEX_DEFINE;
	  //char *msg = "svcs_cs_recv_byteV:: ";
	  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
	  if (h->data_type == svcs_prim_hash("SVCS_BYTE")) {
	    for (int i=0;i< h->n_payloads;i++) {
	      Result_ = svcs_prim_recv_byte(sockid,&B_);
	      byteV[i] = B_;
	      //printf("\n %s byteV[%0d]=%x(%c)",msg,i,B_,B_);
	    }
	  }
	  return Result_;
}

int svcs_cs_comp_byteV   (cs_header* h,char *lhs,char *rhs) {
  int success = 1;
  if (h->data_type ==  svcs_prim_hash("SVCS_BYTEV")) {
    for (int i=0;i< h->n_payloads;i++) {
      if(lhs[i] != rhs[i]) success = 0;
    }
  }
  return success;
}


//Data exchange utilities (array)
int svcs_cs_send_intA (int sockid,int n_payloads,const cs_data_header* h,const int * Int) {
  
  int Result_= 1;
  int indx_ =0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      //printf("\n svcs_cs_send_int (%0d) Int[%0d][%0d]=%d",indx_,i,j,Int[indx_]);
      Result_ = svcs_prim_send_int(sockid,&Int[indx_]);
      indx_++;
    }
  }
  
  return Result_;
}


int  svcs_cs_recv_intA    (int sockid,int n_payloads,cs_data_header* h,int * Int) {
  int Result_= 1;
  
  int indx_ =0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      Result_ = svcs_prim_recv_int(sockid,&Int[indx_]);
      //printf("\n svcs_cs_resv_int (%0d) Int[%0d][%0d]=%d",indx_,i,j,Int[indx_]);
      indx_++;
    }
  }
  return Result_;
}

void  svcs_cs_print_intA   (int n_payloads,cs_data_header* h,int *Int,char* msg) {
  int indx=0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      printf("\n %s (%0d) IntA[%0d][%0d]=%d",msg,indx,i,j,Int[indx]);
      indx++;
    }
  }
  puts("\n");
}

int svcs_cs_comp_intA   (int n_payloads,cs_data_header* h,int *lhs,int *rhs){
  int success = 1;
  int indx=0;
  
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      if(lhs[indx] != rhs[indx]) success = 0;
      indx++;
    }
  }
  return success;
}


int svcs_cs_send_doubleA (int sockid,int n_payloads,const cs_data_header* h,const double * Double) {
  
  int Result_= 1;
  int indx_ =0;
  //printf("\n svcs_cs_send_double n_payloads=%0d",n_payloads);
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      //printf("\n svcs_cs_send_double (%0d) Double[%0d][%0d]=%f",indx_,i,j,Double[indx_]);
      double Double_ = Double[indx_];
      Result_ = svcs_prim_send_double(sockid,&Double_);
      indx_++;
    }
  }
  return Result_;
}


int  svcs_cs_recv_doubleA    (int sockid,int n_payloads,cs_data_header* h,double *Double) {
  int Result_= 1;
  
  int indx_ =0;
  //printf("\n svcs_cs_recv_double n_payloads=%0d",n_payloads);
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      double Double_;
      Result_ = svcs_prim_recv_double(sockid,&Double_);
      Double[indx_] = Double_;
      //printf("\n svcs_cs_recv_double (%0d) Double[%0d][%0d]=%f",indx_,i,j,Double_);//[indx_]);
      indx_++;
    }
  }
  
  return Result_;
}

void  svcs_cs_print_doubleA   (int n_payloads,cs_data_header* h,double *Double,char* msg) {
  int indx=0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      printf("\n %s (%0d) DoubleA[%0d][%0d]=%f",msg,indx,i,j,Double[indx]);
      indx++;
    }
  }
  puts("\n");
}

int svcs_cs_comp_doubleA   (int n_payloads,cs_data_header* h,double *lhs,double *rhs){
  int success = 1;
  //compare
  int indx=0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      if(lhs[indx] != rhs[indx]) success = 0;
      indx++;
    }
  }
  return success;
}

int svcs_cs_send_byteA(int sockid,int n_payloads,cs_data_header* h,const char*  ArrayS)
{
  int Result_= 1;
  int indx_ =0;
  printf("\n svcs_cs_send_byteA n_payloads=%0d",n_payloads);
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      printf("\n svcs_cs_send_byteA (%0d) ArrayS[%0d][%0d]=%x(%c)",indx_,i,j,ArrayS[indx_],ArrayS[indx_]);
      char Byte_ = ArrayS[indx_];
      Result_ = svcs_prim_send_byte(sockid,&Byte_);
      indx_++;
    }
  }
  return Result_;
}

int svcs_cs_recv_byteA(int sockid,int n_payloads,cs_data_header* h,char* ArrayS)
{
  int Result_= 1;
  
  int indx_ =0;
  printf("\n svcs_cs_recv_ByteA n_payloads=%0d",n_payloads);
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      char Byte_;
      Result_ = svcs_prim_recv_byte(sockid,&Byte_);
      ArrayS[indx_] = Byte_;
      printf("\n svcs_cs_recv_ByteA (%0d) ArrayS[%0d][%0d]=%x(%c)",indx_,i,j,Byte_,Byte_);//[indx_]);
      indx_++;
    }
  }
  
  return Result_;
}

void svcs_cs_print_byteA   (int n_payloads,cs_data_header* h,char *ArrayS,char* msg) {
  int indx_ =0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      printf("\n %s (%0d) ArrayS[%0d][%0d]=%d",msg,indx_,i,j,ArrayS[indx_]);
      indx_++;
    }
  }
  puts("\n");
}

int svcs_cs_comp_byteA   (int n_payloads,cs_data_header* h,char *lhs,char *rhs) {
  int success = 1;
  int indx=0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      if(lhs[indx] != rhs[indx]) success = 0;
      indx++;
    }
  }
  return success;
}

int svcs_cs_send_bitN (int sockid,const cs_header* h,const svBitVecVal* BitN) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_send_BitN:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  int Size_ =   h->n_payloads/ 32; 
  
  if(h->n_payloads % 32 > 0) ++Size_; 
  
  int* BitN_  = (int*) BitN;  
  
  if (h->data_type==  svcs_prim_hash("SVCS_BIT")) {
    for (int i=0;i<Size_;i++) {
      //printf("\n %s Bitn_[%0d]=%d",msg,i,BitN_[i]);
      Result_ = svcs_prim_send_int(sockid,&BitN_[i]);
    }
  }
  return Result_;
}

int svcs_cs_recv_bitN (int sockid,const cs_header* h,svBitVecVal* BitN) {
  int Result_=-1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char *msg = "svcs_cs_recv_BitN:: ";
  //svcs_cs_print_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  
  int Size_ =   h->n_payloads/ 32; 
  if(h->n_payloads % 32 > 0) ++Size_; 
  
  int* BitN_  = (int*) BitN;  
  
  if (h->data_type==  svcs_prim_hash("SVCS_BIT")) {
    for (int i=0;i<Size_;i++) {
      Result_ = svcs_prim_recv_int(sockid,&BitN_[i]);
      //printf("\n %s Bitn_[%0d]=%d",msg,i,BitN_[i]); 
    }
  }
  return Result_;
}
////////////
#endif


 
