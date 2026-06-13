#include "include/pic.h"


void pic_remap() {
    // ICW1 - Start initialization in cascade mode
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // ICW2 - Vector Offsets (Crucial Part!)
    outb(0x21, 0x20); // Master PIC vectors start at 0x20 (32)
    outb(0xA1, 0x28); // Slave PIC vectors start at 0x28 (40)

    // ICW3 - Tell Master and Slave how they connect
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // ICW4 - Give environment details (8086 mode)
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Clear masks (or handle masks separately)
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
}

