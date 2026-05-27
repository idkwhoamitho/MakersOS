#include "include/terminal.h"
#include "include/gdt.h"
void kernel_main(void){
    terminal_initialize();
    terminal_writestring("[GDT] Loading the GDT...\n");
    initialize_gdt();
    terminal_writestring("[GDT] Initialize complete\n");
}
