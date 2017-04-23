/*
============================================================================
 File        : svcs_dpi_pkg.sv
 Author      : Victor Besyakov
 Version     : 0.0.0
 Copyright (c) 2016 IC Verimeter. All rights reserved.
               Licensed under the MIT License.
               See LICENSE file in the project root for full license information.
 Description :  prim function svcs dpi bridge test 

               System Verilog client server handshake (SVCS) library SV domain
 ============================================================================
*/
package svcs_dpi_pkg; 
   
   import "DPI-C" function int svcs_dpi_server_init (input int portno);
   import "DPI-C" function int svcs_dpi_client_init (input int portno,input string hostname);
   
   import "DPI-C" function int svcs_dpi_send_int    (input int sockfd,input  int Int);
   import "DPI-C" function int svcs_dpi_recv_int    (input int sockfd,output int Int);
   
   import "DPI-C" function int svcs_dpi_send_real   (input int sockfd,input  real Real);
   import "DPI-C" function int svcs_dpi_recv_real   (input int sockfd,output real Real);
   
endpackage : svcs_dpi_pkg
   
  
