#include <link_layer/framming.hpp>
#include <types.hpp>
#include <iostream>
#include <gtk/gtk.h>

//Insere um valor com uma quantidade de bits específica em um bitsream
void insert_header(int value, bitstream *bits){
    for (int i = 0; i < 16; i++){
        bits->push_back((value & (1<<i))!=0);
    }
}

int get_header(bitstream *bits){
    int header = 0;
    for (int i = 0; i < 16; i++){
        header |= bits->at(i)<<i;
    }
    return header;
}




bitstream bytes_counting_framing(bitstream load, int max_frame_size) {
    bitstream frames;

    unsigned total_bytes = load.size()/8;
    int remaining_byts ;
    int payload_max_bytes = max_frame_size- 2; // 2 bytes para o cabeçalho

    for (int i_byte = 0; i_byte < total_bytes; ) {
        int remaining_bytes = total_bytes- i_byte;
        int payload_bytes = min(payload_max_bytes, remaining_bytes);

        // Insere o cabeçalho com tamanho em bytes
        insert_header(payload_bytes, &frames);

        // Insere a carga útil correspondente (payload_bytes * 8 bits)
        int bytes_to_copy = payload_bytes;
        frames.insert(frames.end(), load.begin() + i_byte*8, load.begin() + i_byte*8 + bytes_to_copy*8);

        i_byte += bytes_to_copy;
    }

    return frames;
}

bitstream bytes_counting_unframing(bitstream frames) {
    bitstream load;
    int i_bit = 0;

    while (i_bit + 16 <= frames.size()) {
        // Lê o cabeçalho
        bitstream header_bits(frames.begin() + i_bit, frames.begin() + i_bit + 16);
        int payload_bytes = get_header(&header_bits);
        i_bit += 16;

        int payload_bits = payload_bytes * 8;

        // Verifica se há bits suficientes
        //if (i_bit + payload_bits > frames.size()) break;

        // Extrai a carga útil
        load.insert(load.end(), frames.begin() + i_bit, frames.begin() + i_bit + payload_bits);
        i_bit += payload_bits;
    }

    return load;
}
