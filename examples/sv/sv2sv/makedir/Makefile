include ./Sim.mk
-include ../../../../utils/makefile.init


SHUNT_VERILATOR_FLAGS = -CFLAGS "-I${SHUNT_HOME}/utils/dpi/include" -CFLAGS "-I${SHUNT_HOME}/utils/c/include" -cc ${SHUNT_HOME}/utils/dpi/include/shunt_verilator_dpi.svh ${SHUNT_HOME}/utils/dpi/src/shunt_dpi_pkg.sv  -LDFLAGS "${SHUNT_HOME}/bin/libutils.so"

export SHUNT_VERILATOR_FLAGS

ifeq (${VERILATOR},)
export VERILATOR = verilator
endif

build_c:
	cd ${SHUNT_HOME}/utils/makedir &&  $(MAKE) clean && $(MAKE) all

build_sv: build_c
ifeq ($(SIM),verilator)
	cd ../initiator/makedir &&  $(MAKE) clean && $(MAKE) compile_$(SIM)_sv
	cd ../target/makedir    &&  $(MAKE) clean && $(MAKE) compile_$(SIM)_sv
else
	cd ../initiator/makedir &&  $(MAKE) clean && $(MAKE) $(SIM)
	cd ../target/makedir    &&  $(MAKE) clean && $(MAKE) $(SIM)
endif

.PHONY: run_initiator
run_initiator:
	cd ../initiator/makedir && ./$(SIM)_run

.PHONY: run_target
run_target:
	cd ../target/makedir  && ./$(SIM)_run	

.PHONY:	clean
clean: 
	cd ${SHUNT_HOME}/bin && rm -rf *
	cd ../initiator/makedir &&  $(MAKE) clean
	cd ../target/makedir    &&  $(MAKE) clean
all: clean build_c build_sv 

