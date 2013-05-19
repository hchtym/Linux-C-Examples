#include <iostream>
using namespace std;
typedef int T;
class Stack{
	T data[100];
	int size;
public:
	Stack():size(){}	
	//��ջ
	void push(const T& d){
		if(full()) throw "full";
		data[size++] = d;
	}
	//��ջ
	void pop(){if(empty()) throw "empty";size--;}
	//�鿴ջ��Ԫ��
	const T top(){return data[size-1];}
	//ջ�Ƿ�Ϊ��
	bool empty(){return size==0;}
	//ջ�Ƿ���
	bool full(){return size==100;}		 
};

int main()
{
	Stack s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	while(!s.empty()){
		cout << s.top() << ' ';
		s.pop();
	}	
	cout << endl;
}

