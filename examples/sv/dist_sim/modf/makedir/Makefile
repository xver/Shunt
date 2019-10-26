compile_verilator_sv:
	cd ../bin && ${VERILATOR}  -Wall  --trace -I../../rtl  -I../../include $(SHUNT_VERILATOR_FLAGS)  -f ../../include/$(MANIFEST_INC) -f ../../rtl/top_modified.f +define+modf --exe ../../makedir/sim_main.cpp	
	cd ../bin && make -C obj_dir -j -f Vshunt_verilator_dpi.mk Vshunt_verilator_dpi
compile_verilator_xml_parser:
	cd ../bin && ${VERILATOR}  -Wall  --trace --xml-only -I../../rtl  -I../../include $(SHUNT_VERILATOR_FLAGS)  -f ../../include/$(MANIFEST_INC) -f ../../rtl/top.f +define+modf --exe ../../makedir/sim_main.cpp
.PHONY: clean
clean:	
	cd ../bin && rm -rf *
all: compile_verilator_sv
