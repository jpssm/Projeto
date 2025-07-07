#include <phisical_layer/digital_modulation.hpp>
#include <stdlib.h>

//Non-return to Zero Polar modulation
digital_signal nrzp_encode(bitstream bits){
    digital_signal transmitted;
    int V = 1;
    for(bit b:bits){
        transmitted.push_back(V*(2*b-1));
        //Bit 0: V*(2*0-1)= -V
        //Bit 1: V*(2*1-1)= = V
    }
    return transmitted;
};
bitstream nrzp_decode(digital_signal received){
    bitstream bits;
    for(digital_sample s:received){
        bits.push_back(s>0);
        //Bit 0: -V > 0 igual a 0
        //Bit 1: V > 0 igual a 1
    }
    return bits;
};

//Manchester modulation
digital_signal manchester_encode(bitstream bits){
    digital_signal transmitted;
    for (int i = 0; i < bits.size()*2; i++){
        transmitted.push_back((i%2)^bits[i/2]);
        //Clock_i = i%2 : alterna entre 0 e 1
        //bit = bits[i/2]: dois clocks para cada bit 
    }
    return transmitted;
};

bitstream manchester_decode(digital_signal received){
    bitstream bits;
    for(int i = 0; i < received.size(); i+=2){
        if(received[i] == 0 && received[i+1] == 1){ //Padrão de subida (01) é bit 0
            bits.push_back(0);
        }
        else if(received[i] == 1 && received[i+1] == 0){ //Padrão de descida (10) é bit 1
            bits.push_back(1);
        }
    }
    return bits;
};

//Bipolar modulation
digital_signal bipolar_encode(bitstream bits){
    digital_signal transmitted;
    int V = 1;
    for (bit b:bits){
        transmitted.push_back(b*V);
        //Bit 0: 1*(+-V) = +-V
        //Bit 1: 0*(+-V) = 0
        if(b){//A cada bit 1 inverte a polaridade
            V*=-1; 
        }
    }
    return transmitted;
};
bitstream bipolar_decode(digital_signal received){
    bitstream bits;
    for(digital_sample sample:received){
        bits.push_back(abs(sample)&&1);
        //Bit 0: abs(0) && 1 = 0
        //Bit 1: abs(+-V) && 1 = 1
    }
    return bits;
};