#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../peripherals/I2C_Display/ssd1306.h"
#include "../peripherals/I2C_Display/ssd1306_font.h"
#include "../peripherals/ADC_DMA/ADC_DMA_functions.h"
#include "screens.h"

#define BASE_TIME_MS 250.000

extern int screen;
extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

extern cursor_data cursor;

typedef struct  {

    note;
    accident;
    octave;     

} note;

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

void sortear_nota(char note_names[], char accidents[], int octaves[]){

    note drawn_musical_note;
    int minimum;
    int maximum;
    int tamanho;

    srand(time(NULL)); // Garante números diferentes a cada execução de rand

    //sorteando a nota musical
    int minimum = 0; 
    int tamanho = sizeof(note_names) / sizeof(note_names[0]);
    int maximum = tamanho - 1;
    int index = minimum + rand() % (maximum - minimum + 1);
    drawn_musical_note.note = note_names[index]; 

    //sorteando o accidente musical
    int minimum = 0; 
    int tamanho = sizeof(accidents) / sizeof(accidents[0]);
    int maximum = tamanho - 1;
    int index = minimum + rand() % (maximum - minimum + 1);
    drawn_musical_note.accident = accidents[index]; 




}

int play_fases(){

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
    
    int minimum, maximum, number;

 
    
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
        "F1/10      N1/16",

    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);





    int fase = 1 ;
    bool sortear = true;

    while (screen == 2){

        if (fase == 1 && sortear ) {



        };
        // else if (fase == 2) fase2();
        // else if (fase == 3) fase3();
        // else if (fase == 4) fase4();
        // else if (fase == 5) fase5();
        // else if (fase == 6) fase6();
        // else if (fase == 7) fase7();
        // else if (fase == 8) fase8();
        // else if (fase == 9) fase9();
        // else                fase10();

        joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

        printf("joystick_data.velocity_x = %d - joystick_data.velocity_y = %d  \n", joystick_data.velocity_x, joystick_data.velocity_y);


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
    
    }

    return 2 ;
}

void screen2()
{

    bool final_result = play_fases();

    if(final_result){

    }
    else{

    }

    return;
}
