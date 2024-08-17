# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := assembler

BUILD_DIR := ./build
SRC_DIRS := ./

CFLAGS = -Wall -pedantic -ansi

# Find all the C files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./hello.c turns into ./build/./hello.c.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# About .PHONY see https://stackoverflow.com/a/2145605/12056841
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: cleanwithoutputs
cleanwithoutputs:
	rm $(SRC_DIRS)example_inputs/*.ob & \
	rm $(SRC_DIRS)example_inputs/*.am & \
	rm $(SRC_DIRS)example_inputs/*.ent & \
	rm $(SRC_DIRS)example_inputs/*.ext & \
	make clean