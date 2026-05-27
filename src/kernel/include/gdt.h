#ifndef GDT_H
#define GDT_H 
#include <stddef.h>
#include <stdint.h>

struct GDT{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access_byte;
  uint8_t limit_high_flags;
  uint8_t base_high; 
}__attribute__((packed));

struct GDT_PTR{
  uint16_t limit;
  uint32_t base;
}__attribute__((packed));


extern struct GDT target[5];


void initialize_gdt();
void set_gdt_entry(struct GDT *target, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
extern void setGdt(uint16_t limit, uint32_t gdt_base_address);


#endif 
