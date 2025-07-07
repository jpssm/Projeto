#include <gtk/gtk.h>
#include <string>

#include <gui/gui.hpp> 

using namespace std;
// GtkWindow
GtkWidget *Janela_Transmissor;

// GtkDrawingArea
GtkWidget *grafico_codificação;
GtkWidget *grafico_modulação;

// GtkComboBox
GtkWidget *cbox_codificacao;
GtkWidget *cbox_modulacao;
GtkWidget *cbox_protocolo;
GtkWidget *cbox_codigo;
GtkWidget *cbox_paridade;

// GtkRadioButton
GtkWidget *radio_button_codificacao;
GtkWidget *radio_button_modulacao;

// GtkSpinButton
GtkWidget *spin_tamanho_quadro;
GtkWidget *spin_frequencia;

// GtkTextView
GtkWidget *text_bits_head;
GtkWidget *text_bits_tail;
GtkWidget *text_paridade;
GtkWidget *text_bits_EDAC;
GtkWidget *text_tempo_bit;
GtkWidget *text_bit_simbolo;
GtkWidget *text_mensagem;
GtkWidget *text_bits;

//GtkEntry 
GtkWidget *entry_polinomio;

// GtkScale
GtkWidget *scale_tempo;

// GtkButton
GtkWidget *botao_enviar;


gboolean is_radio_button_active(GtkWidget *widget) {
    // 1. Verificação de segurança para garantir que o widget é um GtkRadioButton.
    //    Isso evita erros de execução se um tipo de widget errado for passado.
    if (!GTK_IS_RADIO_BUTTON(widget)) {
        g_warning("O widget fornecido não é um GtkRadioButton.");
        return FALSE;
    }

    // 2. GtkRadioButton é uma subclasse de GtkToggleButton. A propriedade "active"
    //    pertence ao GtkToggleButton. Portanto, fazemos o cast para GtkToggleButton*
    //    e usamos a função gtk_toggle_button_get_active().
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
}

string get_text_view_value(GtkWidget *widget) {
    // 1. Verificação de segurança para garantir que o widget é um GtkTextView.
    if (!GTK_IS_TEXT_VIEW(widget)) {
        g_warning("O widget fornecido não é um GtkTextView.");
        return NULL;
    }

    // 2. O texto não está no GtkTextView, mas em seu GtkTextBuffer.
    //    Primeiro, obtemos o buffer.
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
    if (buffer == NULL) {
        g_warning("Não foi possível obter o GtkTextBuffer.");
        return NULL;
    }

    // 3. Para obter o texto, precisamos especificar o intervalo que queremos.
    //    Para obter todo o texto, precisamos de iteradores para o início e o fim.
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    // 4. Extrai o texto entre os iteradores 'start' e 'end'.
    //    O último argumento (FALSE) indica para não incluir caracteres ocultos.
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    string s(text);

    return s;
}

void set_text_view_value(GtkWidget *widget, string text) {
    // 1. Verificação de segurança para garantir que o widget é um GtkTextView.
    if (!GTK_IS_TEXT_VIEW(widget)) {
        g_warning("O widget fornecido não é um GtkTextView.");
        return;
    }

    // 2. Obtém o GtkTextBuffer associado ao GtkTextView.
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
    if (buffer == NULL) {
        g_warning("Não foi possível obter o GtkTextBuffer.");
        return;
    }

    // 3. Define o novo texto. A função gtk_text_buffer_set_text() apaga

    //    todo o conteúdo anterior e o substitui pelo novo texto.
    //    O -1 como terceiro argumento diz à função para calcular o comprimento
    //    da string 'new_text' automaticamente.
    gtk_text_buffer_set_text(buffer, text.c_str(), -1);
}

