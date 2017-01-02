
TITLE: 1. Introduction SVCS

(SVCS) System Verilog client server handshake
(start code)
******************************************************
Data Types: 
 
Elements:
         integer,  double, char

Vectors: 
         integers, doubles , string

Array/composite:
	  integer vectors , double vectors, messages , structure

-------------------------------------------------------
Common Data Structure:
			trnx -> header  ->  trnx_atribute  - hash/random double    
					    trnx_type      - hash double 
					    trnx_id        - random double 
                          
				payload -> size - int , >0   
				data
-------------------------------------------------------
vector:

element -> header ->   trnx_atribute - hash/random double     
                       trnx_type     - hash ("SVCS_V_INT","SVCS_V_DOUBLE","SVCS_V_STRING") 
                       trnx_id       - random double 
                       
           payload ->  size - if vector >1, if element = 1;    
                       data element;
---------------------------------------------------------------
array:
composite -> header ->     trnx_atribute - hash/random double    
                           trnx_type     - hash ("SVCS_A_STRUCTURE") 
                           trnx_id       - random double 
                           
             payload->     size - int , > 1   
                           data - vector  
---------------------------------------------------------------
(end)
 ============================================================================
 Copyright (c) 2016 IC Verimeter. All rights reserved.  
               Licensed under the MIT License. 
============================================================================= 