export SYSTEMC_HOME=/usr/local/systemc-2.3.2
export SYSTEMC_AMS_HOME=/usr/local/systemc-ams-2.3
export LD_LIBRARY_PATH=$(SYSTEMC_AMS_HOME)/lib-linux64/:$(SYSTEMC_HOME)/lib-linux64/

compile_audio_capture:
	@echo "Compiling"
	@g++ -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-linux64 -I$(SYSTEMC_AMS_HOME)/include -L$(SYSTEMC_AMS_HOME)/lib-linux64 \
	tb_audio_capture.cpp microphone.cpp filter_decoup.cpp AudioCapture.cpp generic_initiator_target.cpp -lsystemc -lsystemc-ams -lm -o audio_capture.o

compile_channel:
	@echo "Compiling"
	@g++ -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-linux64 -I$(SYSTEMC_AMS_HOME)/include -L$(SYSTEMC_AMS_HOME)/lib-linux64 \
	protocol_gen.cpp filter.cpp mixer.cpp rectifier.cpp sampler.cpp tb_channel.cpp carrier.cpp -lsystemc -lsystemc-ams -lm -o channel.o

run_audio_capture:
	@echo "Running"
	@./audio_capture.o

run_channel:
	@echo "Running"
	@./channel.o
