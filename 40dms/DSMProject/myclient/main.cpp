#include "logreader.h"
#include "logsender.h"
#include <iostream>
#include <stdexcept>
#include "dmsexception.h"
class DMSClient
{
private:
	ILogRead *reader;
	ILogSend *sender;
public:
	void setReader(ILogRead *rd)
	{
		reader=rd;
	}

	void setSender(ILogSend *sd)
	{
		sender=sd;
	}

	void mine()
	{
		try{
			list<matchedlogrec> logs;
			cout<<"���ݶ�ȡ��......"<<endl;
			reader->readLogs(&logs);
			cout<<"���ݶ�ȡ���"<<endl;
			cout<<"���ݷ�����......"<<endl;
			sender->sendLogs(&logs);
			cout<<"���ݷ������"<<endl;
		}
		catch(DMSException e)
		{
			cout<<e.what()<<endl;
		}
	}
};

int main()
{
	DMSClient client;
	LogReader reader;
	reader.setLogfile("wtmpx");
	
	LogNetSender sender;
	sender.setServerip("127.0.0.1");
	sender.setPort(9999);
	
	client.setReader(&reader);
	client.setSender(&sender);
	try
	{
		client.mine();	
	}catch(DMSException e)
	{
		cout<<e.what()<<endl;
	}	
	return 0;
}
