#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MAX 10

pthread_t thread[2];
pthread_mutex_t mut;
int i = 0, number = 0;

void *thread1()
{
	printf("thread1: I'm thread 1.\n");
	for (i = 0; i < MAX; i++) {
		printf("thread1: number = %d\n", number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *thread2()
{
	printf("thread2: I'm thread 2.\n");
	for (i = 0; i < MAX; i++) {
		printf("thread2: number = %d\n", number);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(2);
	}
	pthread_exit(NULL);
}

void thread_create()
{
	int temp;
	memset(&thread, 0, sizeof(thread));
	if ((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0) {
		printf("create thread1 failed!\n");
	} else {
		printf("create thread1 success!\n");
	}

	if ((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0) {
		printf("create thread2 failed!\n");
	} else {
		printf("create thread2 success!\n");
	}
}

void thread_wait()
{
	if (thread[0] != 0) {
		pthread_join(thread[0], NULL);
		printf("thread1 end!\n");
	}
	if (thread[1] != 0) {
		pthread_join(thread[1], NULL);
		printf("thread2 end!\n");
	}
}

int main()
{
	pthread_mutex_init(&mut, NULL);
	printf("I am Main, I am creating thread!\n");
	thread_create();
	printf("I am Main, I am waiting thread end!\n");
	thread_wait();
	return 0;
}

