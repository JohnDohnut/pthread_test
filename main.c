#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <memory.h>
#include <pthread.h>

typedef struct thread_arg thread_arg;
struct thread_arg{
    int count;
    pthread_mutex_t* lock;
};
thread_arg* thread_arg_init(){
    thread_arg* arg;
    arg = malloc(sizeof(thread_arg));
    if(arg < 0)
        return -1;
    memset(arg, 0, sizeof(thread_arg));
    return arg;
}
void* myThread(void* argv){
    if(argv == NULL){
        printf("myThread arg NULL \n");
        return -1;
    }
    thread_arg* arg = (thread_arg*)argv;
    pthread_mutex_t *lock = arg->lock;
    printf("tid : %d \n",pthread_self());
    pthread_mutex_lock(lock); /// count will be printed in ascending order while tid is not.
    arg->count ++;
    printf("count : %d\n", arg->count);
    pthread_mutex_unlock(lock);
}
int main(int argv, char* argc[]){

    pthread_mutex_t * lock;
    pthread_mutex_init(lock,NULL);
    thread_arg* arg;
    arg = malloc(sizeof(thread_arg));
    arg->count = 0;
    arg->lock=lock;
    pthread_t tid[20];
    int err = -1;

    for(int i=0; i<20; i++)
    {
        err = pthread_create(&tid[i], NULL, myThread, arg);
        if(err<0)
            printf("err\n");
    }
    for(int i=0; i<20; i++){
        err = pthread_join(tid[i],NULL);
        if(err<0)
            printf("err on tid : %d\n",tid[i]); 
    }


}