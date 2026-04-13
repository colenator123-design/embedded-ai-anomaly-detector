CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = sensor_pipeline_demo

.PHONY: all clean run

all: $(TARGET)

$(TARGET): main.c ring_buffer.c sensor_pipeline.c
	$(CC) $(CFLAGS) -o $@ main.c ring_buffer.c sensor_pipeline.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
