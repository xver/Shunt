-include ../../../../utils/makefile.init
make_all:
	cd ../initiator/makedir && $(MAKE) clean && $(MAKE) all
	cd ../target/makedir    && $(MAKE) clean && $(MAKE) all
all: make_all
	./run
.PHONY: run

initiator: 
	cd ../initiator/makedir && $(MAKE) clean && $(MAKE) all

target:
	cd ../target/makedir    && $(MAKE) clean && $(MAKE) all	

clean:
	cd ../initiator/makedir && $(MAKE) clean
	cd ../target/makedir    && $(MAKE) clean
run: 
	./run

