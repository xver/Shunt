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

int svcs_dpi_send_short  (const int sockfd,const short int Short) {
  int Result_ =0;
  Result_ = svcs_prim_send_short(sockfd,&Short);
  return Result_;
}

int svcs_dpi_recv_short  (int sockfd,short int* Short) {
  int Result_ =0;
  Result_ =svcs_prim_recv_short(sockfd,Short);
  return Result_;
}

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

int svcs_dpi_send_long  (const int sockfd,const long int Long) {
  int Result_ =0;
  Result_ = svcs_prim_send_long(sockfd,&Long);
  return Result_;
}

int svcs_dpi_recv_long  (int sockfd,long int* Long) {
  int Result_ =0;
  Result_ =svcs_prim_recv_long(sockfd,Long);
  return Result_;
}

int svcs_dpi_send_time    (const unsigned int sockfd,svLogicVecVal* Time) {
  int Result_;
  //char* msg = "\nsvcs_dpi_send_time"; 
 
 Result_ = 1;
 for (int  i=0;i<2;i++) {
   if (svcs_dpi_send_int(sockfd, (int)Time[i].aval)<=0) Result_=0 ;
   if (svcs_dpi_send_int(sockfd, (int)Time[i].bval)<=0) Result_=0 ;
   //printf("  %s [%0d] Time->aval=%x,Time->bval=%x ",msg,i,Time[i].aval,Time[i].bval);
 }
 
 return Result_; 

}

int svcs_dpi_recv_time    (const unsigned int sockfd,svLogicVecVal* Time) {
  int Result_;
  //char* msg = "\nsvcs_dpi_recv_time"; 
  
  Result_ = 1;
  for (int  i=0;i<2;i++) { 
    if (svcs_dpi_recv_int (sockfd,(int*)(&Time[i].aval))<=0) Result_=0 ;
    if (svcs_dpi_recv_int (sockfd,(int*)(&Time[i].bval))<=0) Result_=0 ;
    //printf("  %s [%0d] Time.aval=%x,Time.bval=%x ",msg,i,Time[i].aval,Time[i].bval); 
  } 

 return Result_;
}

////Direct send/recv  
int svcs_dpi_send_byte(const  unsigned int sockfd, const char Byte) {
  int Result_ =0;
  Result_ = svcs_prim_send_byte(sockfd,&Byte);
  return Result_;
}

int svcs_dpi_send_bit (const unsigned int sockfd,const svBit Bit) {
  return svcs_dpi_send_byte(sockfd,Bit);
}

int svcs_dpi_send_reg (const unsigned int sockfd,const svLogic Reg) {
  return svcs_dpi_send_byte(sockfd,Reg); 
}

int svcs_dpi_send_logic (const unsigned int sockfd,const svLogic Logic) {
  return  svcs_dpi_send_reg (sockfd,Logic);
}

int svcs_dpi_recv_byte(const  unsigned int sockfd,char* Byte) {
  int Result_ =0;
  Result_ =svcs_prim_recv_byte(sockfd,Byte);
  return Result_;
}

int svcs_dpi_recv_bit     (const unsigned int sockfd,svBit* Bit) {
  return svcs_dpi_recv_byte(sockfd,(char*)Bit);
}

int svcs_dpi_recv_reg     (const unsigned int sockfd,svLogic* Reg) {
  return svcs_dpi_recv_byte(sockfd,(char*)Reg);  
}

int svcs_dpi_recv_logic     (const unsigned int sockfd,svLogic* Logic) {
  return  svcs_dpi_recv_reg(sockfd,Logic);
}
////Direct send/recv  
int svcs_dpi_send_real(const  unsigned int sockfd,double Real) {
  int Result_ =0;
  Result_ =svcs_prim_send_double(sockfd,&Real);
  return Result_;
}
int svcs_dpi_send_realtime(const  unsigned int sockfd,double Real) {
  return svcs_dpi_send_real(sockfd,Real);
}

