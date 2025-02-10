/*
 ============================================================================
Title: shunt_typedef.h

 Copyright (c) 2016-2025 IC Verimeter. All rights reserved.

               Licensed under the MIT License.

               See LICENSE file in the project root for full license information.

Description : common includes typedef, #defines Shunt settings
  ============================================================================
 */
#ifndef SHUNT_TYPEDEF_H
#define SHUNT_TYPEDEF_H

//Title: Common defines

#ifdef __cplusplus
#define INLINE inline
#else
#define INLINE
#endif

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

#ifdef SHUNT_SVDPI
#include "svdpi.h"
#else
#ifndef INCLUDED_SVDPI
typedef uint8_t svScalar;
typedef svScalar svLogic; /* scalar */
typedef svScalar svBit; /* scalar */
typedef uint32_t svBitVecVal;
typedef void* svOpenArrayHandle;

typedef struct t_vpi_vecval {
  uint32_t aval;
  uint32_t bval;
} s_vpi_vecval, *p_vpi_vecval;
typedef s_vpi_vecval svLogicVecVal;
#endif
#endif


//compile error struct hostent has no member named h_addr https://github.com/dound/vns/issues/2
#define h_addr h_addr_list[0] /* for backward compatibility */
#if 0
/*
 * Structs exported from in.h
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr;
};

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;   /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif

/*
Variable: shunt_long_t
typedef 64 bit variable , default value is "long long"
*/

#ifndef  shunt_long_t
typedef long long shunt_long_t;
#endif

/*
  Define: SHUNT_DEFAULT_TCP_PORT
  default port is used for dynamic allocation of the client-server TCP port.
  use "-DSHUNT_DEFAULT_TCP_PORT=<new port>" gcc option to change it
--- Code
#define SHUNT_DEFAULT_TCP_PORT 4350
---
*/
#ifndef SHUNT_DEFAULT_TCP_PORT
#define SHUNT_DEFAULT_TCP_PORT 4350
#endif

/*
  Define: SHUNT_DEFAULT_COLLISION_ATTEMPT_LIMIT

  specifies the MAXIMUM number of attempts to bind SHUNT_DEFAULT_TCP_PORT
  --- Code
  SHUNT_DEFAULT_COLLISION_ATTEMPT_LIMIT 180
  ---
*/
#ifndef SHUNT_DEFAULT_COLLISION_ATTEMPT_LIMIT
#define SHUNT_DEFAULT_COLLISION_ATTEMPT_LIMIT 180
#endif

/*
  Define: SHUNT_DEFAULT_COLLISION_LOW
  specifies in msec the MINIMUM random interval delay boundary for the collision resolution of the occupied TCP/IP port
   --- Code
   #define SHUNT_DEFAULT_COLLISION_LOW 500
   ---
  */
#ifndef SHUNT_DEFAULT_COLLISION_LOW
#define SHUNT_DEFAULT_COLLISION_LOW 500
#endif
/*
  Define: SHUNT_DEFAULT_COLLISION_UP
  specifies in msec the MAXIMUM random interval delay boundary for the collision resolution of the occupied TCP/IP port
--- Code
#define SHUNT_DEFAULT_COLLISION_UP 1500
---
*/
#ifndef SHUNT_DEFAULT_COLLISION_UP
#define SHUNT_DEFAULT_COLLISION_UP 1500
#endif
//Section: Data exchange defines

/*
  Variable: shunt_dynamic_port

  is used for dynamic allocation of the client-server TCP port.

  -  host_name   TCP/IP host_name
  -  host_ip     Host IP
  -  port_number TCP/IP host_name

  --- Code
  //Big-endian view:
  typedef struct shunt_dynamic_port_t {
    shunt_long_t port_number;       // port_number
    char         host_ip[16];       // host IP
    char         host_name[256];    // name of host
  } shunt_dynamic_port;
  ---
*/
#define SHUNT_HOST_IP_LEN 16
#define SHUNT_HOST_NAME_LEN 256

