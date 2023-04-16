/* file: shunt.i */
%module shunt
%{
/* Everything in the %{ }% block will be copied in the wrapper file.
   Here, we include C header files necessary to compile the interface
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <stdarg.h>
#include <stdint.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h> 
#include "shunt_typedef.h"
#include "shunt_primitives.h"
#include "shunt_client_server.h"
#include "shunt_user_api.h"
%}

%include "typemaps.i"

/* list functions to be interfaced: */

/* Alternative: */
/* %apply double *OUTPUT { double* s }  */ /* apply rule that defines the argument *s as an output variable */
/* void hw1(double r1, double r2, double *s); */

typedef long long shunt_long_t;

//typedef struct cs_tlm_generic_payload_header_t {
//  shunt_long_t option;
//  shunt_long_t address;
//  shunt_long_t command;
//  shunt_long_t length;
//  shunt_long_t byte_enable_length;
//  shunt_long_t streaming_width;
//  shunt_long_t dmi;
//  shunt_long_t response_status;
//  shunt_long_t delay;
//  shunt_long_t tlm_phase;
//  shunt_long_t tlm_sync;
//  shunt_long_t tlm_extension_id;
//} cs_tlm_generic_payload_header;

//unsigned int shunt_cs_init_initiator(const unsigned int portno_in);

//void shunt_cs_tlm_recv_gp_header(int sockid, cs_tlm_generic_payload_header* OUTPUT);
//void shunt_cs_tlm_recv_gp_header (int sockid, cs_tlm_generic_payload_header* h);
%include "/home/v/workspace/Shunt/utils/c/include/shunt_typedef.h"
%include /home/v/workspace/Shunt/utils/c/include/shunt_primitives.h
%include /home/v/workspace/Shunt/utils/c/include/shunt_client_server.h
%include /home/v/workspace/Shunt/utils/c/include/shunt_user_api.h
