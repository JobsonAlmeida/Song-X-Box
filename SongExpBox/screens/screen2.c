#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../peripherals/I2C_Display/ssd1306.h"
#include "../peripherals/I2C_Display/ssd1306_font.h"
#include "../peripherals/ADC_DMA/ADC_DMA_functions.h"
#include "screens.h"
#include "pico/rand.h"

#include "../sound/sound.h"

#define BASE_TIME_MS 250.000

extern int screen;
bool check = false;
int maximum_levels = 12 ;
int level = 1 ;

extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

extern cursor_data cursor;

float base_volume_level = 0.3; //4 bem alto 0.3  passa de 75 db 0.2 passa de 75 db
float volume_level = 1;
float time_note_duration_ms = 1500;

bool play_secret_note = false;

typedef struct  {
    char note_name;
    char accident;
    char octave;     
} musical_note;

typedef struct  {

    char initial_note[2];
    char initial_accident[2];
    char initial_octave[2];
    char initial_level[3];
    char maximum_levels[3];
    char initial_correct_note_number[3];
    char maximum_correct_note_number[3];
    char initial_incorrect_note_number[2];
    char maximum_incorrect_note_number[2];

} initial_page_parameters;



char notes[] = {    
    /*indice 0  -> */ 0x78, 0x14, 0x12, 0x11, 0x12, 0x14, 0x78, 0x00, // A
    /*indice 8  -> */ 0x7f, 0x49, 0x49, 0x49, 0x49, 0x49, 0x7f, 0x00, // B
    /*indice 16 -> */ 0x7e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x00, // C 
    /*indice 24 -> */ 0x7f, 0x41, 0x41, 0x41, 0x41, 0x41, 0x7e, 0x00, // D
    /*indice 32 -> */ 0x7f, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, // E
    /*indice 40 -> */ 0x7f, 0x09, 0x09, 0x09, 0x09, 0x01, 0x01, 0x00, // F
    /*indice 48 -> */ 0x7f, 0x41, 0x41, 0x41, 0x51, 0x51, 0x73, 0x00, // G
};

char accidentals[] = {
    /*indice 0  -> */   0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, // -
    /*indice 8  -> */   0x24, 0xe4, 0x3f, 0x24, 0xfc, 0x27, 0x24, 0x00, // #
    /*indice 16  -> */  0x00, 0xff, 0x88, 0x88, 0x88, 0xf8, 0x00, 0x00 // bemol
};

char octaves[] = {    
    /*indice 0  -> */ 0x3e, 0x41, 0x41, 0x49, 0x41, 0x41, 0x3e, 0x00, // 0
    /*indice 8  -> */ 0x00, 0x00, 0x42, 0x7f, 0x40, 0x00, 0x00, 0x00, // 1
    /*indice 16 -> */ 0x30, 0x49, 0x49, 0x49, 0x49, 0x46, 0x00, 0x00, // 2
    /*indice 24 -> */ 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x36, 0x00, // 3
    /*indice 32 -> */ 0x3f, 0x20, 0x20, 0x78, 0x20, 0x20, 0x00, 0x00, // 4
    /*indice 40 -> */ 0x4f, 0x49, 0x49, 0x49, 0x49, 0x30, 0x00, 0x00, // 5
    /*indice 48 -> */ 0x3f, 0x48, 0x48, 0x48, 0x48, 0x48, 0x30, 0x00, // 6
    /*indice 56 -> */ 0x01, 0x01, 0x01, 0x61, 0x31, 0x0d, 0x03, 0x00, // 7
    /*indice 64 -> */ 0x36, 0x49, 0x49, 0x49, 0x49, 0x49, 0x36, 0x00, // 8
    /*indice 72 -> */ 0x06, 0x09, 0x09, 0x09, 0x09, 0x09, 0x7f, 0x00, // 9 
};

