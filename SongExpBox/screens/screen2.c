#include <stdio.h>

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
        "1ABCDEFGHIJKLMNO",
        "2ABCDEFGHIJKLMNO",
        "3ABCDEFGHIJKLMNO",
        "4ABCDEFGHIJKLMNO",
        "5ABCDEFGHIJKLMNO",
        "6ABCDEFGHIJKLMNO",
        "7ABCDEFGHIJKLMNO",
        "8ABCDEFGHIJKLMNO",

    };

    int y = 0;
    for (uint i = 0; i < count_of(text); i++)
    {
        ssd1306_draw_string(ssd, 0, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);

    while(screen==2){
        printf("screen na tela 2 %d\n", screen);
        sleep_ms(50);
    }

    return;
}