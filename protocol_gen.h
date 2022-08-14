#ifndef PROTOCOL_GEN_H
#define PROTOCOL_GEN_H

#include "systemc-ams.h"

SCA_TDF_MODULE(protocol_gen) {
    sca_tdf::sca_out<bool> out; // output port

    SCA_CTOR(protocol_gen): out("out") {

    }

    void processing();
};

#endif
