# Compiler and flags
CC = g++-14
#CC = gcc for bella
#CC = g++-14 for hayden

CFLAGS = -Wall -g  -fopenmp
#for debugging add  -fsanitize=address

# Target executable
TARGET = main

# Source files
SRCS = main.c initialise_bodies.c update_positions.c print_world.c compute_force.c update_velocity.c octree.c barnes_calc.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
