-include ../../../../utils/makefile.init

make_all: clean
	cd ../../../../utils/makedir && $(MAKE) all
	cd ../initiator/makedir && $(MAKE) all
	cd ../target/makedir    && $(MAKE) all
all: make_all
	./run
.PHONY: run

clean:
	cd ../../../../utils/makedir && $(MAKE) clean
	cd ../initiator/makedir && $(MAKE) clean
	cd ../target/makedir    && $(MAKE) clean
run: 
	./run

