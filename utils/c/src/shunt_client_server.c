/*
   ============================================================================
   File        : shunt_client_server.c
   Version     : 1.0.0
   Copyright (c) 2016-2021 IC Verimeter. All rights reserved.
                 Licensed under the MIT License.
                 See LICENSE file in the project root for full license information.
   Description : Target-Initiator (Client-Server aka cs) handshake utils
                 System Verilog client server handshake (TCP/IP SystemVerilog SHUNT)
   ============================================================================
*/

#ifndef  SHUNT_CLIENT_SERVER_C_
#define  SHUNT_CLIENT_SERVER_C_


#include "shunt_client_server.h"

INLINE unsigned int shunt_cs_init_target(const unsigned int portno_in ,const char *hostname) {
  unsigned int socketfd;
  shunt_dynamic_port dynamic_port;

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
  char const *msg = "shunt_cs_init_target()";
#endif  

  if(portno_in == 0) {
    dynamic_port.port_number = 0;
    dynamic_port = shunt_cs_tcp_parent_init_target_dpa(hostname);
    
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
    printf("\nDEBUG: %s dynamic_port.port_number=%lld(hex %llx)",msg,dynamic_port.port_number,dynamic_port.port_number);
    printf("\nDEBUG: %s dynamic_port.host_ip(%s)",msg,dynamic_port.host_ip);
    printf("\nDEBUG: %s dynamic_port.host_name(%s)\n",msg,dynamic_port.host_name);
#endif
    socketfd= shunt_prim_init_target(dynamic_port.port_number,dynamic_port.host_name);
  }
  else  socketfd = shunt_prim_init_target(portno_in,hostname);
  
  return socketfd;
}


INLINE shunt_dynamic_port  shunt_cs_tcp_parent_init_target_dpa(const char *hostname) {
  unsigned int socketfd;
   
  int port;
  int success=1;
  
  char const *msg = "shunt_cs_tcp_parent_init_target_dpa()";
  
  cs_header h_trnx;
  shunt_dynamic_port dynamic_port;

  port = SHUNT_DEFAULT_TCP_PORT;
  socketfd= shunt_prim_init_target(port,hostname);
  
  //dynamic_port init
  dynamic_port.port_number = -1;
  
  //recv
  if (shunt_cs_recv_header(socketfd,&h_trnx)<= 0) success = 0;
  if (success == 0 )  printf("\nERROR: %s trnx_header fail to recv TCP PORT NUMBER ",msg);
  if (success == 1 ) dynamic_port.port_number = h_trnx.trnx_id;
  //
  if(shunt_cs_recv_byteV(socketfd,&h_trnx,dynamic_port.host_ip)<=0) success = 0;
  if (success == 0 )  printf("\nERROR: %s String data fail to recv HOST_IP",msg);
  //
  if (shunt_cs_recv_header(socketfd,&h_trnx)<= 0) success = 0;
  if(shunt_cs_recv_byteV(socketfd,&h_trnx,dynamic_port.host_name)<=0) success = 0;
  if (success == 0 )  printf("\nERROR: %s String data fail to recv HOST_NAME",msg);
  
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
  SHUNT_INSTR_HASH_INDEX_DEFINE;
  shunt_cs_print_header (&h_trnx,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY,msg);
  printf("\nDEBUG: %s  dynamic_port.port_number=%lld(hex %llx)",msg,dynamic_port.port_number,dynamic_port.port_number);
  printf("\nDEBUG: %s dynamic_port.host_ip(%s)",msg,dynamic_port.host_ip);
  printf("\nDEBUG: %s dynamic_port.host_name(%s)\n",msg,dynamic_port.host_name);
#endif
  shunt_prim_close_socket(socketfd); 
  
  return dynamic_port;
}

INLINE unsigned int  shunt_cs_init_initiator(const unsigned int portno) {
  
  unsigned int parentfd  = -1;
  unsigned int childfd   = -1;
  //
  if (portno != 0) childfd = shunt_prim_init_initiator(portno);
  else {
    parentfd  = shunt_cs_tcp_parent_init_initiator_dpa(); 
    childfd   = shunt_prim_tcp_child_init_initiator(parentfd);
  }
  
  return  childfd;
}

