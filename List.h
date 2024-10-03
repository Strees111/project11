#ifndef List_H
#define List_H

#include <iostream>

template<typename T>
class List {
private:
    struct Node {
        Node *next;
        T data;
    };
    Node *head;
    Node *tail;
    int sz;
public:
    List();

    List(const List &other);

    ~List();

    void push_back(T data);

    void pop_front();

    void pop_back();

    void push_front(T data);

    void insert(int index, T data);

    void removeAt(int index);

    void clear();

    int size() const { return sz; };

    T &operator[](int index) const;

    List<T> operator=(const List &other);

    friend class DataBase;
};

template<typename T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node{nullptr, data};
        tail = head;
    } else {
        Node *p = new Node{nullptr, data};
        tail->next = p;
        tail = tail->next;
    }
    ++sz;
}

template<typename T>
List<T>::List():  head(nullptr),tail(nullptr),sz(0) {}

template<typename T>
List<T>::List(const List &other): head(nullptr),tail(nullptr),sz(other.sz) {
    Node *p = other.head;
    while (p != nullptr) {
        push_back(p->data);
        p = p->next;
    }
}

template<typename T>
List<T> List<T>::operator=(const List &other) {
    if (this != &other) {
        clear();
        sz = other.sz;
        Node *p = other.head;
        while (p != nullptr) {
            push_back(p->data);
            p = p->next;
        }
    }
    return *this;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
T &List<T>::operator[](int index) const {
    int counter = 0;
    Node *current = this->head;
    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->next;
        ++counter;
    }
}

template<typename T>
void List<T>::pop_front() {
    Node *temp = head;
    head = head->next;
    delete temp;
    --sz;
}

template<typename T>
void List<T>::clear() {
    while (sz) {
        pop_front();
    }
}

template<typename T>
void List<T>::push_front(T data) {
    head = new Node{head, data};
    ++sz;
}

template<typename T>
void List<T>::insert(int index, T data) {
    if (index == 0) {
        push_front(data);
    } else {
        Node *previous = this->head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->next;
        }
        Node *newNode = new Node{previous->next, data};
        previous->next = newNode;
        ++sz;
    }
}

template<typename T>
void List<T>::removeAt(int index) {
    if (index == 0) {
        pop_front();
    } else {
        Node *previous = this->head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->next;
        }
        Node *DlNode = previous->next;
        previous->next = DlNode->next;
        delete DlNode;
        --sz;
    }
}

template<typename T>
void List<T>::pop_back() {
    removeAt(sz - 1);
}

#endif // List_H