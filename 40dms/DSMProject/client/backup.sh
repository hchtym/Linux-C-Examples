#!/bin/bash
#��־���ݽű�����������:ԭ�ļ����������ļ���
#�ж������Ƿ񴫵ݳ��
if (( $# < 2 ))
then
	exit 1
fi

#�ж�������ȷ���
if cp $1 $2 >&/dev/null 
then
#�ж�����Ƿ���ȷ
#	if cat /dev/null >$1
#	then
		exit 0
#	else
#		exit 3	
#	fi
else
	exit 2	
fi

