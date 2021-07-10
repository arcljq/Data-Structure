// 双链表结构
// 来源:袁老师

#include <iostream>
#include <cassert>  // cassert包括了什么内容

class DLListInt{
public:
    DLListInt();
    ~DLListInt();
    DLListInt(const DLListInt& from);
    DLListInt& operator = (const DLListInt& from);
    
    public:
    void push_front(const int& t);
    void push_back(const int& t);
    int pop_front(void);
    int pop_back(void);
    int & front();
    const int& front(void) const;
    int & back();
    const int & back(void) const;
    
    // 基本都是const函数，重新复习相关章节
    bool empty(void) const;
    size_t size(void) const;
    void clear(void);
    
    class iterator;
    // Effects: Removces a single element from the list container
    void erase(iterator i); // i 是一个合法的当前链表的迭代器，并指向一个具体的节点
    // Effects: inserts datum before the element at the specified position.
    void insert(iterator i, const int& datum);
public:
    iterator begin() const noexcept;
    iterator begin() noexcept;
    iterator end() const noexcept;
    iterator end() noexcept;

public: // 迭代器
    class Node;
    class iterator{
        friend class DLListInt;
        friend bool operator == (const typename iterator& lhs, const typename iterator& rhs) {
            return lhs.m_hold == rhs.m_hold;
        }
        friend bool operator != (const iterator& lhs, const iterator& rhs) { 
            return lhs.m_hold != rhs.m_hold; 
        }
    public: 
        iterator(void): m_hold(nullptr){}
        iterator & operator++();    // 用于前置形式
        int& operator*(void) { return this->m_hold->m_data; }
    private:
        Node* m_hold;
    };    
private:
    class Node{
        friend class DLListInt;
    private:
        Node();
        Node(const int& t);
        ~Node();
    private:
        Node* m_prev;
        int m_data;
        Node* m_next;
    };
    void copy(const DLListInt& from);
private:  
    Node* m_first;  // 无单独的头节点，空链表这个指针就指向空指针
    Node* m_last;  // 指向最后一个元素，空指针代表没有最后一个元素，也就是空链表
    size_t m_size;  // 当前有多少个元素
};

#include <string>
#include <algorithm>
void print (const DLListInt& list, const std::string& msg){
    std::cout << "print" << msg << ":";
    for (auto itr = list.begin(); itr != list.end(); ++itr){
        std::cout << *itr << " ";
    }
    std::cout << "\n";
}

// 打印函数
void print(const DLListInt& list, const std::string& msg) {
    std:: cout << "print" << msg<< ":";
    for (auto itr = list.begin(); itr!=list.end(); ++itr){
        std::cout << *itr << " ";
    }
    std::cout << "\n";
}
// 测试函数
void check(bool b){
    if(b){
        std:: cout << "Pass" << std::endl;
    }
    else{
        std::cout << "NOT PASS" << std::endl;
    }
}

