#include "linux/kernel.h"
#include "linux/unistd.h"
#include "linux/uaccess.h"
#include "linux/slab.h"
#include "dm510_msgbox_common.h"


asmlinkage
int sys_dm510_msgbox_get( char* buffer, int length ) {
  unsigned long flags;
  int mlength = -1;

    if (access_ok(buffer, length) && top != NULL) {

    msg_t* msg = top;
    mlength = msg->length;
    if (mlength > length){
            mlength = length;
   }

    top = msg->previous;

    local_irq_save(flags);
    /* copy message */
    if (copy_to_user(buffer, msg->message, mlength) != 0) {
            // Copying failed
            printk("Failed to copy message to user space\n");
            mlength = -EFAULT;
        }

    /* free memory */
    kfree(msg->message);
    kfree(msg);

    local_irq_restore(flags);

    if (mlength >= 0){
            printk("Message length retrieved: %d\n", mlength);
    }

    } else {
        // No message or bad memory access
        mlength = -1;
    }

    return mlength;
}
