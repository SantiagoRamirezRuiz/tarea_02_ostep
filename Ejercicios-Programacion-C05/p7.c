#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int rc = fork();

    if (rc == 0) // child process
    {
        close(STDOUT_FILENO);
        printf("Funciono!\n");
    }

}
