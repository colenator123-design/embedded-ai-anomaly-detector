#ifndef LIGHTWEIGHT_INFERENCE_H
#define LIGHTWEIGHT_INFERENCE_H

#include "../01-sensor-pipeline/sensor_pipeline.h"

typedef enum {
    INFERENCE_NORMAL = 0,
    INFERENCE_WARNING,
    INFERENCE_ALERT
} inference_level_t;

typedef struct {
    float spread_weight;
    float drift_weight;
    float warning_threshold;
    float alert_threshold;
} inference_config_t;

typedef struct {
    float score;
    inference_level_t level;
} inference_result_t;

inference_config_t inference_default_config(void);
inference_result_t run_inference_with_config(const sensor_features_t *features,
                                             inference_config_t config);
inference_result_t run_inference(const sensor_features_t *features);
const char *inference_level_to_string(inference_level_t level);

#endif
