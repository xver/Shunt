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

/*
  typedef struct cs_header_t {
    int      sockid; 
    double   trnx_atribute;
    int   trnx_type;
    double   trnx_id;
    //
    int      trnx_payload_size;
    } cs_header;
*/

void svcs_cs_print_header    (cs_header* header) {

  SVCV_INSTR_HASH_INDEX_DEFINE;

  printf("\nheader->sockid\t(%0d)",header->sockid);
  printf("\nheader->trnx_atribute\t(%f)",header->trnx_atribute);
  printf("\nheader->trnx_type\t(%s)(%d)\thash=%f",SVCV_INSTR_ENUM_NAMES[header->trnx_type],header->trnx_type,svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[header->trnx_type]));
  printf("\nheader->trnx_payload_size\t(%0d)",header->trnx_payload_size);
}


int svcs_cs_send_header    (cs_header* header) {
  double trnx_type_ =0;
  int success_ = 1;

  SVCV_INSTR_HASH_INDEX_DEFINE;
  if (svcs_prim_send_double(header->sockid,&header->trnx_atribute)==0) success_=0;
  trnx_type_ = svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[header->trnx_type]);
  if (svcs_prim_send_double(header->sockid,&trnx_type_)==0) success_=0;
  if (svcs_prim_send_double(header->sockid,&header->trnx_id)==0) success_=0;
  if (svcs_prim_send_int(header->sockid,&header->trnx_payload_size)==0) success_=0;
  return success_;
}

int svcs_cs_recv_header   (cs_header* header) {
	  double trnx_type_ =-1;
	  int success_ = 1;
	  if (svcs_prim_recv_double (header->sockid,&header->trnx_atribute)==0) success_=0;
	  if (svcs_prim_recv_double    (header->sockid,&trnx_type_)==0) success_=0;
	  header->trnx_type = svcs_cs_trnx_type(trnx_type_);
	  if (svcs_prim_recv_double    (header->sockid,&header->trnx_id)==0) success_=0;
	  if (svcs_prim_recv_int       (header->sockid,&header->trnx_payload_size)==0) success_=0;
	  return success_;
}

double svcs_cs_trnx_type_hash(int trnx_type) {

	SVCV_INSTR_HASH_INDEX_DEFINE;
	double result_ = -1;

	if ( trnx_type < SVCS_A_STRUCTURE && trnx_type > 0 ) {
		result_ = svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[trnx_type]);
	  }
	return result_;
}


int svcs_cs_trnx_type(double hash) {
	SVCV_INSTR_HASH_INDEX_DEFINE;
	int result_ = -1;
	int i =0;
	  while (i < SVCS_A_STRUCTURE && result_ < 0) {
	    if (hash == svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[i]))
	      result_ = i;
	    i++;
	  }
	return result_;

}


// Data exchange utilities (element)

int svcs_cs_send_intV (const cs_header* header,const int* Int) {
  int Result_=-1;

  if (header->trnx_type ==  SVCS_V_INT) {
  for (int i=0;i< header->trnx_payload_size;i++) {
  Result_ = svcs_prim_send_int(header->sockid,&Int[i]);
  	  }
  	}
  return Result_;
}


int  svcs_cs_recv_intV    (cs_header* header,int* Int) {
	int Result_=-1;

	  if (header->trnx_type ==  SVCS_V_INT) {
	  for (int i=0;i< header->trnx_payload_size;i++) {
	  Result_ = svcs_prim_recv_int(header->sockid,&Int[i]);
	  	  }
	  	}
	  return Result_;

}

////////////
int svcs_cs_send_doubleV (const cs_header* header,const double* Double) {
  int Result_=-1;

  if (header->trnx_type ==  SVCS_V_DOUBLE) {
  for (int i=0;i< header->trnx_payload_size;i++) {
  Result_ = svcs_prim_send_double(header->sockid,&Double[i]);
  	  }
  	}
  return Result_;
}


int  svcs_cs_recv_doubleV    (cs_header* header,double* Double) {
	int Result_=-1;

	  if (header->trnx_type ==  SVCS_V_DOUBLE) {
	  for (int i=0;i< header->trnx_payload_size;i++) {
	  Result_ = svcs_prim_recv_double(header->sockid,&Double[i]);
	  	  }
	  	}
	  return Result_;

}

int svcs_cs_send_string   (const cs_header* header,const char* string) {
	int Result_=-1;
	 //printf("will send string  (%s) of %d bytes\n",str,length);
	if (header->trnx_type ==  SVCS_V_STRING) {
	 Result_ = send(header->sockid, string,header->trnx_payload_size, 0);
	}
	 return Result_;
}

int svcs_cs_recv_string   (cs_header* header,char* string) {
	int Result_=-1;
	if (header->trnx_type ==  SVCS_V_STRING) {
	  Result_ = recv(header->sockid,string,header->trnx_payload_size, 0);
	  //printf("get string length(%0d) (%s) \n",Result_,string);
	}
    return Result_;
}


//void svcs_cs_send_double    (const cs_header* header,const double Double); TODO

//double* svcs_cs_recv_double    (cs_header* header); TODO



// Data exchange utilities (vector)




//Data exchange utilities (array)

//void svcs_cs_send_intA(const cs_header* header,const int* ArrayI); TODO
//int* svcs_cs_recv_intA(cs_header* header); TODO

//void svcs_cs_send_doubleA(const int sockfd,const int size,const double* ArrayD); TODO
//double* svcs_cs_recv_doubleA(cs_header* header); TODO

//void svcs_cs_send_stringA(const cs_header* header,const char* ArrayS); TODO
//char* svcs_cs_recv_stringA(cs_header structure); TODO


#endif


 
