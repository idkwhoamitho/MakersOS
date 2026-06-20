#ifndef KEYBOARD_H 
#define KEYBOARD_H 

 
extern const char keyboard_table[128];



extern void irq_keyboard_handler();

void init_keyboard();
void c_keyboard_handler();



#endif // !KEYBOARD_H 


