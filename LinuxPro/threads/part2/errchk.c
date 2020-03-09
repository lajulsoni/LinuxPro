#include <pthread.h>
#include <stdio.h>
#include <errno.h>

pthread_mutex_t mutex;

 
void * writer(void *p)
{
	printf("\n %s: \n",__func__);
	if(pthread_mutex_lock(&mutex)==0)
	{
		printf(" Writer: lock acquired\n");
	if(pthread_mutex_lock(&mutex) == EDEADLK )
                        printf("\n Recursive lock attempt detected \n");
		printf(" updating commits .......\n");
		sleep(2);
		printf(" Done : exit from mutex block\n");
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);	
}

void * t_routine(void *p)
{
	printf("\n %s: \n",__func__);
	if(pthread_mutex_unlock(&mutex) == EPERM)
                printf("\n Unlock failed: Mutex not owned by current thread\n");


        pthread_exit(NULL);
}

int main ()
{
	pthread_t tcb1,tcb2;

	/* mutex Attribute object */
	pthread_mutexattr_t attr;
	int rv;

	pthread_mutexattr_init(&attr);

	/* set mutex type to ERRORCHECK */
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ERRORCHECK);

	/* assign mutex attributes */
	pthread_mutex_init(&mutex,&attr);
	
	rv = pthread_create(&tcb1, NULL, writer, NULL);
	if(rv)
	    puts("Failed to create thread");

	rv = pthread_create(&tcb2, NULL, t_routine, NULL);
        if(rv)
             puts("Failed to create thread");

	pthread_exit(NULL);
}