/*
string get_combo_box_value(GtkWidget *widget) {
    // 1. Verificação de segurança para garantir que o widget é um GtkComboBox.
    if (!GTK_IS_COMBO_BOX(widget)) {
        g_warning("O widget fornecido não é um GtkComboBox.");
        return NULL;
    }

    // 2. Faz o cast do GtkWidget* para GtkComboBox*.
    //    Agora podemos usar funções específicas de GtkComboBox.
    GtkComboBox *combo_box = GTK_COMBO_BOX(widget);

    // 3. Obtém o texto do item ativo.
    //    gtk_combo_box_get_active_text() é uma função conveniente que
    //    retorna o texto da coluna do modelo especificada para texto.
    //    Ela retorna uma nova string que deve ser liberada com g_free().
    gchar *active_text = gtk_combo_box_get_active_iter(combo_box);

    string s(active_text);

    return s;
}
*/


gdouble get_spin_button_value(GtkWidget *widget) {
    // 1. Verificação de segurança para garantir que o widget é um GtkSpinButton.
    if (!GTK_IS_SPIN_BUTTON(widget)) {
        g_warning("O widget fornecido não é um GtkSpinButton.");
        return 0.0;
    }

    // 2. Faz o cast do GtkWidget* para GtkSpinButton* e obtém o valor.
    //    A função gtk_spin_button_get_value() retorna o valor como um gdouble.
    return gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
}

string get_entry_value(GtkWidget *widget) {
    // 1. Verificação de segurança para garantir que o widget é um GtkEntry.
    if (!GTK_IS_ENTRY(widget)) {
        g_warning("O widget fornecido não é um GtkEntry.");
        return NULL;
    }

    // 2. Faz o cast do GtkWidget* para GtkEntry* e obtém o texto.
    //    A função gtk_entry_get_text() retorna um ponteiro para o buffer
    //    interno do entry.
    return string(gtk_entry_get_text(GTK_ENTRY(widget)));
}


void initialize_widgets(GtkBuilder *builder){
    Janela_Transmissor = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Transmissor"));
    grafico_codificação = GTK_WIDGET(gtk_builder_get_object(builder, "grafico_codificação"));
    grafico_modulação = GTK_WIDGET(gtk_builder_get_object(builder, "grafico_modulação"));
    cbox_codificacao = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_codificacao"));
    cbox_modulacao = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_modulacao"));
    cbox_protocolo = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_protocolo"));
    cbox_codigo = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_codigo"));
    cbox_paridade = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_paridade"));
    radio_button_codificacao = GTK_WIDGET(gtk_builder_get_object(builder, "radio_button_codificacao"));
    radio_button_modulacao = GTK_WIDGET(gtk_builder_get_object(builder, "radio_button_modulacao"));
    spin_tamanho_quadro = GTK_WIDGET(gtk_builder_get_object(builder, "spin_tamanho_quadro"));
    spin_frequencia = GTK_WIDGET(gtk_builder_get_object(builder, "spin_frequencia"));
    text_bits_head = GTK_WIDGET(gtk_builder_get_object(builder, "text_bits_head"));
    text_bits_tail = GTK_WIDGET(gtk_builder_get_object(builder, "text_bits_tail"));
    entry_polinomio = GTK_WIDGET(gtk_builder_get_object(builder, "entry_polinomio"));
    text_paridade = GTK_WIDGET(gtk_builder_get_object(builder, "text_paridade"));
    text_bits_EDAC = GTK_WIDGET(gtk_builder_get_object(builder, "text_bits_EDAC"));
    text_tempo_bit = GTK_WIDGET(gtk_builder_get_object(builder, "text_tempo_bit"));
    text_bit_simbolo = GTK_WIDGET(gtk_builder_get_object(builder, "text_bit_simbolo"));
    text_mensagem = GTK_WIDGET(gtk_builder_get_object(builder, "text_mensagem"));
    text_bits = GTK_WIDGET(gtk_builder_get_object(builder, "text_bits"));
    scale_tempo = GTK_WIDGET(gtk_builder_get_object(builder, "scale_tempo"));
    botao_enviar = GTK_WIDGET(gtk_builder_get_object(builder, "botao_enviar"));
}