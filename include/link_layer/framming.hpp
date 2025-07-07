#ifndef FRAMMING_HPP
#define FRAMMING_HPP

#include <types.hpp>

void insert_bits(short value, int size, bitstream *bits);

bitstream bytes_counting_framing(bitstream load, int max_frame_size);
bitstream bytes_counting_unframing(bitstream load);

#endif