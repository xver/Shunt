-include ../../../../utils/makefile.init
make_all:
	cd ../initiator/makedir && $(MAKE) clean && $(MAKE) all
	cd ../target/makedir    && $(MAKE) clean && $(MAKE) all
all: make_all
	./run
.PHONY: run

run: 
	./run

