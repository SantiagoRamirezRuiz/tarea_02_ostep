#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
  int p;
  char cad[50];
  FILE*f;
  f=fopen("test.txt","r");
  p=fork();
  if (p>0) {
  // parent goes down this path (main)
    printf("this is the parent\n");
    fgets(cad, 50, f);
    printf("%s\n",cad);
  } else {
  // child (new process)
    printf("this is the child\n");
    fgets(cad, 50, f);
    printf("%s\n",cad);
  }
  
  
}
