#include "include/memory_paging.h"

struct PAGING_T table_entry[1024];
uint32_t paging_ptr;

void init_paging(){
  unsigned int kernel_flags = 0x01 | 0x02 | 0x80; //read write enable, supervisor, with 4 mib initizile  
  unsigned int user_flags = 0x01 | 0x02 | 0x04 | 0x80; //user flags 
  map_page(0xB8000,kernel_flags,&table_entry[0]); // set identifier address: VGA 
  map_page(0x00400000,kernel_flags,&table_entry[1]); // set identifier address: Kernel 

  for (uint32_t idx = 2;idx < 1024;idx++) {
    uint32_t physical_addr = idx * 0x400000;
    map_page(physical_addr,user_flags,&table_entry[idx]);
  }
  paging_ptr = (uint32_t) &table_entry;

  load_paging(paging_ptr);
};

void map_page(uint32_t physical_addr,uint8_t flags,struct PAGING_T *page){
  page->p    = flags & 0x1;
  page->r_w  = (flags & 0x2) >> 1;
  page->u_s  = (flags & 0x4) >> 2;
  page->pwt  = (flags & 0x8) >> 3; 
  page->pcd  = (flags & 0x10) >> 4;
  page->ps_1 = (flags & 0x80) >> 7; 
  
  page-> lower_addr = (physical_addr >> 22) & 0xFF;
  page -> upper_addr = (physical_addr >> 30) & 0x03;
  

}

