#ifndef HAMMING_ENCODER
#define HAMMING_ENCODER

#include <iostream>
#include "systemc.h"
#include <stdlib.h>
#include <queue>
#include "register_map.h"

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#define N_HAMMING 31
#define K_HAMMING 26
#define M_HAMMING N_HAMMING-K_HAMMING

using namespace std;

SC_MODULE(HammingEnc) {
    sc_event event_thread_process;

    // Queues
    queue<tlm::tlm_generic_payload*> trans_pending;
    tlm_utils::simple_target_socket<HammingEnc> target_socket;
    tlm_utils::simple_initiator_socket<HammingEnc> initiator_socket;

    SC_CTOR(HammingEnc): target_socket("target_socket"), initiator_socket("initiator_socket") {
        target_socket.register_nb_transport_fw(this, &HammingEnc::nb_transport_fw);
        initiator_socket.register_nb_transport_bw(this, &HammingEnc::nb_transport_bw);
        SC_THREAD(thread_process);
    }

    void thread_process();

    virtual tlm::tlm_sync_enum nb_transport_fw( tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay );
    virtual tlm::tlm_sync_enum nb_transport_bw( tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay );
};

#endif
