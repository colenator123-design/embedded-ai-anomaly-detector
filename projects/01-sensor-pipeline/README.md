# 01 Sensor Pipeline

This project is the first step of an embedded AI anomaly detection demo.

## What It Does

- simulates a stream of sensor values
- stores values in a fixed-size float ring buffer
- computes simple features from the buffered window

## Why This Matters

Before doing inference, embedded systems often need:

- bounded buffering
- fixed-size windows
- feature extraction from recent samples

## Build

```sh
cd /Users/caita/embedded-ai-anomaly-detector/projects/01-sensor-pipeline
make
```

## Run

```sh
./sensor_pipeline_demo
```

## Files

- `ring_buffer.h` / `ring_buffer.c`: fixed-size float buffer
- `sensor_pipeline.h` / `sensor_pipeline.c`: feature extraction
- `main.c`: demo with simulated sensor samples
