from distutils.core import setup, Extension
import os
import sys
shunthome =  os.environ['SHUNT_HOME'] + "/utils"

name = "shunt"      # name of the module
version = "0.1"     # the module's version number

setup(name=name,
      version=version,
      ext_modules=[Extension(name='_shunt',
                             sources=[shunthome + "/py/src/shunt.i",
                                      shunthome + "/c/src/shunt_primitives.c",
                                      shunthome + "/c/src/shunt_client_server.c",
                                      shunthome + "/c/src/shunt_user_api.c"],
                             include_dirs=[shunthome + '/py/src',
                                           shunthome + '/sc/src',
                                           shunthome +'/c/include',
                                           shunthome +'/c/src'])
                   ])
