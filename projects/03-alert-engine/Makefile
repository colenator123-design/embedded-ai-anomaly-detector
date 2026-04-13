CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = alert_engine_demo

.PHONY: all clean run

all: $(TARGET)

$(TARGET): main.c ../01-sensor-pipeline/ring_buffer.c ../01-sensor-pipeline/sensor_pipeline.c ../02-lightweight-inference/inference.c alert_engine.c
	$(CC) $(CFLAGS) -I../01-sensor-pipeline -I../02-lightweight-inference -o $@ main.c ../01-sensor-pipeline/ring_buffer.c ../01-sensor-pipeline/sensor_pipeline.c ../02-lightweight-inference/inference.c alert_engine.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
