#include <stdio.h>

#include "../01-sensor-pipeline/ring_buffer.h"
#include "../01-sensor-pipeline/sensor_pipeline.h"
#include "inference.h"

static int run_case(const float *samples, size_t sample_count, const char *label)
{
    float storage[8];
    float_ring_buffer_t rb;
    sensor_features_t features;
    inference_config_t config = inference_default_config();

    if (float_ring_buffer_init(&rb, storage, 8) != 0) {
        return -1;
    }

    for (size_t i = 0; i < sample_count; i++) {
        if (float_ring_buffer_push(&rb, samples[i]) != 0) {
            return -1;
        }
    }

    if (sensor_compute_features(&rb, &features) != 0) {
        return -1;
    }

    inference_result_t result = run_inference_with_config(&features, config);

    printf("[%s]\n", label);
    sensor_print_features(&features);
    printf("score=%.2f level=%s thresholds=(%.2f/%.2f)\n\n", result.score,
           inference_level_to_string(result.level), config.warning_threshold,
           config.alert_threshold);
    return 0;
}

int main(void)
{
    const float normal_case[] = {40.0f, 40.1f, 39.9f, 40.0f, 40.2f, 40.1f, 40.0f, 39.8f};
    const float warning_case[] = {40.0f, 40.3f, 40.2f, 40.5f, 41.0f, 41.3f, 41.1f, 40.9f};
    const float alert_case[] = {39.8f, 40.0f, 40.2f, 42.5f, 43.1f, 44.0f, 44.6f, 45.2f};

    if (run_case(normal_case, 8, "normal_case") != 0) {
        fprintf(stderr, "normal_case failed\n");
        return 1;
    }

    if (run_case(warning_case, 8, "warning_case") != 0) {
        fprintf(stderr, "warning_case failed\n");
        return 1;
    }

    if (run_case(alert_case, 8, "alert_case") != 0) {
        fprintf(stderr, "alert_case failed\n");
        return 1;
    }

    return 0;
}
