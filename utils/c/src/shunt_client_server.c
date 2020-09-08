/* 
   ============================================================================
   File        : shunt_client_server.c
   Version     : 1.0.0
   Copyright (c) 2016-2020 IC Verimeter. All rights reserved.  
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
  
  printf("\n%s h_trnx->trnx_type\t(%lx)",msg,h->trnx_type);
  printf("\n%s h_trnx->trnx_id\t(%lx)",msg,h->trnx_id);
  
  int data_type_ = shunt_cs_data_type(h->data_type,data_type_names,last_enum);
  if (data_type_>=0)
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%lx",msg,data_type_names[data_type_],data_type_,h->data_type);
  else
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%lx",msg,"N/A",data_type_,h->trnx_type);
  printf("\n%s h_trnx->n_payloads\t(%0lu)",msg,h->n_payloads);
  puts("\n");
  
  return;
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
  return;
}

int shunt_cs_send_header    (int sockid,cs_header* h) {
  int Result_=0;
  long send_arr[(sizeof(*h) + sizeof(long int))/sizeof(long int)];
  int numbytes;
      
  send_arr[0] = shunt_prim_hash("shunt_cs_header_leader");
  memcpy(&send_arr[1], h,sizeof(*h));
  numbytes = send(sockid,send_arr,sizeof(*h) + sizeof(long int), 0);
  if (numbytes <= 0)  shunt_prim_error("\nERROR in  shunt_cs_send_header : numbytes < 0 ");
  else  Result_=1; 

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
  int  Result_=1;
  long int leader_in;
  long int leader_ref; 
  long recv_arr[(sizeof(*h) + sizeof(long int))/sizeof(long int)];
  int  numbytes=0;

  numbytes = recv(sockid,recv_arr ,sizeof(*h) + sizeof(long int), 0);
  if (numbytes<0)   shunt_prim_error("\nERROR in shunt_cs_recv_header : numbytes < 0 ");
  Result_ = numbytes; 

  leader_in     = recv_arr[0];
  leader_ref = shunt_prim_hash("shunt_cs_header_leader");
  if ( Result_ > 0 && (leader_in == leader_ref)) {
    memcpy(h,&recv_arr[1],sizeof(*h));
  }
  else { 
    Result_ =-1;
    printf("\nshunt_cs_recv_header() get bad  header (%lx)(Ref. to %lx) numbytes=%0d \n", leader_in,leader_ref,numbytes);
    for (int i=0;i<(sizeof(*h) + sizeof(long int))/sizeof(long int);i++) printf("error shunt_cs_recv_header() recv_arr[%0d]=(%ld)%lx\n",i,recv_arr[i],recv_arr[i]);
  }
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
    Result_ = send(sockid,Int, h->n_payloads*sizeof(int), 0);
  }
  return Result_;
}

int shunt_cs_send_shortV (int sockid,const cs_header* h,const short int * Short) {
  int Result_=-1;
  if (h->data_type==  shunt_prim_hash("SHUNT_SHORTINT")) {
    Result_ = send(sockid,Short, h->n_payloads*sizeof(int), 0);
  }
  return Result_;
}

int shunt_cs_send_longV (int sockid,const cs_header* h,const long int * Long) {
  int Result_=-1;
  if (h->data_type==  shunt_prim_hash("SHUNT_LONGINT")) {
    Result_ = send(sockid,Long, h->n_payloads*sizeof(long int), 0);
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


int  shunt_cs_recv_intV    (int sockid,cs_header* h,int* Int) {
  int Result_=-1;
  if (h->data_type == shunt_prim_hash("SHUNT_INT")) {
    Result_ =  recv(sockid,Int , h->n_payloads*sizeof(int) , 0);
  }
  return Result_;
}

int  shunt_cs_recv_shortV    (int sockid,cs_header* h,short int* Shortint) {
  int Result_=-1;
  if (h->data_type == shunt_prim_hash("SHUNT_SHORTINT")) {
    Result_ =  recv(sockid,Shortint , h->n_payloads*sizeof(int) , 0);
  }
  return Result_;
}

int  shunt_cs_recv_longV    (int sockid,cs_header* h,long int* Longint) {
  int Result_=-1;
  if (h->data_type == shunt_prim_hash("SHUNT_LONGINT")) {
    Result_ =  recv(sockid,Longint , h->n_payloads*sizeof(long int) , 0);
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
//aux functions
long int shunt_cs_get_cs_header_leader() {
  long int  Result_ = shunt_prim_hash("shunt_cs_header_leader");
  return Result_;
}

long int shunt_cs_get_tlm_header_leader() {
  long int Result_ = shunt_prim_hash("shunt_tlm_generic_payload_header_leader"); 
  return Result_; 
}

long int shunt_cs_get_tlm_data_leader() {
  long int Result_ =  shunt_prim_hash("shunt_tlm_generic_payload_data_leader");
  return Result_; 
}

int shunt_cs_tlm_data_payload_size(const int data_size) {
  int data_size_ = data_size*sizeof(char)/sizeof(long int);
  if (data_size*sizeof(char)%sizeof(long int)>0 || data_size_ ==0) ++data_size_;
  return data_size_;
}

//TLM2.0
void shunt_cs_tlm_send_gp  (int sockid, const cs_tlm_generic_payload_header* h,const unsigned char* data,const unsigned char* byte_enable) {
  int data_size_ =0;
  int byte_en_size_=0;
  //long int mem/array for  cs_tlm_generic_payload_header
  //pkt size: <tlm header leader> +  <tlm header> + <tlm data leader> + <data vector> + <byte_enable> 
  if(h->length >0 ) {
    data_size_ = shunt_cs_tlm_data_payload_size(h->length);
    byte_en_size_ = shunt_cs_tlm_data_payload_size(h->byte_enable_length);
  }
  int  size_  = sizeof(long int)+ sizeof(*h)+ sizeof(long int) + data_size_*sizeof(long int) + byte_en_size_*sizeof(long int);
  
  long int* send_arr_ = (long int*)malloc(size_); // array to hold the result
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nshunt_cs_tlm_send_gp() DEBUG data_size_(%0d)  byte_en_size_(%0d) size_(%0d.%0d)=%0d\n",data_size_,byte_en_size_,size_/sizeof(long int),size_%sizeof(long int),size_);
#endif
  
  int  offset      = 0;
  send_arr_[offset]   =  shunt_cs_get_tlm_header_leader();
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("shunt_cs_tlm_send_gp() DEBUG offset=%0d\n",offset);
#endif
  
  ++offset;
  memcpy(&send_arr_[offset], h,sizeof(*h));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("shunt_cs_tlm_send_gp() DEBUG offset=%0d\n",offset);
#endif  
  if (data_size_ != 0) {
    offset = offset + sizeof(*h)/sizeof(long int);
    send_arr_[offset] = shunt_cs_get_tlm_data_leader();
    //printf("shunt_cs_tlm_send_gp() DEBUG offset=%0d\n",offset);
    
    ++offset;
    memcpy(&send_arr_[offset],data, h->length*sizeof(char));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    printf("shunt_cs_tlm_send_gp() DEBUG offset=%0d\n",offset);
#endif    
    offset = offset + data_size_;
    memcpy(&send_arr_[offset],byte_enable,h->byte_enable_length*sizeof(char));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    printf("shunt_cs_tlm_send_gp() DEBUG offset=%0d\n",offset);
#endif
  }
  unsigned int max_loop =  offset;
  if (offset>0) max_loop++;
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  for(unsigned int loop = 0; loop < max_loop ; loop++) {
    printf("shunt_cs_tlm_send_gp() DEBUG send_arr_[%0d]=%lx\n",loop,send_arr_[loop]);
  }
#endif
  int numbytes_ = send(sockid,send_arr_,size_, 0);
  if (numbytes_ <= 0)  shunt_prim_error("\nERROR in  shunt_pkt_send_longV()  : numbytes < 0 ");
  
  free(send_arr_);
}

void shunt_cs_tlm_send_gp_header  (int sockid, cs_tlm_generic_payload_header* h) {
  
  //long int mem/array for  cs_tlm_generic_payload_header
  //pkt size: <tlm header leader> +  <tlm header> + <tlm data leader> + <data vector> + <byte_enable> 
  int  size_  = sizeof(long int)+ sizeof(*h);
  
  long int* send_arr_ = (long int*)malloc(size_); // array to hold the result
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nshunt_cs_tlm_send_gp() DEBUG data_size_(%0d)  byte_en_size_(%0d) size_(%0d.%0d)=%0d\n",data_size_,byte_en_size_,size_/sizeof(long int),size_%sizeof(long int),size_);
#endif
  //
  int  offset      = 0;
  send_arr_[offset]   =  shunt_cs_get_tlm_header_leader();
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("shunt_cs_tlm_send_gp() DEBUG offset=%0d\n",offset);
#endif
  ++offset;
  memcpy(&send_arr_[offset], h,sizeof(*h));
  //printf("shunt_cs_tlm_send_gp() DEBUG offset=%0d\n",offset);
  
  unsigned int max_loop =  offset;
  if (offset>0) max_loop++;
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  for(unsigned int loop = 0; loop < max_loop ; loop++) {
    printf("shunt_cs_tlm_send_gp() DEBUG send_arr_[%0d]=%lx\n",loop,send_arr_[loop]);
  }
#endif
  int numbytes_ = send(sockid,send_arr_,size_, 0);
  if (numbytes_ <= 0)  shunt_prim_error("\nERROR in  shunt_pkt_send_longV()  : numbytes < 0 ");
  
  free(send_arr_);
}


void shunt_cs_tlm_recv_gp_header  (int sockid, cs_tlm_generic_payload_header* h) {
  int  Result_=1;
  long int leader_in;
  long int leader_ref; 
  long recv_arr[(sizeof(*h) + sizeof(long int))/sizeof(long int)];
  int  numbytes=0;
  
  numbytes = recv(sockid,recv_arr ,sizeof(*h) + sizeof(long int), 0);
  if (numbytes<0)   shunt_prim_error("\nERROR in shunt_cs_tlm_recv_gp_header : numbytes < 0 ");
  Result_ = numbytes; 
  
  leader_in  = recv_arr[0];
  leader_ref = shunt_cs_get_tlm_header_leader();
  if ( Result_ > 0 && (leader_in == leader_ref)) {
    memcpy(h,&recv_arr[1],sizeof(*h));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    for (int i=0;i<(sizeof(*h) + sizeof(long int))/sizeof(long int);i++) printf("DEBUG: shunt_cs_tlm_recv_gp_header() recv_arr[%0d]=(%ld)%lx\n",i,recv_arr[i],recv_arr[i]);
#endif
  }
  else { 
    Result_ =-1;
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    printf("\nshunt_cs_tlm_recv_gp_header() get bad  header (%lx)(Ref. to %lx) numbytes=%0d \n", leader_in,leader_ref,numbytes);
    for (int i=0;i<(sizeof(*h) + sizeof(long int))/sizeof(long int);i++) printf("error shunt_cs_tlm_recv_gp_header() recv_arr[%0d]=(%ld)%lx\n",i,recv_arr[i],recv_arr[i]);
#endif
  }

}

void  shunt_cs_tlm_recv_gp_data (int sockid, const cs_tlm_generic_payload_header* h,unsigned long* data,unsigned long* byte_enable) {
  int data_size_ =0;
  int byte_en_size_=0;
  int numbytes_     = -1; 
  int  offset       = 0;
  long int leader_ =  shunt_cs_get_tlm_data_leader();

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("shunt_cs_tlm_recv_gp_data(DEBUG: shunt_cs_tlm_recv_gp_data()  h->length=%0ld\n",h->length);
#endif

  if(h->length>0) {
    data_size_    = shunt_cs_tlm_data_payload_size(h->length);
    byte_en_size_ = shunt_cs_tlm_data_payload_size(h->byte_enable_length);
    
    int size_ = sizeof(long int)+data_size_*sizeof(long int)+byte_en_size_*sizeof(long int);//data leader + data + byte_en
    long int* recv_arr_ = (long int*)malloc(size_); // array to hold the result
    
    numbytes_ =  recv(sockid,recv_arr_ ,size_ , 0);

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
    printf("DEBUG: shunt_cs_tlm_recv_gp_data() size_=%0d numbytes_=%0d  data_size_=%0d byte_en_size_=%0d\n",size_,numbytes_, data_size_,byte_en_size_);
#endif

    if (numbytes_ <= 0) shunt_prim_error("\nERROR in  shunt_cs_tlm_recv_gp_data() : numbytes < 0 ");
    if (leader_ == recv_arr_[offset]) {
      offset= offset+1;
      memcpy(data,&recv_arr_[offset],data_size_*sizeof(long int));
      offset= offset+data_size_;
      memcpy(byte_enable,&recv_arr_[offset],byte_en_size_*sizeof(long int));
    }
    else {

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
      printf("shunt_sc_tlm_recv_gp_data() get bad header=%0lx expected(%0lx)\n",leader_ ,recv_arr_[0] );
#endif
      for (int i=0;i<size_/sizeof(long int);i++) printf("error shunt_cs_tlm_recv_gp_data() recv_arr_[%0d]=(%ld)%lx\n",i,recv_arr_[i],recv_arr_[i]);
    }
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    for (int i=0;i<size_/sizeof(long int);i++) printf("DEBUG: shunt_cs_tlm_recv_gp_data() recv_arr_[%0d]=(%ld)%lx\n",i,recv_arr_[i],recv_arr_[i]);
    for (int i=0;i<data_size_;i++) printf("DEBUG: shunt_cs_tlm_recv_gp_data() data[%0d]=(%ld)%lx\n",i,data[i],data[i]);
    for (int i=0;i<byte_en_size_;i++) printf("DEBUG: shunt_cs_tlm_recv_gp_data() byte_enable[%0d]=(%ld)%lx\n",i,byte_enable[i],byte_enable[i]);
#endif
  }
}

#endif
