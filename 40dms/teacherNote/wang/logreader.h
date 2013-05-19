#ifndef LOGREADER_H
#define LOGREADER_H
#include<list>
#include "data.h"
#include<iostream>
using namespace std;
class logreader{
	char loginsfile[30];/*û��ƥ��ĵ�¼��¼�ļ���*/
	char logfile[30];/*Ҫ���ݵ���־�ļ���*/
public:
	/*�������������ļ����Ҫ���͵�����*/
	void readlog(list<logmatchrec> *matches);
private:
	/*1.���� ��wtmpx�������ڱ���
	 *  ��wtmpx���
	 *  �õ����ݵ��ļ���
	 */
	void backlogfile(char *backfilename);
	/*2.��ȡ�ϴ�û��ƥ��ļ�¼*/
	void readlogins(list<logrec> *logins);
	/*3.��ȡ���ݵ���־�ļ� �õ���¼���Ϻ͵ǳ�����*/
	void readbacklogfile(char *backfilename,list<logrec> *logins,
			list<logrec> *logouts);
	/*4.�õǳ����͵�¼������ƥ������յ�ƥ�伯��*/
	void matchlogs(list<logrec> *logins,list<logrec> *logouts,
			list<logmatchrec> *matches);
	/*5.����û��ƥ��ɹ��ĵ�¼��¼*/
	void savelogins(list<logrec> *logins);
};
#endif
