/*
  ============================================================================
  File        : shunt_dpi.c
  Copyright (c) 2016-2021 IC Verimeter. All rights reserved.
                Licensed under the MIT License.
                See LICENSE file in the project root for full license information.
  Description : shunt dpi bridge
                System Verilog target server handshake (TCP/IP SystemVerilog SHUNT)
  ============================================================================
 */

#ifndef SHUNT_DPI_C_
#define SHUNT_DPI_C_

#include "shunt_dpi.h"


//--------------------
// TCP/IP socket init
//--------------------


unsigned int shunt_dpi_target_init(const unsigned int portno, const char *hostname) {
  int Result_ =0;
  Result_ = shunt_cs_init_target(portno,hostname);
  return Result_;
}


unsigned int shunt_dpi_initiator_init(const unsigned int portno) {
  unsigned int  Result_ =0;
  Result_ = shunt_cs_init_initiator(portno);
  return Result_;
}

void shunt_dpi_close_socket(int fd) {
 shunt_prim_close_socket(fd);
 return;
}

void shunt_dpi_unblock_socket(int flag ,int fd) {
  shunt_prim_unblock_socket(flag,fd);
  return;
}

int shunt_dpi_get_status_socket(int fd,int event) {
  int Result_;
  Result_ = shunt_prim_get_status_socket(fd,event);
  return Result_;
}

void shunt_dpi_tcp_nodelay_socket(int flag, int sockfd) {
  shunt_prim_tcp_nodelay_socket(flag,sockfd);
  return;
}

unsigned int shunt_dpi_listener_init(const unsigned int portno) {
  unsigned int  Result_;
  Result_ =shunt_prim_tcp_parent_init_initiator(portno);
  return Result_;
}

unsigned int shunt_dpi_tcp_connect(const unsigned int parentfd) {
  unsigned int  Result_;
  Result_ = shunt_prim_tcp_child_init_initiator(parentfd);
  return Result_;
}
//--------------------
// Direct send/recv
//--------------------

int shunt_dpi_send_short  (const int sockfd,const short int Short) {
  int Result_ =0;
  Result_ = shunt_prim_send_short(sockfd,&Short);
  return Result_;
}

int shunt_dpi_recv_short  (int sockfd,short int* Short) {
  int Result_ =0;
  Result_ =shunt_prim_recv_short(sockfd,Short);
  return Result_;
}

int shunt_dpi_send_int(const  unsigned int sockfd, const int Int) {
  int Result_ =0;
  Result_ = shunt_prim_send_int(sockfd,&Int);
  return Result_;
}

int shunt_dpi_recv_int(const  unsigned int sockfd,int* Int) {
  int Result_ =0;
  Result_ =shunt_prim_recv_int(sockfd,Int);
  return Result_;
}

int shunt_dpi_send_long  (const int sockfd,const shunt_long_t Long) {
  int Result_ =0;
  Result_ = shunt_prim_send_long(sockfd,&Long);
  return Result_;
}

int shunt_dpi_recv_long  (int sockfd,shunt_long_t* Long) {
  int Result_ =0;
  Result_ =shunt_prim_recv_long(sockfd,Long);
  return Result_;
}

int shunt_dpi_send_time    (const unsigned int sockfd,svLogicVecVal* Time) {
  int Result_;

 Result_ = 1;
 for (int  i=0;i<2;i++) {
   if (shunt_dpi_send_int(sockfd, (int)Time[i].aval)<=0) Result_=0 ;
   if (shunt_dpi_send_int(sockfd, (int)Time[i].bval)<=0) Result_=0 ;
 }

 return Result_;

}

int shunt_dpi_recv_time    (const unsigned int sockfd,svLogicVecVal* Time) {
  int Result_;

  Result_ = 1;
  for (int  i=0;i<2;i++) {
    if (shunt_dpi_recv_int (sockfd,(int*)(&Time[i].aval))<=0) Result_=0 ;
    if (shunt_dpi_recv_int (sockfd,(int*)(&Time[i].bval))<=0) Result_=0 ;
    }

 return Result_;
}

//Direct send/recv
int shunt_dpi_send_byte(const  unsigned int sockfd, const char Byte) {
  int Result_ =0;
  Result_ = shunt_prim_send_byte(sockfd,&Byte);
  return Result_;
}

int shunt_dpi_send_bit (const unsigned int sockfd,const svBit Bit) {
  return shunt_dpi_send_byte(sockfd,Bit);
}

