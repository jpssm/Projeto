//Tipo de dados básicos usado para simular fluxo de bits e sinais analógicos e digitais

#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <stdint.h>
using namespace std;

typedef int8_t byte;
typedef bool bit;
typedef int digital_sample;
typedef float analog_sample;

typedef vector<bit> bitstream;
typedef vector<double> analog_signal;
typedef vector<digital_sample> digital_signal;

#endif 