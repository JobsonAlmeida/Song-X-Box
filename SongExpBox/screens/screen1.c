#include <stdio.h>
#include <math.h>
#include "screens.h"
#include "../peripherals/I2C_Display/ssd1306.h"
#include "../peripherals/ADC_DMA/ADC_DMA_functions.h"

#include <string.h>

#include "../peripherals/MATRIZ_RGB/matriz_rgb.h"

#define LIMITE_INFERIOR_Y 23
#define LIMITE_SUPERIOR_Y 39
#define BASE_TIME_MS 200

extern int screen;
extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

extern cursor_data cursor;


void screen1(){

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
        " SELECIONE:",
        "",
        " TREINAR OUVIDO",
        " COMPARAR NOTAS",
        " TOCAR MUSICA",
    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    cursor.position_x = 0; 
    cursor.position_y = 23;  

    int fb_idx;
    uint8_t stored_character[8];

    int initial_position = 23;

     //framebuffer ssd --> stored_character
    fb_idx = (initial_position/8) * 128 + cursor.position_x;

    for (int i = 0; i < 8; i++) {
        stored_character[i] = ssd[fb_idx++] ;
    }


    //setando o cursor no framebuffer ssd
    ssd1306_draw_char(ssd, cursor.position_x , cursor.position_y, '>');

    //mostrando o framebuffer ssd no display
    render_on_display(ssd, &frame_area);

    //limpa matriz de led
    npClear();
    npWrite();

    while (screen == 1){

        joystick_data joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

        // printf("joystick_data.velocity_x %d - joystick_data.velocit_y: %d\n", joystick_data.velocity_x, joystick_data.velocity_y);
        
        if(joystick_data.velocity_y==0){

          
        }        
        else if(joystick_data.velocity_y<0 && (cursor.position_y >= 0 && cursor.position_y <=(ssd1306_height-1) ))
        {
            if(cursor.position_y < LIMITE_SUPERIOR_Y-7)
            {

                //transferindo os bytes referentes ao caracter armazenados em stored_character para o framebuffer ssd 
                // stored_character --> framebuffer ssd na posicão i 
                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;
    
                for (int i = 0; i < 8; i++) {
                    ssd[fb_idx++] = stored_character[i];
                }
    
                //avançando um página para biaxo no display
                cursor.position_y +=8;
                printf("cursor position_y: %d\n", cursor.position_y);

    
                //transferindo os bytes referentes ao caracter armazenados em framebuffer ssd para stored_character
                //framebuffer ssd na posição pagina+1 --> stored_character
                fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;
    
                for (int i = 0; i < 8; i++) {
                    stored_character[i] = ssd[fb_idx++] ;
                }
                
                // setando o cursor no framebuffer ssd na posição pagina+1 
                ssd1306_draw_char(ssd, cursor.position_x , cursor.position_y, '>');
    
                //mostrando o framebuffer ssd no display
                render_on_display(ssd, &frame_area);
    
            }
        }
        else if(joystick_data.velocity_y>0  && (cursor.position_y >= LIMITE_INFERIOR_Y && cursor.position_y <= (ssd1306_height-1)) )
        {
                if(cursor.position_y > LIMITE_INFERIOR_Y+7)
                {
    
    
                    //transferindo os bytes referentes ao caracter armazenados em stored_character para o framebuffer ssd 
                    // stored_character --> framebuffer ssd na posicão i 
                    fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;
        
                    for (int i = 0; i < 8; i++) {
                        ssd[fb_idx++] = stored_character[i];
                    }
        
                    //avançando um página para biaxo no display
                    cursor.position_y -=8;

                    printf("cursor position_y: %d\n", cursor.position_y);

        
                    //transferindo os bytes referentes ao caracter armazenados em framebuffer ssd para stored_character
                    //framebuffer ssd na posição pagina+1 --> stored_character
                    fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;
        
                    for (int i = 0; i < 8; i++) {
                        stored_character[i] = ssd[fb_idx++] ;
                    }
                    
                    // setando o cursor no framebuffer ssd na posição pagina+1 
                    ssd1306_draw_char(ssd, cursor.position_x , cursor.position_y, '>');
        
                    //mostrando o framebuffer ssd no display
                    render_on_display(ssd, &frame_area);



            }
        }

        sleep_ms( (joystick_data.velocity_y==0) ? BASE_TIME_MS : (BASE_TIME_MS/abs(joystick_data.velocity_y)) );

    }
   
    return;
}