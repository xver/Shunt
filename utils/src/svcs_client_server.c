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


//Data exchange utilities (element)

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
  printf("header->sockid \t(%0d) \n",header->sockid);
  printf("header->trnx_atribute \t(%0d) \n",header->trnx_atribute);
  printf("header->trnx_type \t(%0d) ",header->trnx_type);
  while (i < SVCS_A_STRUCTURE)
    {
      trnx_type_ = svcs_prim_hash(SVCV_INSTR_ENUM_NAMES[i]);
      if (header->trnx_type ==trnx_type_) {
	trn_type_result_ = 1;
	printf("\t(%s)",SVCV_INSTR_ENUM_NAMES[SVCS_V_INT]);
      }
      i++;
    }
  if (trn_type_result_ == 0 ) { 	svcs_prim_error("\tcs_header ERROR Undefined trnx_type"); }
  printf("header->trnx_type \t(%0d) ",header->trnx_payload_size);
}


void svcs_cs_send_header    (cs_header* header) {
  svcs_prim_send_double    (header->sockid,header->trnx_atribute);
  svcs_prim_send_double    (header->sockid,header->trnx_type);
  svcs_prim_send_double    (header->sockid,header->trnx_id);
  svcs_prim_send_int       (header->sockid,header->trnx_payload_size);
}

void svcs_cs_recv_header   (cs_header* header) {
  header->trnx_atribute     = svcs_prim_recv_double(header->sockid);
  header->trnx_type         = svcs_prim_recv_double(header->sockid);
  header->trnx_id           = svcs_prim_recv_double(header->sockid);
  header->trnx_payload_size = svcs_prim_recv_int(header->sockid);
}

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
/*
  /*
 Function: svcs_cs_send_double
 send  SVCS transaction with verilog "real"/C "double" data over TCP/IP 
 
 Parameters:
   header - cs_header structure
   Double  - data to send
   
   Returns:
    void
*/

void svcs_cs_send_double    (const cs_header* header,const double Double);

/*
  Function: svcs_cs_recv_double
  fetch SVCS transaction with verilog "real"/C "double" data over TCP/IP 
  
  Parameters:
   header - cs_header structure

  Returns: 
  Double - data from socket 
  and header atributes (cs_header)
    
*/
double* svcs_cs_recv_double    (cs_header* header);




/*
 Section: Data exchange utilities (vector)

(start code)
-------------------------------------------------------
vector ->  sockid - socket id
           header ->  trnx_atribute - hash/random double
                      trnx_type     - hash ("SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING")
                      trnx_id       - random double

          payload -> size          - number of data elements,size >1
                     data elements 
---------------------------------------------------------------
(end)
*/

/*
 Function: svcs_cs_send_intV
  send SVCS transaction with "int" elements vector over TCP/IP 
  
  Parameters:
   
   header - cs_header structure
   Int   - data
    
   Returns:
   void
*/
void svcs_cs_send_intV   (const cs_header* header,const int* Int);

/*
 Function: svcs_cs_recv_intV
  fetch SVCS transaction with "int" elements vector  elements from TCP/IP 
  
  Parameters:
     header - cs_header structure

  Returns: 
   data received from socket
  and header atributes (cs_header)
    
*/
int* svcs_cs_recv_intV   (cs_header* header);


/*
 Function: svcs_cs_send_doubleV
  send SVCS transaction with "double" elements vector over TCP/IP 
  
  Parameters:
     header - cs_header structure
     Double - data 
  Returns:
    void
*/
void svcs_cs_send_doubleV   (const cs_header* header,const double* Double);

/*
 Function: svcs_cs_recv_doubleV
  fetch SVCS transaction with "double" elements vector from TCP/IP 
  
  Parameters:
    header - cs_header structure

  Returns: 
  double - data from socket
  and header atributes (cs_header)
    
*/
double* svcs_cs_recv_doubleV   (cs_header* header);

/*
 Function: svcs_cs_send_string
  send SVCS transaction with verilog string/C char* elements over TCP/IP 
  
  Parameters:
    header - cs_header structure
    string  - data to send

  Returns:
    void
*/
void svcs_cs_send_string   (const cs_header* header,const char* string);

/*
 Function: svcs_cs_recv_string
  fetch SVCS transaction with verilog string/C char* elements from TCP/IP 
  
  Parameters:
    header - cs_header structure

  Returns: 
   data from socket 
  and header atributes (cs_header)
    
*/
char* svcs_cs_recv_string   (cs_header* header);


/*
 Section: Data exchange utilities (array)

(start code)
 ---------------------------------------------------------------
array ->  sockid - socket id
          header ->   trnx_atribute - hash/random double
                         trnx_type   - hash ("SVCS_A_STRUCTURE")
                         trnx_id    - random double
          payload->   size  > 1
          data - vector
---------------------------------------------------------------
 (end)

 */

/*
  Function: svcs_cs_send_intA
  send SVCS transaction with "int" vectors array over TCP/IP 
  
  Parameters:
  header - cs_header structure,
  note: header.trnx_payload_size - The number of array entries is equal to the number of "int" vectors   
  ArrayI  - data 
 */

 void svcs_cs_send_intA(const cs_header* header,const int* ArrayI);

/*
  Function: svcs_cs_recv_intA
  fetch SVCS transaction with "int" array of "int" vectors from TCP/IP  
  
  Parameters:
   header - cs_header structure
   string  - data to send
  
  Returns: 
  Array of int
  
*/
int* svcs_cs_recv_intA(cs_header* header);

/*
  Function: svcs_cs_send_doubleA
   send SVCS transaction with "double" vector array over TCP/IP 
  
  Parameters:
  header - cs_header structure,
  note: header.trnx_payload_size  - The number of array entries is equal to the number of "double" vectors     
  ArrayD  - data 
*/
void svcs_cs_send_doubleA(const int sockfd,const int size,const double* ArrayD);

/*
  Function: svcs_cs_recv_doubleA
  fetch SVCS transaction with "double" array of "double" vectors from TCP/IP  
  
  Parameters:
  header - cs_header structure

  Returns: 
  Array of double 
*/
double* svcs_cs_recv_doubleA(cs_header* header);

/*
  Function: svcs_cs_send_stringA
   send SVCS transaction with "string" vectors array  over TCP/IP 
  
  Parameters:
  header - cs_header structure,
  note: header.trnx_payload_size - The number of array entries is equal to the number of strings 
  ArrayS  - data 
*/
void svcs_cs_send_stringA(const cs_header* header,const char* ArrayS);

/*
  Function: svcs_cs_recv_stringA
  fetch SVCS transaction with string" vectors array from TCP/IP  
  
  Parameters:
  header - cs_header structure,
  
  Returns: 
  Array of strinds
  
*/
char* svcs_cs_recv_stringA(cs_header structure);
*/

#endif


 
