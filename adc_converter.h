#ifndef ADC_CONVERTER_H
#define ADC_CONVERTER_H

#include <systemc-ams>
#include <math.h>

using namespace std;

template<int NBits>
SCA_TDF_MODULE(adc_converter) {
    sca_tdf::sca_in<double> in;
    sca_tdf::sca_out<sc_dt::sc_int<NBits>> out;

    adc_converter(sc_core::sc_module_name nm, double v_max_,
        sca_core::sca_time Tm_ = sca_core::sca_time(125, sc_core::SC_MS))
        : in("in"), out("out"), v_max(v_max_), Tm(Tm_) {
            sc_assert((2 <= NBits) && (NBits <= 64));
            sc_assert(v_max_ > 0.0);
    }

    void set_attributes() {
        set_timestep(Tm);
    }

    void processing() {
        double v_in = in.read();

        if (v_in < -v_max) {
            out.write(-(pow(2, NBits-1)-1));
        } else if (v_in > v_max) {
            out.write((pow(2, NBits-1)-1));
        } else {
            sc_dt::sc_int<NBits> q_v_in = lround((v_in / v_max) * (pow(2, NBits-1)-1));
            out.write(q_v_in);
        }
    }

    private:
        const double v_max;
        sca_core::sca_time Tm;
};

#endif