INLINE  shunt_dynamic_port shunt_cs_update_dynamic_port(unsigned int parentfd_0) {
  
  struct hostent *host_entry;/*host info */
  shunt_dynamic_port dynamic_port;
  struct sockaddr_in sin;
  socklen_t len;
  uint16_t     port_0     = -1;
  char host[SHUNT_HOST_NAME_LEN];
  char *host_ptr;
  char *hostIP_ptr;
  #ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
  char const *msg = "shunt_cs_update_dynamic_port() ";
  #endif
  len = sizeof(sin);

  if (getsockname(parentfd_0, (struct sockaddr *)&sin, &len) == -1)
    perror("getsockname");
  else {
    gethostname(host, sizeof(host)); //find the host name
    host_entry = gethostbyname(host); //find host information
    hostIP_ptr = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
    port_0 = ntohs(sin.sin_port);
    //
    host_ptr = &host[0];
    dynamic_port.port_number =  port_0;
    strcpy(dynamic_port.host_name,host_ptr);
    strcpy(dynamic_port.host_ip,hostIP_ptr);
    
    #ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
    printf("\nDEBUG: %s parentfd_0(%x) host(%s) hostIP_ptr(%s) port_0(%d) ",msg,parentfd_0,host,hostIP_ptr,port_0); 
    printf("\nDEBUG: %s dynamic_port.host_name (%s),dynamic_port.host_ip(%s) dynamic_port.port_number(%lld)\n ",msg,dynamic_port.host_name,dynamic_port.host_ip,dynamic_port.port_number);  
    #endif
    
  }
  return dynamic_port; 
}

INLINE   unsigned int shunt_cs_tcp_parent_init_initiator_dpa() {
  
  unsigned int parentfd = -1;
  unsigned int  childfd;
  unsigned int  port;
  int  success = 1; 
  int portno_in=0;

  unsigned int parentfd_0 = -1;
  // unsigned int childfd_0  = -1;
  shunt_dynamic_port dynamic_port;
  //
  cs_header      h_trnx_exp;
  
  char const *msg = "shunt_cs_init_initiator() ";
  
  port = SHUNT_DEFAULT_TCP_PORT;
  //
  parentfd = shunt_prim_tcp_parent_init_initiator(port);
  childfd  = shunt_prim_tcp_child_init_initiator(parentfd);
  //
  parentfd_0 = shunt_prim_tcp_parent_init_initiator(portno_in);
  dynamic_port = shunt_cs_update_dynamic_port(parentfd_0);
  
  
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG 
  printf("\nDEBUG: %s portno_in(%d) parentfd_0(%x)",msg,portno_in,parentfd_0); 
  printf("\nDEBUG: %s dynamic_port.host_name (%s),dynamic_port.host_ip(%s) dynamic_port.port_number(%llx) ",msg,dynamic_port.host_name,dynamic_port.host_ip,dynamic_port.port_number);  
  printf("\nDEBUG: %s childfd=%d",msg, childfd);
#endif
  
  SHUNT_INSTR_HASH_INDEX_DEFINE;
  
  h_trnx_exp.trnx_type =  shunt_prim_hash("shunt_dynamic_port_leader");
  h_trnx_exp.trnx_id   =  dynamic_port.port_number;
  h_trnx_exp.data_type =  shunt_cs_data_type_hash(SHUNT_BYTE,SHUNT_INSTR_ENUM_NAMES,SHUNT_HEADER_ONLY);
  
  //SEND HOST IP
  h_trnx_exp.n_payloads =SHUNT_HOST_IP_LEN; 
  if (shunt_cs_send_header(childfd,&h_trnx_exp)<= 0) success = 0;
  if (shunt_cs_send_byteV  (childfd,&h_trnx_exp,dynamic_port.host_ip)<= 0) success = 0;
  if (success == 0 )  printf("\nERROR: %s fail send HOST IP",msg);
  
  //SEND HOST NAMe
  h_trnx_exp.n_payloads =SHUNT_HOST_NAME_LEN;
  if (shunt_cs_send_header(childfd,&h_trnx_exp)<= 0) success = 0;
  if (shunt_cs_send_byteV  (childfd,&h_trnx_exp,dynamic_port.host_name)<= 0) success = 0;
  if (success == 0 )  printf("\nERROR: %s fail send HOST NAME",msg); 
  
  shunt_prim_close_socket(parentfd); 
  
  return parentfd_0;
  }

//Data exchange utilities (header)
INLINE shunt_long_t shunt_cs_data_type_hash(shunt_long_t data_type,const char* data_type_names[],int last_enum) {
  shunt_long_t result_ = -1;

  if(data_type < last_enum+1 && data_type >= 0 ) {
    result_ = shunt_prim_hash(data_type_names[data_type]);
  }
  return result_;
}

