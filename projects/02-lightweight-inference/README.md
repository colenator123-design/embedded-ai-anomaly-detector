# 02 Lightweight Inference

This project adds a tiny anomaly scoring stage on top of the sensor pipeline.

## What It Does

- reuses the buffered sensor window
- computes simple features
- turns those features into an anomaly score
- maps the score to `NORMAL`, `WARNING`, or `ALERT`
- supports configurable scoring weights and thresholds

## Why This Matters

This is the first step toward an embedded AI story:

- data arrives from a device
- features are extracted from a bounded buffer
- a lightweight inference step runs on top
- the system outputs an actionable state

## Build

```sh
cd /Users/caita/embedded-ai-anomaly-detector/projects/02-lightweight-inference
make
```

## Run

```sh
./lightweight_inference_demo
```

## Files

- `inference.h` / `inference.c`: scoring and classification logic
- `main.c`: demo with normal, warning, and alert sample windows
