#ifndef SENSOR_RING_BUFFER_H
#define SENSOR_RING_BUFFER_H

#include <stddef.h>

typedef struct {
    float *buffer;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
} float_ring_buffer_t;

int float_ring_buffer_init(float_ring_buffer_t *rb, float *storage, size_t capacity);
int float_ring_buffer_push(float_ring_buffer_t *rb, float value);
int float_ring_buffer_pop(float_ring_buffer_t *rb, float *value);
int float_ring_buffer_is_empty(const float_ring_buffer_t *rb);
int float_ring_buffer_is_full(const float_ring_buffer_t *rb);
size_t float_ring_buffer_size(const float_ring_buffer_t *rb);

#endif