INLINE int shunt_cs_data_type(shunt_long_t hash,const char* trnx_type_names[],int last_enum) {
  int result_ = -1;
  int i =0;

  while(i < last_enum+1 && result_ < 0) {
    shunt_long_t hash_ = shunt_prim_hash(trnx_type_names[i]);
    if(hash == hash_) result_ = i;
    i++;
  }
  return result_;
}

INLINE void shunt_cs_print_header(cs_header* h,const char* data_type_names[],int last_enum,char const *msg) {

  printf("\n%s h_trnx->trnx_type\t(%lx)",msg,(long)h->trnx_type);
  printf("\n%s h_trnx->trnx_id\t(%lx)",msg,(long)h->trnx_id);

  int data_type_ = shunt_cs_data_type(h->data_type,data_type_names,last_enum);
  if(data_type_>=0)
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%lx",msg,data_type_names[data_type_],data_type_,(long)h->data_type);
  else
    printf("\n%s h_trnx->data_type\t(%s )(%d)\thash=%lx",msg,"N/A",data_type_,(long)h->trnx_type);
  printf("\n%s h_trnx->n_payloads\t(%0lu)",msg,(long)h->n_payloads);
  puts("\n");

  return;
}

INLINE void shunt_cs_print_data_header(cs_header* h,cs_data_header* h_data,const char* data_type_names[],int last_enum,char* msg) {

  int data_type_ = shunt_cs_data_type(h_data->data_type,data_type_names,last_enum);
  if(data_type_>=0)
    printf("\n%s h_data->data_type\t(%s )(%d)\thash=%lu",msg,data_type_names[data_type_],data_type_,(long)h_data->data_type);
  else
    printf("\n%s h_data->data_type\t(%s )(%d)\thash=%lu",msg,"N/A",data_type_,(long)h_data->data_type);

  for(int i=0;i<h->n_payloads;i++) {
    printf("\n%s h_data->trnx_payload_sizes[%0d]=%d",msg,i,h_data->trnx_payload_sizes[i]);
  }
  puts("\n");
  return;
}

INLINE int shunt_cs_send_header(int sockid,cs_header* h) {
  int Result_=0;
  shunt_long_t send_arr[(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t)];
  int numbytes=0;
  
  send_arr[0] = shunt_prim_hash("shunt_cs_header_leader");
  memcpy(&send_arr[1], h,sizeof(*h));
  numbytes = send(sockid,send_arr,sizeof(*h) + sizeof(shunt_long_t), 0);
  if(numbytes <= 0)  printf("\nERROR: in  shunt_cs_send_header : numbytes < 0 (%d) size=%ld sockid(%d)",numbytes,(sizeof(*h) + sizeof(shunt_long_t)),sockid);
  else  Result_=1;

  return Result_;
}

INLINE int shunt_cs_send_data_header(int sockid,int n_payloads,cs_data_header* h) {
  int Result_=1;
  if(shunt_prim_send_long(sockid,&h->data_type)==0) Result_=0;
  for(int i=0;i<n_payloads;i++) {
    if(shunt_prim_send_int(sockid,&h->trnx_payload_sizes[i])==0) Result_=0;
  }
  return Result_;
}

INLINE int shunt_cs_recv_header(int sockid,cs_header* h) {
  int  Result_=1;
  shunt_long_t leader_in;
  shunt_long_t leader_ref;
  shunt_long_t recv_arr[(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t)];
  int  numbytes=0;

  numbytes = recv(sockid,recv_arr ,sizeof(*h) + sizeof(shunt_long_t), 0);
  if(numbytes<0)   shunt_prim_error("\nERROR: in shunt_cs_recv_header : numbytes < 0 ");
  Result_ = numbytes;

  leader_in     = recv_arr[0];
  leader_ref = shunt_prim_hash("shunt_cs_header_leader");
  if(Result_ > 0 && (leader_in == leader_ref)) {
    memcpy(h,&recv_arr[1],sizeof(*h));
  }
  else {
    Result_ =-1;
    printf("\nERROR: shunt_cs_recv_header() get bad  header (%lx)(Ref. to %lx) numbytes=%0d", (long)leader_in,(long)leader_ref,numbytes);
    for(unsigned int i=0;i<(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t);i++) printf("\nERROR: shunt_cs_recv_header() recv_arr[%0d]=(%ld)%lx",i,(long)recv_arr[i],(long)recv_arr[i]);
  }
  return Result_;
}