int main(){
    {
        // test empty/size;
        std:: cout << "test empty() size()" << std::endl;
        DLListInt slist;
        check(slist.size() == 0);
        check(slist.empty());

        slist.push_back(123);
        check(slist.size() == 1);
        check(slist.empty() == false);
        
        slist.pop_front();
        check(slist.size() == 0);
        check(slist.empty());
    }
    {
        std::cout << "test copy consructor insert/get/" << std::endl;
        DLListInt slist;
        for (auto i=1; i <=10; i++){
            slist.push_back(i);
        }
        print(slist,"slist: ");
        DLListInt scopy(slist);
        print(scopy, "scopy:");
        std::string s("12345678910");
        std::string spop;
        for (size_t i = 0; i < 10; i++){
            spop.append(std::to_string(scopy.pop_front()));
        }
        check(spop == s);
        // 检查10是否在slist中
        check(std::find(slist.begin(), slist.end(), 10) != slist.end());
        // 检测11是否在slist中
        check(std::find(slist.begin(), slist.end(), 11) == slist.end());
        // 检测10是否在scopy中
        check(std::find(slist.begin(), slist.end(), 10) == slist.end());
        // 检测11是否在scopy中
        check(std::find(slist.begin(), slist.end(), 11) == slist.end());

        scopy.clear();
        for (size_t i =1; i <=10; i++){
            scopy.push_front(i);
        }
        check(scopy.back() == 1);
        check(scopy.front()== 10);

        spop.clear();
        for (size_t i = 0; i<10; i++){
            spop.append(std::to_string(scopy.pop_front()));
        }
        check(spop == "10987654321");
    }
    {
        std::cout << "test copy" << std::endl;
        DLListInt slist;
        {
            DLListInt slist2(slist);
        }
        {
            DLListInt slist3;
            slist3 = slist;
        }
        slist.clear();
    }
    {
        // test front
        DLListInt list1;
        list1.push_front(2);
        assert(list1.front() == 2);
        assert(list1.back() == 2);
        list1.push_front(1);
        assert(list1.front() == 1);
        assert(list1.back() == 2);
        assert(list1.size()==2);
        list1.pop_back();
        assert(list1.size() == 0);
        assert(list1.empty() == true);
    }
    {
        // test pop_front
        DLListInt list1;
        list1.push_front(2);
        assert(list1.front() == 2);
        assert(list1.back() == 2);
        assert(list1.size() == 1);
        list1.push_back(1);
        assert(list1.front() == 2);
        assert(list1.back() == 1);
        assert(list1.size() == 2);
        {
            auto t2 = (list1.front() ==1);
            assert(t2 == 1);
        }
        assert(list1.front() == 1);
        assert(list1.back() == 1);
        assert(list1.size() == 1);
        {
            auto t2 = list1.pop_front();
            assert(t2 == 1);
        }
        assert(list1.size() == 0);
        assert(list1.empty() == true);
    }
    {
        // test erase;
        DLListInt list1;
        list1.push_front(1);
        list1.push_back(2);
        list1.push_back(3);
        list1.push_back(4);
        list1.push_back(5);
        auto i = list1.begin();
        print(list1, "total");
        list1.erase(i);
        print(list1,"erase 1");
        assert(*list1.begin() == 2);
        i = list1.begin();
        ++i;
        list1.erase(i);
        print(list1, "erase 3");
        i = list1.begin();
        ++i;
        ++i;    // 5
        list1.erase(i);
        print(list1, "erase 5");
    }
    {
        // test insert
        DLListInt list1;
        list1.push_front(1);
        list1.push_back(2);
        list1.push_back(3);
        list1.push_back(4);
        list1.push_back(5);
        {
            auto itr = list1.begin();
            print(list1, "total");
            list1.insert(itr, 0);
            print(list1, "0 1 2 3 4 5");
        }
        {
            auto itr = list1.begin();
            for (int i = 0; i < list1.size(); i++){
                ++itr;
            }
            assert(itr == list1.end());
        }
        {
            auto list2 = list1;
            auto itr = list2.begin();
            list2.erase(++itr); // erase 1
            list2.insert(++list2.begin(),1);
            auto itrOld = list1.begin();
            for (auto itr = list2.begin(); itr != list2.end(); ++itr, ++itrOld){
                assert(*itr == *itrOld);
            }
            print(list1, "list1");
            print(list2, "list2");
        }
    }
}

DLListInt::DLListInt():m_first(nullptr), m_last(nullptr), m_size(0){
    std::cout << "DLListInt()\n";
}

DLListInt::~DLListInt(){
    clear();
    std::cout << "~DLListInt()\n";
}

void DLListInt::copy(const DLListInt& from){
    clear();
    for (auto itr : from){
        push_back(itr);
    }
}
DLListInt & DLListInt::operator=(const DLListInt & from){
    if (this == &from){
        std::cout << "DLListInt & DLListInt::operator=(const DLListInt & from)\n";
        return *this;
    }
    else
    {
        copy(from);
        std::cout << "DLListInt & DLListInt::operator=(const DLListInt & from)\n";
        return *this;
    }
}

bool DLListInt::empty(void) const{
    return m_size == 0;
}

size_t DLListInt::size(void) const{
    return m_size;
}

int & DLListInt::front(){
    return this->m_first->m_data;
}

const int & DLListInt::front(void) const{
    return this->m_first->m_data;
}

void DLListInt::push_front(const int & t){
    auto p = new Node(t);
    if(empty()){
        this->m_first = this->m_last = p
    }
    else {
        p->m_next = this->m_first;
        this->m_first->m_prev = p;
        m_first = p;
    }
    ++this->m_size;
}

int DLListInt::pop_front(void){
    if (m_size == 0){
        

    }
}