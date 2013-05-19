#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t c=PTHREAD_COND_INITIALIZER;
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t n=PTHREAD_MUTEX_INITIALIZER;

void* work(void* p)
{
	pthread_mutex_lock(&m);
//	sleep(2);
	printf("�߳�%x��ʼ�����\n", pthread_self());
	++(*(int*)p);
	pthread_cond_signal(&c);
	pthread_mutex_unlock(&m);
	sleep(10);//�����߳����Լ��Ĺ���
	printf("�߳�%x����\n", pthread_self());
	return p;
}
int main()
{
	int i;
	int cnt=0;
	pthread_t ids[5];
	pthread_mutex_lock(&m);
	for(i=0; i<5; i++){
		pthread_create(&ids[i],NULL,work,&cnt);
	}
	printf("�����������߳�\n");
	struct timespec ts;
	ts.tv_sec = 1;
	ts.tv_nsec = 0;
	pthread_mutex_lock(&n);
	pthread_mutex_unlock(&m);
	do{
	//	if(cnt==5) break;
//		if(pthread_cond_timedwait(&c,&n,&ts)!=0)
//			printf("��ʱ\n");
		pthread_cond_wait(&c,&n);
		printf("�Ѿ���ɳ�ʼ�����߳���%d\n", cnt);
	}while(cnt!=5);
	printf("�����߳���ɳ�ʼ��\n");
	pthread_mutex_unlock(&n);
	pthread_mutex_destroy(&n);
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);
	//.....���߳����Լ��Ĺ���
	for(i=0; i<5; i++){//�ȴ������߳̽���
		pthread_join(ids[i], NULL);
	}
	return 0;
}

