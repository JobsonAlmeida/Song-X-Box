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
bool play_left_note;
bool play_right_note;

extern float base_volume_level; 
extern float volume_level;
extern float time_note_duration_ms;

extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

extern cursor_data cursor;

typedef struct  {

    char note_name;
    unsigned char accident;
    int octave;     

} musical_note;


extern void wait(joystick_data joystick_data);

int increment_notes_indice_right(int notes_index) {
    notes_index = (notes_index + 8) % 56;
    return notes_index;
}

int decrement_notes_indice_right(int notes_index) {
    notes_index = (notes_index - 8 + 56) % 56;
    return notes_index;
}

int increment_accidentals_index_right(int accidentals_index) {
    accidentals_index = (accidentals_index + 8) % 24;
    return accidentals_index;
}

int decrement_accidentals_index_right(int accidentals_index) {
    accidentals_index = (accidentals_index - 8 + 24) % 24;
    return accidentals_index;
}

int increment_octaves_index_right(int octaves_index) {
    octaves_index = (octaves_index + 8) % 80;
    return octaves_index;
}

int decrement_octaves_index_right(int octaves_index) {
    octaves_index = (octaves_index - 8 + 80) % 80;
    return octaves_index;
}



int increment_notes_indice_left(int notes_index) {
    notes_index = (notes_index + 8) % 56;
    return notes_index;
}

int decrement_notes_indice_left(int notes_index) {
    notes_index = (notes_index - 8 + 56) % 56;
    return notes_index;
}

int increment_accidentals_index_left(int accidentals_index) {
    accidentals_index = (accidentals_index + 8) % 24;
    return accidentals_index;
}

int decrement_accidentals_index_left(int accidentals_index) {
    accidentals_index = (accidentals_index - 8 + 24) % 24;
    return accidentals_index;
}

int increment_octaves_index_left(int octaves_index) {
    octaves_index = (octaves_index + 8) % 80;
    return octaves_index;
}

int decrement_octaves_index_left(int octaves_index) {
    octaves_index = (octaves_index - 8 + 80) % 80;
    return octaves_index;
}


// Adquire os pixels para um caractere (de acordo com ssd1306_font.h)
inline int get_note_character(int line)
{   

    char character;

    switch (line)
    {
    case 0:
        character = 'A';
        break;
    case 1:
        character = 'B';
        break;
    case 2:
        character = 'C';
        break;
    case 3:
        character = 'D';
        break;
    case 4:
        character = 'E';
        break;
    case 5:
        character = 'F';
        break;
    case 6:
        character = 'G';
        break;

    default:
        break;
    }
   
    return character;
}


inline int get_accident_character(int line)
{   

    char character;

    switch (line)
    {
    case 0:
        character = '-';
        break;
    case 1:
        character = '#';
        break;
    case 2:
        character = 'b';
        break;
    default:
        break;
    }
   
    return character;
}


inline int get_octave_character(int line)
{   

    char character;

    switch (line)
    {
    case 0:
        character = '0';
        break;
    case 1:
        character = '1';
        break;
    case 2:
        character = '2';
        break;
    case 3:
        character = '3';
        break;
    case 4:
        character = '4';
        break;
    case 5:
        character = '5';
        break;
    case 6:
        character = '6';
        break;
    case 7:
        character = '7';
        break;
    case 8:
        character = '8';
        break;
    case 9:
        character = '9';
        break;
    default:
        break;
    }
   
    return character;
}



