#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

size_t factorial(size_t num)
{
     if (num <= 1)
          return 1;

     if (num == 2)
          return 2;

     size_t result = 2;
     for (size_t i = 3; i <= num; i++)
          result *= i;

     return result;
}

size_t is_prime(size_t num)
{
     for (size_t i = 2; i * i <= num; i++)
     {
          if (num % i == 0)
               return 0;
     }

     return 1;
}

struct prime_attr
{
     int count;
     pthread_t c_thread;
};

void *
prime_func(void *args)
{
     struct prime_attr attr = *(struct prime_attr *)args;
     int count = attr.count;
     size_t *arr = malloc(sizeof(size_t) * count);

     size_t **res_arr = malloc(sizeof(size_t *) * 2);
     res_arr[0] = arr;

     size_t
         prime_count = 0,
         num = 0;

     while (prime_count < count)
     {
          if (is_prime(num))
          {
               arr[prime_count] = num;
               printf("Find one more prime number\n");
               num++;
               prime_count++;

               continue;
          }
          else
               num++;
     }

     pthread_join(attr.c_thread, (void **)&res_arr[1]);

     pthread_exit((void **)res_arr);
}

void *calag_func(void *args)
{
     int count = *(int *)(args);
     size_t *arr = malloc(sizeof(size_t) * count);

     // int **res_arr = malloc(sizeof(int *) * 2);
     // res_arr[0] = arr;

     for (int i = 0; i < count; i++)
     {
          //     printf("(2*n)! = %ld\n (n+1)! = %ld - | - n! = %ld\n", factorial(2 * i), factorial(i + 1), factorial(i));
          arr[i] = factorial(2 * i) / (factorial(i + 1) * factorial(i));
          //   printf("Calagan number: %ld\n", arr[i]);
          printf("Add one more calagan number\n");
     }

     pthread_exit((void *)arr);
}

int main(int argc, char **argv)
{
     srand(time(NULL));

     int count = 10;

     pthread_t calag_thread;
     if (pthread_create(&calag_thread, NULL, calag_func, (void *)(&count)) != 0)
     {
          fprintf(stderr, "Couldn't create prime thread!\n");

          return EXIT_FAILURE;
     }

     struct prime_attr attr;
     attr.count = count;
     attr.c_thread = calag_thread;

     pthread_t prime_thread;
     if (pthread_create(&prime_thread, NULL, prime_func, (void *)(&attr)) != 0)
     {
          fprintf(stderr, "Couldn't create calagan thread!\n");

          return EXIT_FAILURE;
     }

     size_t **arr;
     printf("\n --- Waiting for result ---\n\n");
     pthread_join(prime_thread, (void **)(&arr));

     printf("\n --- Returned to main thread ---\n\n");

     printf("Prime numbers: \n");
     for (size_t i = 0; i < count; i++)
     {
          printf("%ld\t", arr[0][i]);
     }

     printf("\n");

     printf("Calagan numbers: \n");
     for (size_t i = 0; i < count; i++)
     {
          printf("%ld\t", arr[1][i]);
     }

     printf("\n\n");

     return 0;
}