
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int value = 0;

static void *thread_func1(void *ignored_argument)
{
    while(1){
        printf("[thread_func1()] a\n"); 

        pthread_mutex_lock(&mutex);

        printf("[thread_func1()] b\n"); 

        if(value == 0){
            pthread_cond_wait(&cond, &mutex);
            printf("[thread_func1()] wake up, value: %d\n", value); 
        } 

        printf("[thread_func1()] c\n"); 

        value--;
        printf("[thread_func1()] value--: %d\n", value); 

        printf("[thread_func1()] d\n"); 
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex); 

        printf("[thread_func1()] e\n");  

        printf("\n\n");
    }

    return NULL;
}


static void *thread_func2(void *ignored_argument)
{

    while(1){
        printf("[thread_func2()] a\n"); 

        pthread_mutex_lock(&mutex);

        printf("[thread_func2()] b\n"); 

        if(value == 1){ 
            pthread_cond_wait(&cond, &mutex);
            printf("[thread_func2()] wake up, value: %d\n", value);
        }

        printf("[thread_func2()] c\n"); 

        value++;
        printf("[thread_func1()] value++: %d\n", value); 

        pthread_cond_signal(&cond);

        printf("[thread_func2()] d\n"); 

        pthread_mutex_unlock(&mutex);

        printf("[thread_func2()] e\n"); 

        printf("\n\n");
    }


    return NULL;
}



  

int main(void)
{
    pthread_t thr1, thr2;

    pthread_create(&thr1, NULL, &thread_func1, NULL);
    sleep(1);    
    pthread_create(&thr2, NULL, &thread_func2, NULL);

    
    pthread_join(thr1, NULL); 
    pthread_join(thr2, NULL); 

    return 0;
}