int svcs_dpi_send_shortreal(const  unsigned int sockfd,float Real) {
  int Result_ =0;
  //char* msg = "svcs_dpi_send_shortreal";
  //printf("  %s  Real=%f ",msg,Real);
  Result_ =svcs_prim_send_float(sockfd,&Real);
  return Result_;
}

int svcs_dpi_recv_real(const  unsigned int sockfd,double* Real) {
  int Result_ =0;
  Result_ =svcs_prim_recv_double(sockfd,Real);
  return Result_;
}

int svcs_dpi_recv_realtime(const  unsigned int sockfd,double* Real) {
  return svcs_dpi_recv_real(sockfd,Real);
}
int svcs_dpi_recv_shortreal(const  unsigned int sockfd,float* Real) {
  int Result_ =0;
  Result_ =svcs_prim_recv_float(sockfd,Real);
  return Result_; 
}

////Direct send/recv  
//*****************************************
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
  //for(int i=0;i<size;i++) printf("%s Int_[%0d]=%s of %d\n",msg,Int_[i]);
  return Result_;
}

void svcs_dpi_print_intV(cs_header* h,int *Int,char* msg) {

  svcs_cs_print_intV(h,Int,msg);
  //return Result_;
}
// ****************************************************

int svcs_dpi_send_shortV(int sockid, const int size,const svOpenArrayHandle Int){
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_shortV:";
  
#ifndef C_TEST
  short int* Short_= (short int *) svGetArrayPtr(Int); 
#else
  short int* Short_= (short int *) Int;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_SHORTINT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //for(int i=0;i<size;i++) printf("%s Short_[%0d]=%0d of %0d\n",msg,i,Short_[i],size);
  Result_ = svcs_cs_send_shortV(sockid,&h_,Short_);
  return Result_;
}


int svcs_dpi_recv_shortV(int sockid,int size,svOpenArrayHandle Int) {
  cs_header h_;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_shortV:";
#ifndef C_TEST
   short int* Short_ = (short int *) svGetArrayPtr(Int);
#else
   short int* Short_= (short int *) Int;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_SHORTINT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  Result_ = svcs_cs_recv_shortV(sockid,&h_,Short_);
  //for(int i=0;i<size;i++) printf("%s Short_[%0d]=%0d of %0d\n",msg,i,Short_[i],size);
  return Result_;
}
// ****************************************************
////////////////////////////////
int svcs_dpi_send_longV(int sockid, const int size,const svOpenArrayHandle Int){
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_longV:";
  
#ifndef C_TEST
  long int* Long_= (long int *) svGetArrayPtr(Int); 
#else
  long int* Long_= (long int *) Int;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_LONGINT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //for(int i=0;i<size;i++) printf("%s Long_[%0d]=%0d of %0d\n",msg,i,Long_[i],size);
  Result_ = svcs_cs_send_longV(sockid,&h_,Long_);
  return Result_;
}


int svcs_dpi_recv_longV(int sockid,int size,svOpenArrayHandle Int) {
  cs_header h_;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_longV:";
#ifndef C_TEST
   long int* Long_ = (long int *) svGetArrayPtr(Int);
#else
   long int* Long_= (long int *) Int;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_LONGINT");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  Result_ = svcs_cs_recv_longV(sockid,&h_,Long_);
  //for(int i=0;i<size;i++) printf("%s Long_[%0d]=%0d of %0d\n",msg,i,Long_[i],size);
  return Result_;
}
////////////////////////////////
////Direct send/recv  
int svcs_dpi_send_realV(int sockid, const int size,const svOpenArrayHandle Real) {
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_realV:";
#ifndef C_TEST
  double* Real_ = (double *) svGetArrayPtr(Real);
#else
  int* Real_= (double *) Real;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_REAL");
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
  int* Real_= (double *) Real;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_REAL");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  Result_ = svcs_cs_recv_doubleV(sockid,&h_,Real_);
  //svcs_cs_print_realV(&h_,Real_,msg);
  return Result_;
}
////////////////////////////////////////
int svcs_dpi_send_shortrealV(int sockid, const int size,const svOpenArrayHandle Shortreal) {
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_shortrealV:";
#ifndef C_TEST
  float* Shortreal_ = (float *) svGetArrayPtr(Shortreal);
#else
  int* Shortreal_= (float *) Shortreal;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_SHORTREAL");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  //svcs_cs_print_shortrealV(&h_,Shortreal_,msg);
  Result_ = svcs_cs_send_floatV(sockid,&h_,Shortreal_);
  return Result_;
}

