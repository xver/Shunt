/*
============================================================================
 File        : shunt.i
 Copyright (c) 2016-2023 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
Description : TCP/IP Python SHUNT swig interface 
 ============================================================================
*/

%module shunt
%{
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


typedef long long shunt_long_t;

%include "../utils/c/include/shunt_typedef.h"
%include "../utils/c/include/shunt_primitives.h"
%include "../utils/c/include/shunt_client_server.h"
%include "../utils/c/include/shunt_user_api.h"
