include ./Sim.mk
-include ../../../../utils/makefile.init

export SHUNT_VERILATOR_FLAGS

ifeq (${VERILATOR},)
export VERILATOR = verilator
endif

ifeq ($(MANIFEST_INC),)
export MANIFEST_INC = inc.f 
endif

build_c:
	cd ${SHUNT_HOME}/utils/makedir &&  $(MAKE) clean && $(MAKE) all

build_orgn_sv: build_c
ifeq ($(SIM),verilator)
	cd ../orgn/makedir &&  $(MAKE) clean && $(MAKE) compile_$(SIM)_sv
endif

build_modf_sv: build_c
ifeq ($(SIM),verilator)
	cd ../modf/makedir &&  $(MAKE) clean && $(MAKE) compile_$(SIM)_sv
endif

build_anchor_sv: build_c
ifeq ($(SIM),verilator)
	cd ../anchor/makedir && $(MAKE) compile_$(SIM)_sv
endif

build_anchor_sv_srv: build_c
ifeq ($(SIM),verilator)
	cd ../anchor/makedir_srv && $(MAKE) compile_$(SIM)_sv
endif

.PHONY: run_anchor
run_anchor:
	cd ../anchor/makedir  && ./$(SIM)_run

.PHONY: run_anchor
run_anchor_srv:
	cd ../anchor/makedir_srv  && ./$(SIM)_run

.PHONY: run_orgn
run_orgn:
	cd ../orgn/makedir  && ./$(SIM)_run

.PHONY: run_modf
run_modf:
	cd ../modf/makedir  && ./$(SIM)_run

.PHONY:	clean
clean_all: 
	cd ${SHUNT_HOME}/bin && rm -rf *
	cd ../orgn/makedir        &&  $(MAKE) clean
	cd ../modf/makedir        &&  $(MAKE) clean
	cd ../anchor/makedir      &&  $(MAKE) clean
	cd ../anchor/makedir_srv  &&  $(MAKE) clean
all: clean build_c build_sv 

