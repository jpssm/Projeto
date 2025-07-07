#ifndef CARRIER_MODULATION_HPP
#define CARRIER_MODULATION_HPP

#include <types.hpp>

//Amplitude Shift Keying modulation
analog_signal ask_encode(bitstream bits);
bitstream ask_decode(analog_signal received);

//Frequency Shift Keying
analog_signal fsk_encode(bitstream bits);
bitstream fsk_decode(analog_signal received);

//8-Quadrature Amplitude Modulation
analog_signal qam8_encode(bitstream bits);
bitstream qam8_decode(analog_signal received);

#endif