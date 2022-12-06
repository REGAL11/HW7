#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct attributes
{
     char *name;

     int num;
     char *str;

     pthread_t par_thread;

} attributes;

typedef struct rand_attributes
{
     int count;

     int min;
     int max;

     int target;

} rand_attributes;

void *str_func(void *args)
{
     attributes attr = *(attributes *)args;
     for (int i = 0; i < attr.num; i++)
     {
          printf("%s thread. %s %d\n", attr.name, attr.str, i);
          sleep(rand() % 2);
     }

     pthread_join(attr.par_thread, NULL);
}

void *rand_func(void *args)
{
     rand_attributes r_attr = *(rand_attributes *)args;
     for (int i = 0; i < r_attr.count; i++)
     {
          int num = rand() % (r_attr.max - r_attr.min + 1) + r_attr.min;
          if (num == r_attr.target)
          {
               printf("Random thread. Iteration %d from %d. Number: %d\n", i, r_attr.count, num);
               printf(" -- Number: %d equal to target %d\n Ending rand thread\n", num, r_attr.target);

               return NULL;
          }

          printf("Random thread. Iteration %d from %d. Number: %d\n", i, r_attr.count, num);

          sleep(rand() % 2);
     }
}

int main(int argc, char **argv)
{
     srand(time(NULL));

     attributes attr;

     attr.name = "Bravo";
     attr.num = rand() % 16 + 5;
     attr.str = "Hexagon never dies";

     rand_attributes r_attr;

     r_attr.count = rand() % 51 + 50;
     r_attr.min = -15;
     r_attr.max = 15;
     r_attr.target = 5;

     pthread_t rand_thread;
     pthread_create(&rand_thread, NULL, rand_func, (void *)(&r_attr));

     attr.par_thread = rand_thread;

     pthread_t str_thread;
     pthread_create(&str_thread, NULL, str_func, (void *)(&attr));

     printf("\n --- Main thread waiting for finishing all child threads --- \n\n");
     pthread_join(str_thread, NULL);

     printf("All proccesses done!\n");

     return 0;
}