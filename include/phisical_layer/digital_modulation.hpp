#ifndef DIGITAL_MODULATION_HPP
#define DIGITAL_MODULATION_HPP


#include <types.hpp>

//Non-return to Zero Polar modulation
digital_signal nrzp_encode(bitstream bits);
bitstream nrzp_decode(digital_signal received);

//Manchester modulation
digital_signal manchester_encode(bitstream bits);
bitstream manchester_decode(digital_signal received);

//Bipolar modulation
digital_signal bipolar_encode(bitstream bits);
bitstream bipolar_decode(digital_signal received);

#endif