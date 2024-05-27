#include "linux/kernel.h"
#include "linux/unistd.h"
#include "linux/slab.h"
#include "linux/uaccess.h"
#include "dm510_msgbox_common.h"

msg_t *bottom = NULL;
msg_t *top = NULL;

asmlinkage
int sys_dm510_msgbox_put( char *buffer, int length ) {
  if(length<=0) {
	printk("Invalid length of input! \n");
	return -EINVAL;
  }
  unsigned long flags;

  if(access_ok(buffer, length)){

  local_irq_save(flags);
  
  msg_t* msg = kmalloc(sizeof(msg_t), GFP_KERNEL);
  if (!msg) {
        local_irq_restore(flags);
        printk("Memory allocation failure. \n");
        return -ENOMEM; 
  }
  msg->previous = NULL;
  msg->length = length;
  msg->message = kmalloc(length, GFP_KERNEL);
  if (!msg->message) {
        kfree(msg); 
        local_irq_restore(flags);
        printk("Memory allocation failure. \n");
	return -ENOMEM; 
  }
  copy_from_user(msg->message, buffer, length);
  
  local_irq_restore(flags);

  if (bottom == NULL) {
    bottom = msg;
    top = msg;
  } else {
    /* not empty stack */
    msg->previous = top;
    top = msg;
  }

  printk("Message put: %s\n", msg->message);

  return 0;
  }
  else {
     printk("Bad memory access. \n");
     return -1;
  }
}
