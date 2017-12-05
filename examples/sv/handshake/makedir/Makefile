
build_c:
	cd ${SHUNT_HOME}/utils/makedir &&  $(MAKE) clean && $(MAKE) all

build_sv:
	cd ../initiator/makedir &&  $(MAKE) clean && $(MAKE) all
	cd ../target/makedir    &&  $(MAKE) clean && $(MAKE) all

.PHONY: run_initiator
run_initiator: 
	cd ../initiator/makedir && ./run

.PHONY: run_target
run_target:
	cd ../target/makedir  && ./run	

.PHONY: clean
clean:
	cd ${SHUNT_HOME}/bin && rm -rf *
	cd ../initiator/makedir &&  $(MAKE) clean
	cd ../target/makedir    &&  $(MAKE) clean
all: clean build_c build_sv 

