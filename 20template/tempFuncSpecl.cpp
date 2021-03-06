/*函数模板的特殊化*/
/*在编写通用方法的时候，我们最好使用 "<"来进行比较
 *因为，大部分自定义类型都重载了小于号
 *函数模板也可以有特化函数模板和偏特化函数模板
 */
#include <iostream>
#include <cstring>
using namespace std;
template<typename T>
void insertSort(T* a,int n)
{
	for(int i=1;i<n;++i){
		T x=a[i];
		int j;
		for(j=i;j>0&&x<a[j-1];--j)    //一般情况下只重载小于号
			a[j]=a[j-1];
		a[j]=x;
	}
}
/*对C风格的字符串特殊化排序方法*/
template<>
void insertSort<char* >(char** a,int n)
{
	for(int i=1;i<n;++i){
		char x[20];
		strcpy(x,a[i]);
		int j;
		for(j=i;j>0&&x<a[j-1];--j)    //一般情况下只重载小于号
			strcpy(a[j],a[j-1]);
		strcpy(a[j],x);
	}
}
template<typename T>
void print(T* a,int n)
{
	for(int i=0;i<n;++i)
		cout<<a[i]<<" ";
	cout<<endl;
}

class Emp{
private:
	string name;
	int age;
public:
	Emp(string name,int age):name(name),age(age){}
	friend ostream& operator<<(ostream& os,const Emp& e)
		{
			return os<<e.name<<" "<<e.age;	
		}
	friend bool operator <(const Emp& one,const Emp& two)
		{
			return one.age<two.age;
		}
};

int main()
{
	int a[10]={12,3,4,66,7,89,4,22,56,23};
	insertSort<int>(a,10);
	print(a,10);
	double b[6]={11.23,12.44,87.32,1.24,5.68,3.35};
	insertSort(b,6);
	print(b,6);
	
	Emp ee[3]={
		{"winlin",12},
		{"wangh",24},
		{"hang",32}
	};
	insertSort(ee,3);
	print(ee,3);
	
        return 0;    
}
