#include "inference.h"

static float absolute_value(float value)
{
    return value < 0.0f ? -value : value;
}

inference_config_t inference_default_config(void)
{
    inference_config_t config;
    config.spread_weight = 0.6f;
    config.drift_weight = 0.4f;
    config.warning_threshold = 0.8f;
    config.alert_threshold = 2.0f;
    return config;
}

inference_result_t run_inference_with_config(const sensor_features_t *features,
                                             inference_config_t config)
{
    inference_result_t result;
    result.score = 0.0f;
    result.level = INFERENCE_NORMAL;

    if (features == 0) {
        result.level = INFERENCE_ALERT;
        result.score = 999.0f;
        return result;
    }

    float spread = features->max_value - features->min_value;
    float drift = absolute_value(features->latest_value - features->mean_value);

    result.score = (spread * config.spread_weight) + (drift * config.drift_weight);

    if (result.score >= config.alert_threshold) {
        result.level = INFERENCE_ALERT;
    } else if (result.score >= config.warning_threshold) {
        result.level = INFERENCE_WARNING;
    } else {
        result.level = INFERENCE_NORMAL;
    }

    return result;
}

inference_result_t run_inference(const sensor_features_t *features)
{
    return run_inference_with_config(features, inference_default_config());
}

const char *inference_level_to_string(inference_level_t level)
{
    switch (level) {
    case INFERENCE_NORMAL:
        return "NORMAL";
    case INFERENCE_WARNING:
        return "WARNING";
    case INFERENCE_ALERT:
        return "ALERT";
    }

    return "UNKNOWN";
}
