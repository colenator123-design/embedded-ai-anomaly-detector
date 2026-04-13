CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = lightweight_inference_demo

.PHONY: all clean run

all: $(TARGET)

$(TARGET): main.c ../01-sensor-pipeline/ring_buffer.c ../01-sensor-pipeline/sensor_pipeline.c inference.c
	$(CC) $(CFLAGS) -I../01-sensor-pipeline -o $@ main.c ../01-sensor-pipeline/ring_buffer.c ../01-sensor-pipeline/sensor_pipeline.c inference.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
