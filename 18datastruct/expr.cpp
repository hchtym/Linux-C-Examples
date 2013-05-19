#include <iostream>
using namespace std;
typedef char T;
class Stack{
	T data[100];
	int size;
public:
	Stack():size(){}	
	void push(const T& d){
		if(full()) throw "full";
		data[size++] = d;
	}
	void pop(){if(empty()) throw "empty";size--;}
	const T top(){return data[size-1];}
	bool empty(){return size==0;}
	bool full(){return size==100;}		 
};

//+ - * /  c1�����ȼ�����c2����true,����false
bool prior(char c1, char c2){
	return (c1=='*'||c1=='/')&&(c2=='+'||c2=='-');
}

int main(){
	string str = "1+2*(3+4)/7+8*9";
	cout << str << endl;
	Stack res;//���ջ	
	Stack exp;//�����ջ
	for(int i=0; i<str.length(); i++){
		char ch = str[i];
		if(isdigit(ch)){//��������֣�ֱ������ջ
			res.push(ch);
		//�����������,ֱ���������ջ
		}else if(ch=='('){
			exp.push(ch);
		//����������ţ��������ջ�е������������ջ��ֱ������������Ϊֹ
		}else if(ch==')'){
			while(exp.top()!='('){
				res.push(exp.top());
				exp.pop();
			}
			exp.pop();
		}else{//���򣬾����������+ - * /
			while(!exp.empty()&&(exp.top()!='(')
				&&(!prior(ch,exp.top()))){
				res.push(exp.top());
				exp.pop();
			}
			exp.push(ch);
		}
	}
	while(!exp.empty()){
		res.push(exp.top());
		exp.pop();
	}
	Stack s;
	while(!res.empty()){
		s.push(res.top());
		res.pop();
	}
	while(!s.empty()){
		cout << s.top() << ' ';
		s.pop();
	}
	cout << endl;
}

