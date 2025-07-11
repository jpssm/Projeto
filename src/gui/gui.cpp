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
GtkWidget *text_bits_frames;

// GtkListStore
//GtkWidget *list_códigos_de_erro;
//GtkWidget *list_enquadramento;
//GtkWidget *list_paridade;
//GtkWidget *list_codificacao;
//GtkWidget *list_modulacao;

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


string get_combo_box_value(GtkWidget *widget) {
    // 2. Faz o cast do GtkWidget* para GtkComboBox*.
    //    Agora podemos usar funções específicas de GtkComboBox.
    GtkComboBox *combo_box = GTK_COMBO_BOX(widget);

    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *text = NULL;

    g_return_val_if_fail(GTK_IS_COMBO_BOX(combo_box), NULL);

    model = gtk_combo_box_get_model(combo_box);

    // Tenta obter a iteração para o item selecionado
    if (gtk_combo_box_get_active_iter(combo_box, &iter)) {
        // Assume que a coluna de texto é a primeira coluna (coluna 0) no modelo
        // Se seu modelo tiver múltiplas colunas e a coluna de texto não for a 0,
        // você precisará ajustar este índice.
        gtk_tree_model_get(model, &iter, 1, &text, -1);
    }

    g_object_unref(model); // Liberar a referência ao modelo

    string s(text);

    return s;

}


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



void initialize_widgets(GtkBuilder *builder) {
    // É uma boa prática adicionar uma verificação inicial para o builder também
    if (builder == NULL) {
        fprintf(stderr, "Erro: GtkBuilder é NULL. Não foi possível carregar a UI.\n");
        return; // Ou g_error("..."); para encerrar o programa
    }

    Janela_Transmissor = GTK_WIDGET(gtk_builder_get_object(builder, "Janela_Transmissor"));
    if (Janela_Transmissor == NULL) {
        fprintf(stderr, "Erro: Widget 'Janela_Transmissor' não encontrado no arquivo UI.\n");
        // Considere g_error() aqui se a janela principal for essencial para o funcionamento do app
    }

    grafico_codificação = GTK_WIDGET(gtk_builder_get_object(builder, "grafico_codificação"));
    if (grafico_codificação == NULL) {
        fprintf(stderr, "Erro: Widget 'grafico_codificação' não encontrado no arquivo UI.\n");
    }

    grafico_modulação = GTK_WIDGET(gtk_builder_get_object(builder, "grafico_modulação"));
    if (grafico_modulação == NULL) {
        fprintf(stderr, "Erro: Widget 'grafico_modulação' não encontrado no arquivo UI.\n");
    }

    cbox_codificacao = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_codificacao"));
    if (cbox_codificacao == NULL) {
        fprintf(stderr, "Erro: Widget 'cbox_codificacao' não encontrado no arquivo UI.\n");
    }

    cbox_modulacao = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_modulacao"));
    if (cbox_modulacao == NULL) {
        fprintf(stderr, "Erro: Widget 'cbox_modulacao' não encontrado no arquivo UI.\n");
    }

    cbox_protocolo = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_protocolo"));
    if (cbox_protocolo == NULL) {
        fprintf(stderr, "Erro: Widget 'cbox_protocolo' não encontrado no arquivo UI.\n");
    }

    cbox_codigo = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_codigo"));
    if (cbox_codigo == NULL) {
        fprintf(stderr, "Erro: Widget 'cbox_codigo' não encontrado no arquivo UI.\n");
    }

    cbox_paridade = GTK_WIDGET(gtk_builder_get_object(builder, "cbox_paridade"));
    if (cbox_paridade == NULL) {
        fprintf(stderr, "Erro: Widget 'cbox_paridade' não encontrado no arquivo UI.\n");
    }

    radio_button_codificacao = GTK_WIDGET(gtk_builder_get_object(builder, "radio_button_codificacao"));
    if (radio_button_codificacao == NULL) {
        fprintf(stderr, "Erro: Widget 'radio_button_codificacao' não encontrado no arquivo UI.\n");
    }

    radio_button_modulacao = GTK_WIDGET(gtk_builder_get_object(builder, "radio_button_modulacao"));
    if (radio_button_modulacao == NULL) {
        fprintf(stderr, "Erro: Widget 'radio_button_modulacao' não encontrado no arquivo UI.\n");
    }

    spin_tamanho_quadro = GTK_WIDGET(gtk_builder_get_object(builder, "spin_tamanho_quadro"));
    if (spin_tamanho_quadro == NULL) {
        fprintf(stderr, "Erro: Widget 'spin_tamanho_quadro' não encontrado no arquivo UI.\n");
    }

    spin_frequencia = GTK_WIDGET(gtk_builder_get_object(builder, "spin_frequencia"));
    if (spin_frequencia == NULL) {
        fprintf(stderr, "Erro: Widget 'spin_frequencia' não encontrado no arquivo UI.\n");
    }

    text_bits_frames = GTK_WIDGET(gtk_builder_get_object(builder, "text_bits_frames"));
    if (text_bits_frames == NULL) {
        fprintf(stderr, "Erro: Widget 'text_bits_frames' não encontrado no arquivo UI.\n");
    }

    entry_polinomio = GTK_WIDGET(gtk_builder_get_object(builder, "entry_polinomio"));
    if (entry_polinomio == NULL) {
        fprintf(stderr, "Erro: Widget 'entry_polinomio' não encontrado no arquivo UI.\n");
    }

    text_paridade = GTK_WIDGET(gtk_builder_get_object(builder, "text_paridade"));
    if (text_paridade == NULL) {
        fprintf(stderr, "Erro: Widget 'text_paridade' não encontrado no arquivo UI.\n");
    }

    text_bits_EDAC = GTK_WIDGET(gtk_builder_get_object(builder, "text_bits_EDAC"));
    if (text_bits_EDAC == NULL) {
        fprintf(stderr, "Erro: Widget 'text_bits_EDAC' não encontrado no arquivo UI.\n");
    }

    text_tempo_bit = GTK_WIDGET(gtk_builder_get_object(builder, "text_tempo_bit"));
    if (text_tempo_bit == NULL) {
        fprintf(stderr, "Erro: Widget 'text_tempo_bit' não encontrado no arquivo UI.\n");
    }

    text_bit_simbolo = GTK_WIDGET(gtk_builder_get_object(builder, "text_bit_simbolo"));
    if (text_bit_simbolo == NULL) {
        fprintf(stderr, "Erro: Widget 'text_bit_simbolo' não encontrado no arquivo UI.\n");
    }

    text_mensagem = GTK_WIDGET(gtk_builder_get_object(builder, "text_mensagem"));
    if (text_mensagem == NULL) {
        fprintf(stderr, "Erro: Widget 'text_mensagem' não encontrado no arquivo UI.\n");
    }

    text_bits = GTK_WIDGET(gtk_builder_get_object(builder, "text_bits"));
    if (text_bits == NULL) {
        fprintf(stderr, "Erro: Widget 'text_bits' não encontrado no arquivo UI.\n");
    }

    scale_tempo = GTK_WIDGET(gtk_builder_get_object(builder, "scale_tempo"));
    if (scale_tempo == NULL) {
        fprintf(stderr, "Erro: Widget 'scale_tempo' não encontrado no arquivo UI.\n");
    }

    botao_enviar = GTK_WIDGET(gtk_builder_get_object(builder, "botao_enviar"));
    if (botao_enviar == NULL) {
        fprintf(stderr, "Erro: Widget 'botao_enviar' não encontrado no arquivo UI.\n");
    }
}
