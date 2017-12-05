compile_sv:
	cd ../bin && echo ${PWD} "<COMPLE_SV PLACEHOLDER ${SHUNT_HOME}/utils/dpi/src/shunt_dpi_pkg.sv ../src/Initiator.sv>"
compile_verilator_sv:
	cd ../bin && verilator  -Wall ../../includes/cs_common.svh $(SHUNT_VERILATOR_FLAGS)  ../src/Initiator.sv --exe ../../makedir/sim_main.cpp
	cd ../bin && make -C obj_dir -j -f Vcs_common.mk Vcs_common
.PHONY: clean
clean:	
	cd ../bin && rm -rf *
all: compile_sv
