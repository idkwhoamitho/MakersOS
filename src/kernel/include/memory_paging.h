#ifndef MEMORY_PAGING
#define MEMORY_PAGING

#include <stdint.h> 

typedef struct PAGING_T{
  uint32_t p  : 1;
  uint32_t r_w: 1;
  uint32_t u_s: 1;
  uint32_t pwt: 1;
  uint32_t pcd: 1;
  uint32_t A  : 1;
  uint32_t D  : 1;
  uint32_t ps_1: 1;
  uint32_t g  : 1;
  unsigned int avl: 2;
  uint32_t pat:  1;
  uint8_t upper_addr;
  uint32_t rsdv: 1;
  uint8_t lower_addr;
}__attribute__((packed)) PAGING_T; 

__attribute__((aligned(4096)))
extern struct PAGING_T table_entry[1024];
extern uint32_t paging_ptr; 

extern void load_paging(uint32_t ptr);
void init_paging(void);

void *get_addr(void* virtual_addr);
void map_page(uint32_t physical_addr,uint8_t flags,struct PAGING_T *page);




#endif 
