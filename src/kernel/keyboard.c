#include "include/keyboard.h"
#include "include/terminal.h"
#include "include/util.h"

const char keyboard_table[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 0x00 - 0x09 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',/* Tab */
  'q', 'w', 'e', 'r',	/* 0x10 - 0x13 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,/* 0x1D - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 0x1E - 0x27 */
 '\'', '`',   0,/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.',	/* 0x2B - 0x34 */
  '/',   0,/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    // ... complete down to 128 indices
};

void init_keyboard(){
  outb(0x21, inb(0x21) & ~(1 << 1));
  terminal_writestring("\n[KEYBOARD] flushing...\n");
  while (inb(0x64) & 0x01) {
        inb(0x60); // Read and drop the data byte
  }
  terminal_writestring("[KEYBOARD] flushing complete...\n");
  __asm__ volatile("sti");
}


void c_keyboard_handler(){
  uint8_t scancode = inb(0x60);
  if(!(scancode& 0x80)){
    char ascii = keyboard_table[scancode];
    if(ascii != 0){
      terminal_putchar(ascii);
    }
  } 
  outb(0x20,0x20);
}  
