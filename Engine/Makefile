# Compiler and flags
CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lglfw -lGL -lGLEW -lm  # Add GLFW and OpenGL dependencies

# Target executable
TARGET = main

# Source files
SRCS = main.cpp src/engine.cpp src/check_input.cpp src/window/window_init.cpp src/renderer/renderer.cpp src/glew/glew_init.cpp

# Object files (Fix incorrect replacement pattern)
OBJS = $(SRCS:.cpp=.o)

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files into object files (Fix incorrect pattern)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
