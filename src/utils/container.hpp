/*
 * Copyright 2023, Brandon Chaney
 */

#pragma once
#include <cstdint>
#include <exception>
#include <iostream>

template <typename T>
struct Node {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;

    value_type data;
    Node<T> *next;
    Node<T> *prev;

    explicit Node(value_type data) : data(data), next(nullptr), prev(nullptr) {}

    ~Node() = default;
};

template <typename T>
class Stack {
 private:
    using node_type = Node<T>;
    using node_pointer = Node<T> *;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;

    node_pointer _head = nullptr;
    uint32_t _size = 0;

 public:
    Stack() = default;

    ~Stack() {
        while (_head) {
            pop();
        }
    }

    Stack(const Stack &other) {
        node_pointer current_node = other._head;
        while (current_node) {
            push(current_node->data);
            current_node = current_node->next;
        }
    }

    /// @brief adds a new value to the end of the stack.
    /// @tparam T type of parameter.
    /// @param value the value being added to the stack.
    void push(const T &value) {
        node_pointer new_node{new Node(value)};
        if (!_head) {
            _head = new_node;
        } else {
            new_node->next = _head;
            _head = new_node;
        }

        _size++;
    }

    /// @brief returns and removes the last value of the stack.
    /// @tparam T type of parameter.
    /// @return the value at the top of the stack. Throws an exception when
    /// the stack is empty.
    value_type pop() {
        if (!_head) throw std::exception();
        value_type data{_head->data};
        node_pointer old_node = _head;
        _head = _head->next;
        old_node->~Node();
        _size--;
        return data;
    }

    ///
    /// @brief Returns true when the stack is empty.
    /// @tparam T the type of values in the stack.
    /// @return
    bool is_empty() { return _head == nullptr; }

    /// @brief Returns the number of elements in the stack.
    /// @tparam T the type of elements in the stack.
    /// @return
    uint32_t size() { return _size; }
};

template <typename T>
class Queue {
 private:
    using node_type = Node<T>;
    using node_pointer = node_type *;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;

    node_pointer _head;
    node_pointer _tail;
    size_t _size;

 public:
    Queue() = default;

    /// @brief Queue<T> destructor.
    /// @tparam T
    ~Queue() {
        // Iteritively delete each node in Queue.
        while (_head) {
            node_pointer curr{_head};
            _head = _head->next;
            curr->~Node();
        }
    }

    /// @brief The copy constructor for Queue<T>. Creates new instance of
    /// Queue<T> with copies of the same elements in the same order.
    /// @tparam T
    /// @param other
    Queue(const Queue<T> &other) {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;

        node_pointer curr_node = other._head;
        while (curr_node) {
            enqueue(curr_node->data);
            curr_node = curr_node->next;
        }
    }

    /// @brief Assignment operator for Queue<T>.
    /// @tparam T
    /// @param other
    /// @return
    Queue<value_type> &operator=(const Queue<value_type> &other) {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;

        node_pointer curr_node{other._head};
        while (curr_node) {
            enqueue(curr_node->data);
            curr_node = curr_node->next;
        }
        return *this;
    }

    /// @brief Adds new element to the end of the queue.
    /// @tparam T type of elements in the queue.
    /// @param data value being added to the queue.
    void enqueue(value_type data) {
        node_pointer new_node{new Node<T>(data)};

        // Queue is empty
        if (_head == nullptr) {
            _head = new_node;
            _tail = _head;
        } else {
            // add new nodes to the tail of the list
            _tail->next = new_node;
            new_node->prev = _tail;
            _tail = new_node;
        }
        _size++;
    }

    /// @brief Returns and removes the front element of the queue.
    /// @tparam T value type of elements in the queue.
    /// @return front element of the queue.

    value_type dequeue() {
        node_pointer node{_head};

        // one node remaining
        if (_head == _tail) {
            _head = _tail = nullptr;
        } else {
            _head = _head->next;
            _head->prev = nullptr;
        }
        value_type data{node->data};
        node->~Node();
        _size--;
        return data;
    }

    /// @brief Returns the number of elements in the queue.
    /// @tparam T the type of elements in the queue.
    /// @return
    size_t size() { return _size; }

    /// @brief Returns a pointer to an array with a copy of the queue's contents
    /// @return a pointer to a new array. The caller gets ownership of this
    /// array.
    value_type *to_array() {
        // if size is 0, return a nullptr
        if (size() == 0) return nullptr;

        // make a new array of the contained type
        value_type *arr{new value_type[size()]};
        node_pointer curr_node{_head};
        unsigned int i{0};
        while (curr_node) {
            if (i == size()) break;
            arr[i++] = curr_node->data;
            curr_node = curr_node->next;
        }
        return arr;
    }

    /// @brief ostream operator overloaded to support printing of Queue<T>
    /// objects.
    /// @tparam T type of elements in the queue.
    /// @param os an ostream.
    /// @param q a Queue<T>.
    /// @return os.
    friend std::ostream &operator<<(std::ostream &os, Queue<T> &q) {
        Node<T> *current = q._head;
        while (current) {
            os << current->data << std::endl;
            current = current->next;
        }
        return os;
    }
};

template <typename T>
class ArrayList {
    using value_type = T;
    using pointer_type = T *;

    size_t _size;
    size_t _max_size;

 public:
    pointer_type _arr;
    ArrayList() = default;

    explicit ArrayList(int n) {
        _arr = new value_type[n];
        _size = 0;
        _max_size = n;
    }

    ~ArrayList() { delete[] _arr; }

    value_type operator[](int i) const {
        if (i < 0 || i >= static_cast<int>(_size)) {
            throw std::exception();
        }
        return _arr[i];
    }

    void insert(int i, value_type value) {
        if (i > static_cast<int>(_size)) throw std::exception();
        if (_size < _max_size) {
            _size++;
        } else if (i == static_cast<int>(_size)) {
            return;  // if list is full and attempts to insert to the end
        }
        for (int j = _size - 1; j > i; j--) {
            _arr[j] = _arr[j - 1];
        }
        _arr[i] = value;
    }

    size_t size() { return _size; }

    size_t max_size() { return _max_size; }
};
