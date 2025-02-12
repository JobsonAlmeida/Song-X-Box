 // ----------- ADC e DMA -------------


 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/adc.h"
 #include "hardware/dma.h"
 
 #include "peripherals/ADC_DMA/ADC_DMA_functions.h"
 #include "screens/screens.h"
 
 
 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/pwm.h"
 #include "hardware/clocks.h"
 #include "hardware/i2c.h"
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include "pico/stdlib.h"
 #include "pico/binary_info.h"
 #include "peripherals/I2C_Display/ssd1306.h"
 #include "hardware/i2c.h"
 
 const uint I2C_SDA = 14;
 const uint I2C_SCL = 15;
 
 extern uint16_t x_axis_buffer[];
 extern uint16_t y_axis_buffer[];
 
 extern int dma_chan_0;
 extern int dma_chan_1;
 
 int screen = 1;
 
 int main() {
 
     // ---- REFERENTE À INICIALIZAÇÃO DO DISPLAY ---- 
 
     // Inicialização do i2c
     i2c_init(i2c1, ssd1306_i2c_clock * 1000);
     gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
     gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
     gpio_pull_up(I2C_SDA);
     gpio_pull_up(I2C_SCL);
 
     // Processo de inicialização completo do OLED SSD1306
     ssd1306_init();
 
     // // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
     // struct render_area frame_area = {
     //     start_column : 0,
     //     end_column : ssd1306_width - 1,
     //     start_page : 0,
     //     end_page : ssd1306_n_pages - 1
     // };
 
     // calculate_render_area_buffer_length(&frame_area);
 
     // // zera o display inteiro
     // uint8_t ssd[ssd1306_buffer_length];
     // memset(ssd, 0, ssd1306_buffer_length);
     // render_on_display(ssd, &frame_area);
 
     // ---------- REFERENTE À INICIALIZAÇÃO DO ADC -------------
     stdio_init_all();
     setup_adc_and_dma(); // Inicia o adc e o dma correpondente ao adc  
 
     while (true) {
 
        if (screen == 1) screen1();
         // else if (screen == 2) screen2();
         // else screen3();   
 
         sleep_ms(100);    
           
     };
         
     return 0;
  
 }
 
 //----------- ADC e DMA -------------
 
 
 
 
 // --------------- DISPLAY ----------------------------
 
 
 // #include <stdio.h>
 // #include "pico/stdlib.h"
 // #include "hardware/pwm.h"
 // #include "hardware/clocks.h"
 // #include "hardware/i2c.h"
 
 // #include <stdio.h>
 // #include <string.h>
 // #include <stdlib.h>
 // #include <ctype.h>
 // #include "pico/stdlib.h"
 // #include "pico/binary_info.h"
 // #include "peripherals/I2C_Display/ssd1306.h"
 // #include "hardware/i2c.h"
 
 
 // const uint I2C_SDA = 14;
 // const uint I2C_SCL = 15;
 
 // int main()
 // {
 //     stdio_init_all();   // Inicializa os tipos stdio padrão presentes ligados ao binário
 
 //     // Inicialização do i2c
 //     i2c_init(i2c1, ssd1306_i2c_clock * 1000);
 //     gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
 //     gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
 //     gpio_pull_up(I2C_SDA);
 //     gpio_pull_up(I2C_SCL);
 
 //     // Processo de inicialização completo do OLED SSD1306
 //     ssd1306_init();
 
 //     // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
 //     struct render_area frame_area = {
 //         start_column : 0,
 //         end_column : ssd1306_width - 1,
 //         start_page : 0,
 //         end_page : ssd1306_n_pages - 1
 //     };
 
 //     calculate_render_area_buffer_length(&frame_area);
 
 //     // zera o display inteiro
 //     uint8_t ssd[ssd1306_buffer_length];
 //     memset(ssd, 0, ssd1306_buffer_length);
 //     render_on_display(ssd, &frame_area);
 
 // // Parte do código para exibir a mensagem no display (opcional: mudar ssd1306_height para 32 em ssd1306_i2c.h)
 // // /**
 //     char *text[] = {
 //         "Bem-vindos!   ",
 //         "Embarcatech   "};
 
 //     int y = 0;
 //     for (uint i = 0; i < count_of(text); i++)
 //     {
 //         ssd1306_draw_string(ssd, 0, y, text[i]);
 //         y += 8;
 //     }
 //     render_on_display(ssd, &frame_area);
 // // */
 
 
 //     while(true) {
 //         sleep_ms(1000);
 //     }
 
 //     return 0;
 // }
 
 
 // __________________ END DISPLAY ________________
 
 // // #include "./constants/GPIO_Constants.h"
 // // #include "./constants/Musical_Note_Constants.h"
 // // #include "./types/Adjustment.h"
 // // #include "./headers/play_note.h"
 
 // #define BUZZER_LEFT_1 21  
 // #define BUZZER_RIGHT_1 10
 
 // #define PWM_CLOCK_SOURCE 125000000.0000000000
 
 // // C_0
 // #define C_0_FREQUENCY 16.35160
 // #define C_0_WRAP 61992
 // #define C_0_INTEGER 123
 // #define C_0_FRACTIONAL 5.0000000000
 // #define C_0_DIVIDER (PWM_CLOCK_SOURCE/(C_0_FREQUENCY*(C_0_WRAP+1)))
 
 // // C_5
 // #define C_5_FREQUENCY 523.2511 //Best Frequency Found: = 523.2512
 // #define C_5_WRAP 64783
 // #define C_5_INTEGER 3
 // #define C_5_FRACTIONAL 11.0000
 // #define C_5_DIVIDER 3.6875 //(PWM_CLOCK_SOURCE/(C_5_FREQUENCY*(C_5_WRAP+1)))
 
 // // Bs4
 // #define Bs4_FREQUENCY C_5_FREQUENCY 
 // #define Bs4_WRAP C_5_WRAP 
 // #define Bs4_INTEGER C_5_INTEGER
 // #define Bs4_FRACTIONAL C_5_FRACTIONAL
 // #define Bs4_DIVIDER (PWM_CLOCK_SOURCE/(Bs4_FREQUENCY*(Bs4_WRAP+1)))
 
 // // B_4
 // #define B_4_FREQUENCY 493.8833 //Best Frequency Found: = 493.8833
 // #define B_4_WRAP 51259
 // #define B_4_INTEGER 4
 // #define B_4_FRACTIONAL 15.0000
 // #define B_4_DIVIDER 4.9375 //(PWM_CLOCK_SOURCE/(B_4_FREQUENCY*(B_4_WRAP+1)))
 
 // // As4 - Bb4
 // #define As4_Bb4_FREQUENCY 466.1638 //Best Frequency Found: = 466.1637
 // #define As4_Bb4_WRAP 10645
 // #define As4_Bb4_INTEGER 25
 // #define As4_Bb4_FRACTIONAL 3.0000
 // #define As4_Bb4_DIVIDER 25.1875 //(PWM_CLOCK_SOURCE/(As4_Bb4_FREQUENCY*(As4_Bb4_WRAP+1)))
 
 // // A_4
 // #define A_4_FREQUENCY 440.0000 //Best Frequency Found: = 440.0002
 // #define A_4_WRAP 25112
 // #define A_4_INTEGER 11
 // #define A_4_FRACTIONAL 5.0000
 // #define A_4_DIVIDER 11.3125 //(PWM_CLOCK_SOURCE/(A_4_FREQUENCY*(A_4_WRAP+1)))
 
 // // Gs4 - Ab4
 // #define Gs4_Ab4_FREQUENCY 415.3047 //Best Frequency Found: = 415.3046
 // #define Gs4_Ab4_WRAP 55996
 // #define Gs4_Ab4_INTEGER 5
 // #define Gs4_Ab4_FRACTIONAL 6.0000
 // #define Gs4_Ab4_DIVIDER 5.3750 //(PWM_CLOCK_SOURCE/(Gs4_FREQUENCY*(Gs4_WRAP+1)))
 
 // // G_4
 // #define G_4_FREQUENCY 391.9954 //Best Frequency Found: = 391.9955
 // #define G_4_WRAP 56689
 // #define G_4_INTEGER 5
 // #define G_4_FRACTIONAL 10.0000
 // #define G_4_DIVIDER 5.6250 //(PWM_CLOCK_SOURCE/(G_4_FREQUENCY*(G_4_WRAP+1)))
 
 // // Fs4 - Gb4
 // #define Fs4_Gb4_FREQUENCY 369.9944 //Best Frequency Found: = 369.9944
 // #define Fs4_Gb4_WRAP 61425
 // #define Fs4_Gb4_INTEGER 5
 // #define Fs4_Gb4_FRACTIONAL 8.0000
 // #define Fs4_Gb4_DIVIDER 5.5000 //(PWM_CLOCK_SOURCE/(Fs4_Gb4_FREQUENCY*(Fs4_Gb4_WRAP+1)))
 
 // // F_4
 // #define F_4_FREQUENCY 349.2282 //Best Frequency Found: = 349.2281
 // #define F_4_WRAP 21610
 // #define F_4_INTEGER 16
 // #define F_4_FRACTIONAL 9.0000
 // #define F_4_DIVIDER 16.5625 //(PWM_CLOCK_SOURCE/(F_4_FREQUENCY*(F_4_WRAP+1)))
 
 // // Fb4
 // #define Fb4_FREQUENCY E_4_FREQUENCY
 // #define Fb4_WRAP E_4_WRAP
 // #define Fb4_INTEGER E_4_INTEGER
 // #define Fb4_FRACTIONAL E_4_FRACTIONAL
 // #define Fb4_DIVIDER (PWM_CLOCK_SOURCE/(Fb4_FREQUENCY*(Fb4_WRAP+1)))
 
 // // Es4
 // #define Es4_FREQUENCY F_4_FREQUENCY 
 // #define Es4_WRAP F_4_WRAP 
 // #define Es4_INTEGER F_4_INTEGER
 // #define Es4_FRACTIONAL F_4_FRACTIONAL 
 // #define Es4_DIVIDER (PWM_CLOCK_SOURCE/(Es4_FREQUENCY*(Es4_WRAP+1)))
 
 // // E_4
 // #define E_4_FREQUENCY 329.6276	//Best Frequency Found: = 329.6276
 // #define E_4_WRAP 50986
 // #define E_4_INTEGER 7
 // #define E_4_FRACTIONAL 7.0000
 // #define E_4_DIVIDER 7.4375 //(PWM_CLOCK_SOURCE/(E_4_FREQUENCY*(E_4_WRAP+1)))
 
 // // Ds4 - Eb4
 // #define Ds4_Eb4_FREQUENCY 311.1270 //Best Frequency Found: = 311.1270
 // #define Ds4_Eb4_WRAP 4986
 // #define Ds4_Eb4_INTEGER 80
 // #define Ds4_Eb4_FRACTIONAL 9.0000
 // #define Ds4_Eb4_DIVIDER 80.5625 //(PWM_CLOCK_SOURCE/(Ds4_Eb4_FREQUENCY*(Ds4_Eb4_WRAP+1)))
 
 // // D_4
 // #define D_4_FREQUENCY 293.6648 //Best Frequency Found: = 293.6648
 // #define D_4_WRAP 37626
 // #define D_4_INTEGER 11
 // #define D_4_FRACTIONAL 5.0000
 // #define D_4_DIVIDER 11.3125 //(PWM_CLOCK_SOURCE/(D_4_FREQUENCY*(D_4_WRAP+1)))
 
 // // Cs4 - Db4
 // #define Cs4_Db4_FREQUENCY 277.1826 //Best Frequency Found: = 277.1826
 // #define Cs4_Db4_WRAP 51538
 // #define Cs4_Db4_INTEGER 8
 // #define Cs4_Db4_FRACTIONAL 12.0000
 // #define Cs4_Db4_DIVIDER 8.7500 //(PWM_CLOCK_SOURCE/(Cs4_Db4_FREQUENCY*(Cs4_Db4_WRAP+1)))
 
 // // C_4
 // #define C_4_FREQUENCY 261.6256 //Best Frequency Found: = 261.6256
 // #define C_4_WRAP 64783
 // #define C_4_INTEGER 7
 // #define C_4_FRACTIONAL 6.0000
 // #define C_4_DIVIDER 7.3750 //(PWM_CLOCK_SOURCE/(C_4_FREQUENCY*(C_4_WRAP+1)))
 
 // // Cb4
 // #define Cb4_FREQUENCY B_3_FREQUENCY
 // #define Cb4_WRAP B_3_WRAP
 // #define Cb4_INTEGER B_3_INTEGER
 // #define Cb4_FRACTIONAL B_3_FRACTIONAL
 // #define Cb4_DIVIDER (PWM_CLOCK_SOURCE/(Cb4_FREQUENCY*(Cb4_WRAP+1)))
 
 // // Bs3
 // #define Bs3_FREQUENCY 
 // #define Bs3_WRAP 
 // #define Bs3_INTEGER 
 // #define Bs3_FRACTIONAL 
 // #define Bs3_DIVIDER (PWM_CLOCK_SOURCE/(Bs3_FREQUENCY*(Bs3_WRAP+1)))
 
 // // B_3
 // #define B_3_FREQUENCY 246.9417 //Best Frequency Found: = 246.9417
 // #define B_3_WRAP 16837
 // #define B_3_INTEGER 30
 // #define B_3_FRACTIONAL 1.0000
 // #define B_3_DIVIDER 30.0625 //(PWM_CLOCK_SOURCE/(B_3_FREQUENCY*(B_3_WRAP+1)))
 
 // // Bb3
 // #define Bb4_FREQUENCY 
 // #define Bb4_WRAP 
 // #define Bb4_INTEGER 
 // #define Bb4_FRACTIONAL 
 // #define Bb4_DIVIDER (PWM_CLOCK_SOURCE/(Bb4_FREQUENCY*(Bb4_WRAP+1)))
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 // uint32_t pwm_clock_hz;
 
 // typedef struct {
 //     uint16_t wrap;
 //     float divider;
 // } Adjustment;
 
 
 // Adjustment get_divisor_wrap_from_note(char note[3]){
 
 //     static Adjustment adjustment; 
 
 //     if(note[2] == '0')
 //     {
 
 //         if(note[0] == 'C'){
 //                  if(note[1] == '-') {adjustment.wrap = C_0_WRAP; adjustment.divider = C_0_DIVIDER;}
 //             else if(note[1] == '#') {}
 //             else                    {  }
 //         }
 //         else if(note[0] == 'D'){
 //             if(note[1] == '-') {}
 //             else if(note[1] == '#') {}
 //             else {}
 //         }
 //         else if(note[0] == 'E'){
 //             if(note[1] == '-') {}
 //             else if(note[1] == '#') {}
 //             else {}
 //         }
 //         else if(note[0] == 'F'){
 //             if(note[1] == '-') {}
 //             else if(note[1] == '#') {}
 //             else {}
 //         }
 //         else if(note[0] == 'G'){
 //             if(note[1] == '-') {}
 //             else if(note[1] == '#') {}
 //             else {}
 //         }
 //         else if(note[0] == 'A'){
 //                  if(note[1] == '-') {  }
 //             else if(note[1] == '#') {}
 //             else {}
 //         }
 //         else if(note[0] == 'B'){
 //             if(note[1] == '-') {}
 //             else if(note[1] == '#') {}
 //             else {}
 //         }
 
 //     }    
 
 //      if(note[2] == '4')
 //     {
 //         if(note[0] == 'C'){
 //                  if(note[1] == '-') { adjustment.wrap = C_4_WRAP; adjustment.divider = C_4_DIVIDER; }
 //             else if(note[1] == '#') { adjustment.wrap = Cs4_Db4_WRAP; adjustment.divider = Cs4_Db4_DIVIDER; }
 //             else                    { adjustment.wrap = Cb4_WRAP; adjustment.divider = Cb4_DIVIDER; }
 //         }
 //         else if(note[0] == 'D'){
 //             if(note[1] == '-')      { adjustment.wrap = D_4_WRAP; adjustment.divider = D_4_DIVIDER; }
 //             else if(note[1] == '#') { adjustment.wrap = Ds4_Eb4_WRAP; adjustment.divider = Ds4_Eb4_DIVIDER; }
 //             else                    { adjustment.wrap = Cs4_Db4_WRAP; adjustment.divider = Cs4_Db4_DIVIDER; }
 //         }
 //         else if(note[0] == 'E') {
 //             if(note[1] == '-')      { adjustment.wrap = E_4_WRAP; adjustment.divider = E_4_DIVIDER;}
 //             else if(note[1] == '#') { adjustment.wrap = Es4_WRAP; adjustment.divider = Es4_DIVIDER; }
 //             else                    { adjustment.wrap = Ds4_Eb4_WRAP; adjustment.divider = Ds4_Eb4_DIVIDER; }
 //         }
 //         else if(note[0] == 'F'){
 //             if(note[1] == '-')      { adjustment.wrap = F_4_WRAP; adjustment.divider = F_4_DIVIDER; }
 //             else if(note[1] == '#') { adjustment.wrap = Fs4_Gb4_WRAP; adjustment.divider = Fs4_Gb4_DIVIDER; }
 //             else                    { adjustment.wrap = Fb4_WRAP; adjustment.divider = Fb4_DIVIDER; }
 //         }
 //         else if(note[0] == 'G'){
 //             if(note[1] == '-')      { adjustment.wrap = G_4_WRAP; adjustment.divider = G_4_DIVIDER; }
 //             else if(note[1] == '#') { adjustment.wrap = Gs4_Ab4_WRAP; adjustment.divider = Gs4_Ab4_DIVIDER; }
 //             else                    { adjustment.wrap = Fs4_Gb4_WRAP; adjustment.divider = Fs4_Gb4_DIVIDER; }
 //         }
 //         else if(note[0] == 'A'){
 //                  if(note[1] == '-') { adjustment.wrap = A_4_WRAP; adjustment.divider = A_4_DIVIDER; }
 //             else if(note[1] == '#') { adjustment.wrap = As4_Bb4_WRAP; adjustment.divider = As4_Bb4_DIVIDER; }
 //             else                    { adjustment.wrap = Gs4_Ab4_WRAP; adjustment.divider = Gs4_Ab4_DIVIDER; }
 //         }
 //         else if(note[0] == 'B'){
 //             if(note[1] == '-')      { adjustment.wrap = B_4_WRAP; adjustment.divider = B_4_DIVIDER; }
 //             else if(note[1] == '#') { adjustment.wrap = Bs4_WRAP; adjustment.divider = Bs4_DIVIDER; }
 //             else                    { adjustment.wrap = As4_Bb4_WRAP; adjustment.divider = As4_Bb4_DIVIDER; }
 //         }
 
 //     }    
 
 //     printf("adjustment.divider = %.3f - adjustment.wrap = %d \n", adjustment.divider , adjustment.wrap);
  
 //     return adjustment;
 
 // }
 
 // // Struct para ser passada para a função de callback repeating_timer_callback
 // struct Data_Struct{
 //     uint slice;
 // };
 // struct Data_Struct data_note;
 
 // int64_t stop_note(alarm_id_t id, void *user_data) {
 
 //     struct Data_Struct* data = (struct Data_Struct*) user_data;
 
 //     pwm_set_enabled(data->slice, false);
 
 //     return 0;
 
 // }
 
 
 // void play_note(uint buzzer_id, char note[3], float duty_cycle, uint32_t time_ms){
 
 //     // static varibale so that they are not created every time
 //     static uint slice = 2;
 //     static uint channel = 1;
 //     static Adjustment adjustement = {0, 0.0f};
 
 //     slice = pwm_gpio_to_slice_num(buzzer_id);
 //     channel = pwm_gpio_to_channel(buzzer_id);    
 
 //     adjustement = get_divisor_wrap_from_note(note);
     
 //     pwm_set_clkdiv(slice, adjustement.divider);
 //     pwm_set_wrap(slice,  adjustement.wrap);
 
 //     pwm_set_chan_level(slice, channel, duty_cycle*(adjustement.wrap+1));
 
 //     data_note.slice = slice;
 
 //     pwm_set_enabled(slice, true);
 
 //     add_alarm_in_ms(time_ms, stop_note, &data_note, false);
 
 //     return;
 // }
 
 
 // int main() {
 
 //     irq_set_enabled(PWM_IRQ_WRAP, true);  // Habilitar as interrupções de PWM (se necessário)
 
 //     stdio_init_all();
 //     sleep_ms(10000);
 //     printf("Programa executando\n");
 
 //     pwm_clock_hz = clock_get_hz(clk_sys);
 //     printf("Frequencia fora while: %u Hz\n", pwm_clock_hz);
 
 //     //Initial Configurations
 //     gpio_set_function(BUZZER_LEFT_1, GPIO_FUNC_PWM);
 //     gpio_set_function(BUZZER_RIGHT_1, GPIO_FUNC_PWM);
 
 //     // sleep_ms(4000);
 
 //     printf("Antes de playnote \n");
 
 //     play_note(BUZZER_RIGHT_1, "A-4", 0.005, 2000);
 
 //     // O loop vazio. 
 //     while (true) {
 //         //  printf("A frequência do clock do PWM (clk_sys) é: %u Hz\n", pwm_clock_hz);
 //         //  sleep_ms(1000);
 
 //         tight_loop_contents(); // Função que otimiza o loop vazio para evitar consumo excessivo de CPU.
 //     }
 
 //     return 0;
    
 // }
 
 
 