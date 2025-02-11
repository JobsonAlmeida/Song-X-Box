#include "hardware/adc.h"
#include "hardware/dma.h"
#include "ADC_types.h"

#define PIN_JOYSTICK_X 27

#define NUM_AMOSTRAS 1
uint16_t buffer_adc_x[NUM_AMOSTRAS];

void setup_adc() {
    adc_init();
    adc_gpio_init(PIN_JOYSTICK_X);  // Configura o pino do ADC
    adc_select_input(1);  // Canal 1 (GPIO27)
    adc_set_clkdiv(480);  // Reduz a frequência da conversão (ajuste conforme necessário)

    adc_fifo_setup(
        true,    // Habilita FIFO
        true,    // Habilita requisição de DMA
        1,       // Número mínimo de amostras no FIFO antes de avisar
        false,   // Sem shift
        false    // Sem ativação automática
    );
    
    adc_run(true);  // Inicia conversão contínua
}


int dma_chan;

void setup_dma_adc() {

    dma_chan = dma_claim_unused_channel(true); // Obtém um canal DMA disponível
    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    
    channel_config_set_transfer_data_size(&c, DMA_SIZE_16); // Transferência de 16 bits (ADC é de 12 bits)
    channel_config_set_read_increment(&c, false);  // Não incrementar endereço de leitura (fixo no ADC)
    // channel_config_set_ring(&c, true, 4);  // Habilita buffer circular de 16 bytes    
    channel_config_set_write_increment(&c, false);  // Não incrementar endereço de escrita (buffer na RAM)
    channel_config_set_dreq(&c, DREQ_ADC);  // O ADC controla o DMA (transfere quando há dado novo)
    channel_config_set_chain_to(&c, dma_chan);  // DMA se reinicia automaticamente após cada transferência concluída

    dma_channel_configure(
        dma_chan,
        &c,
        buffer_adc_x,  // Destino: buffer de memória
        &adc_hw->fifo,  // Fonte: FIFO do ADC
        NUM_AMOSTRAS,  // Número de amostras a coletar
        true  // Não inicia automaticamente
    );

    dma_channel_start(dma_chan);

    return;

}

void setup_adc_and_dma(){

    setup_adc();
    setup_dma_adc();

    return;
}


joystick_data velocity_and_direction(uint16_t buffer_adc_x[]){

    static joystick_data joystick_data;

    // velocidade para a esquerda      
    if(buffer_adc_x[0]>= 0 && buffer_adc_x[0] <=255 ){
        joystick_data.velocity = -7;                
    }
    else  if(buffer_adc_x[0]>= 256 && buffer_adc_x[0] <=511 ){
        joystick_data.velocity = -6;                
    }
    else  if(buffer_adc_x[0]>= 512 && buffer_adc_x[0] <=767 ){
        joystick_data.velocity = -5;                
    }
    else  if(buffer_adc_x[0]>= 768 && buffer_adc_x[0] <=1023 ){
        joystick_data.velocity = -4;                
    }
    else  if(buffer_adc_x[0]>= 1024 && buffer_adc_x[0] <=1279 ){
        joystick_data.velocity = -3;                
    }
    else  if(buffer_adc_x[0]>= 1280 && buffer_adc_x[0] <=1535 ){
        joystick_data.velocity = -2;                
    }
    else  if(buffer_adc_x[0]>= 1536 && buffer_adc_x[0] <=1791 ){
        joystick_data.velocity = -1;                
    }
    else  if(buffer_adc_x[0]>= 1792 && buffer_adc_x[0] <=2047 ){
        joystick_data.velocity = 0;                
    }

    // velocidade para a direita      
    else if(buffer_adc_x[0]>= 2048 && buffer_adc_x[0] <=2303 ){
        joystick_data.velocity = 0;                
    }
    else  if(buffer_adc_x[0]>= 2304 && buffer_adc_x[0] <=2559 ){
        joystick_data.velocity = +1;                
    }
    else  if(buffer_adc_x[0]>= 2560 && buffer_adc_x[0] <=2815 ){
        joystick_data.velocity = +2;                
    }
    else  if(buffer_adc_x[0]>= 2816 && buffer_adc_x[0] <=3071 ){
        joystick_data.velocity = +3;                
    }
    else  if(buffer_adc_x[0]>= 3072 && buffer_adc_x[0] <=3327 ){
        joystick_data.velocity = +4;                
    }
    else  if(buffer_adc_x[0]>= 3328 && buffer_adc_x[0] <=3583 ){
        joystick_data.velocity = +5;                
    }
    else  if(buffer_adc_x[0]>= 3584 && buffer_adc_x[0] <=3839 ){
        joystick_data.velocity = +6;                
    }
    else  if(buffer_adc_x[0]>= 3840 && buffer_adc_x[0] <=4095 ){
        joystick_data.velocity = +7;                
    }

    else {
        joystick_data.velocity = 0;
    }

    return joystick_data;
    
}