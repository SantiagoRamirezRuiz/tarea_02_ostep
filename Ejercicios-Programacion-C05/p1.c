#include<stdio.h>
int main()
{
  int p;
  int x;
  x=100;
  p=fork();
  if (p>0) {
  // parent goes down this path (main)
    x=200;
    printf("%d\n",x);
  } else {
  // child (new process)
    printf("%d\n",x);
    x=300;
    printf("%d\n",x);
  }
  return 0;
}
