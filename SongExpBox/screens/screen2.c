#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../peripherals/I2C_Display/ssd1306.h"
#include "../peripherals/ADC_DMA/ADC_DMA_functions.h"

#include <string.h>

#include "screens.h"

#define BASE_TIME_MS 250


extern int screen;
extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

extern cursor_data cursor;



int increment_notes_indice(int notes_index) {
    notes_index = (notes_index + 8) % 56;
    return notes_index;
}

int decrement_notes_indice(int notes_index) {
    notes_index = (notes_index - 8 + 56) % 56;
    return notes_index;
}

int fase1(){

    char notes[] = {    
        /*indice 0  -> */ 0x78, 0x14, 0x12, 0x11, 0x12, 0x14, 0x78, 0x00, // A
        /*indice 8  -> */ 0x7f, 0x49, 0x49, 0x49, 0x49, 0x49, 0x7f, 0x00, // B
        /*indice 16 -> */ 0x7e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x00, // C 
        /*indice 24 -> */ 0x7f, 0x41, 0x41, 0x41, 0x41, 0x41, 0x7e, 0x00, // D
        /*indice 32 -> */ 0x7f, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, // E
        /*indice 40 -> */ 0x7f, 0x09, 0x09, 0x09, 0x09, 0x01, 0x01, 0x00, // F
        /*indice 48 -> */ 0x7f, 0x41, 0x41, 0x41, 0x51, 0x51, 0x73, 0x00, // G
    };
    
    char accidentals[] = {'-','#','b'};
    int octave;
    
    int minimum, maximum, number;
    char note_char, accidental_char;

    // srand(time(NULL)); // Garante números diferentes a cada execução de rand

    // //sorteando a nota
    // minimum = 0; 
    // maximum = 6;
    // number = minimum + rand() % (maximum - minimum + 1);
    // note_char = notes[number]; 

    // //sorteando o acidente
    // minimum = 0, maximum = 1;
    // number = minimum + rand() % (maximum - minimum + 1);
    // accidental_char = accidentals[number];

    // //sorteando a oitava
    // minimum = 0, maximum = 7;
    // number = minimum + rand() % (maximum - minimum + 1);
    // accidental_char = accidentals[number];
    
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

    cursor.position_x = 72; 
    cursor.position_y = 40; 
    int fb_idx; 
    int notes_index = 0;


       
    //Carregando primeira informação na tela:
    char *text[] = {
        " QUAL E A NOTA?",
        "",
        "    CORRETO     ",
        "",
        "         {      ",
        "   ]}]   A#4    ",
        "         [     ",
        "F1/10      N1/16",

    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);


    while (screen == 2){

        joystick_data joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

        if(joystick_data.velocity_y==0){

        }        
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 72 && cursor.position_x <=79 ) )
        {           
            printf("Entrou!\n");

            fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

            notes_index = decrement_notes_indice(notes_index);
            printf("notes_indice: %d", notes_index);

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = notes[notes_index + i];
            }

            render_on_display(ssd, &frame_area);
       
        }
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 72 && cursor.position_x <=79 ) )
        {           
            printf("Entrou!\n");

            fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

            notes_index = increment_notes_indice(notes_index);
            printf("notes_indice: %d", notes_index);

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = notes[notes_index + i];
            }

            render_on_display(ssd, &frame_area);
       
        }
       
        sleep_ms( (joystick_data.velocity_y==0) ? BASE_TIME_MS : (BASE_TIME_MS/abs(joystick_data.velocity_y)) );

    }

    return 2 ;
}



void screen2()
{

    int fase = 1;

    while(screen==2)
    {
             if (fase == 1) fase1();
        // else if (fase == 2) fase2();
        // else if (fase == 3) fase3();
        // else if (fase == 4) fase4();
        // else if (fase == 5) fase5();
        // else if (fase == 6) fase6();
        // else if (fase == 7) fase7();
        // else if (fase == 8) fase8();
        // else if (fase == 9) fase9();
        // else                fase10();
    }

    return;
}
