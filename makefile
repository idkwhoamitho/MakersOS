# Toolchain Configurations
AS = nasm
CC = gcc
LD = gcc
EMU = qemu-system-i386

# Compilation Flags
ASFLAGS = -f elf32
CFLAGS  = -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fno-pic -Isrc/kernel/include
LDFLAGS = -m32 -T linker.ld -ffreestanding -O2 -nostdlib -no-pie -lgcc

# Project Folders
BUILD_DIR = build
BIN_DIR = bin
ISO_DIR = $(BUILD_DIR)/iso
SRC_DIR = src

# Target Outputs
TARGET_ELF = $(BIN_DIR)/mykernel.elf
TARGET_ISO = $(BIN_DIR)/mykernel.iso

# ====================================================================
# MODULAR SYSTEM: Dynamically find all source files in any subdirectory
# ====================================================================
# Find all C source files recursively inside src/
SRCS_C := $(shell find $(SRC_DIR) -name '*.c')
# Find all Assembly source files recursively inside src/
SRCS_S := $(shell find $(SRC_DIR) -name '*.s')

# Transform source file paths into corresponding object paths in build/
# E.g., src/kernel/main.c -> build/src/kernel/main.o
OBJ_C := $(SRCS_C:%.c=$(BUILD_DIR)/%.o)
OBJ_S := $(SRCS_S:%.s=$(BUILD_DIR)/%.o)
ALL_OBJS := $(OBJ_S) $(OBJ_C)

.PHONY: all clean run

# Default target
all: $(TARGET_ISO)

# Rule to build a genuine GRUB bootable ISO
$(TARGET_ISO): $(TARGET_ELF) grub.cfg
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(ISO_DIR)/boot/grub
	
	# Copy files into the standard GRUB layout
	cp $(TARGET_ELF) $(ISO_DIR)/boot/mykernel.elf
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	
	# Verify and generate the ISO
	grub-file --is-x86-multiboot $(ISO_DIR)/boot/mykernel.elf
	grub-mkrescue -o $(TARGET_ISO) $(ISO_DIR)

# Rule to link the ELF executable
$(TARGET_ELF): $(ALL_OBJS)
	@mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $(TARGET_ELF) $(ALL_OBJS)

# Pattern Rule for compiling C files from ANY subdirectory
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern Rule for assembling .s files from ANY subdirectory
$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

# Boot via native QEMU CD-ROM device emulator
run: $(TARGET_ISO)
	$(EMU) -cdrom $(TARGET_ISO)

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) 
