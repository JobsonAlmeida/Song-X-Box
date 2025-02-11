#include "hardware/adc.h"
#include "hardware/dma.h"

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