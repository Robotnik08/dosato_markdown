# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wno-format

# Include directories
INCLUDES = -I./dosato_source -I./

# Linker flags
LDFLAGS_WINDOWS = -L./dosato_source -llibdosato -L./src/lib -lmingw32
LDFLAGS_LINUX = -L./dosato_source -ldosato -L./src/lib -lm -Wno-format -fPIC

# Source files
SRCS = main.c $(wildcard src/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Target
TARGET = markdown

# Detect OS
ifeq ($(OS),Windows_NT)
	LDFLAGS = $(LDFLAGS_WINDOWS)
	RM = del
	TARGET := $(TARGET).dll
else
	LDFLAGS = $(LDFLAGS_LINUX)
	RM = rm -f
	TARGET := $(TARGET).so
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -shared -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -fPIC -shared -Wno-format -lm

clean:
	$(RM) $(TARGET) *.o
