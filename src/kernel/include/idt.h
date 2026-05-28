#ifndef IDT_H 
#define IDT_H 

#include <stdint.h> 
#include <stdbool.h> 

#define IDT_MAX_DESCRIPTOR 256

typedef struct IDT_ENTRY{
  uint16_t isr_low;
  uint16_t kernel_cs;
  uint8_t reserves;
  uint8_t attributes;
  uint16_t isr_high;
    
}__attribute__((packed))idt_entry_t; 
typedef struct IDT_PTR{
  uint16_t limit;
  uint64_t base;
}__attribute__((packed))idt_ptr_t;


__attribute__((aligned(0x10)))
static idt_entry_t idt_entry[IDT_MAX_DESCRIPTOR];
static idt_ptr_t idtr;
static bool vectors[IDT_MAX_DESCRIPTOR];
extern void* isr_stub_table[];


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t  flags);
void init_idt();



#endif // !IDT_H 
 



