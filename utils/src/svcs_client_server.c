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
    double   trnx_type;
    double   trnx_id;
    //
    int      trnx_payload_size;
    } cs_header;
*/

void svcs_cs_print_header    (cs_header* header) {
  SVCV_INSTR_HASH_INDEX_DEFINE;
  int trn_type_result_ = 0;
  double trnx_type_ =0;
  int i =0;
  printf("header->sockid\t(%0d)\n",header->sockid);
  printf("header->trnx_atribute\t(%d)\n",header->trnx_atribute);
  printf("header->trnx_type\t(%s)\t%d\n ",svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[header->trnx_type]),SVCV_INSTR_ENUM_NAMES[header->trnx_type]);
  printf("header->trnx_type\t(%0d)\n",header->trnx_payload_size);
}

/* TODO compile error
void svcs_cs_send_header    (cs_header* header) {
  double trnx_type_ =0;
  SVCV_INSTR_HASH_INDEX_DEFINE;
  svcs_prim_send_double    (header->sockid,header->trnx_atribute);
  svcs_prim_send_double    (header->sockid,header->trnx_type);
  trnx_type_ = svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[header->trnx_type]);
  svcs_prim_send_double    (header->sockid,header->trnx_id);
  svcs_prim_send_int       (header->sockid,header->trnx_payload_size);
}

void svcs_cs_recv_header   (cs_header* header) {
  double trnx_type_    = 0;
  SVCV_INSTR_HASH_INDEX_DEFINE;
  header->trnx_type = -1; 
  
  header->trnx_atribute     = svcs_prim_recv_double(header->sockid);
  //
  trnx_type_                = svcs_prim_recv_double(header->sockid);
  int i =0;
  while (i < SVCS_A_STRUCTURE && header->trnx_type < 0) {
    if (trnx_type_ == svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[i]))
      header->trnx_type = i;   
    i++;	  
  }
  
  if ( header->trnx_type < 0) { 	
    svcs_prim_error("\tcs_header ERROR Undefined trnx_type"); 
    printf("header->trnx_type \t(%0d) ",header->trnx_payload_size);
  }
  //
  header->trnx_id  = svcs_prim_recv_double(header->sockid);
  header->trnx_payload_size = svcs_prim_recv_int(header->sockid);
}

*/
// Data exchange utilities (element)
/* TODO comp error
void svcs_cs_send_int (const cs_header* header,const int* Int) {
  int Result_=0;
  double trnx_type_ =0;
  SVCV_INSTR_HASH_INDEX_DEFINE;
  if (header->trnx_payload_size !=1)   Result_=-1;
  trnx_type_ = svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[SVCS_V_INT]);
  if (header-> trnx_type != trnx_type_ )   Result_=-1;
  if(Result_<0)  {
    svcs_prim_error("svcs_cs_send_int header Error");
    svcs_cs_print_header(header);
  }
  else svcs_cs_send_header(header);
  svcs_prim_send_int       (header->sockid,Int);
}
*/
/*TODO ERROR
int* svcs_cs_recv_int    (cs_header* header) {
  int Result_=0;
  double trnx_type_ =0;
  
  SVCV_INSTR_HASH_INDEX_DEFINE;
  svcs_cs_recv_header(header);
  if (header->trnx_payload_size !=1)   Result_=-1;
  trnx_type_ = svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[SVCS_V_INT]);
  if (header-> trnx_type != trnx_type_ )   Result_=-1;
  if(Result_<0)  {
    svcs_prim_error("svcs_cs_recv_int header Error");
    svcs_cs_print_header(header);
  }
   return svcs_prim_recv_int(header->sockid);
}
*/

//void svcs_cs_send_double    (const cs_header* header,const double Double); TODO

//double* svcs_cs_recv_double    (cs_header* header); TODO



// Data exchange utilities (vector)


//void svcs_cs_send_intV   (const cs_header* header,const int* Int) TODO
//int* svcs_cs_recv_intV   (cs_header* header); TODO

//void svcs_cs_send_doubleV   (const cs_header* header,const double* Double); TODO
//double* svcs_cs_recv_doubleV   (cs_header* header);

//void svcs_cs_send_string   (const cs_header* header,const char* string); TODO
//char* svcs_cs_recv_string   (cs_header* header); TODO


//Data exchange utilities (array)

//void svcs_cs_send_intA(const cs_header* header,const int* ArrayI); TODO
//int* svcs_cs_recv_intA(cs_header* header); TODO

//void svcs_cs_send_doubleA(const int sockfd,const int size,const double* ArrayD); TODO
//double* svcs_cs_recv_doubleA(cs_header* header); TODO

//void svcs_cs_send_stringA(const cs_header* header,const char* ArrayS); TODO
//char* svcs_cs_recv_stringA(cs_header structure); TODO


#endif


 
