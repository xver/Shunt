import os
import sys
shunthome =  os.environ['SHUNT_HOME'] + "/bin" 
sys.path.insert(0,shunthome)
from shunt import *
h = cs_tlm_generic_payload_header()
print(h)