// Adquire os pixels para um caractere (de acordo com notes.h)
int ssd1306_get_font_notes(uint8_t character, char notes[], char accidentals[], char octaves[])
{   

    if (character >= 'A' && character <= 'G') {
        return  character - 'A';
    }
    else if (character >= '0' && character <= '9') {
        return character - '0';
    }
    else if (character == '-') {
        return 0; // caractere com tudo branco
    }
    else if (character == '#') {
        return 1;
    }
    else if (character == 'b') {
        return 2;
    }
        

    return 0;
}


int increment_notes_indice(int notes_index) {
    notes_index = (notes_index + 8) % 56;
    return notes_index;
}

int decrement_notes_indice(int notes_index) {
    notes_index = (notes_index - 8 + 56) % 56;
    return notes_index;
}

int increment_accidentals_index(int accidentals_index) {
    accidentals_index = (accidentals_index + 8) % 24;
    return accidentals_index;
}

int decrement_accidentals_index(int accidentals_index) {
    accidentals_index = (accidentals_index - 8 + 24) % 24;
    return accidentals_index;
}

int increment_octaves_index(int octaves_index) {
    octaves_index = (octaves_index + 8) % 80;
    return octaves_index;
}

int decrement_octaves_index(int octaves_index) {
    octaves_index = (octaves_index - 8 + 80) % 80;
    return octaves_index;
}

void wait(joystick_data joystick_data){

    int time_divider = abs(joystick_data.velocity_x) > abs(joystick_data.velocity_y) ? abs(joystick_data.velocity_x) : abs(joystick_data.velocity_y);
    sleep_ms( (time_divider==0) ? BASE_TIME_MS : (BASE_TIME_MS/(float) time_divider) );

    return;
}

musical_note sortear_nota(char note_names[], int note_size, unsigned char accidents[], int acc_size, unsigned char octaves[], int oct_size) {

    musical_note drawn_musical_note;
    int index;
    int minimum = 0;
    int maximum;

    do{
        // Sorteia a nota musical
        maximum = note_size - 1;
        index = minimum +  get_rand_32()% (maximum - minimum + 1);
        drawn_musical_note.note_name = note_names[index];

        // Sorteia o acidente musical
        maximum = acc_size - 1;
        index = minimum + get_rand_32() % (maximum - minimum + 1);
        drawn_musical_note.accident = accidents[index];

        // Sorteia a oitava
        maximum = oct_size - 1;
        index = minimum + get_rand_32() % (maximum - minimum + 1);
        drawn_musical_note.octave = octaves[index];

    }
    while ((drawn_musical_note.note_name == 'B' && drawn_musical_note.accident == '#') || 
           (drawn_musical_note.note_name == 'E' && drawn_musical_note.accident == '#') ||
           (drawn_musical_note.note_name == 'F' && drawn_musical_note.accident == 'b') ||
           (drawn_musical_note.note_name == 'C' && drawn_musical_note.accident == 'b')         
        );

    return drawn_musical_note;

}

