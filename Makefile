export SYSTEMC_HOME=/usr/local/systemc-2.3.2
export SYSTEMC_AMS_HOME=/usr/local/systemc-ams-2.3
export LD_LIBRARY_PATH=$(SYSTEMC_AMS_HOME)/lib-linux64/:$(SYSTEMC_HOME)/lib-linux64/

compile:
	@echo "Compiling"
	@g++ -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-linux64 -I$(SYSTEMC_AMS_HOME)/include -L$(SYSTEMC_AMS_HOME)/lib-linux64 \
	tb.cpp microphone.cpp filter.cpp AudioCapture.cpp generic_initiator_target.cpp -lsystemc -lsystemc-ams -lm -o ams.o

run:
	@echo "Running"
	@./ams.o
