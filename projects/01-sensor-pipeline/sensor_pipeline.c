#include "sensor_pipeline.h"

#include <stdio.h>

int sensor_compute_features(const float_ring_buffer_t *rb, sensor_features_t *features)
{
    if (rb == 0 || features == 0 || rb->count == 0) {
        return -1;
    }

    float min_value = rb->buffer[rb->tail];
    float max_value = rb->buffer[rb->tail];
    float sum = 0.0f;

    for (size_t i = 0; i < rb->count; i++) {
        size_t index = (rb->tail + i) % rb->capacity;
        float value = rb->buffer[index];

        if (value < min_value) {
            min_value = value;
        }
        if (value > max_value) {
            max_value = value;
        }
        sum += value;
    }

    size_t latest_index = (rb->head + rb->capacity - 1) % rb->capacity;

    features->min_value = min_value;
    features->max_value = max_value;
    features->mean_value = sum / (float)rb->count;
    features->latest_value = rb->buffer[latest_index];
    return 0;
}

void sensor_print_features(const sensor_features_t *features)
{
    if (features == 0) {
        return;
    }

    printf("min=%.2f max=%.2f mean=%.2f latest=%.2f\n", features->min_value,
           features->max_value, features->mean_value, features->latest_value);
}
