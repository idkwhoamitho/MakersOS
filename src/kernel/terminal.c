#include "include/terminal.h"

size_t terminal_row;
size_t terminal_column; // Make sure this matches the spelling in terminal.h!
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

size_t strlen(const char* str){
    size_t len  = 0;
    while(str[len])
        len++;
    return len;
}


/*
    The data structure of the VGA is 
    16-BIT VGA CHARACTER ENTRY
 ┌───────────────────────────────────────┬───────────────────────────────────────┐
 │        UPPER BYTE (Bits 8-15)         │         LOWER BYTE (Bits 0-7)         │
 ├───────────────────┬───────────────────┼───────────────────────────────────────┤
 │  Background Color │  Foreground Color │           ASCII Character             │
 │    (4 Bits)       │    (4 Bits)       │              (8 Bits)                 │
 └───────────────────┴───────────────────┴───────────────────────────────────────┘
  15               12 11                8 7                                     0

    This fucntion below is an packed bits function packing the whole Memory data into format above
    Like example
    Blue: 0001      'A': 01000001
    Gray: 0111
    First pack the color
    fg|(bg<<4) : shift the bg 4 bits so its sit on the upper bytes 0001 0000
    then combine it to the using bitwse OR so the whole upper 8 bytes is 0001 0111
    then do the same to packed it with the lower bytes(Ascii)

*/


/*
    Initialize the terminal, 
    for searching the index we use 
        index = (col * Height) + Row
    
*/
/*
void terminal_scroll(void){
  
  for(size_t y = 0; y < VGA_WIDTH; y++){
    for(size_t x = 0; x < VGA_HEIGHT; x++){
      
      const size_t current = y * VGA_WIDTH + x;
      const size_t next_index = (y+1) * VGA_WIDTH + x;
      
      terminal_buffer[current] = terminal_buffer[next_index];
      
      }
  }

*/
    

void terminal_scroll(void){
  // VGA_HEIGHT is to short so i kept it to 80 
  for(size_t x = 0;x < 80;x++){
    for(size_t y = 0; y < VGA_WIDTH;y++){
      const size_t current = y * VGA_WIDTH + x;
      const size_t next_index = (y+1) * VGA_WIDTH + x;
      
       terminal_buffer[current] = terminal_buffer[next_index];

    }
  }
    const size_t last_row = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for(int y = 0; y < VGA_WIDTH; y++){
      terminal_buffer[last_row + y] = vga_entry(' ',terminal_color);

    }
}


void terminal_initialize(void){
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY,VGA_COLOR_BLACK);

    for(int y = 0; y < VGA_WIDTH;y++){
        for(int x = 0; x < VGA_HEIGHT;x++){
            const size_t index = y * VGA_WIDTH + x; 
            terminal_buffer[index]= vga_entry(' ',terminal_color);
        }
    }

}


void terminal_setcolor(uint8_t color){
    terminal_color = color;
}

// Putting entry
//
void terminal_putentryat(char c, uint8_t color,size_t x,size_t y){
    
	  const size_t index = y * VGA_WIDTH + x; 
    terminal_buffer[index]= vga_entry(c,color);
  
}

// Putting char and checking the if its overflow the screen
void terminal_putchar(char c){
    //terminal_putentryat(c,terminal_color,terminal_column,terminal_row);
	if(c == '\n'){
		terminal_row++;
		terminal_column=0;
	}
  
  else{
    terminal_putentryat(c,terminal_color,terminal_column,terminal_row);
    terminal_column++;
  }
  
  
  if(terminal_column >= VGA_WIDTH){
    terminal_column = 0;
    terminal_row++;
  }
  if(terminal_row >= VGA_HEIGHT){
    terminal_scroll();
    terminal_row = VGA_HEIGHT - 1;
  }
  /*
  else{
    terminal_putentryat(c,terminal_color,terminal_column,terminal_row);
  }
  */
  
  //terminal_putentryat(c,terminal_color,terminal_column,terminal_row);
}

void terminal_write(const char* data, size_t size){
    for(size_t i = 0; i < size; i++){
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data){
    terminal_write(data,strlen(data));
}
