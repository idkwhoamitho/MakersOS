
global irq_keyboard_handler
extern c_keyboard_handler 

irq_keyboard_handler:
  pushad  

  call c_keyboard_handler

  popad   
  iret 