int shunt_dpi_send_reg (const unsigned int sockfd,const svLogic Reg) {
  return shunt_dpi_send_byte(sockfd,Reg);
}

int shunt_dpi_send_logic (const unsigned int sockfd,const svLogic Logic) {
  return  shunt_dpi_send_byte (sockfd,Logic);
}

int shunt_dpi_recv_byte(const  unsigned int sockfd,char* Byte) {
  int Result_ =0;
  Result_ =shunt_prim_recv_byte(sockfd,Byte);
  return Result_;
}

int shunt_dpi_recv_bit     (const unsigned int sockfd,svBit* Bit) {
  return shunt_dpi_recv_byte(sockfd,(char*)Bit);
}

int shunt_dpi_recv_reg     (const unsigned int sockfd,svLogic* Reg) {
  return shunt_dpi_recv_byte(sockfd,(char*)Reg);
}

int shunt_dpi_recv_logic     (const unsigned int sockfd,svLogic* Logic) {
  return  shunt_dpi_recv_reg(sockfd,Logic);
}
//Direct send/recv
int shunt_dpi_send_real(const  unsigned int sockfd,double Real) {
  int Result_ =0;
  Result_ =shunt_prim_send_double(sockfd,&Real);
  return Result_;
}
int shunt_dpi_send_realtime(const  unsigned int sockfd,double Real) {
  return shunt_dpi_send_real(sockfd,Real);
}

int shunt_dpi_send_shortreal(const  unsigned int sockfd,float Real) {
  int Result_ =0;
  Result_ =shunt_prim_send_float(sockfd,&Real);
  return Result_;
}

int shunt_dpi_recv_real(const  unsigned int sockfd,double* Real) {
  int Result_ =0;
  Result_ =shunt_prim_recv_double(sockfd,Real);
  return Result_;
}

int shunt_dpi_recv_realtime(const  unsigned int sockfd,double* Real) {
  return shunt_dpi_recv_real(sockfd,Real);
}
int shunt_dpi_recv_shortreal(const  unsigned int sockfd,float* Real) {
  int Result_ =0;
  Result_ =shunt_prim_recv_float(sockfd,Real);
  return Result_;
}

//Direct send/recv
//*****************************************
int shunt_dpi_send_intV(int sockid, const int size,const svOpenArrayHandle Int){
  cs_header h_ ;

  int* Int_= (int *) svGetArrayPtr(Int);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_INT");
  h_.n_payloads = size;
  Result_ = shunt_cs_send_intV(sockid,&h_,Int_);
  return Result_;
}


int shunt_dpi_recv_intV(int sockid,int size,svOpenArrayHandle Int) {
  cs_header h_;
  int* Int_ = (int *) svGetArrayPtr(Int);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_INT");
  h_.n_payloads = size;
  Result_ = shunt_cs_recv_intV(sockid,&h_,Int_);
  return Result_;
}


// ****************************************************

int shunt_dpi_send_shortV(int sockid, const int size,const svOpenArrayHandle Int){
  cs_header h_ ;

  short int* Short_= (short int *) svGetArrayPtr(Int);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_SHORTINT");
  h_.n_payloads = size;
  Result_ = shunt_cs_send_shortV(sockid,&h_,Short_);
  return Result_;
}


int shunt_dpi_recv_shortV(int sockid,int size,svOpenArrayHandle Int) {
  cs_header h_;
  short int* Short_ = (short int *) svGetArrayPtr(Int);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_SHORTINT");
  h_.n_payloads = size;
  Result_ = shunt_cs_recv_shortV(sockid,&h_,Short_);
  return Result_;
}
// ****************************************************
int shunt_dpi_send_longV(int sockid, const int size,const svOpenArrayHandle Int){
  cs_header h_ ;

  shunt_long_t* Long_= (shunt_long_t *) svGetArrayPtr(Int);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_LONGINT");
  h_.n_payloads = size;

  Result_ = shunt_cs_send_longV(sockid,&h_,Long_);
  return Result_;
}


int shunt_dpi_recv_longV(int sockid,int size,svOpenArrayHandle Int) {
  cs_header h_;

   shunt_long_t* Long_ = (shunt_long_t *) svGetArrayPtr(Int);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_LONGINT");
  h_.n_payloads = size;
  Result_ = shunt_cs_recv_longV(sockid,&h_,Long_);

  return Result_;
}

