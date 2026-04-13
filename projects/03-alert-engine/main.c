#include <stdio.h>

#include "../01-sensor-pipeline/ring_buffer.h"
#include "../01-sensor-pipeline/sensor_pipeline.h"
#include "../02-lightweight-inference/inference.h"
#include "alert_engine.h"

static inference_result_t evaluate_window(const float *samples, size_t count)
{
    float storage[8];
    float_ring_buffer_t rb;
    sensor_features_t features;
    inference_result_t result;

    result.score = 999.0f;
    result.level = INFERENCE_ALERT;

    if (float_ring_buffer_init(&rb, storage, 8) != 0) {
        return result;
    }

    for (size_t i = 0; i < count; i++) {
        if (float_ring_buffer_push(&rb, samples[i]) != 0) {
            return result;
        }
    }

    if (sensor_compute_features(&rb, &features) != 0) {
        return result;
    }

    return run_inference(&features);
}

int main(void)
{
    const float windows[][8] = {
        {40.0f, 40.0f, 39.9f, 40.1f, 40.0f, 40.1f, 39.8f, 40.0f},
        {40.0f, 40.2f, 40.1f, 40.4f, 40.8f, 41.0f, 41.1f, 41.0f},
        {40.1f, 40.3f, 40.4f, 40.6f, 41.0f, 41.3f, 41.5f, 41.4f},
        {40.0f, 41.0f, 42.5f, 43.2f, 44.1f, 44.8f, 45.0f, 45.3f},
        {40.2f, 40.1f, 40.0f, 39.9f, 40.0f, 39.8f, 40.1f, 40.0f},
        {40.1f, 40.0f, 39.9f, 40.0f, 39.8f, 39.9f, 40.0f, 40.1f}};

    alert_engine_t engine;
    alert_engine_init(&engine);

    for (size_t i = 0; i < sizeof(windows) / sizeof(windows[0]); i++) {
        inference_result_t result = evaluate_window(windows[i], 8);
        alert_engine_update(&engine, result);

        printf("step=%zu score=%.2f inference=%s system_state=%s cooldown=%u\n", i + 1,
               result.score, inference_level_to_string(result.level),
               system_state_to_string(engine.state), engine.cooldown_ticks_remaining);
    }

    return 0;
}