#if __BYTE_ORDER__== __ORDER_BIG_ENDIAN__
typedef struct shunt_dynamic_port_t {
  shunt_long_t port_number;       // port_number
  char         host_ip[SHUNT_HOST_IP_LEN];       // host IP
  char         host_name[SHUNT_HOST_NAME_LEN];    // name of host
} shunt_dynamic_port;
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
typedef struct shunt_dynamic_port_t {
  char         host_name[SHUNT_HOST_NAME_LEN];    // name of host
  char         host_ip[SHUNT_HOST_IP_LEN];        // host IP
  shunt_long_t port_number;       // port_number
} shunt_dynamic_port;

#endif

/*
Variable: SHUNT_INSTR_ENUM

 *Integer 2 states:*

  SHUNT_INT         - int
  SHUNT_SHORTINT    - shortint
  SHUNT_LONGINT     - longint
  SHUNT_BYTE        - byte
  SHUNT_BIT         - bit

  *Integer 4 states:*

  SHUNT_INTEGER     - integer,time
  SHUNT_REG         - reg,logic

  *Non integer types IEEE 754:*

  SHUNT_REAL        - real,realtime
  SHUNT_SHORTREAL   - shortreal
  SHUNT_STRING      - string

  SHUNT_A_STRUCTURE - complex data types/user defined data types : arrays/struct,union,enums
  SHUNT_HEADER_ONLY - cs_header_t header only.

  --- Code
  typedef enum {SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_BIT,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} SHUNT_INSTR_ENUM;
  ---

*/
typedef enum {SHUNT_INT,SHUNT_REAL,SHUNT_SHORTREAL,SHUNT_STRING,SHUNT_A_STRUCTURE,SHUNT_INTEGER,SHUNT_BYTE,SHUNT_REG,SHUNT_BIT,SHUNT_SHORTINT,SHUNT_LONGINT,SHUNT_HEADER_ONLY} SHUNT_INSTR_ENUM;

/*
Define: SHUNT_INSTR_ENUM_NAMES

--- Code
#define SHUNT_INSTR_HASH_INDEX_DEFINE const char* SHUNT_INSTR_ENUM_NAMES[] = {"SHUNT_INT","SHUNT_REAL","SHUNT_SHORTREAL","SHUNT_STRING","SHUNT_A_STRUCTURE","SHUNT_INTEGER","SHUNT_BYTE","SHUNT_REG","SHUNT_BIT","SHUNT_SHORTINT","SHUNT_LONGINT","SHUNT_HEADER_ONLY"}
---

*/
#define SHUNT_INSTR_HASH_INDEX_DEFINE const char* SHUNT_INSTR_ENUM_NAMES[] = {"SHUNT_INT","SHUNT_REAL","SHUNT_SHORTREAL","SHUNT_STRING","SHUNT_A_STRUCTURE","SHUNT_INTEGER","SHUNT_BYTE","SHUNT_REG","SHUNT_BIT","SHUNT_SHORTINT","SHUNT_LONGINT","SHUNT_HEADER_ONLY"}

/*
  Variable: cs_header_t

  - trnx_type      user defined transaction attribute
  - trnx_id        user defined unique transaction number
  - data_type      <SHUNT_INSTR_ENUM>
  - n_payloads     number of data payloads (for Array number of vectors)

  --- Code
  //Big-endian view:
  typedef struct cs_header_t {
    shunt_long_t   trnx_type;
    shunt_long_t   trnx_id;
    shunt_long_t   data_type;
    shunt_long_t   n_payloads;
   }cs_header;
---

*/
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

#if __BYTE_ORDER__== __ORDER_BIG_ENDIAN__

typedef struct cs_header_t {
  shunt_long_t   trnx_type;
  shunt_long_t   trnx_id;
  shunt_long_t   data_type;
  shunt_long_t   n_payloads;
} cs_header;
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
typedef struct cs_header_t {
  shunt_long_t   n_payloads;
  shunt_long_t   data_type;
  shunt_long_t   trnx_id;
  shunt_long_t   trnx_type;
} cs_header;
#endif

