#/*
#============================================================================
# File        : initiator.py
#Copyright (c) 2016-2023 IC Verimeter. All rights reserved.
#               Licensed under the MIT License.
#               See LICENSE file in the project root for full license information.
# Description : Initiator(server) TCP/IP Python SHUNT example
# ============================================================================
#*/
import os
import sys
shunthome =  os.environ['SHUNT_HOME'] + "/bin" 
sys.path.insert(0,shunthome)
from shunt import *
h = cs_tlm_generic_payload_header()
print(h)
