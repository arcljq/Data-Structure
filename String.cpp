// c++ 复制控制/ c++ 动态内存管理

#include <vecotr>
#include <iostream>
#include <cassert>

using std::cout;
using std::cin;
using std::endl;

class String
{
	friend std::ostream& operator << (std::ostream& out, const String& str);	// 为什么要把该函数声明在外面？
public:
	String();
	String(const char* str);
	String(const String& other);
	~String(void);
	String& operator = (const String& other);
	char* c_str(void) const { return m_data; }
	int size(void) const;
	bool empty(void) const;	// const 关键字

private:
	// std::ostream& Print(std::ostream& other) const;
	char* m_data;
};

void f(const String& s)
{
	std::cout << s << endl;
}

void g(std::vector<String> stringList)
{
	for (auto i : stringList) {
		std::cout<<i<<endl;
	}
}

int main()
{
	std::vector<String> stringList;
	String sEmpty1;
	std::cout << sEmpty1 << std::endl;

	const char* p = "Hello World! ";
	String s(p);
	std::cout << s << std::endl;
	String sEmpty;

	for (size_t i=0; i<2; i++)
	{
		stringList.push_back(s);
		assert(stringList[i].size() == s.size());
	}
	String s1("ni hao ma ?");
	String q(s1);
	s1 = s = s = s1;	// 这啥意思
	cout << s1 << ' ' <<s;
	cout << s;
	cout << s1;
	f(s);
	g(stringList);
	s = s = s1;	// 连等号啥意思
	s = s;
}

String