//Direct send/recv

int shunt_dpi_send_realV(int sockid, const int size,const svOpenArrayHandle Real) {
  cs_header h_ ;

  double* Real_ = (double *) svGetArrayPtr(Real);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_REAL");
  h_.n_payloads = size;
  Result_ = shunt_cs_send_doubleV(sockid,&h_,Real_);
  return Result_;
}

int shunt_dpi_recv_realV(int sockid,int size,svOpenArrayHandle Real) {
  cs_header h_;
  double* Real_ = (double *) svGetArrayPtr(Real);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_REAL");
  h_.n_payloads = size;
  Result_ = shunt_cs_recv_doubleV(sockid,&h_,Real_);
  return Result_;
}

int shunt_dpi_send_shortrealV(int sockid, const int size,const svOpenArrayHandle Shortreal) {
  cs_header h_ ;
  float* Shortreal_ = (float *) svGetArrayPtr(Shortreal);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_SHORTREAL");
  h_.n_payloads = size;

  Result_ = shunt_cs_send_floatV(sockid,&h_,Shortreal_);
  return Result_;
}

int shunt_dpi_recv_shortrealV(int sockid,int size,svOpenArrayHandle Shortreal) {
  cs_header h_;

  float* Shortreal_ = (float *) svGetArrayPtr(Shortreal);

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_SHORTREAL");
  h_.n_payloads = size;
  Result_ = shunt_cs_recv_floatV(sockid,&h_,Shortreal_);
  return Result_;
}

//Direct send/recv

int shunt_dpi_send_string(int sockid,int size,char* string) {
  cs_header h_ ;

  int Result_ =0;
  h_.trnx_type  = rand();
  h_.trnx_id    = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_BYTE");
  h_.n_payloads = size;

  Result_ = shunt_cs_send_byteV(sockid, &h_,string);
  return Result_;
}

int shunt_dpi_recv_string(int sockid,int size,char** string) {
  cs_header h_ ;

  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_BYTE");
  h_.n_payloads = size;
  Result_ = shunt_cs_recv_byteV(sockid,&h_,*string);
  return Result_;
}


//--------------------
// HandShake(hs) send/recv
//--------------------
shunt_long_t shunt_dpi_hash(const char *str) {
  shunt_long_t Result_;
  Result_ = shunt_prim_hash(str);
  return Result_;
}
//  HandShake(hs) send/recv
int shunt_dpi_send_header         (int sockid,cs_header* h){
 int Result_ =0;
 Result_ = shunt_cs_send_header(sockid,h);
 return Result_;
}

int shunt_dpi_send_data_header (int sockid,cs_header* h,shunt_long_t data_type,svOpenArrayHandle trnx_payload_sizes) {
  cs_data_header h_data_;
  int Result_ =0;

  h_data_.data_type = data_type;
  int* Int_ = (int*) svGetArrayPtr(trnx_payload_sizes);
  for(int i=0;i<h->n_payloads;i++) h_data_.trnx_payload_sizes[i] = Int_[i];

  Result_ = shunt_cs_send_data_header (sockid,h->n_payloads,&h_data_);
  return Result_;
}

int shunt_dpi_recv_header         (int sockid,cs_header* h){
 int Result_ =0;
 Result_ = shunt_cs_recv_header(sockid,h);
 return Result_;
}

int shunt_dpi_recv_data_header   (int sockid,cs_header* h,shunt_long_t* data_type,svOpenArrayHandle**  trnx_payload_sizes) {
  int Result_;
  cs_data_header h_data;
  int n_payloads;
  n_payloads =  h->n_payloads;

  Result_ = shunt_cs_recv_data_header(sockid,n_payloads,&h_data);

  int* Int_ = (int *)svGetArrayPtr(trnx_payload_sizes);
  *data_type =h_data.data_type;
  for (int i=0;i<n_payloads;i++) {
    Int_[i]  = h_data.trnx_payload_sizes[i];
  }
  return Result_;
}

//  HandShake(hs) send/recv

int shunt_dpi_hs_send (int sockid,cs_header* h_trnx,svOpenArrayHandle Array){
  return shunt_api_send (sockid,h_trnx,Array);
}

int shunt_dpi_hs_send_short (int sockid,cs_header* h_trnx,svOpenArrayHandle Array) {
  short int* Short_ = (short int *) svGetArrayPtr(Array);
  return shunt_api_send(sockid,h_trnx,Short_);
}

