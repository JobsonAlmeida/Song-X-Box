#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../peripherals/I2C_Display/ssd1306.h"
#include "../peripherals/I2C_Display/ssd1306_font.h"
#include "../peripherals/ADC_DMA/ADC_DMA_functions.h"
#include "screens.h"
#include "pico/rand.h"


#define BASE_TIME_MS 250.000

extern int screen;
bool check = false;
bool allow_get_state_button_B = true;
int max_error_counter = 3;

extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

extern cursor_data cursor;

volatile absolute_time_t now;
volatile absolute_time_t last_press_time_button_B;
volatile bool button_B_pressed;

typedef struct  {

    unsigned char note_name;
    unsigned char accident;
    unsigned char octave;     

} musical_note;

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

musical_note sortear_nota(char note_names[], int note_size, unsigned char accidents[], int acc_size, unsigned char octaves[], int oct_size) {

    musical_note drawn_musical_note;
    int index;
    int minimum = 0;
    int maximum;

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

    return drawn_musical_note;

}

int play_levels(){

    cursor.position_x = 72; 
    cursor.position_y = 40; 
    int fb_idx; 
    int notes_index = 16;
    int accidentals_index = 0;
    int octaves_index = 32;
    
    joystick_data joystick_data;

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
     
    
    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);


    //Carregando primeira informação na tela:
    char *text[] = {
        " QUAL E A NOTA? ",
        "                ",
        "                ",
        "                ",
        "         {      ",
        "   ]}]   C-4    ",
        "         [      ",
        "F1/10 N1/16 E0/3",

    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    int level = 1 ;
    bool sortear = true;
    int draw_counter = 0;
    musical_note drawn_note;
    int error_counter = 0;

    last_press_time_button_B = get_absolute_time();

    while (screen == 2){

        if (level == 1 && sortear ) {

            unsigned char note_names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            unsigned char accidents[] = {'-', '#', 'b'};
            unsigned char  octaves[] = {'4','5'};

            int note_names_size = sizeof(note_names) / sizeof(note_names[0]);
            int accidents_size = sizeof(accidents) / sizeof(accidents[0]);
            int octaves_size = sizeof(octaves) / sizeof(octaves[0]);

            drawn_note = sortear_nota(note_names, note_names_size, accidents, accidents_size, octaves, octaves_size);
            printf("drawn_note.note = %c - drawn_note.accident = %c - drawn_note.octave = %c\n", drawn_note.note_name, drawn_note.accident, drawn_note.octave);
            printf("allow_get_state_button_B %d\n", allow_get_state_button_B);
            draw_counter++;
            sortear = false;

        }
        else if (level == 2 && sortear){
            printf("Entrou level 2!\n");


        }
        // else if (fase == 3) fase3();
        // else if (fase == 4) fase4();
        // else if (fase == 5) fase5();
        // else if (fase == 6) fase6();
        // else if (fase == 7) fase7();
        // else if (fase == 8) fase8();
        // else if (fase == 9) fase9();
        // else                fase10();

        joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

        // printf("joystick_data.velocity_x = %d - joystick_data.velocity_y = %d  \n", joystick_data.velocity_x, joystick_data.velocity_y);


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

                printf("cursor.position_x = %d - cursor.position_y = %d \n", cursor.position_x, cursor.position_y);
           
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);
            }

        }     
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 32 && cursor.position_x <=39 ) ) {

            while (joystick_data.velocity_y>0){

                printf("cursor.position_x = %d - cursor.position_y = %d \n", cursor.position_x, cursor.position_y);
           
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);
            }

        }       
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 72 && cursor.position_x <=79 ) )
        {           

            while (joystick_data.velocity_y<0){

                printf("cursor.position_x = %d - cursor.position_y = %d \n", cursor.position_x, cursor.position_y);

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

                printf("Entrou!\n");

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

                printf("cursor.position_x = %d - cursor.position_y = %d \n", cursor.position_x, cursor.position_y);

                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                accidentals_index = decrement_accidentals_index(accidentals_index);
                printf("accidentals_index: %d\n", accidentals_index);
                
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

                printf("cursor.position_x = %d - cursor.position_y = %d \n", cursor.position_x, cursor.position_y);

                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                accidentals_index = increment_accidentals_index(accidentals_index);
                printf("accidentals_index: %d\n", accidentals_index);
                
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

                printf("cursor.position_x = %d - cursor.position_y = %d \n", cursor.position_x, cursor.position_y);

                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                octaves_index = decrement_octaves_index(octaves_index);
                printf("octaves_index: %d\n", octaves_index);
                
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

                printf("cursor.position_x = %d - cursor.position_y = %d \n", cursor.position_x, cursor.position_y);

                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                octaves_index = increment_octaves_index(octaves_index);
                printf("octaves_index: %d\n", octaves_index);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = octaves[octaves_index + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }
        }
    
        
        absolute_time_t now = get_absolute_time();
        if(check && absolute_time_diff_us(last_press_time_button_B, now) > 1500000){
            last_press_time_button_B = now;

            // allow_get_state_button_B = false;

            check = false;

            bool note_check = true;
            bool accidental_check = true;
            bool octave_check = true;

            int line = ssd1306_get_font_notes(drawn_note.note_name, notes, accidentals, octaves );
            printf("line drawn_note.note_name %d\n", line);
            int fb_idx = 5* 128 + 72;
            printf("fb_ind %d\n", fb_idx);
            for (int i = 0; i < 8; i++) {
                if (ssd[fb_idx++] != notes[line * 8 + i]) {
                    note_check = false;
                    break;
                }
                 
            }

            line = ssd1306_get_font_notes(drawn_note.accident, notes, accidentals, octaves );
            printf("line drawn_note.accident %d\n", line);
            fb_idx = 5* 128 + 80;
            printf("fb_ind %d\n", fb_idx);
            for (int i = 0; i < 8; i++) {
                if (ssd[fb_idx++] != accidentals[line * 8 + i]) {
                    accidental_check = false;
                    break;
                }
                 
            }

            line = ssd1306_get_font_notes(drawn_note.octave, notes, accidentals, octaves );
            printf("line drawn_note.octave: %d\n", line);
            fb_idx = 5* 128 + 88;
            printf("fb_ind %d\n", fb_idx);
            for (int i = 0; i < 8; i++) {
                if (ssd[fb_idx++] != octaves[line * 8 + i]) {
                    octave_check = false;
                    break;
                }       
            }

            printf("note_check = %d  - accidental_check = %d - octave_check = %d\n",note_check,  accidental_check, octave_check );
            
            if(note_check && accidental_check && octave_check ) {

                printf("Você acertou !\n");

                if (draw_counter<16) {

                    draw_counter += 1;
                    sortear = true;;
                    allow_get_state_button_B = true;
                }
                else{

                    level = 2;
                    draw_counter = 0;
                    sortear = true;
                }

            }
            else{             

                if(error_counter+1 > max_error_counter) {
                    // allow_get_state_button_B = true;                    
                    return false;
                }
                
                error_counter++;

                printf("error counter %d\n", error_counter);

                
                // button_B_pressed = false;

                printf("Você errou! - error_counter = %d!\n", error_counter);

                char string_error =  '0' + error_counter;
                printf("string_error =  %c\n", string_error);

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

                // line = ssd1306_get_font_(error_to_screen);
                // printf("line: %d\n", line);
                // fb_idx = 7* 128 + 104;
                // printf("fb_ind %d\n", fb_idx);
                // for (int i = 0; i < 8; i++) {
                //     ssd[fb_idx++] = octaves[line * 8 + i];                      
                // }

                // allow_get_state_button_B = true;

                
            }

        }
    }

    return 2 ;
}

void  screen2()
{

    bool final_result = play_levels();
    

    if(final_result){

    
    }
    else{

        printf("Você perdeu o jogo!\n");
        screen = 1;
    }

    return;
}
