#ifndef DMSEXCEPTION_H
#define DMSEXCEPTION_H
#include <stdexcept>
class DMSException:public runtime_error
{
public:
		DMSException():runtime_error("���ݲɼ��쳣"){}
		DMSException(char *msg):runtime_error(msg){}
};
#endif
