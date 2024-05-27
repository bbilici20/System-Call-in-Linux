#ifndef DM510_MSGBOX_COMMON_H
#define DM510_MSGBOX_COMMON_H

#include "linux/kernel.h"
#include "linux/unistd.h"

typedef struct _msg_t msg_t;

struct _msg_t {
    msg_t* previous;
    int length;
    char* message;
};

extern msg_t *bottom;
extern msg_t *top;

#endif