INLINE int shunt_cs_recv_data_header(int sockid,int n_payloads,cs_data_header* h) {

  int Result_=1;

  shunt_prim_recv_long(sockid,&h->data_type);

  for(int i=0;i<n_payloads;i++) {
    if(shunt_prim_recv_int(sockid,&h->trnx_payload_sizes[i])==0) Result_=0;
  }
  return Result_;
}

// Data exchange utilities (element/vector)

INLINE int shunt_cs_send_intV(int sockid,const cs_header* h,const int* Int) {
  int Result_=-1;
  if(h->data_type==  shunt_prim_hash("SHUNT_INT")) {
    Result_ = send(sockid,Int, h->n_payloads*sizeof(int), 0);
  }
  return Result_;
}

INLINE int shunt_cs_send_shortV(int sockid,const cs_header* h,const short int * Short) {
  int Result_=-1;
  if(h->data_type==  shunt_prim_hash("SHUNT_SHORTINT")) {
    Result_ = send(sockid,Short, h->n_payloads*sizeof(int), 0);
  }
  return Result_;
}

INLINE int shunt_cs_send_longV(int sockid,const cs_header* h,const shunt_long_t * Long) {
  int Result_=-1;
  if(h->data_type==  shunt_prim_hash("SHUNT_LONGINT")) {
    Result_ = send(sockid,Long, h->n_payloads*sizeof(shunt_long_t), 0);
  }
  return Result_;
}

INLINE int shunt_cs_send_doubleV(int sockid,const cs_header* h,const double* Double) {
  int Result_=-1;

  if(h->data_type ==  shunt_prim_hash("SHUNT_REAL")) {
    for(int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_send_double(sockid,&Double[i]);
    }
  }
  return Result_;
}

INLINE int shunt_cs_send_floatV(int sockid,const cs_header* h,const float* Float) {
  int Result_=-1;
  if(h->data_type ==  shunt_prim_hash("SHUNT_SHORTREAL")) {
    for(int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_send_float(sockid,&Float[i]);
    }
  }
  return Result_;
}

INLINE int shunt_cs_send_byteV(int sockid,const cs_header* h,const char* byteV) {
  int Result_=-1;
  char B_ = 0;
  if(h->data_type==  shunt_prim_hash("SHUNT_BYTE" )|| h->data_type==  shunt_prim_hash("SHUNT_STRING")) {
    for(int i=0;i< h->n_payloads;i++) {
      B_ = byteV[i];
      Result_ = shunt_prim_send_byte(sockid,&B_);
    }
  }
  return Result_;
}

INLINE int shunt_cs_send_integerV(int sockid,const cs_header* h,const svLogicVecVal* IntegerV) {
  int Result_=-1;
  int Size_ =   h->n_payloads;

  if(h->data_type==  shunt_prim_hash("SHUNT_INTEGER")) {
    for(int i=0;i<Size_;i++) {
      Result_ = shunt_prim_send_integer(sockid,&IntegerV[i]);
    }
  }
  return Result_;
}

INLINE int shunt_cs_send_regN(const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  int Result_;

  Result_ = 1;
  svLogicVecVal* Reg_ =  (svLogicVecVal* )Reg;

  int Size_ =h_trnx->n_payloads / 32;
  if(h_trnx->n_payloads % 32 > 0) ++Size_;

  for(int i=0;i<Size_ ;i++) {
    int* Aval_ = (int*)&(Reg_[i].aval);
    int* Bval_ = (int*)&(Reg_[i].bval);
    if(shunt_prim_send_int(sockfd,Aval_)<=0) Result_=0;
    if(shunt_prim_send_int(sockfd,Bval_)<=0) Result_ =0;
  }
  return Result_;
}

INLINE int shunt_cs_send_bitN(int sockid,const cs_header* h,const svBitVecVal* BitN) {
  int Result_=-1;
  int Size_ =   h->n_payloads/ 32;

  if(h->n_payloads % 32 > 0) ++Size_;

  int* BitN_  = (int*) BitN;

  if(h->data_type==  shunt_prim_hash("SHUNT_BIT")) {
    for(int i=0;i<Size_;i++) {
      Result_ = shunt_prim_send_int(sockid,&BitN_[i]);
    }
  }
  return Result_;
}


INLINE int  shunt_cs_recv_intV(int sockid,cs_header* h,int* Int) {
  int Result_=-1;
  if(h->data_type == shunt_prim_hash("SHUNT_INT")) {
    Result_ =  recv(sockid,Int , h->n_payloads*sizeof(int) , 0);
  }
  return Result_;
}