int shunt_dpi_hs_send_int (int sockid,cs_header* h_trnx,svOpenArrayHandle Array ) {
 int* Int_ = (int *) svGetArrayPtr(Array);
  return shunt_dpi_hs_send(sockid,h_trnx,Int_);
}

int shunt_dpi_hs_send_long (int sockid,cs_header* h_trnx,svOpenArrayHandle Array) {
  shunt_long_t* Long_ = (shunt_long_t *) svGetArrayPtr(Array);
  return shunt_api_send(sockid,h_trnx,Long_);
}

int shunt_dpi_hs_send_byte (int sockid,cs_header* h_trnx,svOpenArrayHandle Array ){
  char* Byte_ = (char *) svGetArrayPtr(Array);
  return shunt_dpi_hs_send(sockid,h_trnx,Byte_);
}

int shunt_dpi_hs_send_string (int sockid,cs_header* h_trnx,char* Array){
  return shunt_dpi_hs_send(sockid,h_trnx,Array);
}

int shunt_dpi_hs_send_integer   (int sockid,cs_header* h_trnx,svOpenArrayHandle Array) {

  svLogicVecVal* Integer_ = (svLogicVecVal*)svGetArrayPtr(Array);


  return shunt_dpi_hs_send(sockid,h_trnx,Integer_);
}

int shunt_dpi_hs_send_real (int sockid,cs_header* h_trnx,svOpenArrayHandle Array ){
 double* Real_ = (double *) svGetArrayPtr(Array);
  return shunt_dpi_hs_send(sockid,h_trnx,Real_);
}

int shunt_dpi_hs_send_shortreal (int sockid,cs_header* h_trnx,svOpenArrayHandle Array ){
  float* Float_ = (float *) svGetArrayPtr(Array);
  return shunt_dpi_hs_send(sockid,h_trnx,Float_);
}

//  HandShake(hs) send/recv
int shunt_dpi_hs_recv (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array){
  return shunt_api_recv   (sockid,h_trnx,Array);
}

int shunt_dpi_hs_recv_short     (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array) {
  svOpenArrayHandle** Short_ = svGetArrayPtr(Array);
  return shunt_dpi_hs_recv(sockid,h_trnx,Short_);
}
int shunt_dpi_hs_recv_int (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array ) {
svOpenArrayHandle** Int_ = svGetArrayPtr(Array);
 return shunt_dpi_hs_recv(sockid,h_trnx,Int_);
}


int shunt_dpi_hs_recv_long (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array ) {
svOpenArrayHandle** Long_ = svGetArrayPtr(Array);
 return shunt_dpi_hs_recv(sockid,h_trnx,Long_);
}

int shunt_dpi_hs_recv_byte (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array ) {
 svOpenArrayHandle** Byte_ = svGetArrayPtr(Array);
 return shunt_dpi_hs_recv(sockid,h_trnx,Byte_);
}

int shunt_dpi_hs_recv_string (int sockid,cs_header* h_trnx,char** Array ) {
  return shunt_dpi_hs_recv(sockid,h_trnx,(svOpenArrayHandle**)(*Array));
}

int shunt_dpi_hs_recv_integer (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array ) {
 svOpenArrayHandle** Integer_ = svGetArrayPtr(Array);
 return shunt_dpi_hs_recv(sockid,h_trnx,Integer_);
}

int shunt_dpi_hs_recv_real (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array )  {
svOpenArrayHandle** Real_ = svGetArrayPtr(Array);
 return shunt_dpi_hs_recv(sockid,h_trnx,Real_);
}

int shunt_dpi_hs_recv_shortreal (int sockid,cs_header* h_trnx,svOpenArrayHandle** Array )  {
svOpenArrayHandle** Float_ = svGetArrayPtr(Array);
 return shunt_dpi_hs_recv(sockid,h_trnx,Float_);
}

//4-states


int shunt_dpi_send_integer (const unsigned int sockfd,svLogicVecVal* Int) {
  return shunt_prim_send_integer (sockfd,Int);
}


int shunt_dpi_recv_integer (const unsigned int sockfd,svLogicVecVal* Int) {
  return shunt_prim_recv_integer (sockfd,Int);
}


int shunt_dpi_send_integerV (const unsigned int sockid,const int size,const svLogicVecVal* IntegerV){
  cs_header h_;

  svLogicVecVal* IntegerV_ =  (svLogicVecVal*)svGetArrayPtr((svOpenArrayHandle*)IntegerV);

  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_INTEGER");
  h_.n_payloads = size;

  return shunt_cs_send_integerV(sockid,&h_,IntegerV_);
}

