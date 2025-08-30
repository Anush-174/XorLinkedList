#pragma once

#include <cstdint> //uintptr_t
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class XORLinkedList {
private:
    struct Node {
        T m_val;
        Node* m_both{};
    };
    class Iterator;
    class ReverseIterator;
public:

    XORLinkedList() = default;
    XORLinkedList(const XORLinkedList& other);
    XORLinkedList& operator=(const XORLinkedList& rhs);
    XORLinkedList(XORLinkedList&& other) noexcept;
    XORLinkedList& operator=(XORLinkedList&& rhs) noexcept;
    ~XORLinkedList();

    void clear();

    Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

    std::size_t getSize() const;

    T front() const;
    T back() const;
    bool empty() const;


    // Modifiers
    void push_back(T val);
    void push_front(T val);
    void pop_back();
    void pop_front();
    void insert(T val, size_t pos);
    void erase(size_t pos);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const XORLinkedList<U>& list);
    static Node* XOR(Node* a, Node* b);

private:
    class Iterator {
        public:
        using NodeType = Node;
        
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator(NodeType* curr, NodeType* prev);

        reference operator*();
        pointer operator->();

        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);

    private:
        NodeType* m_node;
        NodeType* m_prev;
    };  
    
    // Reverse iterator
    class ReverseIterator {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        ReverseIterator(Node* curr = nullptr, Node* next = nullptr);

        reference operator*();
        pointer operator->();

        ReverseIterator& operator++();    // move backward in list
        ReverseIterator operator++(int);
        ReverseIterator& operator--();    // move forward in list
        ReverseIterator operator--(int);

        bool operator==(const ReverseIterator& other) const;
        bool operator!=(const ReverseIterator& other) const;

    private:
        Node* m_node;
        Node* m_next;
    };
private:
    Node* m_head{};
    Node* m_tail{};
    std::size_t m_size{};
};

#include "xorLL.tpp"