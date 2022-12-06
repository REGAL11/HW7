#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct attributes
{
     char *name;

     int num;
     char *str;

} attributes;

void *child_func(void *args)
{
     attributes attr = *(attributes *)args;
     for (int i = 0; i < attr.num; i++)
     {
          printf("%s thread. %s %d\n", attr.name, attr.str, i);
          sleep(rand() % 3);
     }
}

int main(int argc, char **argv)
{

     attributes attr[4];

     attr[0].name = "Western";
     attr[0].num = rand() % 7 + 2;
     attr[0].str = "Charlie is my name";

     attr[1].name = "Bravo";
     attr[1].num = rand() % 7 + 2;
     attr[1].str = "Hexagon never dies";

     attr[2].name = "Blackberry";
     attr[2].num = rand() % 7 + 2;
     attr[2].str = "Too old for this";

     attr[3].name = "Husky";
     attr[3].num = rand() % 7 + 2;
     attr[3].str = "Good wine is always best choice";

     for (int i = 0; i < 4; i++)
     {
          pthread_t thread;
          pthread_create(&thread, NULL, child_func, (void *)(attr + i));
     }

     printf("Main thread is sleeping\n");

     sleep(15);

     printf("Main thread is awake\n");

     return 0;
}