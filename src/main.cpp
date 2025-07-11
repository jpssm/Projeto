//Bibliotecas Externas
#include <gtk/gtk.h>
#include <cairo.h>
#include <bits/stdc++.h>

//Bibliotecas do simulador

#include <phisical_layer/carrier_modulation.hpp>
#include <phisical_layer/digital_modulation.hpp>
#include <link_layer/framming.hpp>
#include <application_layer/bits_codification.hpp>

//Declaração de todos os Widgest e métodos para manipula-los
#include <gui/gui.hpp> 

using namespace std;


int protocolo;
int codigo_correcao_erro;
bool codificacao_digital;
int tipo_codificacao;
int tipo_modulacao;
bool modulacao_portadora;

int num_frames;

static void enviar(GtkButton *button, gpointer user_data) {
    //Camada de Aplicação
    string messagem = get_text_view_value(text_mensagem);
    bitstream bits = string_to_bits(messagem);
    
    
    //g_print("\nUnframe_size = %d", unframe.size());

    //Camada de Enlace
    bitstream frames;
    int tamanho_maximo_quadro = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_tamanho_quadro));
    protocolo = gtk_combo_box_get_active(GTK_COMBO_BOX(cbox_protocolo));
    if(protocolo < 1){ //Contagem de Bytes
        protocolo = 1;
        frames = bytes_counting_framing(bits, tamanho_maximo_quadro);
        num_frames = (int)ceil(frames.size()/(4.0*8));
    }
    else{
        g_print("ERRO: %d", protocolo);
        sleep(10);
    }
    set_text_view_value(text_bits_frames, bitstream_printing(frames));

/*
    //Camada Física
    digital_signal d_signal;
    analog_signal a_signal;
    if(is_radio_button_active(radio_button_codificacao)){
        codificacao_digital = true;
        modulacao_portadora = false;
        tipo_codificacao = gtk_combo_box_get_active(GTK_COMBO_BOX(cbox_codificacao));
        if (tipo_codificacao == 0){ //NRZ Polar
            d_signal = nrzp_encode(frames);
        }
        else if(tipo_codificacao == 1){ //Machester
            d_signal = manchester_encode(frames);
        }
        else if (tipo_codificacao == 2){ //Bipolar
            d_signal = bipolar_encode(frames);
        }
        
    }
    else if(is_radio_button_active(radio_button_modulacao)){
        modulacao_portadora = true;
        codificacao_digital = false;
        tipo_modulacao = gtk_combo_box_get_active(GTK_COMBO_BOX(cbox_modulacao));

        if (tipo_modulacao == 0){ //ASK
            a_signal = ask_encode(frames);
        }
        else if(tipo_modulacao == 1){ //FSK
            a_signal = fsk_encode(frames);
        }
        else if (tipo_modulacao == 2){ //8QAM
            a_signal = qam8_encode(frames);
        }
    }

   */
}

void on_window_destroy(GtkWidget *widget, gpointer user_data) {
    gtk_main_quit(); // Encerra o loop principal do GTK
}
int main(int argc, char** argv){
    GtkBuilder *builder;

    
    GError *error = NULL;

    // Inicializa o GTK
    gtk_init(&argc, &argv);

    // Cria um GtkBuilder
    builder = gtk_builder_new();

    // Carrega o arquivo Glade
    if (!gtk_builder_add_from_file(builder, "./include/gui/transmissor.xml", &error)) {
        g_printerr("Erro ao carregar o arquivo Glade: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }


    // Inicializa todos os widgets a serem manipulados
    initialize_widgets(builder);

    // Conecta os sinais automaticamente definidos no Glade às funções de callback
    gtk_builder_connect_signals(builder, NULL);

    // Conecta o sinal de fechar a janela manualmente a função de saída
    g_signal_connect(Janela_Transmissor, "destroy", G_CALLBACK(on_window_destroy), NULL);

    //Conecta sinal do botão enviar a função "enviar"
    g_signal_connect(botao_enviar, "clicked", G_CALLBACK(enviar), NULL);

    // Se você tiver outros sinais definidos no Glade, ainda pode usar:
    //gtk_builder_connect_signals(builder, NULL);


    // Exibe a janela
    gtk_widget_show_all(Janela_Transmissor);

    // Inicia o loop principal do GTK
    gtk_main();

    // Libera o builder
    g_object_unref(builder);

    return 0;
}