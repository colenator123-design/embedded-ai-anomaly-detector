# 03 Alert Engine

This project adds a simple firmware-style alert engine on top of lightweight
inference.

## What It Does

- receives `NORMAL`, `WARNING`, or `ALERT` inference results
- keeps internal system state
- requires repeated warning conditions before escalating
- holds an alert cooldown for a few ticks after an alert

## Why This Matters

Real firmware usually does not map one inference output directly to one device
action. It often needs:

- state tracking
- debounce / hysteresis behavior
- cooldown windows
- system-level decision logic

## Build

```sh
cd /Users/caita/embedded-ai-anomaly-detector/projects/03-alert-engine
make
```

## Run

```sh
./alert_engine_demo
```

## Files

- `alert_engine.h` / `alert_engine.c`: state and transition logic
- `main.c`: demo that feeds multiple sensor windows through inference and alert handling
