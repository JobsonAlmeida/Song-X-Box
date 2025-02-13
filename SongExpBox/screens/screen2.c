#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../peripherals/I2C_Display/ssd1306.h"
#include <string.h>



extern int screen;

void screen2(){

    printf("Entrou na tela 2\n");


    
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
        " QUAL E A NOTA?",
        "",
        "    CORRETO     ",
        "",
        "",
        "   ]}]   A#4    ",
        "",
        "1/10",

    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    char notes[] = {"A", "B", "C", "D", "E", "F", "G"};
    char accidentals[] = {"#", "b"};
    int octave;

    int minimum, maximum, number;
    char note_char, accidental_char;

    while(screen==2){

        srand(time(NULL)); // Garante números diferentes a cada execução de rand

        //sorteando a nota
        minimum = 0; 
        maximum = 6;
        number = minimum + rand() % (maximum - minimum + 1);
        note_char = notes[number]; 

        //sorteando o acidente
        minimum = 0, maximum = 1;
        number = minimum + rand() % (maximum - minimum + 1);
        accidental_char = accidentals[number];

        //sorteando a oitava
        minimum = 0, maximum = 7;
        number = minimum + rand() % (maximum - minimum + 1);
        accidental_char = accidentals[number];










        printf("note number %d\n", note_number);











        printf("screen na tela 2 %d\n", screen);
        sleep_ms(50);
    }

    return;
}