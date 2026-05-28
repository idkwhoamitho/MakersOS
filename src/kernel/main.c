#include "include/terminal.h"
#include "include/gdt.h"
#include "include/idt.h"

void kernel_main(void){
    terminal_initialize();
    terminal_writestring("[GDT] Loading the GDT...\n");
    initialize_gdt();
    terminal_writestring("[GDT] Initialize complete\n");
    terminal_writestring("[IDT] Initialize IDT\n");
    init_idt();
    terminal_writestring("[IDT] Successfully Initialize\n");
}
