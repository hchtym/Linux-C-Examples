#include <iostream>
#include <stdexcept>
#include "list.h"
using namespace std;
List::Node*& List::getptr(int pos){
	if(pos==0) return head;
	if(pos<0||pos>sz) pos=sz;
	Node* p = head;
	for(int i=0; i<pos-1; i++){
		p = p->next;
	}
	return p->next;	
}
List& List::insert(const T& d, int pos){
	Node* pn = new Node(d);
	Node*& ptr = getptr(pos);
	pn->next = ptr;
	ptr = pn;
	sz++;
	return *this;
}
	//ɾ��ָ��λ�õ�Ԫ��
bool List::erase(int pos){
	if(pos<0||pos>=sz) return false;
	Node*& ptr = getptr(pos);
	Node* p = ptr;
	ptr = ptr->next;
	delete p;
	sz--;
	return true;	
}
	//ɾ�����ݵ���d��Ԫ��
void List::remove(const T& d){
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
bool List::set(const T& d, int pos){
	if(pos<0||pos>=sz) return false;
	Node*& ptr = getptr(pos);
	ptr->data = d;
	return true;		
}	
T& List::at(int pos){
	if(pos<0||pos>=sz) 
		throw out_of_range("list index out");
	Node*& ptr = getptr(pos);
	return ptr->data;
}

	//��ӡ
void List::travel(){
		//�����޸�ͷָ���ֵ
	Node* p = head;
	while(p){
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}
void List::clear(){
	while(head){
		Node* p = head;
		head = head->next;
		delete p;
	}
}

