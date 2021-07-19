//	 move example
#include <utility>	// std::move
#include <iostream>	// std::std:;cout
#include <vector>	// std::vector
#include <string>	// std::string

class String
{
	friend std::ostream& operator<<(std::ostream& os, const String& str);
public:
	String(void);
	String(const char* data, int length);
	String(const char* data);

	String(const String& from);	//1 复制构造
	String& operator = (const String& from);	// 2 赋值操作符

	~String();	// 3 析构函数

	String(String&& from);	// 4 移动构造
	String& operator = (String&& from);	// 5 移动赋值操作符
}
