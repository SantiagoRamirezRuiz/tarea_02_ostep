#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
int rc = fork();
 if (rc>0) {
// parent goes down this path (main) 
sleep(1);
printf("goodbye\n");
} else {
// child (new process)
printf("Hello\n");
}
return 0;
}
