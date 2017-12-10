include ./Sim.mk
-include ../../../../utils/makefile.init

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

