#include "include/idt.h"
#include "include/keyboard.h"
static bool vectors[IDT_MAX_DESCRIPTOR];
idt_entry_t  idt_entry[IDT_MAX_DESCRIPTOR];
idt_ptr_t idtr;
extern void* isr_stub_table[];


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
  idt_entry_t* descriptor = &idt_entry[vector];

  descriptor -> isr_low    = (uint32_t) isr & 0xFFFF;
  descriptor -> kernel_cs  = 0x08; 
  descriptor -> attributes = flags;
  descriptor -> isr_high   = (uint32_t) isr >> 16;
  descriptor -> reserves    = 0; 
}

void init_idt(){
  idtr.base = (uintptr_t) &idt_entry[0];
  idtr.limit = (uint16_t) sizeof(idt_entry_t) * IDT_MAX_DESCRIPTOR - 1;
  
  
  for (uint8_t vector = 0;vector < 32;vector++) {
      idt_set_descriptor(vector,isr_stub_table[vector],0x8E);
      vectors[vector] = true; 
  
  }
  //register the keyboard handler 
  idt_set_descriptor(0x21, irq_keyboard_handler,0x8E);
  vectors[0x21] = true;

  __asm__ volatile("lidt %0"::"m"(idtr)); 
  __asm__ volatile("sti");
}