int shunt_dpi_recv_integerV (const unsigned int sockid,const int size,svLogicVecVal* IntegerV) {
  cs_header h_;

  svLogicVecVal* IntegerV_ = (svLogicVecVal*) svGetArrayPtr(IntegerV);

  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = shunt_prim_hash("SHUNT_INTEGER");
  h_.n_payloads = size;

  return shunt_cs_recv_integerV(sockid,&h_,IntegerV_);
}

int shunt_dpi_hs_send_regN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  svLogicVecVal* Reg_ =  (svLogicVecVal*)svGetArrayPtr((svOpenArrayHandle*)Reg);
  return  shunt_cs_send_regN(sockfd,h_trnx,Reg_);
}
int shunt_dpi_hs_send_logicN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  svLogicVecVal* Reg_ =  (svLogicVecVal*)svGetArrayPtr((svOpenArrayHandle*)Reg);
  return  shunt_cs_send_regN(sockfd,h_trnx,Reg_);
}

int shunt_dpi_hs_recv_regN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
 svLogicVecVal* Reg_ =  (svLogicVecVal*)svGetArrayPtr((svOpenArrayHandle*)Reg);
  return shunt_cs_recv_regN (sockfd,h_trnx,Reg_);
}

int shunt_dpi_hs_recv_logicN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
  svLogicVecVal* Reg_ =  (svLogicVecVal*)svGetArrayPtr((svOpenArrayHandle*)Reg);
  return shunt_cs_recv_regN (sockfd,h_trnx,Reg_);
}
int shunt_dpi_send_bitN  (const int sockfd,const int size,const svBitVecVal* bitN) {

  cs_header* h_ = NULL;

  h_->trnx_type = rand();
  h_->trnx_id   = rand();
  h_->data_type  = shunt_prim_hash("SHUNT_BIT");
  h_->n_payloads = size;

  svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
  return shunt_cs_send_bitN(sockfd,h_,bitN_);
}

int shunt_dpi_hs_send_bitN  (const int sockfd,const cs_header* h_trnx,const svBitVecVal* bitN) {
  svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
  return  shunt_cs_send_bitN  (sockfd,h_trnx,bitN_);
}

int shunt_dpi_recv_bitN  (const int sockfd,const int size,svBitVecVal* bitN) {
  cs_header* h_ = NULL;
  h_->trnx_type = rand();
  h_->trnx_id   = rand();
  h_->data_type  = shunt_prim_hash("SHUNT_BIT");
  h_->n_payloads = size;
  svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
  return shunt_cs_recv_bitN(sockfd,h_,bitN_);
 }

int shunt_dpi_hs_recv_bitN  (const int sockfd,const cs_header* h_trnx,svBitVecVal* bitN) {
    svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
    return shunt_cs_recv_bitN  (sockfd,h_trnx,bitN_);
}

int shunt_dpi_send_pkt_longV  (int sockid, const cs_header* h,const  svOpenArrayHandle Long) {
  int Result_ =0;
  shunt_long_t* Long_= (shunt_long_t *) svGetArrayPtr(Long);
  Result_ = shunt_pkt_send_longV (sockid,h,Long_);
  return Result_;
}

int shunt_dpi_recv_pkt_longV  (int sockid, cs_header* h, svOpenArrayHandle Long){
  int Result_ =0;
  shunt_long_t* Long_ = (shunt_long_t *) svGetArrayPtr(Long);
  Result_ = shunt_pkt_recv_longV  (sockid,h,Long_);
  return Result_;
}

shunt_long_t shunt_dpi_get_cs_header_id() {
  shunt_long_t Result_ = shunt_cs_get_cs_header_leader();
  return Result_;
}

//TLM 2.0

shunt_long_t shunt_dpi_tlm_header_id() {
  shunt_long_t Result_ =  shunt_cs_get_tlm_header_leader();
  return Result_;
}

shunt_long_t shunt_dpi_tlm_data_id() {
  shunt_long_t Result_ =  shunt_cs_get_tlm_data_leader();
  return Result_;
}

shunt_long_t shunt_dpi_tlm_axi3_ext_id() {
  shunt_long_t Result_ =  shunt_cs_get_tlm_axi3_ext_leader();
  return Result_;
}

