//Bibliotecas Externas
#include <gtk/gtk.h>
#include <cairo.h>
#include <bits/stdc++.h>

//Bibliotecas do simulador
#include <phisical_layer/carrier_modulation.hpp>
#include <phisical_layer/digital_modulation.hpp>
#include <application_layer/bits_codification.hpp>

//Declaração de todos os Widgest e métodos para manipula-los
#include <gui/gui.hpp> 

using namespace std;

static void enviar(GtkButton *button, gpointer user_data) {
    //Camada de Aplicação
    string messagem = get_text_view_value(text_mensagem);
    bitstream bits = string_to_bits(messagem);
    //g_print(bits_to_string(bits).c_str());

    //Camada de Enlace



    //Camada Física
   
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
    if (!gtk_builder_add_from_file(builder, "./include/gui/gui.xml", &error)) {
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