initial_page_parameters load_first_page(int first_page, uint8_t* ssd, struct render_area *frame_area){

    initial_page_parameters page;
    char string_aux1[17];
    int line;
    int fb_idx;

    //limpa o frame buffer
    memset(ssd, 0, ssd1306_buffer_length);
     
    if (first_page == 1){

        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "-");
        strcpy(page.initial_octave, "4");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

    }
    else if(first_page == 2){

        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "#");
        strcpy(page.initial_octave, "4");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos
        

    }
    else if(first_page == 3){

        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "b");
        strcpy(page.initial_octave, "4");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos
           
        
    }
    else if(first_page == 4){

        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "-");
        strcpy(page.initial_octave, "5");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

     
        
    }
    else if(first_page == 5){

        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "#");
        strcpy(page.initial_octave, "5");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

   
        
    }
    else if(first_page == 6){

        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "b");
        strcpy(page.initial_octave, "5");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

        
    }
    else if(first_page == 7){
        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "-");
        strcpy(page.initial_octave, "3");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

   
        
    }
    else if(first_page == 8){
        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "#");
        strcpy(page.initial_octave, "3");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

        
    }
    else if(first_page == 9){
        strcpy(page.initial_note, "C");
        strcpy(page.initial_accident, "b");
        strcpy(page.initial_octave, "3");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

     
    }
    else if(first_page == 10){

        strcpy(page.initial_note, "A");
        strcpy(page.initial_accident, "-");
        strcpy(page.initial_octave, "4");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

 
        
    }

    else if(first_page == 11){

        strcpy(page.initial_note, "A");
        strcpy(page.initial_accident, "#");
        strcpy(page.initial_octave, "4");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos

 
        
    }

    else if(first_page == 11){

        strcpy(page.initial_note, "A");
        strcpy(page.initial_accident, "b");
        strcpy(page.initial_octave, "4");

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", level);  // Formato com zero à esquerda        
        strcpy(page.initial_level, string_aux1);

        memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
        sprintf(string_aux1, "%02d", maximum_levels);  // Formato com zero à esquerda        
        strcpy(page.maximum_levels, string_aux1);

        strcpy(page.initial_correct_note_number, "00");
        strcpy(page.maximum_correct_note_number, "03"); // numero máximo de notas a ser acertadas
        strcpy(page.initial_incorrect_note_number, "0");
        strcpy(page.maximum_incorrect_note_number, "5"); //numero máximo de erros permitidos
        
    }
   

    //page 0 
    strcpy(string_aux1,  " QUAL E A NOTA? ");
    ssd1306_draw_string(ssd, 0, 0,string_aux1);

    //page 1
    strcpy(string_aux1,  "                ");
    ssd1306_draw_string(ssd, 0, 8,string_aux1);

    //page 2
    strcpy(string_aux1,  "                ");
    ssd1306_draw_string(ssd, 0, 16,string_aux1);

    //page 3
    strcpy(string_aux1,  "                ");
    ssd1306_draw_string(ssd, 0, 24,string_aux1);

    // //page 4
    strcpy(string_aux1,  "                ");
    ssd1306_draw_string(ssd, 0, 32,string_aux1);

    //page 5
    memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
    strcat(string_aux1,  "   ]}]   ");
    ssd1306_draw_string(ssd, 0, 40, string_aux1);

    line = ssd1306_get_font_notes(page.initial_note[0], notes, accidentals, octaves);
    fb_idx = 5 * 128 + 72;            
    for (int i = 0; i < 8; i++) {
        ssd[fb_idx++] = notes[line * 8 + i];
    }

    line = ssd1306_get_font_notes(page.initial_accident[0], notes, accidentals, octaves);
    fb_idx = 5 * 128 + 80;    
    for (int i = 0; i < 8; i++) {
        ssd[fb_idx++] = accidentals[line * 8 + i];
    }

    line = ssd1306_get_font_notes(page.initial_octave[0], notes, accidentals, octaves);
    fb_idx = 5 * 128 + 88;    
    for (int i = 0; i < 8; i++) {
        ssd[fb_idx++] = octaves[line * 8 + i];
    }

    memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
    strcat(string_aux1,   "    ");
    ssd1306_draw_string(ssd, 96, 40, string_aux1);

    //page 6
    strcpy(string_aux1,"               ");
    ssd1306_draw_string(ssd, 0, 48,string_aux1);

    //page 7
    memset(string_aux1, 0, sizeof(string_aux1));  // Define todos os bytes como 0
    // strcat(string_aux1,  "F");
    strcat(string_aux1, page.initial_level );
    strcat(string_aux1, "/" );
    strcat(string_aux1, page.maximum_levels);
    strcat(string_aux1, " ");
    // strcat(string_aux1, "A");
    strcat(string_aux1, page.initial_correct_note_number);
    strcat(string_aux1, "/" );
    strcat(string_aux1, page.maximum_correct_note_number);
    strcat(string_aux1, " ");
    strcat(string_aux1, " ");
    // strcat(string_aux1, "E");
    strcat(string_aux1, page.initial_incorrect_note_number);
    strcat(string_aux1, "/" );
    strcat(string_aux1, page.maximum_incorrect_note_number);
    ssd1306_draw_string(ssd, 0, 56,string_aux1);

    ssd1306_draw_string(ssd, cursor.position_x, cursor.position_y-8, "{");
    ssd1306_draw_string(ssd, cursor.position_x, cursor.position_y+8, "[");
        
    //mostrando do display
    render_on_display(ssd, frame_area);

    return page;

}