shunt_long_t  shunt_dpi_tlm_signal_id() {
  shunt_long_t Result_ =   shunt_cs_get_tlm_axi3_signal_leader();
  return Result_;
}

void shunt_dpi_tlm_send_gp_transport(int sockid, cs_tlm_generic_payload_header* h, svOpenArrayHandle* data, svOpenArrayHandle* byte_enable){
  unsigned char *data_tcp;// =  (unsigned char *)svGetArrayPtr(data);
  unsigned char *byte_enable_tcp;// =  (unsigned char *) svGetArrayPtr(byte_enable);
  unsigned char *data_ =     (unsigned char *) svGetArrayPtr(data);
  unsigned char *byte_enable_ =  (unsigned char *) svGetArrayPtr(byte_enable);
  unsigned int size_byte_enable_payload = shunt_cs_tlm_data_payload_size(h->byte_enable_length);
  data_tcp        = (unsigned char*)malloc(h->length);
  byte_enable_tcp = (unsigned char*)malloc(size_byte_enable_payload*sizeof(shunt_long_t));
  if(h->length > 0) {
    memset(data_tcp,0,h->length);
    memset(byte_enable_tcp,0,size_byte_enable_payload*sizeof(shunt_long_t));
    memcpy(data_tcp,data_,h->length);
    memcpy(byte_enable_tcp,byte_enable_,(size_byte_enable_payload*sizeof(shunt_long_t)));
  }
#ifdef SHUNT_DPI_C_DEBUG
  for (int i=0;i<h->length;i++) printf("\nDEBUG: shunt_dpi_tlm_send_gp() data_tcp[%0d]=(%d)%x",i,data_tcp[i],data_tcp[i]);
  for (unsigned int i=0;i<size_byte_enable_payload;i++) printf("\nDEBUG: shunt_dpi_tlm_send_gp()  byte_enable_tcp[%0d]=(%d)%x",i,byte_enable_tcp[i],byte_enable_tcp[i]);
#endif
  shunt_cs_tlm_send_gp(sockid,h,data_tcp,byte_enable_tcp);
  free(data_tcp);
  free(byte_enable_tcp);
}

void shunt_dpi_tlm_send_command(int socket,const shunt_dpi_tlm_command_e Com) {
  cs_tlm_generic_payload_header csgp={0};
  csgp.command = Com;
#ifdef SHUNT_DPI_C_DEBUG
  printf("(\nDEBUG: shunt_dpi_tlm_send_command() csgp->lengtcsgp >0 (%0lld) csgp->byte_enable_lengtcsgp (%0lld)",csgp.length,csgp.byte_enable_length);
#endif
  shunt_cs_tlm_send_gp_header (socket,&csgp);
}

void shunt_dpi_tlm_recv_gp_transport (int sockid, cs_tlm_generic_payload_header* h,svOpenArrayHandle data,svOpenArrayHandle byte_enable) {

  shunt_long_t* data_tcp;
  shunt_long_t* byte_enable_tcp;
  unsigned char* data_        = (unsigned char *) svGetArrayPtr(data);
  unsigned char* byte_enable_ = (unsigned char *) svGetArrayPtr(byte_enable);
  
  while(shunt_prim_get_status_socket(sockid,0) !=1 );
  shunt_cs_tlm_recv_gp_header(sockid,h);
  if(h->length > 0) {
    int size_byte_enable_payload = shunt_cs_tlm_data_payload_size(h->byte_enable_length);
#ifdef SHUNT_DPI_C_DEBUG
    int size_data_payload        = shunt_cs_tlm_data_payload_size(h->length);
    printf("(\nDEBUG: shunt_dpi_tlm_recv_gp_transport() h->length >0 (%0lld) h->byte_enable_length (%0lld)",h->length,h->byte_enable_length);
#endif

    data_tcp        = (shunt_long_t*)malloc(h->length);
    memset(data_tcp,0,h->length);
    byte_enable_tcp = (shunt_long_t*)malloc(size_byte_enable_payload*sizeof(shunt_long_t));
    memset(byte_enable_tcp,0,size_byte_enable_payload*sizeof(shunt_long_t));
    shunt_cs_tlm_recv_gp_data (sockid,h, data_tcp, byte_enable_tcp);

#ifdef SHUNT_DPI_C_DEBUG
    for (int i=0;i<size_data_payload;i++) printf("\nDEBUG: shunt_dpi_tlm_recv_gp_transport() data_tcp[%0d]=(%lld)%llx",i,data_tcp[i],data_tcp[i]);
    for (int i=0;i<size_byte_enable_payload;i++) printf("\nDEBUG: shunt_dpi_tlm_recv_gp_transport() byte_enable_tcp[%0d]=(%lld)%llx",i,byte_enable_tcp[i],byte_enable_tcp[i]);
#endif

    memcpy(data_,data_tcp,h->length);

    if (h->byte_enable_length>0) memcpy(byte_enable_,byte_enable_tcp,h->byte_enable_length);

    free(data_tcp);
    free(byte_enable_tcp);

#ifdef SHUNT_DPI_C_DEBUG
    for (int i=0;i<h->length;i++) printf("\nDEBUG: shunt_dpi_tlm_recv_gp_transport() data_[%0d]=(%d)%x\n",i,data_[i],data_[i]);
#endif
  }
}

