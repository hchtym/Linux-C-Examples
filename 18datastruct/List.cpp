#include <iostream>
#include <stdexcept>
using namespace std;
typedef int T;
class List{
	struct Node{//�ڲ���
		T data;
		Node* next;
		Node(const T& d):data(d),next(){}
		//~Node(){cout <<"~Node()," << data << endl;}
	};	
	Node* head;
	int sz;
	//��ָ��λ�õ�ָ�뱾��
	Node*& getptr(int pos){
		if(pos==0) return head;
		if(pos<0||pos>sz) pos=sz;
		Node* p = head;
		for(int i=0; i<pos-1; i++){
			p = p->next;
		}
		return p->next;	
	}
public:
	List():head(),sz(){}
	~List(){clear();}
	//��ָ��λ�ò���Ԫ��
	List& insert(const T& d, int pos=0){
		Node* pn = new Node(d);
		Node*& ptr = getptr(pos);
		pn->next = ptr;
		ptr = pn;
		sz++;
		return *this;
	}
	//ɾ��ָ��λ�õ�Ԫ��
	bool erase(int pos){
		if(pos<0||pos>=sz) return false;
		Node*& ptr = getptr(pos);
		Node* p = ptr;
		ptr = ptr->next;
		delete p;
		sz--;
		return true;	
	}
	//ɾ�����ݵ���d��Ԫ��
	void remove(const T& d){
		int pos = 0;
		Node* p = head;
		for(; pos<sz; pos++){
			if(p->data == d){
				p = p->next;
				erase(pos);
				pos--;
			}else p = p->next;	
		}		
	}
	//�޸�ָ��λ�õ�Ԫ��
	bool set(const T& d, int pos){
		if(pos<0||pos>=sz) return false;
		Node*& ptr = getptr(pos);
		ptr->data = d;
		return true;		
	}	
	T& at(int pos){
		if(pos<0||pos>=sz) 
			throw out_of_range("list index out");
		Node*& ptr = getptr(pos);
		return ptr->data;
	}

	//��ӡ
	void travel(){
		//�����޸�ͷָ���ֵ
		Node* p = head;
		while(p){
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
	void clear(){
		while(head){
			Node* p = head;
			head = head->next;
			delete p;
		}
	}
	int size(){ return sz;}
	//��β������
	void push_back(const T& d){insert(d, sz);}
	//��ͷ������
	void push_front(const T& d){insert(d);}
	//����ͷ������ 
	const T front(){return head->data;}
	//����β������
	const T back(){
		Node*& ptr = getptr(sz-1);
		return ptr->data;
	}
};
int main()
{
	List list;
	list.insert(1).insert(2).insert(3).insert(4);
	list.insert(2).insert(2).insert(2);
	list.travel();	
	list.remove(2);
	list.travel();	
	list.push_back(100);
	list.push_front(200);
	list.travel();
	cout << list.front() << endl;
	cout << list.back() << endl;
}