int compare_notes(){

    cursor.position_x = 72; 
    cursor.position_y = 40; 
    int fb_idx; 
    int notes_index_right = 16;
    int notes_index_left= 16;

    int accidentals_index_right = 0;
    int accidentals_index_left = 0;

    int octaves_index_right = 32;
    int octaves_index_left = 32;
    
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
        "  ESCOLHA PARA  ",
        "   COMPARAR:    ",
        "                ",
        "                ",
        "         {      ",
        "   C-4   C-4    ",
        "         [      ",
        "                ",

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

    char note_character;
    char accident_character;
    char octave_character;
    int count;
    char right_note[4];
    char left_note[4];


    while (screen == 3){
    
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
            cursor.position_x = (cursor.position_x >=40 && cursor.position_x <=47) ? 72 : cursor.position_x + 8;

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
        else if(joystick_data.velocity_x<=0 && ( (cursor.position_x - 8)>=24) ){


            //Apagando as setas para cima e para baixo na localização atual
            fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[i];
            }

            fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[i];
            }


            //Mostrando na tela as setas para cima e para baixo na próxima localização à esquerda
            cursor.position_x = (cursor.position_x >=72 && cursor.position_x <=79) ? 40 : cursor.position_x - 8;

            fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[560 + i];
            }

            fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = font[568 + i];
            }

            // if(cursor.position_x == 40){

            //     fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

            //     for (int i = 0; i < 8; i++) {
            //         ssd[fb_idx++] = font[576 + i];
            //     }
    
            //     fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 
    
            //     for (int i = 0; i < 8; i++) {
            //         ssd[fb_idx++] = font[584 + i];
            //     }
    
            // }
            // else {

            //     fb_idx =  ((cursor.position_y-8)/8) * 128  + cursor.position_x; 

            //     for (int i = 0; i < 8; i++) {
            //         ssd[fb_idx++] = font[560 + i];
            //     }
    
            //     fb_idx =  ((cursor.position_y+8)/8) * 128  + cursor.position_x; 
    
            //     for (int i = 0; i < 8; i++) {
            //         ssd[fb_idx++] = font[568 + i];
            //     }
    
            // }

            render_on_display(ssd, &frame_area);
            wait(joystick_data);

        } 

         if(joystick_data.velocity_y==0){

        }       
        //right
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 72 && cursor.position_x <=79 ) )
        {           

            while (joystick_data.velocity_y<0){

                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                notes_index_right = decrement_notes_indice_right(notes_index_right);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = notes[notes_index_right + i];
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

                notes_index_right = increment_notes_indice_right(notes_index_right);
            
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = notes[notes_index_right + i];
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

                accidentals_index_right = decrement_accidentals_index_right(accidentals_index_right);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = accidentals[accidentals_index_right + i];
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

                accidentals_index_right = increment_accidentals_index_right(accidentals_index_right);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = accidentals[accidentals_index_right + i];
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

                octaves_index_right = decrement_octaves_index_right(octaves_index_right);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = octaves[octaves_index_right + i];
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

                octaves_index_right = increment_octaves_index_right(octaves_index_right);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = octaves[octaves_index_right + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }
        }
    
        //left 
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 24 && cursor.position_x <=31 ) )
        {           

            while (joystick_data.velocity_y<0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                notes_index_left = decrement_notes_indice_left(notes_index_left);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = notes[notes_index_left + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);
            }
        

        }
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 24 && cursor.position_x <=31 ) )
        {      
            
            while (joystick_data.velocity_y>0){

                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                notes_index_left = increment_notes_indice_left(notes_index_left);
            
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = notes[notes_index_left + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }
       
        }
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 32 && cursor.position_x <=39 ) )
        {           


            while (joystick_data.velocity_y<0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                accidentals_index_left = decrement_accidentals_index_left(accidentals_index_left);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = accidentals[accidentals_index_left + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }

        }
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 32 && cursor.position_x <=39 ) )
        {          

            while (joystick_data.velocity_y>0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                accidentals_index_left = increment_accidentals_index_left(accidentals_index_left);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = accidentals[accidentals_index_left + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }

        }
        else if( joystick_data.velocity_y<0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 40 && cursor.position_x <=47 ) )
        {           

            while (joystick_data.velocity_y<0){

                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                octaves_index_left = decrement_octaves_index_left(octaves_index_left);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = octaves[octaves_index_left + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }

        }
        else if( joystick_data.velocity_y>0 && (cursor.position_y>=40 && cursor.position_y <=47) && (cursor.position_x >= 40 && cursor.position_x <=47 ) )
        {          

            while (joystick_data.velocity_y>0){


                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x; 

                octaves_index_left = increment_octaves_index_left(octaves_index_left);
                
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = octaves[octaves_index_left + i];
                }

                render_on_display(ssd, &frame_area);                
                wait(joystick_data);

                joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

            }
        }


        if(play_right_note){

            //pegando a letra da nota
            for(int line=0; line<7; line++){

                int fb_idx = 5* 128 + 72;
                int count = 0;
                for (int i = 0; i < 8; i++) {
                    if (ssd[fb_idx++] == notes[line * 8 + i]) {
                        count++;
                    }    
                }

                if(count==8){
                    note_character = get_note_character(line);
                    break;
                }   

            }

            //pegando o acidente da nota
            for(int line=0; line<3; line++){

                int fb_idx = 5* 128 + 80;
                int count = 0;
                for (int i = 0; i < 8; i++) {
                    if (ssd[fb_idx++] == accidentals[line * 8 + i]) {
                        count++;
                    }    
                }

                if(count==8){
                    accident_character = get_accident_character(line);
                    break;
                }   

            }


            //pegando o a oitava da nota
            for(int line=0; line<10; line++){

                int fb_idx = 5* 128 + 88;
                int count = 0;
                for (int i = 0; i < 8; i++) {
                    if (ssd[fb_idx++] == octaves[line * 8 + i]) {
                        count++;
                    }    
                }

                if(count==8){
                    octave_character = get_octave_character(line);
                    break;
                }   

            }
        
            sprintf(right_note, "%c%c%c", note_character, accident_character, octave_character);
            printf("right note - note_character: %c accident_character: %c octave_character: %c\n", note_character , accident_character, octave_character);
            play_note(BUZZER_RIGHT_1, right_note, base_volume_level*volume_level, time_note_duration_ms );

            play_right_note = false;

        }


        
        if(play_left_note){

            //pegando a letra da nota
            for(int line=0; line<7; line++){

                int fb_idx = 5* 128 + 24;
                int count = 0;
                for (int i = 0; i < 8; i++) {
                    if (ssd[fb_idx++] == notes[line * 8 + i]) {
                        count++;
                    }    
                }

                if(count==8){
                    note_character = get_note_character(line);
                    break;
                }   

            }

            //pegando o acidente da nota
            for(int line=0; line<3; line++){

                int fb_idx = 5* 128 + 32;
                int count = 0;
                for (int i = 0; i < 8; i++) {
                    if (ssd[fb_idx++] == accidentals[line * 8 + i]) {
                        count++;
                    }    
                }

                if(count==8){
                    accident_character = get_accident_character(line);
                    break;
                }   

            }

            //pegando o a oitava da nota
            for(int line=0; line<10; line++){

                int fb_idx = 5* 128 + 40;
                int count = 0;
                for (int i = 0; i < 8; i++) {
                    if (ssd[fb_idx++] == octaves[line * 8 + i]) {
                        count++;
                    }    
                }

                if(count==8){
                    octave_character = get_octave_character(line);
                    break;
                }   

            }
        
            sprintf(left_note, "%c%c%c", note_character, accident_character, octave_character);
            printf(" left note - note_character: %c accident_character: %c octave_character: %c\n", note_character , accident_character, octave_character);
            play_note(BUZZER_RIGHT_1, left_note, base_volume_level*volume_level, time_note_duration_ms );

            play_left_note = false;

        }

    }

    return 2 ;
}

void screen3()
{

    bool final_result = compare_notes();

    return;
}
