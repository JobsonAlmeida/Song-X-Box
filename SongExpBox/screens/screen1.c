#include <stdio.h>
#include "screens.h"
#include "../peripherals/I2C_Display/ssd1306.h"
#include "../peripherals/ADC_DMA/ADC_DMA_functions.h"

#include <string.h>


extern int screen;
extern uint16_t x_axis_buffer[];
extern uint16_t y_axis_buffer[];

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
        "SELECIONE:",
        "#",
        ":TREINAR OUVIDO",
        ":TOCAR MUSICA",
        ":ABC MUSICA"};

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    typedef struct 
    {
        int16_t position_x;
        int16_t position_y;

    } cursor_data;

    cursor_data cursor;

    cursor.position_x = 0; 
    cursor.position_y = 23;  

    int fb_idx;
    uint8_t stored_character[8];

    while (screen == 1){

        joystick_data joystick_data = velocity_and_direction(x_axis_buffer, y_axis_buffer);

        // printf("joystick_data.velocity_x %d - joystick_data.velocit_y: %d\n", joystick_data.velocity_x, joystick_data.velocity_y);
        
        if(joystick_data.velocity_y==0){
            ssd1306_draw_char(ssd, cursor.position_x , cursor.position_y, '>');
            render_on_display(ssd, &frame_area);
        }        
        else if(joystick_data.velocity_y<0){

            fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = stored_character[i];
            }
            cursor.position_y +=8;

            fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;

            for (int i = 0; i < 8; i++) {
                stored_character[i] = ssd[fb_idx++] ;
            }
            
            ssd1306_draw_char(ssd, cursor.position_x , cursor.position_y, '>');
            render_on_display(ssd, &frame_area);

        }

        else if(joystick_data.velocity_y>0){

            fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;

            for (int i = 0; i < 8; i++) {
                ssd[fb_idx++] = stored_character[i];
            }
            cursor.position_y -=8;

            fb_idx = (cursor.position_y/8) * 128 + cursor.position_x;

            for (int i = 0; i < 8; i++) {
                stored_character[i] = ssd[fb_idx++] ;
            }
            
            ssd1306_draw_char(ssd, cursor.position_x , cursor.position_y, '>');
            render_on_display(ssd, &frame_area);

        }

       
    
        sleep_ms(100);

    }
   
    return;
}