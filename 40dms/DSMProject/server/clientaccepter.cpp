#include "clientaccepter.h"
#include "dmsexception.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "dmsdao.h"
#include "userdata.h"
#include <iostream>
using namespace std;
UserData  udata; //ȫ�ֵķŽ������ݵ�����
void* receviedata(void *thobj)
{
	threadp* smfd=(struct threadp*)thobj;
	cout<<"mfd"<<(smfd->cfd)<<endl;
	int cfd=smfd->cfd;
	char *cip=smfd->cip;
	struct matchedlogrec log;
	//ÿ����304�ֽڣ�����log���������ͱ��浽���ݿ�		
	size_t size=0;//ͬʱ��¼�ṹ���ŵ�ƫ��λ��,������304��ʱ�򣬴����һ���ṹ��
	size_t len=sizeof(struct matchedlogrec);//�ṹ���ܳ���	

	while(1)
	{
		//�߳�ִ�д�
		char  data[sizeof(struct matchedlogrec)];//ÿ�ν��ܵ�����ֽ���
		//��Ϊʹ�õ���TCP��ÿ�ν��ܵ�����δ����һ�������Ľṹ,����Ҫȷ��304�ֽڵ�������
		size_t t=recv(cfd,&data,sizeof(data),0);
		
		if(t<=0 || t==-1)//��ʾ����ϵ��˻��߽���ʧ��
		{	
			break;//�ɼ������������ֹ���βɼ�
		}
		if(t>0)//���ܵ�����
		{
			if(t<len-size)//δ��
			{	
				memcpy(((char*)&log)+size,data,t);//ע��ָ������Ļ�����λ
				size+=t;	
			}
			else//��
			{
				memcpy(((char*)&log)+size,data,len-size);//ʣ�ಿ�ַ���һ����¼
				//cout<<log.logname<<":"<<log.logip<<endl;
				//���ݸ�DAO������-����
				struct logdata rdata;
				memcpy(&rdata,&log,sizeof(log));
				strcpy(rdata.labip,cip);
				//mdao.save(rdata);  ���ڲ�������������ݿ�
				udata.push_data(rdata);
				cout<<cfd<<":"<<cip<<":"<<rdata.logname<<endl;
				if(t-len+size>0)
				{
					memcpy(&log,data+len-size,t-len+size);
					//����Ŀ���뻺��ȳ����������ﲻ���ж��Ƿ񹻳�
					size=t-len+size;
				}
				else
				{
					size=0;
				}
			}		
		} 
	}
	close(cfd);
	cout<<"�ɼ�����"<<endl;
    return thobj;

}
class  DataReciveThread  //����߳�ֻ�ܽ������� �൱��������
{
 public:  //���������������ݵ��̵߳ĺ���
      void  start(threadp *tp){
          pthread_t threadid;
          pthread_create(&threadid,NULL,receviedata,(void*)tp);
       }
};
void * savedata(void *obj){
	DMSDAO  mdao;  //�����������ݵĶ���
	char  userp[30]="openlab/open123";
	mdao.connect(userp);
	int i=0;
	while(1){		
		if(i++%150==0) mdao.commit();  //150������ͳһ�ύ  ����150�߳̽���ʱ�ύ
	    mdao.save(udata.pop_data());
	    if(udata.getsize()==0) break;  //�������û������  ���������߳�
	}
	mdao.close();
}
class  DataCustomerThread  //����߳�ֻ�ܰ����ݷ������ݿ� �൱��������
{
 public:  //���������������ݵ��̵߳ĺ���
      void  start(){
          pthread_t threadid;
          pthread_create(&threadid,NULL,savedata,NULL);
       }
};
//������
ClientAccepter::ClientAccepter():port(9999)
{
}
//���÷������˿ڣ�������Ĭ�ϳ�ʼ��Ϊ9999
void ClientAccepter::setPort(unsigned short pt)
{
	port=pt;
}
//��ʼ��������
int  ClientAccepter:: initSocket()
{
	//����Socket������
	fd=socket(PF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		throw DMSException("������Socket��������");
	}
	//�󶨵�ַ
	struct sockaddr_in addr={};
	addr.sin_family=PF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	int re=bind(fd,(struct sockaddr*)&addr,sizeof(sockaddr_in));
	if(re==-1)
	{
		throw DMSException("������Socket�󶨴���");
	}
	//����
	re=listen(fd,10);
	if(re==-1)
	{
		throw DMSException("������Socket��������");
	}
	return fd;
}


int main(){
  ClientAccepter  serverm;
  int fd= serverm.initSocket();
  while(1){
	
    struct sockaddr_in addr={};
	socklen_t len=sizeof(struct sockaddr_in);
	int cfd=accept(fd, (struct sockaddr *)&addr, &len);
	cout<<"cfd"<<cfd<<endl;
	if(cfd==-1)
	{
		throw DMSException("���ܿͻ����Ӵ���");
	}
	char *cip=inet_ntoa(addr.sin_addr);
    cout<<"cip"<<cip<<endl;
	//�����ﴴ�� �������ݵ��߳�  �ѵõ��Ŀͻ�������������cfd
	//�Ϳͻ��˵ķ�����ip���뵽�߳���
	 struct  threadp  tp;
	 tp.cfd=cfd;
	 strcpy(tp.cip,cip);
	 DataReciveThread  drt;  //���������� ��������
	 cout<<"���βɼ���ʼ"<<endl;
	 drt.start(&tp); 
	 DataCustomerThread  dct; //����������  �������ݵ����ݿ�
	 dct.start();
  }
 
}