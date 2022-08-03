#include "filter.h"

void filter::initialize() {
    num(0) = 1.0;
    den(0) = 1.0;
    den(1) = 1.0 /( 2.0* M_PI * fc );
}
 
void filter::processing() {
    double tmp = ltf_nd( num, den, in.read(), gain );
    out.write(tmp);
}
