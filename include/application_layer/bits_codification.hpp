#ifndef BITS_CODIFICATION_HPP
#define BITS_CODIFICATION_HPP

#include <string>
#include <types.hpp>

using namespace std;

bitstream string_to_bits(string text);

string bits_to_string(bitstream bits);

string bitstream_printing(bitstream bits);

#endif