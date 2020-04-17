#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int global[2];

void *multiply_thread(void *arg)
{
    int *args_array;
    args_array =(int*) arg;

    int n1,n2,sum;
    n1=args_array[0];
    n2=args_array[1];
    sum = n1*n2;

    printf("N1 * N2 = %d\n",sum);

    return NULL;
}

int main() 
{
    printf("First number: ");
    scanf("%d",&global[0]);

    printf("Second number: ");
    scanf("%d",&global[1]);
    pthread_t tid_mul;
    pthread_create(&tid_mul,NULL,multiply_thread,(void*)&global);
    pthread_join(tid_mul,NULL);

    return 0;
}
