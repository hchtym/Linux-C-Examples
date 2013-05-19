#include "logsender.h"
#include "dmsexception.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <strings.h>
#include  <netdb.h>

//������
LogNetSender::LogNetSender()
{
	bzero(serverip,sizeof(serverip));//string.h
	strcpy(serverip,"127.0.0.1");
	port=9999;
	bzero(filename,sizeof(filename));
	strcpy(filename,"fail.dat");
}
//����������
void LogNetSender::sendLogs(list<matchedlogrec> *logs)
{
	try{
		//���ϴη���ʧ�ܵ����ݶ�ȡ�����ϲ���һ��		
		cout<<"��ȡ�ϴη���ʧ�ܼ�¼......"<<endl;			
		readLogs(logs);
		cout<<"�ϴη���ʧ���뱾�η��ͼ�¼����:"<<logs->size()<<endl;			
		//��ʼ������
		cout<<"���ӷ�������......"<<endl;			
		initSocket();
		cout<<"��ʼ��������......"<<endl;			
		//ѭ����������[���Է�װ��һ��˽�к���]
		
		while(logs->size()>0)
		{
			list<matchedlogrec>::iterator it=logs->begin();
			int re=send(fd,&(*it),sizeof(matchedlogrec),0);
			if(re==-1)
			{
				throw DMSException("��������ʧ��!");
			}
			cout<<"���� ��¼:"<<logs->size()<<":"<<it->logname<<";"<<it->logip<<endl;
			logs->erase(it);
		}
		cout<<"�������!������־���Է���ʧ�ܵ����ݣ�Ҫ�������ϣ�"<<endl;
		
	}
	catch(DMSException e)
	{
		cout<<"�����쳣!"<<endl;		
		//�����쳣���ͱ�������
		cout<<"���淢��ʧ��������....!"<<endl;
		saveLogs(logs);
		cout<<"���淢��ʧ���������!"<<endl;
		throw;
	}
}
void LogNetSender::setServerip(char *ip)
{
	bzero(serverip,sizeof(serverip));
	strcpy(serverip,ip);	
}
void LogNetSender::setPort(unsigned short pt)
{
	port=pt;
}
//��ʼ�����磬���ӷ�����
void LogNetSender::initSocket()
{
	//�������ݱ��ĵķ�ʽ����
	fd=socket(PF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		throw DMSException("����socket����");
	}
	struct sockaddr_in  addr={};
	addr.sin_family=PF_INET;
	addr.sin_port=htons(port);
//	addr.sin_addr.s_addr=inet_addr(serverip);
	int re=connect(fd,(sockaddr*)&addr, sizeof(sockaddr_in));
	if(re==-1)
	{
		throw DMSException("���ӷ���������!");
	}	 
}
//��ȡ�ϴη���ʧ�ܵ�����
void LogNetSender::readLogs(list<matchedlogrec> *logs)
{
	//��ʣ��ĵ����¼�ļ���
	int fd=open(filename,O_RDONLY|O_EXCL);
	if(fd==-1)
	{
		//�ļ������ڵ�ԭ��
		return;//�����κδ���
	}
	while(1)//ѭ����ȡ��¼
	{
		matchedlogrec log;
		int re=read(fd,&log,sizeof(log));
		if(re<=0)
		{
			//0 ��ʾ��ȡ��� ������ʾ�쳣
			close(fd);
			return;//��������
		}
		logs->push_back(log);
	}
}
//���汾�η���ʧ�ܵ�����
void LogNetSender::saveLogs(list<matchedlogrec> *logs)
{
	//��ʣ��ĵ����¼�ļ���
	int fd=open(filename,O_RDWR|O_CREAT|O_TRUNC);
	if(fd==-1)
	{
		//�����ļ����쳣
		return;//�����κδ���
	}
	while(logs->size()>0)
	{
		list<matchedlogrec>::iterator it=logs->begin();
		matchedlogrec log=*it;
		int re=write(fd,&log,sizeof(matchedlogrec));
		logs->erase(it);
		if(re==-1)
		{
			break;//������������д����
		}
	}
	close(fd);
}

