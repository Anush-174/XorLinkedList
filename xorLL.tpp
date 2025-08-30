#include"xorLL.hpp"

//XORLinkedList functions
template<typename T>
XORLinkedList<T>::XORLinkedList(const XORLinkedList& other) : m_head{other.m_head},
                                         m_tail{other.m_tail}, m_size{other.m_size}
{
    for (Node* curr = other.m_head, *prev = nullptr; curr != nullptr;) {
        this->push_back(curr->m_val);
        XORLinkedList<T>::Node* next = XOR(curr->m_both, prev);
        prev = curr;
        curr = next;
    }
}

template<typename T>
XORLinkedList<T>& XORLinkedList<T>::operator=(const XORLinkedList& rhs) {
    if (this != &rhs) {
        this->clear();

        for (Node* curr = rhs.m_head, *prev = nullptr; curr != nullptr;) {
            this->push_back(curr->m_val);
            Node* next = XOR(curr->m_both, prev);
            prev = curr;
            curr = next;
        }   
    }

    return *this;
}

template<typename T>
XORLinkedList<T>::XORLinkedList(XORLinkedList<T>&& other) noexcept 
        : m_head{other.m_head}, m_tail{other.m_tail}, m_size{other.m_size}
{
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}


template<typename T>
XORLinkedList<T>& XORLinkedList<T>::operator=(XORLinkedList&& rhs) noexcept
{
    if (this != &rhs) {
        this->clear();
        m_head = rhs.m_head;
        m_tail = rhs.m_tail;
        m_size = rhs.m_size;

        rhs.m_head = rhs.m_tail = nullptr;
        rhs.m_size = 0;
    }

    return *this;
}

template<typename T>
XORLinkedList<T>::~XORLinkedList()
{
    clear();
}

