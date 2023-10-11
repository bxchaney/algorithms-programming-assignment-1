/*
 * Copyright 2023, Brandon Chaney
 */

#pragma once
#include <cstdint>
#include <exception>
#include <iostream>

template <typename T>
class ArrayQueue {
    using value_type = T;
    using value_pointer = T *;

    size_t _size;
    value_pointer _arr;
    size_t _max_size;
    int _front;

    void resize(int n) {
        value_pointer new_arr{new value_type[n]};
        for (int i = 0; i < static_cast<int>(_size); i++) {
            new_arr[i] = _arr[(_front + i) % _max_size];
        }

        _max_size = n;
        _front = 0;
        value_pointer old_arr{_arr};
        _arr = new_arr;
        delete[] old_arr;
    }

 public:
    ArrayQueue() {
        // default allocated space is 20
        _arr = new value_type[20];
        _size = 0;
        _max_size = 20;
    }

    explicit ArrayQueue(int n) {
        // may specify a different starting allocation
        _arr = new value_type[n];
        _size = 0;
        _max_size = n;
    }

    ~ArrayQueue() { delete[] _arr; }

    void enqueue(value_type data) {
        if (_size == _max_size) {
            resize(_max_size * 2);
        }
        if (_size == 0) {
            _front = 0;
            _arr[0] = data;
        } else {
            // queue wraps around
            _arr[(_front + _size) % _max_size] = data;
        }
        _size++;
    }

    value_type dequeue() {
        if (_size == 0) throw std::exception();
        value_type data{_arr[_front]};
        _front = (_front + 1) % _max_size;
        _size--;
        if (_size < (_max_size / 4) && (_max_size > 40)) {
            resize(_max_size / 2);
        }
        return data;
    }

    size_t size() { return _size; }

    value_pointer to_array() {
        value_pointer p{new value_type[_size]};
        for (int i = 0; i < static_cast<int>(_size); i++) {
            p[i] = _arr[(_front + i) % _max_size];
        }
        return p;
    }
};

template <typename T>
class ArrayList {
    using value_type = T;
    using pointer_type = T *;
    using reference_type = T &;

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

    reference_type operator[](int i) const {
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

    pointer_type to_array() {
        pointer_type new_arr{new value_type[_size]};
        for (int i = 0; i < static_cast<int>(_size); i++) {
            new_arr[i] = _arr[i];
        }
        return new_arr;
    }
};
