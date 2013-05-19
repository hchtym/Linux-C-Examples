#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	if(fork()==0){//��һ������
		printf("1st child: %d\n", getpid());
		for(;;){
			putchar('.');
			fflush(stdout);
			sleep(1);
		}
	}
	else if(fork()==0){//�ڶ�������
		printf("2nd child: %d\n", getpid());
		int i;
		for(i=0; i<5; i++){
			putchar('*');
			fflush(stdout);
			sleep(1);
		}
		return 5;//exit(0);
	}
	else{//������
		pid_t cid;
		int state;
		int data = 0;
		for(;;){
			cid=waitpid(-1,&state,WNOHANG);//0,-1,>0
			if(cid==0)printf("(-)");
			else if(cid>0){
			  if(WIFEXITED(state)){
				printf("%d����%d\n",cid,WEXITSTATUS(state));
			  }
			  else{//if(WIFSIGNALED(state))
				printf("%d�쳣%d\n",cid,WTERMSIG(state));
			  }
			}
			else{
				printf("û���ӽ�����\n");
				break;
			}
			printf("%d ", ++data);
			fflush(stdout);
			sleep(1);
		}
	}
}

