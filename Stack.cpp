#include <iostream>
#include <iomanip>

class CStack{
public:
	CStack(void);
	CStack(const CStack& _stack);
	CStack& operator=(const CStack& _stack);
	~CStack(void);

public:
	inline const T& top(void) const;
	inline bool empty(void) const;
	inline size_t size(void) const;
	void push(const T& _item);
	void pop(void);
	void clear(void);
private:
	void copy(const CStakck& stack1);
private:
	struct CStackitem
	{
	public:
		CStackitem(void);
		CStackitem(const T& _data)
	}	

}