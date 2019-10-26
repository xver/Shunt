compile_verilator_sv:
	cd ../bin_srv && ${VERILATOR}  -Wall  --trace -I../../rtl  -I../../include $(SHUNT_VERILATOR_FLAGS)  -f ../../include/$(MANIFEST_INC) -f ../../rtl/top_anchor_srv.f +define+anchor --exe ../../makedir/sim_main.cpp	
	cd ../bin_srv && make -C obj_dir -j -f Vshunt_verilator_dpi.mk Vshunt_verilator_dpi
.PHONY: clean
clean:	
	cd ../bin_srv && rm -rf *
all: compile_verilator_sv
