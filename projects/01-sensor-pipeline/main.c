#include <stdio.h>

#include "ring_buffer.h"
#include "sensor_pipeline.h"

int main(void)
{
    float storage[8];
    float_ring_buffer_t rb;
    sensor_features_t features;

    if (float_ring_buffer_init(&rb, storage, 8) != 0) {
        fprintf(stderr, "float_ring_buffer_init failed\n");
        return 1;
    }

    const float samples[] = {40.2f, 40.4f, 40.1f, 39.9f, 40.0f, 41.8f, 42.6f, 43.1f};
    size_t sample_count = sizeof(samples) / sizeof(samples[0]);

    for (size_t i = 0; i < sample_count; i++) {
        if (float_ring_buffer_push(&rb, samples[i]) != 0) {
            fprintf(stderr, "push failed at sample %zu\n", i);
            return 1;
        }
        printf("sample %.2f buffered, size=%zu\n", samples[i], float_ring_buffer_size(&rb));
    }

    if (sensor_compute_features(&rb, &features) != 0) {
        fprintf(stderr, "sensor_compute_features failed\n");
        return 1;
    }

    sensor_print_features(&features);
    return 0;
}
