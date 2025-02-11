#include "hardware/adc.h"
#include "hardware/dma.h"
#include "ADC_DMA_types.h"

#include <stdio.h>
#include "pico/stdlib.h"

#define PIN_JOYSTICK_Y 26
#define PIN_JOYSTICK_X 27 

#define NUM_AMOSTRAS 1
uint16_t x_axis_buffer[NUM_AMOSTRAS];
uint16_t y_axis_buffer[NUM_AMOSTRAS];

void setup_adc() {

    adc_init();
    adc_gpio_init(PIN_JOYSTICK_X);  
    adc_gpio_init(PIN_JOYSTICK_Y);

    adc_select_input(0);

    adc_set_clkdiv(480);  // Reduz a frequência da conversão.

    adc_fifo_setup(
        true,    // Habilita FIFO
        true,    // Habilita requisição de DMA
        1,       // Número mínimo de amostras no FIFO antes de avisar
        false,   // Sem shift
        false    // Sem ativação automática
    );
    
    adc_run(true);  // Inicia conversão contínua
}


int dma_chan_0, dma_chan_1;

void adc_dma_irq_handler() {

    // Identifica qual canal DMA terminou a transferência
    if (dma_channel_get_irq0_status(dma_chan_0)) {
        dma_channel_acknowledge_irq0(dma_chan_0); //reconhece e limpa a interrupção gerada por um canal específico do DMA.
        // adc_select_input(1);  // Troca para ADC1
        // dma_channel_start(dma_chan_1);

        dma_channel_start(dma_chan_0);

        // printf("Entrou por dma_cha_0 \n");
     } 

    if (dma_channel_get_irq0_status(dma_chan_1)) {
        dma_channel_acknowledge_irq0(dma_chan_1);

        dma_channel_start(dma_chan_1);


    //     adc_select_input(0);  // Troca para ADC0
    //     dma_channel_start(dma_chan_0);
    }

    // if (dma_channel_get_irq1_status(dma_chan_0)) {
    //     dma_channel_acknowledge_irq1(dma_chan_0); //reconhece e limpa a interrupção gerada por um canal específico do DMA.
    //     // adc_select_input(1);  // Troca para ADC1
    //     // dma_channel_start(dma_chan_1);

    //     // printf("Entrou por dma_cha_0 \n");
    //  } 

    return;
}


