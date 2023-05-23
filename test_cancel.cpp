
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void *thread_func(void *ignored_argument)
{



    printf("[thread_func()] a\n");

    // PTHREAD_CANCEL_ASYNCHRONOUS, PTHREAD_CANCEL_DEFERRED
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    printf("[thread_func()] b\n");    

    
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    printf("[thread_func()] c\n");

    sleep(2);

    printf("[thread_func()] d\n");

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    printf("[thread_func()] e\n");

    sleep(1);       

    printf("[thread_func()] f\n");

    return NULL;
}


int main(void)
{

    pthread_t thr;
    void *res;

    printf("[main()] a\n");
    
    pthread_create(&thr, NULL, &thread_func, NULL);

    printf("[main()] b\n");
    
    sleep(1);     
    
    printf("[main()] c\n");    
    
    pthread_cancel(thr); // non-blocking
   
    printf("[main()] d\n");
    
    // double a = 1.;
    // for(int i = 0;i<1000000000;i++){
    //     a *= 1.0000000001;
    // }
    // printf("a = %f\n", a);

    pthread_join(thr, &res); // blocking

    printf("[main()] e\n");

    if (res == PTHREAD_CANCELED) printf("main(): thread was canceled\n");
    else printf("main(): thread wasn't canceled (shouldn't happen!)\n");
    
    exit(EXIT_SUCCESS);
}