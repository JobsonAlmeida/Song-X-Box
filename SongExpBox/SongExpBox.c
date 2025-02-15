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
 #include "hardware/gpio.h"
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include "pico/stdlib.h"
 #include "pico/binary_info.h"
 #include "peripherals/I2C_Display/ssd1306.h"
 #include "hardware/i2c.h"
 #include "peripherals/GPIO_BUTTONS_A_B/GPIO_BUTTONS_A_B.h"
 #include "sound/sound.h"
 

// const uint I2C_SDA = 14;
// const uint I2C_SCL = 15;

// extern uint16_t x_axis_buffer[];
// extern uint16_t y_axis_buffer[];

// extern int dma_chan_0;
// extern int dma_chan_1;

// int screen;

// cursor_data cursor;

// int main() {
 
//      // ---- REFERENTE À INICIALIZAÇÃO DO DISPLAY ---- 
 
//      // Inicialização do i2c
//      i2c_init(i2c1, ssd1306_i2c_clock * 1000);
//      gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
//      gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
//      gpio_pull_up(I2C_SDA);
//      gpio_pull_up(I2C_SCL);
 
//      // Processo de inicialização completo do OLED SSD1306
//      ssd1306_init();
 
    
 
//      // ---------- REFERENTE À INICIALIZAÇÃO DO ADC -------------
//      stdio_init_all();
//      setup_adc_and_dma(); // Inicia o adc e o dma correpondente ao adc  

//      /// gpio BUTTONS A E B
//      gpio_init_buttons();

//      // Buzzers
//      buzzers_config();


//      screen = 0; 
//      while (true) {
 
//              if (screen == 0) screen0();
//         else if (screen == 1) screen1();
//         else if (screen == 2) screen2();           
//      };
         
//      return 0;
  
// }
 

int main() {

irq_set_enabled(PWM_IRQ_WRAP, true);  // Habilitar as interrupções de PWM (se necessário)

stdio_init_all();

uint32_t pwm_clock_hz = clock_get_hz(clk_sys);
printf("Frequencia fora while: %u Hz\n", pwm_clock_hz);

//Initial Configurations
gpio_set_function(BUZZER_LEFT_1, GPIO_FUNC_PWM);
gpio_set_function(BUZZER_RIGHT_1, GPIO_FUNC_PWM);

// sleep_ms(4000);

printf("Antes de playnote \n");

play_note(BUZZER_RIGHT_1, "A-4", 0.005, 2000);

// O loop vazio. 
while (true) {
     //  printf("A frequência do clock do PWM (clk_sys) é: %u Hz\n", pwm_clock_hz);
     //  sleep_ms(1000);

     tight_loop_contents(); // Função que otimiza o loop vazio para evitar consumo excessivo de CPU.
}

return 0;

}

 
 