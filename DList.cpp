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

    
}