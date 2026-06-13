#include "include/keyboard.h"
#include "include/terminal.h"
#include "include/util.h"


void init_keyboard(){
  outb(0x21, inb(0x21) & ~(1 << 1));
  terminal_writestring("[KEYBOARD] flushing...\n");
  while (inb(0x64) & 0x01) {
        inb(0x60); // Read and drop the data byte
  }
  terminal_writestring("[KEYBOARD] flushing complete...\n");
  __asm__ volatile("sti");
}


void c_keyboard_handler(){
  uint8_t scancode = inb(0x60);
  terminal_writestring("\n[KEYBOARD]PRESSING..\n");
  if(scancode == 0x1E){
    terminal_putchar('A');
  }
 
  outb(0x20,0x20);
}  
