
#include "pico/stdlib.h"

#define BUZZER_LEFT_1 21  
#define BUZZER_RIGHT_1 10

typedef struct {
    uint16_t wrap;
    float divider;
} Adjustment;


//Obtem os valores específicos do diviosr e do wrap para cada nota 
Adjustment get_divisor_wrap_from_note(char note[3]);

//Faz a nota parar de tocar
int64_t stop_note(alarm_id_t id, void *user_data);

//Faz a nota começar a tocar
void play_note(uint buzzer_id, char note[3], float duty_cycle, uint32_t time_ms);

// Inicializa o GPIO dos uzzers
void buzzers_config();