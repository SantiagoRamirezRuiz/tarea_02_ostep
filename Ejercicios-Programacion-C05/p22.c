#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
  int p;
  int a=1;
  char cad[50];
  FILE*f;
  f=fopen("test.txt","w");
  p=fork();
  fprintf(f,"%d\n",a);
  printf("test");
  
}
