#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *child_func(void *args)
{
     for (int i = 0; i < 10; i++)
     {
          printf("Child thread. Iteration: %d\n", i + 1);
          sleep(rand() % 3);
     }
}

int main(int argc, char **argv)
{
     printf("Main thread. 1st iteration\n");

     pthread_t thread;
     pthread_create(&thread, NULL, child_func, NULL);

     for (int i = 0; i < 10; i++)
     {
          printf("Main thread. Iteration: %d\n", i + 1);
          sleep(rand() % 3);
     }

     return 0;
}