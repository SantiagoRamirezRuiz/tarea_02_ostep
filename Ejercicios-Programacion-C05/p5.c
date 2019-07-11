#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
int rc = fork();
 if (rc>0) {
// parent goes down this path (main)
wait(NULL);
printf("goodbye\n");
} else {
// child (new process)
wait(NULL);
printf("Hello\n");
}
return 0;
}
