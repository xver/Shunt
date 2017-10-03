compile_sv:
	vlib ../bin/work
	cd ../bin && vlog ${SHUNT_HOME}/utils/dpi/src/shunt_dpi_pkg.sv ${SHUNT_HOME}/utils/dpi/src/shunt_hs_pkg.sv ../src/Target.sv

.PHONY: clean
clean:	
	cd ../bin && rm -rf *
all: compile_sv
