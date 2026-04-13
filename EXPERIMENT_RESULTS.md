# Experiment Results

This file records a simple deterministic experiment for the embedded AI anomaly
detector pipeline.

## Experiment Goal

Show that the pipeline can:

1. buffer sensor samples
2. extract bounded-window features
3. compute a lightweight anomaly score
4. convert that score into `NORMAL`, `WARNING`, or `ALERT`
5. drive a higher-level alert state machine

## Inference Configuration

- `spread_weight = 0.6`
- `drift_weight = 0.4`
- `warning_threshold = 0.8`
- `alert_threshold = 2.0`

## Feature and Inference Cases

| Case | Min | Max | Mean | Latest | Score | Level |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| normal_case | 39.80 | 40.20 | 40.01 | 39.80 | 0.33 | NORMAL |
| warning_case | 40.00 | 41.30 | 40.66 | 40.90 | 0.88 | WARNING |
| alert_case | 39.80 | 45.20 | 42.43 | 45.20 | 4.35 | ALERT |

## Alert Engine Timeline

| Step | Score | Inference | System State | Cooldown |
| --- | ---: | --- | --- | ---: |
| 1 | 0.18 | NORMAL | NORMAL | 0 |
| 2 | 0.83 | WARNING | NORMAL | 0 |
| 3 | 1.07 | WARNING | WARNING | 0 |
| 4 | 4.01 | ALERT | ALERT | 2 |
| 5 | 0.25 | NORMAL | ALERT | 1 |
| 6 | 0.23 | NORMAL | NORMAL | 0 |

## Interpretation

- The feature extractor separates stable and unstable windows.
- The lightweight score is sufficient to distinguish normal, warning, and alert
  conditions in this small deterministic demo.
- The alert engine adds system behavior on top of raw inference, including
  escalation and cooldown instead of reacting to every single sample window.

## Current Limitations

- The inference stage is lightweight and rule-based, not a trained neural model.
- The sensor stream is simulated and deterministic.
- The project is a prototype for edge or firmware integration, not a
  production-ready deployment.
