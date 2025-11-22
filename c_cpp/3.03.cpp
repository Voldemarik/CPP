#include <cstddef>
#include <iostream>
#include <vector>
#include <numeric>

struct Node
{
    int val;
    Node *next;
};

class List
{
    Node *start, *end;

public:
    List() {start = nullptr, end = nullptr;}
    
    ~List()
    {
        Node *st = start;
        while (st != nullptr)
        {
            auto *temp = st;
            st = st->next;
            delete temp;
        }
    }
    
    bool empty() const {
        return start == nullptr;
    }
    
    void show() const {
        for (Node *st = start; st != nullptr; st = st->next)
        {
            std::cout << st->val << ' ';
        }
        std::cout << '\n';
    }
    
    void push_front(int val)
    {
        if (start == nullptr)
        {
            start = new Node{val, nullptr};
            return; 
        }
        auto temp = new Node{val, start};
        start = temp;
    }
    
    void push_back(int val)
    {
        if (start == nullptr)
        {
            start = new Node{val, nullptr};
            return; 
        }
        else if (end == nullptr){
            end = new Node{val, nullptr};
            start->next = end;
            return;
        }
        auto temp = new Node{val, nullptr};
        end->next = temp;
        end = temp;
    }
    
    void pop_front()
    {
        if (empty()) return;
        
        Node *temp = start;
        start = start->next;
        
        if (start == nullptr) {
            end = nullptr;
        }
        
        delete temp;
    }
    
    void pop_back()
    {
        if (empty()) return;
        
        if (start == end) {
            delete start;
            start = nullptr;
            end = nullptr;
            return;
        }
        
        Node *st = start;
        while (st->next != end) {
            st = st->next;
        }
        
        delete end;
        end = st;
        end->next = nullptr;
    }
    
    int get() const
    {
        if (empty()) {
            return 0;
        }
        
        std::vector<int> arr;
        for (Node *st = start; st != nullptr; st = st->next)
        {
            arr.push_back(st->val);
        }
        return arr[std::midpoint(size_t(0), arr.size())];
    }
};