int play_levels(){

    cursor.position_x = 72; 
    cursor.position_y = 40; 
    int fb_idx; 
    int notes_index;
    int accidentals_index;
    int octaves_index;
    int initial_page = 1;
    bool sortear = true;
    int draw_counter = 0;
    int error_counter = 0;
    int hit_counter = 0;
    int maximum_correct_note_number;
    int maximum_error_counter;
    musical_note drawn_note;
    joystick_data joystick_data;

    char secret_note[3];


    // zera o display inteiro
     uint8_t ssd[ssd1306_buffer_length];
     
    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    printf("level: %d\n", level);
    while (screen == 2){

        if(level == 1 && sortear ) {

            if(initial_page == 1){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 1     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-'};
            unsigned char  octaves[] = {'4'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;

        }
        else if (level == 2 && sortear){
            
            if(initial_page == 2){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 2     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#'};
            unsigned char  octaves[] = {'4'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );
            
            draw_counter++;
            sortear = false;
        
        }
        else if (level == 3 && sortear){
            
            if(initial_page == 3){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 3     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#','b'};
            unsigned char  octaves[] = {'4'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 4 && sortear){
            
            if(initial_page == 4){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 4     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-'};
            unsigned char  octaves[] = {'5'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 5 && sortear){
            

            if(initial_page == 5){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 5     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#'};
            unsigned char  octaves[] = {'5'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );
            draw_counter++;
            sortear = false;
        
        }
        else if (level == 6 && sortear){
            
            if(initial_page == 6){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 6     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#', 'b'};
            unsigned char  octaves[] = {'5'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 7 && sortear){
            

            if(initial_page == 7){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 7     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-'};
            unsigned char  octaves[] = {'3'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 8 && sortear){
            
            if(initial_page == 8){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 8     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#'};
            unsigned char  octaves[] = {'3'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 9 && sortear){
            
            if(initial_page == 9){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 9     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#', 'b'};
            unsigned char  octaves[] = {'3'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 10 && sortear){
            

            if(initial_page == 10){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 10     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#', 'b'};
            unsigned char  octaves[] = {'4', '5'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 11 && sortear){
            

            if(initial_page == 11){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 11     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#', 'b'};
            unsigned char  octaves[] = {'3', '4'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
        else if (level == 12 && sortear){
            
            if(initial_page == 12){

                // zera o display inteiro e mostra mensagem de termino                   
                memset(ssd, 0, ssd1306_buffer_length);                                   
                ssd1306_draw_string(ssd, 0, 24, "     FASE 12     ");                        
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                initial_page_parameters first_page_parameters;                
                first_page_parameters = load_first_page(initial_page, ssd, &frame_area);

                int line = ssd1306_get_font_notes(first_page_parameters.initial_note[0], notes, accidentals, octaves );
                notes_index = line*8;

                line = ssd1306_get_font_notes(first_page_parameters.initial_accident[0], notes, accidentals, octaves );
                accidentals_index = line*8; 

                line = ssd1306_get_font_notes(first_page_parameters.initial_octave[0], notes, accidentals, octaves );
                octaves_index = line*8; 

                maximum_correct_note_number = atoi(first_page_parameters.maximum_correct_note_number);
                maximum_error_counter = atoi(first_page_parameters.maximum_incorrect_note_number);

                initial_page++;            
            }

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#', 'b'};
            unsigned char  octaves[] = {'3','4', '5'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            draw_counter++;
            sortear = false;
        
        }
       
        joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

        if(joystick_data.velocity_x==0){

        } 
        else if(joystick_data.velocity_x>=0 && ( (cursor.position_x + 8)<=95) ){


            //Apagando as setas para cima e para baixo na localização atual
            fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[i];
            }

            fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[i];
            }


            //Mostrando na tela as setas para cima e para baixo na próxima localização à direita
            cursor.position_x = (cursor.position_x >=32 && cursor.position_x <=39) ? 72 : cursor.position_x + 8;

            fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[560 + i];
            }

            fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[568 + i];
            }

            render_on_display(ssd, &frame_area);
            wait(joystick_data);



        } 
        else if(joystick_data.velocity_x<=0 && ( (cursor.position_x - 8)>=32) ){


            //Apagando as setas para cima e para baixo na localização atual
            fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[i];
            }

            fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[i];
            }


            //Mostrando na tela as setas para cima e para baixo na próxima localização à direita
            cursor.position_x = (cursor.position_x >=72 && cursor.position_x <=79) ? 32 : cursor.position_x - 8;

            if(cursor.position_x == 32){

                fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = font[576 + i];
                }
    
                fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 
    
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = font[584 + i];
                }
    
            }
            else {

                fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = font[560 + i];
                }
    
                fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 
    
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = font[568 + i];
                }
    
            }

            render_on_display(ssd, &frame_area);
            wait(joystick_data);

        } 

         if(joystick_data.velocity_y==0){

        } 
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 32 && cursor.position_x <=39 ) ) {

            while (joystick_data.velocity_y<0){

           
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);
            }

        }     
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 32 && cursor.position_x <=39 ) ) {

            while (joystick_data.velocity_y>0){

           
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);
            }

        }       
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 72 && cursor.position_x <=79 ) )
        {           

            while (joystick_data.velocity_y<0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                notes_index = decrement_notes_indice(notes_index);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = notes[notes_index + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);
            }
        

        }
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 72 && cursor.position_x <=79 ) )
        {      
            
            while (joystick_data.velocity_y>0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                notes_index = increment_notes_indice(notes_index);
            
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = notes[notes_index + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }
       
        }
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 80 && cursor.position_x <=87 ) )
        {           


            while (joystick_data.velocity_y<0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                accidentals_index = decrement_accidentals_index(accidentals_index);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = accidentals[accidentals_index + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }

        }
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 80 && cursor.position_x <=87 ) )
        {          

            while (joystick_data.velocity_y>0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                accidentals_index = increment_accidentals_index(accidentals_index);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = accidentals[accidentals_index + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }

        }
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 88 && cursor.position_x <=95 ) )
        {           

            while (joystick_data.velocity_y<0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                octaves_index = decrement_octaves_index(octaves_index);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = octaves[octaves_index + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }

        }
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 88 && cursor.position_x <=95 ) )
        {          

            while (joystick_data.velocity_y>0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                octaves_index = increment_octaves_index(octaves_index);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = octaves[octaves_index + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }
        }
            
        if(check){
            
            check = false;

            bool note_check = true;
            bool accidental_check = true;
            bool octave_check = true;

            int line = ssd1306_get_font_notes(drawn_note.note_name, notes, accidentals, octaves );
            int fb_idx = 5* 128 + 72;
            for (int i = 0; i < 8; i++) {
                if (ssd[fb_idx++] != notes[line * 8 + i]) {
                    note_check = false;
                    break;
                }
                 
            }

            line = ssd1306_get_font_notes(drawn_note.accident, notes, accidentals, octaves );
            fb_idx = 5* 128 + 80;
            for (int i = 0; i < 8; i++) {
                if (ssd[fb_idx++] != accidentals[line * 8 + i]) {
                    accidental_check = false;
                    break;
                }
                 
            }

            line = ssd1306_get_font_notes(drawn_note.octave, notes, accidentals, octaves );
            fb_idx = 5* 128 + 88;
            for (int i = 0; i < 8; i++) {
                if (ssd[fb_idx++] != octaves[line * 8 + i]) {
                    octave_check = false;
                    break;
                }       
            }

            
            if(note_check && accidental_check && octave_check ) {

                hit_counter += 1;


                char string_hit_counter[3];
                char string_message[17];

                sprintf(string_hit_counter, "%02d", hit_counter);

                strcpy(string_message, "    CORRETO     ");
                ssd1306_draw_string(ssd, 0, 16, string_message);
                ssd1306_draw_string(ssd, 48, 56, string_hit_counter);

                memset(string_message, 0, sizeof(string_message));  // Define todos os bytes como 0
                snprintf(string_message, sizeof(string_message), "%s%c", string_message, drawn_note.note_name);
                snprintf(string_message, sizeof(string_message), "%s%c", string_message, drawn_note.accident);
                snprintf(string_message, sizeof(string_message), "%s%c", string_message, drawn_note.octave);
                ssd1306_draw_string(ssd, 24, 40, string_message);

                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                strcpy(string_message, "                " );
                ssd1306_draw_string(ssd, 0, 16,string_message);

                memset(string_message, 0, sizeof(string_message));  // Define todos os bytes como 0
                strcat(string_message, "]}]");
                ssd1306_draw_string(ssd, 24, 40, string_message);

                render_on_display(ssd, &frame_area);  

                if (hit_counter < maximum_correct_note_number) {

                    sortear = true;;

                }
                else{ //hit_counter > maximum_correct_note_number

                    level++;
                    printf("level: %d\n", level);

                    if(level <= maximum_levels){
                        error_counter = 0;
                        hit_counter = 0;
                        sortear = true;
                    }
                    else{
                        
                        // zera o display inteiro e mostra mensagem de termino                   
                        memset(ssd, 0, ssd1306_buffer_length);                                   
                        ssd1306_draw_string(ssd, 0, 8, "   PARABENS!    ");                        
                        ssd1306_draw_string(ssd, 0, 24, "VOCE DESENVOLVEU");                        
                        ssd1306_draw_string(ssd, 0, 40, "OUVIDO ABSOLUTO");                        
                        render_on_display(ssd, &frame_area);

                        sleep_ms(5000);

                        level = 1;
                        error_counter = 0;
                        hit_counter = 0;
                        sortear = true;

                        return true;

                    }
                    
                }

            }
            else{   

                if(error_counter+1 > maximum_error_counter) {

                    // zera o display inteiro e mostra mensagem de termino                   
                    memset(ssd, 0, ssd1306_buffer_length);                                   
                    ssd1306_draw_string(ssd, 0, 24, "  VOCE PERDEU!  ");                        
                    render_on_display(ssd, &frame_area);

                    sleep_ms(1500);

                    level = 1;
                    error_counter = 0;
                    hit_counter = 0;
                    sortear = true;

                    return false;
                }
                
                error_counter++;

                char string_error =  '0' + error_counter;

                char string_message[17];

                char string_error_number[2] = {string_error,'\0'};

                strcpy(string_message, "     ERRADO     ");
                ssd1306_draw_string(ssd, 0, 16,string_message);
                ssd1306_draw_string(ssd, 104, 56, string_error_number);
                render_on_display(ssd, &frame_area);

                sleep_ms(1500);

                strcpy(string_message, "                " );
                ssd1306_draw_string(ssd, 0, 16,string_message);
                render_on_display(ssd, &frame_area);

            }

        }
    
        if(play_secret_note){

            printf("drawn_note.note_name: %c drawn_note.accident: %c drawn_note.octave: %c\n",drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            char note[] = { drawn_note.note_name, drawn_note.accident, drawn_note.octave};
            strcpy(secret_note, note );
            play_note(BUZZER_RIGHT_1, secret_note, base_volume_level*volume_level, time_note_duration_ms );

            play_secret_note = false;

        }
    
    }

    return 2 ;
}

void  screen2()
{

    bool final_result = play_levels();
    
    if(final_result){
        screen = 1;
    }
    else{     
        screen = 1;
    }

    return;
}
