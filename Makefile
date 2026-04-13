SUBDIRS = projects/01-sensor-pipeline projects/02-lightweight-inference projects/03-alert-engine

.PHONY: all clean

all:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

clean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
