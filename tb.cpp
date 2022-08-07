#include "systemc.h"
#include "systemc-ams.h"

#include "AudioCapture.h"
#include "HammingEnc.h"
#include <math.h>

int sc_main (int argc, char* argv[]) {
    ////////////////////////////////////////////////////
    // Audio Capture
    AudioCapture AudioCapture0("AudioCapture");

    ////////////////////////////////////////////////////
    // HammingEnc
    HammingEnc HammingEnc0("HammingEnc");

    ////////////////////////////////////////////////////
    // Router
    AudioCapture0.initiator_socket.bind( HammingEnc0.target_socket );
    HammingEnc0.initiator_socket.bind( AudioCapture0.target_socket );

    ////////////////////////////////////////////////////
    // VCD File
    sca_util::sca_trace_file *vcdfile= sca_util::sca_create_vcd_trace_file("ams.vcd");
    sca_trace(vcdfile, AudioCapture0.microphone_out, "microphone_out");
    sca_trace(vcdfile, AudioCapture0.filter_out, "filter_out");
    sca_trace(vcdfile, AudioCapture0.adc_out, "adc_out");

    sc_start(500, sc_core::SC_US);

    // FIXME
    // Update ACD sample frequency
    // This will be accessed through a register later
    /*AudioCapture0.adc_converter0.set_sample_frequency(MICROPHONE_SAMPLE_FREQUENCY_);
    // Update filter parameters
    AudioCapture0.filter0.set_gain(1);
    AudioCapture0.filter0.set_cutoff_frequency(1);

    sc_start(500, sc_core::SC_US);

    // FIXME
    // Update ACD sample frequency
    // This will be accessed through a register later
    AudioCapture0.adc_converter0.set_sample_frequency(ADC_SAMPLE_FREQUENCY_);*/

    sc_start(1000, sc_core::SC_MS);

    sca_util::sca_close_vcd_trace_file(vcdfile);

	return 0;
}