void setup_dma_adc() {

    dma_chan_0 = dma_claim_unused_channel(true); // Obtém um canal DMA disponível
    dma_chan_1 = dma_claim_unused_channel(true); // Obtém um canal DMA disponível

    dma_channel_config c_0 = dma_channel_get_default_config(dma_chan_0);    
    channel_config_set_transfer_data_size(&c_0, DMA_SIZE_16); // Transferência de 16 bits (ADC é de 12 bits)
    channel_config_set_read_increment(&c_0, false);  // Não incrementar endereço de leitura (fixo no ADC)
    channel_config_set_write_increment(&c_0, false);  // Não incrementar endereço de escrita (buffer na RAM)
    channel_config_set_dreq(&c_0, DREQ_ADC);  // O ADC controla o DMA (transfere quando há dado novo)

    dma_channel_config c_1 = dma_channel_get_default_config(dma_chan_1);    
    channel_config_set_transfer_data_size(&c_1, DMA_SIZE_16); // Transferência de 16 bits (ADC é de 12 bits)
    channel_config_set_read_increment(&c_1, false);  // Não incrementar endereço de leitura (fixo no ADC)
    channel_config_set_write_increment(&c_1, false);  // Não incrementar endereço de escrita (buffer na RAM)
    channel_config_set_dreq(&c_1, DREQ_ADC);  // O ADC controla o DMA (transfere quando há dado novo)

    dma_channel_configure(
        dma_chan_0,
        &c_0,
        y_axis_buffer,  // Destino: buffer de memória
        &adc_hw->fifo,  // Fonte: FIFO do ADC
        NUM_AMOSTRAS,  // Número de amostras a coletar
        false  // Não inicia automaticamente
    );

    dma_channel_configure(
        dma_chan_1,
        &c_1,
        x_axis_buffer,  // Destino: buffer de memória
        &adc_hw->fifo,  // Fonte: FIFO do ADC
        NUM_AMOSTRAS,  // Número de amostras a coletar
        false  // Não inicia automaticamente
    );

    // Configura interrupções
    dma_channel_set_irq0_enabled(dma_chan_0, true); //configura o canal 0 do DMA para disparar IRQ0
    // dma_channel_set_irq0_enabled(dma_chan_1, true); //configura o canal 1 do DMA para disparar IRQ0
    irq_set_exclusive_handler(DMA_IRQ_0, adc_dma_irq_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    dma_channel_start(dma_chan_0);  // Inicia a conversão pelo canal 0
    // dma_channel_start(dma_chan_1);  // Inicia a conversão pelo canal 1

    return;

}

void inicia_interrupcao_dma(){

    // Configura interrupções
    dma_channel_set_irq1_enabled(dma_chan_0, true); //configura o canal de DMA para disparar IRQ0
    // dma_channel_set_irq0_enabled(dma_chan_1, true); //configura o canal de DMA para disparar IRQ0
    irq_set_exclusive_handler(DMA_IRQ_1, adc_dma_irq_handler);
    // irq_set_enabled(DMA_IRQ_1, true);

    return; 

}

void setup_adc_and_dma(){

    setup_adc();
    setup_dma_adc();

    return;
}

joystick_data velocity_and_direction(uint16_t buffer_adc_x[], uint16_t buffer_adc_y[]){

    static joystick_data joystick_data;

    // velocidade no eixo x para a esquerda      
    if(buffer_adc_x[0]>= 0 && buffer_adc_x[0] <=255 ){
        joystick_data.velocity_x = -7;                
    }
    else  if(buffer_adc_x[0]>= 256 && buffer_adc_x[0] <=511 ){
        joystick_data.velocity_x = -6;                
    }
    else  if(buffer_adc_x[0]>= 512 && buffer_adc_x[0] <=767 ){
        joystick_data.velocity_x = -5;                
    }
    else  if(buffer_adc_x[0]>= 768 && buffer_adc_x[0] <=1023 ){
        joystick_data.velocity_x = -4;                
    }
    else  if(buffer_adc_x[0]>= 1024 && buffer_adc_x[0] <=1279 ){
        joystick_data.velocity_x = -3;                
    }
    else  if(buffer_adc_x[0]>= 1280 && buffer_adc_x[0] <=1535 ){
        joystick_data.velocity_x = -2;                
    }
    else  if(buffer_adc_x[0]>= 1536 && buffer_adc_x[0] <=1791 ){
        joystick_data.velocity_x = -1;                
    }
    else  if(buffer_adc_x[0]>= 1792 && buffer_adc_x[0] <=2047 ){
        joystick_data.velocity_x = 0;                
    }

    // velocidade no eixo y para a direita      
    else if(buffer_adc_x[0]>= 2048 && buffer_adc_x[0] <=2303 ){
        joystick_data.velocity_x = 0;                
    }
    else  if(buffer_adc_x[0]>= 2304 && buffer_adc_x[0] <=2559 ){
        joystick_data.velocity_x = +1;                
    }
    else  if(buffer_adc_x[0]>= 2560 && buffer_adc_x[0] <=2815 ){
        joystick_data.velocity_x = +2;                
    }
    else  if(buffer_adc_x[0]>= 2816 && buffer_adc_x[0] <=3071 ){
        joystick_data.velocity_x = +3;                
    }
    else  if(buffer_adc_x[0]>= 3072 && buffer_adc_x[0] <=3327 ){
        joystick_data.velocity_x = +4;                
    }
    else  if(buffer_adc_x[0]>= 3328 && buffer_adc_x[0] <=3583 ){
        joystick_data.velocity_x = +5;                
    }
    else  if(buffer_adc_x[0]>= 3584 && buffer_adc_x[0] <=3839 ){
        joystick_data.velocity_x = +6;                
    }
    else  if(buffer_adc_x[0]>= 3840 && buffer_adc_x[0] <=4095 ){
        joystick_data.velocity_x = +7;                
    }

    else {
        joystick_data.velocity_x = 0;
    }

    // velocidade no eixo y para a esquerda      
    if(buffer_adc_y[0]>= 0 && buffer_adc_y[0] <=255 ){
        joystick_data.velocity_y = -7;                
    }
    else  if(buffer_adc_y[0]>= 256 && buffer_adc_y[0] <=511 ){
        joystick_data.velocity_y = -6;                
    }
    else  if(buffer_adc_y[0]>= 512 && buffer_adc_y[0] <=767 ){
        joystick_data.velocity_y = -5;                
    }
    else  if(buffer_adc_y[0]>= 768 && buffer_adc_y[0] <=1023 ){
        joystick_data.velocity_y = -4;                
    }
    else  if(buffer_adc_y[0]>= 1024 && buffer_adc_y[0] <=1279 ){
        joystick_data.velocity_y = -3;                
    }
    else  if(buffer_adc_y[0]>= 1280 && buffer_adc_y[0] <=1535 ){
        joystick_data.velocity_y = -2;                
    }
    else  if(buffer_adc_y[0]>= 1536 && buffer_adc_y[0] <=1791 ){
        joystick_data.velocity_y = -1;                
    }
    else  if(buffer_adc_y[0]>= 1792 && buffer_adc_y[0] <=2047 ){
        joystick_data.velocity_y = 0;                
    }

    // velocidade no eixo y para a direita      
    else if(buffer_adc_y[0]>= 2048 && buffer_adc_y[0] <=2303 ){
        joystick_data.velocity_y = 0;                
    }
    else  if(buffer_adc_y[0]>= 2304 && buffer_adc_y[0] <=2559 ){
        joystick_data.velocity_y = +1;                
    }
    else  if(buffer_adc_y[0]>= 2560 && buffer_adc_y[0] <=2815 ){
        joystick_data.velocity_y = +2;                
    }
    else  if(buffer_adc_y[0]>= 2816 && buffer_adc_y[0] <=3071 ){
        joystick_data.velocity_y = +3;                
    }
    else  if(buffer_adc_y[0]>= 3072 && buffer_adc_y[0] <=3327 ){
        joystick_data.velocity_y = +4;                
    }
    else  if(buffer_adc_y[0]>= 3328 && buffer_adc_y[0] <=3583 ){
        joystick_data.velocity_y = +5;                
    }
    else  if(buffer_adc_y[0]>= 3584 && buffer_adc_y[0] <=3839 ){
        joystick_data.velocity_y = +6;                
    }
    else  if(buffer_adc_y[0]>= 3840 && buffer_adc_y[0] <=4095 ){
        joystick_data.velocity_y = +7;                
    }

    else {
        joystick_data.velocity_y = 0;
    }

    return joystick_data;
    
}