int svcs_dpi_recv_shortrealV(int sockid,int size,svOpenArrayHandle Shortreal) {
  cs_header h_;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_recv_shortrealV:";
#ifndef C_TEST
  float* Shortreal_ = (float *) svGetArrayPtr(Shortreal);
#else
  int* Shortreal_= (float *) Shortreal;
#endif
  int Result_ =0;
  h_.trnx_type = rand();
  h_.trnx_id   = rand();
  h_.data_type  = svcs_prim_hash("SVCS_SHORTREAL");
  h_.n_payloads = size;
  //svcs_cs_print_header (&h_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  Result_ = svcs_cs_recv_floatV(sockid,&h_,Shortreal_);
  //svcs_cs_print_shortrealV(&h_,Shortreal_,msg);
  return Result_;
}
////////////////////////////////////////
////Direct send/recv  

int svcs_dpi_send_string(int sockid,int size,char* string) {
  cs_header h_ ;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "\nsvcs_dpi_send_string: ";
  int Result_ =0;
  h_.trnx_type  = rand();
  h_.trnx_id    = rand();
  h_.data_type  = svcs_prim_hash("SVCS_BYTE");
  h_.n_payloads = size;
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

int svcs_dpi_send_data_header (int sockid,cs_header* h,double data_type,svOpenArrayHandle trnx_payload_sizes) {
  cs_data_header h_data_;
  int Result_ =0;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "svcs_dpi_send_data_header";
  h_data_.data_type = data_type;
  int* Int_ = (int*) svGetArrayPtr(trnx_payload_sizes);
  for(int i=0;i<h->n_payloads;i++) h_data_.trnx_payload_sizes[i] = Int_[i];
  //svcs_cs_print_data_header(h,&h_data_,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  Result_ = svcs_cs_send_data_header (sockid,h->n_payloads,&h_data_);
  return Result_;
}

int svcs_dpi_recv_header         (int sockid,cs_header* h){
 int Result_ =0;
 Result_ = svcs_cs_recv_header(sockid,h);
 return Result_;
}

int svcs_dpi_recv_data_header   (int sockid,cs_header* h,double* data_type,svOpenArrayHandle**  trnx_payload_sizes) {
  int Result_;
  cs_data_header h_data;
  int n_payloads;
  n_payloads =  h->n_payloads;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "svcs_dpi_recv_data_header";
  Result_ = svcs_cs_recv_data_header(sockid,n_payloads,&h_data);
  //svcs_cs_print_data_header_dbg (n_payloads,&h_data,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  int* Int_ = (int *)svGetArrayPtr(trnx_payload_sizes); 
  *data_type =h_data.data_type;  
  for (int i=0;i<n_payloads;i++) { 
    Int_[i]  = h_data.trnx_payload_sizes[i];
  } 
  return Result_;
}

////  HandShake(hs) send/recv

int svcs_dpi_hs_send (int sockid,cs_header* h_trnx,svOpenArrayHandle Array){
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
//4-states
int svcs_dpi_send_byte4s (const unsigned int sockfd,svLogicVecVal* Byte) {
 int Result_;
 //char* msg = "\nsvcs_dpi_send_byte4s"; 
 
 Result_ = 1;
 
 if (svcs_dpi_send_byte(sockfd, Byte->aval)<=0) Result_=0 ;
 if (svcs_dpi_send_byte(sockfd, Byte->bval)<=0) Result_=0 ;
 //printf("  %s  Byte->aval=%x,Byte->bval=%x ",msg,Byte->aval,Byte->bval);
 
 return Result_;
}

int svcs_dpi_recv_byte4s (const unsigned int sockfd,svLogicVecVal* Byte) {
  int Result_;
  //char* msg = "\nsvcs_dpi_recv_byte4s"; 
  
  Result_ = 1;
   
  if (svcs_dpi_recv_byte (sockfd,(char *)(&Byte->aval))<=0) Result_=0 ;
  if (svcs_dpi_recv_byte (sockfd,(char *)(&Byte->bval))<=0) Result_=0 ;
  //printf("  %s  Byte->aval=%x,Byte->bval=%x ",msg,Byte->aval,Byte->bval);  

 return Result_;
}

int svcs_dpi_send_int4s (const unsigned int sockfd,svLogicVecVal* Int) {
 int Result_;
 //char* msg = "\nsvcs_dpi_send_int4s"; 
 
 Result_ = 1;
 
 if (svcs_dpi_send_int(sockfd, Int->aval)<=0) Result_=0 ;
 if (svcs_dpi_send_int(sockfd, Int->bval)<=0) Result_=0 ;
 //printf("  %s  Int->aval=%x,Int->bval=%x size(%0d)",msg,Int->aval,Int->bval,sizeof(int));
 
 return Result_;
}
int svcs_dpi_send_integer (const unsigned int sockfd,svLogicVecVal* Int) {
  return svcs_dpi_send_int4s (sockfd,Int);
}


int svcs_dpi_recv_int4s (const unsigned int sockfd,svLogicVecVal* Int) {
  int Result_;
  //char* msg = "\nsvcs_dpi_recv_int4s"; 
  
  Result_ = 1;
   
  if (svcs_dpi_recv_int (sockfd,(int *)(&Int->aval))<=0) Result_=0 ;
  if (svcs_dpi_recv_int (sockfd,(int *)(&Int->bval))<=0) Result_=0 ;
  //printf("  %s  Int->aval=%x,Int->bval=%x ",msg,Int->aval,Int->bval);  

 return Result_;
}

int svcs_dpi_recv_integer (const unsigned int sockfd,svLogicVecVal* Int) {
  return svcs_dpi_recv_int4s (sockfd,Int); 
}


int svcs_dpi_hs_send4s (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  int Result_;
  //char* msg = "\nsvcs_dpi_hs_send4s";
  
  Result_ = 1;
  svLogicVecVal* Reg_ =  (svLogicVecVal*)svGetArrayPtr((svOpenArrayHandle*)Reg);
  
  int Size_ =h_trnx->n_payloads / 32; 
  if(h_trnx->n_payloads % 32 > 0) ++Size_;
  for(int i=0;i<Size_ ;i++) {
    //printf("%s  Reg->aval=%x,Reg->bval=%x size=%0d (%0d/%0d) bits",msg,Reg_[i].aval,Reg_[i].bval,svSizeOfArray((svOpenArrayHandle*)Reg),Size_,h_trnx->n_payloads % 32);
    if (svcs_dpi_send_int(sockfd, Reg_[i].aval)<=0) Result_=0;
    if (svcs_dpi_send_int(sockfd, Reg_[i].bval)<=0) Result_ =0;
  }
  
  return Result_;
}


int svcs_dpi_hs_send_reg4s (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  return  svcs_dpi_hs_send4s(sockfd,h_trnx,Reg);
}
int svcs_dpi_hs_send_regN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  return  svcs_dpi_hs_send4s(sockfd,h_trnx,Reg);
}
int svcs_dpi_hs_send_logicN (const unsigned int sockfd,cs_header* h_trnx,const  svLogicVecVal*  Reg) {
  return  svcs_dpi_hs_send4s(sockfd,h_trnx,Reg);
}

int svcs_dpi_hs_recv4s (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
  int Result_;
  //char* msg = "\nsvcs_dpi_hs_recv4s";
  Result_ = 1;
  svLogicVecVal* Reg_ =  (svLogicVecVal*)svGetArrayPtr((svOpenArrayHandle*)Reg);
  
  int Size_ =h_trnx->n_payloads / 32; 
  if(h_trnx->n_payloads % 32 > 0) ++Size_;
  
  for(int i=0;i<Size_ ;i++) { 
    if (svcs_dpi_recv_int(sockfd,(int *)&(Reg_[i].aval))<=0) Result_=0 ; 
    if (svcs_dpi_recv_int(sockfd,(int *)&(Reg_[i].bval))<=0) Result_=0 ; 
    //printf("%s  Reg->aval=%x,Reg->bval=%x size=%0d (%0d/%0d) bits",msg,Reg_[i].aval,Reg_[i].bval,svSizeOfArray((svOpenArrayHandle*)Reg),Size_,h_trnx->n_payloads % 32);
  } 
  
 return Result_; 
}

int svcs_dpi_hs_recv_reg4s (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
  return svcs_dpi_hs_recv4s (sockfd,h_trnx,Reg);
}

int svcs_dpi_hs_recv_regN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
  return svcs_dpi_hs_recv4s (sockfd,h_trnx,Reg);
}