template<typename T>
void XORLinkedList<T>::clear() 
{
    for (Node* curr{m_head}, *prev{nullptr}; curr != nullptr;) {
        Node* next = XOR(curr->m_both, prev);
        prev = curr;
        delete curr;
        curr = next;
    }

    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template<typename T>
std::size_t XORLinkedList<T>::getSize() const {
    return m_size;
}

template<typename T>
T XORLinkedList<T>::front() const {
    if (m_head) {
        return m_head->m_val;
    }

    throw std::out_of_range("XORLinkedList is empty.");
}

template<typename T>
T XORLinkedList<T>::back() const {
    if (m_tail) {
        return m_tail->m_val;
    } 
    throw std::out_of_range("XORLinkedList is empty.");
}
template<typename T>
bool XORLinkedList<T>::empty() const {
    return m_size == 0;
}


//Modifiers
template<typename T>
void XORLinkedList<T>::push_back(T val)
{
    Node* newNode = new Node{val};
    if (m_head == nullptr) {
        m_head = m_tail = newNode;
        newNode->m_both = nullptr;
    } else {
        newNode->m_both = XOR(m_tail, nullptr);
        m_tail->m_both = XOR(m_tail->m_both, newNode);
        m_tail = newNode;
    }
    ++m_size; 
}

template<typename T>
void XORLinkedList<T>::push_front(T val)
{
    if (m_head == nullptr) {
        push_back(val);
        return;
    }

    Node* newNode = new Node{val};
    newNode->m_both = XOR(m_head,nullptr);
    
    m_head->m_both = XOR(m_head->m_both, newNode);
    m_head = newNode;
    ++m_size;
}

template<typename T>
void XORLinkedList<T>::pop_back()
{
    if (m_head == nullptr) {
	    throw std::out_of_range("XORLinkedList is empty.");
	}

    if (m_head == m_tail) {
        delete m_head;
        m_head = m_tail = nullptr;
    }
    else {
        Node* prev = XOR(m_tail->m_both, nullptr);
        prev->m_both = XOR(XOR(prev->m_both, m_tail), nullptr);
        delete m_tail;
        m_tail = prev;
    }
    --m_size;
}

template<typename T>
void XORLinkedList<T>::pop_front()
{
    if (m_head == nullptr) {
		throw std::out_of_range("XORLinkedList is empty.");
	}

    if (m_head == m_tail) {
        delete m_head;
        m_head = m_tail = nullptr;
    } else {
        Node* next = XOR(m_head->m_both, nullptr);
        next->m_both = XOR(nullptr, XOR(m_head, next->m_both));
        delete m_head;
        m_head = next;
    }
    --m_size;
}

template<typename T>
void XORLinkedList<T>::insert(T val, size_t pos)
{
    if (pos > m_size) {
		throw std::out_of_range("Index out of range");
	}

    if (pos == 0) {
        push_front(val);
        return;
    }
    
    if (pos == m_size) {
        push_back(val);
        return;
    }

    Node* curr {m_head};
    Node* prev{nullptr};
    while (curr && pos--) {
        Node* next = XOR(prev, curr->m_both);
        prev = curr;
        curr = next;
    }

    Node* newNode = new Node{val};
    prev->m_both = XOR(XOR(prev->m_both, curr),newNode);
    newNode->m_both = XOR(prev, curr);
    curr->m_both = XOR(newNode, XOR(curr->m_both, prev));
    ++m_size;
    
}

template<typename T>
void XORLinkedList<T>::erase(size_t pos)
{
    if (pos > m_size) {
		throw std::out_of_range("Index out of range");
	}

    if (pos == 0) {
        pop_front();
        return;
    }
    
    if (pos == m_size - 1) {
        pop_back();
        return;
    }

    Node* prev{nullptr};
    Node* curr{m_head};

    while (curr && pos--) {
        Node* next = XOR(prev, curr->m_both);
        prev = curr;
        curr = next;
    }
    
    Node* next = XOR(prev, curr->m_both);
    prev->m_both = XOR(XOR(prev->m_both, curr), next);
    next->m_both = XOR(prev, XOR(curr, next->m_both));
    delete curr;
    --m_size;
}

template<typename T>
typename XORLinkedList<T>::Node* XORLinkedList<T>::XOR(XORLinkedList<T>::Node* a, XORLinkedList<T>::Node* b) 
{
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const XORLinkedList<T>& list)
{
    if (!list.m_head) {
        os << "List is empty!";
        return os;
    }

    typename XORLinkedList<T>::Node* curr{list.m_head};
    typename XORLinkedList<T>::Node* prev{nullptr};
    typename XORLinkedList<T>::Node* next = XORLinkedList<T>::XOR(prev, curr->m_both);

    while (curr) {
        os << curr->m_val << " -> ";
        next = XORLinkedList<T>::XOR(prev, curr->m_both);
        prev = curr;
        curr = next;
    }
    os << "X";
    return os;
}


// begin and end implementations
template<typename T>
typename XORLinkedList<T>::Iterator XORLinkedList<T>::begin() {
    return Iterator{m_head, nullptr};
}

template<typename T>
typename XORLinkedList<T>::Iterator XORLinkedList<T>::end() {
    return Iterator{nullptr, m_tail};
}

// rbegin and rend implementations
template <typename T>
typename XORLinkedList<T>::ReverseIterator XORLinkedList<T>::rbegin() {
    return ReverseIterator(m_tail, nullptr);
}

template <typename T>
typename XORLinkedList<T>::ReverseIterator XORLinkedList<T>::rend() {
    return ReverseIterator(nullptr, m_head);

}

// Implementation for Iterator
template <typename T>
XORLinkedList<T>::Iterator::Iterator(Iterator::NodeType* node, Iterator::NodeType* prev) 
                                                            : m_node{node}, m_prev{prev}{}


template<typename T>
typename XORLinkedList<T>::Iterator::reference XORLinkedList<T>::Iterator::operator*() 
{
    return this->m_node->m_val;
}


template<typename T>
typename XORLinkedList<T>::Iterator::pointer XORLinkedList<T>::Iterator::operator->()
{
    return &this->m_node->m_val;
}

template<typename T>
typename XORLinkedList<T>::Iterator& XORLinkedList<T>::Iterator::operator++()
{
    if (m_node == nullptr) {
        throw std::out_of_range("Incrementing the end iterator is undefined behavior");
    }
    NodeType* next = XOR(m_node->m_both, m_prev);
    m_prev = m_node;
    m_node = next;

    return *this;
}

template<typename T>
typename XORLinkedList<T>::Iterator XORLinkedList<T>::Iterator::operator++(int)
{
    Iterator tmp{*this};
    ++(*this);

    return tmp; 
}

template<typename T>
typename XORLinkedList<T>::Iterator& XORLinkedList<T>::Iterator::operator--()
{
    if (m_prev == nullptr) {
        throw std::out_of_range("Decrementing the begin iterator is undefined behavior");
    }

    NodeType* prevPrev = XOR(m_prev->m_both, this->m_node);
    m_node = m_prev;
    m_prev = prevPrev;
    return *this;
}

template<typename T>
typename XORLinkedList<T>::Iterator XORLinkedList<T>::Iterator::operator--(int)
{
    XORLinkedList<T>::Iterator tmp{*this};
    --(*this);

    return tmp;
}


template<typename T>
bool XORLinkedList<T>::Iterator::operator==(const Iterator& other)
{
    return this->m_node == other.m_node;
}

template<typename T>
bool XORLinkedList<T>::Iterator::operator!=(const Iterator& other)
{
    return !(*this == other);
}


// Implementation for ReverseIterator

template <typename T>
XORLinkedList<T>::ReverseIterator::ReverseIterator(Node* curr, Node* next)
    : m_node(curr), m_next(next) {}

template <typename T>
typename XORLinkedList<T>::ReverseIterator::reference
XORLinkedList<T>::ReverseIterator::operator*() {
    return m_node->m_val;
}

template <typename T>
typename XORLinkedList<T>::ReverseIterator::pointer
XORLinkedList<T>::ReverseIterator::operator->() {
    return &(m_node->m_val);
}

// ++rit moves backward (toward head)
template <typename T>
typename XORLinkedList<T>::ReverseIterator& XORLinkedList<T>::ReverseIterator::operator++() {
    Node* prev = m_node;
    m_node = m_next;
    if (m_node != nullptr)
        m_next = XOR(prev, m_node->m_both);
    return *this;
}

template <typename T>
typename XORLinkedList<T>::ReverseIterator XORLinkedList<T>::ReverseIterator::operator++(int) {
    ReverseIterator tmp = *this;
    ++(*this);
    return tmp;
}

// --rit moves forward (toward tail)
template <typename T>
typename XORLinkedList<T>::ReverseIterator& XORLinkedList<T>::ReverseIterator::operator--() {
    Node* next = m_node;
    m_node = XOR(m_next, m_node->m_both);
    m_next = next;
    return *this;
}

template <typename T>
typename XORLinkedList<T>::ReverseIterator XORLinkedList<T>::ReverseIterator::operator--(int) {
    ReverseIterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool XORLinkedList<T>::ReverseIterator::operator==(const ReverseIterator& other) const {
    return m_node == other.m_node && m_next == other.m_next;
}

template <typename T>
bool XORLinkedList<T>::ReverseIterator::operator!=(const ReverseIterator& other) const {
    return !(*this == other);
}