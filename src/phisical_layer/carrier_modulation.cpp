#include <phisical_layer/carrier_modulation.hpp>
#include <math.h>


#define NUM_SAMPLES 20
//Amplitude Shift Keying modulation
analog_signal ask_encode(bitstream bits){
    analog_signal s;
    for (bit b:bits){
        for (int i = 1; i <= NUM_SAMPLES; i++){
            s.push_back(sin(2*M_PI*i/NUM_SAMPLES)*b);
        }
    }
    return s;
};
bitstream ask_decode(analog_signal received){
    bitstream bits;
    for (int cicle_i = 0; cicle_i < received.size(); cicle_i+=NUM_SAMPLES){
        double energy = 0;
        for (int sample_i = 0; sample_i < NUM_SAMPLES; sample_i++){ //10 amostrar por ciclo
            energy+=abs(received[cicle_i+sample_i]);
        }
        //Integral idefinida de 0 a 2pi de |sen(x)| é igual a 4, margem erro de 30% para ruído
        if (energy >= 2.8){ //Se a amostra tem o mínimo de energia é interpretada como bit 1
            bits.push_back(1);
        }
        else{
            bits.push_back(0);
        }
    }
    return bits;
};

//Frequency Shift Keying
analog_signal fsk_encode(bitstream bits){
    analog_signal s;
    for (bit b:bits){
        for (int i = 0; i < NUM_SAMPLES; i++){
            s.push_back(sin((1+b)*2*M_PI*i/NUM_SAMPLES));
            //Bit 0: frequencia = 1
            //Bit 1: frequencia = 2
        }
    }
    return s;
};
bitstream fsk_decode(analog_signal received){
    bitstream bits;
    int V =1;
    for (int cicle_i = 0; cicle_i < received.size(); cicle_i+=NUM_SAMPLES){
        int polarity= -1;
        int half_cycles = 0;
        for (int sample_i = 0; sample_i < NUM_SAMPLES; sample_i++){ //10 amostrar por simbolo
            //Se atingiu um novo pico de polaridade inversa ao último
            if(abs(received[cicle_i+sample_i]) > 0.8*V && received[cicle_i+sample_i]*polarity  < 0){
                    half_cycles++;
                    polarity *=-1;
            }    
        }
        bits.push_back(half_cycles/2-1);
        //Bit 0: frequencia = 1
        //Bit 1: frequencia = 2
    }
    return bits;
};

//8-Quadrature Amplitude Modulation
analog_signal qam8_encode(bitstream bits){
};
bitstream qam8_decode(analog_signal received){

};