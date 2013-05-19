#ifndef LOGSENDER_H
#define LOGSENDER_H
#include <list>
#include "logreader.h"
//���ͽӿ�
class ILogSend
{
public:
	virtual void sendLogs(list<matchedlogrec> *logs)=0;
};
//���͵�����ʵ����[�������ļ�ʵ�֣�����̨ʵ�ֵ�
class LogNetSender:public ILogSend
{
private:
	char filename[52];//���淢��ʧ�����ݵ��ļ���
	char serverip[32];//������IP��ַ
	unsigned short  port;//�������˿�
	int fd;//������������
public:
	LogNetSender();
	virtual void sendLogs(list<matchedlogrec> *logs);//����������

	void setServerip(char *ip);
	void setPort(unsigned short pt);
private:
	void initSocket();//��ʼ�����磬���ӷ�����
	void readLogs(list<matchedlogrec> *logs); //��ȡ�ϴη���ʧ�ܵ�����
	void saveLogs(list<matchedlogrec> *logs); //�Ѵ汾�η���ʧ�ܵ�����
};
#endif
