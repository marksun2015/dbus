cc=gcc
CFLAGS=-g -c -Wall -m64 -Ofast -flto -march=native -funroll-loops -DLINUX `pkg-config --cflags --libs dbus-1`
#CFLAGS=-g -c -Wall -mthumb -O3 -march=armv7-a -mcpu=cortex-a9 -mtune=cortex-a9 -mfpu=neon -mvectorize-with-neon-quad -mfloat-abi=hard -DLINUX

LIBS += $(shell pkg-config --cflags dbus-1) 
LIBS += $(shell pkg-config --cflags glib-2.0)
LIBS += $(shell pkg-config --libs dbus-1) 
LIBS += $(shell pkg-config --libs glib-2.0)

SRCS=dbus-example.c
OBJS=$(SRCS:.c=.o)
TARGET=dbus-example

all: $(SRCS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fr $(OBJS) $(TARGET)