INLINE int  shunt_cs_recv_shortV(int sockid,cs_header* h,short int* Shortint) {
  int Result_=-1;
  if(h->data_type == shunt_prim_hash("SHUNT_SHORTINT")) {
    Result_ =  recv(sockid,Shortint , h->n_payloads*sizeof(int) , 0);
  }
  return Result_;
}

INLINE int  shunt_cs_recv_longV(int sockid,cs_header* h,shunt_long_t* Longint) {
  int Result_=-1;
  if(h->data_type == shunt_prim_hash("SHUNT_LONGINT")) {
    Result_ =  recv(sockid,Longint , h->n_payloads*sizeof(shunt_long_t) , 0);
  }
  return Result_;
}


INLINE int  shunt_cs_recv_doubleV(int sockid,cs_header* h,double* Double) {
  int Result_=-1;

  if(h->data_type ==  shunt_prim_hash("SHUNT_REAL")) {
    for(int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_double(sockid,&Double[i]);
    }
  }
  return Result_;
}


INLINE int  shunt_cs_recv_floatV(int sockid,cs_header* h,float* Float) {
  int Result_=-1;

  if(h->data_type ==  shunt_prim_hash("SHUNT_SHORTREAL")) {
    for(int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_float(sockid,&Float[i]);
    }
  }
  return Result_;
}

INLINE int shunt_cs_recv_byteV(int sockid,cs_header* h,char* byteV) {
  int Result_=-1;
  char B_=0;
  if(h->data_type == shunt_prim_hash("SHUNT_BYTE" )|| h->data_type == shunt_prim_hash("SHUNT_STRING")) {
    for(int i=0;i< h->n_payloads;i++) {
      Result_ = shunt_prim_recv_byte(sockid,&B_);
      byteV[i] = B_;
    }
  }
  return Result_;
}

INLINE int shunt_cs_recv_bitN(int sockid,const cs_header* h,svBitVecVal* BitN) {
  int Result_=-1;
  int Size_ =   h->n_payloads/ 32;
  if(h->n_payloads % 32 > 0) ++Size_;

  int* BitN_  = (int*) BitN;

  if(h->data_type==  shunt_prim_hash("SHUNT_BIT")) {
    for(int i=0;i<Size_;i++) {
      Result_ = shunt_prim_recv_int(sockid,&BitN_[i]);
    }
  }
  return Result_;
}


INLINE int shunt_cs_recv_integerV(int sockid,const cs_header* h,svLogicVecVal* IntegerV) {
  int Result_=-1;
  int Size_ =   h->n_payloads;

  if(h->data_type==  shunt_prim_hash("SHUNT_INTEGER")) {
    for(int i=0;i<Size_;i++) {
      Result_ = shunt_prim_recv_integer(sockid,&IntegerV[i]);
    }
  }
  return Result_;
}

INLINE int shunt_cs_recv_regN(const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
  int Result_;
  Result_ = 1;
  svLogicVecVal* Reg_ =  Reg;

  int Size_ =h_trnx->n_payloads / 32;
  if(h_trnx->n_payloads % 32 > 0) ++Size_;

  for(int i=0;i<Size_ ;i++) {
    if(shunt_prim_recv_int(sockfd,(int *)&(Reg_[i].aval))<=0) Result_=0 ;
    if(shunt_prim_recv_int(sockfd,(int *)&(Reg_[i].bval))<=0) Result_=0 ;
  }

  return Result_;
}
//aux functions
INLINE shunt_long_t shunt_cs_get_cs_header_leader() {
  shunt_long_t  Result_ = shunt_prim_hash("shunt_cs_header_leader");
  return Result_;
}

INLINE shunt_long_t shunt_cs_get_tlm_header_leader() {
  shunt_long_t Result_ = shunt_prim_hash("shunt_tlm_generic_payload_header_leader");
  return Result_;
}

INLINE shunt_long_t shunt_cs_get_tlm_data_leader() {
  shunt_long_t Result_ =  shunt_prim_hash("shunt_tlm_generic_payload_data_leader");
  return Result_;
}

INLINE shunt_long_t shunt_cs_get_tlm_axi3_ext_leader() {
  shunt_long_t Result_ = shunt_prim_hash("shunt_tlm_axi3_extension_payload_header_leader");
  return Result_;
}

INLINE shunt_long_t shunt_cs_get_tlm_axi3_signal_leader() {
  shunt_long_t Result_ = shunt_prim_hash("shunt_tlm_signal_extension_payload_header_leader");
  return Result_;
}


