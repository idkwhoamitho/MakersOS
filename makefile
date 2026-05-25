# Toolchain Configurations
AS = nasm
CC = i686-elf-gcc
LD = i686-elf-gcc
EMU = qemu-system-i386

# Compilation Flags
ASFLAGS = -f elf32
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Isrc/kernel/include
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

# Output Folders
BUILD_DIR = build
BIN_DIR = bin

# File Tracking
BOOT_SRC = src/Boot/boot.s
OBJ = $(BUILD_DIR)/boot.o $(BUILD_DIR)/main.o $(BUILD_DIR)/temporary_terminal.o

TARGET_ELF = $(BIN_DIR)/mykernel.elf

.PHONY: all clean run

# Default target
all: $(TARGET_ELF)

# Rule to link the ELF executable
$(TARGET_ELF): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $(TARGET_ELF) $(OBJ)

# Rule to assemble boot.s
$(BUILD_DIR)/boot.o: src/Boot/boot.s
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Rule to compile main.c
$(BUILD_DIR)/main.o: src/kernel/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile terminal.c
$(BUILD_DIR)/temporary_terminal.o: src/kernel/terminal.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Trigger Native QEMU Multiboot Bootloader Emulation
run: $(TARGET_ELF)
	$(EMU) -kernel $(TARGET_ELF)

# Clean out old build dependencies across both environments
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)