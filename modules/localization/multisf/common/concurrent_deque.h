#pragma once

#include <iostream>
#include <deque>
#include <mutex>
#include <memory>

template <typename T>
class ConcurrentDeque {
public:
    ConcurrentDeque(const size_t &max_size = 1000) : _max_size(max_size) {}
    // TODO @dabing: 删除拷贝构造函数, 增加专用拷贝函数;
    ConcurrentDeque(const ConcurrentDeque<T> &c) {
        std::lock_guard<std::mutex> lock_outer(c._data_mutex);
        std::lock_guard<std::mutex> lock_inner(this->_data_mutex);
        this->_max_size = c._max_size;
        this->_deque = c._deque;
    }
    // ConcurrentDeque& copy() {
    //     std::lock_guard<std::mutex> lock_inner(this->_data_mutex);
    //     ConcurrentDeque<T> c(this->_max_size);
    //     std::lock_guard<std::mutex> lock_outer(c._data_mutex);
    //     c._deque = this->_deque;
    //     return c;
    // }

    ~ConcurrentDeque() = default;

    void insert(const T &data) {
        std::lock_guard<std::mutex> lock(_data_mutex);
        _deque.push_back(data);
        if (_deque.size() > _max_size) {
            _deque.pop_front();
        }
    }

    T &operator[](const size_t &pos) {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque[pos];
    }

    const T &operator[](const size_t &pos) const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque[pos];
    }

    T &at(const size_t &pos) {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.at(pos);
    }

    const T &at(const size_t &pos) const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.at(pos);
    }

    T &front() {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.front();
    }

    auto begin() {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.begin();
    }

    auto end() {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.end();
    }

    void pop_front() {
        std::lock_guard<std::mutex> lock(_data_mutex);
        if (!_deque.empty()) {
            _deque.pop_front();
        } else {
            // do nothing
        }
    }

    void pop_back() {
        std::lock_guard<std::mutex> lock(_data_mutex);
        if (!_deque.empty()) {
            _deque.pop_back();
        } else {
            // do nothing
        }
    }

    const T &front() const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.front();
    }

    const T &back() const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.back();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        return _deque.empty();
    }

    bool latest(T &data) const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        if (_deque.empty) {
            return false;
        }

        data = _deque.back();
        return true;
    }

    void clear() {
        std::lock_guard<std::mutex> lock(_data_mutex);
        _deque.clear();
    }

    std::vector<T> to_vector() const {
        std::lock_guard<std::mutex> lock(_data_mutex);
        std::vector<T> data_vec;
        data_vec.resize(_deque.size());
        for (size_t i = 0; i < _deque.size(); ++i) {
            data_vec[i] = _deque.at(i);
        }

        return data_vec;
    }

private:
    std::deque<T> _deque;
    size_t _max_size;
    mutable std::mutex _data_mutex{};
};
