#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "arch/x86/include/generated/uapi/asm/unistd_64.h"

int main(int argc, char** argv) {
  char *in = "This is a stupid message.";
  char msg[50];
  int msglen;

  printf("Calling dm510_msgbox_put... \n");
  /* Send a message containing 'in' */
  syscall(__NR_dm510_msgbox_put, in, strlen(in)+1);

  printf("Calling dm510_msgbox_get... \n");
  /* Read a message */
  msglen = syscall(__NR_dm510_msgbox_get, msg, 50);

  char *in2 = "This is another message.";
  char msg2[50];
  int msglen2;

  printf("Calling dm510_msgbox_put... \n");
  /* Send a message containing 'in2' but with invalid strlen */
  syscall(__NR_dm510_msgbox_put, in2, -1);

  printf("Calling dm510_msgbox_get... \n");
  /* Read a message */
  msglen = syscall(__NR_dm510_msgbox_get, msg2, 50);

  char *in3 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer egestas justo at scelerisque tempus. Ut bibendum suscipit dictum. Praesent bibendum sit amet dui ut cursus. Donec varius risus at hendrerit consequat. Sed et molestie lectus. Quisque mauris urna, facilisis in ornare sit amet, sollicitudin a libero. Nunc vulputate nisi leo, in ultricies nunc lacinia id. Sed ante nisl, lobortis in malesuada id, gravida at leo. Etiam suscipit, urna eu fermentum aliquam, felis diam feugiat metus, at mollis tortor arcu sit amet nisi. Fusce id velit scelerisque justo finibus accumsan. Maecenas mollis tristique congue. Cras et tellus eros. Integer aliquam ut nulla sit amet sodales. Vestibulum pellentesque nunc a massa venenatis, at pellentesque mauris laoreet.";
  char msg3[50];
  int msglen3;

  printf("Calling dm510_msgbox_put... \n");
  /* Send a message containing 'in3' */
  syscall(__NR_dm510_msgbox_put, in3, strlen(in3)+1);

  printf("Calling dm510_msgbox_get... \n");
  /* Read a message but the length of the buffer is not enough*/
  msglen = syscall(__NR_dm510_msgbox_get, msg3, 50);

  /*Put multiple messages and read them*/
  char *first = "This is the first message.";
  char msg4[50];
  int msglen4;

  printf("Calling dm510_msgbox_put... \n");
  /* Send a message containing the first message of the multiple messages */
  syscall(__NR_dm510_msgbox_put, first, strlen(first)+1);

  char *second = "This is the second message.";
  char msg5[50];
  int msglen5;

  printf("Calling dm510_msgbox_put... \n");
  /* Send a message containing the second message of the multiple messages */
  syscall(__NR_dm510_msgbox_put, second, strlen(second)+1);

  printf("Calling dm510_msgbox_get... \n");
  /* Should retrieve the second message */
  msglen = syscall(__NR_dm510_msgbox_get, msg5, 50);

  printf("Calling dm510_msgbox_get... \n");
  /* Should retrieve the first message */
  msglen = syscall(__NR_dm510_msgbox_get, msg4, 50);

  return 0;
}
