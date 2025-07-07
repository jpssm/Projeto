#include <link_layer/framming.hpp>
#include <types.hpp>


//Insere uma quantidade de bits específica ao final do bitstream
void insert_bits(short value, int num_bits, bitstream *bits){
    for (int i = 0; i < num_bits; i++){
        bits->push_back((value && 1<<i)>0);
    }
}

//Enquadra o fluxo de bits, sempre reservando 2 bytes para o cabeçalho
bitstream bytes_counting_framing(bitstream load, int max_frame_size){
    bitstream frames; //Fluxo de bits com todos os frames
    unsigned byte_counting = load.size()/8;
    max_frame_size-=2;//Reserva 2 bytes para o cabeçalho

    //Se é possível alocar em um único quadro
    if(byte_counting <= max_frame_size){ 
        insert_bits(byte_counting+2, 16, &load);
        frames.insert(frames.end(), load.begin(), load.end());
    }
    //Caso contrário monta vários quadros
    else{
        int remaing_bits; //Contagem de bits restantes
        //Monta um quadro para cada sequencia com tamanho maximo de bits
        for(int i_frame=0; i_frame < byte_counting*8; i_frame+=(max_frame_size)){
            remaing_bits = byte_counting*8-i_frame-1;
            //Se ainda existem bits suficientes para formar novos quadros;
            if(remaing_bits >= (max_frame_size)*8){
                //Cabeçalho
                insert_bits(max_frame_size, 16, &load);
                //Carga útil
                frames.insert(frames.end(), load.begin() + i_frame, 
                            load.begin() + i_frame + max_frame_size*8);
            }
            else{ //Caso contrário monta um quadro com o restante de bits
                insert_bits(remaing_bits/8, 16, &load);
                frames.insert(frames.end(), load.begin() + i_frame, 
                            load.begin() + i_frame + remaing_bits);
            }
        }
    }
    return frames;
}


//Desenquadra o fluxo de bits;
bitstream bytes_counting_unframing(bitstream frames){
    bitstream load;
    int i = 0;
    int frame_size ;
    while(i < frames.size()){
        frame_size = 
    }
}
