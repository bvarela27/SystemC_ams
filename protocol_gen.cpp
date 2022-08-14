#include "protocol_gen.h"

void protocol_gen::processing() {
    out.write((bool)(std::rand()%2) );
}
