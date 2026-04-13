#ifndef SENSOR_PIPELINE_H
#define SENSOR_PIPELINE_H

#include <stddef.h>

#include "ring_buffer.h"

typedef struct {
    float min_value;
    float max_value;
    float mean_value;
    float latest_value;
} sensor_features_t;

int sensor_compute_features(const float_ring_buffer_t *rb, sensor_features_t *features);
void sensor_print_features(const sensor_features_t *features);

#endif
