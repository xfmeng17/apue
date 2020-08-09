#include "apue.h"

#include <pthread.h>

#define EQ_NUM 10

struct msg {
	struct msg *m_next;
	time_t m_time;
	int m_num;
	//** more stuff here
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void) {
	struct msg *mp;

	for (;;) {
		pthread_mutex_lock(&qlock);
		while (workq == NULL) {
			pthread_cond_wait(&qready, &qlock);
		}
		mp = workq;
		workq = mp->m_next;
		pthread_mutex_unlock(&qlock);
		//** now process the message mp
		printf("worker=%ld, m_time=%ld, m_num=%d\n",
			   pthread_self(), mp->m_time, mp->m_num);
		sleep(1);
	}
}

void enqueue_msg(struct msg *mp) {
	pthread_mutex_lock(&qlock);
	mp->m_next = workq;
	workq = mp;
	pthread_mutex_unlock(&qlock);
	pthread_cond_signal(&qready);
}

void* thread_process(void* p) {
	printf("process_msg,n=%d,tid=%ld\n", *((int*)p), pthread_self());
	process_msg();
}
void* thread_enqueue(void* p) {
	printf("*p=%d\n", *((int*)p));
	for (int i = 0; i < EQ_NUM; i++) {
		struct msg *mp = (struct msg*)malloc(sizeof(struct msg));
		mp->m_next = NULL;
		mp->m_time = time(NULL);
		mp->m_num = *((int*)p);
		enqueue_msg(mp);
		sleep(1);
	}
	printf("enqueue_msg,n=%d,tid=%ld\n", *((int*)p), pthread_self());
}

int main() {
	int err = 0;
	pthread_t tid_p;
	pthread_t tid_e;
	int *num = (int*)malloc(sizeof(int)*20);
	for (int i = 0; i < 2; i ++) {
		num[i] = i;
		err = pthread_create(&tid_p, NULL, thread_process, &num[i]);
	}
	for (int i = 0; i < 10; i++) {
		num[i] = i;
		err = pthread_create(&tid_e, NULL, thread_enqueue, &num[i]);
	}
	pthread_join(tid_p, NULL);
	pthread_join(tid_e, NULL);
	return(0);
}
