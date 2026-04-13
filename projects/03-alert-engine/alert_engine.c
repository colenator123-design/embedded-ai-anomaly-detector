#include "alert_engine.h"

void alert_engine_init(alert_engine_t *engine)
{
    if (engine == 0) {
        return;
    }

    engine->state = SYSTEM_STATE_NORMAL;
    engine->consecutive_warning_count = 0;
    engine->consecutive_alert_count = 0;
    engine->cooldown_ticks_remaining = 0;
}

void alert_engine_update(alert_engine_t *engine, inference_result_t result)
{
    if (engine == 0) {
        return;
    }

    if (engine->cooldown_ticks_remaining > 0) {
        engine->cooldown_ticks_remaining--;
    }

    switch (result.level) {
    case INFERENCE_NORMAL:
        engine->consecutive_warning_count = 0;
        engine->consecutive_alert_count = 0;
        if (engine->cooldown_ticks_remaining == 0) {
            engine->state = SYSTEM_STATE_NORMAL;
        }
        break;

    case INFERENCE_WARNING:
        engine->consecutive_warning_count++;
        engine->consecutive_alert_count = 0;
        if (engine->consecutive_warning_count >= 2 &&
            engine->state != SYSTEM_STATE_ALERT) {
            engine->state = SYSTEM_STATE_WARNING;
        }
        break;

    case INFERENCE_ALERT:
        engine->consecutive_alert_count++;
        engine->consecutive_warning_count = 0;
        if (engine->consecutive_alert_count >= 1) {
            engine->state = SYSTEM_STATE_ALERT;
            engine->cooldown_ticks_remaining = 2;
        }
        break;
    }
}

const char *system_state_to_string(system_state_t state)
{
    switch (state) {
    case SYSTEM_STATE_NORMAL:
        return "NORMAL";
    case SYSTEM_STATE_WARNING:
        return "WARNING";
    case SYSTEM_STATE_ALERT:
        return "ALERT";
    }

    return "UNKNOWN";
}