INLINE unsigned int shunt_cs_tlm_data_payload_size(const unsigned int data_size) {
  unsigned int data_size_ = data_size*sizeof(char)/sizeof(shunt_long_t);
  if(data_size*sizeof(char)%sizeof(shunt_long_t)>0 || data_size_ ==0) ++data_size_;
  return data_size_;
}

//TLM2.0
INLINE void shunt_cs_tlm_send_gp(int sockid, const cs_tlm_generic_payload_header* h,const unsigned char* data,const unsigned char* byte_enable) {
  int data_size_ =0;
  int byte_en_size_=0;
  //shunt_long_t mem/array for  cs_tlm_generic_payload_header
  //pkt size: <tlm header leader> +  <tlm header> + <tlm data leader> + <data vector> + <byte_enable>
  if(h->length >0 ) {
    data_size_ = shunt_cs_tlm_data_payload_size(h->length);
    byte_en_size_ = shunt_cs_tlm_data_payload_size(h->byte_enable_length);
  }
  int  size_  = sizeof(shunt_long_t)+ sizeof(*h)+ sizeof(shunt_long_t) + data_size_*sizeof(shunt_long_t) + byte_en_size_*sizeof(shunt_long_t);

  shunt_long_t* send_arr_ =(shunt_long_t*)malloc(size_); // array to hold the result
  memset(send_arr_,0,size_);
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_gp() data_size_(%0d)  byte_en_size_(%0d) size_(%0ld.%0ld)=%0d",data_size_,byte_en_size_,size_/sizeof(shunt_long_t),size_%sizeof(shunt_long_t),size_);
#endif

  int  offset      = 0;

  send_arr_[offset]   =  shunt_cs_get_tlm_header_leader();
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_gp() tlm_header leader offset=%0d",offset);
#endif
  
  ++offset;
  memcpy(&send_arr_[offset], h,sizeof(*h));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_gp() header offset=%0d",offset);
#endif
  
  if(data_size_ != 0) {
    offset = offset + sizeof(*h)/sizeof(shunt_long_t);
    send_arr_[offset] = shunt_cs_get_tlm_data_leader();
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    printf("\nDEBUG: shunt_cs_tlm_send_gp() tlm_data leader offset=%0d",offset);
#endif

    ++offset;
    memcpy(&send_arr_[offset],data, h->length*sizeof(char));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    printf("\nDEBUG: shunt_cs_tlm_send_gp() tlm_data array offset=%0d",offset);
#endif

    offset = offset + data_size_;
    memcpy(&send_arr_[offset],byte_enable,h->byte_enable_length*sizeof(char));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    printf("\nDEBUG: shunt_cs_tlm_send_gp() tlm_byte_enable array offset=%0d",offset);
#endif
  }
  
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  unsigned int max_loop =  offset;
  if(offset>0) max_loop++;
  for(unsigned int loop = 0; loop < max_loop ; loop++) {
    printf("\nDEBUG: shunt_cs_tlm_send_gp() send_arr_[%0d]=%lx",loop,(long)send_arr_[loop]);
  }
  printf("\n"); 
#endif
  int numbytes_ = send(sockid,send_arr_,size_, 0);
  if(numbytes_ <= 0)  shunt_prim_error("\nERROR: in shunt_cs_tlm_send_gp()  : numbytes < 0 ");

  free(send_arr_);
}

INLINE void shunt_cs_tlm_send_gp_header(int sockid, cs_tlm_generic_payload_header* h) {

  //shunt_long_t mem/array for  cs_tlm_generic_payload_header
  //pkt size: <tlm header leader> +  <tlm header> + <tlm data leader> + <data vector> + <byte_enable>
  int  size_  = sizeof(shunt_long_t)+ sizeof(*h);

  shunt_long_t* send_arr_ = (shunt_long_t*)malloc(size_); // array to hold the result
  memset(send_arr_,0,size_);
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_gp_header() size_(%0d) size_(%0ld.%0ld)=%0d",size_,size_/sizeof(shunt_long_t),size_%sizeof(shunt_long_t),size_);
#endif
  //
  int  offset      = 0;
  send_arr_[offset]   =  shunt_cs_get_tlm_header_leader();
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_gp_header() offset=%0d",offset);
#endif
  ++offset;
  memcpy(&send_arr_[offset], h,sizeof(*h));

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_gp_header() offset=%0d",offset);
#endif

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  unsigned int max_loop =  offset;
  if(offset>0) max_loop++;
  for(unsigned int loop = 0; loop < max_loop ; loop++) {
    printf("\nDEBUG: shunt_cs_tlm_send_gp_header() send_arr_[%0d]=%lx",loop,(long)send_arr_[loop]);
  }
  printf("\n");
#endif
  int numbytes_ = send(sockid,send_arr_,size_, 0);
  if(numbytes_ <= 0)  shunt_prim_error("\nERROR: in shunt_cs_tlm_send_gp_header    : numbytes < 0 ");

  free(send_arr_);
}


