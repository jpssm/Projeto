#include <application_layer/bits_codification.hpp>

using namespace std;

//Codificação em bts
bitstream string_to_bits(string text){
    bitstream bits;
    for(char c:text){
        for(unsigned char i =0 ; i < 8 ; i++){
            bits.push_back((c & (1 << i)) > 0);
        }
    }
    return bits;
}

//Decodificação de bits
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


//Impressão de fluxo de bits
string bitstream_printing(bitstream bits){
    string s;
    for(bit b:bits){
        s.push_back((char)(b+48)); //0 ASCII = 48
    }
    s.push_back(0); // \0 no final para indicar fim da string
    return s;
}
