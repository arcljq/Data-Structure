#include <iostream>

using namespace std;

struct List {
    int val;
    struct List* next;
};

void Init (struct List* L) {    // 创建链表 // 不是很看得明白
    int cur;
    cin >> cur;
    while (cur!=-1){
        struct List * ptr = (struct List* )malloc(sizeof(struct List));
        ptr->val = cur;
        ptr->next = NULL;
        L->next = ptr;
        L = L ->next;
        cin >> cur;
    }
}

void Show(struct List* L){  // 遍历链表
    cout << "遍历链表：";
        
    while (L->next) {
        cout << L->next -> val << " "; // 打印L的下一个节点的值
        L = L ->next;   // 指向L的下一个节点
        // L的值并没有打印，是否是说L作为头节点本身是空的。
    }
}
    
void InsertList (strcut List*L, int k, int data){
    strcut List* pre = NULL; // 存储第K-1个元素的值
    struct List* ptr = (struct List*)malloc(sizeof(struct List));   // 申请空间
    ptr->val =data;
    ptr->next = NULL;

    while (k && L-> next) { // 查找到放置data元素的位置
    // 这个判别条件保证了两点 1.找到k 2. 链表结束前若没找到，停在最后一个元素
    // 详细来说，即是从表头开始，往后走K步，使得pre刚好指向第k-1个元素，L指向第k个元素
    pre = L;
    L = L->next;
    k--;   
    }

    if (k>0){   // 如果K >0, 直接插到链表的表尾
    L->next= ptr;
    L=L->next;
    }else{
        pre->next = ptr;    // 链接链表
        ptr->next = L
    }
}

int lengthList (struct List *L) {   // 链表求长度
    int len=0;
    while (L->next){
        len ++
        L=L->next;
    }
    return len;
}

void DeleteList_by_value (struct List*L, int x) {    // 删除值为x的节点 （链表无重复值）// 删除第k个节点同理
    if (lengthList(L) <= 0 ) {
        cout << "表空，没有元素可删除" << endl;
        return;
    }

    struct List* ptr = L ->next;
    struct List* pre = L;   // 记录ptr的前一个位置的节点
    while (ptr) {
        if (ptr->val == x) {
            pre->next = ptr -> next;
            free(ptr);  // 释放空间
            return; // 操作成功后跳出循环
        }
        // 没找到目标值，一对操作子各自往下移动一个位置
        pre = ptr;
        ptr = pre ->next;
    }
}

void DeleteList_by_Position(struct List*L, int k) { // 删除第K个位置的节点
    if (lengthList(L)<=0){
        cout << "List is empty!";
        return;     // jump out form the loop
    }

    // 一对操作子
    struct List* ptr = L->next;
    struct List* pre = L;
    // 不是很明白这一部分写的，如果k = 1， 那么应该是对的?头节点本身不存储
    // k = k -1;  // 因为如果 k =1, 直接用pre-> next = ptr->next就把ptr删掉了，所以要减1
    // 这还不如--k呢 。。。。
    while (--k && ptr){
        pte = ptr;
        ptr= ptr ->next;
    }
    if (ptr == NULL || k>0){
        cout << "要删除的位置不存在" << endl;
    }else{
        pre -> next = ptr ->next; // 删除ptr节点
        free(ptr); // 释放空间
    }
}

bool IsEmptyList(struct List* L) {
    if(L->next ==NULL){
        return true;
    }else {
        return false;
    }
}

int GetElemList(struct List* L, int i){
    struct List* ptr = L;
    int k = i;  // 标记i的值，以防不存在输出显示
    while (i >0 && ptr->next) {
        ptr = ptr->next;
        i--;
    }

    if (i == 0 && ptr != NULL) {    // 当 i==0 和 ptr 不为空代表找到了第i个位置的元素
        return ptr->val;
    }else{
        cout << "第" << k << "个位置不存在" << endl;
        return -1;
    }
}

void ClearList(struct List* L){ // 清空链表
    struct List* ptr = L;
    if (lengthList(L)>0) {  // 在链表长度范围内
        while (ptr->next) {
            // 这多一个temp变量只是为了释放空间吗，看上去有点不那么优雅
            struct List *temp = ptr->next; // 其实可以直接携程 auto temp = ptr->next 现在的编译器已经很聪明了
            ptr->next = ptr->next->next;    // ptr->next 节点从链表中被剔除
            free(temp); // 释放空间
        }
        // 最后效果是只剩一个头节点
    }
}