/*
  Variable: cs_data_header_t

  - data_type           <SHUNT_INSTR_ENUM>
  - trnx_payload_sizes   array of payload sizes, number of array elements are equal to n_payloads
*/
typedef struct cs_data_header_t {
  shunt_long_t   data_type;            // see SHUNT_INSTR_ENUM
  int     *trnx_payload_sizes; // array of payload sizes, number of array elements are equal to n_payloads
} cs_data_header;

//Section: TLM2.0 defines
/*
   Variable:  cs_tlm_generic_payload_header

   *TLM 2.0 Generic Payload structure* (Ref. to TLM 2.0 Generic Payload attributes)

   --- Code
   //Big-endian view:
   typedef struct cs_tlm_generic_payload_header_t {
     shunt_long_t option;
     shunt_long_t address;
     shunt_long_t command;
     shunt_long_t length;
     shunt_long_t byte_enable_length;
     shunt_long_t streaming_width;
     shunt_long_t dmi;
     shunt_long_t response_status;
     shunt_long_t delay;
     shunt_long_t tlm_phase;
     shunt_long_t tlm_sync;
     shunt_long_t tlm_extension_id;
   } cs_tlm_generic_payload_header;
   ---

   - *option*           Generic payload option :

   --- Code
   enum  tlm_gp_option { TLM_MIN_PAYLOAD, TLM_FULL_PAYLOAD, TLM_FULL_PAYLOAD_ACCEPTED }
   ---

   - *command*         Transaction type:

   --- Code
   enum  tlm_command { TLM_READ_COMMAND, TLM_WRITE_COMMAND, TLM_IGNORE_COMMAND }
   ---

   - *address*          Transaction base start address (bytes)

   - *length*           Total number of bytes of the transaction.

   - *byte_enable_length*  Number of elements in the bytes enable array.

   - *streaming_width*     Number of bytes transferred on each data-beat.

   - *dmi_allowed*        DMI allowed/not allowed (bool attribute)

   - *response_status*    Transaction status:

    --- Code
   enum  tlm_response_status {
   TLM_OK_RESPONSE = 1, TLM_INCOMPLETE_RESPONSE = 0, TLM_GENERIC_ERROR_RESPONSE = -1, TLM_ADDRESS_ERROR_RESPONSE = -2,
   TLM_COMMAND_ERROR_RESPONSE = -3, TLM_BURST_ERROR_RESPONSE = -4, TLM_BYTE_ENABLE_ERROR_RESPONSE = -5
   }
   ---
   - *delay*              Shunt tlm header extension equal to b_transport/nb_trasport delay attribute

   - *tlm_phase*          Shunt tlm header nb_trasport attribute:

   --- Code
   enum  tlm_phase_enum {
   UNINITIALIZED_PHASE =0, BEGIN_REQ =1, END_REQ, BEGIN_RESP,END_RESP
   }
   ---

   - *tlm_sync*         shunt tlm header nb_trasport attribute:

   --- Code
   enum  tlm_sync_enum { TLM_ACCEPTED, TLM_UPDATED, TLM_COMPLETED }
   ---

   - *tlm_extension_id*   tlm_extension id. if "0" extension is not available

*/

#if __BYTE_ORDER__== __ORDER_BIG_ENDIAN__
typedef struct cs_tlm_generic_payload_header_t {
  shunt_long_t option;
  shunt_long_t address;
  shunt_long_t command;
  shunt_long_t length;
  shunt_long_t byte_enable_length;
  shunt_long_t streaming_width;
  shunt_long_t dmi;
  shunt_long_t response_status;
  shunt_long_t delay;
  shunt_long_t tlm_phase;
  shunt_long_t tlm_sync;
  shunt_long_t tlm_extension_id;
} cs_tlm_generic_payload_header;
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
typedef struct cs_tlm_generic_payload_header_t {
  shunt_long_t tlm_extension_id;
  shunt_long_t tlm_sync;
  shunt_long_t tlm_phase;
  shunt_long_t delay;
  shunt_long_t response_status;
  shunt_long_t dmi;
  shunt_long_t streaming_width;
  shunt_long_t byte_enable_length;
  shunt_long_t length;
  shunt_long_t command;
  shunt_long_t address;
  shunt_long_t option;
} cs_tlm_generic_payload_header;
#endif

