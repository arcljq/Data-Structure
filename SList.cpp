// 单链表的cpp实现，较为详尽版
// 来源：袁老师专栏
// 功能详尽，应该是目前找得到的最完整，最合理也是最先进的实现版本


#include <iostream>
#include <string>

// 这里使用typedef的好处显而易见：之后只要改变这里的 int，就可以将链表改造成适配其他数据类型的链表
typedef int ElementType;
// 一个容器总是要能够对其元素进行:增加/删除/修改/查询

class SLListInt {
public:
	SLListInt(); // 默认构造函数
	SLListInt(const SLListInt& from);	// 复制构造函数
	// 千辛万苦终于理解了，这一步是在SLListInt类内部重载了 = 运算符，详细的重载函数内容后面再写
	SLListInt& operator = (const SLListInt& from); 
	~SLListInt(); //	析构函数

public:
	void print(std::ostream& out);	// 遍历打印函数
	// 此处为何要将参数声明为const
	void push_front(const int& t);	// 在首端插入数据
	void push_back(const int& t);	// 在尾端插入数据

	int pop_front(void);	// 删除首端数据

	// 这是干什么
	int& front(void);
	// 这又是干什么
	const int& front(void) const;
	// 暂时不清楚这两对函数是做什么用的
	int& back(void);
	const int& back(void) const;

	bool exist(const ElementType& e);	// 查找值e是否在链表内
	bool empty(void) const { return m_size == 0; } //	判断链表是否为空
	int size(void) const { return m_size; } // 返回链表元素数量
	void clear(void);	// 删除所有元素
private:
	// 单个节点的定义
	class SLNode {
		friend class SLListInt; // 声明友元，SLListInt不需要通过public就可以访问
	private:
		SLNode();	// 默认构造
		SLNode(const ElementType& t);	// 带参数初始化构造
		~SLNode();
	public:
		ElementType m_data;	// 节点数据
		SLNode* m_next;	// 节点指针
	};
private:
	void copy(const SLListInt& from);	// 拷贝函数
private:
	/* 指向头节点，不存储元素；
		next 为空指针表示没有最后一个元素，也就是空链表；
		方便代码编写
	*/
	/* m_head 用来简化代码编写，让大部分遍历类的成员函数实现都得到简化*/
	SLNode m_head;
	/* 尾节点的前驱节点，m_tail 用来保证push_back 的常数时间完成；
		这也会要求任何可能会让m_tail 失效的成员函数都要去维护m_tail的有效性*/
	SLNode m_tail;
	/* 链表当前有多少个元素，m_size 用来保证size成员函数的常数时间完成*/
	int m_size;
};


// 打印调试函数
void check(bool b) {
	if (b) 
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "NOT PASS" << std::endl;
	}
}

// main函数的主要功能为提供测试
int main() {
	{
		// test empty/size;
		std::cout << "test empty() size()" << std::endl;
		SLListInt slist;
		check(slist.size() == 0);
		check(slist.empty());

		slist.push_back(123);
		check(slist.size() == 1);
		check(slist.empty() == false);

		slist.pop_front();
		check(slist.size() == 0);
		check(slist.empty());
	}
	// 为什么要分两个代码块
	{
		std::cout << "test copy constructor insert/get/" << std::endl;
		SLListInt slist;
		for (int i = 1; i <= 10; i++)
		{
			slist.push_back(i);
		}
		std::cout << "slist: ";
		slist.print(std::cout);
		SLListInt scopy(slist);
		std::cout << "scopy:";
		scopy.print(std::cout);
		std::string s("12345678910");
		std::string spop;
		for (size_t i = 0; i < 10; i++)
			spop.append(std::to_string(scopy.pop_front()));
		check(spop == s);
		check(slist.exist(10));
		check(!slist.exist(11));
		check(!scopy.exist(10));
		check(!scopy.exist(11));

		scopy.clear();
		for (size_t i = 1; i <= 10; i++)
			scopy.push_front(i);
		check(scopy.back() == 1);
		check(scopy.front() == 10);

		spop.clear();
		for (size_t i = 0; i < 10; i++)
			spop.append(std::to_string(scopy.pop_front()));
		check(spop == "10987654321");
	}
	{
		std::cout << "test copy" << std::endl;
		SLListInt slist;
		{
			SLListInt slist2(slist);
		}
		{
			SLListInt slist3;
			slist3 = slist;
		}
		slist.clear();
	}
}

// 在类定义时只需声明函数，详细的函数行为定义可以后置

// 构造函数以及析构函数的初始化
// SLNODE的构造函数，初始化时next为空指针
SLListInt::SLNode::SLNode(): m_next(nullptr){}

SLListInt::SLNode::SLNode(const ElementType& t) : m_next(nullptr), m_data(t){}

SLListInt::SLNode::~SLNode(){ }

SLListInt::SLListInt(): m_size(0) { }

SLListInt::SLListInt(const SLListInt& from) {
	if (!from.empty())
	{
		copy(from);
	}
	std::cout << "SLListInt(const SLListInt & from)\n";
}

SLListInt& SLListInt::operator = (const SLListInt& from) {
	std::cout << "SLListInt & DLList::operator = (const SLListInt &from)\n";
	if (this == &from) {
		return *this;
	}
	else
	{
		copy(from);
		return *this;
	}
}

SLListInt::~SLListInt() {
	std::cout << "~SLListInt()\n";
	clear();
}

void SLListInt::print(std::ostream& out) {
	auto p = m_head.m_next;
	while (p) {
		out << p->m_data << " ";
		p = p->m_next;
	}
	out << std::endl;
}
void SLListInt::push_front(const int& t) {
	auto p = new SLNode(t);
	auto oldFirst = m_head.m_next;
	p->m_next = oldFirst;
	m_head.m_next = p;
	if (m_size == 0)
		m_tail.m_next = p;
	++m_size;
}
void SLListInt::push_back(const int& t) {
	// 找到被插入的节点的前驱节点，默认的前驱节点就是头节点
	m_tail.m_next = new SLNode(t);
	++m_size;
}

int SLListInt::pop_front(void) {
	if (empty())
	{
		throw std::runtime_error("SLListInt::pop_front while list is empty!");
	}
	auto next = m_head.m_next->m_next;
	auto p = m_head.m_next;
	m_head.m_next = next;
	int result = p->m_data;
	delete p;
	if (m_size == 1)
		m_tail.m_next = m_head.m_next;
	--m_size;
	return result;
}

int& SLListInt::front(void) {
	if (empty()) {
		throw std::runtime_error("SLListInt::front called while *this is empty!");
	}
	return m_head.m_next->m_data;
}

int& SLListInt::back(void) {
	if (empty())
	{
		throw std::runtime_error("SLListInt:back called while *this is empty!");
	}
	return m_tail.m_data;
}

const int& SLListInt::back(void) const {
	if (empty())
	{
		throw std::runtime_error("SLListInt:back called while *this is empty!");
	}
	return m_tail.m_data;
}

bool SLListInt::exist(const ElementType& e) {
	auto p = m_head.m_next;
	while (p != nullptr) {
		if (p->m_data == e)
			return true;
		p = p->m_next;
	}
	return false;
}

void SLListInt::clear(void) {
	auto p = m_head.m_next;
	while (p != nullptr) {
		auto next = p->m_next;
		delete p;
		p = next;
	}
	m_head.m_next = m_tail.m_next = nullptr;
	m_size = 0;
}

void SLListInt::copy(const SLListInt& from) {
	clear();
	auto p = from.m_head.m_next;
	for (int i = 0; i < from.m_size; i++)
	{
		push_back(p->m_data);
		p = p->m_next;
	}
}



