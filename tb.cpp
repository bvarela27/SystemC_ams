#include "systemc.h"
#include "systemc-ams.h"

#include "AudioFile.h"
#include "adc_converter.h"
#include "filter.h"
#include "microphone.h"
#include <math.h>

#define MICROPHONE_SAMPLE_FREQUENCY 44100.0
#define FILTER_CUTOFF_FREQUENCY     18000.0
#define FILTER_GAIN                 1.0
#define ADC_SAMPLE_FREQUENCY        8000.0
#define ADC_NUM_BITS                32
   
int sc_main (int argc, char* argv[]) {

    ////////////////////////////////////////////////////
    // Read WAV file
    AudioFile<double> audioFile;
    audioFile.load("speech.wav");

    int channel = 0;
    vector<double> samples = audioFile.samples[channel];

    ////////////////////////////////////////////////////
    // Microphone
    sca_tdf::sca_signal<double> microphone_out;
    sc_core::sc_time time_step_microphone((1.0/MICROPHONE_SAMPLE_FREQUENCY), sc_core::SC_SEC);
    microphone microphone0("microphone", samples, time_step_microphone);
    microphone0.out(microphone_out);

    ////////////////////////////////////////////////////
    // Filter
    sca_tdf::sca_signal<double> filter_out;
    filter filter0("filter", FILTER_CUTOFF_FREQUENCY, FILTER_GAIN);
    filter0.in(microphone_out);
    filter0.out(filter_out);

    ////////////////////////////////////////////////////
    // ADC converter
    sca_tdf::sca_signal<sc_dt::sc_int<ADC_NUM_BITS>> adc_out;
    sc_core::sc_time time_step_adc((1.0/ADC_SAMPLE_FREQUENCY), sc_core::SC_SEC);
    adc_converter<ADC_NUM_BITS> adc_converter0("adc_converter", (pow(2,ADC_NUM_BITS-1)-1), time_step_adc);
    adc_converter0.in(filter_out);
    adc_converter0.out(adc_out);

    ////////////////////////////////////////////////////
    // VCD File
    sca_util::sca_trace_file *vcdfile= sca_util::sca_create_vcd_trace_file("ams.vcd");
    sca_trace(vcdfile, microphone_out, "microphone_out");
    sca_trace(vcdfile, filter_out, "filter_out");
    sca_trace(vcdfile, adc_out, "adc_out");

    sc_start(1000, sc_core::SC_MS);

    sca_util::sca_close_vcd_trace_file(vcdfile);

	return 0;
}