INLINE void shunt_cs_tlm_recv_gp_header(int sockid, cs_tlm_generic_payload_header* h) {
  int  Result_=1;
  shunt_long_t leader_in;
  shunt_long_t leader_ref;
  shunt_long_t recv_arr[(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t)];
  int  numbytes=0;

  numbytes = recv(sockid,recv_arr ,sizeof(*h) + sizeof(shunt_long_t), 0);
  if(numbytes<0)   shunt_prim_error("\nERROR: in shunt_cs_tlm_recv_gp_header : numbytes < 0 ");
  Result_ = numbytes;

  leader_in  = recv_arr[0];
  leader_ref = shunt_cs_get_tlm_header_leader();
  if(Result_ > 0 && (leader_in == leader_ref)) {
    memcpy(h,&recv_arr[1],sizeof(*h));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    for(unsigned int i=0;i<(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t);i++) printf("\nDEBUG: shunt_cs_tlm_recv_gp_header() recv_arr[%0d]=(%ld)%lx",i,(long)recv_arr[i],(long)recv_arr[i]);
    printf("\n");
#endif
  }
  else {
    Result_ =-1;
    printf("\nERROR: shunt_cs_tlm_recv_gp_header() get bad  header (%lx)(Ref. to %lx) numbytes=%0d", (long)leader_in,(long)leader_ref,numbytes);
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    for(unsigned int i=0;i<(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t);i++) printf("\nDEBUG: ERROR shunt_cs_tlm_recv_gp_header() recv_arr[%0d]=(%ld)%lx",i,(long)recv_arr[i],(long)recv_arr[i]);
    printf("\n");
#endif
  }
}

INLINE void shunt_cs_tlm_send_axi3_header(int sockid, cs_tlm_axi3_extension_payload_header* h) {

  //shunt_long_t mem/array for  cs_tlm_axi3_extension_payload_header
  //pkt size: <tlm header leader> +  <tlm header> + <tlm data leader> + <data vector> + <byte_enable>
  int  size_  = sizeof(shunt_long_t)+ sizeof(*h);

  shunt_long_t* send_arr_ = (shunt_long_t*)malloc(size_); // array to hold the result
  memset(send_arr_,0,size_);
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_axi3_header size_(%0d) size_(%0ld.%0ld)=%0d",size_,size_/sizeof(shunt_long_t),size_%sizeof(shunt_long_t),size_);
#endif
  //
  int  offset      = 0;
  send_arr_[offset]   =  shunt_cs_get_tlm_axi3_ext_leader();
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_axi3_header offset=%0d",offset);
#endif
  ++offset;
  memcpy(&send_arr_[offset], h,sizeof(*h));

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_send_axi3_header offset=%0d",offset);
#endif

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  unsigned int max_loop =  offset;
  if(offset>0) max_loop++;
  for(unsigned int loop = 0; loop < max_loop ; loop++) {
    printf("\nDEBUG: shunt_cs_tlm_send_axi3_header send_arr_[%0d]=%lx",loop,(long)send_arr_[loop]);
  } 
  printf("\n");
#endif
  int numbytes_ = send(sockid,send_arr_,size_, 0);
  if(numbytes_ <= 0)  shunt_prim_error("\nERROR: in shunt_cs_tlm_send_axi3_header()   : numbytes < 0 ");

  free(send_arr_);
}


