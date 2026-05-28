#include "include/gdt.h"
#include "include/terminal.h"

struct GDT target[5];
struct GDT_PTR gdt_pointer;

void initialize_gdt()
{
  
  set_gdt_entry( &target[0],  0 ,0x00,    0x00, 0x0); // NULL 
  set_gdt_entry( &target[1],  0, 0xFFFFF, 0x9A, 0xC); // Kernel code segments 
  set_gdt_entry( &target[2],  0, 0xFFFFF, 0x92, 0xC); // kernel data segments 
  set_gdt_entry( &target[3],  0, 0xFFFFF, 0xFA, 0xC); // user code segments 
  set_gdt_entry( &target[4],  0, 0xFFFFF, 0xF2, 0xC); // user data segments 
  //load the gdt
  //
  gdt_pointer.limit = (sizeof(struct GDT) * 5) - 1;
  gdt_pointer.base  = (uint32_t)&target;
  
  setGdt(gdt_pointer.limit, gdt_pointer.base);
  
}


void set_gdt_entry(struct GDT *target, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    if (limit > 0xFFFFF) {
        // terminal_writestring("[GDT] Error: Limit exceeds 20 bits\n");
        return;
    }

    target->base_low    = (base & 0xFFFF);        // Lower 16 bits
    target->base_middle = (base >> 16) & 0xFF;    // Next 8 bits
    target->base_high   = (base >> 24) & 0xFF;    // Upper 8 bits

    // Map limit segments
    target->limit_low   = (limit & 0xFFFF);       // Lower 16 bits
    
    // Combine upper 4 bits of limit (bits 16-19) with your 4-bit flags (bits 4-7)
    target->limit_high_flags = (limit >> 16) & 0x0F;
    target->limit_high_flags |= (flags << 4);   // Set page granularity / size bits
    target->access_byte = access;
}
