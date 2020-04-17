#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t r1,r2,r3;
void *p1()
{
    printf("\nP1 currently using R1");
    pthread_mutex_lock(&r1);
        sleep(1);
        printf("\nP1 trying to get R2");
        pthread_mutex_lock(&r2);
        printf("\nP1 got R2!!");
        pthread_mutex_unlock(&r2);
     pthread_mutex_unlock(&r1);
return 0;
}

void *p2()
{
    printf("\nP2 currently using R2");
    pthread_mutex_lock(&r2);
        sleep(1);
        printf("\nP2 trying to get R1");
        printf("\nP2 trying to get R3");
        pthread_mutex_lock(&r1);
        pthread_mutex_lock(&r3);
        printf("\nP2 got R1!!");
        printf("\nP2 got R3!!");
        pthread_mutex_unlock(&r1);
        pthread_mutex_unlock(&r3);

     pthread_mutex_unlock(&r2);
return 0;
}

void *p3()
{
    printf("\nP3 currently using R3\n");
    pthread_mutex_lock(&r3);
        sleep(1);
        printf("\nP3 trying to get R2");
        pthread_mutex_lock(&r2);
        printf("\nP3 got R2!!");
        pthread_mutex_unlock(&r2);
     pthread_mutex_unlock(&r3);
return 0;
}



int main(){
    pthread_t t1,t2,t3;
    pthread_mutex_init(&r1, NULL);
    pthread_mutex_init(&r2, NULL);
    pthread_mutex_init(&r3, NULL);

    pthread_create(&t1,NULL, p1 , NULL);
    pthread_create(&t2,NULL, p2 , NULL);
    pthread_create(&t3,NULL, p3 , NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    pthread_mutex_destroy(&r1);
    pthread_mutex_destroy(&r2);
    pthread_mutex_destroy(&r3);

}
