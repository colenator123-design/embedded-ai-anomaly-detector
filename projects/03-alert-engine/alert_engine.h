#ifndef ALERT_ENGINE_H
#define ALERT_ENGINE_H

#include "../02-lightweight-inference/inference.h"

typedef enum {
    SYSTEM_STATE_NORMAL = 0,
    SYSTEM_STATE_WARNING,
    SYSTEM_STATE_ALERT
} system_state_t;

typedef struct {
    system_state_t state;
    unsigned int consecutive_warning_count;
    unsigned int consecutive_alert_count;
    unsigned int cooldown_ticks_remaining;
} alert_engine_t;

void alert_engine_init(alert_engine_t *engine);
void alert_engine_update(alert_engine_t *engine, inference_result_t result);
const char *system_state_to_string(system_state_t state);

#endif
