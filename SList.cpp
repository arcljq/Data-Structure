// �������cppʵ�֣���Ϊ�꾡��
// ��Դ��Ԭ��ʦר��
// �����꾡��Ӧ����Ŀǰ�ҵõ����������������Ҳ�����Ƚ���ʵ�ְ汾


#include <iostream>
#include <string>

// ����ʹ��typedef�ĺô��Զ��׼���֮��ֻҪ�ı������ int���Ϳ��Խ������������������������͵�����
typedef int ElementType;
// һ����������Ҫ�ܹ�����Ԫ�ؽ���:����/ɾ��/�޸�/��ѯ

class SLListInt {
public:
	SLListInt(); // Ĭ�Ϲ��캯��
	SLListInt(const SLListInt& from);	// ���ƹ��캯��
	// ǧ�������������ˣ���һ������SLListInt���ڲ������� = ���������ϸ�����غ������ݺ�����д
	SLListInt& operator = (const SLListInt& from); 
	~SLListInt(); //	��������

public:
	void print(std::ostream& out);	// ������ӡ����
	// �˴�Ϊ��Ҫ����������Ϊconst
	void push_front(const int& t);	// ���׶˲�������
	void push_back(const int& t);	// ��β�˲�������

	int pop_front(void);	// ɾ���׶�����

	// ���Ǹ�ʲô
	int& front(void);
	// �����Ǹ�ʲô
	const int& front(void) const;
	// ��ʱ����������Ժ�������ʲô�õ�
	int& back(void);
	const int& back(void) const;

	bool exist(const ElementType& e);	// ����ֵe�Ƿ���������
	bool empty(void) const { return m_size == 0; } //	�ж������Ƿ�Ϊ��
	int size(void) const { return m_size; } // ��������Ԫ������
	void clear(void);	// ɾ������Ԫ��
private:
	// �����ڵ�Ķ���
	class SLNode {
		friend class SLListInt; // ������Ԫ��SLListInt����Ҫͨ��public�Ϳ��Է���
	private:
		SLNode();	// Ĭ�Ϲ���
		SLNode(const ElementType& t);	// ��������ʼ������
		~SLNode();
	public:
		ElementType m_data;	// �ڵ�����
		SLNode* m_next;	// �ڵ�ָ��
	};
private:
	void copy(const SLListInt& from);	// ��������
private:
	/* ָ��ͷ�ڵ㣬���洢Ԫ�أ�
		next Ϊ��ָ���ʾû�����һ��Ԫ�أ�Ҳ���ǿ�����
		��������д
	*/
	/* m_head �����򻯴����д���ô󲿷ֱ�����ĳ�Ա����ʵ�ֶ��õ���*/
	SLNode m_head;
	/* β�ڵ��ǰ���ڵ㣬m_tail ������֤push_back �ĳ���ʱ����ɣ�
		��Ҳ��Ҫ���κο��ܻ���m_tail ʧЧ�ĳ�Ա������Ҫȥά��m_tail����Ч��*/
	SLNode m_tail;
	/* ����ǰ�ж��ٸ�Ԫ�أ�m_size ������֤size��Ա�����ĳ���ʱ�����*/
	int m_size;
};


// ��ӡ���Ժ���
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

// main��������Ҫ����Ϊ�ṩ����
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
	// ΪʲôҪ�����������
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

// ���ඨ��ʱֻ��������������ϸ�ĺ�����Ϊ������Ժ���

// ���캯���Լ����������ĳ�ʼ��
// SLNODE�Ĺ��캯������ʼ��ʱnextΪ��ָ��
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
	// �ҵ�������Ľڵ��ǰ���ڵ㣬Ĭ�ϵ�ǰ���ڵ����ͷ�ڵ�
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



