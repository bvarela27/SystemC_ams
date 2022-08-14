#ifndef BASK_MOD_H
#define BASK_MOD_H

#include "systemc-ams.h"

#include "mixer.h"
#include "carrier.h"

SC_MODULE(bask_mod) {
    sca_tdf::sca_in<bool>    in;
    sca_tdf::sca_out<double> out;
	
    carrier carrier_inst;
    mixer   mix;

    SCA_CTOR(bask_mod): in("in"),out("out"),
        carrier_inst("carrier", 1.0e7, sca_core::sca_time( 5.0, sc_core::SC_NS ) ),
        mix("mix") {

        // Connections
        carrier_inst.out(carrier_signal);
        mix.in_wav(carrier_signal);
        mix.in_bin(in);
        mix.out(out);
    }

    private:
        sca_tdf::sca_signal<double> carrier_signal;
};

#endif