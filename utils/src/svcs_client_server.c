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
vectors:          integers, doubles , string
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
  
  printf("\n%s h->trnx_type\t(%f)",msg,h->trnx_type);
  printf("\n%s h->trnx_id\t(%f)",msg,h->trnx_id);
  //
  int data_type_ = svcs_cs_data_type(h->data_type,data_type_names,last_enum);
  if (data_type_>=0)
    printf("\n%s h->data_type\t(%s )(%d)\thash=%f",msg,data_type_names[data_type_],data_type_,h->data_type);
  else
    printf("\n%s h->data_type\t(%s )(%d)\thash=%f",msg,"N/A",data_type_,h->trnx_type);
  printf("\n%s h->n_payloads\t(%0d)",msg,h->n_payloads);
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
  
  int data_type_ = svcs_cs_data_type(h->data_type,data_type_names,last_enum);
  if (data_type_>=0)
    printf("\n%s h->data_type\t(%s )(%d)\thash=%f",msg,data_type_names[data_type_],data_type_,h->data_type);
  else
    printf("\n%s h->data_type\t(%s )(%d)\thash=%f",msg,"N/A",data_type_,h->trnx_type);
  
  for(int i=0;i<h->n_payloads;i++) {
    printf("\n%s h_data->trnx_payload_sizes[%0d]=%d",msg,i,h_data->trnx_payload_sizes[i]);
  }
}


int svcs_cs_send_header    (int sockid,cs_header* h) {
  int Result_=1;
  
  // SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "svcs_cs_send_trnx_header";
  //svcs_cs_print_trnx_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg)
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

/* TOODO remove
   int svcs_cs_recv_header   (int sockid,cs_header* h) {
   int Result_=1;
   svcs_cs_recv_trnx_header(sockid,&(*h).trnx);
   svcs_cs_recv_data_header(sockid,&(*h).data);
   return Result_;
   }
*/
int svcs_cs_recv_header   (int sockid,cs_header* h) {
  int Result_=1;
  //SVCV_INSTR_HASH_INDEX_DEFINE;
  //char* msg = "svcs_cs_recv_trnx_header";
  //svcs_cs_print_trnx_header (h,SVCV_INSTR_ENUM_NAMES,SVCS_HEADER_ONLY,msg);
  if (svcs_prim_recv_double(sockid,&h->trnx_type)==0) Result_=0;
  if (svcs_prim_recv_double(sockid,&h->trnx_id)==0)   Result_=0;
  if (svcs_prim_recv_double(sockid,&h->data_type)==0) Result_=0;
  if (svcs_prim_recv_int(sockid,&h->n_payloads)==0) Result_=0;
  return Result_;
}

int svcs_cs_recv_data_header   (int sockid,int n_payloads,cs_data_header* h) {
  
  int Result_=1;
  
  svcs_prim_recv_double(sockid,&h->data_type);
  //h->trnx_payload_sizes = malloc(h->n_payloads*sizeof(int));
  //if (h->trnx_payload_sizes == NULL) {
  //  Result_= -1;
  //  puts("\n Error: svcs_cs_recv_data_header cannot allocate memory ");
  // }
  //else {
  for(int i=0;i<n_payloads;i++) {
    if (svcs_prim_recv_int(sockid,&h->trnx_payload_sizes[i])==0) Result_=0;
  }
  return Result_;
}
/* TOODO remove
   int svcs_cs_recv_data_header_clean   (cs_data_header* h) {
   int Result_=1;
   free(h->trnx_payload_sizes);
   return Result_;
   }
*/
/////////////////////////////////////////
// Data exchange utilities (element/vector)
int svcs_cs_send_intV (int sockid,const cs_header* h,const int* Int) {
  int Result_=-1;
  
  if (h->data_type==  SVCS_INT) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_send_int(sockid,&Int[i]);
    }
  }
  return Result_;
}


int  svcs_cs_recv_intV    (int sockid,cs_header* h,int* Int) {
  int Result_=-1;
  
  if (h->data_type ==  SVCS_INT) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_recv_int(sockid,&Int[i]);
    }
  }
  return Result_;
  
}

////////////
int svcs_cs_send_doubleV (int sockid,const cs_header* h,const double* Double) {
  int Result_=-1;
  
  if (h->data_type ==  SVCS_DOUBLE) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_send_double(sockid,&Double[i]);
    }
  }
  return Result_;
}


int  svcs_cs_recv_doubleV    (int sockid,cs_header* h,double* Double) {
  int Result_=-1;
  
  if (h->data_type ==  SVCS_DOUBLE) {
    for (int i=0;i< h->n_payloads;i++) {
      Result_ = svcs_prim_recv_double(sockid,&Double[i]);
    }
  }
  return Result_;
  
}

int svcs_cs_send_string   (int sockid,const cs_header* h,const char* string) {
  int Result_=-1;
  //printf("will send string  (%s) of %d bytes\n",str,length);
  if (h->data_type ==  SVCS_STRING) {
    Result_ = send(sockid, string,h->n_payloads, 0);
  }
  return Result_;
}

int svcs_cs_recv_string   (int sockid,cs_header* h,char* string) {
  int Result_=-1;
  if (h->data_type ==  SVCS_STRING) {
    Result_ = recv(sockid,string,h->n_payloads, 0);
    //printf("get string length(%0d) (%s) \n",Result_,string);
  }
  return Result_;
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


int  svcs_cs_recv_intA    (int sockid,int n_payloads,cs_data_header* h,int ** Int) {
  int Result_= 1;
  
  //int sum_=0;
  //puts("\n");
  //for (int i=0;i< h->n_payloads;i++) {
  //  sum_=sum_+ 	h->trnx_payload_sizes[i];
  //}
  
  //(*Int) = (int *)malloc(sum_* sizeof(int));
  //if (*Int == NULL) {
  //  Result_= -1;
  //  puts("\n Error: svcs_cs_recv_int cannot allocate memory ");
  // }
  // else {
  int indx_ =0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      Result_ = svcs_prim_recv_int(sockid,&(*Int)[indx_]);
      //printf("\n svcs_cs_resv_int (%0d) Int[%0d][%0d]=%d",indx_,i,j,(*Int)[indx_]);
      indx_++;
    }
  }
  // }
  return Result_;
}

/* TODO remove
   int svcs_cs_recv_int_clean   (int ** Int) {
   int Result_=1;
   free( (*Int));
   return Result_;
   }
*/

int svcs_cs_send_doubleA   (int sockid,int n_payloads,const cs_data_header* h,const double* Double) {
  int Result_=-1;
  int indx_ =0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      //printf("\n svcs_cs_send_double (%0d) Double[%0d][%0d]=%d",indx_,i,j,Double[indx_]);
      Result_ = svcs_prim_send_double(sockid,&Double[indx_]);
      indx_++;
    }
  }
  return Result_;
}

int svcs_cs_recv_doubleA   (int sockid,int n_payloads,cs_data_header* h,double ** Double) {
  int Result_=-1;
  int indx_ =0;
  for(int i=0;i<n_payloads;i++) {
    for (int j=0;j< h->trnx_payload_sizes[i];j++) {
      Result_ = svcs_prim_recv_double(sockid,&(*Double)[indx_]);
      //printf("\n svcs_cs_resv_double (%0d) Double[%0d][%0d]=%d",indx_,i,j,(*Double)[indx_]);
      indx_++;
    }
  }
  return Result_;
}
/*
  int svcs_cs_recv_double_clean   (double ** Double) {
  int Result_=1;
  free( (*Double));
  return Result_;
  }
*/
////////////


#endif


 