//---------------------------------------------------------------------------
// group: TLM enumeration types (extension of systemc tlm.h )
//---------------------------------------------------------------------------
/* Enum: shunt_tlm_command
   Ref to SystemC tlm_gp.h tlm_command enum for TLM_READ_COMMAND , TLM_WRITE_COMMAND, and TLM_IGNORE_COMMAND
  --- Code
typedef enum shunt_tlm_command {
    TLM_READ_COMMAND, //
    TLM_WRITE_COMMAND,
    TLM_IGNORE_COMMAND,
    SHUNT_TLM_END_SIM,  // end of Client simulation, send by Server
    SHUNT_TLM_START_SIM // start of simulation,send by Target
} shunt_dpi_tlm_command_e;
  ---
  */
typedef enum shunt_tlm_command {
    TLM_READ_COMMAND,
    TLM_WRITE_COMMAND,
    TLM_IGNORE_COMMAND,
    SHUNT_TLM_END_SIM,
    SHUNT_TLM_START_SIM
} shunt_dpi_tlm_command_e;

/* Enum: tlm_response_status
   cloned from SystemC tlm_gp.h tlm_response_status
  --- Code
  enum tlm_response_status {
    TLM_OK_RESPONSE = 1,
    TLM_INCOMPLETE_RESPONSE = 0,
    TLM_GENERIC_ERROR_RESPONSE = -1,
    TLM_ADDRESS_ERROR_RESPONSE = -2,
    TLM_COMMAND_ERROR_RESPONSE = -3,
    TLM_BURST_ERROR_RESPONSE = -4,
  ---
  */
enum tlm_response_status {
    TLM_OK_RESPONSE = 1,
    TLM_INCOMPLETE_RESPONSE = 0,
    TLM_GENERIC_ERROR_RESPONSE = -1,
    TLM_ADDRESS_ERROR_RESPONSE = -2,
    TLM_COMMAND_ERROR_RESPONSE = -3,
    TLM_BURST_ERROR_RESPONSE = -4,
    TLM_BYTE_ENABLE_ERROR_RESPONSE = -5
};

/* Enum: tlm_gp_option
   cloned from SystemC tlm_gp.h
  --- Code
  enum tlm_gp_option {
    TLM_MIN_PAYLOAD,
    TLM_FULL_PAYLOAD,
    TLM_FULL_PAYLOAD_ACCEPTED
};
  ---
  */
enum tlm_gp_option {
    TLM_MIN_PAYLOAD,
    TLM_FULL_PAYLOAD,
    TLM_FULL_PAYLOAD_ACCEPTED
};

/* Enum: tlm_phase_enum
   cloned from SystemC tlm_phase.h
  --- Code
  enum tlm_phase_enum
    {
    UNINITIALIZED_PHASE=0,
    BEGIN_REQ=1,
    END_REQ,
    BEGIN_RESP,
    END_RESP
  };
  ---
  */
enum tlm_phase_enum
{
  UNINITIALIZED_PHASE=0,
  BEGIN_REQ=1,
  END_REQ,
  BEGIN_RESP,
  END_RESP
};

/* Enum: tlm_sync_enum
   cloned from SystemC tlm_phase.h
  --- Code
 enum tlm_sync_enum {
    TLM_ACCEPTED,
    TLM_UPDATED,
    TLM_COMPLETED };
  ---
  */
