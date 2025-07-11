#ifndef GUI_HPP
#define GUI_HPP

#include <gtk/gtk.h>
#include <string>

using namespace std;

// GtkWindow
extern GtkWidget *Janela_Transmissor;

// GtkDrawingArea
extern GtkWidget *grafico_codificação;
extern GtkWidget *grafico_modulação;

// GtkComboBox
extern GtkWidget *cbox_codificacao;
extern GtkWidget *cbox_modulacao;
extern GtkWidget *cbox_protocolo;
extern GtkWidget *cbox_codigo;
extern GtkWidget *cbox_paridade;

// GtkRadioButton
extern GtkWidget *radio_button_codificacao;
extern GtkWidget *radio_button_modulacao;

// GtkSpinButton
extern GtkWidget *spin_tamanho_quadro;
extern GtkWidget *spin_frequencia;

// GtkTextView
extern GtkWidget *text_bits_head;
extern GtkWidget *text_bits_tail;
extern GtkWidget *text_paridade;
extern GtkWidget *text_bits_EDAC;
extern GtkWidget *text_tempo_bit;
extern GtkWidget *text_bit_simbolo;
extern GtkWidget *text_mensagem;
extern GtkWidget *text_bits;
extern GtkWidget *text_bits_frames;

// GtkListStore
//extern GtkWidget *list_códigos_de_erro;
//extern GtkWidget *list_enquadramento;
//extern GtkWidget *list_paridade;
//extern GtkWidget *list_codificacao;
//extern GtkWidget *list_modulacao;

//GtkEntry 
extern GtkWidget *entry_polinomio;

// GtkScale
extern GtkWidget *scale_tempo;

// GtkButton
extern GtkWidget *botao_enviar;



//Inicializar os widgets
void initialize_widgets(GtkBuilder *builder);

//Manipulação dos Widgets
gboolean is_radio_button_active(GtkWidget *widget);
string get_text_view_value(GtkWidget *widget);
void set_text_view_value(GtkWidget *widget, string text);
string get_combo_box_value(GtkWidget *widget);
#endif
