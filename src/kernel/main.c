#include "include/terminal.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/keyboard.h"
#include "include/pic.h"

void kernel_main(void){
    terminal_initialize();
    terminal_writestring("[GDT] Loading the GDT...\n");
    initialize_gdt();
    terminal_writestring("[PIC] remapping...\n");
    pic_remap();
    terminal_writestring("[PIC] Successfully remapping PIC\n");
    terminal_writestring("[GDT] Initialize complete\n");
    terminal_writestring("[IDT] Initialize IDT\n");
    init_idt();
    terminal_writestring("[IDT] Successfully Initialize\n");
    terminal_writestring("[KEYBOARD] initializing keyboard");
    
    init_keyboard();
    
    while (true) {
    }
    

}
