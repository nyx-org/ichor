BUILD_DIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=$(BUILD_DIR)/%.c.o)
TARGET = $(BUILD_DIR)/libichor.a
CC = clang
CFLAGS = -ffreestanding -fno-stack-protector -nostdlib -Wall -Wextra -Werror -Iinclude

MKCWD = mkdir -p $(@D)

$(BUILD_DIR)/%.c.o: src/%.c
	@$(MKCWD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	@$(MKCWD)
	$(AR) rcs $@ $^


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
