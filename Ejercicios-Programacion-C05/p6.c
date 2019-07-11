#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main() {
int rc = fork();
int status;
 if (rc>0) {
// parent goes down this path (main)
waitpid(rc, &status, 0);
printf("goodbye\n");
} else {
// child (new process)
wait(NULL);
printf("Hello\n");
}
return 0;
}
