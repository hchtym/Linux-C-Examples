#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void furong()
{
	puts("�ټ�ܽ��");
}
void fengjie()
{
	puts("�����˷��");
}
void myexit(const char* msg, int val)
{
	puts(msg);
	_exit(val);//exit(val);
}
int main()
{
	atexit(furong);//�Ǽǣ��������ڵ��ö��ǳ������ʱ����
	atexit(fengjie);//�Ǽǣ��������ڵ��ö��ǳ������ʱ����
	printf("�Ǽ����\n");
	sleep(5);
	printf("ready to terminate\n");
	myexit("call myexit", 0);
	printf("you cannot see me.\n");
	return 0;
}