enum tlm_sync_enum { TLM_ACCEPTED, TLM_UPDATED, TLM_COMPLETED };

/*
  Variable:   cs_tlm_axi3_extension_payload_header

  *TLM 2.0  ARM AXI3 signals extension structure*  REF to Copyright 2003, 2004, 2010, 2011 ARM. All rights reserved.ARM IHI 0022D (ID102711)

  --- Code
  //Big-endian view:
  typedef struct cs_tlm_axi3_extension_payload_header_t {
    shunt_long_t  AxBURST;
    shunt_long_t  AxCACHE;
    shunt_long_t  AxID;
    shunt_long_t  AxLEN;
    shunt_long_t  AxLOCK;
    shunt_long_t  AxPROT;
    shunt_long_t  AxSIZE;
    shunt_long_t  xRESP;
    shunt_long_t  xSTRB;
  } cs_tlm_axi3_extension_payload_header;
  ---

   - *AxBURST* - determines how the address for each transfer within the burst is calculated

   --- Code
   AxBURST[1:0] | Burst type
   =========================
   0b00         |  FIXED
   0b01         |  INCR
   0b10         |  WRAP
   0b11         |  Reserved
   ---

   *AxCACHE* - Memory type indicates how transactions are required to progress through a system

   --- Code
   AxCACHE | Value | Transaction attribute
    ======================================
    [0]    |   0   |    Non-bufferable
           |   1   |    Bufferable
    [1]    |   0   |    Non-cacheable
           |   1   |    Cacheable
    [2]    |   0   |    No Read-allocate
           |   1   |    Read-allocate
    [3]    |   0   |    No Write-allocate
           |   1   |    Write-allocate
   ---

   *AxID*  - is identification tag for the transaction address group.

   *AxLEN* - gives the exact number of transfers in a burst.

   *AxLOCK*  - provides additional information about the transaction atomic characteristics

   --- Code
   AxLOCK[1:0] | Access type
   =============================
   0b00        | Normal access
   0b01        | Exclusive access
   0b10        | Locked access
   0b11        | Reserved
   ---

   *AxPROT* - indicates the privilege and transaction security level.

   --- Code
    AxPROT | Value |     Function
    =====================================
    [0]    |   0   |  Unprivileged access
           |   1   |  Privileged access
    [1]    |   0   |  Secure access
           |   1   |  Non-secure access
    [2]    |   0   |  Data access
           |   1   |  Instruction access
    ---

    *AxSIZE* - indicates the size of each transfer in the burst.

    *xRESP*  - indicates the status of the read transfer.

    --- Code
    RRESP[1:0] |
    BRESP[1:0] | Response
    =====================
    0b00       | OKAY
    0b01       | EXOKAY
    0b10       | SLVERR
    0b11       | DECERR
    ---

    *xSTRB* -  indicates which byte lanes hold valid data.
*/




#if __BYTE_ORDER__== __ORDER_BIG_ENDIAN__
typedef struct cs_tlm_axi3_extension_payload_header_t {
  shunt_long_t  AxBURST;
  shunt_long_t  AxCACHE;
  shunt_long_t  AxID;
  shunt_long_t  AxLEN;
  shunt_long_t  AxLOCK;
  shunt_long_t  AxPROT;
  shunt_long_t  AxSIZE;
  shunt_long_t  xRESP;
  shunt_long_t  xSTRB;
} cs_tlm_axi3_extension_payload_header;
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
typedef struct cs_tlm_axi3_extension_payload_header_t {
  shunt_long_t  xSTRB;
  shunt_long_t  xRESP;
  shunt_long_t  AxSIZE;
  shunt_long_t  AxPROT;
  shunt_long_t  AxLOCK;
  shunt_long_t  AxLEN;
  shunt_long_t  AxID;
  shunt_long_t  AxCACHE;
  shunt_long_t  AxBURST;
} cs_tlm_axi3_extension_payload_header;
#endif
#endif //#ifndef SHUNT_TYPEDEF_H

