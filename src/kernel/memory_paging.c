#include "include/memory_paging.h"

struct PAGING_T table_entry[1024];
uint32_t paging_ptr;

void init_memory_pagin(){
  paging_ptr = (uint32_t)&table_entry;
  unsigned int kernel_flags = 0x01 | 0x02 | 0x80; //read write enable, supervisor, with 4 mib initizile  
  unsigned int user_flags = 0x01 | 0x02 | 0x04 | 0x80; //kernel flags 
  map_page(0x0000,0x0C0000,kernel_flags); // set identifier address: VGA & Kernel 

  for (int idx = 2;idx < 1024;idx++) {
    void* virtual_addr = 0xC00000 + (0x400000 * idx); 
    void* phys_addr = idx * 0x400000 
    map_page(phys_addr,virtual_addr, user_flags);
  }


  load_paging();
};

void map_page(void* phys_addr,void* virtual_addr, unsigned int flag){
  
  unisgned long pd_index = (unsigned long) virtual_addr >> 22;


  table_entry[pd_index] = ((unsigned long)phys_addr) | (flags & 0xFFF) | 0x81 //present bit 
}

