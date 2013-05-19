#include "logreader.h"
#include "dmsexception.h"
#include <string.h>
#include <cstdlib>
#include <string>
#include <strings.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>

//���캯��
LogReader::LogReader()
{
	char file[]="logins.dat";	
	bzero(loginsfile,255);
	memcpy(loginsfile,file,strlen(file));
}
//��־��ȡ��������
void LogReader::readLogs(list<matchedlogrec> *logs)
{
	
	char backfile[255];
	bzero(backfile,255);
	try{
		backup(backfile);
		list<logrec> logins;
		cout<<"��ȡ�ϴ�ʣ������¼......"<<endl;
		readLogins(&logins);
		cout<<"�ϴ�ʣ����:"<<logins.size()<<endl;
		list<logrec> logouts;
		cout<<"��ȡϵͳ��־......"<<endl;
		readLogFile(backfile,&logins,&logouts);
		cout<<"�����¼��:"<<logins.size()<<";�ǳ���¼��:"<<logouts.size()<<endl;
		cout<<"ƥ����룯�ǳ�������......"<<endl;
		match(&logins,&logouts,logs);
		cout<<"ƥ��ʣ������¼��:"<<logins.size()<<";ƥ��ɹ���:"<<logs->size()<<endl;
		cout<<"����ʣ���������......"<<endl;
		saveLogins(&logins);
	}
	catch(DMSException e)
	{
		throw;
	}
}
//���òɼ�����־�ļ�
void LogReader::setLogfile(char *file)
{
	memcpy(logfile,file,strlen(file));	
}
//ʣ������¼�ı����ļ���
void LogReader::setLoginsfile(char *file)
{
	memcpy(loginsfile,file,strlen(file));	
}
//������־�ļ�
void LogReader::backup(char*backfile)
{
		//�����ļ��� dmsyyyymmdd		
		//�õ�ϵͳʱ��
		time_t t=time(NULL); 
		struct tm* st=localtime(&t);
		sprintf(backfile,"dms%04d%02d%02d%02d%02d",st->tm_year+1900,st->tm_mon+1,st->tm_mday,st->tm_hour,st->tm_min);
		string backcmd("./backup.sh ");
		backcmd+=" wtmpx ";
		backcmd+=backfile;
		backcmd+="  2>/dev/null ";
		int re=system(backcmd.data());
                cout<<re<<endl; 
		if(re!=0)		
		{
			throw  DMSException("����ָ�����!"); 
		}
}
//��ȡ�ϴ�ƥ��ʣ��ĵ����¼
void LogReader::readLogins(list<logrec> *logins)
{
	//��ʣ��ĵ����¼�ļ���
	int fd=open(loginsfile,O_RDONLY|O_EXCL);
	if(fd==-1)
	{
		//�ļ������ڵ�ԭ��
		return;//�����κδ���
	}
	while(1)//ѭ����ȡ��¼
	{
		logrec log;
		int re=read(fd,&log,sizeof(log));
		if(re<=0)
		{
			//0 ��ʾ��ȡ��� ������ʾ�쳣
			close(fd);
			return;//��������
		}
		logins->push_back(log);
	}
}
//��ȡ��־�ļ�
void LogReader::readLogFile(char*backfile,list<logrec>*logins,list<logrec>*logouts)
{
	int fd=open(backfile,O_RDONLY|O_EXCL);
	if(fd==-1)
	{
		throw  DMSException("���ļ�����!"); 
	}
	while(1)
	{
		logrec logs={};
		short type;
		bzero(logs.logname,32);
		int re=read(fd,logs.logname,32);
		if(re<=0)
		{
			break;
		}		
		
		lseek(fd,36,SEEK_CUR);	
		re=read(fd,&logs.pid,sizeof(pid_t));
		logs.pid=ntohl(logs.pid);
				
		re=read(fd,&type,2);
		
		//�����ֽ���
		/*��������ʵ���µ�ϵͳ��Linux��
		ʵ�ʵ���־�ļ���Unix�����ò�ͬ���ֽ���,������һ��ת��*/
		type=ntohs(type);		
		
		lseek(fd,6,SEEK_CUR);	
		re=read(fd,&logs.logtime,4);	
		logs.logtime=ntohl(logs.logtime);		
		
		lseek(fd,28,SEEK_CUR);	
		short size;
		re=read(fd,&size,2);
		size=ntohs(size);
		bzero(logs.logip,257);
		re=read(fd,logs.logip,257);
		logs.logip[size]=0;
		if(logs.logname[0]!='.')
		{	

			if(type==7)
			{
				/*
				cout<<logs.logname<<";";
				cout<<logs.pid<<";";
				cout<<logs.logtime<<";";
				cout<<logs.logip<<";"<<endl;*/
				logins->push_back(logs);
			}
			else if(type==8)
			{
				logouts->push_back(logs);
			}
		}
		lseek(fd,1,SEEK_CUR);
	}
	close(fd);
}
//ƥ����־�ļ�
void LogReader::match(list<logrec>*logins,list<logrec>*logouts,list<matchedlogrec> *logs)
{
	list<logrec>::iterator i=logouts->begin();
	bool b=0;
	while(i!=logouts->end())
	{	
		b=0;
		list<logrec>::iterator j=logins->begin();
		while(j!=logins->end())
		{
			if(i->pid==j->pid &&
				!strncmp(i->logname,j->logname,strlen(i->logname))&&
				!strncmp(i->logip,j->logip,strlen(i->logip)))
			{
				matchedlogrec log;
				memset(&log.logname,0,sizeof(log.logname));
				memcpy(&log.logname,j->logname,strlen(j->logname));
				
				memset(&log.logip,0,sizeof(log.logip));
				memcpy(&log.logip,j->logip,strlen(j->logip));
				
				log.logintime=j->logtime;
				log.logouttime=i->logtime;
				log.durations=i->logtime-j->logtime;
				logs->push_back(log);
				//sleep(1);
				b=1;
				logins->erase(j);
				break;
			}
			j++;
		}
		logouts->erase(i);
		i=logouts->begin();	
	}
}
//����û��ƥ��ĵ����¼
void LogReader::saveLogins(list<logrec> *logins)
{
	//��ʣ��ĵ����¼�ļ���
	int fd=open(loginsfile,O_RDWR|O_CREAT|O_TRUNC);
	if(fd==-1)
	{
		//�����ļ����쳣
		return;//�����κδ���
	}
	while(logins->size()>0)
	{
		list<logrec>::iterator it=logins->begin();
		logrec log=*it;
		int re=write(fd,&log,sizeof(logrec));
		logins->erase(it);
		if(re==-1)
		{
			break;//������������д����
		}
	}
	close(fd);
}