INLINE void  shunt_cs_tlm_recv_axi3_header(int sockid, cs_tlm_axi3_extension_payload_header* h) {
  int  Result_=1;
  shunt_long_t leader_in;
  shunt_long_t leader_ref;
  shunt_long_t recv_arr[(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t)];
  int  numbytes=0;

  numbytes = recv(sockid,recv_arr ,sizeof(*h) + sizeof(shunt_long_t), 0);
  if(numbytes<0)   shunt_prim_error("\nERROR: in  shunt_cs_tlm_recv_axi3_header : numbytes < 0 ");
  Result_ = numbytes;

  leader_in  = recv_arr[0];
  leader_ref = shunt_cs_get_tlm_axi3_ext_leader();
  if(Result_ > 0 && (leader_in == leader_ref)) {
    memcpy(h,&recv_arr[1],sizeof(*h));
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    for(unsigned int i=0;i<(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t);i++) printf("\nDEBUG:  shunt_cs_tlm_recv_axi3_header() recv_arr[%0d]=(%ld)%lx",i,(long)recv_arr[i],(long)recv_arr[i]);
    printf("\n");
#endif
  }
  else {
    Result_ =-1;
    printf("\nERROR: shunt_cs_tlm_recv_axi3_header()  get bad  header (%lx)(Ref. to %lx) numbytes=%0d", (long)leader_in,(long)leader_ref,numbytes);
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    for(unsigned int i=0;i<(sizeof(*h) + sizeof(shunt_long_t))/sizeof(shunt_long_t);i++) printf("\nDEBUG: ERROR shunt_cs_tlm_recv_axi3_header recv_arr[%0d]=(%ld)%lx",i,(long)recv_arr[i],(long)recv_arr[i]);
    printf("\n");
#endif
  }
}

INLINE void  shunt_cs_tlm_recv_gp_data(int sockid, const cs_tlm_generic_payload_header* h,shunt_long_t* data,shunt_long_t* byte_enable) {
  int data_size_ =0;
  int byte_en_size_=0;
  int numbytes_     = -1;
  int  offset       = 0;
  shunt_long_t leader_ =  shunt_cs_get_tlm_data_leader();

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
  printf("\nDEBUG: shunt_cs_tlm_recv_gp_data()  h->length (%0ld)  ",(long)h->length);
#endif

  if(h->length>0) {
    data_size_    = shunt_cs_tlm_data_payload_size(h->length);
    byte_en_size_ = shunt_cs_tlm_data_payload_size(h->byte_enable_length);

    int size_ = sizeof(shunt_long_t)+data_size_*sizeof(shunt_long_t)+byte_en_size_*sizeof(shunt_long_t);//data leader + data + byte_en
    shunt_long_t* recv_arr_ = (shunt_long_t*)malloc(size_); // array to hold the result
    memset(recv_arr_,0,size_);

    numbytes_ =  recv(sockid,recv_arr_ ,size_ , 0);

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    printf("\nDEBUG: shunt_cs_tlm_recv_gp_data() size_=%0d numbytes_=%0d  data_size_=%0d byte_en_size_=%0d",size_,numbytes_, data_size_,byte_en_size_);
#endif

    if(numbytes_ <= 0) shunt_prim_error("\nERROR in  shunt_cs_tlm_recv_gp_data() : numbytes < 0 ");
    if(leader_ == recv_arr_[offset]) {
      offset= offset+1;
      memcpy(data,&recv_arr_[offset],data_size_*sizeof(shunt_long_t));
      offset= offset+data_size_;
      memcpy(byte_enable,&recv_arr_[offset],byte_en_size_*sizeof(shunt_long_t));
    }
    else {

#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
      printf("\nDEBUG: shunt_sc_tlm_recv_gp_data() get bad header=%0lx expected(%0lx)",(long)leader_ ,(long)recv_arr_[0] );
#endif
      for(unsigned int i=0;i<size_/sizeof(shunt_long_t);i++) printf("\nERROR: shunt_cs_tlm_recv_gp_data() recv_arr_[%0d]=(%ld)%lx",i,(long)recv_arr_[i],(long)recv_arr_[i]);
    }
#ifdef SHUNT_CLIENT_SERVER_C_DEBUG
    for(unsigned int i=0;i<size_/sizeof(shunt_long_t);i++) printf("\nDEBUG: shunt_cs_tlm_recv_gp_data() recv_arr_[%0d]=(%ld)%lx",i,(long)recv_arr_[i],(long)recv_arr_[i]); 
    printf("\n");
    for(int i=0;i<data_size_;i++) printf("\nDEBUG: shunt_cs_tlm_recv_gp_data() data[%0d]=(%ld)%lx",i,(long)data[i],(long)data[i]);
    printf("\n");
    for(int i=0;i<byte_en_size_;i++) printf("\nDEBUG: shunt_cs_tlm_recv_gp_data() byte_enable[%0d]=(%ld)%lx",i,(long)byte_enable[i],(long)byte_enable[i]);
    printf("\n");
#endif
  }
}

#endif