int svcs_dpi_hs_recv_logicN (const unsigned int sockfd,cs_header* h_trnx,svLogicVecVal* Reg) {
  return svcs_dpi_hs_recv4s (sockfd,h_trnx,Reg);
}

int svcs_dpi_send_bitN  (const int sockfd,const int size,const svBitVecVal* bitN) {
  
  int Result_;
  //char* msg = "\nsvcs_dpi_send_bitN";
  
  Result_ = 1;
  svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
  
  int Size_ = size / 32; 
  if(size % 32 > 0) ++Size_;
  
  for(int i=0;i<Size_ ;i++) {
    //printf("%s  bitN=%x size=%0d (%0d/%0d) bits svDimension=%0d, svSize=%0d",msg,bitN_[i],svSizeOfArray((svOpenArrayHandle*)bitN),Size_,size,d,size_);
    if (svcs_dpi_send_int(sockfd, bitN_[i])<=0) Result_=0;
  }
  
  return Result_;}

int svcs_dpi_hs_send_bitN  (const int sockfd,const cs_header* h_trnx,const svBitVecVal* bitN) {
  svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
  return  svcs_cs_send_bitN  (sockfd,h_trnx,bitN_); 
}

 int svcs_dpi_recv_bitN  (const int sockfd,const int size,svBitVecVal* bitN) {
 int Result_;
  //char* msg = "\nsvcs_dpi_recv_bitN";
  Result_ = 1;
  svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
  
  int Size_ =size / 32; 
  if(size % 32 > 0) ++Size_;
  
  for(int i=0;i<Size_ ;i++) { 
    if (svcs_dpi_recv_int(sockfd,(int *)&(bitN_[i]))<=0) Result_=0 ; 
    //printf("%s  bitN->aval=%x,bitN->bval=%x size=%0d (%0d/%0d) bits",msg,bitN_[i].aval,bitN_[i].bval,svSizeOfArray((svOpenArrayHandle*)bitN),Size_,size % 32);
  } 
  
  return Result_; 
 }

int svcs_dpi_hs_recv_bitN  (const int sockfd,const cs_header* h_trnx,svBitVecVal* bitN) {
    svBitVecVal* bitN_ =  (svBitVecVal*)svGetArrayPtr((svOpenArrayHandle*)bitN);
    return svcs_cs_recv_bitN  (sockfd,h_trnx,bitN_);
}
#endif /* SVCS_DPI_C_ */