void shunt_dpi_tlm_recv_gp_header (int sockid, cs_tlm_generic_payload_header* h) {
  shunt_cs_tlm_recv_gp_header (sockid, h);
}

void shunt_dpi_tlm_send_gp_header (int sockid, cs_tlm_generic_payload_header* h) {
  shunt_cs_tlm_send_gp_header (sockid,h);
}

void shunt_dpi_tlm_recv_axi3_header (int sockid, cs_tlm_axi3_extension_payload_header* h) {
  shunt_cs_tlm_recv_axi3_header (sockid,h);
}

void shunt_dpi_tlm_send_axi3_header (int sockid, cs_tlm_axi3_extension_payload_header* h) {
  shunt_cs_tlm_send_axi3_header (sockid, h);
}


void  shunt_dpi_tlm_recv_gp_data (int sockid, cs_tlm_generic_payload_header* h,svOpenArrayHandle data,svOpenArrayHandle byte_enable){
  
  shunt_long_t* data_tcp;
  shunt_long_t* byte_enable_tcp;
  unsigned char* data_        = (unsigned char *) svGetArrayPtr(data);
  unsigned char* byte_enable_ = (unsigned char *) svGetArrayPtr(byte_enable);

  while(shunt_prim_get_status_socket(sockid,0) !=1 );
  if(h->length > 0) {
    int size_byte_enable_payload = shunt_cs_tlm_data_payload_size(h->byte_enable_length);
#ifdef SHUNT_DPI_C_DEBUG
    int size_data_payload        = shunt_cs_tlm_data_payload_size(h->length);
    printf("(\nDEBUG:  shunt_dpi_tlm_recv_gp_data h->length >0 (%0lld) h->byte_enable_length (%0lld)",h->length,h->byte_enable_length);
#endif
    
    data_tcp        = (shunt_long_t*)malloc(h->length);
    memset(data_tcp,0,h->length);
    byte_enable_tcp = (shunt_long_t*)malloc(size_byte_enable_payload*sizeof(shunt_long_t));
    
    shunt_cs_tlm_recv_gp_data (sockid,h, data_tcp, byte_enable_tcp);
    
#ifdef SHUNT_DPI_C_DEBUG
    for (int i=0;i<size_data_payload;i++) printf("\nDEBUG: shunt_dpi_tlm_recv_gp_data() data_tcp[%0d]=(%lld)%llx",i,data_tcp[i],data_tcp[i]);
    for (int i=0;i<size_byte_enable_payload;i++) printf("\nDEBUG: shunt_dpi_tlm_recv_gp_data() byte_enable_tcp[%0d]=(%lld)%llx",i,byte_enable_tcp[i],byte_enable_tcp[i]);
#endif
    
    memcpy(data_,data_tcp,h->length);

    if (h->byte_enable_length>0) memcpy(byte_enable_,byte_enable_tcp,h->byte_enable_length);

    free(data_tcp);
    free(byte_enable_tcp);

#ifdef SHUNT_DPI_C_DEBUG
    for (int i=0;i<h->length;i++) printf("\nDEBUG: shunt_dpi_tlm_recv_gp_data() data_[%0d]=(%d)%x\n",i,data_[i],data_[i]);
#endif
  }
}

//Linux system utils
shunt_long_t shunt_dpi_gettimeofday_sec() {
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec;
}

shunt_long_t shunt_dpi_gettimeofday_usec() {
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_usec;
}
#endif /* SHUNT_DPI_C_ */
