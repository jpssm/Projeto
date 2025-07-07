#include <application_layer/bits_codification.hpp>

using namespace std;


bitstream string_to_bits(string text){
    bitstream bits;
    for(char c:text){
        for(unsigned char i =0 ; i < 8 ; i++){
            bits.push_back((c & (1 << i)) > 0);
        }
    }
    return bits;
}

string bits_to_string(bitstream bits){
    string text;
    char c;
    int total =  bits.size();
    for (int i_byte = 0; i_byte < total; i_byte+=8){
        c = 0;
        for (int i_bit = 0; i_bit <8 && i_byte+i_bit < total; i_bit++){
            c |= bits[i_byte+i_bit]<< i_bit; //bitmask
        }
        text.push_back(c);
    }
    return text;
}