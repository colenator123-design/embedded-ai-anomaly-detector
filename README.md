# Embedded AI Anomaly Detector

This project is a firmware-oriented AI demo that simulates an embedded device
collecting sensor data, extracting simple features, and running lightweight
anomaly detection logic.

## Goal

Bridge firmware-style data flow with AI-style inference:

- sensor stream input
- fixed-size buffering
- feature extraction
- lightweight anomaly scoring
- alert output

## Intended Story

This project is designed to answer a practical engineering question:

How can AI be introduced into an embedded or firmware-like system without
turning the whole project into a pure ML notebook?

## Planned Architecture

```mermaid
flowchart LR
    A[Sensor Stream] --> B[Ring Buffer]
    B --> C[Feature Extraction]
    C --> D[Lightweight Inference]
    D --> E[Normal / Warning / Alert]
```

## Current Architecture

```mermaid
flowchart LR
    A[01 Sensor Pipeline] --> B[02 Lightweight Inference]
    B --> C[03 Alert Engine]
    C --> D[System Decision Output]
```

## Roadmap

1. `01-sensor-pipeline`
2. `02-lightweight-inference`
3. `03-alert-engine`

## Why This Matters

This kind of demo can connect:

- firmware thinking
- embedded data flow
- predictive maintenance ideas
- edge AI deployment concepts

## What Exists Today

### 01. Sensor Pipeline

Path:

- `projects/01-sensor-pipeline`

Focus:

- bounded buffering
- fixed-size sample windows
- feature extraction from recent sensor data

### 02. Lightweight Inference

Path:

- `projects/02-lightweight-inference`

Focus:

- anomaly scoring
- configurable thresholds
- `NORMAL / WARNING / ALERT` mapping

### 03. Alert Engine

Path:

- `projects/03-alert-engine`

Focus:

- firmware-style decision logic
- cooldown behavior
- state transition handling

## Experiment Snapshot

See:

- `EXPERIMENT_RESULTS.md`

Key outcomes:

- normal sensor windows stay below the warning threshold
- moderate drift/spread can be promoted to `WARNING`
- large excursions trigger `ALERT`
- the alert engine prevents immediate de-escalation through cooldown logic
