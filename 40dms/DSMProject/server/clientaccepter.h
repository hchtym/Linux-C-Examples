#ifndef CLIENTACCEPTER_H
#define CLIENTACCEPTER_H
#include <sys/socket.h>
#include <sys/types.h>
struct  threadp  //Ϊ���̴߳��ݲ�����ƵĽṹ��
{
	int  cfd;
    char cip[32];
};
class ClientAccepter
{
private:
	unsigned short port;//�������˿�  
	int fd;//������������
public:
	ClientAccepter();//������	
	int initSocket();//��ʼ��������
	void setPort(unsigned short pt);//���÷������˿�
};
#endif
